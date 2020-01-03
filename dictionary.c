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

void removerCaracteres(char *cadena, char *caracteres) {
  int indiceCadena = 0, indiceCadenaLimpia = 0;
  int deberiaAgregarCaracter = 1;
  // Recorrer cadena carácter por carácter
  while (cadena[indiceCadena]) {
    // Primero suponemos que la letra sí debe permanecer
    deberiaAgregarCaracter = 1;
    int indiceCaracteres = 0;
    // Recorrer los caracteres prohibidos
    while (caracteres[indiceCaracteres]) {
      // Y si la letra actual es uno de los caracteres, ya no se agrega
      if (cadena[indiceCadena] == caracteres[indiceCaracteres]) {
        deberiaAgregarCaracter = 0;
      }
      indiceCaracteres++;
    }
    // Dependiendo de la variable de arriba, la letra se agrega a la "nueva
    // cadena"
    if (deberiaAgregarCaracter) {
      cadena[indiceCadenaLimpia] = cadena[indiceCadena];
      indiceCadenaLimpia++;
    }
    indiceCadena++;
  }
  // Al final se agrega el carácter NULL para terminar la cadena
  cadena[indiceCadenaLimpia] = 0;
}

Keynode *getGeneral(const Dictionary *dictionary, const char *key,Keynode *p,int type,int amount){
   if(strcmp(key,p->name) == 0 && p->tipo == type)
      return p;
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

   int tipo = 4; //Si no entra en ninguna condicion, es bool.
   switch(s[0])
   {
      case '{': tipo = 1; break;
      case '"': tipo = 2; break;
   }
   if(s[0]>='0' && s[0]<= '9') tipo=3;

   return tipo;
}

char *all2Array(const char *json)
//Copia el json y mete a todos los valores en arreglos, incluso si es un sólo elemento.
{
   char *result = (char *) malloc(sizeof(char)*strlen(json)+30);
   strcpy(result,json);

   char copia[1024];
   char *aux = strstr(result,":");

   while(aux)
   {
      aux++;
      if(*aux != '[' && *aux != '{')
      {
         strcpy(copia,aux);
         *aux = '[';
         aux++;
         strcpy(aux,copia);

         aux = strstr(aux,",") ? strstr(aux,",") : strstr(aux,"}");
         strcpy(copia,aux);
         *aux = ']';
         aux++;
         strcpy(aux,copia);
      }
      else if(*aux == '[')
      {
         //aux = strstr(aux,"]"); //<--- ERROR!!!, No siempre sucede que el siguiente corchete es el indicado.
         int desbalance = 1;
         while(desbalance)
         {
            aux++;
            if(*aux == ']')
               desbalance--;
            if(*aux == '[')
               desbalance++;
         }
      }
      else if(*aux == '{')
      {
         //Agrego corchete abre
         strcpy(copia,aux);
         *aux = '[';
         aux++;
         strcpy(aux,copia);

         char *iniDicc, *finalDicc;
         iniDicc = finalDicc = aux;
         int desbalance = 1;

         while(desbalance)
         {
            finalDicc++;
            if(*finalDicc == '}')
               desbalance--;
            if(*finalDicc == '{')
               desbalance++;
         }
         finalDicc++; //Apunto al espacio despues de llave de cierre correspondiente.

         //Agrego corchete cierra
         strcpy(copia,finalDicc);
         *finalDicc = ']';
         finalDicc++;
         strcpy(finalDicc,copia);
         finalDicc--; //Esto queda apuntando a corchete cierra.

         char *jsonAux = (char *) malloc(sizeof(char)*(finalDicc-iniDicc)+1);
         strncpy(jsonAux,iniDicc,finalDicc-iniDicc);

         char *jsonAuxArray = all2Array(jsonAux);

         char finalCad[1024]; //Guardo todo lo que estas despues de llave cierre.
         strcpy(finalCad,finalDicc);

         strcpy(iniDicc,jsonAuxArray);   //Pego el json convertido.
         iniDicc+= strlen(jsonAuxArray); //Me muevo al final de lo que pegué.
         strcpy(iniDicc,finalCad);       //Lo dejo como estaba

         aux = iniDicc;

         free(jsonAux);
         free(jsonAuxArray);
      }
      aux=strstr(aux,":");
   }

   return result;
}

Dictionary *dictionaryFromJson(const char *json)
{
   char *j = all2Array(json);
   //printf("%s \n\n\n",json);
   //printf("%s \n",j);
   //return NULL;

   Dictionary *result = newDictionary();
   Keynode *actual = result->kfirst = newKeynode();
   int hayHijos = 1;

   char *finalValue = j-1; //Hago esto para dar inicio al bucle

   do
   {
      //Guardo el key
      char *inicioKey = finalValue+3, *finalKey = strstr(inicioKey,"\"");
      char *llave = (char *) malloc(sizeof(char)*(finalKey-inicioKey)+1);
      strncpy(llave,inicioKey,finalKey-inicioKey);

      //Guardo el arreglo value (después de corchete que abre)
      char *iniValue = finalKey+3;
      finalValue = iniValue;

      //Busco el final del value (apuntando a corchete que cierra)
      if(*iniValue == '{')
      {
         int desbalance = 1;

         while(desbalance)
         {
            finalValue++;
            if(*finalValue == ']')
               desbalance--;
            if(*finalValue == '[')
               desbalance++;
         }
      }
      else
      {
         finalValue = strstr(iniValue,"],") ? strstr(iniValue,"],") : strstr(iniValue,"]}");
      }

      char *value = (char *) malloc(sizeof(char)*(finalValue-iniValue)+1);
      strncpy(value,iniValue,finalValue-iniValue); //Los value se guardan sin corchetes.

      //Asigno el key en el knode
      actual->name = llave;

      //Colocando y contando valores
      int cantElem = 0, hayValores = 1;
      char *centinelaIni, *centinelaFin, *unvalor;
      centinelaFin = centinelaIni = value;
      switch(tipoDatoCadena(value))
      {
         case 1:
            actual->tipo = 1;
            Dictionary *Daux = actual->D, *resultHijo;
            do
            {
               int desbalance = 1;
               centinelaFin = centinelaIni;

               //Con este bucle centinelaFin apunta al '}' correspondiente.
               while(desbalance)
               {
                  centinelaFin++;
                  if(*centinelaFin == '{')
                     desbalance++;
                  if(*centinelaFin == '}')
                     desbalance--;
               }

               unvalor = (char *) malloc(sizeof(char)*(centinelaFin-centinelaIni)+2); //+2 por la llave de cierre y caracter nulo.
               strncpy(unvalor,centinelaIni,centinelaFin-centinelaIni+1);

               actual->D = (Dictionary *) realloc(actual->D, sizeof(Dictionary)*(cantElem+1));

               resultHijo = dictionaryFromJson(unvalor);
               Daux = actual->D;
               Daux += cantElem;
               *Daux = *resultHijo;


               free(resultHijo);
               free(unvalor);
               centinelaIni = strstr(centinelaFin,"{");
               cantElem++;
            }while(centinelaIni);
         break;

         case 2:
            actual->tipo = 2;
            do
            {
               if(strstr(centinelaIni,","))
               {
                  centinelaFin =  strstr(centinelaIni,",");
               }
               else
               {
                  centinelaFin = centinelaIni+strlen(centinelaIni);
                  hayValores = 0;
               }

               unvalor = (char *) malloc(sizeof(char)*(centinelaFin-centinelaIni)+1);
               strncpy(unvalor,centinelaIni,centinelaFin-centinelaIni);
               removerCaracteres(unvalor,"\"");

               actual->sa = (char **) realloc(actual->sa, sizeof(char *)*(cantElem+1));
               actual->sa[cantElem] = unvalor;

               centinelaIni = centinelaFin+1;
               cantElem++;
            }while(hayValores);
         break;

         default: //Caso 3 o 4.
            do
            {
               if(strstr(centinelaIni,","))
               {
                  centinelaFin =  strstr(centinelaIni,",");
               }
               else
               {
                  centinelaFin = centinelaIni+strlen(centinelaIni);
                  hayValores = 0;
               }

               unvalor = (char *) malloc(sizeof(char)*(centinelaFin-centinelaIni)+1);
               strncpy(unvalor,centinelaIni,centinelaFin-centinelaIni);

               if(tipoDatoCadena(unvalor) == 3)
               {
                  actual->tipo = 3;
                  actual->d = (double *) realloc(actual->d, sizeof(double)*cantElem+1);
                  actual->d[cantElem] = strtod(unvalor,NULL);
               }
               if(tipoDatoCadena(unvalor) == 4)
               {
                  actual->tipo = 4;
                  actual->b = (Bool *) realloc(actual->b, sizeof(Bool)*cantElem+1);
                  if(!strcmp(unvalor,"true")  || !strcmp(unvalor,"True"))
                     actual->b[cantElem] = true;
                  if(!strcmp(unvalor,"false") || !strcmp(unvalor,"False"))
                     actual->b[cantElem] = false;
               }

               free(unvalor);
               centinelaIni = centinelaFin+1;
               cantElem++;
            }while(hayValores);
         break;
      }

      actual->cantElem = cantElem;
      //Determinando próximo hijo diccionario
      if(strstr(finalValue,","))
      {
         actual->next = newKeynode();
         actual = actual->next;
      }
      else
      {
         hayHijos = 0;
      }

      free(value);
   }while(hayHijos);

   free(j); //Libero json auxiliar
   return result;
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
