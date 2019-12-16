#include <stdio.h>
#include "dictionary.h"

int main() {
	Dictionary *d1, *d2;
	Double v1,v2;

	d1 = newDictionary();
	d2 = dictionaryFromJson("{\"name\":\"camera\",\"price\":25.8}");

	setNumber(d1,"value",30.5);

	if(getNumber(d1,"value",&v1) && getNumber(d2,"price",&v2) && v1 == v2) {
		printf("iguales\n");
	}
	return 0;
}