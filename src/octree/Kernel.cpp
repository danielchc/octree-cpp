#include "Kernel.h"

/**
 * Dado un tipo de kernel, creo un kernel de ese tipo
 * @param center
 * @param radius
 * @param type
 * @return
 */
std::unique_ptr<AbstractKernel> kernelFactory(const Point &center,
											  const double radius,
											  const Kernel_t &type) {
	switch (type) {
		case Kernel_t::square:
			return std::make_unique<SquareKernel>(center, radius);
		case Kernel_t::circle:
			return std::make_unique<CircularKernel>(center, radius);
		case Kernel_t::cube:
			return std::make_unique<CubeKernel>(center, radius);
		case Kernel_t::sphere:
			return std::make_unique<SphereKernel>(center, radius);
		default:
			return nullptr;
	}
}

/**
 * Comproba se un octante dado se solapa co núcleo dado en 2 dimensións
 * @param octant
 * @return
 */
const bool Kernel2D::boxOverlap(const Octant &octant) const {
	if (octant.getBound().maxX() < outter->minX() ||
		octant.getBound().maxY() < outter->minY())
		return false;
	if (octant.getBound().minX() > outter->maxX() ||
		octant.getBound().minY() > outter->maxY())
		return false;

	return true;
}

/**
 * Comproba se un octante dado se solapa co núcleo dado en 3 dimensións
 * @param octant
 * @return
 */
const bool Kernel3D::boxOverlap(const Octant &octant) const {
	if (octant.getBound().maxX() < outter->minX() ||
		octant.getBound().maxY() < outter->minY() ||
		octant.getBound().maxZ() < outter->minZ())
		return false;
	if (octant.getBound().minX() > outter->maxX() ||
		octant.getBound().minY() > outter->maxY() ||
		octant.getBound().minZ() > outter->maxZ())
		return false;

	return true;
}


/**
 * Comproba se un octante dado está contido no kernel en 2 dimensions
 * @param octant
 * @return
 */
const bool Kernel2D::contains(const Octant &octant) const {
	return (octant.getBound().minX() > inner->minX() &&
			octant.getBound().minY() > inner->minY()) &&
		   (octant.getBound().maxX() < inner->maxX() &&
			octant.getBound().maxY() < inner->maxY());
}

/**
 * Comproba se un octante dado está contido no kernel en 3 dimensions
 * @param octant
 * @return
 */
const bool Kernel3D::contains(const Octant &octant) const {
	return (octant.getBound().minX() > inner->minX() &&
			octant.getBound().minY() > inner->minY() &&
			octant.getBound().minZ() > inner->minZ()) &&
		   (octant.getBound().maxX() < inner->maxX() &&
			octant.getBound().maxY() < inner->maxY() &&
			octant.getBound().maxZ() < inner->maxZ());
}

/**
 * @brief Comproba se un punto dado está dentro do kernel de forma cadrada
 * @param p
 * @return
 */
const bool SquareKernel::isInside(const Point &p) const {
	return (p.getX() > inner->minX() && p.getY() > inner->minY()) &&
		   (p.getX() < inner->maxX() && p.getY() < inner->maxY());
}

/**
 * @brief Comproba se un punto dado está dentro do kernel de forma cubo
 * @param p
 * @return
 */
const bool CubeKernel::isInside(const Point &p) const {
	return (p.getX() > inner->minX() && p.getY() > inner->minY() &&
			p.getZ() > inner->minZ()) &&
		   (p.getX() < inner->maxX() && p.getY() < inner->maxY() &&
			p.getZ() < inner->maxZ());
};

/**
 * @brief Comproba se un punto dado está dentro do kernel de forma círculo
 * @param p
 * @return
 */
const bool CircularKernel::isInside(const Point &p) const {
	return (p.getX() - center.getX()) * (p.getX() - center.getX()) +
			   (p.getY() - center.getY()) * (p.getY() - center.getY()) <
		   radius * radius;
}

/**
 * @brief Comproba se un punto dado está dentro do kernel de forma esfera
 * @param p
 * @return
 */
const bool SphereKernel::isInside(const Point &p) const {
	return (p.getX() - center.getX()) * (p.getX() - center.getX()) +
			   (p.getY() - center.getY()) * (p.getY() - center.getY()) +
			   (p.getZ() - center.getZ()) * (p.getZ() - center.getZ()) <
		   radius * radius;
}