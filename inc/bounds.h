#pragma once
#include "Lpoint.h"
#include <vector>

class Bound {
	private:
		Vector min_{};
		Vector max_{};

	public:
        Bound(){};
        Bound(const Point &min, const Point &max) : min_(min), max_(max){};
        Bound(const Point &p, const float radius) {
            min_=p-radius;
            max_=p+radius;
        }


		const			Vector & min() const { return min_; }
		const 			Vector & max() const { return max_; }

		double			minX() const { return min_.getX(); }
		double			minY() const { return min_.getY(); }
		double			minZ() const { return min_.getZ(); }
		double			maxX() const { return max_.getX(); }
		double			maxY() const { return max_.getY(); }
		double			maxZ() const { return max_.getZ(); }
};
