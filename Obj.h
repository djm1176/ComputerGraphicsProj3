#pragma once

#include <GL/freeglut.h>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <array>
#include <iostream>

class ObjFile {
private:
	std::vector<std::array<float, 3>> obj_vertices;
	std::vector<std::array<int, 3>> obj_faces;
	


	void read(const char* buf, const char* format, ...) {
		va_list args;
		va_start(args, format);
		vsscanf(buf, format, args);
		va_end(args);
	}

public:
	std::vector<std::array<int, 3>> obj_colors;
	ObjFile(std::string filepath) {
		static const char* format{ "%c %f %f %f" };
		std::ifstream in_obj(filepath);
		if (!in_obj.is_open()) {
			std::cout << "WARNING: Unable to open OBJ file '" << filepath << ". Model will not be loaded." << std::endl;
			return;
		}


		//Load vertices
		int vcount{ 0 }, fcount{ 0 };
		for (std::string line; std::getline(in_obj, line);) {
			char ch;
			float fx, fy, fz;
			read(line.c_str(), format, &ch, &fx, &fy, &fz);

			if (ch == 'v') {
				vcount++;
				std::array<float, 3> v{ fx, fy, fz };
				obj_vertices.push_back(v);
				
			}
			else if (ch == 'f') {
				//This is face indices
				fcount++;
				std::array<int, 3> f{ fx, fy, fz };
				obj_faces.push_back(f);
				obj_colors.push_back({ rand() % 50 ,rand() %50, rand() %200+55});
			}
		}

		std::cout << "Initialized ObjFile with " << vcount << " vertices and " << fcount << " faces" << std::endl;
	}

	const std::vector<std::array<float, 3>>& getVertices() const {
		return obj_vertices;
	}

	const std::vector <std::array<int, 3>>& getFaces() const {
		return obj_faces;
	}

	const std::array<std::array<float, 3>, 3> getTriangle(int index) const {
		auto indices = obj_faces.at(index);
		std::array<std::array<float, 3>, 3> triangle{ obj_vertices.at(indices.at(0) - 1),
														obj_vertices.at(indices.at(1) - 1),
														obj_vertices.at(indices.at(2) - 1) };
		return triangle;
	}

	int getFaceCount() const {
		return obj_faces.size();
	}

};
