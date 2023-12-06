// test1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Each Instruction can 
#include <iostream>
#include <string>
using namespace std;
int memory[10] = {1,2,3,4,0,0,0,0,0,0};
enum instructions {
	LOAD = 0x00,
	STORE,
	ADD,
	SUB,
	NOP,
	JMP,
	CMP
};

enum operands {
	R1 = 1,
	R2,
	R3,
	OP_ERROR,
};

class RISC
{
public:
	int R1 = 1; //Operand
	int R2 = 2;
	int R3 = 3;
	int T0 = 4; //Argument(numbers)
	int T1 = 0;
	int programCounter = 0;
	//int operationNum?;
public:
	int getOperationFromString(char* operationString);
	int parseInstruction(char* textToParse);
	void getOperands(char* opString, int **);
	void incrementPC() { programCounter++; };
	void resetPC() { programCounter = 0; };
	void executeInstruction(char* instruction, char *op1, char *op2, char *op3);
};

//Let us define some registers that can be used

int RISC::getOperationFromString(char* operationString)
{
	int _operationNum = 0;
	if (strcmp(operationString, "LOAD") == 0)
	{
		_operationNum = LOAD;
	}
	else if (strcmp(operationString, "STORE") == 0)
	{
		_operationNum = STORE;
	}
	else if (strcmp(operationString, "JMP") == 0)
	{
		_operationNum = JMP;
	}
	else if (strcmp(operationString, "ADD") == 0)
	{
		_operationNum = ADD;
	}
	else if (strcmp(operationString, "SUB") == 0)
	{
		_operationNum = SUB;
	}
	else if (strcmp(operationString, "NOP") == 0)
	{
		_operationNum = NOP;
	}
	else if (strcmp(operationString, "CMP") == 0)
	{
		_operationNum = CMP;
	}
	return _operationNum;
}
/*
* This function returns the instruction operands, operator
* eg. LOAD R1,10
*     ADD R1,T0,T1 //R1 = T0+T1
* Returns Enum for the instruction
*/
int RISC::parseInstruction(char* textToParse)
{
	int i, commaIndex;
	int j = 0;
	char operationString[10], operandString[3][10];
	//memset(operand, '0',30);
	//memset(operationString, '0',10);

	int spaceDelimiter = 0;
	char* currentChar = 0;
	int commaDelimiters[3] = { 0,0,0 }; //Let us assume max 3 commas
	int operationNum = 0;
	//char operands[3][3];
	int currentIndex = 0;
	int subStart = 0, subEnd = 0;
	for (i = 0, commaIndex = 0;i<20;i++)
	{
		currentChar = (textToParse + i);
		switch (*currentChar)
		{
		case ' ':
			spaceDelimiter = i;
			subStart = 0;
			subEnd = spaceDelimiter;
			strncpy_s(operationString, textToParse, subEnd - subStart);
			subStart = spaceDelimiter + 1; //For next iteration
			break;

		case ',':
			commaDelimiters[commaIndex++] = i;
			subEnd = i;
			strncpy_s(operandString[j++], textToParse + subStart, subEnd - subStart);
			subStart = subEnd + 1;
			break;
		case '\0':
			subEnd = i;
			strncpy_s(operandString[j], textToParse + subStart, subEnd - subStart);
			i = 20;
			break;
		default:
			break;
		}
	}
	cout << "Operation: " << operationString << "Operand 1:" << operandString[0] << ',' << operandString[1] << ',' << operandString[2] << endl;
	executeInstruction(operationString, operandString[0], operandString[1], operandString[2]);
	return operationNum;
}
void RISC::getOperands(char* opString, int** operandPtr)
{
	if (strcmp(opString, "R1") == 0)
	{
		*operandPtr = &R1;
	}
	else if (strcmp(opString, "R2") == 0)
	{
		*operandPtr = &R2;
	}
	else if (strcmp(opString, "R3") == 0)
	{
		*operandPtr = &R3;
	}
	else
	{
		//Operand will be an integer
		try
		{
			T1 = stoi(opString);
			*operandPtr = &T1;

		}
		catch (...) //Could be some unknown integer error
		{
			T1 = 0;
			*operandPtr = &T1;
		}
	}

	//return operand;

}

void RISC::executeInstruction(char* instruction, char *op1String, char *op2String, char *op3String)
{
	int* op1 = &R1, * op2 = &R1, * op3 = &R1;
	switch (getOperationFromString(instruction))
	{
		case LOAD:
		//For load operation, eg. LOAD R1,10 , we need to load a value from memory location 10 ro 
			getOperands(op1String, &op1);
			getOperands(op2String, &op2);
			*op1 = memory[* op2];
			break;
		case ADD:
			//For load operation, eg. LOAD R1,10 , we need to load a value from memory location 10 ro 
			getOperands(op1String, &op1);
			getOperands(op2String, &op2);
			getOperands(op3String, &op3);
			*op1 = *op2 + *op3;
			break;
		case STORE:
			//For load operation, eg. LOAD R1,10 , we need to load a value from memory location 10 ro 
			getOperands(op1String, &op1);
			getOperands(op2String, &op2);
			memory[*op2] = *op1;
			break;
	}
}









int main()
{
	RISC m1;
	int operation = 0;
	cout << "Hello World!\n";
	char line[100];
	strcpy_s(line, "LOAD R1,1");
	operation = m1.parseInstruction(line);
	strcpy_s(line,"LOAD R2,2");
	operation = m1.parseInstruction(line);
	strcpy_s(line, "LOAD R3,3");
	operation = m1.parseInstruction(line);
	strcpy_s(line, "ADD R1,R2,R3");
	operation = m1.parseInstruction(line);
	strcpy_s(line, "STORE R3,5");
	operation = m1.parseInstruction(line);
	//cout << "Operation Number is: " << operation;
	cout << "R1 " << m1.R1 << " R2 " << m1.R2 << " R3 " << m1.R3<<endl;
	cout << "Mem"<<memory[5];
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
