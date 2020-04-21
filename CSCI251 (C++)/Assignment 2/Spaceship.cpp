#include <iostream>
#include "Spaceship.h"
#include "Utility.h"
using namespace std;

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
#define DEFENSE 7
#define ATTACK 8

Spaceship::Spaceship(string _type, int resources[RESOURCE_COUNT], int _defense, int _attack)
{
	type = _type;
	shipHealth = 100;
	shipResources[CASH_INDEX] = resources[CASH_INDEX];
	shipResources[FOOD_INDEX] = resources[FOOD_INDEX];
	shipResources[FUEL_INDEX] = resources[FUEL_INDEX];
	shipResources[AMMO_INDEX] = resources[AMMO_INDEX];
	defense = _defense;
	attack = _attack;
}

OpponentSpaceship::OpponentSpaceship(string _type, int resources[RESOURCE_COUNT], int _defense, int _attack, Species _occupiedBy)
									: Spaceship(_type, resources, _defense, _attack)
{
	occupiedBy = _occupiedBy;
}

PlayerSpaceship::PlayerSpaceship(string _type, int resources[RESOURCE_COUNT], int _defense, int _attack, string _shipName, int _cargoCapacity[4], vector<Officer*> _officers, int _abilities[7])
								: Spaceship(_type, resources, _defense, _attack)
{
	shipName = _shipName;
	officers = _officers;
	crewCount = 50;
	cargoCapacity[CASH_INDEX] = _cargoCapacity[CASH_INDEX];
	cargoCapacity[FOOD_INDEX] = _cargoCapacity[FOOD_INDEX];
	cargoCapacity[FUEL_INDEX] = _cargoCapacity[FUEL_INDEX];
	cargoCapacity[AMMO_INDEX] = _cargoCapacity[AMMO_INDEX];
	abilities[DIPLOMACY] = _abilities[DIPLOMACY];
	abilities[BARTER] = _abilities[BARTER];
	abilities[TRAVEL_EFFICIENCY] = _abilities[TRAVEL_EFFICIENCY];
	abilities[COMBAT_MANUEVERS] = _abilities[COMBAT_MANUEVERS];
	abilities[CONFLICT_EVASION] = _abilities[CONFLICT_EVASION];
	abilities[RECOVERY] = _abilities[RECOVERY];
	abilities[MINING_ABILITY] = _abilities[MINING_ABILITY];
}

void Spaceship::displayShipInfo()
{
	cout << "Alien spaceship abilities:" << endl;
	cout << "Defense: " << defense << endl;
	cout << "Attack: " << attack << endl;

	cout << endl; 
}


void Spaceship::setHealth(int _shipHealth) 
{ 
	if (_shipHealth  <= 0)
	{
		shipHealth = 0;
	}
	else if (_shipHealth >= 100)
	{
		shipHealth = 100;
	}
	else 
	{
		shipHealth = _shipHealth; 
	}	
} 


void Spaceship::displayResourceInfo()
{	
	cout << "Resource information:" << endl;

	cout << "Cash: " << shipResources[CASH_INDEX] << endl;
	cout << "Food: " << shipResources[FOOD_INDEX] << endl;
	cout << "Fuel: " << shipResources[FUEL_INDEX] << endl;
	cout << "Ammo: " << shipResources[AMMO_INDEX] << endl;

	cout << endl;
}

void Spaceship::displayResourceInfo(int oldResourceValues[RESOURCE_COUNT])
{
	cout << "Resource information:" << endl;

	cout << "Cash: " << shipResources[CASH_INDEX] << "   (" << shipResources[CASH_INDEX] - oldResourceValues[CASH_INDEX] << ")" << endl;
	cout << "Food: " << shipResources[FOOD_INDEX] << "   (" << shipResources[FOOD_INDEX] - oldResourceValues[FOOD_INDEX] << ")" << endl;
	cout << "Fuel: " << shipResources[FUEL_INDEX] << "   (" << shipResources[FUEL_INDEX] - oldResourceValues[FUEL_INDEX] << ")" << endl;
	cout << "Ammo: " << shipResources[AMMO_INDEX] << "   (" << shipResources[AMMO_INDEX] - oldResourceValues[AMMO_INDEX] << ")" << endl;

	cout << endl;
}

int PlayerSpaceship::getAbility(int abilityIndex)
{
	switch (abilityIndex)
	{
		case DIPLOMACY:
			return abilities[DIPLOMACY] + ((Captain*)(officers.at(0)))->getDiplomacy();
			break;
		case BARTER:
			return abilities[BARTER] + ((Captain*)(officers.at(0)))->getBarter();
			break;
		case TRAVEL_EFFICIENCY:
			return abilities[TRAVEL_EFFICIENCY] + (((Pilot*)(officers.at(1)))->getTravelEfficiency() + ((Engineer*)(officers.at(2)))->getTravelEfficiency()) / 2;
			break;
		case COMBAT_MANUEVERS:
			return abilities[COMBAT_MANUEVERS] + (((Pilot*)(officers.at(1)))->getCombatManeuvers() + ((Engineer*)(officers.at(2)))->getCombatManeuvers()) / 2;
			break;
		case CONFLICT_EVASION:
			return abilities[CONFLICT_EVASION] + (((Pilot*)(officers.at(1)))->getEvasion() + ((Engineer*)(officers.at(2)))->getEvasion()) / 2; 
			break;
		case RECOVERY:
			return abilities[RECOVERY] + ((Engineer*)(officers.at(0)))->getRecovery();
			break;
		case MINING_ABILITY:
			return abilities[MINING_ABILITY] + ((Miner*)(officers.at(0)))->getMining();
			break;
		case DEFENSE:
			return defense + ((Commando*)(officers.at(0)))->getDefense();
			break;
		case ATTACK:
			return attack + ((Commando*)(officers.at(0)))->getAttack();
			break;
	}
	return 0;
}

void PlayerSpaceship::changeResourceAmount(int resourceIndex, int change)
{
	// potentially need to check that the index matches one of the four resources 
	if (shipResources[resourceIndex] + change <= 0)
	{
		shipResources[resourceIndex] = 0;
	}
	else 
	{	
		shipResources[resourceIndex] += change; 
	}
}

void PlayerSpaceship::displayShipInfo()
{
	cout << "Player spaceship statistics:" << endl;
	cout << "Health: " << shipHealth << endl;
	cout << "Crew count: " << crewCount << endl;
	cout << "Diplomacy: " << getAbility(DIPLOMACY) << endl;
	cout << "Barter: " << getAbility(BARTER) << endl;
	cout << "Travel efficiency: " << getAbility(TRAVEL_EFFICIENCY) << endl;
	cout << "Combat maneuvers: " << getAbility(COMBAT_MANUEVERS) << endl;
	cout << "Conflict evasion: " << getAbility(CONFLICT_EVASION) << endl;
	cout << "Recovery: " << getAbility(RECOVERY) << endl;
	cout << "Mining ability: " << getAbility(MINING_ABILITY) << endl;
	cout << "Defense: " << getAbility(DEFENSE) << endl;
	cout << "Attack: " << getAbility(ATTACK) << endl;
	
	cout << endl;
	displayResourceInfo();
}

void PlayerSpaceship::displayDeceased()
{
	cout << "Deceased officers:" << endl;

	if (deceasedOfficers.empty())
	{
		cout << "No officer deaths on your journey." << endl;		
	}

	for (auto o : deceasedOfficers)
	{			
		cout << o << endl;
	}
}

void PlayerSpaceship::displaySectorHistory()
{
	cout << "Sectors you encountered along your journey:" << endl;
	for (auto s : sectorHistory)
	{
		cout << s << endl;
	}
	cout << endl;
}

void PlayerSpaceship::consumeResources()
{
	changeResourceAmount(CASH_INDEX, -10 * crewCount);
	changeResourceAmount(FOOD_INDEX, -3 * crewCount);
	changeResourceAmount(FUEL_INDEX, -1 * crewCount);
	
	cout << "Resources have been used from travelling to another sector." << endl << endl;
}

bool PlayerSpaceship::checkEmptyResources()
{	
	if (shipResources[FOOD_INDEX] <= 0)
	{
		cout << "You have ran out of food. Your crew starved to death. Game over!" << endl;
		return true;
	}
	else if (shipResources[FUEL_INDEX] <= 0)
	{
		cout << "You have ran out of fuel. Your crew slowly starves to death as your ship floats aimlessly through space. Game Over!" << endl;
		return true;
	}
	else if (shipResources[CASH_INDEX] <= 0)
	{
		cout << "You have ran out of money. Your funder is not happy with you. They tell you to sieze operations. Game Over!" << endl;
		return true;
	}
	return false;
}

void PlayerSpaceship::checkResourceCapacity()
{
	for (int i = 0; i < RESOURCE_COUNT; i++)
	{
		if (shipResources[i] > cargoCapacity[i])
		{
			switch (i)
			{
				case CASH_INDEX:
					cout << "You have reached the maximum cargo capacity of cash." << endl;
					cout << "Throwing away " << shipResources[i] - cargoCapacity[i] << " cash." << endl;
					break;
				case FOOD_INDEX:
					cout << "You have reached the maximum cargo capacity of food." << endl;
					cout << "Throwing away " << shipResources[i] - cargoCapacity[i] << " food." << endl;
					break;
				case FUEL_INDEX:
					cout << "You have reached the maximum cargo capacity of fuel." << endl;
					cout << "Throwing away " << shipResources[i] - cargoCapacity[i] << " fuel." << endl;
					break;
				case AMMO_INDEX:
					cout << "You have reached the maximum cargo capacity of ammo." << endl;
					cout << "Throwing away " << shipResources[i] - cargoCapacity[i] << " ammo." << endl;
					break;
			}
			shipResources[i] = cargoCapacity[i];
		}
	}
}

void PlayerSpaceship::systemsRecovery()
{
	cout << "Your Engineer is attempting to repair some ship damages..." << endl;
	// have a chance based on recovery skill to bring some ship health back 
	if (diceRoll(0, 100) <= abilities[RECOVERY])
	{
		// repair ship a bit
		int recoveredHealth = diceRoll(1, 15);
		cout << "Your Engineer successfully recovered " << recoveredHealth << " health points" << endl;
		shipHealth += recoveredHealth;
	}
	else 
	{
		// dont repair health 
		cout << "Your Engineer was unable to repair the ship" << endl;
	}

	cout << "Your ship is at " << shipHealth << " health." << endl;
}

void PlayerSpaceship::exploreSector(vector<Species> species, int sectorNumber)
{
	cout << "Sector number: " << sectorNumber << endl << endl;
	
	// percentage chance of event occuring
	int eventNumber = diceRoll(0, 100);

	int currentResources[RESOURCE_COUNT];
	currentResources[CASH_INDEX] = shipResources[CASH_INDEX];
	currentResources[FOOD_INDEX] = shipResources[FOOD_INDEX];
	currentResources[FUEL_INDEX] = shipResources[FUEL_INDEX];
	currentResources[AMMO_INDEX] = shipResources[AMMO_INDEX];

	Species speciesEncountered = species.at(diceRoll(0, 4));

	if (eventNumber <= 10)
	{
		// your thing -- finding Matthew McConaughey and him giving you some resources 
		findingEndurance();
		addPreviousSector(to_string(sectorNumber) + ": McConaughey");
	}
	else if (eventNumber <= 25)
	{
		// empty sector
		cout << "Your pilot could not find anything in this sector." << endl;
		addPreviousSector(to_string(sectorNumber) + ": Empty sector");
	}
	else if (eventNumber <= 40)
	{
		// trading station
		tradeStationEncounter(speciesEncountered);
		addPreviousSector(to_string(sectorNumber) + ": Trading station");
	}
	else if (eventNumber <= 65)
	{ 
		planetEncounter(speciesEncountered, sectorNumber);
		addPreviousSector(to_string(sectorNumber) + ": Planet encounter");
	}
	else
	{
		// spaceship encounter 
		spaceshipEncounter(speciesEncountered, sectorNumber);
		addPreviousSector(to_string(sectorNumber) + ": Spaceship encounter");
	}

	checkResourceCapacity();
	consumeResources();
	displayResourceInfo(currentResources);

	if (shipHealth < 100)
	{
		systemsRecovery();
	}

	cout << "Player health: " << shipHealth << endl << endl;
		
}

void PlayerSpaceship::spaceshipEncounter(Species speciesEncountered, int sectorNumber)
{
	cout << "Your pilot spots a unidentified spaceship in the distance..." << endl << endl;

	// spaceship is created 
	OpponentSpaceship alienShip = OpponentSpaceship::createAlienSpaceship(speciesEncountered);
	// checks if species is hostile or not 
	if (alienShip.getSpecies().getCanFight())
	{
		cout << "The species occupying the " << alienShip.getShipType() << " is known to be hostile!" << endl;
		cout << "A diplomatic solution to avoid conflict will try to be reached..." << endl;
		// if hostile, have a chance of conflict based on diplomacy 
		if (diceRoll(0, 100) > getAbility(DIPLOMACY))
		{
			cout << "A solution was not found, attempting to flee the enemy ship..." << endl;
			if (diceRoll(0, 100) > getAbility(CONFLICT_EVASION))
			{
				cout << "You could not escape the ship! Begin battle!" << endl;	
				battle(alienShip, sectorNumber);
				return;
			}
			else 
			{
				cout << "You successfully escaped the attacking ship!" << endl;
				return; // go back to explore sector function
			}
		}
		else 
		{
			cout << "A diplomatic solution was found. A battle has been averted!" << endl << endl;
		}
	}

	// if not hostile or pass attack check, check if species can trade
	if (alienShip.getSpecies().getCanTrade())
	{
		cout << "The species occupying the " << alienShip.getShipType() << " are known to trade with outsiders..." << endl;
		cout << "An attempt at trading will be made..." << endl;
		// chance of species trading with you is based on ur barter skill 
		if (diceRoll(0, 100) > getAbility(BARTER))
		{
			cout << alienShip.getSpecies().getSpeciesName() << " do not want to trade with you." << endl;
		}
		else 
		{
			cout << alienShip.getSpecies().getSpeciesName() << " wish to trade with you." << endl;
			trade();
		}
	}
	// chance of species trading with you is based on ur barter skill 
	// if trade check passed, initiate trade
	// if failed, continue on journey...
}

void PlayerSpaceship::planetEncounter(Species planetSpecies, int sectorNumber)
{
		//TODO: array of planetNames
	
	cout << "You come across a planet in the distance..." << endl;
	// if unsucessful, planet sends a spaceship up and you battle
	// if successful, do trade check similar to spaceship 

	
	// check if planet is occupied by a species 
	if (diceRoll(0, 1) == 0)
	{
		// occupied planet
		cout << "This planet is occupied by " << planetSpecies.getSpeciesName() << endl;

		// if it is, do a battle check similar to spaceship
		if (planetSpecies.getCanFight())
		{
			cout << planetSpecies.getSpeciesName() << " is known to be hostile!" << endl;
			cout << "A diplomatic solution to avoid conflict will try to be reached..." << endl;

			// try and solve ur quarrels
			if (diceRoll(0, 100) >= getAbility(DIPLOMACY))
			{
				cout << "A solution was not found, " << planetSpecies.getSpeciesName() << "s are sending out a battleship..." << endl;
				cout << "Attempting the leave the planet's orbit..." << endl;

				if (diceRoll(0, 100) >= getAbility(CONFLICT_EVASION))
				{
					cout << "You could not leave the planet's orbit in time and the ship has caught up! Begin Battle!" << endl;
					OpponentSpaceship enemy = OpponentSpaceship::createAlienSpaceship(planetSpecies);
					battle(enemy, sectorNumber);
					return;
				}
				else 
				{
					cout << "You successfully escaped the attacking ship!" << endl;
					return;
				}
			}
			else
			{
				cout << "A diplomatic solution was found. A battle has been averted!" << endl;
			}
		}

		if (planetSpecies.getCanTrade())
		{
			cout << "The species occupying " << planetSpecies.getSpeciesName() << " are known to trade with outsiders..." << endl;
			cout << "An attempt at trading will be made..." << endl;

			if (diceRoll(0, 100) >= getAbility(BARTER))
			{
				cout << planetSpecies.getSpeciesName() << " do not wish to trade with you." << endl;
				cout << "You leave the planet's orbit." << endl; 
				return;
			}
			else 
			{
				cout << planetSpecies.getSpeciesName() << " wish to trade with you." << endl;
				trade();
			}
		}
		else
		{
			cout << "The species occupying " << planetSpecies.getSpeciesName() << " do not trade with outsiders." << endl;
		}
	}
	else 
	{
		cout << "You are in the airspace of an unoccupied planet." << endl;
		cout << "You send down your miner to the planet attempt to mine the resources of this planet..." << endl;

		if (diceRoll(0, 100) <= getAbility(MINING_ABILITY))
		{
			mine();
		}
		else 
		{
			cout << "Your miner was unable to retrieve any resources off this planet." << endl;
		}
	}
}

void PlayerSpaceship::tradeStationEncounter(Species stationSpecies)
{
	// you have encountered the trade station **name** inhabited by **species**
	// 
	string stationNames[5] = { "Rio", "Ormston", "Beershorn", "Sol", "McAven" };

	string station = stationNames[diceRoll(0, 4)];

	cout << "You have encountered the trade station " << station << " inhabited by " << stationSpecies.getSpeciesName() << endl;

	// check ship resources, buy or sell accordingly 
	// e.g. if low on food, buy more food

	if (stationSpecies.getCanTrade())
	{
		cout << "The species occupying this trade station are known to trade with outsiders... Attempting trade negotiations..." << endl;
		if (diceRoll(0, 100) <= getAbility(BARTER))
		{
			cout << stationSpecies.getSpeciesName() << " wish to trade with you..." << endl;
			trade();
		}
		else
		{
			cout << stationSpecies.getSpeciesName() << " do not want to trade with you. You leave the trade station and continue your journey..." << endl;
			return;
		}
	}
	else
	{
		cout << "The species occupying this trade station only trade with members of their own species. You cannot trade here. Going to the next sector..." << endl;
		return;
	}
}

void PlayerSpaceship::findingEndurance()
{
	cout << "While travelling through the vast nothingness that is space, you stumble upon an odd circular looking ship." << endl;

	cout << "Before your ship's computer finishes processing the unknown ship's information, you here a beautiful, grizzley voice coming through your intercoms." << endl;
	cout << "Intercom: This is Matthew McConaughey." << endl;
	cout << "Suddenly the galaxy became a better place, the beautiful, sometimes incomphrehensible deep tone of McConaughey's voice sparks a light within your crew that none of them have felt before." << endl;

	shipHealth += 10;

	cout << "You gain an extra 10 ship health, and the comfort of knowing that that beautiful man is still out there, saving earth." << endl; 
}

void PlayerSpaceship::battle(OpponentSpaceship enemy, int sectorNumber)
{
	int round = 1;

	while (true) // going to battle until one of the ships dies 
	{
		cout << endl;
		cout << "Round " << round << endl;
		cout << "Your turn." << endl;

		if (diceRoll(0, 100) <= attack)
		{
			changeResourceAmount(AMMO_INDEX, -1);
			int damageDealt = diceRoll(10, 25);
			cout << "You successfully hit the enemy ship dealing " << damageDealt << " damage!" << endl;
			enemy.setHealth( enemy.getHealth() - damageDealt );
		}
		else 
		{
			cout << "Your weapons systems malfunctioned! No shot was fired." << endl;
		}

		if (enemy.getHealth() <= 0)
		{
			cout << "You have won the battle. Salvaging enemy resources..." << endl;
			changeResourceAmount(CASH_INDEX, enemy.getShipResources(CASH_INDEX));
			changeResourceAmount(FOOD_INDEX, enemy.getShipResources(FOOD_INDEX));
			changeResourceAmount(FUEL_INDEX, enemy.getShipResources(FUEL_INDEX));
			changeResourceAmount(AMMO_INDEX, enemy.getShipResources(AMMO_INDEX));
			return;
		}
		
		round++;

		cout << endl;
		cout << "Round " << round << endl;
		cout << "Enemy's turn." << endl << endl;

		if (diceRoll(0, 100) <= enemy.getAttack())
		{
			cout << "Enemy is firing a shot, attempting to evade..." << endl;
			if (diceRoll(0, 100) <= getAbility(COMBAT_MANUEVERS))
			{
				cout << "Shot successfully missed!" << endl;
			}
			else 
			{
				int damageDealt = diceRoll(5, 15);
				cout << "Our ship was hit dealing " << damageDealt << " damage!" << endl;
				setHealth ( shipHealth - damageDealt );

				// have a check that if player health is lower than a threshold, there is a chance that a officer can die!
				if (shipHealth <= 30 && diceRoll(0, 100) <= shipHealth)
				{
					// roll a die to figure out who dies 
					// record that officers detials in the death log 
					Officer* deadOfficer = getOfficers().at(diceRoll(0, 4));
					string officerDeath = "Rank: " + deadOfficer->getRank() + ", Name: " + deadOfficer->getName() + ", Sector of Death: " + to_string(sectorNumber) + ", Cause of death: Spaceship battle";
					deceasedOfficers.push_back(officerDeath);
					deadOfficer->promoteReplacement();
					crewCount -= diceRoll(1, 5);
					cout << "An officer has died and been replaced." << endl;
					cout << "You have lost some crew members." << endl; 
					cout << "The updated abilities for your ship are as follows:" << endl;
					displayShipInfo();
				}
			}
		}
		else 
		{
			cout << "Enemy's weapons malfunctioned They did not fire a shot!" << endl;
		}

		if (shipHealth <= 0)
		{
			cout << "You have lost the battle. Your ship has been destroyed." << endl;
			return;
		}

		round++;
	}
}

void PlayerSpaceship::mine()
{
	// have 3 attempts at mining a resource based on a check from your mining skill 
	// if successful attempt get a material that can be used to make fuel 
	// then add to player resources and remove from mine resources
	// if not successful, try again 

	int fuelMined = 0;

	int cavernNumber = 1;

	while (cavernNumber < 4)
	{
		if (diceRoll(0, 100) <= getAbility(MINING_ABILITY))
		{
			// get resources
			int minedResources = diceRoll(150, 500);

			cout << "Your miner has successfully mined " << minedResources << " fuel. " << endl;

			fuelMined += minedResources;
		}
		else
		{
			cout << "Your miner could not collect any fuel from this cavern." << endl;
		}		

		cavernNumber++;
	}

	cout << "Your miner mined " << fuelMined << " fuel from the mine operation." << endl;
	changeResourceAmount(FUEL_INDEX, fuelMined);
}

void PlayerSpaceship::trade()
{
	if (shipResources[FUEL_INDEX] <= 200)
	{
		cout << "You are running low on fuel and wish to purchase more." << endl;

		changeResourceAmount(CASH_INDEX, -1000);
		changeResourceAmount(FUEL_INDEX, 1000);

		cout << "You have purchased 1000 fuel costing you 1000 dollars." << endl;
	}

	if (shipResources[FOOD_INDEX] <= 400)
	{
		cout << "You are running low on food and wish to purchase more." << endl;

		changeResourceAmount(CASH_INDEX, -1500);
		changeResourceAmount(FOOD_INDEX, 1500);

		cout << "You have purchased 1500 fuel costing you 1500 dollars." << endl;
	}

	if (shipResources[AMMO_INDEX] <= 20)
	{
		cout << "You are running low on ammo and wish to purchase more." << endl;

		changeResourceAmount(CASH_INDEX, -50);
		changeResourceAmount(AMMO_INDEX, 50);

		cout << "You have purchased 50 fuel costing you 50 dollars." << endl;
	}
}

void PlayerSpaceship::deallocateMemory()
{
	for (int i = 0; i < officers.size(); i++)
	{
		delete officers[i];
	}
	officers.clear();
}
