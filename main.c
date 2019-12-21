#include <stdio.h>
#include "dictionary.h"

void testProfe();

void TestMamaPipe(){
   Dictionary *d;
   Dictionary *d2;
   d = newDictionary();
   d2 = newDictionary();


   setNumber(d,"MiPene",30.5);
   setBool(d,"Miculo",false);

   char *test = (char *) malloc(sizeof(char)*20);
   strcpy(test,"Hola");
   setString(d,"Cara",test);

   setNumber(d2,"PeneLuis",2.0);
   setBool(d2,"CuloLuis",false);

   setDictionary(d,"Diccionario2",d2);

   double resultadoNumber;
   printf("Pudo: %d || ",getNumber(d,"MiPene",&resultadoNumber));
   printf("%f\n",resultadoNumber);

   Bool resultadoBool;
   printf("Pudo: %d || ",getBool(d,"Miculo",&resultadoBool));
   printf("%s\n",resultadoBool?"false":"true");  //Como hago que esto imprima false o true

   printf("Pudo: %s\n",getString(d,"Cara"));
}

int main(){
   TestMamaPipe();
   return 0;

}


void test1()
{

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
