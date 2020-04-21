#ifndef SPECIES_H
#define SPECIES_H

#include <vector>
#include <string>

class Species
{
	std::string speciesName;
	bool canFight;
	bool canTrade;

	public:
		Species() {}
		Species(std::string, bool, bool);
		static std::vector<Species> createSpecies()
		{
			std::vector<Species> species;

			Species species1("Macedonians", true, true);
			Species species2("Blob Fish", false, true);
			Species species3("Hooloovoo", true, false);
			Species species4("Amazonians", true, true);
			Species species5("Blamphs", true, false);

			species.push_back(species1);
			species.push_back(species2);
			species.push_back(species3);
			species.push_back(species4);
			species.push_back(species5);

			for (auto s : species)
			{
				s.displaySpecies();
			}

			return species;
		}

		std::string getSpeciesName() { return speciesName; }
		bool getCanFight() { return canFight; }
		bool getCanTrade() { return canTrade; }

		void displaySpecies();
};

#endif
