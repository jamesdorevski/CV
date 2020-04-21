#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include "TextContainer.h"
#include "Latin.h"
#include "Morse.h"
#include "Braille.h"
#include "functions.h"
using namespace std;

static const vector<char> latinLetters {'_', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
static const vector<char> morseSymbols {' ', '.', '-'};
static const vector<char> brailleBits {'0', '1'};

template<typename T>
TextContainer<T>::TextContainer(char _alphabet) {
	alphabet = _alphabet;
}

template<typename T>
void TextContainer<T>::readFile(char fileName[]) {
	ifstream in(fileName); 

	if (!in.good()) {
		cerr << "File containing text to be translated not found." << endl;
		exit(1);
	}

	if (in.bad()) {
		cerr << "Unable to open input file. Check file permissions." << endl;
		exit(1);
	}

	cout << endl << "Reading " << displayAlphabet(alphabet) << " input from " << fileName << "." << endl;

	vector<T> contents;
	string currentLine;

	while (!in.eof()) {
		getline(in, currentLine);

		if (currentLine.empty() || currentLine == " " || currentLine == "\n") {
			continue;
		}

		// checks if input contains all correct characters from the specified alphabet
		for (auto i : currentLine) {
			if (!isValidLetterTextFile(i, alphabet)) {
				displayCharArray(contents);
				cerr << "The input text does not match the input alphabet specified. Aborting operation." << endl;
				exit(1);
			} 
		}
		readLetter(contents, currentLine);
	}

	if (alphabet == 'B' && !(contents.size() % 6 == 0)) {
		cerr << "The number of characters in this Braille sequence is not a multiple of six therefore cannot be translated to Latin. Aborting operation" << endl;
		exit(1);
	}

	cout << "Reading successful." << endl;
	fileContents = contents;
}

template<typename T>
void TextContainer<T>::readLetter(vector<Latin>& contents, string currentLine) {
	Latin object;
	for (auto i : currentLine) {
		if (i == ' ') {
			object.setSymbol('_');
		} else {
			object.setSymbol(i);
		}
		contents.push_back(object); 
	}
}

template<typename T>
void TextContainer<T>::readLetter(vector<Morse>& contents, string currentLine) {
	for (auto i : currentLine) {
		Morse object(i);
		contents.push_back(object);
	}
	Morse object(' ');
	contents.push_back(object);
}

template<typename T>
void TextContainer<T>::readLetter(vector<Braille>& contents, string currentLine) {
	for (auto i : currentLine) {
		Braille object(i);
		contents.push_back(object);
	}
}

template<typename T>
void TextContainer<T>::outputTranslation(char fileName[]) {
	ofstream out(fileName);

	if (!out.good()) {
		cerr << "Could not create an open output file." << endl;
		exit(1);
	}

	for (auto i : fileContents) {
		if (i.getSymbol() == '_') {
			out << " ";
		} else {
			out << i;
		}
	}
	out.close();
}

template<typename T>
void TextContainer<T>::displayCharArray(vector<T>& contents) {
	for (auto it = contents.begin(); it != contents.end(); it++) {
		cout << *it;
	}
	cout << endl;
}

template<typename T>
void TextContainer<T>::displayContents() {
	cout << displayAlphabet(alphabet) << " container content: " << endl;
	for (auto it = fileContents.begin(); it != fileContents.end(); it++) {
		if (*it == '_') {
			cout << " ";
		} else {
			cout << *it;
		}
	}
	cout << endl;
}

template<typename T>
void TextContainer<T>::containerContent() {
	cout << endl << displayAlphabet(alphabet) << " container size: " << fileContents.size() << endl;
	cout << "Symbol distribution:" << endl;
	if (alphabet == 'L') {
		for (auto i : latinLetters) {
			// returns true if i is in the fileContents else excludes it from the output
			if (find(fileContents.begin(), fileContents.end(), i) != fileContents.end()) {
				if (i == '_') {
					cout << "space : " << count(fileContents.begin(), fileContents.end(), i) << endl;
				} else {
					cout << i << " : " << count(fileContents.begin(), fileContents.end(), i) << endl;
				}	
			} else {
				continue;
			}
		}
	} else if (alphabet == 'M') {
		for (auto i : morseSymbols) {
			if (i == ' ') {
				cout << "space : " << count(fileContents.begin(), fileContents.end(), i) << endl;
			} else {
				cout << i << " : " << count(fileContents.begin(), fileContents.end(), i) << endl;
			}	
		}
	} else if (alphabet == 'B') {
		for (auto i : brailleBits) {
			cout << i << " : " << count(fileContents.begin(), fileContents.end(), i) << endl;
		}
	}
}

template class TextContainer<Latin>;
template class TextContainer<Morse>;
template class TextContainer<Braille>;
