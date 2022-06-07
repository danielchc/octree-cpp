#pragma once
#include "Kernel.h"
#include "bounds.h"
#include <vector>


Vector mbbCenter(Vector & min, Vector & radius);
Vector mbbRadii(Vector & min, Vector & max, double & maxRadius);
Vector mbb(const std::vector<Lpoint> & points, double & maxRadius);


