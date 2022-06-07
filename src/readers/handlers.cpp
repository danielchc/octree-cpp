#include "handlers.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "FileReaderFactory.h"
#include "TxtFileReader.h"
#include "lasreader.hpp"

void handleNumberOfPoints(std::vector<Lpoint>& points)
/**
 * Normalization of the number of points.
 * If userNumPoints > numPoints -> numPoints
 * If userNumPoints < numPoints -> userNumPoints
 * If no userNumPoints -> numPoints
 */
{
	unsigned int numPoints = points.size();

	if (mainOptions.userNumPoints) {
		mainOptions.numPoints = std::min(numPoints, mainOptions.numPoints);
	} else {
		mainOptions.numPoints = numPoints;
	}

	points.resize(mainOptions.numPoints);
}

unsigned int getNumberOfCols(const fs::path& filePath)
/**
 * Get the number of columns of the input file.
 * @param filePath
 * @return
 */
{
	std::ifstream file(filePath);
	std::string line, item;
	unsigned int numCols = 0;

	// First Line
	std::getline(file, line);
	std::stringstream ss(line);

	while (ss >> item) numCols++;

	file.close();
	return numCols;
}

void createDirectory(const fs::path& dirName)
/**
 * This function creates a directory if it does not exist.
 * @param dirname
 * @return
 */
{
	if (!fs::is_directory(dirName)) {
		fs::create_directories(dirName);
	}
}

void writePoints(fs::path& filename, std::vector<Lpoint>& points) {
	std::ofstream f(filename);
	f << std::fixed << std::setprecision(2);

	for (Lpoint& p : points) {
		f << p << "\n";
	}

	f.close();
}

std::vector<Lpoint> readPointCloud(const fs::path& filename) {
	// Get Input File extension
	auto fExt = filename.extension();

	FileReader_t readerType = chooseReaderType(fExt);

	if (readerType == err_t) {
		std::cout << "Uncompatible file format\n";
		exit(-1);
	}

	std::shared_ptr<FileReader> fileReader =
		FileReaderFactory::makeReader(readerType, filename);

	return fileReader->read();
}