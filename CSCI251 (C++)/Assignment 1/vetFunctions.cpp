#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include "vetFunctions.h"
using namespace std;

vector<Animal> readAnimals(char fileName[])
{	
	ifstream in(fileName);

	if (!in.good()) // check if file opened correctly
	{
		cerr << "File containing animals not found." << endl; 
		exit(1);
	}

	// check if file has read permissions
	if (in.bad())
	{
		cerr << "Hardware problem detected. Check file permissions." << endl;
		exit(1);
	}

	vector<Animal> animals;
	Animal a;
	
	// string extraction variables 
	string currentLine;
	string delimiter = ":";
	string endOfLine = ".";

	// counts amount of lines
	int count = 0;

	while (!in.eof())
	{
		if (count >= MAX_ANIMALS_SIZE)
		{
			cerr << "Reached max amount of animals" << endl;
			break;
		}

		getline(in, currentLine);

		size_t pos = 0;
		vector<string> tokens;
		
		while ((pos = currentLine.find(delimiter)) != string::npos)
		{
			string token = currentLine.substr(0, pos);
			tokens.push_back(token);
			currentLine.erase(0, pos + delimiter.length());
		}

		// account for final variable
		pos = currentLine.find(endOfLine);
		tokens.push_back(currentLine.substr(0, pos));

		// addresses the final line without printing the error
		if (tokens.at(0).empty() || tokens.size() == 1)
		{	
			continue;
		}

		// checks if line has the correct amount of variables for the struct
		if (tokens.size() != 4)
		{
			cerr << "The current animal line is formatted incorrectly." << endl;
			continue;
		}

		// creating the Animal object from the tokens vector 
		a.name = tokens.at(0);
		a.type = tokens.at(1);
		a.registration = tokens.at(2);
		a.problem = (int) atof(tokens.at(3).c_str());

		// check registration length equals 5
		if (a.registration.length() != 5)
		{
			cerr << "Registration must be 5 digits long." << endl;
			continue;
		}

		// checks if problem parameter is empty OR not an int
		if (a.problem == 0)
		{
			cerr << "Invalid problem int." << endl;
			continue;
		}

		animals.push_back(a);

		count++;
	}

	in.close();

	return animals;
}

void printAnimals(vector<Animal> animals)
{
	cout << endl << "Animals to be checked:" << endl;

	for (vector<Animal>::iterator it = animals.begin(); it != animals.end(); it++)
	{
		cout << "Name: "<< (*it).name <<
			", Type: "<< (*it).type <<
			", Registration: "<< (*it).registration << 
			", Problem: "<< (*it).problem << endl;
	}
}

vector<Vet> readVets(char fileName[])
{	
	ifstream in(fileName);

	if (!in.good())
	{
		cerr << "File containing vets not found." << endl; 
		exit(1);
	}

	// check if file has read permissions
	if (in.bad())
	{
		cerr << "Hardware problem detected. Check file permissions." << endl;
		exit(1);
	}

	vector<Vet> vets; 
	Vet v;

	string currentLine;
	string delimiter = ":";
	string endOfLine = ".";

	int count = 0;

	while (!in.eof())
	{
		if (count >= MAX_VETS_SIZE)
		{
			cerr << "Reached max amount of vets" << endl;
			break;
		}

		getline(in, currentLine);

		size_t pos = 0;
		vector<string> tokens;
		
		while ((pos = currentLine.find(delimiter)) != string::npos)
		{
			string token = currentLine.substr(0, pos);
			tokens.push_back(token);
			currentLine.erase(0, pos + delimiter.length());
		}

		// account for final variable
		pos = currentLine.find(endOfLine);
		tokens.push_back(currentLine.substr(0, pos));

		// removing the final line without printing the error
		if (tokens.at(0).empty() || tokens.size() == 1)
		{	
			continue;
		}

		if (tokens.size() != 2)
		{
			cerr << "The current vet line is formatted incorrectly." << endl;
			continue;
		}

		v.name = tokens.at(0);
		v.quality = (double) atof(tokens.at(1).c_str());

		if (v.quality < 1 || v.quality > 100 || v.quality == 0)
		{
			cerr << "Vet quality must be an int in the range 1 to 100." << endl;
			continue;
		}

		vets.push_back(v);

		count++;
	}

	in.close();

	return vets;
}

void printVets(vector<Vet> vets)
{
	cout << endl << "Avaliable vets:" << endl;

	for (vector<Vet>::iterator it = vets.begin(); it != vets.end(); it++)
	{
		cout << "Name: " << (*it).name << 
			", Quality: "<< (*it).quality << endl;
	}

	cout << endl;
}

vector<Problem> readProblems(char fileName[])
{
	ifstream in(fileName);

	if (!in.good())
	{
		cerr << "File containing problems not found." << endl; 
		exit(1);
	}

	vector<Problem> problems;
	Problem p;

	string currentLine;
	string delimiter = ":";
	string endOfLine = ".";

	int count = 0;

	while (!in.eof())
	{	
		if (count >= MAX_PROBLEMS_SIZE)
		{
			cerr << "Reached max amount of problems" << endl;
			break;
		}

		getline(in, currentLine);

		size_t pos = 0;
		vector<string> tokens;
		
		while ((pos = currentLine.find(delimiter)) != string::npos)
		{
			string token = currentLine.substr(0, pos);
			tokens.push_back(token);
			currentLine.erase(0, pos + delimiter.length());
		}

		// account for final variable
		pos = currentLine.find(endOfLine);
		tokens.push_back(currentLine.substr(0, pos));

		// removing the final line without printing the error
		if (tokens.at(0).empty() || tokens.size() == 1)
		{	
			continue;
		}

		if (tokens.size() != 4)
		{
			cerr << "The current problem line is formatted incorrectly." << endl;
			continue;
		}

		p.name = tokens.at(0);
		p.determinationComplexity = (double) atof(tokens.at(1).c_str());
		p.treatmentComplexity = (double) atof(tokens.at(2).c_str());
		p.treatment = (int) atof(tokens.at(3).c_str());

		if (p.determinationComplexity < 1 || p.determinationComplexity > 100 || p.treatmentComplexity < 1 || p.treatmentComplexity > 100 || p.treatment == 0)
		{
			cerr << "Problem Determination or Treatment complexity is incorrect. They must be an int between 1 and 100." << endl;
			continue;
		}

		problems.push_back(p);

		count++;
	}

	in.close();

	return problems;
}

void printProblems(vector<Problem> problems)
{
	cout << "Potential problems:" << endl;

	for (vector<Problem>::iterator it = problems.begin(); it != problems.end(); it++)
	{
		cout << "Name: " << (*it).name <<
			", Determination Complexity: "<< (*it).determinationComplexity <<
			", Treatment Complexity: "<< (*it).treatmentComplexity <<
			", Treatment: "<< (*it).treatment << endl; 
	}

	cout << endl;
}

vector<Treatment> readTreatments(char fileName[])
{
	ifstream in(fileName);

	if (!in.good())
	{
		cerr << "File contaning treatments not found." << endl; 
		exit(1);
	}

	if (in.bad())
	{
		cerr << "Hardware problem detected. Check file permissions." << endl;
		exit(1);
	}
	
	vector<Treatment> treatments;
	Treatment t;

	string currentLine;

	int count = 0;

	while (!in.eof())
	{	
		if (count >= MAX_TREATMENTS_SIZE)
		{
			cerr << "Reached max amount of treatments" << endl;
			break;
		}

		getline(in, currentLine);

		// a good treatment will never be less than 4 character long
		// OR removing empty lines
		if (currentLine.empty() || currentLine.at(0) == ' ' || currentLine.length() < 4 || currentLine == "\n")
		{	
			cerr << "Invalid treatment has been entered." << endl;
			continue;
		}

		t.name = currentLine;
		treatments.push_back(t);

		count++;
	}

	in.close();

	return treatments;
}

void printTreatments(vector<Treatment> treatments)
{
	cout << "Avaliable treatments:" << endl;

	for (vector<Treatment>::iterator it = treatments.begin(); it != treatments.end(); it++)
	{
		cout << "Name: " << (*it).name << endl;
	}

	cout << endl;
}

vector<Result> runClinic(int limit, vector<Animal> animals, vector<Vet> vets, vector<Problem> problems, vector<Treatment> treatments)
{
	vector<Result> results;

	// counter so program knows which animal to select
	int animalIndex = 0;
	// iterate over the number of animals to be checked 
	for (vector<Animal>::iterator it = animals.begin(); it != animals.end(); it++)
	{
		if (limit <= animalIndex)
		{
			cerr << "Specified animal limit (" << limit << ") has been reached." << endl;
			break;
		}

		Animal currentAnimal;
		Vet selectedVet;
		Problem correctProblem; 
		Problem diagnosedProblem;
		Result result;

		// selecting animal
		currentAnimal = animals.at(animalIndex);

		// checks if animal's problem exists
		if (currentAnimal.problem > problems.size())
		{
			cerr << currentAnimal.name << " has a problem that we can't fix! DON'T PANIC" << endl;
			animalIndex++;
			continue;
		}

		// gets the vet object from randomly generated int 
		selectedVet = vets.at(diceRoll(0, vets.size() - 1));
		// gets the animal's correct problem based on int specified in Animal struct 
		correctProblem = problems.at(currentAnimal.problem - 1);

		// diagnosing problem 
		int problemAttemptPercentage = attemptDiagnosisPercentage(selectedVet.quality, correctProblem.determinationComplexity);
		bool correctDiagnosis = determineCorrectDiagnosis(problemAttemptPercentage);
		diagnosedProblem = performDiagnosis(correctDiagnosis, currentAnimal.problem, problems);

		// checks if problem's treatment exists
		if (diagnosedProblem.treatment > treatments.size())
		{
			cerr << "We found a problem with " << currentAnimal.name << ", but we are unable to treat the poor fella." << endl;
			animalIndex++;
			continue;
		}	

		// treating animal
		int treatmentAttemptPercentage = attemptTreatmentPercentage(correctDiagnosis, selectedVet.quality, correctProblem.treatmentComplexity);
		bool treatmentSuccessful = applyTreatment(treatmentAttemptPercentage);

		// compliling vet visit results into a struct to simplify the output process
		result.animalNumber = animalIndex;
		result.animalName = currentAnimal.name;
		result.vetName = selectedVet.name;
		result.correctProblemName = correctProblem.name;
		result.problemAttemptPercentage = problemAttemptPercentage;
		result.diagnosedProblemName = diagnosedProblem.name;
		result.treatmentName = treatments.at(diagnosedProblem.treatment - 1).name;
		result.treatmentAttemptPercentage = treatmentAttemptPercentage;
		result.treatmentSuccess = treatmentSuccessful;

		results.push_back(result);

		cout << "Animal " << animalIndex + 1 << " has left the Vet. Moving onto the next animal to be treated..." << endl << endl;

		animalIndex++;
	}

	return results;
}

int diceRoll(int min, int max)
{
	// random number generator that will generate a number between the min and max
	static random_device rd; // seed the random generator alogorithm 
	static mt19937 randomNumberGenerator(rd()); // generator 
	uniform_int_distribution<> distribution(min, max);

	return distribution(randomNumberGenerator);
}

int percentageAlgorithm(double vetQuality, double complexity)
{
	// based off table in spec
	// check difference between skill and complexity
	// divide by 25 as difference of 25 results in the 10% modifier
	// returns the baseline + the 10% difference in skill to complexity 
	double difference = vetQuality - complexity;
	difference = difference / 25;
	return (int) (50 + 10 * difference);
}

int attemptDiagnosisPercentage(double vetQuality, double problemDeterminationComplexity)
{
	// returns the chance of successful diagnosis in %
	return percentageAlgorithm(vetQuality, problemDeterminationComplexity);
}

bool determineCorrectDiagnosis(int problemAttemptPercentage)
{
	int randomNumber = diceRoll(1, 100);

	// returns true if random number generated is lower than the problem attempt percentage
	if (randomNumber < problemAttemptPercentage)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

Problem performDiagnosis(bool correctDiagnosis, int correctProblem, vector<Problem> problems)
{
	if (correctDiagnosis == true)
	{
		// link animal's problem with the correct one 
		return problems.at(correctProblem - 1);
	}
	else 
	{
		// get the number of problems and select a random one 
		int randomProblem = diceRoll(0, problems.size() - 1);
		return problems.at(randomProblem);
	}
}

int attemptTreatmentPercentage(bool correctDiagnosis, double vetQuality, double problemTreatmentComplexity)
{
	if (correctDiagnosis == true)
	{
		// if diagnosis is correct determine treatment success percentage without penalty
		return percentageAlgorithm(vetQuality, problemTreatmentComplexity);
	}
	else 
	{
		// if incorrect, determine treatment success percentage with 25% penalty
		return percentageAlgorithm(vetQuality, problemTreatmentComplexity) / 4;
	}	
}

bool applyTreatment(int treatmentAttemptPercentage)
{
	int randomNumber = diceRoll(1, 100);

	// returns true if random number generated is lower than the problem attempt percentage
	if (randomNumber < treatmentAttemptPercentage)
	{
		return true;
	}
	else 
	{
		return false;
	}	
}

void outputReport(char fileName[], vector<Result> results)
{
	ofstream out(fileName);

	if (!out.good())
	{
		cerr << "Could not create and open output file." << endl;
		exit(1);
	}

	for (vector<Result>::iterator it = results.begin(); it != results.end(); it++)
	{
		out << "Animal no." << (*it).animalNumber + 1 << ":" << endl;
		out << "Name of animal being seen: " << (*it).animalName << endl;
		out << "Name of vet treating " << (*it).animalName <<  ": " << (*it).vetName << endl;
		out << "Correct problem " << (*it).animalName << " has: " << (*it).correctProblemName << endl;
		out << "Chance of " << (*it).vetName << " performing correct diagnosis: " << (*it).problemAttemptPercentage << "%" << endl;
		out << "Diagnosed problem that " << (*it).vetName << " gave: " << (*it).diagnosedProblemName << endl;
		out << "Treatment applied to " << (*it).animalName << ": " << (*it).treatmentName << endl;
		out << "Chance of " << (*it).vetName << " performing successful treatment : " << (*it).treatmentAttemptPercentage << "%" << endl;

		if ((*it).treatmentSuccess == 1)
		{
			out << "The treatment was successful." << endl;
		}
		else
		{
			out << "The treatment was not successful." << endl;
		}

		out << endl;
	}

	out.close();
}
