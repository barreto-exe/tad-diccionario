#include <stdio.h>
#include "dictionary.h"

void testProfe();

void TestMamaPipe(){
   Dictionary *d;
   d = newDictionary();
   setNumber(d,"MiPene",30.5);
   setBool(d,"Miculo",false);
   double resultado;
   printf(" Pudo: %d\n",getNumber(d,"MiPene",&resultado));
   printf("%lf",resultado);
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
