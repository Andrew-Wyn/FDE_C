#include "lib.c"

int main(){
  fdimension text;
  fdimension key;

  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      for(int x=0; x<4; x++){
        for(int y=0; y<4; y++){
          text[i][j][x][y].b = 0;
        }
      }
    }
  }

  printf("%d\n",sizeof(fdimension));

  char *str;

  printf("Inserisci testo:\n");
  fflush(stdout);
  str = getstringfromkeyboard();
  putin(text, str);
  printf("Inserisci chiave:\n");
  fflush(stdout);
  str = getstringfromkeyboard();
  putin(key, str);

  bit bit, bitappo;
  vector vector, vectorappo;
  matrix matrix, matrixappo;
  cube cube, cubeappo;

  for(int m=0; m<4; m++){
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
    for(int i=0; i<4; i++){
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
      for(int j=0; j<4; j++){

        //SHIFT
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
         /****************/

        for(int x=0; x<4; x++){

          //SHIFT
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
          /****************/

          for(int y=0; y<4; y++){
            text[i][j][x][y].b ^= key[i][j][x][y].b;
          }
        }
      }
    }
  }


  printbitseq(text);

  return 0;
}
