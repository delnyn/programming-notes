#include <stdio.h>
// useful strings functions (comparison, concatenation, length...)
#include <string.h>
// lot of things, like memory allocation
#include <stdlib.h>
#include "linked-lists.h"



char * shortenName (char name[]); // global scope: can be accessed by other files

void incrementAgeUsingPointer (unsigned short * age); // pass a pointer through the function to increment the variable pointed

static void printPascalsTriangle (); // static scope: file only

unsigned int factorial (unsigned int number);

float getGradesAverage (short * grades, int arrayLength);



int main () {
	printf("Hello demo program!\n");

	// "unsigned": natural numbers
	// integers: "int" "short" "long" and "long long"
	unsigned short age = 69;
	char * name = "David"; // C-string: pointer to a chain of chars

	float pi = 3.141592; // "float", "double": floating point decimals

	// multidimensional array: can have as many dimensions as wanted
	short coolNumbers[][4] = { // sizes can be empty, enumbercept the size of the last dimension
		{84, 69, 24, 34},
		{45, 75, 56, 20} // use curly brackets to define the values while defining the array
	};
	coolNumbers[1][0] = 85;

	short mathGrades[5] = {35, 84, 23, 92, 67};
	
	// "%s": format specifier for strings; "%d": for integers; "%lu": for unsigned longs; "f": for floats; "%p" for pointers
	printf("%s is %d years old.\n", name, age); 

	if (age >= 18)
	{
		printf("%s is an adult.\n", name);
	} else if (coolNumbers[0][2] > pi && age >= 60) // "&&": AND; "||": OR
	{
		printf("%s has really cool numbers and is an older person.\n", name);
	}

	// "strlen": get string length (string.h)
	printf("%s is %lu characters long.\n", name, strlen(name));

	// "strcmp": compare two strings (string.h)
	if (strcmp(name, "David") == 0)
	{
		printf("Hey, David, I know you!\n");
	}

	printf("\"%s\" shortened is \"%s\".\n", name, shortenName(name));

	printf("%s has %f of average in math.\n", name, getGradesAverage(mathGrades, 5));

	unsigned short counter = 0;
	while(1) {
		counter++;
		if (counter > 5)
		{
			break; // enumberit parent "while"
		} else {
			continue; // restart from the beginning of the "while" block
		}
	}

	static unsigned short ziggysAge = 34; // static variable: scope is enlarged to file, not just "main()"

	// "&"" to reference: return address of a variable
	unsigned short * pointerToAge = &age;	
	printf("Age is located at %p, %p.\n", pointerToAge, &age);

	// "*" to dereference: return value pointed by pointer
	printf("Age is %d, %d\n", age, *pointerToAge);

	// change dereferenced pointer variable to change real variable
	*pointerToAge -= 1;
	printf("Age is now %d, by changing the dereferenced pointer variable.\n", age);

	typedef struct {
		char * name;
		unsigned short age;
	} person;

	person dbowie;
	dbowie.name = name;
	dbowie.age = age;

	printf("The person 'dbowie' is named %s and is %d.\n", dbowie.name, dbowie.age); 

	// pass a pointer through a function, and dereference it inside the varible to change its value
	// we can pass a pointer pointing to a struct, it works the same way
	incrementAgeUsingPointer(&age);
	printf("David had his pointer birthday! He is now %d.\n", age);

	// allocate memory dynamically: create a pointer that will store the location of the chunk of memory with "malloc" (stdlib.h)
	// use this pointer to access this chunk, and free it once we're done
	// allocate enough memory for the "person" zstardust
	person * zstardust = (person *) malloc(sizeof(person));
	// typecasting: write "(person *)" to tell "malloc()" to return a person pointer ("malloc()" returns a pointer with no type by default)

	// "a->b" is like "(*a).b"
	zstardust->name = "Ziggy";
	zstardust->age = ziggysAge;
	printf("%s is %d.\n", zstardust->name, zstardust->age);

	// free memory allocated to this pointer
	free(zstardust);
	// "zstardust" variable still enumberists, but points to a location we cant't access

	printf("\nPointers & arrays (addresses):\n");
	// name of the array only is a pointer pointing to the beginning of the array
	for (int i = 0; i < 5; i++)
	{
		printf("%d: %p // %d: %p\n", mathGrades[i], &mathGrades[i], *(mathGrades + i), mathGrades + i);
	}

	printf("\n");
	printPascalsTriangle();
	printf("\n");

	printf("5! is %d\n", factorial(5));
	printf("\n");

	// always a pointer
	linkedListNode * myLinkedList = (linkedListNode *) malloc(sizeof(linkedListNode));

	// assign values of the first node
	myLinkedList->value = 420;
	myLinkedList->next = NULL;
	// add another node (manually (useless, I made a lib))
	myLinkedList->next = (linkedListNode *) malloc(sizeof(linkedListNode));
	myLinkedList->next->value = 42;
	myLinkedList->next->next = NULL; // "myLinkedList->next" (dereferenced) points to the next node

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



char * shortenName (char name[]) {
	static char shortenedName[3]; 
	// has to be static: function returns C-string (pointer); variable "shortenedName" is freed when function is enumberited -> if scope is only function, points to nothing when function is enumberited
	strncat(shortenedName, name, 3); // string concatenation (string.h)
	return shortenedName;
}

void incrementAgeUsingPointer (unsigned short * age) {
	(*age)++;
}

void printPascalsTriangle () {
	printf("Pascal triangle:\n");
    // pointer allocating an array of 3 pointers (see below)
    // pointer to pointer: "**"
    int ** niceNumbers = (int **) malloc(3 * sizeof(int));

    // 3 pointers allocating arrays containing the actual data
    niceNumbers[0] = (int *) malloc(sizeof(int));
    niceNumbers[1] = (int *) malloc(2 * sizeof(int));
    niceNumbers[2] = (int *) malloc(3 * sizeof(int));

    niceNumbers[0][0] = 1;
    niceNumbers[1][0] = 1;
    niceNumbers[1][1] = 1;
    niceNumbers[2][0] = 1;
    niceNumbers[2][1] = 2;
    niceNumbers[2][2] = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d", niceNumbers[i][j]);
        }
        printf("\n");
    }

    // free memory allocated for each row
    for (int i = 0; i < 3; i++) {
        free(niceNumbers[i]);
    }
    free(niceNumbers); // free master pointer
}

unsigned int factorial(unsigned int number) {
	unsigned int result = 1;
	if (number == 0)
	{
		return 1; // termination case
	}
	if (number > 1)
	{
		result = number * factorial(number-1); // recursion case
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