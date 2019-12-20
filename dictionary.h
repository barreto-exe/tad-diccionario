#include<string.h>

typedef enum {true, false} Bool;

typedef struct key{
   char *name;

   int tipo, cantElem;     //Tipo de dato del Keynode, Cantidad de elementos (arreglo dinámico).
   double *d;              //Tipo Numérico.
   Bool *b;                //Tipo Booleano.
   char *s;                //Tipo Cadena.
   char **sa;               //Tipo arreglo de Cadenas.
   struct dictionary *D;   //Tipo Diccionario.
   struct key *next;
} Keynode;

typedef struct dictionary {
	char *nombre;
	struct key *kfirst;
} Dictionary;

/*
   Tipos:
   0 -> BOOL
   1 -> Entero
   2 -> char
   3 -> array (No se si tener un tipo array sea necesario, casi seguro que no)
   4 -> Dictionary
*/
//Aqui pondre funciones que en caso de ser necesarion moveremos a un .h auxiliar

Keynode *getGeneral(const Dictionary *dictionary, const char *key,Keynode *p,int type,int amount){
   if(amount == -1){
      if(strcmp(key,p->name) == 0 && p->tipo == type)
         return p;
      if(p->next != NULL)
         return getGeneral(dictionary,key,p->next,type,p->next->cantElem);
   }else{
      for(int i=0; i<amount && p != NULL ; i++){ //No estoy muy seguro como se maneja esa parte de los arreglos dinamicos
         if(strcmp(key,p->name) == 0 && p->tipo == type)
            return p;
         getGeneral(dictionary,key,p->next,type,p->next->cantElem);
      }
   }
   return NULL;
}


//Termina aqui


// Creates a new empty dictionary
Dictionary *newDictionary();

// Saves the number associated to the corresponding key in result.
// Returns 1 if it was able to get it otherwise returns 0
int getNumber(const Dictionary *dictionary, const char *key, double *result){
   if(dictionary == NULL)
      return 0;
   Keynode *Aux = dictionary->k;
   Keynode *p = getGeneral(dictionary,key,Aux,1,dictionary->k->cantElem);
   if(p == NULL)
      return 0;
   else{
      result = p->d;
      return 1;
   }
}

// Saves the boolean associated to the corresponding key in result.
// Returns 1 if it was able to get it otherwise returns 0
int getBool(const Dictionary *dictionary, const char *key, Bool *result){
   if(dictionary == NULL)
      return 0;
   Keynode *Aux = dictionary->k;
   Keynode *p = getGeneral(dictionary,key,Aux,0,dictionary->k->cantElem);
   if(p == NULL)
      return 0;
   else{
      result = p->b;
      return 1;
   }
}
// Returns the string associated to the corresponding key, otherwise returns NULL
char *getString(const Dictionary *dictionary, const char *key){
   if(dictionary == NULL)
      return 0;
   Keynode *Aux = dictionary->k;
   Keynode *p = getGeneral(dictionary,key,Aux,2,dictionary->k->cantElem);
   if(p == NULL)
      return NULL;
   else
      return p->s;

}

// Returns the dictionary associated to the corresponding key, otherwise returns NULL
Dictionary *getDictionary(const Dictionary *dictionary, const char *key);

// Returns the numeric array associated to the corresponding key, otherwise returns NULL
double *getNumberArray(const Dictionary *dictionary, const char *key, int *sizeResult);

// Returns the boolean array associated to the corresponding key, otherwise returns NULL
Bool *getBoolArray(const Dictionary *dictionary, const char *key, int *sizeResult);

// Returns the array of strings associated to the corresponding key, otherwise returns NULL
char **getStringArray(const Dictionary *dictionary, const char *key, int *sizeResult);

// Returns the array of dictionaries associated to the corresponding key, otherwise returns NULL
Dictionary **getDictionaryArray(const Dictionary *dictionary, const char *key, int *sizeResult);

// Removes the given key. Returns 1 if it was able to do it otherwise returns 0
int removeElement(Dictionary *dictionary, const char *key);

// Sets a number for the given key, if the key does not exists it creates it else it overrides the previous value.
// Returns 1 if it was able to do it otherwise returns 0
int setNumber(Dictionary *dictionary, const char *key, double value);

// Sets a boolean for the given key, if the key does not exists it creates it else it overrides the previous value.
// Returns 1 if it was able to do it otherwise returns 0
int setBool(Dictionary *dictionary, const char *key, Bool value);

// Sets a string for the given key, if the key does not exists it creates it else it overrides the previous value.
// Returns 1 if it was able to do it otherwise returns 0
int setString(Dictionary *dictionary, const char *key, const char *value);

// Sets a dictionary for the given key, if the key does not exists it creates it else it overrides the previous value.
// Returns 1 if it was able to do it otherwise returns 0
int setDictionary(Dictionary *dictionary, const char *key, Dictionary *value);

// Sets a numeric array for the given key, if the key does not exists it creates it else it overrides the previous value.
// Returns 1 if it was able to do it otherwise returns 0
int setNumberArray(Dictionary *dictionary, const char *key, int size, double value[size]);

// Sets a boolean array for the given key, if the key does not exists it creates it else it overrides the previous value.
// Returns 1 if it was able to do it otherwise returns 0
int setBoolArray(Dictionary *dictionary, const char *key, int size, Bool value[size]);

// Sets an array of strings for the given key, if the key does not exists it creates it else it overrides the previous value.
// Returns 1 if it was able to do it otherwise returns 0
int setStringArray(Dictionary *dictionary, const char *key, int size, char *value[size]);

// Sets an array of dictionaries for the given key, if the key does not exists it creates it else it overrides the previous value.
// Returns 1 if it was able to do it otherwise returns 0
int setDictionaryArray(Dictionary *dictionary, const char *key, int size, Dictionary *value[size]);

// Returns a new dictionary created from its json representation. If it can't parse the json returns NULL
Dictionary *dictionaryFromJson(const char *json);

// Returns the json representation string for the given dictionary. If it can't do it returns NULL
char *jsonFromDictionary(const Dictionary *dictionary);

// Releases the memory of the given dictionary
void freeDictionary(Dictionary *dictionary);

