#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "RISC.h"
using namespace std;


RISC::RISC(int* _ram, string* _flash, int codeSize)
{
	PC = 0;
	//memcpy(RAM, _ram, 10 * sizeof(int));
	for (int i = 0;i < 100;i++)
		RAM[i] = 0;
	for (int i = 0;i < codeSize;i++)
	{
		FLASH[i] = _flash[i];
	}
}
int RISC::getOperationFromString(string operationString)
{
	int _operationNum = 0;
	if (operationString.compare("LOAD") == 0)//(operationString, "LOAD") == 0)
	{
		_operationNum = LOAD;
	}
	else if (operationString.compare("STORE") == 0)
	{
		_operationNum = STORE;
	}
	else if (operationString.compare("JMP") == 0)
	{
		_operationNum = JMP;
	}
	else if (operationString.compare("ADD") == 0)
	{
		_operationNum = ADD;
	}
	else if (operationString.compare("SUB") == 0)
	{
		_operationNum = SUB;
	}
	else if (operationString.compare("NOP") == 0)
	{
		_operationNum = NOP;
	}
	else if (operationString.compare("CMP") == 0)
	{
		_operationNum = CMP;
	}
	else if (operationString.compare("HALT") == 0)
	{
		_operationNum = HALT;
	}
	else if (operationString.compare("DEBUG") == 0)
	{
		_operationNum = DEBUG;
	}
	else
	{
		_operationNum = NOP;
	}
	return _operationNum;
}
/*
* This function returns the instruction operands, operator
* eg. LOAD R1,10
*     ADD R1,T0,T1 //R1 = T0+T1
* Returns Enum for the instruction
*/
int RISC::parseInstruction(string textToParse)
{
	int i = 0, commaIndex;
	int j = 0;
	string operationString, operandString[3];
	//memset(operand, '0',30);
	//memset(operationString, '0',10);

	int spaceDelimiter = 0;
	char	 currentChar = 0;
	int commaDelimiters[3] = { 0,0,0 }; //Let us assume max 3 commas
	int operationNum = 0;
	//char operands[3][3];
	int currentIndex = 0;
	int subStart = 0, subEnd = 0;
	istringstream iss(textToParse);
	getline(iss, operationString, ' ');
	while (!iss.eof())
	{
		getline(iss, operandString[i++], ',');
	}

	cout << "Operation: " << operationString << "Operand 1:" << operandString[0] << ',' << operandString[1] << ',' << operandString[2] << endl;
	executeInstruction(operationString, operandString[0], operandString[1], operandString[2]);
	return operationNum;
}
void RISC::getOperands(string opString, int** operandPtr)
{
	if (opString.compare("R1") == 0)
	{
		*operandPtr = &R1;
	}
	else if (opString.compare("R2") == 0)
	{
		*operandPtr = &R2;
	}
	else if (opString.compare("R3") == 0)
	{
		*operandPtr = &R3;
	}
	else if (opString.compare("T1") == 0)
	{
		*operandPtr = &T1;
	}
	//else if (opString.compare("T2") == 0)
	//{
	//	*operandPtr = &T2;
	//}
	else if (opString.compare("F1") == 0)
	{
		*operandPtr = &F1;
	}
	else if (opString.compare("A1") == 0)
	{
		*operandPtr = &A1;
	}
	else if (opString.compare("A2") == 0)
	{
		*operandPtr = &A2;
	}
	else if (opString.compare("A3") == 0)
	{
		*operandPtr = &A3;
	}
	else if (opString.compare("A4") == 0)
	{
		*operandPtr = &A4;
	}
	else if ((opString.front() == '[') && (opString.back() == ']'))
	{
		//int memLocation = stoi(opString.substr(1, opString.size() - 2));
		//T1 = stoi(opString);
		//*operandPtr = &RAM[memLocation];
		getOperands(opString.substr(1, opString.size() - 2), operandPtr);

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

void RISC::executeInstruction(string instruction, string op1String, string op2String, string op3String)
{
	int* op1 = &R1, * op2 = &R1, * op3 = &R1;
	switch (getOperationFromString(instruction))
	{
	case LOAD:
		//For load operation, eg. LOAD R1,10 , we need to load a value from memory location 10 ro 
		getOperands(op1String, &op1);
		getOperands(op2String, &op2);
		*op1 = *op2;
		PC++;
		break;
	case ADD:
		//For load operation, eg. LOAD R1,10 , we need to load a value from memory location 10 ro 
		getOperands(op1String, &op1);
		getOperands(op2String, &op2);
		getOperands(op3String, &op3);
		*op1 = *op2 + *op3;
		PC++;
		break;
	case SUB:
		//For load operation, eg. LOAD R1,10 , we need to load a value from memory location 10 ro 
		getOperands(op1String, &op1);
		getOperands(op2String, &op2);
		getOperands(op3String, &op3);
		*op1 = *op2 - *op3;
		PC++;
		break;
	case STORE:
		//For load operation, eg. LOAD R1,10 , we need to load a value from memory location 10 ro 
		getOperands(op1String, &op1);
		getOperands(op2String, &op2);
		RAM[*op2] = *op1;
		PC++;
		break;
	case JMP:
		getOperands(op1String, &op1);
		getOperands(op2String, &op2);
		getOperands(op3String, &op3);
		if (*op1 == *op2)
		{
			PC = *op3;
		}
		else
			PC++;
		break;
	case HALT:
		PC = 10000;
		break;
	case CMP:
		getOperands(op1String, &op1);
		getOperands(op2String, &op2);
		if (*op1 == *op2)
		{
			F1 = 1; //Set Flag
		} //This needs to be cleared if F1 is used again
		else		
		{
			F1 = 0; //Set Flag
		} //This needs to be cleared if F1 is used again
		PC++;
		break;
	case DEBUG:
		getOperands(op1String, &op1);
		cout << "Value is:"<< * op1<<endl;
		PC++;
		break;
	default:
		break;

	}
}
void RISC::simulateMachine()
{
	while(PC!= 10000)
		parseInstruction(FLASH[PC]);
}
void RISC::printRegisters()
{
	cout << "R1: " << R1 << " R2: " << R2 << " R3: "<<R3<<" F1: " << F1<<endl;

}