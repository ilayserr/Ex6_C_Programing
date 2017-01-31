/*******************************************
*  testStringList.c                        *
*  ~~~~~~~~~~~~~~~~                        *
*  Testing procedure for string list data  *
*  structure. See testStringList.out for   *
*  expected output.                        *
*******************************************/

#include <stdio.h>
#include "stringList.h"

/************************************
*               MAIN                *
************************************/ 

int main() {
   /*** array of string pointers to add to lists ***/
   char* listOfStrings[] = {"Hello, ","Hello world", "I", "am", "very", "very", "fine", ", I", "am","."};

   int i, numStrs = sizeof(listOfStrings)/sizeof(listOfStrings[0]);
   StringList strList1, strList2;

   printf(" 1. Creating empty string lists strList1 and strList2\n");
   strList1 = newStrList();
   strList2 = newStrList();
   if(!strList1) {
      fprintf(stderr,"OOM strList1\n");
      return 1;
   }
   if(!strList2) {
      fprintf(stderr,"OOM strList2\n");
      freeStrList(strList1);
      return 1;
   }
   printf(" 2. Making sure that strList1 is empty\n");
   if(numStrsInList(strList1) == 0 && !firstStrInList(strList1) && !lastStrInList(strList2)) {
      printf("      okay\n");
   } else {
      printf("      strList1 is not truly empty. Please check!\n");
   }

   printf(" 3. Printing both string lists:\n");
   printf("     strList1: ");
   printStrList(strList1,0);
   printf("     strList2: ");
   printStrList(strList2,0);

   printf(" 4. Adding strings one by one to lists. Strings in strList1 are added to tail, and strings in strList2 are added sorted:\n");
   for(i=0; i<numStrs; i++) {
      printf("     adding string %s\n", listOfStrings[i]);
      addStrToList(strList1, listOfStrings[i]);
      addStrToSortedList(strList2, listOfStrings[i]);
      printf("     strList1 has %d strings: first: %s |last: %s\n", numStrsInList(strList1), firstStrInList(strList1), lastStrInList(strList1));
      printf("     strList2 has %d strings: first: %s |last: %s\n", numStrsInList(strList2), firstStrInList(strList2), lastStrInList(strList2));
   }

   printf(" 5. Making sure that list does not point to source string, by modifying first source string to \"Something new\":\n");
   listOfStrings[0] = "Something new";
   printf("     first string in strList1 his still \"%s\" \n", firstStrInList(strList1));


   for(i=0; i<4; i++) { 
      printf("%2d. Printing strList1 using format=%d:\n",6+2*i,i);
      printStrList(strList1,i);
      printf("%2d. Printing strList2 using format=%d:\n",7+2*i,i);
      printStrList(strList2,i);
   }
   printf("%2d. Freeing both lists.\n",6+2*i);
   freeStrList(strList1);
   freeStrList(strList2);
   
   return 0;      
}
/*** end of main ***/

