//
// Created by miguelyermo on 25/3/21.
//

#include "Lpoint.h"
#include "laspec.h"

std::vector<Lpoint *> filterGroundRoadPoints(std::vector<Lpoint> & points)
{
	std::vector<Lpoint *> grPoints;
	for (Lpoint & p : points)
	{
		if (p.getClass() == GROUND || p.getClass() == ROAD)
		{
			grPoints.emplace_back(&p);
		}
	}

	return grPoints;
}

std::vector<Lpoint *> filterGroundPoints(std::vector<Lpoint> & points)
{
	std::vector<Lpoint *> grPoints;
	for (Lpoint & p : points)
	{
		if (p.getClass() == GROUND)
		{
			grPoints.emplace_back(&p);
		}
	}

	return grPoints;
}

bool isVegetation(unsigned int type)
{
	return type == GRASS || type == LOW_VEG || type == MED_VEG || type == HIGH_VEG || type == TREE;
}

std::vector<Lpoint *> filterVegPoints(std::vector<Lpoint> & points)
{
	std::vector<Lpoint *> vegPoints;
	for (Lpoint & p : points)
	{
		if (isVegetation(p.getClass()))
		{
			vegPoints.emplace_back(&p);
		}
	}

	return vegPoints;
}

void Lpoint::computeNDVI()
/**
 *  It obtains the NDVI (Normalized Difference Vegetation Index) using RGB and NIR information
 *  NDVI = (NIR - RED) / (NIR + RED)
 *
 *  Note: usually, the NIR info is in the Red RGB channel, so the rest of the values are shifted one position,
 *  losing the last RGB value.
 */
{
	double ndvi = 0.0f, r = r_, g = g_;
	if ((r + g) > 0) ndvi = (double) (r - g) / (double) (r + g);

	ndvi_ = ndvi;
};

void Lpoint::computeNDWI()
/**
 *  It obtains the NDWI (Normalized Difference Water Index) using RGB and NIR information
 *  NDWI = (GREEN - NIR) / (GREEN + NIR)
 *
 *  Note: usually, the NIR info is in the Red RGB channel, so the rest of the values are shifted one position,
 *  losing the last RGB value.
 */
{
	double ndwi = 0.0f, r = r_, b = b_;
	if ((b + r) > 0) ndwi = double(b - r) / double(b + r);

	ndwi_ = ndwi;
}