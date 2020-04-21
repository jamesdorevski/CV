#ifndef BRAILLE_H
#define BRAILLE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

class Latin;

class Braille {
	friend bool operator< (const Braille& lhs, const Braille& rhs);
	friend bool operator== (const Braille& lhs, const Braille& rhs);
	friend std::ostream& operator<< (std::ostream& out, const Braille& braille);

	char brailleBit;
	static std::map<std::string, char> brailleToLatinRules;

	public:
		Braille() {}
		Braille(char _brailleBit);

		char getSymbol() { return brailleBit; }		
		static std::map<std::string, char> getBrailleToLatinRules() { return brailleToLatinRules;}

		void setSymbol(char _bit) { brailleBit = _bit; }
		static void setBrailleToLatinRules(std::map<std::string, char> _brailleToLatinRules) { brailleToLatinRules = _brailleToLatinRules; }
};

#endif
