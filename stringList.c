
/************************
Name : Ilay Serr
Email : ilay92@gmail.com
************************/

/*********************************************************
*  stringList.c                                          *
*  ~~~~~~~~~~~~                                          *
*  file implementing data structure and functions for    *
*  string list                                           *
*********************************************************/

/*** use only these C libraries ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>    
#include "genericLinkedList.h"
#include "stringList.h"

struct StringList_st {
	int numStrs;
	ListNode listHead;
	ListNode listTail;
};

/***************************************************************************
Functions 1.2 - 1.9 implementation
***************************************************************************/

/************************************
Function numStrsInList
Params:
- strList - the given pointer to the list
A function that returns the number of strings in a given string list.
Return value: the number of "words" (taken from field numStrs)
***********************************/
  
int numStrsInList(StringList strList) {
   	return strList->numStrs;
}     

/************************************
Function firstStrInList  
Params:                      
- strList - the given pointer to the list
the function receives a string list object (type StringList)
and returns the first word (char*) in it.
Return value: the first word in the list
***********************************/

char* firstStrInList(StringList strList) {
   	return listNodeData(strList->listHead);
}

/************************************
Function lastStrInList  
Params:                      
- strList - the given pointer to the list
the function receives a string list object (type StringList)
and returns the last word (char*) in it.
Return value: the last word in the list
***********************************/

char* lastStrInList(StringList strList) {
  	return listNodeData(strList->listTail);
}

/************************************
Function newStrList
Params:
- source - the given pointer to the string
The function should allocate space for the string list data structure and should
initialize it to hold an empty string list.
If allocation failed, the function returns NULL.
Return value: the new list, If allocation failed, the function returns NULL.

***********************************/

StringList newStrList(void) {
   	StringList newList = malloc (sizeof(struct StringList_st));

   	/*** set structure members ***/
   	if (newList) {
		newList->numStrs = 0;
		newList->listHead = NULL; 
		newList->listTail = NULL; 
	}

	/*** return NULL if allocation failed ***/
	return newList;
}

/************************************
Function addStrToList
Params:
- strList - the given list to work on
- str - the given data to enter the end of the list
The function should allocate space for the new string and the new 
list node, and copy the given string to the allocated space.
Return value: The function returns 1 if successful, and 0 if allocation failed.
***********************************/

int addStrToList(StringList strList, char* str) { 
	int res;

	// allocating space to the new string
	char* newStr = malloc (sizeof(char) * strlen(str));
	if (!newStr) return 0;

	// copy given string to the new string
	strcpy(newStr, str);

	// declare new variable newNode
	ListNode newNode = newListNode(newStr);
	// checking if the new Node declartion was succesful 
	if (newNode) {

		if (strList->numStrs == 0) {
			strList->listHead = newNode;		
		} else {

			// inserting the new string into the new node data
			res = listNodeInsert(strList->listTail, newNode);

			// if the insertion failed
			if (res == 0) {
				freeListAndData(newNode);
				return 0;
			}  
		}		
		// replacing the last field
		strList->listTail = newNode;

	// if failed, freeing memorry	
	} else {
		free(newStr);
		return 0;
	}
	strList->numStrs++; 
	return 1;
}

/************************************
Function addStrToSortedList
Params:
- strList - the given pointer to the string
- str - the given data to enter the end of the list
The function should assume that the strings in the list are already sorted 
in ascending lexicographical order (according to function strcmp), and 
should put the new string right before the first string in the list that is
“larger” than the new string (or at the end if it is “larger” than all 
other strings in the list).
Return value: The function returns 1 if successful, and 0 if allocation failed.
***********************************/

int addStrToSortedList(StringList strList, char* str) {
   	int res;

   	//if the list is empty
   	if (strList->numStrs == 0) {
   		res = addStrToList(strList, str);
   		return res;
   	}

   	// allocating space to the new string
	char* newStr = malloc (sizeof(char) * strlen(str));
	if (!newStr) return 0;

	// copy given string to the new string
	//while (*str) {
	//	*newStr = *str;
	//	str++;
	//	newStr++;
	//}
	strcpy(newStr, str);

	// declare new variable newNode
   	ListNode newNode = newListNode(newStr);

   	// checking if the new Node declartion was succesful 
   	if (newNode) { 

   		// creating a variable to use as a pointer
		ListNode curr = strList->listHead;

		// in case the new node is the smallest in the list
		if (strcmp(listNodeData(curr), listNodeData(newNode)) > 0) {

			// inserting the new string into the new node data
			res = listNodeInsert(curr, newNode);
			if (res == 0) {
				freeListAndData(newNode);
				return 0;
			} 

			// deleting the first node from the list
			listSplit(curr);

			//updating the field of the first nnode
			strList->listHead = newNode;

			// inserting the node we extracted in the correct place
			res = listNodeInsert(newNode, curr);
			if (res == 0) {
				freeListAndData(curr);
				return 0;
			} 

		// in case the new node is not the smallest in the list	
		} else {
			while (curr != strList->listTail && strcmp(listNodeData
						(listNodeNext(curr)), listNodeData(newNode)) < 0 ) {
				curr = listNodeNext(curr);
			}	 

			// inserting the new string into the new node data
			res = listNodeInsert(curr, newNode);

			// if the insertion failed
			if (res == 0) {
				freeListAndData(newNode);
				return 0;
			} else {

				// if curr is the last node, replacing the last field
				if (curr == strList->listTail) {
					strList->listTail = newNode;
				}
			}
		}

	// if failed, freeing memorry		
	} else {
		free(newStr);
		return 0;
	}
	strList->numStrs++; 
	return 1;
}

/************************************
Function printStringList
Params:
- strList - the given pointer to the string
- format - the given format:
		0 - then the function simply prints each string in a separate line
		1 - then the function prints only one copy of each distinct string,
			meaning that if a string is identical to the string immediately 
			before it in the list, then it is not printed.
		2 - then the function prints only one copy of each distinct string 
		(see format 1), but it also prints the number of occurrences of each 
		string. Number appears before string in a field of width 4
A function that prints the string list to the screen accordint to the format
if format is some other value (not 0,1,2), then the function does nothing.
***********************************/

void printStrList(StringList strList, int format) {

	// creating a variable to use as a pointer
	ListNode curr = strList->listHead;

	// if the list is empty
	if (strList->numStrs == 0) {
		printf ("Empty list\n");
		return;
	}
	// if the format is 0 print all the lines
	if (format == 0) {
		while(curr != strList->listTail) {
			printf("%s\n",(char*)listNodeData(curr));
			curr = listNodeNext(curr);
		}
		printf("%s\n",(char*)listNodeData(curr));

	// if the format is 1 or 2
	} else if (format == 1 || format == 2) {

		//if the list is in size 1
		if (strList->numStrs == 1){
			if (format == 1) printf("%s\n",(char*)listNodeData(curr));
			else printf("   %d %s\n",1 ,(char*)listNodeData(curr));
			return;
		}

		// if the list is in size 2 or more
		int sum = 1;
		ListNode next = listNodeNext(curr);
		while (next != strList->listTail) {

			// if there was a double word
			if (strcmp(listNodeData(curr), listNodeData(next)) == 0) {
				sum++;
				curr = listNodeNext(curr);	
				next = listNodeNext(next);

			// if there ws not a double word
			} else {
				if (format == 1) printf("%s\n",(char*)listNodeData(curr));
				else printf("   %d %s\n",sum ,(char*)listNodeData(curr));
				sum = 1;
				curr = listNodeNext(curr);	
				next = listNodeNext(next);
			}
		}

		// dealing with the last two cases
		if (strcmp(listNodeData(curr), listNodeData(next)) == 0) {
			sum++;
			if (format == 1) printf("%s\n",(char*)listNodeData(curr));
			else printf("   %d %s\n",sum ,(char*)listNodeData(curr));
		} else {
			if (format == 1) printf("%s\n",(char*)listNodeData(curr));
			else printf("   %d %s\n",sum ,(char*)listNodeData(curr));
			if (format == 1) printf("%s\n",(char*)listNodeData(next));
			else printf("   %d %s\n",1 ,(char*)listNodeData(next));
		}

	// if the format is no 0/1/2	
	} else return;
}

/************************************
Function freeStrList
Params:
- strList - the given list to work on
The function receives a string list object and frees all memory allocated for
the string list.
***********************************/

void freeStrList(StringList strList) { 
	if (strList->numStrs == 0) {
		freeList(strList->listHead);
		return;
	} else {
		freeListAndData(strList->listHead);
	} 
}
