// Prog03.cpp
// Nischal Khanal
// Lab section 11
// Programming Assignment #3

#include "timer.h"
#include "Hash.cpp"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace::std;
using std::string;

string cleanWord(string word);

int main()
{
	
	Timer myTimer;                  // Used to declare the timer
	vector<string> misspelled;      // Vector to store missplled words.
	Hash<string> dictionary;        // Used to load dictionary in Hash data structure
	int skipped = 0;				// Used to count skipped words.
	int successfulCompares = 0;		// Used to count total number of successful compares.
	int unsuccessfulCompares = 0;	// Used to count total number of unsuccessful compares.
	int foundWords = 0;				// Used to count total number of found words.
	int notFoundWords = 0;			// Used to count total number of words that were not found.

	ifstream dictFile("dict.txt");                      // Loading dict.txt.  
	if (!dictFile)                                      // Used to handle file error.
	{
		cerr << "Error finding dictionary file.\nMake sure the file is in the right directory!" << endl;
		dictFile.close();
		dictFile.clear();
	}
	else {
		string dictWord;
		while (dictFile >> dictWord)
		{
			dictionary.addData(cleanWord(dictWord));          // Adds clean word to the dictionary data structure.
		}
		dictFile.close();
		dictFile.clear();
		myTimer.Start();                                      // Starting the timer.
		ifstream bookFile("book.txt");                        // Loading Book.txt.
		if (!bookFile)                       	              // Used to handle file error.
		{
			cerr << "Error finding book file.\nMake sure the file is in the right directory!" << endl;
			bookFile.close();
			bookFile.clear();
		}
		else {
			string bookWord;
			while (bookFile >> bookWord)
			{

				string clean = cleanWord(bookWord);
				if (isalpha(clean[0]))
				{
					int compares = 0;
					if (dictionary.isPresent(clean, compares))
					{
						foundWords++;
						successfulCompares = successfulCompares + compares;
					}
					else
					{
						notFoundWords++;
						unsuccessfulCompares = unsuccessfulCompares + compares;
					}
				}
				else if (!clean.empty())
				{
					skipped++;
				}
			}
				myTimer.Stop();
				bookFile.close();
				bookFile.clear();

				ifstream book("book.txt");
				string word;

				while (book >> word)
				{
					string clean = cleanWord(word);
					if (isalpha(clean[0]))
					{
						int compares = 0;
						if (!dictionary.isPresent(clean, compares))
						{
							misspelled.push_back(clean);
						}
					}
				}
				bookFile.close();
				bookFile.clear();
				// Displaying the output in correct format.
				cout << "dictionary size " << dictionary.getSize() << endl;
				cout << "Done Checking and these are the results:" << endl;
				cout << "Finished in time: " << myTimer.Time() << endl;
				cout << "Finished in Milliseconds Time: " << fixed << setprecision(2) << myTimer.TimeMS()<< endl;
				cout << "There are " << foundWords << " words found in the dictionary" << endl;
				cout << "\t\t" << successfulCompares << " compares. Average: " << successfulCompares / foundWords << endl;
				cout << "There are " << notFoundWords << " words NOT found in the dictionary" << endl;
				cout << "\t\t" << unsuccessfulCompares << " compares. Average: " << fixed << setprecision(3) << 1.0 * unsuccessfulCompares / notFoundWords << endl;
				cout << "There are " << skipped << " words not checked." << endl;
				ofstream outFile("misspelled.txt");      // Creating an output file for misspelled words.
				for (int i = 0; i < misspelled.size(); i++)
				{
					outFile << misspelled[i] << endl;
				}
				outFile.close();
				outFile.clear();

		}
	}
	return 0;
}

string cleanWord(string word)                     // Cleanword function
{
	int size = word.length();
	string cleanWord = "";
	char c;
	for (int i = 0; i < size; i++)
	{
		if (isalnum(word[i]) || word[i] == '\'')    // Using the escape sequence for apostrophe
		{
			c = tolower(word[i]);
			cleanWord = cleanWord + c;
		}
	}
	return cleanWord;
}
