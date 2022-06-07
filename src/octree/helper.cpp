#include "helper.h"

#include "Lpoint.h"

/** Calculate the radius in each axis and save the max radius of the bounding
 * box */
Vector mbbRadii(Vector &min, Vector &max, double &maxRadius) {
	double x = (max.getX() - min.getX()) / 2.0;
	double y = (max.getY() - min.getY()) / 2.0;
	double z = (max.getZ() - min.getZ()) / 2.0;

	Vector radii(x, y, z);

	if (radii.getX() >= radii.getY() && radii.getX() >= radii.getZ()) {
		maxRadius = radii.getX();
	} else if (radii.getY() >= radii.getX() && radii.getY() >= radii.getZ()) {
		maxRadius = radii.getY();
	} else {
		maxRadius = radii.getZ();
	}

	return radii;
}

/** Calculate the center of the bounding box */
Vector mbbCenter(Vector &min, Vector &radius) {
	return Vector(min.getX() + radius.getX(), min.getY() + radius.getY(),
				  min.getZ() + radius.getZ());
}

/**
 * Computes the minimum bounding box of a set of points
 * @param points Array of points
 * @param numPoints Number of points
 * @param[out] maxRadius Maximum radius of the bounding box
 * @return (Vector) center of the bounding box
 */
Vector mbb(const std::vector<Lpoint> &points, double &maxRadius) {
	Vector center, min, max, radii;

	min.setX(std::numeric_limits<double>::max());
	min.setY(std::numeric_limits<double>::max());
	min.setZ(std::numeric_limits<double>::max());

	max.setX(-std::numeric_limits<double>::max());
	max.setY(-std::numeric_limits<double>::max());
	max.setZ(-std::numeric_limits<double>::max());

	for (const Point &p : points) {
		if (p.getX() < min.getX()) min.setX(p.getX());
		if (p.getX() > max.getX()) max.setX(p.getX());
		if (p.getY() < min.getY()) min.setY(p.getY());
		if (p.getY() > max.getY()) max.setY(p.getY());
		if (p.getZ() < min.getZ()) min.setZ(p.getZ());
		if (p.getZ() > max.getZ()) max.setZ(p.getZ());
	}

	radii = mbbRadii(min, max, maxRadius);
	center = mbbCenter(min, radii);
	return center;
}
