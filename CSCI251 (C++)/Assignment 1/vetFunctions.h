#include <string>
#include <vector>

const int MAX_ANIMALS_SIZE = 20;
const int MAX_VETS_SIZE = 10;
const int MAX_PROBLEMS_SIZE = 20;
const int MAX_TREATMENTS_SIZE = 20; 

// structs
struct Animal
{
	std::string name;
	std::string type;
	std::string registration;
	int problem;	
};

struct Vet
{
	std::string name;
	double quality;
};

struct Problem
{
	std::string name;
	double determinationComplexity;
	double treatmentComplexity;
	int treatment;
};

struct Treatment
{
	std::string name;
};

struct Result
{
	int animalNumber;
	std::string animalName;
	std::string vetName;
	std::string correctProblemName;
	int problemAttemptPercentage;
	std::string diagnosedProblemName;
	std::string treatmentName;
	int treatmentAttemptPercentage;
	bool treatmentSuccess;
};

// functions
std::vector<Animal> readAnimals(char[]);
void printAnimals(std::vector<Animal>);

std::vector<Vet> readVets(char[]);
void printVets(std::vector<Vet>);

std::vector<Problem> readProblems(char[]);
void printProblems(std::vector<Problem>);

std::vector<Treatment> readTreatments(char[]);
void printTreatments(std::vector<Treatment>);

std::vector<Result> runClinic(int, std::vector<Animal>, std::vector<Vet>, std::vector<Problem>, std::vector<Treatment>);

int diceRoll(int, int);
int percentageAlgorithm(double, double);

// diagnosis related functions
int attemptDiagnosisPercentage(double, double);
bool determineCorrectDiagnosis(int);
Problem performDiagnosis(bool, int, std::vector<Problem>);

// treatment related functions
int attemptTreatmentPercentage(bool, double, double);
bool applyTreatment(int);

//output results to file
void outputReport(char[], std::vector<Result>);
