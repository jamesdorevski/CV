#include <random>
#include "Utility.h"
using namespace std;

int diceRoll(int min, int max)
{
	// random number generator that will generate a number between the min and max
	static random_device rd; // seed the random generator alogorithm 
	static mt19937 randomNumberGenerator(rd()); // generator 
	uniform_int_distribution<> distribution(min, max);

	return distribution(randomNumberGenerator);
}
