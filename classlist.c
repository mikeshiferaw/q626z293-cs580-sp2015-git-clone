/*
* File: classlist.c
*
* This program uses a binary search tree to store names of students who are
* enrolled for a course in alphabetical order. Students can be added and
* removed from the course list. The final list is saved to a file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bin_search_tree.h"
#include "classlist.h"
int main(void)
{
Tree class_tree = NULL; /* tree to store the class list */
tree_init(&class_tree); /* initialize the tree since no constructor */
Key student; /* key created from data read from file */
char enroll_file_name[] = "enrollment_list"; /* input file name */
char drop_file_name[] = "drop_list"; /* input file name */
char outfile_name[] = "classlist.txt"; /* output file name */
FILE *in_fp, *out_fp; /* file pointers */
/* Read enrollment records from input file */
in_fp = fopen(enroll_file_name, "r");
if (in_fp == NULL)
{
printf("Error: Could not open input file %s for reading.\n", enroll_file_name);
exit(EXIT_FAILURE);
}
while (!feof(in_fp))
{
make_key(student, in_fp);
tree_insert(&class_tree, student);
}
fclose(in_fp);
/* Read drop records from input file */
in_fp = fopen(drop_file_name, "r");
if (in_fp == NULL)
{
printf("Error: Could not open input file %s for reading.\n", drop_file_name);
exit(EXIT_FAILURE);
}
while (!feof(in_fp))
{
make_key(student, in_fp);
tree_delete(class_tree, student);
}
fclose(in_fp);
/* Write class list from tree to output file */
out_fp = fopen(outfile_name, "w");
if (out_fp == NULL)
{
printf("Error: Could not open output file %s for writing.\n", outfile_name);
exit(EXIT_FAILURE);
}
print_inorder(class_tree, out_fp);
fclose(out_fp);
printf("The class list was saved in the file %s.\n\n", outfile_name);
tree_makenull(&class_tree);
return 0;
}
/* The function make_key reads data from the input file and forms a Key from
* each record as: Lastname, Firstname Middlename
*/
void make_key(Key new_key, FILE *fp)
{
char line[LINE_LENGTH]; /* current line of text being processed */
char course_num[7] = {’\0’}; /* data to read from file and ignore */
char first[30] = {’\0’}, middle[30] = {’\0’}, last[30] = {’\0’};
/* first, middle, and last are parts of the key */
/* Read one line of data from the file */
fgets(line, LINE_LENGTH, fp);
if (!feof(fp))
{
rtrim(line);
set_empty(new_key, KEY_LENGTH);
sscanf(line, "%6c:%[^’:’]:%[^’:’]:%[^’\n’]", course_num, first, middle, last);
strcat(new_key, last);
strcat(new_key, ", ");
strcat(new_key, first);
strcat(new_key, " ");
strcat(new_key, middle);
}
}
/* The function print_inorder prints the keys from the tree in alphabetical
* order, to the file fp.
*/
void print_inorder(Tree t, FILE *fp)
{
fprintf(fp, "Class List for CS 300:\n\n");
tree_inorder(t, fp);
}
/* The function rtrim will remove a newline character from the end of a string
* if it contains one.
*/
void rtrim(char *str)
{
char *end = str + strlen(str) - 1; /* pointer to last char of string */
if (*end == ’\n’)
{
*end = ’\0’;
}
}
/* The function set_empty will set all characters of a string to the null
* character.
*/
void set_empty(char *str, int length)
{
int i; /* index for string */
for (i = 0; i < length; i++)
{
str[i] = ’\0’;
}
}
