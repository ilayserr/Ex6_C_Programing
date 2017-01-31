
/************************
Name : Ilay Serr
Email : ilay92@gmail.com
************************/

/*********************************************************
*  sortFileWords.c                                          *
*  ~~~~~~~~~~~~                                          *
*  file implementing sorting a list                                          *
*********************************************************/

/*** use only these C libraries ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>    
#include "stringList.h"


#define BUFF_SIZE 201


/***************************************************************************
Functions declarations
***************************************************************************/
/* ALL THOSE FUNCTIONS ARE FROM EX5 */

/*********************************************************
   emptyStrList                    
   writes an empty string list in a given array (buffer).
   buffer size should be at least 2
*********************************************************/
void emptyStrList(char* target);

/*********************************************************
   strListFromWords                         
   writes a new string list into a given array (buffer)
   using words in a given source string.
   returns number of srings in list
   - if buffSize<2, returns -1 (and does nothing
   - if buffSize is too small to hold the entire list, writes
     an empty list and returns 0
*********************************************************/
int strListFromWords(const char* source, char* target, int buffSize);

/*********************************************************
   createStrList                            
   creates a new string list using words in a given string.
   allocates required space (exactly)
   returns pointer to new string list
   (or NULL if allocation failed)
*********************************************************/
char* createStrList(const char* str);

/*********************************************************
   nextStrInList                           
   returns pointer to next string in list.
   - if previous call to function was with different list,
     returns pointer to first string in list.
   - if previous call to function was with same list,
     returns pointer to next string in list
     (following the string returned by the previous call).
     If that string was the last one, then returns NULL.
   - if function is called with NULL pointer, then it re-sets
     the identity of the previous list.
*********************************************************/
char* nextStrInList(char* strList);

/***************************************************************************
main
***************************************************************************/

int main(int argc , char** argv) {
	
	// checking if the number of arguments is valid
	if (argc < 2 || argc > 3) {
		fprintf(stderr, "Usage: ./sortFileWords file [-u|-c]]\n");
		return 1; 
	}

	if (argc == 3 && strcmp(argv[2], "-u") != 0 && strcmp(argv[2], "-c") != 0) {
		fprintf(stderr, "Invalid usage operator %s. Expecting -u or -c\n" , argv[2]);
		return 1;
	}

	// declaring the variables and allocating memorry
	FILE* file;
	char* line = malloc((BUFF_SIZE) * sizeof(char));
	char* lineStr = malloc((BUFF_SIZE) * sizeof(char));
	char* word;
	int res;
	StringList strList;

	strList = newStrList();

   // checking if allocation successfull
	if (!line || !lineStr) {
		fprintf(stderr, "Could not allocate memorry\n");
		return 1;
	}

   // checking if the user want the standard input
	if (*argv[1] == '-') file = stdin;
  	else file = fopen(argv[1], "r");

   // trying to open the file
	if(!file) {
		fprintf(stderr, "Could not open input file %s for reading\n", argv[1]); 	
   		freeStrList(strList);
   		free(line);
   		free(lineStr);
      	return 1;
   }

   // inserting the file lines into the allocated array
	while(fgets(line,BUFF_SIZE,file)) {
		lineStr = createStrList(line);
		word = nextStrInList(lineStr);
		while (word) {
			res = addStrToSortedList(strList, word);
			if (res == 0) {
				freeStrList(strList);
   				free(line);
   				free(lineStr);
				return 1;
			}
			word = nextStrInList(lineStr);
		}
	}

	if (argc == 3) {
		if (strcmp(argv[2], "-u")) printStrList(strList, 2);
		else printStrList(strList, 1);
	} else printStrList(strList, 0);
	
   //freeing memorry
	fclose(file);
	freeStrList(strList);
	free(line);
	free(lineStr);

   return 0;
}
/* end of main */

/************************************
Function emptyStrList
Params:
- target - the given pointer to the list
A function that makes an empty list
Return value: nothing
***********************************/
void emptyStrList(char* target) {
   target[0] = '\0';
   target[1] = '\0';
   return;
}


/************************************
Function strListFromWords
Params:
- source - the given pointer to the string
- target - the given pointer to the string list
- buffSize - the size of target
- count - a counter of the number of "words/strings in the list
  useing count is more efficient than using the function "numStrsInList"
A function that copy the string from 'source' to 'target'
Return value: the number of "words" in target (after making it)
***********************************/

int strListFromWords(const char* source, char* target, int buffSize) {
   int count = 0;
   if (buffSize < 2) return -1;
   while (isspace(*source)) source++; 
   if (*source != '\0') count = 1;
   while (*source) {
      if (isspace(*source)) {
         *target = '\0';
         while (isspace(*source)) source++;
         if (*source == '\0') return count;
         count++;
      } else {
         *target = *source;
         source++;
      }
      target++;
   }
   *target = '\0';
   *(target + 1) = '\0';
   while (isspace(*source)) source++;
   if (*source != '\0'){
      emptyStrList(target);
      return 0;   
   }
   return count;
}


/************************************
Function createStrList
Params:
- str - the given pointer to the string
- len - an index of the location in the list
- count - a counter of the number of charcters while shrinking the spaces
A function that creates a string list in a newly allocated array from words
in a given string str. the allocated space is as effiecient as possible
(no extra spaces).
Return value: a pointer to the start of the new string list
***********************************/
char* createStrList(const char* str) {
   int count = 0, len = 0; 
   while (isspace(str[len])) len++;
   while (str[len]) {
      if (isspace(str[len])) {
         while (isspace(str[len])) len++;
         count++;
      }
      count++;
      len++;
   }
   count += 2;
   char *target = malloc (count * sizeof(char));
   strListFromWords(str , target, count);
   return target;
}

/************************************
Function nextStrInList
Params:
- strList - the given pointer to the string
- last - a pointer to the last list called
- p - a pointer to the last string 
A function that return the next word in a string already called by the function
or NULL if it is the last word in the string. or the first word in the string
if it's the first time the function called the list.
Return value: a pointer to the word requested by the orders given.
***********************************/
char* nextStrInList(char* strList) {
   static char* last = NULL;
   static char* p = NULL;
   if (last == strList && strList != NULL) {
      while (*p != '\0') p++;
      p++;
      if (*p == '\0') return NULL;
      else return p;
   } else {
      p = strList;
      last = strList;
      return strList;
   }
}
       

