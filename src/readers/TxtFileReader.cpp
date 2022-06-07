//
// Created by miguelyermo on 6/8/21.
//

#include "TxtFileReader.h"
#include "main_options.h"
#include <fstream>
#include <iterator>

std::vector<std::string> splitLine(std::string & line)
{
	std::istringstream                 buf(line);
	std::istream_iterator<std::string> beg(buf), end;
	std::vector<std::string>           tokens(beg, end);

	return tokens;
}

void TxtFileReader::setNumberOfColumns(std::ifstream & file)
{
	std::string line, item;

	std::getline(file, line);
	file.seekg(0); // Return to first line to be read later.
	std::stringstream ss(line);

	numCols = 0;
	while (ss >> item)
		numCols++;
}

std::vector<Lpoint> TxtFileReader::read()
{
	std::ifstream file(path.string());
	std::string   line{};

	setNumberOfColumns(file);

	mainOptions.numCols = numCols; // To be used later in the program

	unsigned int        idx = 0;
	std::vector<Lpoint> points;

	// TODO: Pensar como modularizarlo...
	switch (numCols)
	{
		case 3:
			while (std::getline(file, line, '\n'))
			{
				auto tokens = splitLine(line);
				points.emplace_back(idx++,                 // id
				                    std::stod(tokens[0]),  // x
				                    std::stod(tokens[1]),  // y
				                    std::stod(tokens[2])); // z
			}
			break;
		case 6:
			while (std::getline(file, line, '\n'))
			{
				auto tokens = splitLine(line);
				points.emplace_back(idx++,                 // id
				                    std::stod(tokens[0]),  // x
				                    std::stod(tokens[1]),  // y
				                    std::stod(tokens[2]),  // z
				                    std::stod(tokens[3]),  // I
				                    std::stoi(tokens[4]),  // regionID
				                    std::stoi(tokens[5])); // classification
			}
			break;

		case 7:
			while (std::getline(file, line, '\n'))
			{
				auto tokens = splitLine(line);
				points.emplace_back(idx++,                 // id
				                    std::stod(tokens[0]),  // x
				                    std::stod(tokens[1]),  // y
				                    std::stod(tokens[2]),  // z
				                    std::stod(tokens[3]),  // I
				                    std::stod(tokens[4]),  // rn
				                    std::stod(tokens[5]),  // nor
				                    std::stoi(tokens[6])); // classification
			}
			break;

		// Raw point cloud without RGB
		case 9:
			while (std::getline(file, line, '\n'))
			{
				auto tokens = splitLine(line);
				points.emplace_back(idx++,                 // id
				                    std::stod(tokens[0]),  // x
				                    std::stod(tokens[1]),  // y
				                    std::stod(tokens[2]),  // z
				                    std::stod(tokens[3]),  // I
				                    std::stoi(tokens[4]),  // rn
				                    std::stoi(tokens[5]),  // nor
				                    std::stoi(tokens[6]),  // dir
				                    std::stoi(tokens[7]),  // edge
				                    std::stoi(tokens[8])); // classification
			}
			break;
		// Over-segmented point cloud with group Ids
		case 10:
			while (std::getline(file, line, '\n'))
			{
				auto tokens = splitLine(line);
				points.emplace_back(idx++,                 // id
				                    std::stod(tokens[0]),  // x
				                    std::stod(tokens[1]),  // y
				                    std::stod(tokens[2]),  // z
				                    std::stod(tokens[3]),  // I
				                    std::stoi(tokens[4]),  // rn
				                    std::stoi(tokens[5]),  // nor
				                    std::stoi(tokens[6]),  // dir
				                    std::stoi(tokens[7]),  // edge
				                    std::stoi(tokens[8]),  // classification
				                    std::stoi(tokens[9])); // regionID
			}
			break;

		case 11:
			while (std::getline(file, line, '\n'))
			{
				auto tokens = splitLine(line);
				points.emplace_back(idx++,                  // id
				                    std::stod(tokens[0]),   // x
				                    std::stod(tokens[1]),   // y
				                    std::stod(tokens[2]),   // z
				                    std::stod(tokens[3]),   // realZ
				                    std::stod(tokens[4]),   // I
				                    std::stoi(tokens[5]),   // rn
				                    std::stoi(tokens[6]),   // nor
				                    std::stoi(tokens[7]),   // dir
				                    std::stoi(tokens[8]),   // edge
				                    std::stoi(tokens[9]),   // classification
				                    std::stoi(tokens[10])); // regionID
			}
			break;

		case 12:
			while (std::getline(file, line, '\n'))
			{
				auto tokens = splitLine(line);
				points.emplace_back(idx++,                  // id
				                    std::stod(tokens[0]),   // x
				                    std::stod(tokens[1]),   // y
				                    std::stod(tokens[2]),   // z
				                    std::stod(tokens[3]),   // I
				                    std::stoi(tokens[4]),   // rn
				                    std::stoi(tokens[5]),   // nor
				                    std::stoi(tokens[6]),   // dir
				                    std::stoi(tokens[7]),   // edge
				                    std::stoi(tokens[8]),   // classification
				                    std::stoi(tokens[9]),   // r
				                    std::stoi(tokens[10]),  // g
				                    std::stoi(tokens[11])); // b
			}
			break;

		case 13:
			// Reading a non-RGB (9 fields) segmented map.
			while (std::getline(file, line, '\n'))
			{
				auto tokens = splitLine(line);
				points.emplace_back(idx++,                  // id
				                    std::stod(tokens[0]),   // x
				                    std::stod(tokens[1]),   // y
				                    std::stod(tokens[2]),   // z
				                    std::stod(tokens[3]),   // I
				                    std::stoi(tokens[4]),   // rn
				                    std::stoi(tokens[5]),   // nor
				                    std::stoi(tokens[6]),   // dir
				                    std::stoi(tokens[7]),   // edge
				                    std::stoi(tokens[8]),   // classification
				                    std::stoi(tokens[9]),   // regionId
				                    std::stod(tokens[10]),  // nx
				                    std::stod(tokens[11]),  // ny
				                    std::stod(tokens[12])); // nz
			}
			break;

		case 16:
			// Reading a RGB (16 fields) segmented map.
			// NOTA: En función si la entrada del segmentador en C tiene rgb o no (9 vs 12 campos), la salida obtenida
			// es distinta: 16 campos para ambas, una con normal y autovalores y otra con rgb y normales).
			while (std::getline(file, line, '\n'))
			{
				auto tokens = splitLine(line);
				points.emplace_back(idx++,                 // id
				                    std::stod(tokens[0]),  // x
				                    std::stod(tokens[1]),  // y
				                    std::stod(tokens[2]),  // z
				                    std::stod(tokens[3]),  // I
				                    std::stoi(tokens[4]),  // rn
				                    std::stoi(tokens[5]),  // nor
				                    std::stoi(tokens[6]),  // dir
				                    std::stoi(tokens[7]),  // edge
				                    std::stoi(tokens[8]),  // classification
				                    std::stoi(tokens[9]),  // regionId
				                    std::stoi(tokens[10]), // r
				                    std::stoi(tokens[11]), // g
				                    std::stoi(tokens[12]), // b
				                    std::stod(tokens[13]), // nx
				                    std::stod(tokens[14]), // ny
				                    std::stod(tokens[15])  // nz
				);
			}

			break;

		default:
			std::cout << "Unrecognized format\n";
			exit(1);
	}
	file.close();
	std::cout << "Read points: " << idx << "\n";
	return points;
};