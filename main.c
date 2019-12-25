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

   setNumber(d2,"K1",2.0);
   setBool(d2,"K2",false);

   setDictionary(d,"Diccionario2",d2);

   double resultadoNumber;
   printf("Pudo: %d || ",getNumber(d,"PeneLuis",&resultadoNumber));
   printf("%f\n",resultadoNumber);

   Bool resultadoBool;
   printf("Pudo: %d || ",getBool(d,"Miculo",&resultadoBool));
   printf("%s\n",resultadoBool?"false":"true");  //Como hago que esto imprima false o true

   printf("Pudo: %s\n",getString(d,"Cara"));
}

int main(){
   test2();
   return 0;

}

void test1()
{
   Dictionary *d;
   Dictionary *d2;
   d = newDictionary();
   d2 = newDictionary();


   setNumber(d,"D1K1",30.5);

   Bool ar[] = {true,false,true};
   setBoolArray(d,"D1K2",3,ar);

   //printf("Pudo: %d || ",);
   //printf("%s\n",resultadoNumber?"true":"false");

   printf("Pudo eliminar: %d \n",removeElement(d,"D1K2"));


   freeDictionary(d);
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


void test2()
{
   //dictionaryFromJson("{\"nombre\":\"La tasca\",\"distancia\":30.5,\"abierto\":false,\"gerente\":{\"nombre\":\"Juan\",\"sueldo\":1500.0},\"comentarios\":[\"servicio de primera\",\"perfecto\"]}");

   Dictionary *a = dictionaryFromJson("{\"Numero\":[30,20,40,33,33.3],\"Bool\":[false,true,false,true]}");

   Keynode a1 = *a->kfirst, a2 = *a->kfirst->next;

   Bool Test;

   for(int i= 0; i<a2.cantElem; i++)
   {
      Test = a2.b[i];
   }
}
