//
// Created by miguelyermo on 25/3/21.
//

#ifndef RULE_BASED_CLASSIFIER_CPP_LPOINT_H
#define RULE_BASED_CLASSIFIER_CPP_LPOINT_H

#include "point.h"

class Region; // Region forward declaration

class Lpoint : public Point
{
	protected:
	double         I_{};              // Intensity
	unsigned short rn_{};             // Return Number
	unsigned short nor_{};            // Number of Returns (given pulse)
	unsigned short dir_{};            // Scan Direction Flag
	unsigned short edge_{};           // Edge of Flight Line
	unsigned short classification_{}; // Classification of the point
	char           sar_{};            // Scan Angle Rank
	unsigned char  ud_{};             // User Data
	unsigned short psId_{};           // Point Source ID
	unsigned int   gId_{};            // Group ID

	size_t   regionId_{}; // Region ID
	Region * region_{};   // Region to which the point belongs

	unsigned int r_{}; // Red channel (0-65535)
	unsigned int g_{}; // Green channel (0-65535)
	unsigned int b_{}; // Blue channel (0-65535)

	double ndvi_{}; // NDVI (Normalized Difference Vegetation Index) = (NIR - RED) / (NIR + RED)
	double ndwi_{}; // NDWI (Normalized Difference Water Index) = (GREEN - NIR) / (GREEN + NIR)

	// Normal vector
	Vector normal_{};

	// Curvature value
	double curvature_{}; // TODO: Revisar si se usa

	public:
	protected:
	double dtmZ_{};
	double slope_{};
	bool   hasSlope_{};

	double realZ_{}; // Real Z value

	double slopeDTM_{}; // Slope DTM value

	int fuelType_{}; // Prometheus fuel type

	// Flags to not duplicate points when drawing
	bool slopePainted = false;

	// Density of points in the volume around the point
	double pointDensity_{};

	// Quartil number. 1->1st quartil (< 25%), 2-> 2nd quartil, (>25 and <50)...
	unsigned short qn_{};

	// Is the point clusterized? (Belongs to a tower yet?)
	bool isClusterized_{};
	bool isNoise_{};

	// Is the point inside some polygon??
	bool isInPoly_{};

	// Powerlines
	bool wire_{}; // Is the point detected as a wire?
	bool cat_{};  // Is the point already included in a catenary?


	// Classification
	bool boundUsed_ = false; // Flag to indicate if it is a boundary
	bool border_    = false; // Flag to indicate if it is planar
	bool areaUsed_  = false; // Flag to indicate if it was used in area calculations

	public:
	// Default constructor
	Lpoint() : Point(){};
	Lpoint(size_t id, double x, double y, double z) : Point(id, x, y, z) {};
	Lpoint(double x, double y) : Point(x, y){};
	Lpoint(double x, double y, double z) : Point(x, y, z){};
	Lpoint(double x, double y, unsigned int fuelType) : Point(x, y), fuelType_(fuelType){};

	// Reading points from classification
	Lpoint(size_t id, double x, double y, double z, double I, unsigned int regionId, unsigned int classification) :
	  Point(id, x, y, z), I_(I), regionId_(regionId), classification_(classification){};

	// Reading points ISPRS format
	Lpoint(size_t id, double x, double y, double z, double I, double rn, double nor, unsigned int classification) :
	  Point(id, x, y, z), I_(I), rn_(rn), nor_(nor), classification_(classification){};

	Lpoint(size_t id, double x, double y, double z, double I, unsigned short rn, unsigned short nor, unsigned char dir,
	       unsigned char edge, unsigned short classification, unsigned int regionId) :
	  Point(id, x, y, z),
	  I_(I), rn_(rn), nor_(nor), dir_(dir), edge_(edge), classification_(classification), regionId_(regionId){};

	Lpoint(size_t id, double x, double y, double z, double realZ, double I, unsigned short rn, unsigned short nor,
	       unsigned char dir, unsigned char edge, unsigned short classification, size_t regionId) :
	  Point(id, x, y, z),
	  realZ_(realZ), I_(I), rn_(rn), nor_(nor), dir_(dir), edge_(edge), classification_(classification),
	  regionId_(regionId){};

	// Reading standard classified cloud
	Lpoint(size_t id, double x, double y, double z, double I, unsigned short rn, unsigned short nor, unsigned char dir,
	       unsigned char edge, unsigned short classification) :
	  Point(id, x, y, z),
	  I_(I), rn_(rn), nor_(nor), dir_(dir), edge_(edge), classification_(classification){};

	// Reading classified cloud with RGB
	Lpoint(size_t id, double x, double y, double z, double I, unsigned short rn, unsigned short nor, unsigned char dir,
	       unsigned char edge, unsigned short classification, unsigned int r, unsigned int g, unsigned int b) :
	  Point(id, x, y, z),
	  I_(I), rn_(rn), nor_(nor), dir_(dir), edge_(edge), classification_(classification), r_(r), g_(g), b_(b){};

	// Reading segmentation output.
	Lpoint(size_t id, double x, double y, double z, double I, unsigned short rn, unsigned short nor, unsigned char dir,
	       unsigned char edge, unsigned short classification, size_t regionId, double nx, double ny, double nz) :
	  Point(id, x, y, z),
	  regionId_(regionId), I_(I), rn_(rn), nor_(nor), dir_(dir), edge_(edge), classification_(classification)
	{
		normal_.setX(nx);
		normal_.setY(ny);
		normal_.setZ(nz);
	}

	// Reading segmentation RGB output.
	Lpoint(size_t id, double x, double y, double z, double I, unsigned short rn, unsigned short nor, unsigned char dir,
	       unsigned char edge, unsigned short classification, size_t regionId, unsigned int r, unsigned int g,
	       unsigned int b, double nx, double ny, double nz) :
	  Point(id, x, y, z),
	  I_(I), rn_(rn), nor_(nor), dir_(dir), edge_(edge), classification_(classification), regionId_(regionId), r_(r),
	  g_(g), b_(b)
	{
		normal_.setX(nx);
		normal_.setY(ny);
		normal_.setZ(nz);
	}

	// Reading Point Data Record Format 2 (Babcock / Coremain request)
	Lpoint(size_t id, double x, double y, double z, double I, unsigned short rn, unsigned short nor, unsigned char dir,
	       unsigned char edge, unsigned short classification, char sar, unsigned char ud, unsigned short psId,
	       unsigned int r, unsigned int g, unsigned int b) :
	  Point(id, x, y, z),
	  I_(I), rn_(rn), nor_(nor), dir_(dir), edge_(edge), classification_(classification), sar_(sar), ud_(ud), psId_(psId),
	  r_(r), g_(g), b_(b){};

	// Setters and getters
	inline double I() const { return I_; }

	// TODO: delete gId references
	inline unsigned int   gId() const { return gId_; }
	inline void           setGId(unsigned int gId) { gId_ = gId; }
	inline unsigned short getClass() const { return classification_; }
	inline void           setClass(unsigned short classification) { classification_ = classification; }
	inline double         pointDensity() const { return pointDensity_; }
	inline void           setPointDensity(double pointDensity) { pointDensity_ = pointDensity; }
	inline unsigned short qn() const { return qn_; }
	inline void           setQn(unsigned short qn) { qn_ = qn; }
	inline unsigned short rn() const { return rn_; }
	inline unsigned short nor() const { return nor_; }
	inline unsigned short dir() const { return dir_; }
	inline unsigned short edge() const { return edge_; }
	inline bool           isClusterized() const { return isClusterized_; }
	inline void           isClusterized(bool isClusterized) { isClusterized_ = isClusterized; }
	inline bool           isNoise() const { return isNoise_; }
	inline void           isNoise(bool isNoise) { isNoise_ = isNoise; }
	inline bool           isInPoly() const { return isInPoly_; }
	inline void           isInPoly(bool isInPoly) { isInPoly_ = isInPoly; }
	inline double         getDtmZ() const { return dtmZ_; }
	inline void           setDtmZ(double dtmZ) { dtmZ_ = dtmZ; }
	inline double         getSlope() const { return slope_; }
	inline void           setSlope(double slope) { slope_ = slope; }
	inline void           setSlopeDTM(double slopeDTM) { slopeDTM_ = slopeDTM; }
	inline double         getSlopeDTM() const { return slopeDTM_; }
	inline void           setDTMSlope(double slopeDTM) { slopeDTM_ = slopeDTM; }
	inline bool           hasSlope() const { return hasSlope_; }
	inline void           hasSlope(bool hasSlope) { hasSlope_ = hasSlope; }
	inline bool           isSlopePainted() const { return slopePainted; }
	inline void           setSlopePainted(bool slopePainted) { Lpoint::slopePainted = slopePainted; }
	inline double         getRealZ() const { return realZ_; }
	inline void           setRealZ(double realZ) { realZ_ = realZ; }
	inline const int      getFuelType() const { return fuelType_; }
	inline void           setFuelType(int fuelType) { fuelType_ = fuelType; }
	inline bool           isWire() const { return wire_; }
	inline void           setWire(bool wire) { wire_ = wire; }
	inline bool           isCat() const { return cat_; }
	inline void           setCat(bool cat) { cat_ = cat; }
	inline bool           isBoundUsed() const { return boundUsed_; }
	inline void           setBoundUsed(bool boundUser) { boundUsed_ = boundUser; }
	inline bool           isBorder() const { return border_; }
	inline void           setBorder(bool isBorder) { border_ = isBorder; }
	inline unsigned int   getRegionId() const { return regionId_; };
	inline Region *       getRegion() const { return region_; };
	inline void           setRegionId(unsigned int regionId) { regionId_ = regionId; };
	inline void           setRegion(Region * r) { region_ = r; };
	inline bool           isAreaUsed() const { return areaUsed_; }
	inline void           setAreaUsed(bool areaUsed) { areaUsed_ = areaUsed; }
	inline unsigned int   getR() const { return r_; }
	inline void           setR(unsigned int r) { r_ = r; }
	inline unsigned int   getG() const { return g_; }
	inline void           setG(unsigned int g) { g_ = g; }
	inline unsigned int   getB() const { return b_; }
	inline void           setB(unsigned int b) { b_ = b; }
	const Vector &        getNormal() const { return normal_; }
	void                  setNormal(const Vector & normal) { normal_ = normal; }
	inline double         getCurvature() const { return curvature_; }
	inline void           setCurvature(double curvature) { curvature_ = curvature; }
	void                  setEigenvalues(const std::vector<double> & eigenvalues) {}
	inline double         getNDVI() const { return ndvi_; }
	inline void           setNDVI(double ndvi) { ndvi_ = ndvi; }
	inline double         getNDWI() const { return ndwi_; }
	inline void           setNDWI(double ndwi) { ndwi_ = ndwi; }

	void                  computeNDVI();
	void                  computeNDWI();
};

std::vector<Lpoint *> filterGroundRoadPoints(std::vector<Lpoint> & points);
std::vector<Lpoint *> filterGroundPoints(std::vector<Lpoint> & points);
std::vector<Lpoint *> filterVegPoints(std::vector<Lpoint> & points);
bool                  isVegetation(unsigned int type);


#endif //RULE_BASED_CLASSIFIER_CPP_LPOINT_H
