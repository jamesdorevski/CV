#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Latin.h"
#include "Morse.h"
#include "Braille.h"
#include "TextContainer.h"
#include "functions.h"
using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 5) {
		cerr << "The program does not have the correct number of files needed for it to run. Please specify the correct files in the command line." << endl; 
		cerr << "The program must run as: ./TS From To In.txt Out.txt" << endl;
		exit(1);
	}

	char inputAlphabet = argv[1][0];
	char outputAlphabet = argv[2][0];
	char* inputTextFile = argv[3];
	char* outputTextFile = argv[4];

	if (inputAlphabet == outputAlphabet) {
		cerr << "The arguments From and To cannot be the same. Please specify two different alphabets. Program will now end." << endl;
		exit(1);
	}

	if (inputAlphabet != 'L' && inputAlphabet != 'M' && inputAlphabet != 'B') {
		cerr << "Incorrect argument for alphabet specified. Please only use 'L' 'M' 'B'." << endl;
		exit(1);
	} else if (outputAlphabet != 'L' && outputAlphabet != 'M' && outputAlphabet != 'B') {
		cerr << "Incorrect argument for alphabet specified. Please only use 'L' 'M' 'B'." << endl;
		exit(1);
	} 

	// creating containers and reading in translation files for use later 
	TextContainer<Latin> latinContainer('L');
	TextContainer<Morse> morseContainer('M');
	TextContainer<Braille> brailleContainer('B');

	readMorseTranslationFile();
	readBrailleTranslationFile();

	cout << endl << "Translation from " << displayAlphabet(inputAlphabet) << " to " << displayAlphabet(outputAlphabet) << endl;
	if (inputAlphabet == 'L') {
		latinContainer.readFile(inputTextFile);
		latinContainer.containerContent();

		if (outputAlphabet == 'M') {
			translateText(latinContainer, morseContainer);
			morseContainer.containerContent();
			morseContainer.outputTranslation(outputTextFile);
		} else if (outputAlphabet == 'B') {
			translateText(latinContainer, brailleContainer);
			brailleContainer.containerContent();
			brailleContainer.outputTranslation(outputTextFile);
		}
	} else if (inputAlphabet == 'M') {
		morseContainer.readFile(inputTextFile);
		morseContainer.containerContent();

		if (outputAlphabet == 'L') {
			translateText(morseContainer, latinContainer);
			latinContainer.containerContent();
			latinContainer.outputTranslation(outputTextFile);			
		} else if (outputAlphabet == 'B') {
			translateText(morseContainer, latinContainer);
			latinContainer.containerContent();
			latinContainer.displayContents();
			translateText(latinContainer, brailleContainer);
			brailleContainer.containerContent();
			brailleContainer.outputTranslation(outputTextFile);		
		}
	} else if (inputAlphabet == 'B') {
		brailleContainer.readFile(inputTextFile);
		brailleContainer.containerContent();

		if (outputAlphabet == 'L') {
			translateText(brailleContainer, latinContainer);
			latinContainer.containerContent();
			latinContainer.outputTranslation(outputTextFile);
		} else if (outputAlphabet == 'M') {
			translateText(brailleContainer, latinContainer);
			latinContainer.containerContent();
			latinContainer.displayContents();
			translateText(latinContainer, morseContainer);
			morseContainer.containerContent();
			morseContainer.outputTranslation(outputTextFile);
		}
	}	

	cout << endl << "All done. " << displayAlphabet(outputAlphabet) << " container written to " << outputTextFile << endl;  
	
	return 0;
}
