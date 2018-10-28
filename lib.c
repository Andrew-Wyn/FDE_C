#include "lib.h"


char* getstringfromkeyboard(){ //la funzione prende le stringhe inserite da tastiera (massimo 32 caratteri e le inserisce all'interno del puntatore *str)
    char *str = (char *)malloc(1);
      /*malloc():

  La funzione malloc viene comunemente utilizzata soprattutto per "conquistare"
  una funzione di memoria. Viene definita con l'istruzione:

      char *malloc(int number_of_bytes)

  Questa funzione ritorna un puntatore a carattere che corrisponde al
  punto di inizio in memoria della porzione riservata di dimensione
  "number_of_bytes". Se la memoria richiesta non puo' essere allocata, ritorna
  un puntatore nullo.

  Cosi':

      char *cp;
      cp = malloc(100);

  tenta di riservare 100 bytes ed assegna l'indirizzo di inizio a "cp".

  Se si vuole avere un puntatore ad un altro tipo di dato, si deve utilizzare
  la coercizione. Inoltre solitamente viene utilizzata la funzione sizeof()
  per specificare il numero di bytes:

      int *ip;
      ip = (int *) malloc(100*sizeof(int));

  Il comando (int *) simboleggia la coercizione ad un pointer integer. La
  coercizione per correggere il tipo dei puntatori e' molto importante per
    garantire che i puntatori aritmetici vengano rappresentati correttamente.

  E' buona norma utilizzare sizeof anche nel caso in cui si sia gia' a
  conoscenza della dimensione reale necessaria; questo garantisce codici
  portabili (device independent).

  "sizeof" puo' essere usata per trovare la dimensione di un qualsiasi tipo
  di dato, variabile o struttura; e' possibile farlo semplicemente passando
  uno di questi come argomento alla funzione.
  Cosi':

      int i;
      struct COORD {float x,y,z};
      typedef struct COORD PT;

      sizeof(int), sizeof(i), sizeof(struct COORD) e sizeof(PT)

  sono tutti accettabili.

  Nell'esempio che segue possiamo utilizzare il collegamento tra pointer e
  array per trattare la memoria riservata come un array,  per poter cioe'
  fare cose come:

      ip[0] = 100;

  oppure:

      for(i=0;i<100;++i) scanf("%d",ip++);*/

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

void putin(fdimension bits, char *str){
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
          (bits[x][y][(j+1)+(j*2-j)][i]).b = appo; // uno schifo per l'indice ma non ho trovato di meglio
        }
      }
    }
  }
}

void printbitseq(fdimension bits){

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
void shiftrows(fdimension bits){
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
}
