#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


// 
// allocate a linked list and give it a name
// 
int list_init(list_t **list, char *name)
{
	list_t *temp = (list_t *)malloc(sizeof(list_t));
	
	// if we allocated ok then fill in structure
	if(temp != NULL){
		temp->head = temp->tail = NULL;
		temp->name = strdup(name);
	}
	
	// set new list pointer
	*list = temp;
	
	return (temp != NULL);
}

// 
// rename linked list
// 
int list_name(list_t *list, char *name)
{
	// sanity check parameters
	if(list == NULL || name == NULL)
		return 0;
	
	// free old name and duplicate new one
	free(list->name);
	list->name = strdup(name);
	
	return 1;
}

// 
// free previously allocated linked list
// 
int list_free(list_t **list)
{
	list_t *temp;
	node_t *next;
	
	// sanity check parameters
	if(list == NULL || *list == NULL)
		return 0;
	
	// free each node starting from head
	for(temp = *list; temp->head; temp->head = next){
		next = temp->head->next;
		list_free_node(&temp->head);
	}
	
	// free list structure itself
	free(temp->name);
	free(temp);
	
	// clear list pointer
	*list = NULL;
	
	return 1;
}

// 
// returns the number of nodes in a linked list
// 
int list_length(list_t *list)
{
	node_t *temp;
	int count;
	
	// sanity check parameters
	if(list == NULL)
		return 0;
	
	// interate though linked list keeping count
	count = 0;
	for(temp = list->head; temp; temp = temp->next)
		count++;
	
	return count;
}

int list_inserttail(list_t *list, node_t *node)
{
	// sanity check parameters
	if(list == NULL || node == NULL)
		return 0;
	
	// if tail then set our node as the next
	if(list->tail != NULL)
		list->tail->next = node;
	
	// if head has not been set we must also set it
	if(list->head == NULL)
		list->head = node;
	
	// add ourselves as tail node
	list->tail = node;
	
	return 1;
}

int list_inserthead(list_t *list, node_t *node)
{
	// sanity check parameters
	if(list == NULL || node == NULL)
		return 0;
	
	// if head then set our node as the next
	if(list->head != NULL)
		node->next = list->head;
	
	// if tail has not been set we must also set it
	if(list->tail == NULL)
		list->tail = node;
	
	// add ourselves as head node
	list->head = node;
	
	return 1;
}

// 
// allocate a node structure with given name
// 
node_t *list_alloc_node(char *name)
{
	node_t *node = (node_t *)malloc(sizeof(node_t));
	
	// if we allocated ok then fill in structure
	if(node != NULL){
		node->name = strdup(name);
		node->next = NULL;
	}
	
	return node;
}

int list_free_node(node_t **node)
{
	// sanity check parameters
	if(node == NULL || *node == NULL)
		return 0;
	
	// free node structure itself
	free((*node)->name);
	free(*node);
	
	// clear node pointer
	*node = NULL;
	
	return 1;
}

