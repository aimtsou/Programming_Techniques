#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


// 
// creates linked list from input file
// 
int list_create(list_t **list, FILE *file)
{
	char buffer[BUFSIZ];
	int i = 0, len;
	
	// sanity check parameters
	if(list == NULL || file == NULL)
		return 0;
	
	// read each line of file
	while(fgets(buffer, BUFSIZ, file) != NULL)
	{
		// save line length
		len = strlen(buffer);
		
		// trim newline
		if(len > 0)
			buffer[--len] = 0;
		
		// break reading if we have a blank line
		if(len == 0) 
			break;
		
		// on first iteration allocate list with name
		if(i == 0){
			if(!list_init(list, buffer)){
				perror("failed to create linked list");
				return 0;
			}
		
		// on further interations insert items into list
		}else{
			if(!list_inserttail(*list, list_alloc_node(buffer))){
				perror("failed to insert node into linked list");
				return 0;
			}
		}
		
		// increase interation count
		i++;
	}
	return i;
}

// 
// print list out to file handle
// 
int list_print(list_t *list, FILE *file)
{
	node_t *temp;
	
	// sanity check parameters
	if(list == NULL || file == NULL)
		return 0;
	
	// output list name
	fprintf(file, "%s\n", list->name);
	
	// output each list node
	for(temp = list->head; temp; temp = temp->next)
		fprintf(file, "%s\n", temp->name);
	
	// output blank line to indicate end of list
	fprintf(file, "\n");
	
	return 1;
}

// 
// duplicate copy_len list entries from src_list at src_pos into dest_list at dest_pos
// 
int insertsublist(list_t *dest_list, int dest_pos, list_t *src_list, int src_pos, int copy_len)
{
	node_t *next, **dest, *src;
	int dest_len, src_len;
	
	// sanity check parameters
	if(dest_list == NULL || src_list == NULL)
		return 0;
	
	// get list lengths
	dest_len = list_length(dest_list);
	src_len  = list_length(src_list);
	
	// check parameters
	if(dest_len < dest_pos - 1){
		perror("not enough entries in destination to satisfy copy");
		return 0;
	}else if(src_len < src_pos + copy_len - 1){
		perror("not enough entries in source to satisfy copy");
		return 0;
	}else if(dest_pos < 1){
		perror("cannot copy to positions less than 1");
		return 0;
	}else if(src_pos < 1){
		perror("cannot copy from positions lesss than 1");
		return 0;
	}
	
	// move pointers to correct positions in linked lists
	for(dest = &dest_list->head; *dest && --dest_pos > 0; dest = &(*dest)->next);
	for(src = src_list->head; src && --src_pos > 0; src = src->next);
	
	// save next pointer from dest
	next = *dest;
	
	// duplicate each node entry for copy_len
	for(; copy_len--; src = src->next, dest = &(*dest)->next)
		*dest = list_alloc_node(src->name);
	
	// restore previous pointer in dest 
	*dest = next;
	
	return 1;
}

//
// program entry point
//
int main(int argc, char *argv[])
{
	FILE *input, *output;
	list_t *list1, *list2;
	
	// open input file for read
	input = fopen("test_data.txt", "r");
	if(input == NULL){
		perror("failed to open test_data.txt for read");
		return EXIT_FAILURE;
	}
	
	// open output file for write
	output = fopen("output.txt", "w");
	if(output == NULL){
		perror("failed to open output.txt for write");
		fclose(input);
		return EXIT_FAILURE;
	}
	
	// read list1 from input file
	if(list_create(&list1, input) == 0)
		return EXIT_FAILURE;
	
	// read list2 from input file
	if(list_create(&list2, input) == 0)
		return EXIT_FAILURE;
	
	// output list lengths
	printf("%d entries\n", list_length(list1));
	printf("%d entries\n", list_length(list2));
	printf("\n");
	
	// output lists to stdout
	list_print(list1, stdout);
	list_print(list2, stdout);
	
	// output lists to output
	list_print(list1, output);
	list_print(list2, output);
	
	// modify list1 to include part of list2
	list_name(list1, "Merged List");
	insertsublist(list1, 6, list2, 1, 7);
	
	// output modified list to stdout
	list_print(list1, stdout);
	
	// free memory allocated to lists
	list_free(&list2);
	list_free(&list1);
	
	// close previously opened files
	fclose(output);
	fclose(input);
	
	return EXIT_SUCCESS;
}
