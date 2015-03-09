/*
* Mike Shiferaw, Q626Z293, Assignment 7
* File: bin_search_tree.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bin_search_tree.h"
/* Function prototypes for internal functions */
void replace_with_successor(Tree t);
void replace_with_predecessor(Tree t);
int max(int a, int b);
/* Start of functions to implement binary search tree operations */
/* sets the key a to the value of the key b */
void key_setequal(Key a, Key b)
{
strcpy(a, b);
}
/* returns true (1) if the two keys are equal or false (0) otherwise */
int key_isequal(Key a, Key b)
{
return ((strcmp(a, b) == 0) ? 1 : 0);
}
/* returns true (1) if a < b, or false (0) otherwise */
int key_lessthan(Key a, Key b)
{
int result; /* true or false */
char a_last[30] = {’\0’}, a_fstmid[60] = {’\0’}; /* split a into parts */
char b_last[30] = {’\0’}, b_fstmid[60] = {’\0’}; /* split b into parts */
sscanf(a, "%[^’,’],%s", a_last, a_fstmid);
sscanf(b, "%[^’,’],%s", b_last, b_fstmid);
result = ((strcmp(a_last, b_last) < 0) ? 1 : 0);
if (strcmp(a_last, b_last) == 0)
{
result = ((strcmp(a_fstmid, b_fstmid) < 0) ? 1 : 0);
}
return result;
}
/* tree initialization - contains what is typically in a constructor */
void tree_init(Tree *t)
{
*t = NULL;
}
/* Creates a new node for adding to a tree */
Node *tree_makenode(Key k, Node *parent)
{
Node *n = malloc(sizeof(Node));
if (n)
{
key_setequal(n->key, k);
n->parent = parent;
n->leftchild = NULL;
n->rightchild = NULL;
}
return n;
}
/* Returns the root of a tree */
Node *tree_root(Tree t)
{
return t;
}
/* Returns the parent of a node */
Node *tree_parent(Node *n, Tree t)
{
Node *x = (n ? n->parent : NULL);
return x;
}
/* Returns the left child of a node */
Node *tree_leftchild(Node *n, Tree t)
{
Node *x = (n ? n->leftchild : NULL);
return x;
}
/* Returns the right child of a node */
Node *tree_rightchild(Node *n, Tree t)
{
Node *x = (n ? n->rightchild : NULL);
return x;
}
/* Searches a tree for a key, and if found returns a pointer to the node with
* that key, otherwise returns NULL.
*/
Node *tree_search(Key k, Tree t)
{
if (t == NULL || key_isequal(t->key, k))
{
return t;
}
else if (key_lessthan(k, t->key))
{
return tree_search(k, t->leftchild);
}
else
{
return tree_search(k, t->rightchild);
}
}
/* Returns the number of children of a node */
int tree_num_children(Node *n)
{
int num;
if (!(n->leftchild) && !(n->rightchild))
num = 0;
else if (n->leftchild && n->rightchild)
num = 2;
else
num = 1;
return num;
}
/* Adds a node with a given key to a tree, ordered by the key. */
void tree_insert(Tree *t, Key k)
{
if (t == NULL || (*t) == NULL) /* add first node to tree */
{
(*t) = tree_makenode(k, NULL);
}
else if (key_isequal(k, (*t)->key)) /* don’t insert duplicates */
{
return;
}
else if (key_lessthan(k, (*t)->key)) /* insert in left subtree */
{
if ((*t)->leftchild == NULL)
{
(*t)->leftchild = tree_makenode(k, *t);
}
else
{
tree_insert(&((*t)->leftchild), k);
}
}
else /* insert in right subtree */
{
if ((*t)->rightchild == NULL)
{
(*t)->rightchild = tree_makenode(k, *t);
}
else
{
tree_insert(&((*t)->rightchild), k);
}
}
}
/* Removes a node with a particular key from a tree if the tree contains it. */
void tree_delete(Tree t, Key k)
{
Node *parent;
if (t == NULL)
{
return;
}
else if (key_lessthan(k, t->key))
{
tree_delete(t->leftchild, k);
}
else if (key_lessthan(t->key, k))
{
tree_delete(t->rightchild, k);
}
else /* found node to remove */
{
if (tree_num_children(t) == 0) /* node is a leaf */
{
parent = t->parent;
if (parent)
{
if (parent->leftchild == t)
{
parent->leftchild = NULL;
}
else if (parent->rightchild == t)
{
parent->rightchild = NULL;
}
}
free(t);
}
else if (tree_num_children(t) == 1)
{
parent = t;
if (t->leftchild)
{ /* replace node with its leftchild */
if (parent->parent == NULL)
{
t = parent->leftchild;
}
else if (parent->parent->leftchild == parent)
{
parent->parent->leftchild = parent->leftchild;
}
else
{
parent->parent->rightchild = parent->leftchild;
}
free(parent);
}
else
{ /* replace node with its rightchild */
if (parent->parent == NULL)
{
t = parent->rightchild;
}
else if (parent->parent->leftchild == parent)
{
parent->parent->leftchild = parent->rightchild;
}
else
{
parent->parent->rightchild = parent->rightchild;
}
free(parent);
}
}
else /* if node has 2 children, replace with successor or predecessor */
{
if (rand() % 2)
replace_with_successor(t);
else
replace_with_predecessor(t);
}
}
}
/* Writes the keys of the nodes of a tree in preorder. */
void tree_preorder(Node *n, FILE *fp)
{
if (!n) return;
fprintf(fp, "%s\n", n->key);
tree_preorder(n->leftchild, fp);
tree_preorder(n->rightchild, fp);
}
/* Writes the keys of the nodes of a tree in postorder. */
void tree_postorder(Node *n, FILE *fp)
{
if (!n) return;
tree_postorder(n->leftchild, fp);
tree_postorder(n->rightchild, fp);
fprintf(fp, "%s\n", n->key);
}
/* Writes the keys of the nodes of a tree inorder. */
void tree_inorder(Node *n, FILE *fp)
{
if (!n) return;
tree_inorder(n->leftchild, fp);
fprintf(fp, "%s\n", n->key);
tree_inorder(n->rightchild, fp);
}
/* returns 1 if t is empty and 0 if t is not empty */
int tree_empty(Tree t)
{
int is_empty = (t == NULL);
return is_empty;
}
/* Returns the height of a tree. */
int tree_height(Tree t)
{
int left_height, right_height;
if (!t) return -1;
left_height = tree_height(t->leftchild);
right_height = tree_height(t->rightchild);
return max(left_height, right_height) + 1;
}
/* Delete all nodes of a tree - traverse in postorder to delete each child
* before its parent.
* This version is accepted - although it doesn’t set final tree to NULL.
*
void tree_makenull(Tree t)
{
Node *parent;
if (!t) return;
tree_makenull(t->leftchild);
tree_makenull(t->rightchild);
parent = t->parent;
if (parent)
{
if (parent->leftchild == t)
{
parent->leftchild = NULL;
}
else if (parent->rightchild == t)
{
parent->rightchild = NULL;
}
e
free(t);
}
*/
/* Delete all nodes of a tree - traverse in postorder to delete each child
* before its parent.
* This version is more complete because sets tree to NULL in the end -
* requires parameter type to be changed to a pointer to a Tree.
* This version is also accepted.
*/
void tree_makenull(Tree *t)
{
Node *parent;
if (!t || !(*t)) return;
tree_makenull(&((*t)->leftchild));
tree_makenull(&((*t)->rightchild));
/* delete node pointed to by t */
parent = (*t)->parent;
if (parent)
{
if (parent->leftchild == *t)
{
parent->leftchild = NULL;
}
else if (parent->rightchild == *t)
{
parent->rightchild = NULL;
}
}
free(*t);
*t = NULL;
}
/* End of functions to implement binary search tree operations */
/* The following functions are "internal" to this file. They are used only by
* other functions in this file and are NOT part of the interface, so their
* prototypes are NOT found in the interface (.h) file.
*/
/* Replace a node in a tree with its successor */
void replace_with_successor(Tree t)
{
Node *successor;
if (t == NULL) return;
successor = t->rightchild;
while (successor && successor->leftchild)
{
successor = successor->leftchild;
}
key_setequal(t->key, successor->key);
tree_delete(successor, successor->key);
}
/* Replace a node in a tree with its predecessor */
void replace_with_predecessor(Tree t)
{
Node *predecessor;
if (t == NULL) return;
predecessor = t->leftchild;
while (predecessor && predecessor->rightchild)
{
predecessor = predecessor->rightchild;
}
key_setequal(t->key, predecessor->key);
tree_delete(predecessor, predecessor->key);
}
/* Return the maximum of two int’s */
int max(int a, int b)
{
return (a > b ? a : b);
}
