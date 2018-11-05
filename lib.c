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
          (bits[x][y][(j+1)+(j>>1-j)][i]).b = appo; // uno schifo per l'indice ma non ho trovato di meglio
        }
      }
    }
  }
}

void printbitseq(Fdimension bits){

  int u = 0;

  for(int i=0; i<4; i++) {
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
void shiftbits(Fdimension bits, int i, int j, int x, _Bool cod){

  Bit bit, bitappo;

  if(cod){
    for(int ii=0; ii<x; ii++){
      for(int p=0; p<4; p++){
        if(p==0){
            bitappo.b = text[i][j][x][0].b;
        }
        if(p<3){
            bit.b = text[i][j][x][p+1].b;
            text[i][j][x][p].b = bit.b;
        }else{
            text[i][j][x][p].b = bitappo.b;
        }
      }
    }
  } else {
    for(int ii=0; ii<4-x; ii++){
      for(int p=0; p<4; p++){
        if(p==0){
            bitappo.b = text[i][j][x][0].b;
        }
        if(p<3){
            bit.b = text[i][j][x][p+1].b;
            text[i][j][x][p].b = bit.b;
        }else{
            text[i][j][x][p].b = bitappo.b;
        }
      }
    }
  }

}

void shiftrows(Fdimension bits, int i, int j, _Bool cod){

  Vector vector, vectorappo;

  if(cod){
    for(int ii=0; ii<j; ii++){
      for(int z=0; z<4; z++){
        for(int p=0; p<4; p++){
          if(z==0){
              vectorappo[p].b = text[i][j][0][p].b;
          }
          if(z<3){
              vector[p].b = text[i][j][z+1][p].b;
              text[i][j][z][p].b = vector[p].b;
          }else{
              text[i][j][z][p].b = vectorappo[p].b;
          }
        }
      }
    }
  } else {
    for(int ii=0; ii<4-j; ii++){
      for(int z=0; z<4; z++){
        for(int p=0; p<4; p++){
          if(z==0){
              vectorappo[p].b = text[i][j][0][p].b;
          }
          if(z<3){
              vector[p].b = text[i][j][z+1][p].b;
              text[i][j][z][p].b = vector[p].b;
          }else{
              text[i][j][z][p].b = vectorappo[p].b;
          }
        }
      }
    }
  }
}

void shiftmatrix(Fdimension bits, int i, _Bool cod){

  Matrix matrix, matrixappo;

  if(cod){
    for(int ii=0; ii<i; ii++){
      for(int q=0; q<4; q++){
        for(int z=0; z<4; z++){
          for(int p=0; p<4; p++){
            if(q==0){
                matrixappo[z][p].b = text[i][0][z][p].b;
            }
            if(q<3){
                matrix[z][p].b = text[i][q+1][z][p].b;
                text[i][q][z][p].b = matrix[z][p].b;
            }else{
                text[i][q][z][p].b = matrixappo[z][p].b;
            }
          }
        }
      }
    }
  } else {
    for(int ii=0; ii<4-i; ii++){
      for(int q=0; q<4; q++){
        for(int z=0; z<4; z++){
          for(int p=0; p<4; p++){
            if(q==0){
                matrixappo[z][p].b = text[i][0][z][p].b;
            }
            if(q<3){
                matrix[z][p].b = text[i][q+1][z][p].b;
                text[i][q][z][p].b = matrix[z][p].b;
            }else{
                text[i][q][z][p].b = matrixappo[z][p].b;
            }
          }
        }
      }
    }
  }
}

void shiftcubes(Fdimension bits, int m, _Bool cod){

  Cube cube, cubeappo;

  if(cod){
    for(int ii=0; ii<m; ii++){
      for(int i=0; i<4; i++){
        for(int q=0; q<4; q++){
          for(int z=0; z<4; z++){
            for(int p=0; p<4; p++){
              if(i==0){
                  cubeappo[q][z][p].b = text[0][q][z][p].b;
              }
              if(i<3){
                  cube[q][z][p].b = text[i+1][q][z][p].b;
                  text[i][q][z][p].b = cube[q][z][p].b;
              }else{
                  text[i][q][z][p].b = cubeappo[q][z][p].b;
              }
            }
          }
        }
      }
    }
  } else {
    for(int ii=0; ii<m+1; ii++){
      for(int i=0; i<4; i++){
        for(int q=0; q<4; q++){
          for(int z=0; z<4; z++){
            for(int p=0; p<4; p++){
              if(i==0){
                  cubeappo[q][z][p].b = text[0][q][z][p].b;
              }
              if(i<3){
                  cube[q][z][p].b = text[i+1][q][z][p].b;
                  text[i][q][z][p].b = cube[q][z][p].b;
              }else{
                  text[i][q][z][p].b = cubeappo[q][z][p].b;
              }
            }
          }
        }
      }
    }
  }
}

void vmmoltiplication(Fdimension bits, Matrix matrix, int i, int j, int x){
  Bit a, b, c, d;
  a.b = 0;
  b.b = 0;
  c.b = 0;
  d.b = 0;

  for(int p=0; p<4; p++){
    for(int y=0; y<4; y++){
      if(p==0){
        a.b ^= text[i][j][x][y].b & matrix[p][y].b;
      }
      if(p==1){
        b.b ^= text[i][j][x][y].b & matrix[p][y].b;
      }
      if(p==2){
        c.b ^= text[i][j][x][y].b & matrix[p][y].b;
      }
      if(p==3){
        d.b ^= text[i][j][x][y].b & matrix[p][y].b;
      }
    }
  }

  text[i][j][x][0].b = a.b;
  text[i][j][x][1].b = b.b;
  text[i][j][x][2].b = c.b;
  text[i][j][x][3].b = d.b;
}

void sumnextbit(Fdimension bits, int i, int j, int x, int y){
  text[i][j][x][y].b ^= text[i][j][x][y+1].b;
}

void putout(Fdimension text){ // NON FUNZIONAAAAAA!
  char appo = '0';
  int c=0;
            printf("%c %i\n", appo, c);

  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      for(int z=0; z<4; z++){:
        for(int k=0; k<4; k++){
          appo ^= text[i][j][z][k].b;
          c++;
          printf("%c %i\n", appo, c);
          if(c==8){
            printf("%c",appo);
            c=0;
          }
          appo >>= 1;
        }
      }
    }
  }

}
