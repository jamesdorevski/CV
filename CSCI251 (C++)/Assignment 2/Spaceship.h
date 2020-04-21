#ifndef SPACESHIP_H
#define SPACESHIP_H


#include <vector>
#include <string>
#include "Officer.h"
#include "Species.h"
#include "Utility.h"

#define RESOURCE_COUNT 4
#define CASH_INDEX 0
#define FOOD_INDEX 1
#define FUEL_INDEX 2
#define AMMO_INDEX 3

#define ABILITY_COUNT 7
#define DIPLOMACY 0
#define BARTER 1
#define TRAVEL_EFFICIENCY 2
#define COMBAT_MANUEVERS 3
#define CONFLICT_EVASION 4
#define RECOVERY 5
#define MINING_ABILITY 6


class Spaceship
{
	protected:
		std::string type;
		int shipHealth;		
		int shipResources[RESOURCE_COUNT];
		int defense;	
		int attack;

	public:
		Spaceship() {}
		Spaceship(std::string, int[RESOURCE_COUNT], int, int);
		virtual void displayShipInfo();
		
		std::string getShipType() { return type; }
		int getHealth() { return shipHealth; }

		int getShipResources(int resourceType) { return shipResources[resourceType]; }		
		int getDefense() { return defense; }
		int getAttack() { return attack; }

		void setHealth(int);

		void displayResourceInfo();
		void displayResourceInfo(int[RESOURCE_COUNT]);

};

class OpponentSpaceship : public Spaceship
{
	Species occupiedBy;

	public:
		OpponentSpaceship() {}
		OpponentSpaceship(std::string, int[RESOURCE_COUNT], int, int, Species);

		Species getSpecies() { return occupiedBy; }

		void setSpecies(Species _occupiedBy) { occupiedBy = _occupiedBy; }

		static OpponentSpaceship createAlienSpaceship(Species species)
		{
			int randomSpaceship = diceRoll(1, 5);
			
			int alienResources[RESOURCE_COUNT];
			alienResources[CASH_INDEX] = 1000;
			alienResources[FOOD_INDEX] = 500;
			alienResources[FUEL_INDEX] = 500;
			alienResources[AMMO_INDEX] = 20;
			
			std::string type;
			int defense;
			int attack;

			switch (randomSpaceship)
			{
				case 1:
					type = "Frigate";
					defense = diceRoll(35, 100);
					attack = diceRoll(35, 100);
					break;

				case 2: 
					type = "Freighter";
					defense = diceRoll(30, 100);
					attack = diceRoll(10, 100);
					break;

				case 3:
					type = "Old-Reliable";
					defense = diceRoll(25, 100);
					attack = diceRoll(20, 100);
					break;

				case 4:
					type = "Explorer";
					defense = diceRoll(10, 100);
					attack = diceRoll(10, 100);
					break;

				case 5:
					type = "Big Boi";
					defense = diceRoll(40, 100);
					attack = diceRoll(40, 100);
					break;
			}

			OpponentSpaceship alienShip(type, alienResources, defense, attack, species);

			std::cout << "Enemy ship: " << alienShip.getShipType() << " occupied by: " << alienShip.getSpecies().getSpeciesName() << std::endl;

			alienShip.displayShipInfo();

			return alienShip;
		}
};


class PlayerSpaceship : public Spaceship
{
	std::string shipName;
	int cargoCapacity[RESOURCE_COUNT];
	int abilities[ABILITY_COUNT];
	int crewCount;
	std::vector<Officer*> officers;
	std::vector<std::string> deceasedOfficers;
	std::vector<std::string> sectorHistory;

	public:
		PlayerSpaceship() {}
		PlayerSpaceship(std::string, int[RESOURCE_COUNT], int, int, std::string, int[RESOURCE_COUNT], std::vector<Officer*>, int[ABILITY_COUNT]);
		~PlayerSpaceship() {}

		std::string getShipName() { return shipName; }
		int getCargoCapacity(int resourceType) { return cargoCapacity[resourceType]; }
		int getCrewCount() { return crewCount; }	
		int getAbility(int);
		std::vector<Officer*> getOfficers() { return officers; }
		std::vector<std::string> getDeadOfficers() { return deceasedOfficers; }
		std::vector<std::string> getSectorHistory() { return sectorHistory; }

		void changeResourceAmount(int, int);
		void setCrewCount(int _crewCount) { crewCount = _crewCount; }
		void officerDeath(std::string _deadOfficer) { deceasedOfficers.push_back(_deadOfficer); }

		void displayShipInfo();
		void displayDeceased();
		void displaySectorHistory();

		void consumeResources();
		bool checkEmptyResources();
		void checkResourceCapacity();
		void systemsRecovery();
		void deallocateMemory();


		void exploreSector(std::vector<Species>, int);
		void spaceshipEncounter(Species, int);
		void planetEncounter(Species, int);
		void tradeStationEncounter(Species);
		void findingEndurance();

		void addPreviousSector(std::string sector)
		{
			sectorHistory.push_back(sector);
		}

		void battle(OpponentSpaceship, int);
		void mine();
		void trade();

		static PlayerSpaceship initialisePlayerSpaceship(std::vector<Officer*> officers)
		{
			int randomSpaceship = diceRoll(1, 5);
			//TODO: add more names to array 

			std::string shipNames[5] = {"Planet Express Ship", "Ford Focus Trend", "Nugget", "Heart of Gold", "Oof"};

			int startingResources[RESOURCE_COUNT];
			startingResources[CASH_INDEX] = 20000;
			startingResources[FOOD_INDEX] = 3000;
			startingResources[FUEL_INDEX] = 500;
			startingResources[AMMO_INDEX] = 50;

			std::string type;
			int cargoCapacity[RESOURCE_COUNT];
			int defense;
			int attack;
			int abilities[ABILITY_COUNT];

			switch (randomSpaceship)
			{
				//TODO:: capacity
				case 1:
					type = "Frigate";
					cargoCapacity[CASH_INDEX] = diceRoll(10000, 15000);
					cargoCapacity[FOOD_INDEX] = diceRoll(10000, 15000);
					cargoCapacity[FUEL_INDEX] = diceRoll(10000, 15000);
					cargoCapacity[AMMO_INDEX] = diceRoll(50, 100);
					abilities[DIPLOMACY] = diceRoll(30, 45);
					abilities[BARTER] = diceRoll(10, 20);
					abilities[TRAVEL_EFFICIENCY] = diceRoll(30, 40);
					abilities[COMBAT_MANUEVERS] = diceRoll(40, 50);
					abilities[CONFLICT_EVASION] = diceRoll(30, 35);
					defense = diceRoll(35, 45);
					abilities[RECOVERY] = diceRoll(30, 45);
					abilities[MINING_ABILITY] = diceRoll(10, 15);
					attack = diceRoll(35, 50);
					break;

				case 2: 
					type = "Freighter";
					cargoCapacity[CASH_INDEX] = diceRoll(17500, 30000);
					cargoCapacity[FOOD_INDEX] = diceRoll(17500, 30000);
					cargoCapacity[FUEL_INDEX] = diceRoll(17500, 30000);
					cargoCapacity[AMMO_INDEX] = diceRoll(75, 150);
					abilities[DIPLOMACY] = diceRoll(30, 45);
					abilities[BARTER] = diceRoll(30, 45);
					abilities[TRAVEL_EFFICIENCY] = diceRoll(5, 20);
					abilities[COMBAT_MANUEVERS] = diceRoll(10, 30);
					abilities[CONFLICT_EVASION] = diceRoll(5, 15);
					defense = diceRoll(30, 50);
					abilities[RECOVERY] = diceRoll(30, 50);
					abilities[MINING_ABILITY] = diceRoll(30, 40);
					attack = diceRoll(10, 30);
					break;

				case 3:
					type = "Old-Reliable";
					cargoCapacity[CASH_INDEX] = diceRoll(15000, 25000);
					cargoCapacity[FOOD_INDEX] = diceRoll(15000, 25000);
					cargoCapacity[FUEL_INDEX] = diceRoll(15000, 25000);
					cargoCapacity[AMMO_INDEX] = diceRoll(50, 150);
					abilities[DIPLOMACY] = diceRoll(20, 40);
					abilities[BARTER] = diceRoll(20, 40);
					abilities[TRAVEL_EFFICIENCY] = diceRoll(25, 50);
					abilities[COMBAT_MANUEVERS] = diceRoll(25, 50);
					abilities[CONFLICT_EVASION] = diceRoll(25, 50);
					defense = diceRoll(25, 35);
					abilities[RECOVERY] = diceRoll(25, 35);
					abilities[MINING_ABILITY] = diceRoll(30, 40);
					attack = diceRoll(20, 40);
					break;

				case 4:
					type = "Explorer";
					cargoCapacity[CASH_INDEX] = diceRoll(12000, 24000);
					cargoCapacity[FOOD_INDEX] = diceRoll(12000, 24000);
					cargoCapacity[FUEL_INDEX] = diceRoll(12000, 24000);
					cargoCapacity[AMMO_INDEX] = diceRoll(60, 100);
					abilities[DIPLOMACY] = diceRoll(40, 50);
					abilities[BARTER] = diceRoll(40, 50);
					abilities[TRAVEL_EFFICIENCY] = diceRoll(35, 45);
					abilities[COMBAT_MANUEVERS] = diceRoll(10, 20);
					abilities[CONFLICT_EVASION] = diceRoll(10, 30);
					defense = diceRoll(10, 25);
					abilities[RECOVERY] = diceRoll(20, 25);
					abilities[MINING_ABILITY] = diceRoll(30, 40);
					attack = diceRoll(10, 25);
					break;

				case 5:
					type = "Big Boi";
					cargoCapacity[CASH_INDEX] = diceRoll(20000, 40000);
					cargoCapacity[FOOD_INDEX] = diceRoll(20000, 40000);
					cargoCapacity[FUEL_INDEX] = diceRoll(20000, 40000);
					cargoCapacity[AMMO_INDEX] = diceRoll(200, 300);
					abilities[DIPLOMACY] = diceRoll(5, 10);
					abilities[BARTER] = diceRoll(5, 10);
					abilities[TRAVEL_EFFICIENCY] = diceRoll(10, 20);
					abilities[COMBAT_MANUEVERS] = diceRoll(10, 20);
					abilities[CONFLICT_EVASION] = diceRoll(10, 20);
					defense = diceRoll(40, 50);
					abilities[RECOVERY] = diceRoll(30, 50);
					abilities[MINING_ABILITY] = diceRoll(20, 30);
					attack = diceRoll(40, 50);
					break;
			}
			
			PlayerSpaceship player(type, startingResources, defense, attack, shipNames[diceRoll(0, 4)], cargoCapacity, officers, abilities);
		
			std::cout << "Ship " << player.getShipType() << " called " <<  player.getShipName() << " has been established. " << std::endl;

			return player;
		}
};

#endif
