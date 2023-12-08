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
	for (int i = 0;i < RAM_SIZE;i++)
		RAM[i] = 0;
	for (int i = 0;i < codeSize;i++)
	{
		FLASH[i] = _flash[i];
	}
}
/**
 * Function to find the operation from the string
 *
 * \param operationString String of the operation
 * \return
 */
int RISC::GetOperationFromString(string operationString)
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
	else if (operationString.compare("MUL") == 0)
	{
		_operationNum = MUL;
	}
	else if (operationString.compare("DIV") == 0)
	{
		_operationNum = DIV;
	}
	else if (operationString.compare("NCMP") == 0)
	{
		_operationNum = DIV;
	}
	else if (operationString.compare("NJMP") == 0)
	{
		_operationNum = DIV;
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
int RISC::ParseInstruction(string textToParse)
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

	ExecuteInstruction(operationString, operandString[0], operandString[1], operandString[2]);
	return operationNum;
}
/**
 * Get the operand from the String.
 *
 * \param opString String of operand
 * \param operandPtr	Returns a pointer that points to the Specific register in the machine
 */
void RISC::GetOperands(string opString, int** operandPtr)
{
	int isMemLocation = 0;
	int* memLocation;
	if ((opString.front() == '[') && (opString.back() == ']')) //Mem locations are enclosed with []
	{
		//Is Memory Location
		isMemLocation = true;
		opString = (opString.substr(1, opString.size() - 2));
	}

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
	//{
	//	//is Address
	//	//int memLocation = stoi(opString.substr(1, opString.size() - 2));
	//	//T1 = stoi(opString);
	//	//*operandPtr = &RAM[memLocation];
	//	getOperands(opString.substr(1, opString.size() - 2), operandPtr);
	//}
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
	if (isMemLocation)
	{
		int test = 0;
		test = 1;
		*operandPtr = &RAM[**operandPtr];
	}
	//return operand;

}

/**
 * Executes the instructions provided in the arguments.
 *
 * \param instruction The operation as a string
 * \param op1String	Operand 1 as a string
 * \param op2String	Operand 2 as a string
 * \param op3String	Operand 3 as a string
 */
void RISC::ExecuteInstruction(string instruction, string op1String, string op2String, string op3String)
{
	int* op1 = &R1, * op2 = &R1, * op3 = &R1;
	switch (GetOperationFromString(instruction))
	{
	case LOAD:
		//For load operation, eg. LOAD R1,10 
		GetOperands(op1String, &op1);
		GetOperands(op2String, &op2);
		*op1 = *op2;
		//cout << "Operation: LOAD";
		PC++;
		break;
	case ADD:
		//For Add operation. Eg. ADD R1,1 or ADD R1,R2,R3 =>R1 = R2+R3
		GetOperands(op1String, &op1);
		GetOperands(op2String, &op2);
		GetOperands(op3String, &op3);
		*op1 = *op2 + *op3;
		PC++;
		break;
	case SUB:
		//For SUbtraction operation. Eg. SUB R1,R2,R3 => R1 = R2-R3
		GetOperands(op1String, &op1);
		GetOperands(op2String, &op2);
		GetOperands(op3String, &op3);
		*op1 = *op2 - *op3;
		PC++;
		break;
	case MUL:
		//For SUbtraction operation. Eg. SUB R1,R2,R3 => R1 = R2-R3
		GetOperands(op1String, &op1);
		GetOperands(op2String, &op2);
		GetOperands(op3String, &op3);
		*op1 = *op2 * *op3;
		PC++;
		break;
	case DIV:
		//For SUbtraction operation. Eg. SUB R1,R2,R3 => R1 = R2-R3
		GetOperands(op1String, &op1);
		GetOperands(op2String, &op2);
		GetOperands(op3String, &op3);
		*op1 = *op2 / *op3;
		PC++;
		break;
	case STORE:
		//For load operation, eg. LOAD R1,10 , we need to load a value from memory location 10 ro 
		GetOperands(op1String, &op1);
		GetOperands(op2String, &op2);
		*op2 = *op1;
		PC++;
		break;
	case JMP:
		GetOperands(op1String, &op1);
		GetOperands(op2String, &op2);
		GetOperands(op3String, &op3);
		if (*op1 == *op2)
		{
			PC = *op3 - 1;
		}
		else
			PC++;
		break;
	case NJMP:
		GetOperands(op1String, &op1);
		GetOperands(op2String, &op2);
		GetOperands(op3String, &op3);
		if (*op1 != *op2)
		{
			PC = *op3 - 1;
		}
		else
			PC++;
		break;
	case HALT:
		PC = 10000;
		break;
	case CMP:
		GetOperands(op1String, &op1);
		GetOperands(op2String, &op2);
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
	case NCMP:
		GetOperands(op1String, &op1);
		GetOperands(op2String, &op2);
		if (*op1 != *op2)
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
		GetOperands(op1String, &op1);
		cout << "Value is:" << *op1 << endl;
		PC++;
		break;
	case NOP:
		PC++;
		break;
	default:
		break;

	}
}
/**
 * The main siimulation code that runs the machine.
 *
 */
void RISC::SimulateMachine()
{
	while (PC != 10000)
		ParseInstruction(FLASH[PC]);
}
void RISC::printRegisters()
{
	cout << "R1: " << R1 << " R2: " << R2 << " R3: " << R3 << " F1: " << F1 << endl;

}
/**
 * API To Print memory in the RAM.
 *
 */
void RISC::PrintMemory()
{
	for (int i = 0;i < RAM_SIZE;i++)
	{
		cout << RAM[i] << " ";
	}
}
