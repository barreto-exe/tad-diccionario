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
  // setString(d,"Cara","Lista Para Semen");

   setNumber(d2,"PeneLuis",2.0);
   setBool(d2,"CuloLuis",true);

   setDictionary(d,"Diccionario2",d2);

   double resultadoNumber;
   printf(" Pudo: %d\n",getNumber(d,"MiPene",&resultadoNumber));
   printf("%lf\n",resultadoNumber);
   Bool resultadoBool;
   printf(" Pudo: %d\n",getBool(d,"MiPene",&resultadoBool)); //Si pongo un key que no coincide
   printf("%s\n",resultadoBool);
   printf(" Pudo: %s\n",getString(d,"Cara"));
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
