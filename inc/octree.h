#pragma once

#include "Lpoint.h"
#include "point.h"
#include "Kernel.h"
#include "octant.h"
#include "bounds.h"
#include "helper.h"
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

class Octree {
protected:
    Octant *root_{};
    std::vector<Lpoint*> points_{};
    unsigned int numPoints_{};
    unsigned int max_bucket_{};
    std::vector<unsigned int> successors_{};

    void insertPoints(std::vector<Lpoint> &points);

    void buildOctree(Vector center, double radius);

public:
    Octree(unsigned int max_bucket = 32);

    Octree(std::vector<Lpoint> &points, unsigned int max_bucket = 32);

    ~Octree();

    const std::vector<Lpoint*> &getPoints() const { return points_; }

    unsigned int getNumPoints() const { return numPoints_; }

    const Vector &getCenter() const { return root_->getCenter(); }

    const double getRadius() const { return root_->getRadius(); }

    Lpoint* getPoint(const unsigned int i) const { return points_[i]; }


    Octant *
    createOctant(Vector center, double radius, unsigned int startIdx, unsigned int endIdx, unsigned int size);

    void writeOctree(std::ofstream &f, size_t index) const;


    void writeOctree(const Octant *octant, std::ofstream &f, size_t index) const;


    void neighbors(Octant *octant, std::unique_ptr<AbstractKernel> &k, std::vector<Lpoint *> &ptsInside) const;

    std::vector<Lpoint *> searchNeighbors(const Point &p, double radius, const Kernel_t &k_t) const;

};
