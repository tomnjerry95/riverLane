#pragma once
#include <iostream>

using namespace std;

enum instructions {
	LOAD = 0x00,
	STORE,
	ADD,
	SUB,
	NOP,
	JMP,
	CMP,
	HALT,
	DEBUG,
	MUL,
	DIV,
	NCMP,
	NJMP
};
const int RAM_SIZE = 100;
/**
 * Class for implementing the RISC machine.
 */
class RISC
{
private:
	int R1 =0; //Operand
	int R2 = 0;
	int R3 = 0;
	int T0 = 0; //Argument(numbers)
	int T1 =0 ;
	int F1 = 0; //Flag
	int A1, A2, A3, A4;
	int PC = 0;
	int RAM[100];
	string FLASH[100];
	//int operationNum?;
public:
	RISC(int* x, string* y, int length);
	int GetOperationFromString(string operationString);
	int ParseInstruction(string textToParse);
	void GetOperands(string opString, int**);
	void incrementPC() { PC++; };
	void resetPC() { PC = 0; };
	void ExecuteInstruction(string instruction, string op1String, string op2String, string op3String);
	void SimulateMachine();
	void printRegisters();
	void PrintMemory();
};