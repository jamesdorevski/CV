#ifndef TEXTCONTAINER_H
#define TEXTCONTAINER_H

#include <vector>
#include <string>

class Latin;
class Morse;
class Braille;

template<typename T>
class TextContainer {
	char alphabet;
	std::vector<T> fileContents;

	public:
		TextContainer() {}
		TextContainer(char _alphabet);

		void readFile(char fileName[]);

		void readLetter(std::vector<Latin>& contents, std::string currentLine);
		void readLetter(std::vector<Morse>& contents, std::string currentLine);
		void readLetter(std::vector<Braille>& contents, std::string currentLine);

		void outputTranslation(char fileName[]);

		char getType() { return alphabet; }
		std::vector<T> getContents() { return fileContents; }

		void setContents(std::vector<T> _fileContents) { fileContents = _fileContents; }

		void displayCharArray(std::vector<T> &contents);
		void displayContents();
		void containerContent();
};

#endif
