// test1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Each Instruction can 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "RISC.h"
using namespace std;

/**
 * Function to Remove Trailing Spaces in a string.
 *
 * \param str Pointer to the string to be corrected
 */
void removeTrailingTabsAndSpaces(string& str) {
	str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), str.end());
}
/**
 * API to remove comments from the Line. Comments begin with #. The lines that are comments in the file are not loaded into the code memory
 *
 * \param line
 */
void RemoveComments(string& line) {
	size_t commentPos = line.find('#');
	if (commentPos != string::npos) {
		line.erase(commentPos); //Erase the rest of it
	}
}
/*
* API to load the code from a txt file "code.txt"
* Returns length
*/
uint8_t LoadCode(string* code)
{
	int i = 0;
	ifstream file("code.txt");
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, code[i]);
			RemoveComments(code[i]); //API 
			removeTrailingTabsAndSpaces(code[i]);
			cout << code[i] << endl;
			if (code[i].length() > 0)
				i++;
		}
	}
	return i;
}


int main()
{
	int memory[100];
	memset(memory, '0', 100 * sizeof(int));

	string code[100];
	int length = LoadCode(code);
	RISC m1(memory, code, length); //
	int i;
	m1.SimulateMachine();
	cout << "Memory in RAM is " << endl;
	m1.PrintMemory();
	cout << endl;
	cout << "Registers: ";
	m1.printRegisters();
	return 0;
}
