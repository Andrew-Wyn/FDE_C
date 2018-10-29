#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct{
   unsigned int b : 1;
} Bit;

typedef struct{
   unsigned int b : 1;
} Vector[4];

typedef struct{
   unsigned int b : 1;
} Matrix[4][4];

typedef struct{
   unsigned int b : 1;
} Cube[4][4][4];

typedef struct{
   unsigned int b : 1; // crea un unsigned int che contiene 1 solo bit (0 o 1);
} Fdimension[4][4][4][4]; //assegna sotto nome di fdimension un vettore in 4 dimensioni, contenente 64 vettori di lunghezza 4 (1 nibble);

Fdimension text;
Fdimension key;

char* getstringfromkeyboard();

void putin(Fdimension bits, char *str);

void printbitseq(Fdimension bits);

void shifbits(Fdimension bits, int i, int j, int x);

void shiftrows(Fdimension bits);

void shiftmatrix(Fdimension bits);

void shiftcubes(Fdimension bits);

void vmmoltiplication(Fdimension bits, Matrix matrix, int i, int j, int x);
