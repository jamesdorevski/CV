#include <iostream>
#include <string>
#include <map>
#include "Latin.h"
#include "Braille.h"
using namespace std;

map<string, char> Braille::brailleToLatinRules;

Braille::Braille(char _brailleBit) {
	brailleBit = _brailleBit;
}

bool operator< (const Braille& lhs, const Braille& rhs) {
	return lhs.brailleBit < rhs.brailleBit;
}

bool operator== (const Braille& lhs, const Braille& rhs) {
	return lhs.brailleBit == rhs.brailleBit;
}

std::ostream& operator<< (std::ostream& out, const Braille& braille) {
	out << braille.brailleBit;
	return out;
}
