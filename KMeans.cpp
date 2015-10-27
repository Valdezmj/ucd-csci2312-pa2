//
// Created by Michael Valdez on 10/16/15.
//

#include "KMeans.h"
#include <fstream>
#include <sstream>
#include <cmath>

namespace Clustering {
    double KMeans::SCORE_DIFF_THRESHOLD = .001;
    Clustering::KMeans::KMeans(int __i, double __thresh, unsigned int __pd, std::string __if, std::string __ot) {
        __size = __i;
        __rf = __if;
        __of = __ot;
        SCORE_DIFF_THRESHOLD = __thresh;
        __ps = new Cluster(__pd);
        readFile();
        __ps->pickPoints(__size - 1, __centroids);
        if (__i > 1) {
            createClusters();
        }
    }

    void Clustering::KMeans::start() {
        __ps->computeCentroid();
        if (__size > 1) {
            __sd = SCORE_DIFF_THRESHOLD + 1;
            __s = 0;

            while (__sd >= SCORE_DIFF_THRESHOLD) {
                //loop through clusters
                Cluster::Move *it;
                double __disMin, __temp;
                Cluster *__closestCentroid = nullptr;

                for (int i = 0; i < __ps->getSize(); i++) {
                    __disMin = (*(*__ps)[i]).distanceTo(__ps->getCentroid());
                    for (int j = 0; j < __size - 1; j++) {
                        __temp = (*(*__ps)[i]).distanceTo(__cl[j].getCentroid());
                        if (__temp < __disMin) {
                            __disMin = __temp;
                            __closestCentroid = &__cl[j];
                        }

                    }

                    if (__closestCentroid != nullptr && __closestCentroid->getCentroid() != __ps->getCentroid()) {
                        it = new Cluster::Move((*__ps)[i], __ps, __closestCentroid);
                        it->perform();
                        delete it;
                        i--;
                    }
                    __closestCentroid = nullptr;
                }

                __closestCentroid = nullptr;

                for (int i = 0; i < __size - 1; i++) {
                    for (int j = 0; j < __cl[i].getSize(); j++) {
                        __disMin = __cl[i][j]->distanceTo(__cl[i].getCentroid());
                        for (int k = i + 1; k < __size - 1; k++) {
                            __temp = __cl[i][j]->distanceTo(__cl[k].getCentroid());
                            if (__temp < __disMin) {
                                __disMin = __temp;
                                __closestCentroid = &__cl[k];
                            }
                        }
                        if (__closestCentroid != nullptr && __closestCentroid->getCentroid() != __cl[i].getCentroid()) {
                            it = new Cluster::Move(__cl[i][j], &__cl[i], __closestCentroid);
                            it->perform();
                            delete it;
                            j--;
                        }
                        __closestCentroid = nullptr;
                    }
                }

                if (!__ps->checkCentroid()) {
                    __ps->computeCentroid();
                }
                for (int i = 0; i < __size - 1; i++) {
                    if (!__cl[i].checkCentroid()) {
                        __cl[i].computeCentroid();
                    }
                }
                __sd = std::abs(__s - computeClusteringScore());
                __s = computeClusteringScore();
            }
        }
        writeFile();
    }

    void Clustering::KMeans::readFile() {
        std::ifstream __read_File(__rf, std::ios::in);
        while (!__read_File.eof()) {
            __read_File >> *__ps;
        }
        __read_File.close();
    }

    void Clustering::KMeans::createClusters() {
        __cl = new Cluster[__size - 1];

        for (int i = 0; i < __size - 1; i++) {
            __cl[i].setPointDimension(__ps->getPointDimension());
            __cl[i].setCentroid(*__centroids[i]);

        }
    }

    double Clustering::KMeans::computeClusteringScore() {
        double __bCV = 0;
        double __dIn = 0, __dOut = 0, __pIn = 0, __pOut = 0;

        for (int i = 0; i < __size - 1; i++) {
            __dIn += __cl[i].intraClusterDistance();
            __pIn += __cl[i].getClusterEdges();
            for (int j = i + 1; j < __size; j++) {
                __dOut += interClusterDistance(__cl[i], __cl[j]);
                __pOut += __cl[i].getSize() * __cl[j].getSize();
            }
        }
        for (int i = 0; i < __ps->getSize(); i++) {
            __dIn += __ps->intraClusterDistance();
            __pIn += __ps->getClusterEdges();
            for (int j = 0; j < __size - 1; j++) {
                __dOut += interClusterDistance(*__ps, __cl[j]);
                __pOut += __cl[j].getSize() * __ps->getSize();
            }
        }

        if (__size != 1) {
            __bCV = (__dIn / __pIn) / (__dOut / __pOut);
        } else {
            __bCV = 0;
        }
        return __bCV;
    }

    void Clustering::KMeans::writeFile() {
        std::ofstream file(__of, std::ios::out);

        file << *__ps;

        for (int i = 0; i < __size - 1; i++) {
            file << __cl[i];
        }

        file.close();
    }

    KMeans::~KMeans() {
        delete [] __cl;
        delete __ps;
        delete [] __centroids;
    }
}