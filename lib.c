#include "lib.h"


char* getstringfromkeyboard(){ //la funzione prende le stringhe inserite da tastiera (massimo 32 caratteri e le inserisce all'interno del puntatore *str)
    char *str = (char *)malloc(1);
     
    int chars = 0;
    _Bool boo = true;

    do {
        if(chars > 32){
            *(str + chars) = '\0'; // equivalente alla dicitura str[chars];
            boo=false;
            break;
        }
        else {
          char a = 0;
          a = getchar();
          if(chars == 0){
              strcpy(str, &a); //si immettono gli 8 bit del carattere in str
          }
          if(a =='\n'){
            while(chars <= 32){
              *(str + chars) = NULL; //genera warning!! dk why
              chars++;
              str = (char *)realloc(str, ((sizeof(char)*chars)+1)); //si ingrandisce lo spazio in memoria di str
            }
              *(str + chars) = '\0';
              boo=false;
              break;
          } else {
              *(str + chars) = a;
              chars++;
              str = (char *)realloc(str, ((sizeof(char)*chars)+1));
          }
        }
    }while(boo);
    return str;
}

void putin(Fdimension bits, char *str){
  int u = 0;
  for(int x=0; x<4; x++){
    for(int y=0; y<4; y++){
      for(int j=0; j<2; j++){
        char a = str[u];
        u++;
        for(int i=0; i<4; i++){
          int appo = a;
          appo >>= i;
          (bits[x][y][j*2][i]).b = appo;
        }
        a >>= 4;
        for(int i=0; i<4; i++){
          int appo = a;
          appo >>= i;
          (bits[x][y][(j+1)+(j>>2-j)][i]).b = appo; // uno schifo per l'indice ma non ho trovato di meglio
        }
      }
    }
  }
}

void printbitseq(Fdimension bits){

  int u = 0;

  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      for(int x=0; x<4; x++){
        for(int y=0; y<4; y++){
          u++;
          printf("%d ----------> %d\n", bits[i][j][x][y].b, u);
          if(u%8 == 0){
            printf("------------------\n");
          }
        }
      }
    }
  }
}

//try to implement little function
void shifbits(Fdimension bits, int i, int j, int x){

  Bit bit, bitappo;

  for(int ii=0; ii<x; ii++){
    for(int p=0; p<4; p++){
      if(p==0){
          bitappo.b = bits[i][j][x][0].b;
      }
      if(p<3){
          bit.b = bits[i][j][x][p+1].b;
          bits[i][j][x][p].b = bit.b;
      }else{
          bits[i][j][x][p].b = bitappo.b;
      }
    }
  }
}

void vmmoltiplication(Fdimension bits, Matrix matrix, int i, int j, int x){
  Bit a, b, c, d;

  for(int p=0; p<4; p++){
    for(int y=0; y<4; y++){
      if(p==0){
        a.b ^= bits[i][j][x][y].b & matrix[p][y].b;
      }
      if(p==1){
        b.b ^= bits[i][j][x][y].b & matrix[p][y].b;
      }
      if(p==2){
        c.b ^= bits[i][j][x][y].b & matrix[p][y].b;
      }
      if(p==3){
        d.b ^= bits[i][j][x][y].b & matrix[p][y].b; 
      }
    }
  } 

  bits[i][j][x][0].b = a.b;
  bits[i][j][x][1].b = b.b;
  bits[i][j][x][2].b = c.b;
  bits[i][j][x][3].b = d.b;

}