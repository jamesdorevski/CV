/*
	Assignment 1 - Word Processor
	James Dorevski 
	jd107
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <time.h>
using namespace std;

#define DICTIONARY_SIZE 400000
#define MAX_WORD_LENGTH 35
#define DICTIONARY_HASH_SIZE 131072
#define POEM_HASH_SIZE 256
#define ANAGRAM_OUTPUT_LIMIT 10 

struct Anagrams;

// Part 1 & 2 prototypes
void linearSearchEmordnilap();
void binarySearchEmordnilap();
void hashEmordnilap();
void readDictionaryFile();
void insertWord(string word);
void findEmordnilapLinear(string word);
void findEmordnilapBinarySearch(string word);
string invertWord(string word);
void insertDictionaryHash(string word);
void findEmordnilapHashLookup(string word);

// Part 3 prototypes
void performSpellCheck();
void readSampleFile();
void preProcessWord(string &word); 
void insertSampleWordHash(string word);
bool findValidWordBST(string &word);

// Part 4 prototypes
void anagramSearch();
Anagrams* findAnagramHash(string word);
bool isAnagram(string one, string two);
string sortString(string &word);
void orderedAnagramBinaryTree(Anagrams *toInsert, Anagrams *currentNode);
void printAnagrams(Anagrams *node);

// Part 2 struct
struct DictionaryWord {
	string word;
	DictionaryWord *next;
};

// Part 3 struct
struct SampleWord {
	string word;
	bool valid;
	bool unique;
	SampleWord* next;
};

// Part 4 struct
struct Anagrams {
	string word;
	string wordsAnagrams;
	int anagramCount;
	Anagrams *left;
	Anagrams *right;
};

// Part 1 & 2 global variables
string dictionary[DICTIONARY_SIZE];
DictionaryWord dictionaryHash[DICTIONARY_HASH_SIZE];
int primeNumbers[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
int wordIndex = 0;
int emordnilapCountLinear = 0;
int emordnilapCountPartTwo = 0;
string longestEmordnilap;

// Part 3 global variables
SampleWord sampleValidUniqueWordsHash[POEM_HASH_SIZE];
int validWords = 0;
int uniqueWords = 0;
int validUniqueWords = 0;

// Part 4 global variables
int numberOfWordsWithAnagrams = 0;
int totalNumberOfAnagrams = 0;
int printedAnagrams = 0;
Anagrams *root;
Anagrams *longestAnagram;
Anagrams *wordWithMostAnagrams;

int main() {
	time_t start, end;
	time(&start);

	// Part 1 
	linearSearchEmordnilap();

	// Part 2
	// creating a hash with chaining for the dictionary as a speed enhancement
	for (int i = 0; i < wordIndex; i++) {
		insertDictionaryHash(dictionary[i]);
	}

	binarySearchEmordnilap();
	hashEmordnilap();

	// Part 3
	performSpellCheck();	

	// Part 4 
	anagramSearch();

	time(&end);
	double duration = difftime(end, start);
	cout << endl << "Total program run-time (secs): " << duration << endl;

	return 0;
}

void linearSearchEmordnilap() {
	cout << "PART 1 --- Linear search of Emordnilaps." << endl;
	time_t start, end;
	time(&start);

	readDictionaryFile();	

	cout << "Number of words in dictionary: " << wordIndex << endl;
	cout << "First 5 emordnilap words:" << endl;
	for (int i = 0; emordnilapCountLinear < 5; i++) {
		// exclude single character entries
		if (dictionary[i].length() < 2) {
			continue;
		}
		findEmordnilapLinear(dictionary[i]);
	}

	time(&end);
	double duration = difftime(end, start);
	cout << endl << "Total run time of emordnilap linear search to find 5 emordnilaps (secs): " << duration << endl;
}

void binarySearchEmordnilap() {
	cout << endl << endl << "PART 2 --- Improved Emordnilap Search." << endl;
	time_t start, end;
	time(&start);

	cout << "Using Binary Search to find ALL emordnilaps..." << endl;
	cout << "First 10 emordnilap words: " << endl;
	for (int i = 0; i < DICTIONARY_SIZE; i++) {
		if (dictionary[i].length() < 2) {
			continue;
		}
		findEmordnilapBinarySearch(dictionary[i]);
	}

	cout << "The longest emordnilap found was: " << longestEmordnilap << endl;

	time(&end);
	double duration = difftime(end, start);
	cout << endl << "Total run time of emordnilap binary search to find ALL emordnilaps (secs): " << duration << endl;
}

// Using hash with chaining for a speed enhancement
void hashEmordnilap() {
	time_t start, end;
	time(&start);

	cout << endl << "Using Dictionary Hash to find ALL emordnilaps..." << endl;
	for (int i = 0; i < DICTIONARY_SIZE; i++) {
		if (dictionary[i].size() < 2) {
			continue;
		}
		findEmordnilapHashLookup(dictionary[i]);
	}

	time(&end);
	double duration = difftime(end, start);
	cout << "Total run time of emordnilap hash lookup to find ALL emordnilaps (secs): " << duration << endl;
}

void readDictionaryFile() {
	ifstream in("dictionary.txt");

	if (!in.good()) {
		cerr << "dictionary.txt not found. Exiting program." << endl;
		exit(1);
	}

	string currentLine;
	while (!in.eof()) {
		in >> currentLine;
		if (currentLine.length() > MAX_WORD_LENGTH || currentLine.empty() || currentLine == " ") {
			cerr << "Word is longer than 35 characters. Aborting operation." << endl;
			exit(1);
		}
		insertWord(currentLine);
	}
	in.close();
}

void insertWord(string word) {
	if (wordIndex > DICTIONARY_SIZE) {
		cerr << "Dictionary is full." << endl;
	} else {
		dictionary[wordIndex++] = word;
	}
}

void findEmordnilapLinear(string word) {
	string reversedWord = invertWord(word);
	for (int i = 0; i < wordIndex; i++) {	
		if (dictionary[i] == reversedWord) {
			cout << word << " : " << reversedWord << endl;
			emordnilapCountLinear++;
		}
	}
}

void findEmordnilapBinarySearch(string word) {
	string reversedWord = invertWord(word);
	int targetIndex;
	int leftNode = 0;
	int rightNode = wordIndex - 1;

	while (leftNode <= rightNode) {
		targetIndex = floor((leftNode + rightNode) / 2);
		if (dictionary[targetIndex] < reversedWord) {
			leftNode = targetIndex + 1;
		} else if (dictionary[targetIndex] > reversedWord) {
			rightNode = targetIndex - 1;
		} else {
			if (emordnilapCountPartTwo < 10) {
	    		cout << word << " : " << reversedWord << endl;
	    	}

	    	if (reversedWord.size() > longestEmordnilap.size()) {
	    		longestEmordnilap = reversedWord;
	    	} 
			emordnilapCountPartTwo++;
			return;

		}
	}
}

string invertWord(string word) {
    for (unsigned int i = 0; i < word.length() / 2; i++) { 
        swap(word[i], word[word.length() - i - 1]); 
    }
    return word;
}

void insertDictionaryHash(string word) {
	long hashValue = 1;
	for (unsigned int i = 0; i < word.size(); i++) {
		hashValue *= primeNumbers[word[i] - 'a']; // explained in specification at the bottom
		hashValue %= DICTIONARY_HASH_SIZE;
	}

	if (dictionaryHash[hashValue].word == "") {
		dictionaryHash[hashValue].word = word;
		dictionaryHash[hashValue].next = NULL;
	} else {
		DictionaryWord *newWord = new DictionaryWord();
		newWord->word = word;
		newWord->next = NULL;

		if (dictionaryHash[hashValue].next) {
			DictionaryWord *nextDictionaryWordPointer = dictionaryHash[hashValue].next;
			while (nextDictionaryWordPointer->next != NULL) {
				nextDictionaryWordPointer = nextDictionaryWordPointer->next;
			}
			nextDictionaryWordPointer->next = newWord;
		} else {
			dictionaryHash[hashValue].next = newWord;
		}
	}
}

void findEmordnilapHashLookup(string word) {
	long hashValue = 1;
	for (unsigned int i = 0; i < word.size(); i++) {
		hashValue *= primeNumbers[word[i] - 'a']; 
		hashValue %= DICTIONARY_HASH_SIZE;
	}

	string reversedWord = invertWord(word);

	if (dictionaryHash[hashValue].word == reversedWord) {
		if (reversedWord.size() > longestEmordnilap.size()) {
			longestEmordnilap = reversedWord;
		}
	}

	DictionaryWord *nextDictionaryWordPointer = dictionaryHash[hashValue].next;

	while (nextDictionaryWordPointer != NULL) {
		if (nextDictionaryWordPointer->word == reversedWord) {
			if (reversedWord.size() > longestEmordnilap.size()) {
				longestEmordnilap = reversedWord;
			}
		}
		nextDictionaryWordPointer = nextDictionaryWordPointer->next;
	}
}

void performSpellCheck() {
	time_t start, end;
	time(&start);

	cout << endl << endl << "PART 3 --- Spell Check" << endl;
	readSampleFile();
	cout << "Number of valid words from sample.txt: " << validWords << endl;
	cout << "Number of unique words read: " << uniqueWords << endl;
	cout << "Number of valid unique words: " << validUniqueWords << endl;

	time(&end);
	double duration = difftime(end, start);
	cout << endl << "Total run time of the spell-check (secs): " << duration << endl;
}

void readSampleFile() {
	ifstream in("sample.txt");

	if (!in.good()) {
		cerr << "sample.txt not found. Exiting program." << endl;
		exit(1);
	}

	string currentWord;
	while (!in.eof()) {
		in >> currentWord;
		preProcessWord(currentWord);
		if (currentWord == "") {
			continue;
		}
		insertSampleWordHash(currentWord);
		validWords++;
	}
	in.close();
}

// proprocesses a passed string as per the assignment spec
void preProcessWord(string &word) {
	int wordLength = word.size();
	for (int i = 0; i < wordLength; i++) {
		if (ispunct(word[i])) {
			word.erase(i--, 1);
			wordLength = word.size();
		} else {
			word[i] = tolower(word[i]);
		}
	}
}

void insertSampleWordHash(string word) {
	int hashValue = 0;
	// retrieve the int value of all the characters in word
	for (unsigned int i = 0; i < word.size(); i++) {
		hashValue += word[i];
	} 

	hashValue %= POEM_HASH_SIZE;

	// if word at the position is empty then store the word there 
	if (sampleValidUniqueWordsHash[hashValue].word == "") {
		sampleValidUniqueWordsHash[hashValue].word = word;
		sampleValidUniqueWordsHash[hashValue].unique = true;
		sampleValidUniqueWordsHash[hashValue].valid = findValidWordBST(word);

		if (sampleValidUniqueWordsHash[hashValue].valid) {
			validUniqueWords++;
		}
		uniqueWords++;
		sampleValidUniqueWordsHash[hashValue].next = NULL;
	} else if (sampleValidUniqueWordsHash[hashValue].word == word) {
		return;
	} else {
		SampleWord *pointer = sampleValidUniqueWordsHash[hashValue].next;

		// searches the hash chain for the inserting word
		while (pointer != NULL) {
			if (pointer->word == word) {
				return;
			}
			pointer = pointer->next;
		}

		SampleWord *newWord = new SampleWord();
		uniqueWords++;
		newWord->valid = findValidWordBST(word);

		if (newWord->valid) {
			validUniqueWords++;
		}

		newWord->word = word;
		newWord->unique = true;
		newWord->next = sampleValidUniqueWordsHash[hashValue].next;
		sampleValidUniqueWordsHash[hashValue].next = newWord;
	}
}


bool findValidWordBST(string &word) {
	int targetIndex;
	int leftNode = 0;
	int rightNode = wordIndex;

	while (leftNode <= rightNode) {
		targetIndex = ((leftNode + rightNode) / 2);

		if (dictionary[targetIndex] < word) {
			leftNode = targetIndex + 1;
		} else if (dictionary[targetIndex] > word) {
			rightNode = targetIndex - 1;
		} else {
			return true;
		}
	}

	return false;
}

// searches for anagrams and inserts them into a binary tree 
void anagramSearch() {
	cout << endl << endl << "PART 4 --- Ordered Anagram Search" << endl;

	time_t start, end;
	time(&start);

	for (int i = 0; i < POEM_HASH_SIZE; i++) {
		if (sampleValidUniqueWordsHash[i].word == "") {
			continue;
		}

		if (sampleValidUniqueWordsHash[i].valid) {
			Anagrams *temp = findAnagramHash(sampleValidUniqueWordsHash[i].word);

			if (temp != NULL) {
				numberOfWordsWithAnagrams++;
				orderedAnagramBinaryTree(temp, root);
			}
		}

		SampleWord *nextWordPointer = sampleValidUniqueWordsHash[i].next;
		while (nextWordPointer != NULL) {
			if (nextWordPointer->valid) {
				Anagrams *temp = findAnagramHash(nextWordPointer->word);
				if (temp != NULL) {
					numberOfWordsWithAnagrams++;
					orderedAnagramBinaryTree(temp, root);
				}
			}
			nextWordPointer = nextWordPointer->next;
		}
	}

	cout << "First 10 words with anagrams found: " << endl;
	printAnagrams(root);
	cout << endl << "Word with the most anagrams: " << wordWithMostAnagrams->word << endl;
	cout << "Longest word with anagrams: " << longestAnagram->word << endl;
	cout << "Total number of words with anagrams: " << numberOfWordsWithAnagrams << endl;
	cout << "Total number of anagrams: " << totalNumberOfAnagrams << endl;

	time(&end);
	double duration = difftime(end, start);
	cout << endl << "Total time to process anagrams (secs): " << duration << endl;
}

// searches for anagrams in the dictionary hash 
Anagrams* findAnagramHash(string word) {
	long hashValue = 1;

	for (unsigned int i = 0; i < word.size(); i++) {
		hashValue *= primeNumbers[word[i] - 'a'];
		hashValue %= DICTIONARY_HASH_SIZE;
	}

	string wordsFound = "";
	int anagramCount = 0;

	if (isAnagram(dictionaryHash[hashValue].word, word)) {
		anagramCount++;
		totalNumberOfAnagrams++;
		wordsFound += dictionaryHash[hashValue].word + " ";
	}

	DictionaryWord *nextWordPointer = dictionaryHash[hashValue].next;

	while (nextWordPointer != NULL) {
		if (isAnagram(nextWordPointer->word, word)) {
			anagramCount++;
			totalNumberOfAnagrams++;
			wordsFound += nextWordPointer->word + " ";
		}
		nextWordPointer = nextWordPointer->next;
	}

	if (anagramCount == 0) {
		return NULL;
	}

	Anagrams *anagramsPointer = new Anagrams();
	anagramsPointer->word = word;
	anagramsPointer->wordsAnagrams = wordsFound;
	anagramsPointer->anagramCount = anagramCount;
	anagramsPointer->left = NULL;
	anagramsPointer->right = NULL;

	return anagramsPointer;
}

bool isAnagram(string one, string two) {
	if (one.size() != two.size()) {
		return false;
	}

	// words can't be anagrams of themselves
	if (one == two) {
		return false;
	}

	string oneSorted = sortString(one);
	string twoSorted = sortString(two);

	return oneSorted == twoSorted;
}

// rebuilds string in alphabetical order for anagram search
string sortString(string &word) {
	int charCount[26] = {0};
	string sorted;

	for (unsigned int i = 0; i < word.size(); i++) {
		charCount[word[i] - 'a']++;
	}

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < charCount[i]; j++) {
			sorted += (char) ('a' + i);
		}
	}
	return sorted;
}

// inserts the ordered anagrams into a binary tree
void orderedAnagramBinaryTree(Anagrams *toInsert, Anagrams *currentNode) {
	if (root == NULL) {
		root = toInsert;
		longestAnagram = toInsert;
		wordWithMostAnagrams = toInsert;
	} else {
		if (toInsert->word < currentNode->word) {
			if (currentNode->left != NULL) {
				orderedAnagramBinaryTree(toInsert, currentNode->left);
			} else {
				currentNode->left = toInsert;
				if (toInsert->word.size() > longestAnagram->word.size()) {
					longestAnagram = toInsert;
				}

				if (toInsert->anagramCount > wordWithMostAnagrams->anagramCount) {
					wordWithMostAnagrams = toInsert;
				}
			}
		} else {
			if (currentNode->right != NULL) {
				orderedAnagramBinaryTree(toInsert, currentNode->right);
			} else {
				currentNode->right = toInsert;
				if (toInsert->word.size() > longestAnagram->word.size()) {
					longestAnagram = toInsert;
				}
				if (toInsert->anagramCount > wordWithMostAnagrams->anagramCount) {
					wordWithMostAnagrams = toInsert;
				}
			}
		}
	}
}

void printAnagrams(Anagrams *node) {
	if (node == NULL) {
		return;
	}

	if (node->left != NULL) {
		printAnagrams(node->left);
	}

	if (printedAnagrams < ANAGRAM_OUTPUT_LIMIT) {
		cout << node->word << ": " << node->wordsAnagrams << endl;
		printedAnagrams++;
	}

	if (node->right != NULL) {
		printAnagrams(node->right);
	}
}


/*	
	STEP 1 & 2
	Speedup factor (theoretical) - reduced from an O(n^2) (linear) to an O(n*logn) (binary).
	An additional speed enhancement was achieved by implementing a hash with chaining to store the dictionary contents in. O(n) lookup speeds.
	Using a hash reduced the time to find all emordnilaps to 2 seconds.   
	
	The following is a speedup factor test testing how long it took to find a specified amount of emordnilaps using the different methods:
		Actual speedup factor test:
		Emordnilaps: 		50		100		500		ALL
		------------------------------------------------
		Linear Search       594s    N/A     N/A     N/A
		Binary Search       1s    	2s      3s      4s
		Hash                N/A     N/A     N/A     2s
	

	STEP 3
	A hash with chaining is used to store the unique sample words. 
	A binary search is used to search for these words in the hashed dictionary. 

	STEP 4
	A hash with chaining is used to store the dictionary contents in. 
	The hash function sets the hashValue of a word to the product of many primes (primes are assigned to each character by subtracting the ASCII value of 'a' from it's own ASCII value)
	modulo the dictionary's hash size. The dictionary's hash size was chosen as a base 2 number around 1/4 of the size of the number of words in the dictionary. 

	The dictionary hash function is used to find anagrams. 
	Found anagrams are stored in a binary tree of objects that contain the original word and the word's anagrams in a string. 
	The binary tree allowed the anagrams to be printed in alphabetical order. (because BST's are well-ordered).


	Total program run-time: 12 seconds (running on Banshee)
*/
