#pragma once

namespace Maths {

	//Linearly interpolates between a and b, by t, which represents a percentage from 0.0 to 1.0
	static double lerp(double a, double b, double t) {
		return a + (b - a) * t;
	}

	//Clamps value between a minimum and maximum
	static double clamp(double min, double max, double value) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}
};
