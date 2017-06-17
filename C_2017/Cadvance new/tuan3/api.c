#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10
#define MAX 20
typedef struct entry
{
  void *key;
  void *value;
}Entry;
typedef struct symbol{
  Entry *entries;
  int size;
  int total;
  Entry (*makeNode)(void *, void *);
  int (*compare)(void *, void*);{
    if (tab == NULL)
      exit(1);
    if (tab->entries != NULL)
      {
	Entry *to_free_entry = tab->entries;
	int i = 0;
	while (i < tab->total)
	  {
	    free(to_free_entry->key);
	    free(to_free_entry->value);
	    to_free_entry++;
	    i++;
	  }
	free(tab->entries);
      }
    tab->total = 0;
    tab->size = INITIAL_SIZE;
    tab->entries = NULL;
  }
  Entry *getEntry(void *key, SymbolTable book)
  {
    Entry *res = book.entries;
    int i = 0;
    while (i < book.total)
      {
	if (book.compare(res->key, key) == 0)
	  return res;
	res++;
	i++;
      }
    return NULL;
  }
  void addEntry(void *key, void *value, SymbolTable *book)
  {
    if (key == NULL || book == NULL)
      exit(1);
    if (getEntry(key, *book) != NULL)
      return;
    if (book->entries == NULL)
      exit(1);
    if (book->total == book->size)
      {
	(book->size) += INCREMENTAL_SIZE;
	(book->entries) = (Entry *)realloc(book->entries, sizeof(Entry) * (book->size));
	if (book->entries == NULL)
	  exit(1);
      }
    Entry *add = book->entries;
    add[book->total] = book->makeNode(key, value);
    (book->total)++;
  }
  Entry makePhone(void *name, void *phone)
  {
    Entry res;
    res.key = strdup((char*)name);
    res.value = strdup((char*)phone);
    memcpy(res.value, phone, sizeof(long));
    return res;
  }
  int comparePhone(void *key1, void *key2)
  {
    return strcmp((char *)key1, (char *)key2);
  }
  void main()
  {
    SymbolTable book = createSymbolTable(makePhone, comparePhone);

    addEntry("DAICA", "01699636338", &book);
    addEntry("Linh", "0969741168", &book);
    addEntry("Doggy", "6969696969", &book);
    addEntry("Thaiboos","0969243103",&book);
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

