#ifndef _list_h_
#define _list_h_

typedef struct node node_t;
struct node {
	char   *name;
	node_t *next;
};

typedef struct list {
    node_t *head;
	node_t *tail;
	char   *name;
} list_t;

int list_init(list_t **list, char *name);
int list_name(list_t *list, char *name);
int list_free(list_t **list);
int list_length(list_t *list);
int list_inserttail(list_t *list, node_t *node);
int list_inserthead(list_t *list, node_t *node);
node_t *list_alloc_node(char *name);
int list_free_node(node_t **node);

#endif // _list_h_
