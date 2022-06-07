//
// Created by miguel.yermo on 6/03/20.
//

/*
* FILENAME :  util.h  
* PROJECT  :  rule-based-classifier-cpp
* DESCRIPTION :
*  
*
*
*
*
* AUTHOR :    Miguel Yermo        START DATE : 14:17 6/03/20
*
*/

#ifndef CPP_UTIL_H
#define CPP_UTIL_H

#include <algorithm>

// Memory Handling

using namespace std;

namespace mem
{
template<class C>
void free(C & c)
{
	c.clear();
	c.shrink_to_fit();
}
} // namespace mem

inline int isNumber(double x)
{
	return (!isnan(x) && !isinf(x));
}

inline double ccw(Lpoint * p1, Lpoint * p2, Lpoint * p3)
/**
 * Counter-clockwise situation of 3 points (ccw > 0, cw < 0, colinear = 0)
 */
{
	return (p2->getX() - p1->getX()) * (p3->getY() - p1->getY()) - (p2->getY() - p1->getY()) * (p3->getX() - p1->getX());
}

// TODO: put onRange and onIntensity in the same function? (the only use of onRange is here...)
inline bool onRange(double value, double offset, double center)
{
	return (value >= (center - offset) && value <= (center + offset));
}

inline bool onIntensity(float int1, float int2, float interval)
{
  float offset = max(int1, int2) * interval;

  return onRange(int1, offset, int2);
}

inline bool onDegree(Vector & normal, double interval, Vector & neighNormal)
{
  Vector degrees = normal.vectorAngles();
  Vector epiDegrees = neighNormal.vectorAngles();
  Vector diffs(fabs(epiDegrees.getX()-degrees.getX()), fabs(epiDegrees.getY()-degrees.getY()), fabs(epiDegrees.getZ() - degrees.getZ()));

  return (diffs.getX() < interval && diffs.getY() < interval && diffs.getZ() < interval);
}

#endif //CPP_UTIL_H
