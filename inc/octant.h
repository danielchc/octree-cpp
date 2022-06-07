#pragma once

#include "Kernel.h"
#include "bounds.h"
#include <array>
#include <vector>

class Octant {
private:
    unsigned int startIdx_{};
    unsigned int endIdx_{};
    unsigned int size_{};
    Bound *bound_{};
    Vector center_{};
    double radius_{};
    unsigned int nOctants_{};
    std::array<Octant *, 8> octants_{};


public:
    Octant();

    Octant(const Vector center, const double radius, const unsigned int startIdx,
           const unsigned int endIdx, const unsigned int size);

    ~Octant();

    const Bound getBound() const { return *bound_; };

    const Vector &getCenter() const { return center_; }

    void setCenter(const Vector &center) { center_ = center; }

    const double getRadius() const { return radius_; }

    void setRadius(double radius) { radius_ = radius; }

    const bool isLeaf() const { return nOctants_ == 0; }


    const unsigned int getStartIdx() const { return startIdx_; }

    void setStartIdx(const unsigned int startIdx) { startIdx_ = startIdx; }

    const unsigned int getEndIdx() const { return endIdx_; }

    void setEndIdx(const unsigned int endIdx) { endIdx_ = endIdx; }

    const unsigned int getSize() const { return size_; }

    void setSize(const unsigned int size) { size_ = size; }

    const unsigned int getOctantCount() const { return nOctants_; }

    void incrementOctantCount() { nOctants_++; }

    const std::array<Octant *, 8> &getOctants() const { return octants_; }

    void setOctant(const unsigned int index, Octant *octant) { octants_[index] = octant; }

    const Octant *getOctant(const unsigned int index) { return octants_[index]; }

    int octantIdx(Lpoint p);
};