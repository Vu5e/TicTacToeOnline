#include "Random.h"

Random::Random()
{

}

Random::Random(int seed)
{
	srand(seed);
	//float temp = rand();

	//std::cout << temp << std::endl;
}

float Random::rand_0_1(void)
{
	float val = (float)rand() / (float)RAND_MAX;
	return val;
}

float Random::randf(float min, float max)
{
	/*float temp = ((float)rand()) / (float)RAND_MAX;
	float dif = max - min;

	float inc = temp * dif;

	temp = min + inc;

	return temp;*/

	float val = (((float)rand()) / (float)RAND_MAX * (max - min)) + min;

	return val;
}

int Random::randi(int min, int max)
{
	int val = rand() % ((max - min) + 1) + min;
	return val;
}
