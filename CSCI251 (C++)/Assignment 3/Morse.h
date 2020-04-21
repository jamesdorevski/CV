#ifndef MORSE_H
#define MORSE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

class Latin;

class Morse {
	friend bool operator< (const Morse& lhs, const Morse& rhs);
	friend bool operator== (const Morse& lhs, const Morse& rhs);
	friend std::ostream& operator<< (std::ostream& out, const Morse& morse);
	
	char symbol;
	static std::map<std::string, char> morseToLatinRules;

	public:
		Morse() {}
		Morse(char _symbol);
		
		char getSymbol() { return symbol; }
		static std::map<std::string, char> getMorseToLatinRules() { return morseToLatinRules;}

		void setSymbol(char _symbol) { symbol = _symbol; }
		static void setMorseToLatinRules(std::map<std::string, char> _morseToLatinRules) { morseToLatinRules = _morseToLatinRules; }
};

#endif
