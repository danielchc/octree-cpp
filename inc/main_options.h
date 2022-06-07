//
// Created by miguelyermo on 11/3/20.
//

/*
* FILENAME :  main_options.h  
* PROJECT  :  rule-based-classifier-cpp
* DESCRIPTION :
*  
*
*
*
*
* AUTHOR :    Miguel Yermo        START DATE : 18:50 11/3/20
*
*/

#ifndef CPP_MAIN_OPTIONS_H
#define CPP_MAIN_OPTIONS_H

#include <filesystem>
#include <getopt.h>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

class main_options
{
	public:
	// Files & paths
	fs::path      inputFile{};
	unsigned char userOutputDirName{};
	fs::path      outputDirName{};
	bool          userCoordinatesFile{};
	fs::path      coordinatesFile{}; // File containing start/end coordinates o path searching.
	bool          userExclusionDir{};
	fs::path      exclusionDir{};
	bool          userDtmFile{};
	std::string   dtmFile{};
	bool          debug{};

	std::string vegGroundTruthShp{};
	std::string vegGroundTruthDbf{};
	std::string vegGroundTruthxyz{};

	// Numerical parameters
	bool         userNumPoints{};
	unsigned int numPoints{};
	uint8_t      numCols{};

	// Path Searching parameters
	float        maxEdgeSlope{};
	double       focusWidth{};
	double       overSegmentRadius{};
	unsigned int overSegmentMaxPoints{};
	double       maxEdgeSlopeDegrees{};
	float        roadPointRatio{};
	float        traffPointRatio{};
	float        roughnessLimit{};

	// Path weight factors
	double slopeFactor05{};
	double slopeFactor510{};
	double slopeFactor1015{};
	double slopeFactor1520{};
	double slopeFactor20{};
	double roadWeightFactor{};
	double roughnessWeightFactor{};

	// Powerline Detection Parameters
	double neighborhoodRadius{};
	double wireThickness{};
	double heightThreshold{};
	double ratioThreshold{};
	double candidatesRadioThreshold{};
	double maxCatDistance{};
	double maxCatAngle{};
	double powerlineMaxWidth{};
	double powerlineMaxAngle{};

	// Hough transform parameters
	float  angleStep{};
	float  gridSpacing{};
	size_t numMinCatPoints{};

	// Tower Detection Parameters
	double       dbscanDistance{};
	unsigned int dbscanMinPoints{};
	double       minHeightDifference{};
	float        maxTowerAngle{};
	double       innerX{};
	double       innerY{};
	double       innerZ{};
	double       outerX{};
	double       outerY{};
	double       outerZ{};

	double low_veg_min_height{};
	double med_veg_min_height{};
	double high_veg_min_height{};
	double tree_min_height{};
	double low_veg_max_height{};
	double med_veg_max_height{};
	double high_veg_max_height{};
	double tree_max_height{};
	double veg_filter_min_height{};
	double veg_filter_max_height{};
	double veg_reclassify_radius{};
	double veg_neighbors_exploration_radius{};
	double prometheus_radius{};
	double prometheus_quartiles_radius{};
	double groundTruth_neighs_radius{};

	// Segmentation Parameters
	double norRadApdFactor{};
	double segRadApdFactor{};
	double intPctDiff{};
	double norAngDiff{};
	double intCentroidWeight{};
	double norCentroidWeight{};
	double minPlanarRegionArea{};

	// Flag ot activate detections
	// TODO: BOOOOOOOOL
	unsigned char catTest{};
	unsigned char pathSearching{};
	unsigned char towerDetection{};
	unsigned char powerDetection{};
	unsigned char pathToClosestRoad{};
	unsigned char photoTowerDetection{};
	unsigned char vegClassification{};
	unsigned char prometheus{};
	unsigned char segmentation{};
	bool          classification{};
	unsigned char roadDetection{};
	bool          dtmPathSearching{};
	bool          dtmRoadDetection{};
	bool          dtm{};
	bool          useDtm{}; // Used in some methods of the classifier
	bool          nir{};
	bool          slopeTesting{};
	bool          delaunay{};
	bool 					isClassified{};

	// Classification parameters
	float  jump_apd_factor;
	float  as_apd_factor;
	float  max_jump_rad;
	float  min_jump_rad;
	float  jump_threshold;
	float  min_jumps_prct;
	float  min_z_comp;
	float  max_dirty_prct;
	float  min_small_build_area;
	double min_water_prct;

	// Road parameters
	double minRoadWidth;
	double maxBalancingStep;
	double maxCurvature;
	double hwAreaRatio;
	double minMatchPct;
	int    maxPercentile;

	// Benchmarks
	size_t                  numThreads;
    u_int                   bucketSize;
    u_int                   numTests;
    std::vector<double>     searchRadiusSet;
    int                     searchNumPoints;
    std::string             testOutputDirectory;
};

extern main_options mainOptions;

// Define short options
const char * const short_opts = "h:i:o:I:C:p:e:n:";

// Define long options
const option long_opts[] = {
	{ "help", no_argument, nullptr, 'h' },
	{ "num-points", required_argument, nullptr, 1 },
	{ "coordinates-file", required_argument, nullptr, 'C' },
	{ "exclusion-dir", required_argument, nullptr, 'e' },
	{ "dtm-file", required_argument, nullptr, 2 },
	{ "debug", no_argument, nullptr, 3 },

	// Path Searching Parameters
	{ "max-edge-slopeDZDL", required_argument, nullptr, 200 },
	{ "focus-width", required_argument, nullptr, 201 },
	{ "oversegment-radius", required_argument, nullptr, 202 },
	{ "oversegment-maxpoints", required_argument, nullptr, 203 },
	{ "max-edge-slopeDZDL-degrees", required_argument, nullptr, 204 },
	{ "road-point-ratio", required_argument, nullptr, 205 },
	{ "traff-point-ratio", required_argument, nullptr, 206 },

	// Weight factors
	{ "slopeDZDL-factor-05", required_argument, nullptr, 207 },
	{ "slopeDZDL-factor-510", required_argument, nullptr, 208 },
	{ "slopeDZDL-factor-1015", required_argument, nullptr, 209 },
	{ "slopeDZDL-factor-1520", required_argument, nullptr, 210 },
	{ "slopeDZDL-factor-20", required_argument, nullptr, 211 },
	{ "road-factor", required_argument, nullptr, 212 },
	{ "roughness-factor", required_argument, nullptr, 213 },
	{ "roughness-limit", required_argument, nullptr, 214 },
	{ "jump_apd_factor", required_argument, 0, 215 },
	{ "as_apd_factor", required_argument, 0, 216 },

	// Tower Detection parameters
	{ "dbscan-distance", required_argument, nullptr, 300 },
	{ "dbscan-minPoints", required_argument, nullptr, 301 },
	{ "min-height-difference", required_argument, nullptr, 302 },
	{ "max-tower-angle", required_argument, nullptr, 303 },
	{ "inner-x", required_argument, nullptr, 304 },
	{ "inner-y", required_argument, nullptr, 305 },
	{ "inner-z", required_argument, nullptr, 306 },
	{ "outer-x", required_argument, nullptr, 307 },
	{ "outer-y", required_argument, nullptr, 308 },
	{ "outer-z", required_argument, nullptr, 309 },

	// Segmentation parameters
	{ "normal-radius-apd-factor", required_argument, nullptr, 400 },
	{ "segment-radius-apd-factor", required_argument, nullptr, 401 },
	{ "intensity-percent-diff", required_argument, nullptr, 402 },
	{ "normal-angle-diff", required_argument, nullptr, 403 },
	{ "intensity-centroid-weight", required_argument, nullptr, 404 },
	{ "normal-centroid-weight", required_argument, nullptr, 405 },
	{ "min-area-planar-region", required_argument, nullptr, 406 },

	// Classification parameters
	{ "max-jump-rad", required_argument, nullptr, 420 },
	{ "min-jump-rad", required_argument, nullptr, 421 },
	{ "jump-threshold", required_argument, nullptr, 422 },
	{ "min-jumps-prct", required_argument, nullptr, 423 },
	{ "min-z-comp", required_argument, nullptr, 424 },
	{ "max-dirty-prct", required_argument, nullptr, 425 },
	{ "min-small-build-area", required_argument, nullptr, 426 },
	{ "min-water-prct", required_argument, nullptr, 427 },

	// Road parameters
	{ "min-road-width", required_argument, nullptr, 440 },
	{ "max-balancing-step", required_argument, nullptr, 441 },
	{ "max-curvature", required_argument, nullptr, 442 },
	{ "max-percentile", required_argument, nullptr, 443 },
	{ "hw-area-ratio", required_argument, nullptr, 444 },

	// Vegetation parameters
	{ "low_veg_min_height", required_argument, nullptr, 500 },
	{ "med_veg_min_height", required_argument, nullptr, 501 },
	{ "high_veg_min_height", required_argument, nullptr, 502 },
	{ "tree_min_height", required_argument, nullptr, 503 },
	{ "veg_filter_min_height", required_argument, nullptr, 504 },
	{ "veg_filter_max_height", required_argument, nullptr, 505 },
	{ "low_veg_max_height", required_argument, nullptr, 506 },
	{ "med_veg_max_height", required_argument, nullptr, 507 },
	{ "high_veg_max_height", required_argument, nullptr, 508 },
	{ "tree_max_height", required_argument, nullptr, 509 },
	{ "veg_reclassify_radius", required_argument, nullptr, 510 },
	{ "veg_neighbors_exploration_radius", required_argument, nullptr, 511 },
	{ "prometheus_radius", required_argument, nullptr, 512 },
	{ "prometheus_quartiles_radius", required_argument, nullptr, 513 },
	{ "veg-ground-truth-shp", required_argument, nullptr, 514 },
	{ "veg-ground-truth-dbf", required_argument, nullptr, 515 },
	{ "groundTruth_neighs_radius", required_argument, nullptr, 516 },
	{ "veg-ground-truth-xyz", required_argument, nullptr, 517 },

	// Flags
	{ "cat-test", no_argument, nullptr, 665 },
	{ "path-searching", no_argument, nullptr, 666 },
	{ "tower-detection", no_argument, nullptr, 667 },
	{ "closest-road", no_argument, nullptr, 668 },
	{ "photo-tower-detection", no_argument, nullptr, 669 },
	{ "veg-classification", no_argument, nullptr, 670 },
	{ "prometheus", no_argument, nullptr, 671 },
	{ "segmentation", no_argument, nullptr, 672 },
	{ "power-detection", no_argument, nullptr, 673 },
	{ "classification", no_argument, nullptr, 674 },
	{ "dtm", no_argument, nullptr, 675 },
	{ "road-detection", no_argument, nullptr, 676 },
	{ "dtm-road-detection", no_argument, nullptr, 677 },
	{ "use-dtm", no_argument, nullptr, 678 },
	{ "is-classified", no_argument, nullptr, 679},
	{ "dtm-path-searching", no_argument, nullptr, 680},
	{ "slope-testing", no_argument, nullptr, 681},
	{ "delaunay", no_argument, nullptr, 682 },
	{ "nir", no_argument, nullptr, 683 },

	// Benchmarks
  { "num-threads", required_argument, nullptr, 700},

  { "bucket-size", required_argument, nullptr, 701},
    { "num-tests", required_argument, nullptr, 702},
    { "search-radius-set", required_argument, nullptr, 704},
    { "search-num-points", required_argument, nullptr, 705},
    { "test-output-directory", required_argument, nullptr, 706}
	//      {"opcion2", required_argument, nullptr, 2},
};

void printHelp();
void processArgs(int argc, char ** argv);
void setDefaults();

#endif //CPP_MAIN_OPTIONS_H
