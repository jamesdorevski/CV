#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Latin.h"
#include "Morse.h"
#include "Braille.h"
using namespace std;

map<char, std::string> Latin::latinToMorseRules;
map<char, std::string> Latin::latinToBrailleRules;

Latin::Latin(char _letter) {
	letter = _letter;
}

bool operator< (const Latin& lhs, const Latin& rhs) {
	return lhs.letter < rhs.letter;
}

bool operator== (const Latin& lhs, const Latin& rhs) {
	return lhs.letter == rhs.letter; 
}

ostream& operator<< (ostream& out, const Latin& lat) {
    out << lat.letter;
    return out;
}
