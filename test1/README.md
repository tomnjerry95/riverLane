# RISC MACHINE #

The enclosing projects contains an implementation of a RISC machine that performs the following instructions
1. LOAD R1,[Address] - Loads a Register with a value or vlaue of a memory location. To give a memory location, enclose the address in "[]".
Eg. *LOAD R1,[1]*
2. STORE R1,[Add] - Stores a Register in a memory location. Provide the memory location enclosed in "[]". Eg. STORE R1,[1] 
3. ADD R1,R2,R3 - Adds the contents of R2,R3 and stores i in R1.
4. SUB R1,R2,R3 - R1 = R2-R3
4. JMP R1,R2,Address - Jumps to mentioned Address if R1 is equal to the value in R2.
4. CMP R1,R2 - Sets a Flag F1 =1 if R1 == R2.
4. HALT - Terminates Instruction execution
4. NOP - Does nothing for one clock cycle

### Registers ###
General Purpose Register - R1,R2,R3\
Address Register A1,A2,A3,A4 - To store an address \
Flag Register F1 - Gets set when CMP is true\
Constant Register T1 - To store constant numbers\

### Code ###
A class has been designed called RISC in the file "RISC.h" and "RISC.cpp" which can be used to emulate the system
The function 

#### Examples ####
The current code in code.txt is a code that finds the first 20 numbers in the fibbonacci sequence and appends them to consequent locations in the program memory

#### Implementing Linked Lists ####
In order to implement linked lists, we need to store the element and the address of the next element in the list in the adjacent memory locations. An Attempt was sstarted in linkedlists.txt, however I was not able to complete it due to time cnstraints.

#### Implementing Binary Encoding ####
It is fairly possible and not that far difficult to iplement a binary encoding for our instruction set. We have around 10 instructions in our system, hence we can decie on 4 bits for the instruction, and 4 bits each for each register, which accounts to upto 16 bits of data for eah line.
Eg. ADD R3,R1,R2 can be denoted as 0x1312 . 0x1 - Add, 0x3-R3, 0x2-R1, 0x1-R1. Due to time constraints I was not able to implement this.

## Building and Running ##

The code has developed in Microsoft Visual Studio 2022 v143. In order to run and build the project, simply open the solution in Visual studio and run the project.
Prior to running the code, provide your assembly code in the format code.txt and save it in the root directory to execute it.

## ADDITIONAL INSTRCTIONS ##

Additional instructions have also been added
1. NCMP - Performs negative comparisons
    eg. NCMP R1,R2 generates F1=1 if R1!=R2
2. NJMP - Performs negative comparisons
    eg. NJMP R1,R2,A1 Jumps to A1 if R1!=R2
3. MUL - Multiplication - eg. MUL R1,R2,R3 Multiples R2,R3 and stores in R1
4. DIV - Division - eg. DIV R1,R2,R3 Divides R2,R3 and stores in R1
