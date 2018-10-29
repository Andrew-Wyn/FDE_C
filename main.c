#include "lib.c"

int main(){

  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      for(int x=0; x<4; x++){
        for(int y=0; y<4; y++){
          text[i][j][x][y].b = 0;
        }
      }
    }
  }

  printf("%d\n",sizeof(Fdimension));

  char *str;

  printf("Inserisci testo:\n");
  fflush(stdout);
  str = getstringfromkeyboard();
  putin(text, str);
  printf("Inserisci chiave:\n");
  fflush(stdout);
  str = getstringfromkeyboard();
  putin(key, str);
  
  Vector vector, vectorappo;
  Matrix matrix, matrixappo;
  Cube cube, cubeappo;

  for(int m=0; m<1; m++){
    for(int ii=0; ii<0; ii++){
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
    for(int i=0; i<4; i++){
      for(int ii=0; ii<0; ii++){
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
      for(int j=0; j<4; j++){

        //SHIFT
        for(int ii=0; ii<0; ii++){
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
         /****************/

        for(int x=0; x<4; x++){

          //SHIFT
          shifbits(text, i, j, x);
          /****************/

          for(int y=0; y<4; y++){
            text[i][j][x][y].b ^= key[i][j][x][y].b;
          }
        }
      }
    }
  }

Fdimension a;
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      for(int x=0; x<4; x++){
        for(int y=0; y<4; y++){
          a[i][j][x][y].b = 0;
        }
      }
    }
  }
  putin(a, str);
  
  Matrix b;
  b[0][0].b = 1;
  b[0][1].b = 1;
  b[0][2].b = 1;
  b[0][3].b = 1;
  b[1][0].b = 1;
  b[1][1].b = 1;
  b[1][2].b = 1;
  b[1][3].b = 1;
  b[2][0].b = 1;
  b[2][1].b = 1;
  b[2][2].b = 1;
  b[2][3].b = 1;
  b[3][0].b = 1;
  b[3][1].b = 1;
  b[3][2].b = 1;
  b[3][3].b = 1;

  vmmoltiplication(a, b, 0, 0, 0);

  printbitseq(a);

  return 0;
}
