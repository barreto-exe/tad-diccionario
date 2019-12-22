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
   int tiposAux = p->tipo;
   char KeyAux[30];
   strcpy(KeyAux,p->name);
   if(strcmp(key,p->name) == 0 && p->tipo == type)
      return p;

   if(p->D != NULL){
      Dictionary *DiccionarioHijo = p->D;
      Keynode *PrimerNodoDeDiccionarioHijo = p->D->kfirst;

      //Keynode a = *(p->D->kfirst), b = *p; //Esto es para probar

      return getGeneral(p->D,key,p->D->kfirst,type,p->D->kfirst->cantElem);
   }

   if(p->next == NULL)
      return NULL;
   return getGeneral(dictionary,key,p->next,type,p->next->cantElem);
}

Keynode *buscaGeneral(Dictionary *d, const char *k, Keynode *keyAnterior)
//La búsqueda NO es recursiva en los diccionarios hijo del diccionario.
{
   Keynode *kaux = d->kfirst;

   keyAnterior = NULL;

   if(strcmp(kaux->name,k) == 0)
   {
      return kaux;
   }

   while(kaux->next)
   {
      if(strcmp(kaux->next->name,k) == 0)
      {
         keyAnterior = kaux;
         return kaux->next;
      }
      kaux = kaux->next;
   }

   return NULL;
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
      char AuxString[30];
      strcpy(AuxString,*p->sa);
      return *p->sa;

   }


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

void freeDictionary(Dictionary *d)
{
   Keynode *kaux = d->kfirst;

   //Hago free de todas las llaves.
   while(kaux)
   {
      Keynode *borrado = kaux;
      kaux = kaux->next;
      freeKey(borrado);
   }

   //Hago free del diccionario
   free(d);
}

void freeKey(Keynode *k)
{
   //Primero hago free del valor.
   switch(k->tipo)
   {
      //Dictionary
      case 1:
         freeDictionary(k->D);
      break;

      //Cadena
      case 2:
         for(int i=0; i<k->cantElem; i++)
         {
            free(k->sa[i]);
         }
         free(k->sa);
      break;

      //Numerico
      case 3:
         free(k->d);
      break;

      //Bool
      case 4:
         free(k->b);
      break;
   }

   //Luego free del nombre
   free(k->name);

   //Por ultimo free del nodo
   free(k);
}

int removeElement(Dictionary *d, const char *key)
{
   Keynode *anterior = NULL, *borrado = NULL;

   if(borrado = buscaGeneral(d,key,anterior))
   {
      if(anterior)
      {
         anterior->next = borrado->next;
      }
      else
      {
         d->kfirst = borrado->next;
      }

      freeKey(borrado);
      return 1;
   }

   return 0;
}
