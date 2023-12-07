// test1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Each Instruction can 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "RISC.h"
using namespace std;



/*
* Returns length
*/
uint8_t loadCode(string* code)
{
	int i = 0;
	ifstream file("code.txt");
	 if(file.is_open())
    {
        string myArray[15];
       while(!file.eof())
        {
			getline(file, code[i]);
			cout << code[i]<<endl;
			i++;
        }
    }
	 return i;
}


int main()
{
	int memory[100];
	memset(memory, '0', 100*sizeof(int));

	string code[100];
	int length = loadCode(code);
	RISC m1(memory, code, length);
		int i ;
	//for ( i = 0;i < length;i++)
	//{
		m1.simulateMachine();
	//}
	cout << "Memory in RAM is " << endl;
	for ( i = 0;i < 100;i++)
	{
		cout << m1.RAM[i]<<" , ";
	}
	//cout << "Mem"<<memory[5];
	m1.printRegisters();
	return 0;
}
