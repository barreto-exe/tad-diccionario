#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

Dictionary *newDictionary()
{
   Dictionary *d = (Dictionary *) malloc(sizeof(Dictionary));
   if(!d)
   {
      printf("Error en reserva de memoria. \n");
      exit -1;
   }

   d->kfirst = NULL;
   return d;
}

Keynode *newKeynode()
{
   Keynode *k = (Keynode *) malloc(sizeof(Keynode));

   if(!k)
   {
      printf("Error en reserva de memoria. \n");
      exit -1;
   }

   k->cantElem = k->tipo = 0;
   k->name = k->next = NULL;

   return k;
}

int tipoDatoCadena(const char *s)
{
   /*
      Devuelve un identificador, según el tipo de dato que
      represente la cadena.

      [1] Diccionario.
      [2] String.
      [3] Numérico.
      [4] Bool.
   */
   int tipo = 0;
   return tipo;
}

Keynode *getGeneral(const Dictionary *dictionary, const char *key,Keynode *p,int type,int amount){
   int tiposAux = p->tipo;
   char KeyAux[30];
   strcpy(KeyAux,p->name);
   if(strcmp(key,p->name) == 0 && p->tipo == type)
      return p;
   if(p->next == NULL)
      return NULL;
   getGeneral(dictionary,key,p->next,type,p->next->cantElem);
}


int getNumber(const Dictionary *dictionary, const char *key, double *result){
   if(dictionary == NULL)
      return 0;
   Keynode *Aux = dictionary->kfirst;
   Keynode *p = getGeneral(dictionary,key,Aux,3,dictionary->kfirst->cantElem);
   if(p == NULL)
      return 0;
   else{
      *result = *p->d; //Listo
      return 1;
   }
}

int getBool(const Dictionary *dictionary, const char *key, Bool *result){
   if(dictionary == NULL)
      return 0;
   Keynode *Aux = dictionary->kfirst;
   Keynode *p = getGeneral(dictionary,key,Aux,4,dictionary->kfirst->cantElem);
   if(p == NULL)
      return 0;
   else{
      result = p->b;
      return 1;
   }
}

char *getString(const Dictionary *dictionary, const char *key){
   if(dictionary == NULL)
      return NULL;
   Keynode *Aux = dictionary->kfirst;
   Keynode *p = getGeneral(dictionary,key,Aux,2,dictionary->kfirst->cantElem);
   if(p == NULL)
      return NULL;
   else
      return p->s;

}

Dictionary *getDictionary(const Dictionary *dictionary, const char *key){
   if(dictionary == NULL)
      return NULL;
   Keynode *Aux = dictionary->kfirst;
   Keynode *p = getGeneral(dictionary,key,Aux,1,dictionary->kfirst->cantElem);
   if(p == NULL)
      return NULL;
   else
      return p->D;

}

double *getNumberArray(const Dictionary *dictionary, const char *key, int *sizeResult){
   if(dictionary == NULL)
      return NULL;
   Keynode *Aux = dictionary->kfirst;
   Keynode *p = getGeneral(dictionary,key,Aux,3,dictionary->kfirst->cantElem);
   if(p == NULL)
      return NULL;
   else{
      double *result = (double *) malloc(sizeof(double)*p->cantElem);
      for(int i=0;i<p->cantElem-1;i++)
         result[i] = p->d[i];
      *sizeResult = p->cantElem;
      return result;
   }
}

Bool *getBoolArray(const Dictionary *dictionary, const char *key, int *sizeResult){
   if(dictionary == NULL)
      return NULL;
   Keynode *Aux = dictionary->kfirst;
   Keynode *p = getGeneral(dictionary,key,Aux,4,dictionary->kfirst->cantElem);
   if(p == NULL)
      return NULL;
   else{
      Bool *result = (Bool *) malloc(sizeof(Bool)*p->cantElem);
      for(int i=0;i<p->cantElem-1;i++)
         result[i] = p->d[i];
      *sizeResult = p->cantElem;
      return result;
   }
}

int setNumberArray(Dictionary *d, const char *key, int size, double value[size])
{
   if(!d) return 0;

   Keynode *newk = (Keynode *) malloc(sizeof(Keynode));

   //Reservo espacio para el nombre, para evitar apuntar al const key.
   char *name = (char *) malloc(sizeof(char)*strlen(key)+1);
   strcpy(name,key);
   newk->name = name;

   //Lo mismo aplica para el valor.
   double *newValue = (double *) malloc(sizeof(double)*size);
   for(int i = 0; i<size; i++)
   {
      newValue[i] = value[i];
   }
   newk->d = newValue;

   newk->cantElem = size;
   newk->tipo = 3;
   newk->next = NULL;

   if(!d->kfirst)
   {
      d->kfirst = newk;
   }
   else
   {
      Keynode *aux = d->kfirst;
      while(aux->next) aux = aux->next; //Me posiciono en el último Keynode.
      aux->next = newk;
   }

   return 1;
}

int setNumber(Dictionary *d, const char *key, double value)
{
   double val[] = {value};
   return setNumberArray(d,key,1,val);
}

int setBoolArray(Dictionary *d, const char *key, int size, Bool value[size])
{
   if(!d) return 0;

   Keynode *newk = (Keynode *) malloc(sizeof(Keynode));

   //Reservo espacio para el nombre, para evitar apuntar al const key.
   char *name = (char *) malloc(sizeof(char)*strlen(key)+1);
   strcpy(name,key);
   newk->name = name;

   //Lo mismo aplica para el valor.
   Bool *newValue = (Bool *) malloc(sizeof(Bool)*size);
   for(int i = 0; i<size; i++)
   {
      newValue[i] = value[i];
   }
   newk->b = newValue;

   newk->cantElem = 1;
   newk->tipo = 4;
   newk->next = NULL;


   if(!d->kfirst)
   {
      d->kfirst = newk;
   }
   else
   {
      Keynode *aux = d->kfirst;
      while(aux->next) aux = aux->next; //Me posiciono en el último Keynode.
      aux->next = newk;
   }

   return 1;
}

int setBool(Dictionary *d, const char *key, Bool value)
{
   Bool val[] = {value};
   setBoolArray(d,key,1,val);
}

int setStringArray(Dictionary *d, const char *key, int size, char *value[size])
{
   if(!d) return 0;

   Keynode *newk = (Keynode *) malloc(sizeof(Keynode));

   //Reservo espacio para el nombre, para evitar apuntar al const key.
   char *name = (char *) malloc(sizeof(char)*strlen(key)+1);
   strcpy(name,key);
   newk->name = name;

   //Lo mismo aplica para el valor.
   char **newValue = (char **) malloc(sizeof(char *)*size);
   for(int i=0; i<size; i++)
   {
      newValue[i] = (char *) malloc(sizeof(char)*strlen(value[i])+1);
      strcpy(newValue[i],value[i]);
   }

   newk->sa = newValue;

   newk->cantElem = size;
   newk->tipo = 2;
   newk->next = NULL;

   if(!d->kfirst)
   {
      d->kfirst = newk;
   }
   else
   {
      Keynode *aux = d->kfirst;
      while(aux->next) aux = aux->next; //Me posiciono en el último Keynode.
      aux->next = newk;
   }

   return 1;
}

int setString(Dictionary *d, const char *key, const char *value)
{
   char *val[] = {value};
   setStringArray(d,key,1,val);
}

int setDictionaryArray(Dictionary *d, const char *key, int size, Dictionary *value[size])
//Coloqué muchos comentarios en esta función porque es más o menos confusa.
{
   if(!d) return 0;

   Keynode *newk = (Keynode *) malloc(sizeof(Keynode));

   //Reservo espacio para el nombre, para evitar apuntar al const key.
   char *name = (char *) malloc(sizeof(char)*strlen(key)+1);
   strcpy(name,key);
   newk->name = name;


   //Reservo espacio para la estructura que será hija de Dictionary d.
   Dictionary **newValue = (Dictionary **) malloc(sizeof(Dictionary)*size);


   for(int i=0; i<size;i++)
   {
      /* NO LE PARES BOLA A ESTO, LO BORRARÉ LUEGO

         //Las cosas del nombre no hacen falta, porque los diccionarios no necesitan nombres.
         //Reservo espacio para el nombre de la estrucutra
         newValueAux->nombre = (char *) malloc((sizeof(char)*strlen(valueAux->nombre))+1);

         //Copio el nombre de la estructura
         strcpy(newValueAux->nombre,valueAux->nombre);
      */


      Dictionary *newValueAux = newValue[i], *valueAux = value[i];

      //Inicializo diccionario en la posicion actual del arreglo.
      newValueAux = newDictionary();

      //Hago copia de primer Keynode de value en newValue
      Keynode *recorreValue = valueAux->kfirst;
      newValueAux->kfirst  = (Keynode *) malloc(sizeof(Keynode));

      //Todo lo que está dentro de value del user estara dentro del first del new
      *newValueAux->kfirst =  *recorreValue; //No considero que recorreValue (dicionario) sea nulo, el profe dijo que eso no pasaría xd.

     //Hago copia de todos los Keynodes en newValue
      Keynode *recorreNew = newValueAux->kfirst;

      while(recorreValue->next)
      {
         recorreValue = recorreValue->next;
         recorreNew->next = (Keynode *) malloc(sizeof(Keynode));
         *recorreNew->next = *recorreValue;
         recorreNew = recorreNew->next;
      }
   }

   newk->D = newValue;
   newk->cantElem = size;
   newk->tipo = 1;
   newk->next = NULL;

   if(!d->kfirst)
   {
      d->kfirst = newk;
   }
   else
   {
      Keynode *aux = d->kfirst;
      while(aux->next) aux = aux->next; //Me posiciono en el último Keynode.
      aux->next = newk;
   }

   return 1;
}

int setDictionary(Dictionary *d, const char *key, Dictionary *value)
{
   Dictionary *val[] = {value};
   setDictionaryArray(d,key,1,val);
}
