#ifndef RANDOM_H
#define RANDOM_H

#include "stdlib.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

static class Random
{
private:

public:
	Random();
	Random(int seed);					/*This generates a pseudo-random seed based on an integer*/

	float rand_0_1(void);				//!Returns a float value between 0.0 and 1.0

	float randf(float min, float max);	//!Returns a float value between 2 inputs, min and max

	int randi(int min, int max);		//!*Returns a integer value between 2 inputs, min and max


};

#endif
