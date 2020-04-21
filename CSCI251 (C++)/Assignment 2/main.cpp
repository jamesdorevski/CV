#include <iostream>
#include <vector>
#include "Spaceship.h"
#include "Officer.h"
#include "Species.h"
using namespace std;

#define RESOURCE_COUNT 4
#define CASH_INDEX 0
#define FOOD_INDEX 1
#define FUEL_INDEX 2
#define AMMO_INDEX 3

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cerr << "You need to give the number of sectors." << endl;
		exit(1);
	}

	int sectorNumbers = atoi(argv[1]);

	if (sectorNumbers < 1 || sectorNumbers > 50)
	{
		cerr << "Amount of sectors can only be between 1 and 50" << endl;
		exit(2);
	}

	// create alien species
	vector<Species> species = Species::createSpecies();

	// creating player 
	vector<Officer*> officers = Officer::createOfficers();
	PlayerSpaceship player = PlayerSpaceship::initialisePlayerSpaceship(officers);
	player.displayShipInfo();

	// save starting resource count to compare in the endgame stats
	int startingResources[RESOURCE_COUNT];
	startingResources[CASH_INDEX] = player.getShipResources(CASH_INDEX);
	startingResources[FOOD_INDEX] = player.getShipResources(FOOD_INDEX);
	startingResources[FUEL_INDEX] = player.getShipResources(FUEL_INDEX);
	startingResources[AMMO_INDEX] = player.getShipResources(AMMO_INDEX);

	int i = 0;
	for (i = 1; i <= sectorNumbers; i++)
	{
		player.exploreSector(species, i);

		if (player.checkEmptyResources() || player.getHealth() == 0)
		{	
			break;
		}

		cout << "You continue your journey into the unknown..." << endl << endl;
	}

	cout << "The journey lasted for " << i << " sectors." << endl;
	player.displayResourceInfo(startingResources);
	player.displaySectorHistory();
	player.displayDeceased();
	player.deallocateMemory();

	return 0;
}


