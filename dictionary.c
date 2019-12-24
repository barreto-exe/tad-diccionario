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
   k->b = k->d = k->sa = k->D = NULL;

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
   if(strcmp(key,p->name) == 0 && p->tipo == type)
      return p;
   if(p->next == NULL)
      return NULL;
   return getGeneral(dictionary,key,p->next,type,p->next->cantElem);
}

int getNumber(const Dictionary *dictionary, const char *key, double *result){
   if(dictionary == NULL)
      return 0;
   Keynode *Aux = dictionary->kfirst;
   Keynode *p = getGeneral(dictionary,key,Aux,3,dictionary->kfirst->cantElem);
   if(p == NULL)
      return 0;
   else{
      *result = *p->d;
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
      *result = *p->b;
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
   else{
      char *result = (char *) malloc(sizeof(char)*strlen(*p->sa)+1);
      strcpy(result,*p->sa);
      return result;
   }
}

Dictionary *getDictionary(const Dictionary *dictionary, const char *key){
   if(dictionary == NULL)
      return NULL;
   Keynode *Aux = dictionary->kfirst;
   Keynode *p = getGeneral(dictionary,key,Aux,1,dictionary->kfirst->cantElem);
   if(p == NULL)
      return NULL;
   else{
      Dictionary *result = (Dictionary *) malloc(sizeof(Dictionary));
      *result = *p->D;

      return result;
   }

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
      for(int i=0;i<p->cantElem;i++)   //Por que con el cantElemn-1 no funciona bien?
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
      int size = p->cantElem;
      for(int i=0;i<p->cantElem;i++)
         result[i] = p->b[i];
      *sizeResult = p->cantElem;
      return result;
   }
}

char **getStringArray(const Dictionary *dictionary, const char *key, int *sizeResult){
   if(dictionary == NULL)
      return NULL;
   Keynode *Aux = dictionary->kfirst;
   Keynode *p = getGeneral(dictionary,key,Aux,2,dictionary->kfirst->cantElem);
   if(p == NULL)
      return NULL;
   else{
      char **result = (char **) malloc(sizeof(char *)*p->cantElem);
      for(int i=0;i<p->cantElem;i++){
         result[i] = (char *) malloc(sizeof(char)*strlen(p->sa[i])+1);
         strcpy(result[i],p->sa[i]);//Se esta recorriendo bien?
      }
      *sizeResult = p->cantElem;
      return result;
   }
}

Dictionary **getDictionaryArray(const Dictionary *dictionary, const char *key, int *sizeResult){
   if(dictionary == NULL)
      return NULL;
   Keynode *Aux = dictionary->kfirst;
   Keynode *p = getGeneral(dictionary,key,Aux,1,dictionary->kfirst->cantElem);
   if(p == NULL)
      return NULL;
   else{
      Dictionary **result = (Dictionary **) malloc(sizeof(Dictionary *)*p->cantElem);
      for(int i=0; i<p->cantElem ; i++){
         result = (Dictionary *) malloc(sizeof(Dictionary));
         *result[i] = p->D[i];
      }
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

   newk->cantElem = size;
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

      //Inicializo diccionario en la posicion actual del arreglo.
      newValue[i] = newDictionary();

      Dictionary *newValueAux = newValue[i], *valueAux = value[i];

      //Hago copia de primer Keynode de value en newValue
      Keynode *recorreValue = valueAux->kfirst;

      newValueAux->kfirst  = newKeynode();

      //Todo lo que está dentro de value del user estara dentro del first del new
      Keynode *primerNodoNew = newValueAux->kfirst;
      *primerNodoNew =  *recorreValue; //No considero que recorreValue (dicionario) sea nulo, el profe dijo que eso no pasaría xd.

      //Keynode a = *primerNodoNew, b = *recorreValue; //Esto es para probar

     //Hago copia de todos los Keynodes en newValue
      Keynode *recorreNew = newValueAux->kfirst;

      while(recorreValue->next)
      {
         //Keynode a = *recorreValue; //Esto es para probar

         recorreValue = recorreValue->next;
         recorreNew->next = (Keynode *) malloc(sizeof(Keynode));
         *recorreNew->next = *recorreValue;
         recorreNew = recorreNew->next;
      }
   }

   newk->D = *newValue;
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
   //Dictionary a = *value; //Esto es para probar
   //Keynode k = *value->kfirst->next;

   Dictionary *val[] = {value};
   setDictionaryArray(d,key,1,val);
}

void PutOnCommas(char *Result,int Remaining, int Actual){
   if(Remaining == Actual+1)
      return;
   strcat(Result,",");
   return;
}

void DictionaryAJson(char *Result,Keynode *p){
   if(p == NULL)
      return;
   int type = p->tipo;
   strcat(Result,"\"");
   strcat(Result,p->name);
   strcat(Result,"\":");
   if(p->cantElem >1)
      strcat(Result,"[");
   if(type == 1){
      for(int i=0; i<p->cantElem; i++){
         strcat(Result,"{");
         DictionaryAJson(Result,p->D->kfirst);  //Como hago para que recorra el arreglo de dictionary
         strcat(Result,"}");
         PutOnCommas(Result,p->cantElem,i);
      }
   }else if(type == 2){
      for(int i=0; i<p->cantElem; i++){
         strcat(Result,"\"");
         strcat(Result,p->sa[i]);
         strcat(Result,"\"");
         PutOnCommas(Result,p->cantElem,i);
      }
   }else if(type == 3){
      for(int i=0; i<p->cantElem; i++){
         char Elem[200];
         gcvt(p->d[i],10,Elem);
         strcat(Result,Elem);
         PutOnCommas(Result,p->cantElem,i);
      }
   }else if(type == 4){
      for(int i=0 ; i<p->cantElem ; i++){
         int size = p->cantElem;
         if(p->b[i])
            strcat(Result,"True");
         else
            strcat(Result,"False");
         PutOnCommas(Result,p->cantElem,i);
      }
   }
   if(p->cantElem >1)
      strcat(Result,"]");
   if(p->next != NULL)
      strcat(Result,",");
   DictionaryAJson(Result,p->next);
}

char *jsonFromDictionary(const Dictionary *dictionary){
   char *Result = (char *) malloc(sizeof(char)*1024);
   strcat(Result,"{");
   DictionaryAJson(Result,dictionary->kfirst);
   strcat(Result,"}");
   printf("%s",Result);
}
