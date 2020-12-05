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

	void read(const char* buf, const char* format, ...) {
		va_list args;
		va_start(args, format);
		vsscanf(buf, format, args);
		va_end(args);
	}

public:
	ObjFile(std::string filepath) {
		static const char* format{ "%c %f %f %f" };
		std::ifstream in_obj(filepath);
		if (!in_obj.is_open()) {
			std::cout << "WARNING: Unable to open OBJ file '" << filepath << ". Model will not be loaded." << std::endl;
			return;
		}

		int vcount{ 0 };
		for (std::string line; std::getline(in_obj, line);) {
			char ch;
			float fx, fy, fz;
			read(line.c_str(), format, &ch, &fx, &fy, &fz);

			if (ch == 'v') {
				vcount++;
				std::array<float, 3> v{fx, fy, fz};
				obj_vertices.push_back(v);
			}
		}
		std::cout << "Initialized ObjFile with " << vcount << " vertices" << std::endl;
	}

	const std::vector<std::array<float, 3>>& getVertices() const {
		return obj_vertices;
	}

};