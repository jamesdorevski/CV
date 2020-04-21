#ifndef OFFICERS_H
#define OFFICERS_H

#include <vector>
#include <string>
#include <iostream>
#include "Utility.h"

class Officer 
{
	protected:
		std::string name;
		int health;
		int age;	

	public:
		Officer() {}
		Officer(std::string, int);

		std::string getName() { return name; }
		virtual std::string getRank() { return "Officer"; }
		virtual char getType() { return 'O'; }
		int getHealth() { return health; }
		int getAge() { return age; }
		virtual void printStats() {}
		void displayOfficer();

		virtual void promoteReplacement() {}

		static std::vector<Officer*> createOfficers();
};

class Captain : public Officer
{
	int diplomacySkill;
	int barterSkill;

	public:
		Captain();
		Captain(std::string, int, int, int);

		std::string getRank() { return "Captain"; }
		char getType() { return 'C'; }
		int getDiplomacy() { return diplomacySkill; }
		int getBarter() { return barterSkill; }
		void printStats() 
		{
			std::cout << "Diplomacy: " << diplomacySkill << std::endl;
			std::cout << "Barter: " << barterSkill << std::endl;
		}

		void promoteReplacement();
};

class Pilot : public Officer
{
	int travelEfficiencySkill;
	int combatManeuversSkill;
	int evasionSkill;

	public:
		Pilot() {}
		Pilot(std::string, int, int, int, int);

		std::string getRank() { return "Pilot"; }
		char getType() { return 'P'; }
		int getTravelEfficiency() { return travelEfficiencySkill; }
		int getCombatManeuvers() { return combatManeuversSkill; }
		int getEvasion() { return evasionSkill; }
		void printStats() 
		{
			std::cout << "Travel efficiency: " << travelEfficiencySkill << std::endl;
			std::cout << "Combat maneuvers: " << combatManeuversSkill << std::endl;
			std::cout << "Evasion skill: " << evasionSkill << std::endl;
		}

		void promoteReplacement();
};

class Engineer : public Officer
{
	int travelEfficiencySkill;
	int combatManeuversSkill;
	int evasionSkill;
	int defenseSkill;
	int recoverySkill;

	public:
		Engineer() {}
		Engineer(std::string, int, int, int, int, int, int);

		std::string getRank() { return "Engineer"; }
		char getType() { return 'E'; }
		int getTravelEfficiency() { return travelEfficiencySkill; }
		int getCombatManeuvers() { return combatManeuversSkill; }
		int getEvasion() { return evasionSkill; }
		int getDefense() { return defenseSkill; }
		int getRecovery() { return recoverySkill; }
		void printStats() 
		{
			std::cout << "Travel efficiency: " << travelEfficiencySkill << std::endl;
			std::cout << "Combat maneuvers: " << combatManeuversSkill << std::endl;
			std::cout << "Evasion skill: " << evasionSkill << std::endl;
			std::cout << "Defense skill: " << defenseSkill << std::endl;
			std::cout << "Recovery skill: " << recoverySkill << std::endl;
		}

		void promoteReplacement();
};

class Miner : public Officer
{
	int miningSkill;

	public:
		Miner() {}
		Miner(std::string, int, int);

		std::string getRank() { return "Miner"; }
		char getType() { return 'M'; }
		int getMining() { return miningSkill; }
		void printStats()
		{
			std::cout << "Mining skill: " << miningSkill << std::endl;
		}

		void promoteReplacement();
};

class Commando : public Officer
{
	int attackSkill;
	int defenseSkill;

	public:
		Commando() {}
		Commando(std::string, int, int, int);

		std::string getRank() { return "Commando"; }
		char getType() { return 'A'; }
		int getAttack() { return attackSkill; }
		int getDefense() { return defenseSkill; }
		void printStats()
		{
			std::cout << "Attack skill: " << attackSkill << std::endl;
			std::cout << "Defense skill: " << defenseSkill << std::endl;
		}

		void promoteReplacement();
};

#endif
