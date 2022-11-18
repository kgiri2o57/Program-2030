// Program03.cpp
// Kamal Giri
//Program3
//Fall 2022

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iomanip>
#include <string>

#include "timer.h"
#include "myHashClass.cpp"


using namespace::std;
using std::string;

string cleanWord(string unclean);

int main()
{
	//Class Decleration
	Timer myTimer;
	myHashClass<string> hash1;

	//Variables Decleration and Initilization
	int missed = 0;
	int successC = 0;
	int unsuccessC = 0;
	int matched = 0;
	int unmatched = 0;


	//Working with Dictionary
	ifstream myDict;
	myDict.open("dict.txt");
	if (!myDict)
	{
		cerr << "Can't open your Dictionary File" << endl;
		myDict.close();
		myDict.clear();
	}
	else {
		string ditem;
		while (myDict >> ditem)
		{
			hash1.insert(cleanWord(ditem));
		}
	}

	myDict.close();
	myDict.clear();
	myTimer.Start();


	//Working with Book
	ifstream myBook;
	myBook.open("book.txt");
	if (!myBook)
	{
		cerr << "Can't Open Your Open!!" << endl;
		myBook.close();
		myBook.clear();
	}

	string bitem;
	while (myBook >> bitem)
	{
		string clean = cleanWord(bitem);
		if (isalpha(clean[0]))
		{



			int compares = 0;
			if (hash1.find(clean, compares))
			{
				matched++;
				successC = successC + compares;
			}
			else
			{
				unmatched++;
				unsuccessC = unsuccessC + compares;
			}
		}
		else if (!clean.empty())
		{
			missed++;
		}
	}
	myTimer.Stop();
	myBook.close();
	myBook.clear();

	ifstream book("book.txt");
	ofstream oFile;
	oFile.open("mispelled.txt");
	string word;

	while (book >> word)
	{
		string unclean = cleanWord(word);
		if (isalpha(unclean[0]))
		{
			int compares = 0;
			if (!hash1.find(unclean, compares))
			{
				oFile << unclean << endl;
			}
		}
	}

	oFile.close();
	oFile.clear();



	//Printing the Output
	cout << "dictionary size " << hash1.getSize() << endl;
	cout << "Done Checking and these are the results:" << endl;
	cout << "finished in time: " << myTimer.Time() << endl;
	cout << "finished in Milliseconds Time: " << fixed << setprecision(2) << myTimer.TimeMS() << endl;
	cout << "There are " << matched << " words found in the dictionary" << endl;
	cout << "\t\t" << successC << " compares. Average: " << successC / matched << endl;
	cout << "There are " << unmatched << " words NOT found in the dictionary" << endl;
	cout << "\t\t" << unsuccessC << " compares. Average: " << fixed << setprecision(3) << 1.0 * unsuccessC / unmatched << endl;
	cout << "There are " << missed << " words not checked." << endl;




return 0;

}

string cleanWord(string unclean)
{
	int size = unclean.length();
	string cleanWord = "";
	char c;
	for (int i = 0; i < size; i++)
	{
		if (isalpha(unclean[i]) || unclean[i] == '\'')  // Using the escape sequence for apostrophe
		{
			c = tolower(unclean[i]);
			cleanWord = cleanWord + c;
		}
	}
	return cleanWord;
}