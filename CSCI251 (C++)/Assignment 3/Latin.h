#ifndef LATIN_H
#define LATIN_H

#include <iostream>
#include <string>
#include <map>

class Morse;
class Braille;

class Latin {
	friend bool operator< (const Latin& lhs, const Latin& rhs);
	friend bool operator== (const Latin& lhs, const Latin& rhs);
	friend std::ostream& operator<< (std::ostream& out, const Latin& lat);

	char letter;	
	static std::map<char, std::string> latinToMorseRules;
	static std::map<char, std::string> latinToBrailleRules;

	public:
		Latin() {}
		Latin(char _letter);

		char getSymbol() { return letter; }
		static std::map<char, std::string> getLatinToMorseRules() { return latinToMorseRules; }
		static std::map<char, std::string> getLatinToBrailleRules() { return latinToBrailleRules; }

		void setSymbol(char setLetter) { letter = setLetter; }
		static void setLatinToMorseRules(std::map<char, std::string> _latinToMorseRules) { latinToMorseRules =  _latinToMorseRules; }
		static void setLatinToBrailleRules(std::map<char, std::string> _latinToBrailleRules) { latinToBrailleRules = _latinToBrailleRules; }
};

#endif
