#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <algorithm>
#include "Latin.h"
#include "Morse.h"
#include "Braille.h"
#include "TextContainer.h"
using namespace std;

static const vector<char> validLatinLetters {'_', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
static const vector<char> validLatinLettersForTextFile {'_', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};

template<typename T, typename U>
bool findDuplicateValue(map<T, U> &alphabetMap, U value) {
	auto it = alphabetMap.begin();
	while (it != alphabetMap.end()) {
		// check if element matches with value provided
		if (it->second == value) {
			cerr << "Duplicate found in translation rules. discarding and continuing operation..." << endl;
			return true;
		}
		it++;
	}
	return false;
}

// checks if element passed matches with correct letters/symbols/bits
bool isValidLetter(char element, char alphabet) {
	if (alphabet == 'L') {
		auto it = find(validLatinLetters.begin(), validLatinLetters.end(), element);
		if (it != validLatinLetters.end()) {
			return true;
		}
	} else if (alphabet == 'M') {
		if (element == '.' || element == '-' || element == ' ') {
			return true;
		}
	} else if (alphabet == 'B') {
		if (element == '0' || element == '1') {
			return true;
		}
	} 
	return false;
}

bool isValidLetterTextFile(char element, char alphabet) {
	if (alphabet == 'L') {
		auto it = find(validLatinLettersForTextFile.begin(), validLatinLettersForTextFile.end(), element);
		if (it != validLatinLettersForTextFile.end()) {
			return true;
		}
	} else if (alphabet == 'M') {
		if (element == '.' || element == '-' || element == ' ') {
			return true;
		}
	} else if (alphabet == 'B') {
		if (element == '0' || element == '1') {
			return true;
		}
	} 
	return false;
}

// displays the correct alphabet when needed in couts etc. 
string displayAlphabet(char alphabet) {
	if (alphabet == 'L') {
		return "Latin";
	} else if (alphabet == 'M') {
		return "Morse";
	} else if (alphabet == 'B') {
		return "Braille";
	}
}

void readMorseTranslationFile() {
	ifstream in("Morse.txt");

	if (!in.good()) {
		cerr << "File containing Morse Translation rules was not found." << endl;
		exit(1);
	}

	if (in.bad()) {
		cerr << "Hardware problem detected. Check file permissions." << endl;
		exit(1);
	}

	cout << "Loading Morse translation rules..." << endl;

	map<char, string> latinToMorseRules;
	map<string, char> morseToLatinRules;

	char latinLetter;
	string currentLine;

	while (!in.eof()) {
		string morseSequence;
		getline(in, currentLine);

		if (currentLine.empty() || currentLine == " " || currentLine == "\n") {
			continue;
		}

		// checks if there is a space between the Latin char and Morse sequence 
		if (currentLine.at(1) != ' ') {
			cerr << "The current line of the morse translation file is formatted incorrectly. Aborting operation." << endl;
			exit(1);
		}

		// checking for valid Latin symbols
		if (!isValidLetter(currentLine.at(0), 'L')) {
			cerr << "Character (" << currentLine.at(0) << ") on current line is invalid Latin. Please make sure it's a char a - z or a underscore (_). Aborting operation." << endl;
			exit(1);
		} else {
			latinLetter = currentLine.at(0);
		}

		// checking and adding valid morse symbols to vector
		for (int i = 2; i < currentLine.length(); i++) {
			if (!isValidLetter(currentLine.at(i), 'M')) {
				cerr << "An invalid morse symbol (" << currentLine.at(i) << ") was found in the sequence. Please only include '.' OR '-'. Aboring operation." << endl;
				exit(1);
			} else {
				morseSequence += currentLine.at(i);
			}
		}

		// checking for duplicate elements and adding to maps if not duplicate
		if (!findDuplicateValue(latinToMorseRules, morseSequence) && !(findDuplicateValue(morseToLatinRules, latinLetter))) {
			latinToMorseRules.insert({ latinLetter, morseSequence });
			morseToLatinRules.insert({ morseSequence, latinLetter });			
		}
	}

	if (latinToMorseRules.size() != validLatinLetters.size()) {
		cerr << "The supplied Morse translation rules do not have all the Latin characters. Please make sure to include chars a - z and a underscore (_). Aborting operation." << endl;
		exit(1);
	}

	Latin::setLatinToMorseRules(latinToMorseRules);
	Morse::setMorseToLatinRules(morseToLatinRules);

	cout << "Morse rule loaded successfully." << endl;

	in.close();
}

void readBrailleTranslationFile() {
	ifstream in("Braille.txt");

	if (!in.good()) {
		cerr << "File containing Braille Translation rules was not found." << endl;
		exit(1);
	}

	if (in.bad()) {
		cerr << "Hardware problem detected. Check file permissions." << endl;
		exit(1);
	}

	cout << "Loading Braille translation rules..." << endl;
 
	map<char, string> latinToBrailleRules;
	map<string, char> brailleToLatinRules;

	char latinLetter;
	string currentLine;

	while (!in.eof()) {
		string brailleSequence;
		getline(in, currentLine);

		if (currentLine.empty() || currentLine == " " || currentLine == "\n") {
			continue;
		}

		// checks if there is a space between the Latin char and Braille sequence 
		if (currentLine.at(1) != ' ') {
			cerr << "The current line of the braille translation file is formatted incorrectly. Aborting operation." << endl;
			exit(1);
		}

		// checking for valid Latin symbols
		if (!isValidLetter(currentLine.at(0), 'L')) {
			cerr << "Character (" << currentLine.at(0) << ") on current line is invalid Latin. Please make sure it's a char a - z or a underscore (_). Aborting operation." << endl;
			exit(1);
		} else {
			latinLetter = currentLine.at(0);
		}

		// checking and adding valid braille symbols to vector
		for (int i = 2; i < currentLine.length(); i++) {
			if (!isValidLetter(currentLine.at(i), 'B')) {
				cerr << "An invalid braille symbol (" << currentLine.at(i) << ") was found in the sequence. Please only include 0 OR 1." << endl;
				exit(1);
			} else {
				brailleSequence += currentLine.at(i);		
			}
		}

		// checking for duplicate elements and adding to maps if not duplicate
		if (!findDuplicateValue(latinToBrailleRules, brailleSequence) && !findDuplicateValue(brailleToLatinRules, latinLetter)) {
			latinToBrailleRules.insert({ latinLetter, brailleSequence });
			brailleToLatinRules.insert({ brailleSequence, latinLetter });			
		}
	}

	// checking if all latin elements are included in the translation rules 
	if (latinToBrailleRules.size() != validLatinLetters.size()) {
		cerr << "The supplied Braille translation rules do not have all the Latin characters. Please make sure to include chars a - z and a underscore (_). Aborting operation." << endl;
		exit(1);		
	}

	cout << "Braille rules loaded successfully." << endl;

	// set the static maps in the classes to these maps 
	Latin::setLatinToBrailleRules(latinToBrailleRules);
	Braille::setBrailleToLatinRules(brailleToLatinRules);

	in.close();
}

void translateText(TextContainer<Latin>& inputContents, TextContainer<Morse>& outputContents) {
	cout << endl << "Translating to Morse proceeds." << endl;

	vector<Morse> translatedMorseText;
	string latinString = "";
	Morse spaceSymbol(' ');
	map<char, string> ruleMap = Latin::getLatinToMorseRules();

	// adding matched latin letters to the latinString
 	for (int i = 0; i < inputContents.getContents().size(); i++) {
 		if (inputContents.getContents().at(i).getSymbol() == ' ') {
 			latinString += "_";
 		} else {
 			latinString += inputContents.getContents().at(i).getSymbol();
 		}
 	}

 	// finding the letters in the translating rules, creating the corresponding morse objects based on the matching value and setting the outContainer to the morse vector
 	for (auto i : latinString) {
		auto it = ruleMap.find(i);
		if (it != ruleMap.end()) {
			for (auto j : it->second) {
				Morse symbol(j);
				translatedMorseText.push_back(symbol);
			}
			translatedMorseText.push_back(spaceSymbol);
		}
 	}
 	outputContents.setContents(translatedMorseText);
 	cout << "Translation completed successfully." << endl;
}

void translateText(TextContainer<Latin>& inputContents, TextContainer<Braille>& outputContents) {
	cout << endl << "Translating to Braille proceeds." << endl;

	vector<Braille> translatedBrailleText;
	string latinString = "";
	map<char, string> ruleMap = Latin::getLatinToBrailleRules();

 	for (int i = 0; i < inputContents.getContents().size(); i++) {
 		if (inputContents.getContents().at(i).getSymbol() == ' ') {
 			latinString += "_";
 		} else {
 			latinString += inputContents.getContents().at(i).getSymbol();
 		}
 	}

 	for (auto i : latinString) {
		auto it = ruleMap.find(i);	
		if (it != ruleMap.end()) {
			for (auto j : it->second) {
				Braille bit(j);
				translatedBrailleText.push_back(bit);
			}
		}
 	}
 	outputContents.setContents(translatedBrailleText);
 	cout << "Translation completed successfully." << endl;
}

void translateText(TextContainer<Morse>& inputContents, TextContainer<Latin>& outputContents) {
	cout << endl << "Translating to Latin proceeds." << endl;

	vector<Latin> translatedLatinText;
	string morseString = "";
	map<string, char> ruleMap = Morse::getMorseToLatinRules();

 	for (int i = 0; i < inputContents.getContents().size(); i++) {
 		// adds the found characters to the morseString then once hitting a space, parses the string into latin objects
 		if (inputContents.getContents().at(i).getSymbol() == ' ') {
			auto it = ruleMap.find(morseString);
			if (it != ruleMap.end()) {
				Latin letter(it->second);
				translatedLatinText.push_back(letter);
			}
			morseString = "";
 			continue;
 		} else {
 			morseString += inputContents.getContents().at(i).getSymbol();
 		}
 	}
	outputContents.setContents(translatedLatinText);
	cout << "Translation completed successfully." << endl;
}

void translateText(TextContainer<Braille>& inputContents, TextContainer<Latin>& outputContents) {
	cout << endl << "Translating to Latin proceeds." << endl;

	vector<Latin> translatedLatinText;
 	string brailleString = "";
 	string latinEquivalent = "";
 	map<string, char> ruleMap = Braille::getBrailleToLatinRules();

 	// transforms the braille container into a string 
 	for (int i = 0; i < inputContents.getContents().size(); i++) {
 		brailleString += inputContents.getContents().at(i).getSymbol();
 	}
 
 	// while the brailleString isn't empty - substrings the first 6 characters of the string then finds the corresponding Latin in the ruleMap from it 
 	while (brailleString.size() > 0) {
 		latinEquivalent = brailleString.substr(0, 6);
 		auto it = ruleMap.find(latinEquivalent);
		if (it != ruleMap.end()) {
			Latin letter(it->second);
			translatedLatinText.push_back(letter);
		}
		//deletes the 6 characters already parsed
		brailleString.erase(0, 6);
 	}
 	outputContents.setContents(translatedLatinText);
 	cout << "Translation completed successfully." << endl;
 }
