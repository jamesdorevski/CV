#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <map>

class Latin;
class Morse;
class Braille;

template<typename T, typename U>
bool findDuplicateValue(std::map<T, U> &alphabetMap, U value);

// validation functions 
bool isValidLetter(char element, char alphabet);
bool isValidLetterTextFile(char element, char alphabet);

std::string displayAlphabet(char alphabet);

// reading 
void readMorseTranslationFile();
void readBrailleTranslationFile();

void translateText(TextContainer<Latin>& inContents, TextContainer<Morse>& translatedContents);
void translateText(TextContainer<Latin>& inContents, TextContainer<Braille>& translatedContents);
void translateText(TextContainer<Morse>& inContents, TextContainer<Latin>& translatedContents);
void translateText(TextContainer<Braille>& inContents, TextContainer<Latin>& translatedContents);

#endif
