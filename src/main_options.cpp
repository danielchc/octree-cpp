#include "main_options.h"
#include <filesystem>
#include <cstring>

namespace fs = std::filesystem;

main_options mainOptions{};

void printHelp()
{
    std::cout
            << "-h: Show this message\n"
               "-i: Path to input file\n"
               "-o: Path to output file\n"
               "-C <--coordinates-file> : Coordinates file of path searching. JSON Format\n"
               "-p <--perimeter-file> : Shapefile containing the perimeter of a given fire\n"
               "-e <--exclusion-area> : Shapefile containing a forbidden area to search a path\n"
               "-n <--num-points>     : Number of points to be read\n"
               "--dtm-file: Path to the dtm file, if existing\n"
               "--path-searching:  Flag to activate path detection\n"
               "--tower-detection: Flag to activate tower detection\n"
               "--power-detection: Flag to activate powerline detection\n"
               "--photo-tower-detection: Flag to activate photogrammetry tower detection\n"
               "--veg-classification: Flag to activate classification of vegetation\n"
               "--prometheus: Flag to activate prometheus computations\n"
               "--segmentation: Flag to activate segmentation\n"
               "--classification: Flag to activate classification\n"
               "--dtm: Flag to activate the DTM\n"
               "--road-detection: Flag to activate the road detection\n"
               "--use-dtm: Flag to activate the use of dtm in some classifier functions\n"
               "--dtm-road-detection: Flag to active road detection using DTM classification\n"
               "--nir: Flag to indicate that the input cloud has NIR information\n"
               "--focus-width: Width of the area around each edge to include LiDAR points\n"
               "--oversegment-radius: Search radius when performing the over segmentation\n"
               "--oversegment-maxpoints: Number of max points per groups in the over segmentation\n"
               "--max-edge-slopeDZDL-degrees: Maximum slopeDZDL (computed using the plane) in degrees than an edge can have\n"
               "--road-point-ratio: Minimum ratio of road points that an edge must have to be considered as road\n"
               "--traff-point-ratio: Minimum ratio of trafficable points that an edge must have to be considered as trafficable\n"
               "--slopeDZDL-factor-05: Weight factor for slopes between 0 and 5 %\n"
               "--slopeDZDL-factor-510: Weight factor for slopes between 5 and 10 %\n"
               "--slopeDZDL-factor-1015: Weight factor for slopes between 10 and 15 %\n"
               "--slopeDZDL-factor-1520: Weight factor for slopes between 15 and 20 %\n"
               "--slopeDZDL-factor-20: Weight factor for slopes greater than 20 %\n"
               "--road-factor: Weight factor for roads\n"
               "--roughness-factor: Weight factor for rough terrains\n"
               "--roughness-limit: Roughness value from which the roughness factor will be applied \n"
               "--dbscanDistance: Distance of searching in dbscan clustering\n"
               "--dbscanMinPoints: Number of min points of a cluster to not being considered as noise\n"
               "--minHeightDifference: Min height difference between highest and lowest point in a cluster to be considered as a tower candidate\n"
               "--max-tower-angle: Maximum angle with the vertical of a pole to be classified as such\n"
               "--inner-x: X dimension (m) of the inner neighborhood in the tower search\n"
               "--inner-y: Y dimension (m) of the inner neighborhood in the tower search\n"
               "--inner-z: Z dimension (m) of the inner neighborhood in the tower search\n"
               "--outer-x: X dimension (m) of the outer neighborhood in the tower search\n"
               "--outer-y: Y dimension (m) of the outer neighborhood in the tower search\n"
               "--outer-z: Z dimension (m) of the outer neighborhood in the tower search\n"
               "--jump_apd_factor: Jumps neighboorhod radius = this factor * average point distance\n"
               "--as_apd_factor: Alpha Shapes APD factor\n"
               "--max-jump-rad: Upper limit for the neighborhood radius for height jump search\n"
               "--min-jump-rad: Lower limit for the neighborhood radius for height jump search\n"
               "--jump-threshold: Difference distance which is considered as a jump\n"
               "--min-jumps-prct: Min percent of jumping boundaries to be no ground\n"
               "--min-z-comp: Min z component of the avg normal vector to be building.\n"
               "--min-water-prct: Min percent of region points with NDWI > 0 to reclassify the region as WATER region.\n"
               "--max-dirty-prct: Max percent of points with multiple returns (veg).\n"
               "--min-road-width: Min road width for neighbour radius estimation\n"
               "--max-balancing-step: Max step for the intensity skewness balancing \n"
               "--max-curvature: Max curvature for a road point\n"
               "--max-percentile: Max percentile for intensity distribution right tail removal\n"
               "--hw-area-ratio: Area ratio (height / width) for a min road chunk\n"
               "--normal-radius-apd-factor: Radius for normal vector = this factor * APD\n"
               "--segment-radius-apd-factor: Radius for segmentation = this factor * APD\n"
               "--intensity-percent-diff: Max percentage difference of normalised intensity\n"
               "--normal-angle-diff: Max angle difference for each axis (degrees)\n"
               "--intensity-centroid-weight: Intensity centroid weight for the epicenter calculation\n"
               "--normal-centroid-weight: Normal centroid weight for the epicenter calculation\n"
               "--min-area-planar-region: Min area for a planar region\n"
               "--max-jump-rad;: upper limit for the neighborhood radius for height jump search\n"
               "--min-jump-rad: lower limit for the neighborhood radius for height jump search\n"
               "--min-small-build-area: min area to be considered small building.\n"
               "--veg_filter_max_height: veg filter max height\n"
               "--low_veg_min_height: low veg min height\n"
               "--med_veg_min_height: med veg min height\n"
               "--high_veg_min_height: high veg min height\n"
               "--tree_min_height: trees min height\n"
               "--low_veg_max_height: low veg max height\n"
               "--med_veg_max_height: med veg max height\n"
               "--high_veg_max_height: high veg max height\n"
               "--tree_max_height: trees max height\n"
               "--veg_filter_min_height: veg filter min height\n"
               "--veg_filter_max_height: veg filter max height\n"
               "--veg_reclassify_radius: veg reclassify radius\n"
               "--veg_neighbors_exploration_radius: veg neighbors exploration radius\n"
               "--prometheus_radius: prometheus radius\n"
               "--prometheus_quartiles_radius: prometheus quartiles radius\n"
               "--veg-ground-truth-shp: vegetation ground truth (shp file)\n"
               "--veg-ground-truth-dbf: vegetation ground truth (dbf file)\n"
               "--veg-ground-truth-xyz: vegetation ground truth (xyz file)\n"
               "--groundTruth_neighs_radius: ground truth neighs radius\n";
    exit(1);
}

void setDefaults()
{
    if (!mainOptions.userOutputDirName) mainOptions.outputDirName = "out";
    mainOptions.debug                 = false;
    mainOptions.maxEdgeSlope          = 0.30; // % of maximum slope. Edges with slopes greater than this will be dropped.
    mainOptions.focusWidth            = 2.0;
    mainOptions.overSegmentRadius     = 2.5;
    mainOptions.overSegmentMaxPoints  = 2500;
    mainOptions.maxEdgeSlopeDegrees   = 20;
    mainOptions.roadPointRatio        = 0.5;
    mainOptions.traffPointRatio       = 0.9;
    mainOptions.slopeFactor05         = 1.0;
    mainOptions.slopeFactor510        = 1.5;
    mainOptions.slopeFactor1015       = 2.5;
    mainOptions.slopeFactor1520       = 3.5;
    mainOptions.slopeFactor20         = 10.0;
    mainOptions.roadWeightFactor      = 0.01;
    mainOptions.roughnessWeightFactor = 1.0;
    mainOptions.roughnessLimit        = 0.2;
    mainOptions.dbscanDistance        = 2.0;
    mainOptions.dbscanMinPoints       = 1;
    mainOptions.minHeightDifference   = 2.0;
    mainOptions.maxTowerAngle         = 15.0;
    mainOptions.innerX                = 4.0;
    mainOptions.innerY                = 4.0;
    mainOptions.innerZ                = 1.0;
    mainOptions.outerX                = 6.0;
    mainOptions.outerY                = 6.0;
    mainOptions.outerZ                = 1.0;
    mainOptions.norRadApdFactor       = 2.0;
    mainOptions.segRadApdFactor       = 3.0;
    mainOptions.intPctDiff            = 7.5;
    mainOptions.norAngDiff            = 7.5;
    mainOptions.intCentroidWeight     = 0.66;
    mainOptions.norCentroidWeight     = 0.66;
    mainOptions.minPlanarRegionArea   = 2.0;

    // Classification parameters
    mainOptions.jump_apd_factor      = 3.5;
    mainOptions.as_apd_factor        = 1.5;
    mainOptions.min_jump_rad         = 1.0;
    mainOptions.max_jump_rad         = 3.0;
    mainOptions.jump_threshold       = 1.5;
    mainOptions.min_jumps_prct       = 0.1;
    mainOptions.min_z_comp           = 0.5;
    mainOptions.max_dirty_prct       = 0.10;
    mainOptions.min_small_build_area = 2;
    mainOptions.min_water_prct = 0.80;

    // Road classification parameters
    mainOptions.minRoadWidth     = 2.0;
    mainOptions.maxBalancingStep = 10.0;
    mainOptions.maxCurvature     = 0.005;
    mainOptions.maxPercentile    = 95;
    mainOptions.hwAreaRatio      = 4;
    mainOptions.minMatchPct      = 2 / 3.;

    // Vegetation parameters
    mainOptions.low_veg_min_height  = 0;
    mainOptions.med_veg_min_height  = 0.6;
    mainOptions.high_veg_min_height = 2;
    mainOptions.tree_min_height     = 4;
    mainOptions.low_veg_max_height  = 0.6;
    mainOptions.med_veg_max_height  = 2;
    mainOptions.high_veg_max_height = 4; // Recomendation: use 6 metres for trees in Galician maps or similar environments
    mainOptions.tree_max_height                  = 1000; // no limit
    mainOptions.veg_filter_min_height            = 0;
    mainOptions.veg_filter_max_height            = 1000;
    mainOptions.veg_reclassify_radius            = 0.5;
    mainOptions.veg_neighbors_exploration_radius = 2.0;
    mainOptions.prometheus_radius                = 2.0;
    mainOptions.prometheus_quartiles_radius      = 2.0;
    mainOptions.groundTruth_neighs_radius        = 15.0;

    // Powerline detection parameters
    mainOptions.neighborhoodRadius       = 1.0;
    mainOptions.wireThickness            = 0.15;
    mainOptions.heightThreshold          = 3.5;
    mainOptions.ratioThreshold           = 0.90;
    mainOptions.candidatesRadioThreshold = 0.01;
    mainOptions.angleStep                = 0.1;
    mainOptions.gridSpacing              = 0.1;
    mainOptions.numMinCatPoints          = 25;
    mainOptions.maxCatDistance           = 1.0;
    mainOptions.maxCatAngle              = 0.5;
    mainOptions.powerlineMaxWidth        = 5.0;
    mainOptions.powerlineMaxAngle        = 2.0;

    // Benchmarks
    mainOptions.numThreads = 1;

    mainOptions.bucketSize=32;
    mainOptions.numTests=5;
    mainOptions.searchRadiusSet={1.0f,2.0f};
    mainOptions.searchNumPoints=-1;
    mainOptions.testOutputDirectory=".";
}


void processArgs(int argc, char ** argv)
{
    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
        {
            break;
        }

        switch (opt)
        {
            // Short Options
            case 'h': {
                printHelp();
                break;
            }
            case 'i': {
                mainOptions.inputFile = fs::path(std::string(optarg));
                std::cout << "Read file set to: " << mainOptions.inputFile << "\n";
                break;
            }
            case 'o': {
                mainOptions.outputDirName     = fs::path(std::string(optarg));
                mainOptions.userOutputDirName = 1;
                std::cout << "Output path set to: " << mainOptions.outputDirName << "\n";
                break;
            }
            case 'C': {
                mainOptions.coordinatesFile     = fs::path(std::string(optarg));
                mainOptions.userCoordinatesFile = true;
                std::cout << "Coordinates File set to: " << mainOptions.coordinatesFile << "\n";
                break;
            }
            case 'e': {
                mainOptions.exclusionDir     = fs::path(std::string(optarg));
                mainOptions.userExclusionDir = true;
                std::cout << "Exclusion Areas directory set to: " << mainOptions.exclusionDir << "\n";
                break;
            }
            case 'n': {
                mainOptions.numPoints     = std::stoi(optarg);
                mainOptions.userNumPoints = true;
                std::cout << "Number of points: " << mainOptions.numPoints << "\n";
                break;
            }

                // Long Options
            case 0: // Help
            {
                printHelp();
            }
            case 1: // Number of points
            {
                mainOptions.numPoints     = std::stoi(optarg);
                mainOptions.userNumPoints = true;
                std::cout << "Number of points: " << mainOptions.numPoints << "\n";
                break;
            }

            case 2: // DTM File
            {
                mainOptions.dtmFile     = std::string(optarg);
                mainOptions.userDtmFile = true;
                std::cout << "DTM File set to: " << mainOptions.dtmFile << "\n";
                break;
            }

            case 3: // Debug flag
            {
                mainOptions.debug = true;
                break;
            }

                // Path Searching Parameters
            case 200: { // Maximum edge slopeDZDL
                mainOptions.maxEdgeSlope = std::stof(optarg);
                std::cout << "Max Edge Slope: " << mainOptions.maxEdgeSlope << "\n";
                break;
            }

            case 201: { // Focus width
                mainOptions.focusWidth = std::stof(optarg);
                std::cout << "Focus Width: " << mainOptions.focusWidth << "\n";
                break;
            }

            case 202: {
                mainOptions.overSegmentRadius = std::stof(optarg);
                std::cout << "Over Segment Radius: " << mainOptions.overSegmentRadius << "\n";
                break;
            }

            case 203: {
                mainOptions.overSegmentMaxPoints = std::stoi(optarg);
                std::cout << "Over Segment max points: " << mainOptions.overSegmentMaxPoints << "\n";
                break;
            }

            case 204: {
                mainOptions.maxEdgeSlopeDegrees = std::stof(optarg);
                std::cout << "Max Edge Slope Degrees: " << mainOptions.maxEdgeSlopeDegrees << "\n";
                break;
            }

            case 205: {
                mainOptions.roadPointRatio = std::stof(optarg);
                std::cout << "Road Point Ratio: " << mainOptions.roadPointRatio << "\n";
                break;
            }

            case 206: {
                mainOptions.traffPointRatio = std::stof(optarg);
                std::cout << "Trafficable Point Ratio: " << mainOptions.traffPointRatio << "\n";
                break;
            }

            case 207: {
                mainOptions.slopeFactor05 = std::stof(optarg);
                std::cout << "Slope Weight from 0 to 5 degrees: " << mainOptions.slopeFactor05 << "\n";
                break;
            }

            case 208: {
                mainOptions.slopeFactor510 = std::stof(optarg);
                std::cout << "Slope Weight from 5 to 10 degrees: " << mainOptions.slopeFactor510 << "\n";
                break;
            }

            case 209: {
                mainOptions.slopeFactor1015 = std::stof(optarg);
                std::cout << "Slope Weight from 10 to 15 degrees: " << mainOptions.slopeFactor1015 << "\n";
                break;
            }

            case 210: {
                mainOptions.slopeFactor1520 = std::stof(optarg);
                std::cout << "Slope Weight from 15 to 20 degrees: " << mainOptions.slopeFactor1520 << "\n";
                break;
            }

            case 211: {
                mainOptions.slopeFactor20 = std::stof(optarg);
                std::cout << "Slope Weight of more than 20 degrees: " << mainOptions.slopeFactor20 << "\n";
                break;
            }

            case 212: {
                mainOptions.roadWeightFactor = std::stof(optarg);
                std::cout << "Road weight factor: " << mainOptions.roadWeightFactor << "\n";
                break;
            }

            case 213: {
                mainOptions.roughnessWeightFactor = std::stof(optarg);
                std::cout << "Roughness weight factor: " << mainOptions.roughnessWeightFactor << "\n";
                break;
            }

            case 214: {
                mainOptions.roughnessLimit = std::stof(optarg);
                std::cout << "Roughness Limit: " << mainOptions.roughnessLimit << "\n";
                break;
            }

            case 215: {
                mainOptions.jump_apd_factor = std::stof(optarg);
                std::cout << "Jump apd factor: " << mainOptions.jump_apd_factor << "\n";
                break;
            }

            case 216: {
                mainOptions.as_apd_factor = std::stof(optarg);
                std::cout << "Alpha Shapes APD factor: " << mainOptions.as_apd_factor << "\n";
                break;
            }

            case 300: {
                mainOptions.dbscanDistance = std::stof(optarg);
                std::cout << "DBSCAN search distance: " << mainOptions.dbscanDistance << "\n";
                break;
            }

            case 301: {
                mainOptions.dbscanMinPoints = std::stoi(optarg);
                std::cout << "DBSCAN minimum number of points: " << mainOptions.dbscanMinPoints << "\n";
                break;
            }

            case 302: {
                mainOptions.minHeightDifference = std::stof(optarg);
                std::cout << "Min height difference: " << mainOptions.minHeightDifference << "\n";
                break;
            }

            case 303: {
                mainOptions.maxTowerAngle = std::stof(optarg);
                std::cout << "Max tower angle: " << mainOptions.maxTowerAngle << "\n";
            }

            case 304: {
                mainOptions.innerX = std::stof(optarg);
                std::cout << "Inner X Radius: " << mainOptions.innerX << "\n";
                break;
            }

            case 305: {
                mainOptions.innerY = std::stof(optarg);
                std::cout << "Inner Y Radius: " << mainOptions.innerY << "\n";
                break;
            }

            case 306: {
                mainOptions.innerZ = std::stof(optarg);
                std::cout << "Inner Z Radius: " << mainOptions.innerZ << "\n";
                break;
            }

            case 307: {
                mainOptions.outerX = std::stof(optarg);
                std::cout << "Outer X Radius: " << mainOptions.outerX << "\n";
                break;
            }

            case 308: {
                mainOptions.outerY = std::stof(optarg);
                std::cout << "Outer Y Radius: " << mainOptions.outerY << "\n";
                break;
            }

            case 309: {
                mainOptions.outerZ = std::stof(optarg);
                std::cout << "Outer Z Radius: " << mainOptions.outerZ << "\n";
                break;
            }

            case 400: {
                mainOptions.norRadApdFactor = std::stof(optarg);
                std::cout << "Normal radius APD factor: " << mainOptions.norRadApdFactor << "\n";
                break;
            }

            case 401: {
                mainOptions.segRadApdFactor = std::stof(optarg);
                std::cout << "Segmentation radius APD factor: " << mainOptions.segRadApdFactor << "\n";
                break;
            }

            case 402: {
                mainOptions.intPctDiff = std::stof(optarg);
                std::cout << "Intensity percent difference: " << mainOptions.intPctDiff << "\n";
                break;
            }

            case 403: {
                mainOptions.norAngDiff = std::stof(optarg);
                std::cout << "Normal angle difference: " << mainOptions.norAngDiff << "\n";
                break;
            }

            case 404: {
                mainOptions.intCentroidWeight = std::stof(optarg);
                std::cout << "Intensity centroid weight: " << mainOptions.intCentroidWeight << "\n";
                break;
            }

            case 405: {
                mainOptions.norCentroidWeight = std::stof(optarg);
                std::cout << "Normal centroid weight: " << mainOptions.norCentroidWeight << "\n";
                break;
            }

            case 406: {
                mainOptions.minPlanarRegionArea = std::stof(optarg);
                std::cout << "Min planar region area: " << mainOptions.minPlanarRegionArea << "\n";
                break;
            }

            case 420: {
                mainOptions.max_jump_rad = std::stof(optarg);
                std::cout << "Max jump radius: " << mainOptions.max_jump_rad << "\n";
                break;
            }

            case 421: {
                mainOptions.min_jump_rad = std::stof(optarg);
                std::cout << "Min jump radius: " << mainOptions.min_jump_rad << "\n";
                break;
            }

            case 422: {
                mainOptions.jump_threshold = std::stof(optarg);
                std::cout << "Jump threshold: " << mainOptions.jump_threshold << "\n";
                break;
            }

            case 423: {
                mainOptions.min_jumps_prct = std::stof(optarg);
                std::cout << "Min Jumps prct: " << mainOptions.min_jumps_prct << "\n";
                break;
            }

            case 424: {
                mainOptions.min_z_comp = std::stof(optarg);
                std::cout << "Min Z Comp: " << mainOptions.min_z_comp << "\n";
                break;
            }

            case 425: {
                mainOptions.max_dirty_prct = std::stof(optarg);
                std::cout << "Max. dirty prct: " << mainOptions.max_dirty_prct << "\n";
                break;
            }

            case 426: {
                mainOptions.min_small_build_area = std::stof(optarg);
                std::cout << "Min. small build area: " << mainOptions.min_small_build_area << "\n";
                break;
            }

            case 427: {
                mainOptions.min_water_prct = std::stof(optarg);
                std::cout << "Min. water prct: " << mainOptions.min_water_prct << "\n";
                break;
            }

            case 440: {
                mainOptions.minRoadWidth = std::stof(optarg);
                std::cout << "Min road width: " << mainOptions.minRoadWidth << "\n";
                break;
            }

            case 441: {
                mainOptions.maxBalancingStep = std::stof(optarg);
                std::cout << "Max balancing step: " << mainOptions.maxBalancingStep << "\n";
                break;
            }

            case 442: {
                mainOptions.maxCurvature = std::stof(optarg);
                std::cout << "Max curvature: " << mainOptions.maxCurvature << "\n";
                break;
            }

            case 443: {
                mainOptions.maxPercentile = std::stoi(optarg);
                std::cout << "Max percentile: " << mainOptions.maxPercentile << "\n";
                break;
            }

            case 500: {
                mainOptions.low_veg_min_height = std::stof(optarg);
                std::cout << "Low veg min height: " << mainOptions.low_veg_min_height << "\n";
                break;
            }

            case 501: {
                mainOptions.med_veg_min_height = std::stof(optarg);
                std::cout << "Med veg min height: " << mainOptions.med_veg_min_height << "\n";
                break;
            }

            case 502: {
                mainOptions.high_veg_min_height = std::stof(optarg);
                std::cout << "High veg min height: " << mainOptions.high_veg_min_height << "\n";
                break;
            }

            case 503: {
                mainOptions.tree_min_height = std::stof(optarg);
                std::cout << "Tree min height: " << mainOptions.tree_min_height << "\n";
                break;
            }
            case 504: {
                mainOptions.veg_filter_min_height = std::stof(optarg);
                std::cout << "Veg filter min height: " << mainOptions.veg_filter_min_height << "\n";
                break;
            }
            case 505: {
                mainOptions.veg_filter_max_height = std::stof(optarg);
                std::cout << "Veg filter max height: " << mainOptions.veg_filter_max_height << "\n";
                break;
            }

            case 506: {
                mainOptions.low_veg_max_height = std::stof(optarg);
                std::cout << "Low veg max height: " << mainOptions.low_veg_max_height << "\n";
                break;
            }

            case 507: {
                mainOptions.med_veg_max_height = std::stof(optarg);
                std::cout << "Med veg max height: " << mainOptions.med_veg_max_height << "\n";
                break;
            }

            case 508: {
                mainOptions.high_veg_max_height = std::stof(optarg);
                std::cout << "High veg max height: " << mainOptions.high_veg_max_height << "\n";
                break;
            }

            case 509: {
                mainOptions.tree_max_height = std::stof(optarg);
                std::cout << "Tree veg max height: " << mainOptions.tree_max_height << "\n";
                break;
            }

            case 510: {
                mainOptions.veg_reclassify_radius = std::stof(optarg);
                std::cout << "Veg reclassify radius: " << mainOptions.veg_reclassify_radius << "\n";
                break;
            }

            case 511: {
                mainOptions.veg_neighbors_exploration_radius = std::stof(optarg);
                std::cout << "Veg neighbors exploration radius: " << mainOptions.veg_neighbors_exploration_radius << "\n";
                break;
            }

            case 512: {
                mainOptions.prometheus_radius = std::stof(optarg);
                std::cout << "Prometheus radius: " << mainOptions.prometheus_radius << "\n";
                break;
            }

            case 513: {
                mainOptions.prometheus_quartiles_radius = std::stof(optarg);
                std::cout << "Prometheus quartiles radius: " << mainOptions.prometheus_quartiles_radius << "\n";
                break;
            }

            case 514: {
                mainOptions.vegGroundTruthShp = std::string(optarg);
                std::cout << "Vegetation ground truth (shp file): " << mainOptions.vegGroundTruthShp << "\n";
                break;
            }

            case 515: {
                mainOptions.vegGroundTruthDbf = std::string(optarg);
                std::cout << "Vegetation ground truth (dbf file): " << mainOptions.vegGroundTruthDbf << "\n";
                break;
            }

            case 516: {
                mainOptions.groundTruth_neighs_radius = std::stof(optarg);
                std::cout << "Ground truth neighs radius: " << mainOptions.groundTruth_neighs_radius << "\n";
                break;
            }

            case 517: {
                mainOptions.vegGroundTruthxyz = std::string(optarg);
                std::cout << "Vegetation ground truth (xyz file): " << mainOptions.vegGroundTruthxyz << "\n";
                break;
            }

            case 665: {
                mainOptions.catTest = true;
                break;
            }

            case 666: // Activate Path Searching
            {
                mainOptions.pathSearching = true;
                break;
            }
            case 667: // Activate Path Searching
            {
                mainOptions.towerDetection = true;
                break;
            }

            case 668: // Activate pathfinding to closest road
            {
                mainOptions.pathToClosestRoad = true;
                break;
            }

            case 669: // Activation of tower detection in photogrametry point clouds
            {
                mainOptions.photoTowerDetection = true;
                break;
            }

            case 670: // Activation of vegetation classification
            {
                mainOptions.vegClassification = true;
                break;
            }

            case 671: // Activation of Prometheus model
            {
                mainOptions.prometheus = true;
                break;
            }

            case 672: // Activation of Prometheus model
            {
                mainOptions.segmentation = true;
                break;
            }

            case 673: {
                mainOptions.powerDetection = true;
                break;
            }
            case 674: {
                mainOptions.classification = true;
                break;
            }

            case 675: {
                mainOptions.dtm = true;
                break;
            }

            case 676: {
                mainOptions.roadDetection = true;
                break;
            }

            case 677: {
                mainOptions.dtmRoadDetection = true;
                break;
            }

            case 678: {
                mainOptions.useDtm = true;
                break;
            }

            case 679: {
                mainOptions.isClassified = true;
                break;
            }

            case 680: {
                mainOptions.dtmPathSearching = true;
                break;
            }

            case 681: {
                mainOptions.slopeTesting = true;
                break;
            }

            case 682: {
                mainOptions.delaunay = true;
                break;
            }

            case 683: {
                mainOptions.nir = true;
                break;
            }

            case 700: {
                mainOptions.numThreads = std::stoi(optarg);
                std::cout << "Number of threads set to " << mainOptions.numThreads << "\n";
                break;
            }
            case 701: {
                mainOptions.bucketSize = std::stoi(optarg);
                break;
            }
            case 702: {
                mainOptions.numTests = std::stoi(optarg);
                break;
            }
            case 704: {
                mainOptions.searchRadiusSet=std::vector<double>();

                std::stringstream ss(optarg);

                while (ss.good()) {
                    std::string substr;
                    getline(ss, substr, ',');
                    mainOptions.searchRadiusSet.push_back(std::atof(substr.c_str()));
                }
                break;
            }
            case 705: {
                mainOptions.searchNumPoints = std::stoi(optarg);
                break;
            }
            case 706: {
                mainOptions.testOutputDirectory = optarg;
                break;
            }

            case '?': // Unrecognized option
            default:
                printHelp();
                break;
        }
    }
}