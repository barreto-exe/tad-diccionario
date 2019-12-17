#include "dictionary.h"
#include <stdlib.h>

Dictionary *newDictionary(){
   Dictionary *d = (Dictionary *) malloc(sizeof(Dictionary));
   if(!d){
      printf("Error en reserva de memoria. \n");
      exit -1;
   }
   return d;
}

Keynode *newKeynode(){
   Keynode *k = (Keynode *) malloc(sizeof(Keynode));
   if(!k){
      printf("Error en reserva de memoria. \n");
      exit -1;
   }
   return k;}

int tipoDatoCadena(const char *s){
   /*
      Devuelve un identificador, según el tipo de dato que
      represente la cadena.

      [0] Diccionario.
      [1] String.
      [2] Numérico.
      [3] Bool.
      [4] Arreglo.
      [5] ???
   */
   int tipo = 0;
   return tipo;
}

int setNumber(Dictionary *d, const char *key, double value){
   if(!d) return 0;


}


