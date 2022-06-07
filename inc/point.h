#ifndef CPP_POINT_H
#define CPP_POINT_H

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>


typedef class Point Vector; // Point and Vector are exactly the same entity, but this is done
                            // to preserve mathematical correctness

class Point
{
	protected:
	unsigned int id_{}; // Id of the point (in order of reading)
	double       x_{};  // X Coordinate
	double       y_{};  // Y Coordinate
	double       z_{};  // Z Coordinate

	public:
	Point() = default;
	explicit Point(unsigned int id) : id_(id){};

	// 2D Geometric constructor ( Z = 0.0 )
	Point(double x, double y) : x_(x), y_(y), z_(0.0){};

	// 3D Geometric constructor
	Point(double x, double y, double z) : x_(x), y_(y), z_(z){};

	// 3D Geometric constructor with ID
	Point(unsigned int id, double x, double y, double z) : id_(id), x_(x), y_(y), z_(z){};


	// Point Methods
	double distance2D(const Point & p) const;
	double distance3D(const Point & p) const;
	double distanceToLine(const Point & l1, const Point & l2) const;
	Point getDest(Vector & v, double distance) const;

	// Vector Methods
	Vector perpenVector() const;
	double norm2D() const ;
	double norm3D() const;
	void normalize2D();
	void normalize3D();
  double dotProduct2D(const Vector & vec) const;
	Point vectorAngles() const;


	// Overload << operator for Point.
	friend std::ostream & operator<<(std::ostream & out, const Point & p)
	{
		out << p.x_ << "\t" << p.y_ << "\t" << p.z_;
		return out;
	}


  // Overload << operator for Point*
  friend std::ostream & operator<<(std::ostream & out, const Point * p)
  {
    out << *p;
    return out;
  }

	friend Point abs(const Point & p)
  {
		return Point(std::abs(p.x_), std::abs(p.y_), std::abs(p.z_));
	}

	// Operator overloading (pointer version done with dereferencing in place)
  Point operator+(const Point & v) const { return Point(x_ + v.getX(), y_ + v.getY(), z_ + v.getZ()); }
  Point operator-(const Point & v) const { return Point(x_ - v.getX(), y_ - v.getY(), z_ - v.getZ()); }
	Point & operator+=(const Point & p)
  {
		x_ += p.getX();
		y_ += p.getY();
		z_ += p.getZ();

		return *this;
	}

	Point & operator/=(const double val)
	{
		x_ /= val;
		y_ /= val;
		z_ /= val;

		return *this;
	}

	friend Point operator-(const Point & lhs, const double val)
	{
		return Point(lhs.x_ - val, lhs.y_ - val, lhs.z_ - val);
	}

	friend Point operator+(const Point & lhs, const double val)
	{
		return Point(lhs.x_ + val, lhs.y_ + val, lhs.z_ + val);
	}

	friend Point operator-(const double val, const Point & rhs)
	{
		return Point(rhs.x_ - val, rhs.y_ - val, rhs.z_ - val);
	}

	friend Point operator+(const double val, const Point & rhs)
	{
		return Point(rhs.x_ + val, rhs.y_ + val, rhs.z_ + val);
	}

	friend bool operator==(const Point & lhs, const Point & rhs)
	{
		return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_ && lhs.z_ == rhs.z_;
	}

  // Multiplication of vector and a scalar
  template<typename T>
  Vector operator*(const T scalar) const { return Vector(x_ * scalar, y_ * scalar, z_ * scalar); }

  // Division of vector and a scalar
  template<typename T>
  Vector operator/(const T scalar) const { return Vector(x_ / scalar, y_ / scalar, z_ / scalar); }

  template<typename T>
  void operator/=(const T scalar) {x_ /= scalar, y_ /= scalar, z_ /= scalar; }

	// Getters and setters
	inline unsigned int id() const { return id_; }
	inline void         id(unsigned int id) { id_ = id; }
	inline double       getX() const { return x_; }
	inline void         setX(double x) { x_ = x; }
	inline double       getY() const { return y_; }
	inline void         setY(double y) { y_ = y; }
	inline double       getZ() const { return z_; }
	inline void         setZ(double z) { z_ = z; }
};

#endif //CPP_POINT_H
