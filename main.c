#include <stdio.h>
#include "dictionary.h"

void testProfe();

void TestMamaPipe(){
   Dictionary *d;
   Dictionary *d2;
   d = newDictionary();
   d2 = newDictionary();

 //  setNumber(d,"MiPene",30.5);
   setBool(d,"Miculo",false);

   char *test = (char *) malloc(sizeof(char)*20);
   strcpy(test,"Hola");
   setString(d,"Cara",test);

   setNumber(d2,"K1",2.0);
   setBool(d2,"K2",false);

   setDictionary(d,"Diccionario2",d2);

   double resultadoNumber;
   printf("Pudo: %d || ",getNumber(d,"PeneLuis",&resultadoNumber));
   printf("%f\n",resultadoNumber);
   resultadoNumber = 0.0;

   Bool resultadoBool;
   printf("Pudo: %d || ",getBool(d2,"K2",&resultadoBool));
   printf("%s\n",resultadoBool?"false":"true");

   printf("Pudo: %s\n",getString(d,"Cara"));

   Dictionary *d3 = getDictionary(d,"Diccionario2");
   printf("Pudo en D3: %d ||",getNumber(d3,"K1",&resultadoNumber));
   jsonFromDictionary(d);
}

void TestMamaPipeTheComeback(){
   Dictionary *d;
   Dictionary *d2;
   Dictionary *d3;

   d = newDictionary();
   d2 = newDictionary();
   d3 = newDictionary();

   char *array[] = {"Hola","Fea",";D"};
   Bool arrayBool[] = {true,false,false};
   double arrayNumber[] = {1.0,2.0,3.0};

   setString(d,"K1","Resultado");
   setNumberArray(d,"K2",3,arrayNumber);
   setStringArray(d,"K3",3,array);
   setBool(d,"K4",true);

   setNumber(d2,"K5",30.5);
   setBoolArray(d2,"K6",3,arrayBool);
   setString(d2,"K7","Hola");

   setNumber(d3,"K8",40.0);
   setBool(d3,"K9",true);
   setString(d3,"K10","HolaBB");

   Dictionary *arrayDictionary[] = {d3,d2};
   setDictionaryArray(d,"K11",2,arrayDictionary);

   jsonFromDictionary(d);
}
int main(){
   TestMamaPipeTheComeback();
   return 0;
}

void test1()
{
   Dictionary *d;
   Dictionary *d2;
   d = newDictionary();
   d2 = newDictionary();


   setNumber(d,"D1K1",30.5);
   setBool(d,"D1K2",false);

   setNumber(d2,"D2K1",2);
   setBool(d2,"D2K2",true);

   setDictionary(d,"D2",d2);

   double resultadoNumber;
   printf("Pudo: %d || ",getNumber(d,"D2K1",&resultadoNumber));
   printf("%f\n",resultadoNumber);
}

void testProfe()
{
	Dictionary *d1, *d2;
	double v1,v2;

	d1 = newDictionary();
	//d2 = dictionaryFromJson("{\"name\":\"camera\",\"price\":25.8}");

	//setNumber(d1,"value",30.5);

	//if(getNumber(d1,"value",&v1) && getNumber(d2,"price",&v2) && v1 == v2) {
		printf("iguales\n");
	//}
}
