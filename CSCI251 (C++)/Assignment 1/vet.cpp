#include <iostream>
#include <vector>
#include "vetFunctions.h"
using namespace std;

int main(int argc, char *argv[])
{	
	// checks argc and terinates the program if number of arguments is incorrect
	if (argc != 7)
	{
		cerr << "The program does not have the correct number of files needed for it to run. Please specify the correct files in the command line." << endl <<
		"Program must run as: ./VET limit Animals.txt Vets.txt Problems.txt Treatments.txt Output-file " << endl;
		exit(1);
	}

	// converts command-line argument into int
	int limit = atoi(argv[1]); 

	vector<Animal> animals = readAnimals(argv[2]);
	vector<Vet> vets = readVets(argv[3]);
	vector<Problem> problems = readProblems(argv[4]);
	vector<Treatment> treatments = readTreatments(argv[5]);
	
	printAnimals(animals);
	printVets(vets);
	printProblems(problems);
	printTreatments(treatments);

	vector<Result> results = runClinic(limit, animals, vets, problems, treatments);

	outputReport(argv[6], results);

	cout << "Vet is now closed." << endl;
}
