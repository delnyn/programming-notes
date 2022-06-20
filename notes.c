#include <stdio.h>
// contains cool strings functions (comparison, concatenation, length...)
#include <string.h>
// contains the stuff for memory allocation
#include <stdlib.h>
#include "linked-lists.h"



char* shortenName (char nameSource[]); // global scope -> can be accessed via other files

void incrementAgeUsingPointer (unsigned short* age); // pass a pointer through the function to increment the variable pointed

static void pascalTriangle (); // static scope -> file only

unsigned int factorial(unsigned int x);

float getGradesAverage(short* grades, int arrayLength);



int main () {
	printf("Hello Demo Program!\n");

	// "unsigned" is for natural numbers
	// for integers, "int" "short" "long" and "long long" types exist
	unsigned short age = 69;
	char* name = "David"; // C-string: pointer to a chain of chars

	float pi = 3.141592;	// "float" and "double" for floating point decimals

	// X (2 here) dimensional array, can make as many dimensions as possible
	short luckSeed[][4] = { // size can be empty, except the size of the last dimension
		{84, 69, 24, 34},
		{45, 75, 56, 20} // to define the values at the same time, use curly brackets
	};

	short mathGrades[5] = {35, 84, 23, 92, 67};

	// define single values (add "int" before when first definition)
	luckSeed[1][0] = 85;
	
	// "%s" is the format specifier for strings, "%d" is for integers
	printf("%s is %d years old.\n", name, age); 

	if (age >= 18)
	{
		printf("%s is an adult.\n", name);
	} else if (luckSeed[0][2] > pi && age >= 60) // "&&" for AND, "||" for OR
	{
		printf("%s has good luck seeds and is an older person.\n", name);
	}

	// string length (from string.h)
	printf("%s is %lu characters long.\n", name, strlen(name));

	// string comparison (from string.h)
	if (strcmp(name, "David") == 0)
	{
		printf("Hey, David, I know you!\n");
	}

	printf("%s in 3 letters is %s.\n", name, shortenName(name));

	printf("%s has %f of average in math.\n", name, getGradesAverage(mathGrades, 5)); // "%f" for floats

	unsigned short counter = 0;
	while(1) {
		counter++;
		if (counter > 5)
		{
			break; // exit parent "while"
		} else {
			continue; // restart from the beginning of the "while" block
		}
	}

	static unsigned short ziggysAge = 34;	// variable is static, so scope is enlarged to file, not just "main()"

	// "&"" to reference: return the address of a variable ("%p" token to format pointers)
	unsigned short* pointerToAge = &age;	
	printf("Age is located at %p, %p.\n", pointerToAge, &age);

	// "*" to dereference: return value pointed by pointer
	printf("Age is %d, %d\n", age, *pointerToAge);

	// changing the dereferenced variable also change the real variable
	*pointerToAge -= 1;
	printf("Age is now %d, by changing the pointer variable.\n", age);

	// here is a struct
	// "struct person {};" works too (not a typedef), but you have to define them with "struct person name;"
	typedef struct {
		char* name;
		unsigned short age;
	} person;

	person dbowie;
	dbowie.name = name;
	dbowie.age = age;

	printf("The person 'dbowie' is named %s and is %d.\n", dbowie.name, dbowie.age); 

	// pass a pointer/referenced value to increment it (as the function requests a pointer)
	// note that we can send pass a pointer to a struct, and it works the same way
	incrementAgeUsingPointer(&age);
	printf("David had his pointer birthday! He is now %d.\n", age);

	// to allocate memory dynamically, we have to create a pointer that will store the location of the chunk
	// we will use this pointer to access this chunk, and free it once we're done
	// let's do that with a struct
	// we allocate enough memory for the "person" Ziggy
	person* zstardust = (person*) malloc(sizeof(person));
	// we write "(person*)" to tell that "malloc()" will return a person pointer
	// because "malloc()" returns a pointer with no type by default (-> doing this is called typecasting)

	// we can then access the data of "zstardust"
	// "a->b" is like "(*a).b"
	zstardust->name = "Ziggy";
	zstardust->age = ziggysAge;
	printf("%s is %d.\n", zstardust->name, zstardust->age);

	// we can then free the memory
	free(zstardust);
	// the "zstardust" variable still exists, but points to a location we don't have access to

	printf("\nPointers meet arrays! Demo (addresses):\n");

	// pointers to arrays are pointers to the first element of the array
	// also calling the name of the array returns the pointer of the array itself
	short* pointerToMathGrades = mathGrades; // we don't use "&mathGrades" because "mathGrades" alone is already a pointer
	for (int i = 0; i < 5; i++)
	{
		printf("%p // %p // %p\n", &mathGrades[i], mathGrades + i, pointerToMathGrades + i); // we don't dereference (*) because we want to print the addresses
	}

	pascalTriangle();

	printf("5! is %d\n", factorial(5));

	// struct defined globally because I need to (see higher)

	// the "pointer to the first element", aka...
	linkedListNode* myLinkedList = (linkedListNode*) malloc(sizeof(linkedListNode));
	if (myLinkedList == NULL)
	{
		return 1;
	}

	// assign values of the first node
	myLinkedList->value = 420;
	myLinkedList->next = NULL;
	// to add another node
	myLinkedList->next = (linkedListNode*) malloc(sizeof(linkedListNode));
	myLinkedList->next->value = 42;
	myLinkedList->next->next = NULL; // look at how "myLinkedList.next", when dereferenced, points to the next value! this can go on and on 

	printLinkedList(myLinkedList);

	addToEnd(myLinkedList, 69);
	pushToLinkedList(&myLinkedList, 13);
	pushToLinkedList(&myLinkedList, 10);
	printLinkedList(myLinkedList);

	popFromLinkedList(&myLinkedList);
	removeLast(myLinkedList);
	pushToLinkedList(&myLinkedList, 1);
	pushToLinkedList(&myLinkedList, 2);
	pushToLinkedList(&myLinkedList, 3);
	removeByIndex(myLinkedList, 3);
	printLinkedList(myLinkedList);

	return 0;
}



char* shortenName (char nameSource[]) {
	static char shortenedName[3]; // has to be static: function returns a C string (pointer), but the variable "shortenedName" is freed when the function is exited, so if not static, points to nothing
	strncat(shortenedName, nameSource, 3); // string concatenation (from string.h)
	return shortenedName;
}

void incrementAgeUsingPointer (unsigned short* age) {
	(*age)++;
}

void pascalTriangle () {
	printf("\nPascal triangle:\n");
    // pointer-allocator of array of 3 pointers (see below)
    int** pnumbers = (int**) malloc(3 * sizeof(int));

    // the 3 pointer-allocators of arrays containing the actual data
    pnumbers[0] = (int *) malloc(sizeof(int));
    pnumbers[1] = (int *) malloc(2 * sizeof(int));
    pnumbers[2] = (int *) malloc(3 * sizeof(int));

    pnumbers[0][0] = 1;
    pnumbers[1][0] = 1;
    pnumbers[1][1] = 1;
    pnumbers[2][0] = 1;
    pnumbers[2][1] = 2;
    pnumbers[2][2] = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d", pnumbers[i][j]);
        }
        printf("\n");
    }

    // free memory allocated for each row
    for (int i = 0; i < 3; i++) {
        free(pnumbers[i]);
    }

    // free top-level pointer
    free(pnumbers);

    printf("\n");
}

unsigned int factorial(unsigned int x) {
	unsigned int result = 1;
	if (x == 0)
	{
		return 1; // termination case
	}
	if (x > 1)
	{
		result = x * factorial(x-1); // recursion case
	}
	return result;
}

float getGradesAverage(short grades[], int arrayLength) {
	float gradesAverage = 0;
	for (int i = 0; i < arrayLength; i++)
	{
		gradesAverage += grades[i];
	}
	gradesAverage = gradesAverage/arrayLength;
	return gradesAverage;
}