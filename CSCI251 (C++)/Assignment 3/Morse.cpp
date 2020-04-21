#include <iostream>
#include <string>
#include <map>
#include "Latin.h"
#include "Morse.h"
using namespace std;

map<string, char> Morse::morseToLatinRules;

Morse::Morse(char _symbol) {
	symbol = _symbol;
}

bool operator< (const Morse& lhs, const Morse& rhs) {
	return lhs.symbol < rhs.symbol;
}

bool operator==(const Morse& lhs, const Morse& rhs) {
	return lhs.symbol == rhs.symbol; 
}

ostream& operator<<(ostream& out, const Morse& morse) {
    out << morse.symbol;
    return out;
}
