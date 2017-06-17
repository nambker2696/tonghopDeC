#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 20

#include "symbol_table.h"
#include "string.h"

int getmenu();
Entry makePhone(void *name, void *phone);
int comparePhone(void *key1, void *key2);

void main()
{
	SymbolTable book = createSymbolTable(makePhone, comparePhone);

	addEntry("ZinZin", "01699636338", &book);
	addEntry("Linh", "0969741168", &book);
	addEntry("Doggy", "6969696969", &book);

	char name[25];

	printf("Name want to find > "); scanf("%s", name);
	Entry *found = getEntry(name, book);
	if (found == NULL)
	{
		printf("Not found\n");	
	}else{
		printf("Phone number of %s is %s\n",(char*)found->key, (char*)found->value);
	}

	dropSymbolTable(&book);
}

Entry makePhone(void *name, void *phone)
{
	Entry res;
	res.key = strdup((char*)name);
	res.value = strdup((char*)phone);
	// memcpy(res.value, phone, sizeof(long));
	return res;
}

int comparePhone(void *key1, void *key2)
{
	return strcmp((char *)key1, (char *)key2);
}

