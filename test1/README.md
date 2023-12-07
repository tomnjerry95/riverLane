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

A class has been designed called RISC in the file "RISC.h" and "RISC.cpp" which can be used to enulate the system
The function 

## Building and Running ##

The code has developed in Microsoft Visual Studio 2022 v143. In order to run and build the project, simply open the solution in Visual studio and run the project.
