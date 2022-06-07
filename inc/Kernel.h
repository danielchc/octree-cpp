#pragma once

#include "Lpoint.h"
#include "bounds.h"
#include "octant.h"
#include <memory>

class Octant;
class Bound;

enum Kernel_t { circle, sphere, square, cube };


class AbstractKernel{
   public:
	double radius{};  // Search Radius
	Point center{};	  // Center of the kernel
	Bound *inner{};	  // Bounding Cube inside the given kernel
	Bound *outter{};  // Bounding Cube around the given kernel
	AbstractKernel(const Point &center, const double radius)
		: center(center), radius(radius) {
		outter = new Bound(center, radius);
	};
	virtual const bool isInside(const Point &p)
		const = 0;
	virtual const bool boxOverlap(const Octant &octant) const = 0;
	virtual const bool contains(const Octant &octant) const = 0;
};

class Kernel2D : public AbstractKernel {
   public:
	Kernel2D(const Point &center, const double radius)
		: AbstractKernel(center, radius){};

	virtual const bool boxOverlap(const Octant &octant) const override;
	virtual const bool contains(const Octant &octant) const override;
};

class Kernel3D : public AbstractKernel {
   public:
	Kernel3D(const Point &center, const double radius)
		: AbstractKernel(center, radius){};

	virtual const bool boxOverlap(const Octant &octant) const override;
	virtual const bool contains(const Octant &octant) const override;
};

class CircularKernel : public Kernel2D {
   public:
	CircularKernel(const Point &center, const double radius)
		: Kernel2D(center, radius) {
		inner = new Bound(center, (radius * sqrt(2)) * 0.5f);
	};

	virtual const bool isInside(const Point &p) const override;
};

class SphereKernel : public Kernel3D {
   public:
	SphereKernel(const Point &center, const double radius)
		: Kernel3D(center, radius) {
		inner = new Bound(center, radius / sqrt(3));
	};

	virtual const bool isInside(const Point &p) const override;
};

class SquareKernel : public Kernel2D {
   public:
	SquareKernel(const Point &center, const double radius)
		: Kernel2D(center, radius) {
		inner = new Bound(center, radius);
	};

	virtual const bool isInside(const Point &p) const override;
};

class CubeKernel : public Kernel3D {
   public:
	CubeKernel(const Point &center, const double radius)
		: Kernel3D(center, radius) {
		inner = new Bound(center, radius);
	};

	virtual const bool isInside(const Point &p) const override;
};

std::unique_ptr<AbstractKernel> kernelFactory(const Point &center,
											  const double radius,
											  const Kernel_t &type);
