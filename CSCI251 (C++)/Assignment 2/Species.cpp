#include <iostream>
#include "Species.h"
using namespace std;

Species::Species(string _speciesName, bool _canFight, bool _canTrade)
{
	speciesName = _speciesName;
	canFight = _canFight;
	canTrade = _canTrade;
}

void Species::displaySpecies()
{
	cout << "The species " << speciesName << " has been discovered in the galaxy." << endl;
	if (canFight)
	{
		cout << "They are known to be hostile." << endl;
	}
	else
	{ 
		cout << "They are not a hostile race." << endl;
	}

	if (canTrade)
	{
		cout << "They are open to the possibility of trading." << endl;
	}
	else
	{
		cout << "They will never trade with you." << endl;
	}

	cout << endl;
}
