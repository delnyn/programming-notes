#include <stdio.h>
// useful strings functions (comparison, concatenation, length...)
#include <string.h>
// lot of things, like memory allocation
#include <stdlib.h>
#include "linked-list.h"
#include "binary-tree.h"



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

	const float pi = 3.141592; // "float", "double": floating point decimals
	// "const": constant variable, you can't  change it
	// pointer to constant must be a constant too
	// constant pointer to a non constant: the pointer will always point to the same location; you can still change the value pointed by it tho

	// multidimensional array: can have as many dimensions as wanted
	short coolNumbers[][4] = { // sizes can be empty, enumbercept the size of the last dimension
		{84, 69, 24, 34},
		{45, 75, 56, 20} // use curly brackets to define the values while defining the array
	};
	coolNumbers[0][0] = 85;

	short mathGrades[5] = {35, 84, 23, 92, 67};
	
	// "%s": format specifier for strings; "%d": for integers; "%lu": for unsigned longs; "f": for floats; "%p": for pointers; "%i": for chars;
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

	binaryTreeNode * root = (binaryTreeNode *) malloc(sizeof(binaryTreeNode));
	root->value = 0;
	root->right = NULL;
	root->left = NULL;

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			appendNode(root, coolNumbers[i][j]);
		}
	}
	printTreeDFSInOrder(root);
	printf("\n");

	// unions: structs but every "variable" is the same in memory
	// an int is 4 bytes. here we can access these 4 bytes as one int, but also as four chars.
	union intParts {
 		int theInt;
 		char theBytes[sizeof(int)];
	};
	union intParts niceInt;
	niceInt.theInt = -905928872; // chosen arbitrarily
	printf("Union: %d // [%i, %i, %i, %i]\n", niceInt.theInt, niceInt.theBytes[0], niceInt.theBytes[1], niceInt.theBytes[2], niceInt.theBytes[3]);

	int chosenInt = niceInt.theInt;
	// reference the int, add an offset, then dereference it, and don't forget to typecast so it's not interpreted as an int
	printf("Union: %d // [%i, %i, %i, %i]\n", niceInt.theInt, (char)chosenInt, *((char *)&chosenInt + 1), *((char *)&chosenInt + 2), *((char *)&chosenInt + 3));

	// unions inside of structs
	typedef struct {
		char * name;
		union {
			int dataInt;
			short dataShort;
		} data;
	} personWithUnion;

	personWithUnion asane;
	asane.name = "Alladin Sane";
	asane.data.dataInt = 6999999;
	printf("%s's data: %d, %d.\n", asane.name, asane.data.dataInt, asane.data.dataShort);

	// here we can define the union without a name so we can access the members of the union directly 
	typedef struct {
		char * name;
		union {
			int dataInt;
			short dataShort;
		};
	} personWithUntitledUnion;

	personWithUntitledUnion twduke;
	twduke.name = "Thin White duke";
	// like this
	twduke.dataInt = 77999999;
	printf("%s's data: %d, %d.\n", twduke.name, twduke.dataInt, twduke.dataShort);

	// also works with unnamed structs inside of unions
	union intPartsWithStruct {
 		int theInt;
		struct {
			char firstByte;
			char secondByte;
		};
	};

	// don't  forget to tell that this is an union
	union intPartsWithStruct realCoolInt;
	realCoolInt.theInt = -905928872;
	printf("The real cool int is %d (%i %i)\n", realCoolInt.theInt, realCoolInt.firstByte, realCoolInt.secondByte);

	short * pointerToGrades = &mathGrades[2];
	printf("mathGrades: %d @ %p\n", *pointerToGrades, pointerToGrades);
	pointerToGrades++;
	printf("mathGrades: %d @ %p\n", *pointerToGrades, pointerToGrades);
	pointerToGrades--;
	pointerToGrades--;
	printf("mathGrades: %d @ %p\n", *pointerToGrades, pointerToGrades);
	pointerToGrades += 3;
	printf("mathGrades: %d @ %p\n", *pointerToGrades, pointerToGrades);
	// this could go on for -, ==, < and >
	
	// function pointers
	// the function returns a pointer to a bunch of chars, is a function pointer and takes a pointer to an int as a parameter
	float (*pointerToAverage)(short *, int);
	pointerToAverage = &getGradesAverage;
	printf("Average (calculated with chad pointer): %f\n", (pointerToAverage)(mathGrades, 5));
	// this can be useful in some cases, mostly passing a function to another function
	
	// or making an array pointing to functions (very practical, I wished to be able to do this back when I was coding in JS lol)
	void (*functions[2])(/*args types go here*/) = {&incrementAgeUsingPointer, &printPascalsTriangle};
	(functions[1])();
	
	// bitmasks: editing data as bits, purely
	char bitmaskVariable = 0;
	// set bit 3 of bitmask to 1
	// (index starting at 0)
	// bitmask is 00003000 -> 8
	bitmaskVariable |= 1 << 3; // set
	bitmaskVariable &= ~(1 << 4); // clear
	bitmaskVariable ^= 1 << 6; // flip
	printf("The third bit is %d\n", bitmaskVariable & (1 << 3)); // check the value of a single bit: returns 1/2/4/8/16... or 0

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
