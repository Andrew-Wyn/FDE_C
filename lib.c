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
  //TODO
}
