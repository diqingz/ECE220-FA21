#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>
/*
Introduction paragraph: 
partner netID: staceyl2
This C program aims to read a matrix that has its information stored in a given
file and store it as a linked list (list of tuples). Each node would store the
value of the cell and its row and column.Values that are zero are would not be 
stored. We can either update a existing node if value is non-zero or insert a 
new node at proper location
 */

//helper function that sorts the tuples
int sort_tuples(sp_tuples_node* node1, sp_tuples_node* node2) {
 if ((node1->row) != (node2->row)) {
 return ((node1->row) > (node2->row));
 }
 else {
 return ((node1->col) > (node2->col));
 }
 
 return -1;
}

sp_tuples * load_tuples(char* input_file)
{
 int rows;
 int cols;
 sp_tuples* ptr = (sp_tuples*)malloc(sizeof(sp_tuples));
 FILE* fptr = fopen(input_file, "r");
 if (fptr == NULL) {
 printf("Error: %s not found", input_file);
 return NULL;
 }
 fscanf(fptr, "%d %d\n", &rows, &cols);
 ptr->m = rows;
 ptr->n = cols;
 ptr->nz = 0;
 ptr->tuples_head = NULL;
 int x;
 int y;
 double value;
 while (fscanf(fptr, "%d %d %lf\n", &y, &x, &value) == 3) {
 set_tuples(ptr, y, x, value);
 }
 //if not reaching end of file, error occured
 if (!feof(fptr)) {
 return NULL;
 }
 fclose(fptr);
 return ptr;
}

double gv_tuples(sp_tuples * mat_t,int row,int col)
{
 sp_tuples_node* node = mat_t->tuples_head;

 while(node != NULL){

 if (node->row == row && node->col == col) {
 return node->value;
 } //if current node contains the rioght value, return
 
 node = node->next;
 } //if not the value desired, move on to next node
 
 return 0;//if cannot find, return 0
}
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  if (mat_t->tuples_head == NULL) {
    if (value != 0) {
      sp_tuples_node* head = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
      head->row = row;
      head->col = col;
      head->value = value;
      head->next = NULL;//allocate values
      mat_t->tuples_head = head;
      mat_t->nz += 1;// increment count
    }
    return;
  }

 if (gv_tuples(mat_t, row, col) != 0) {
   //node exists and equals to zero--DELETE
   if (value == 0) {
     sp_tuples_node* previous = NULL;
     sp_tuples_node* node = mat_t->tuples_head;
     while(node != NULL) {
       if (node->row == row && node->col == col) {
	 if (previous == NULL) {
	   mat_t->tuples_head = node->next;
	 }

 
	 else {
	   previous->next = node->next;
	 }

	 free(node);
	 mat_t->nz -= 1;
	 return;
       }
       previous = node;
       node = node->next;
     }
 }
// node exists and not zero--update node
 else {
   sp_tuples_node* node = mat_t->tuples_head;
   while(node != NULL) {
     if (node->row == row && node->col == col) {
       node->value = value;
       return;
     }
     node = node->next;
   }
 }
 }
 else {
   //node DNE and equals zero
   if (value == 0) {
     return;
   }
   // node DNE and not equal to zero
   else {
     sp_tuples_node* previous = NULL;
     sp_tuples_node* node = mat_t->tuples_head;
     sp_tuples_node* new = 
       (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
     new->row = row;
     new->col = col;
     new->value = value;
     new->next = NULL;
     mat_t->nz += 1;
     while(node != NULL) {
       if (sort_tuples(node, new)) {
	 if (previous == NULL) {
	   new->next = node;
	   mat_t->tuples_head = new;
	 }
	 else {
	   previous->next = new;
	   new->next = node;
	 }
	 return;
       }
       previous = node;
       node = node->next;
     }
     previous->next = new;
     return;
 }
 }
 return;
}

void save_tuples(char * file_name, sp_tuples * mat_t)
{
  FILE* fptr = fopen(file_name, "w");
  fprintf(fptr, "%d %d\n", mat_t->m, mat_t->n);
  sp_tuples_node* node = mat_t->tuples_head;
  while (node != NULL) {
    fprintf(fptr, "%d %d %lf\n", node->row, node->col, node->value);
    node = node->next;
  }
  fclose(fptr);
  return;
}
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
  
  sp_tuples* retmat = (sp_tuples*)malloc(sizeof(sp_tuples));//allocate new matrix
 retmat->m = matA->m;
 retmat->n = matA->n;
 retmat->nz = 0;
 retmat->tuples_head = NULL;
 sp_tuples_node* nodeA = matA->tuples_head;
 sp_tuples_node* nodeB = matB->tuples_head;
 while (nodeA != NULL) {
   //set the values for retmat to the same as matA
   set_tuples(retmat, nodeA->row, nodeA->col, nodeA->value);
   nodeA = nodeA->next;
 }
 while (nodeB != NULL) {
   double valueret = gv_tuples(retmat, nodeB->row, nodeB->col);
   set_tuples(retmat, nodeB->row, nodeB->col, nodeB->value + valueret);
   nodeB = nodeB->next;
 }
 return retmat;
}

void destroy_tuples(sp_tuples * mat_t){
  sp_tuples_node* node = mat_t->tuples_head;
  sp_tuples_node* next = NULL;
  while (node != NULL) {
    next = node->next;
    free(node);
    node = next;
  }
  free(mat_t);//free matrix
  return;
}


