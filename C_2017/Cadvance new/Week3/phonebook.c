#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct {
	char name[80];
	long number;
} PhoneEntry;

typedef struct {
	PhoneEntry * entries;
	int total;
	int size;
} PhoneBook;

PhoneBook createPhoneBook();
void dropPhoneBook(PhoneBook* book);
void addPhoneNumber(char * name, long number, PhoneBook* book);
PhoneEntry * getPhoneNumber(char * name, PhoneBook book);


int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

PhoneBook createPhoneBook(){
	PhoneBook *newPhoneBook;
	newPhoneBook = (PhoneBook *)malloc(sizeof(PhoneBook));
	return newPhoneBook;
}

void dropPhoneBook(PhoneBook* book){
	free(book);
}

int binarySearch(PhoneEntry* entries, int l, int r, char * name, int* found){

}

void addPhoneNumber(char * name, long number, PhoneBook* book){

}
