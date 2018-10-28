#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct{
   unsigned int b : 1;
} bit;

typedef struct{
   unsigned int b : 1;
} vector[4];

typedef struct{
   unsigned int b : 1;
} matrix[4][4];

typedef struct{
   unsigned int b : 1;
} cube[4][4][4];

typedef struct{
   unsigned int b : 1; // crea un unsigned int che contiene 1 solo bit (0 o 1);
} fdimension[4][4][4][4]; //assegna sotto nome di fdimension un vettore in 4 dimensioni, contenente 64 vettori di lunghezza 4 (1 nibble);

fdimension text;
fdimension key;

char* getstringfromkeyboard();

void putin(fdimension bits, char *str);

void printbitseq(fdimension bits);

void shiftrows(fdimension bits);
