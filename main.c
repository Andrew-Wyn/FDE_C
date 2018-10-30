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

  //LINEAR APPL
  linear_appl[0][0].b = 1;
  linear_appl[0][1].b = 0;
  linear_appl[0][2].b = 1;
  linear_appl[0][3].b = 1;
  linear_appl[1][0].b = 0;
  linear_appl[1][1].b = 1;
  linear_appl[1][2].b = 1;
  linear_appl[1][3].b = 0;
  linear_appl[2][0].b = 1;
  linear_appl[2][1].b = 1;
  linear_appl[2][2].b = 0;
  linear_appl[2][3].b = 0;
  linear_appl[3][0].b = 1;
  linear_appl[3][1].b = 0;
  linear_appl[3][2].b = 0;
  linear_appl[3][3].b = 1;
  /*************************/

  //REVERSE LINEAR APPL
  r_linear_appl[0][0].b = 1;
  r_linear_appl[0][1].b = 1;
  r_linear_appl[0][2].b = 1;
  r_linear_appl[0][3].b = 1;
  r_linear_appl[1][0].b = 1;
  r_linear_appl[1][1].b = 1;
  r_linear_appl[1][2].b = 0;
  r_linear_appl[1][3].b = 1;
  r_linear_appl[2][0].b = 1;
  r_linear_appl[2][1].b = 0;
  r_linear_appl[2][2].b = 0;
  r_linear_appl[2][3].b = 1;
  r_linear_appl[3][0].b = 1;
  r_linear_appl[3][1].b = 1;
  r_linear_appl[3][2].b = 1;
  r_linear_appl[3][3].b = 0;
  /*************************/

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

  //printbitseq(text);

  for(int m=0; m<4; m++){
    //SHIFT
    shiftcubes(text, m, true);
    /****************/

    for(int i=0; i<4; i++){
      //SHIFT
      shiftmatrix(text, i, true);
      /****************/
      for(int j=0; j<4; j++){
        //SHIFT
        shiftrows(text, i,j, true);
        /****************/
        for(int x=0; x<4; x++){
          //SHIFT
          shiftbits(text, i,j,x, true);
          /****************/
          for(int y=0; y<4; y++){
            text[i][j][x][y].b ^= key[i][j][x][y].b;

            //sumnext
            if(y<3){
              sumnextbit(text, i, j, x, y);
            }           
            /****************/
          }
          
          //mixrows
          vmmoltiplication(text, linear_appl, i, j, x);
          /****************/
          
          //sumnext
          if(x<3){
              for(int y=0; y<4; y++){
                text[i][j][x][y].b ^= text[i][j][x+1][y].b;
              }
          }
          /****************/
        }

        //sumnext
        if(j<3){
          for(int x=0; x<4; x++){
              for(int y=0; y<4; y++){
                  text[i][j][x][y].b ^= text[i][j+1][x][y].b;
              }
          }
        }
        /****************/
      }

      //sumnext
      if(i<3){
        for(int j=0; j<4; j++){
          for(int x=0; x<4; x++){
              for(int y=0; y<4; y++){
                  text[i][j][x][y].b ^= text[i+1][j][x][y].b;
              }
          }
        }
      }
      /****************/
    }
  }

  printbitseq(text);

  for(int m=0; m<4; m++){

    for(int i=3; i>=0; i--){
      //sumnext
      if(i<3){
        for(int j=3; j>=0; j--){
          for(int x=3; x>=0; x--){
              for(int y=3; y>=0; y--){
               text[i][j][x][y].b ^= text[i+1][j][x][y].b;
              }
          }
        }
      }
      /****************/

      for(int j=3; j>=0; j--){
        //sumnext
        if(j<3){
          for(int x=3; x>=0; x--){
              for(int y=3; y>=0; y--){
                text[i][j][x][y].b ^= text[i][j+1][x][y].b;
              }
          }
        }
        /****************/

        for(int x=3; x>=0; x--){

          //sumnext
          if(x<3){
              for(int y=3; y>=0; y--){
               text[i][j][x][y].b ^= text[i][j][x+1][y].b;
              }
          }
          /****************/

          //mixrows
          vmmoltiplication(text, r_linear_appl, i, j, x);
          /****************/

          for(int y=3; y>=0; y--){

            //sumnext
            if(y<3){
              sumnextbit(text, i, j, x, y);
            }
            /****************/

            text[i][j][x][y].b ^= key[i][j][x][y].b;

          }

          //SHIFT
          shiftbits(text, i,j,x, false);
          /****************/
        }

        //SHIFT
        shiftrows(text, i, j, false);
        /****************/
      }
   
      //SHIFT
      shiftmatrix(text, i, false);
      /****************/
    }
    
    
    //SHIFT
    shiftcubes(text, m, false);
    /****************/
  }

  printbitseq(text);

  return 0;
}
