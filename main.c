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

   d = newDictionary();
   d2 = newDictionary();

   char *array[] = {"Hola","Fea",";D"};
   Bool arrayBool[] = {true,false,false};
   double arrayNumber[] = {1.0,2.0,3.0};
   setNumberArray(d,"K3",3,arrayNumber);
   setStringArray(d,"K1",3,array);
   setBoolArray(d,"K2",3,arrayBool);
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
