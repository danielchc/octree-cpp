#include "TimeWatcher.h"
#include "handlers.h"
#include "main_options.h"
#include "octree.h"
#include "point.h"
#include <bits/stdc++.h>
#include <iostream>


namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    TimeWatcher tm;
    double elapsed;

    setDefaults();
    processArgs(argc, argv);

    fs::path inputFile = mainOptions.inputFile;
    std::string fileName = inputFile.stem();

    // Print three decimals
    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    std::vector<Lpoint> points = readPointCloud(mainOptions.inputFile);


    std::cout << "Number of read points: " << points.size() << "\n";
    std::cout << "Building global octree..." << std::endl;


    u_int bucketSize = mainOptions.bucketSize;
    long numPoints = points.size();
	
	
	tm.start();
	Octree oct(points, bucketSize);
    tm.stop();
    elapsed=tm.getElapsedMillis();
    std::cout << "Octree creation: " << elapsed << "ms\n";

	
	tm.start();
	for (int i = 0; i < numPoints; i++) {
		auto newNeighs = oct.searchNeighbors(points[i], 1.0, Kernel_t::circle);
	}
	tm.stop();
    elapsed=tm.getElapsedMillis();
    std::cout << "Search time: " << elapsed << "ms\n";
	
    return EXIT_SUCCESS;
}
