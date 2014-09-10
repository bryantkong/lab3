#include <stdlib.h>
#include <stdio.h>
#include "arrayList.h"

/**
 * @author Grayson Bryant
 * @version 9/10/2014
 */

//getSize not accessed outside of this file so declare it to be static
//static essentially makes it private to this file 
static int getSize(primitiveType type);

/**
 * Initializes a multitype array list in c with a default size of 4 and 0
 * elements inside the array. It then will specify the type of array (char, int, or short)
 * by the parameter.
 * @parameters type - value associated with the type of array list (char, int, short)
 * @return arrayList * - returns a pointer to the intialized array list with specified type.
 */
arrayList * initialize(primitiveType type)
{
   arrayList * arrayLis;
   arrayLis = (arrayList*) malloc(sizeof(arrayList));
   arrayLis->arraySize = 4;
   arrayLis->type = type;
   arrayLis->numElements = 0;
   arrayLis->elementSize = getSize(type);
   arrayLis->array = malloc(arrayLis->elementSize * 4);
   return arrayLis;
}

/**
 * Sets the number of bytes need for each entry in the array since not all
 * primitive types have the same byte size.
 * @parameter type - (char, int, short) signifies the number of bytes need from the type.
 * @returns int - size of bytes for each entry (char = 1, short = 4, int = 8)
 */
int getSize(primitiveType type)
{
   if (type == charType)
   {
       return sizeof(char);
   }
   if (type == intType)
   {
       return sizeof(int);
   }
   return sizeof(short);
}

/**
 * Adds a new corrolating primitave type to the array list and if the array is full
 * it will create a new array twice the original size and copy the old array the free
 * the old array's space.
 * @parameters arylstP - pointer to an arraylist to add the element.
 *  element - char, int, or short that will be added to the array list.
 */
void addElement(arrayList * arylstP, void * element)
{
   if (arylstP->arraySize == arylstP->numElements)
   {
       void * temp;
       temp = malloc((arylstP->arraySize) * arylstP->elementSize * 2);
       int i = 0;
       for (; i < arylstP->numElements * arylstP->elementSize; i++)
       {
         *((char * )temp + i) = *((char *) (arylstP->array + i));
       }
       free(arylstP->array);
       arylstP->array = temp;
       arylstP->arraySize = arylstP->arraySize * 2;
   }
   if (arylstP->type == charType)
   {
      *((char *) (arylstP->array + arylstP->numElements)) = *((char *) element); 
   }
   else if (arylstP->type == intType)
   {
      *(((int *) arylstP->array) + arylstP->numElements) = *((int *) element);
   }
   else if (arylstP->type == shortType)
   {
      *(((short *) arylstP->array) + arylstP->numElements) = *((short *) element); 
   }
   arylstP->numElements++;
}

/**
 * Removes from an array list the element at the specified entry then
 * the entries behind the deleted spot will be shifted up to fill the blank.
 * @parameters arylstP - pointer to an arraylist to remove the element.
 *  index - entry in the array list that is to be removed.
 */
void removeElement(arrayList * arylstP, int index)
{
    int i;
    if (arylstP->type == charType)
    {
        for (i = index; i < arylstP->numElements - 1; i++)
        {
            *((((char *) arylstP->array) + i)) = *(((char *) arylstP->array) + i + 1);
        }
        arylstP->numElements = arylstP->numElements - 1;
    }
    else if (arylstP->type == shortType)
    {
        for (i = index; i < arylstP->numElements - 1; i++)
        {
            *((((short *) arylstP->array) + i)) = *(((short *) arylstP->array) + i + 1);
        }
        arylstP->numElements = arylstP->numElements - 1;
    }
    else if (arylstP->type == intType)
    {
        for (i = index; i < arylstP->numElements - 1; i++)
        {
            *((((int *) arylstP->array) + i)) = *(((int *) arylstP->array) + i + 1);
        }
        arylstP->numElements = arylstP->numElements - 1;
    }
}
      
/**
 * Prints the contents of the array list.
 * @parameters arylstP - pointer to array list structure that will print the 
 *  values through the number of elements in it.
 */
void printArray(arrayList * arylstP)
{
   int i;
   printf("array size: %d, num elements: %d contents: ", 
          arylstP->arraySize, arylstP->numElements);
   for (i = 0; i < arylstP->numElements; i++)
   {
      if (arylstP->type == charType)
      {
          char element;
          element = *((char *) ((arylstP->array)+ i));
         printf("%02x ", 0xff & element);
      }
      else if (arylstP->type == shortType)
      {
          short shot;
          shot = *(((short *) arylstP->array) + i);
         printf("%04x ", 0xffff & shot);
      }
      else if (arylstP->type == intType)
      {
         //fill in the missing code that gets the element and &s it with 0xffffffff
          int intelem;
          intelem = *(((int *) arylstP->array) + i);
         printf("%08x ", 0xffffffff & intelem);
      }
   }
   printf("\n");
}

