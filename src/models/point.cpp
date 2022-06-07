//
// Created by miguelyermo on 26/3/20.
//

#include "point.h"
// ===== Geometric Methods =====

/* Gets the perpendicular vector (XY plane) */
Vector Vector::perpenVector() const
{
	Vector p(-y_, x_, z_);
	return p;
}

/* Returns the 2D norm of the vector */
double Vector::norm2D() const { return sqrt(x_ * x_ + y_ * y_); }

/* Returns the 3D norm of the vector */
double Vector::norm3D() const { return sqrt(x_ * x_ + y_ * y_ + z_ * z_); }

/* Normalization of the vector in two dimensions */
void Vector::normalize2D() { *this /= norm2D(); }

/* Normalization of the vector in three dimensions */
void Vector::normalize3D() { *this /= norm3D(); }

/* Dot product in 2D */
double Vector::dotProduct2D(const Vector & vec) const { return x_ * vec.getX() + y_ * vec.getY(); }

/* 2D distance between two points */
double Point::distance2D(const Point & p) const
{
	double diffX = x_ - p.getX();
	double diffY = y_ - p.getY();

	return sqrt(diffX * diffX + diffY * diffY);
}

/* 3D distance between two points */
double Point::distance3D(const Point & p) const
{
	double diffX = x_ - p.getX();
	double diffY = y_ - p.getY();
	double diffZ = z_ - p.getZ();

	return sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
}

/* Returns the angle formed by each coordinate with its corresponding edge */
Vector Vector::vectorAngles() const
{
	Vector out{};

	double denom = norm3D();

	if (denom != 0)
	{
		out.setX(acos(x_ / denom) * 180.0 / M_PI);
		out.setY(acos(y_ / denom) * 180.0 / M_PI);
		out.setZ(acos(z_ / denom) * 180.0 / M_PI);
	}

	return out;
}

double Point::distanceToLine(const Point & l1, const Point & l2) const
/**
 * Computes the distance of this point to the line defined by two points
 * @param l1 Origin of the line
 * @param l2 End of the line
 * @return
 */
{
	double y2_y1 = l2.getY() - l1.getY();
	double x2_x1 = l2.getX() - l1.getX();

	return fabs(y2_y1 * x_ - x2_x1 * y_ + l2.getX() * l1.getY() - l2.getY() * l1.getX()) /
	       sqrt(y2_y1 * y2_y1 + x2_x1 * x2_x1);
}

Point Point::getDest(Vector & v, double distance) const
/**
 * Get the destination point of moving a point form a vector a given distance
*/
{
	v.normalize2D();
	Point dest(x_ + v.getX() * distance, y_ + v.getY() * distance, z_);
	return dest;
}