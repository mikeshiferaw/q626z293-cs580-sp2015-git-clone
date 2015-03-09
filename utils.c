/*Mike Shiferaw, q626z293, Assignment 1*/
/*These four functions read in the user’s response as a string, then convert it to the return type of the function*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

int get_int(char *prompt)
{
	char str[20];
	char *end_ptr=(char*)malloc(sizeof(char));
	int valid_number= 1;
	long num;
do
	{
  if (!valid_number)
	printf("You must enter an integer. ");
	printf("%s", prompt);
	scanf("%s", str);
	num= strtol (str, &end_ptr, 10);
  if (end_ptr !=(str + strlen(str)))
		valid_number = 0;
  else
		valid_number = 1;
	} while(!valid_number);
   return (int) num;
}

long get_long(char *prompt)
{ 
	
	char str[20];
	char *end_ptr=(char*)malloc(sizeof(char));
	int valid_number=1;
	long num;
do
	{
  if (!valid_number)
	printf("You must enter an integer. ");
	printf("%s", prompt);
	scanf("%s", str);
	num= strtol (str, &end_ptr, 10);
  if (end_ptr !=(str + strlen(str)))
		valid_number= 0;
  else
		valid_number= 1;
	} while(!valid_number);
   return num;
}

float get_float(char *prompt)
{
	char str[20];
	float num;
	char *end_ptr=(char*)malloc(sizeof(char));
	int valid_number=1;
	
do
{
  if (!valid_number)

	printf("You must enter an integer. ");
	printf("%s", prompt);
	scanf("%s", str);
	num= strtol (str, &end_ptr, 10);
  if (end_ptr !=(str + strlen(str)))
		valid_number= 0;
  else
		valid_number= 1;
	
 }while(!valid_number);

   return num;	
}

double get_double(char* prompt)
{	
	char str[20];
	double num;	
	char *end_ptr=(char*)malloc(sizeof(char));
	int valid_number=1;
do{
  if (!valid_number)
	printf("You must enter a valid number. ");
	printf("%s", prompt);
	scanf("%s", str);
	num= strtod (str, &end_ptr);
  if (end_ptr !=(str + strlen(str)))
		valid_number= 0;
  else
		valid_number= 1;
	} while(!valid_number);
   return num;	
}
