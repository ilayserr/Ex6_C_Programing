
/************************
Name : Ilay Serr
Email : ilay92@gmail.com
************************/

/************************************
*    TYPE DEFINITIONS               *
************************************/ 

typedef struct StringList_st * StringList;

/************************************
*    FUNCTION DECLARATIONS          *
************************************/

/*********************************************************
   numStrsInList                             (Problem 1.2)
   returns number of strings in list.
*********************************************************/
int numStrsInList(StringList strList);

/*********************************************************
   sfirstStrInList                           (Problem 1.3)
   the function receives a string list object (type StringList)
   and returns a pointer to the first string in the list.
*********************************************************/
char* firstStrInList(StringList strList);

/*********************************************************
   lastStrInList                             (Problem 1.4)
   The function receives a string list object (type StringList)
   and returns a pointer to the last string in the list.
*********************************************************/
char* lastStrInList(StringList strList);

/*********************************************************
   newStrList           	                 (Problem 1.5)
   The function should allocate space for the string list data 
   structure and should initialize it to hold an empty string list.
   If allocation failed, the function returns NULL.
*********************************************************/
StringList newStrList(void);

/*********************************************************
   addStrToList         					  (Problem 1.6)
   he function should allocate space for the string list data 
   structure and should initialize it to hold an empty string list.
   If allocation failed, the function returns NULL.                  
*********************************************************/
int addStrToList(StringList strList, char* str);

/*********************************************************
   addStrToSortedList                         (Problem 1.7)
   The function should assume that the strings in the list are already sorted 
   in ascending lexicographical order (according to function strcmp), and 
   should put the new string right before the first string in the list that is
   “larger” than the new string (or at the end if it is “larger” than all 
   other strings in the list).
*********************************************************/
int addStrToSortedList(StringList strList, char* str);

/*********************************************************
   sprintStringList                            (Problem 1.8)
   A function that prints the string list to the screen accordint to the format
   if format is some other value (not 0,1,2), then the function does nothing.
		0 - then the function simply prints each string in a separate line
		1 - then the function prints only one copy of each distinct string,
			meaning that if a string is identical to the string immediately 
			before it in the list, then it is not printed.
		2 - then the function prints only one copy of each distinct string 
		(see format 1), but it also prints the number of occurrences of each 
		string. Number appears before string in a field of width 4

*********************************************************/
void printStrList(StringList strList, int format);

/*********************************************************
   freeStrList                                (Problem 1.9)
   The function receives a string list object and frees all 
   memory allocated for the string list.
*********************************************************/
void freeStrList(StringList strList);
