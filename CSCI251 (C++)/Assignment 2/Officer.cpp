#include <string>
#include "Officer.h"
#include "Utility.h"

using namespace std;

std::vector<Officer*> Officer::createOfficers()
{
	std::vector<Officer*> officers;

	Captain* newCaptain = new Captain("Luke McAven", 24, diceRoll(30, 50), diceRoll(30, 50));
	Pilot* newPilot = new Pilot("Gianluca Strano", 36, diceRoll(30, 50), diceRoll(30, 50), diceRoll(30, 50));
	Engineer* newEngineer = new Engineer("Andrea Burazor", 28, diceRoll(30, 50), diceRoll(30, 50), diceRoll(30, 50), diceRoll(30, 50), diceRoll(30, 50));
	Miner* newMiner = new Miner("Sam Wyz", 40, diceRoll(30, 50));
	Commando* newCommando = new Commando("James Dorevski", 25, diceRoll(30, 50), diceRoll(30, 50));
	
	officers.push_back(newCaptain);
	officers.push_back(newPilot);
	officers.push_back(newEngineer);
	officers.push_back(newMiner);
	officers.push_back(newCommando);

	for (auto o : officers)
	{
		o->displayOfficer();
	}

	return officers;
}


Officer::Officer(string _name, int _age)
{
	name = _name;
	health = 100;
	age = _age;
}

Captain::Captain(string _name, int _age, int _diplomacySkill, int _barterSkill) : Officer(_name, _age)
{
	diplomacySkill = _diplomacySkill;
	barterSkill = _barterSkill;
}

Pilot::Pilot(string _name, int _age, int _travelEfficiencySkill, int _combatManeuversSkill, int _evasionSkill) : Officer(_name, _age)
{
	travelEfficiencySkill = _travelEfficiencySkill;
	combatManeuversSkill = _combatManeuversSkill;
	evasionSkill = _evasionSkill;
}

Engineer::Engineer(string _name, int _age, int _travelEfficiencySkill, int _combatManeuversSkill, int _evasionSkill, int _defenseSkill, int _recoverySkill) : Officer(_name, _age)
{
	travelEfficiencySkill = _travelEfficiencySkill;
	combatManeuversSkill = _combatManeuversSkill;
	evasionSkill = _evasionSkill;
	defenseSkill = _defenseSkill;
	recoverySkill = _recoverySkill;
}

Miner::Miner(string _name, int _age, int _miningSkill) : Officer(_name, _age)
{
	miningSkill = _miningSkill;
}

Commando::Commando(string _name, int _age, int _attackSkill, int _defenseSkill) : Officer(_name, _age)
{
	attackSkill = _attackSkill;
	defenseSkill = _defenseSkill;
}

void Officer::displayOfficer()
{
	cout << getRank() << " " << getName() << " has been recruited." << endl;
	cout << getName() << "'s skills:" << endl;
	printStats();
	cout << endl;
}

void Captain::promoteReplacement()
{
	string names[5] = {"Brendan Jackson", "Johnny", "Ethan", "Sophie", "Juliet"};

	name = names[diceRoll(0, 4)];
	age = diceRoll(18, 50);
	diplomacySkill = diceRoll(20, diplomacySkill);
	barterSkill = diceRoll(20, barterSkill);

	displayOfficer();
}

void Pilot::promoteReplacement()
{
	string names[5] = {"Brendan Jackson", "Johnny", "Ethan", "Sophie", "Juliet"};

	name = names[diceRoll(0, 4)];
	age = diceRoll(18, 50);
	travelEfficiencySkill = diceRoll(20, travelEfficiencySkill);
	combatManeuversSkill = diceRoll(20, combatManeuversSkill);
	evasionSkill = diceRoll(20, evasionSkill);

	displayOfficer();
}

void Engineer::promoteReplacement()
{
	string names[5] = {"Brendan Jackson", "Johnny", "Ethan", "Sophie", "Juliet"};

	name = names[diceRoll(0, 4)];
	age = diceRoll(18, 50);
	travelEfficiencySkill = diceRoll(20, travelEfficiencySkill);
	combatManeuversSkill = diceRoll(20, combatManeuversSkill);
	evasionSkill = diceRoll(20, evasionSkill);
	defenseSkill = diceRoll(20, defenseSkill);
	recoverySkill = diceRoll(20, recoverySkill);

	displayOfficer();
}

void Miner::promoteReplacement()
{
	string names[5] = {"Brendan Jackson", "Johnny", "Ethan", "Sophie", "Juliet"};

	name = names[diceRoll(0, 4)];
	age = diceRoll(18, 50);
	miningSkill = diceRoll(20, miningSkill);

	displayOfficer();
}

void Commando::promoteReplacement()
{
	string names[5] = {"Brendan Jackson", "Johnny", "Ethan", "Sophie", "Juliet"};

	name = names[diceRoll(0, 4)];
	age = diceRoll(18, 50);
	defenseSkill = diceRoll(20, defenseSkill);
	attackSkill = diceRoll(20, attackSkill);

	displayOfficer();
}
