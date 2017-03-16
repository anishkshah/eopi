#include <stdio.h>
#include <stdlib.h>

#define SUCCESS	0;
#define FAILED -1;

/*
 *      Single Linked LIST
 *
 *	|head| -> | n1 | -> | n2 | -> | n3 | ->
 *
 */

struct node {
	int value;
	struct node *next;
};

/* allocate a new node for the list */
struct node *list_get_node(int value)
{
	struct node *node = NULL;
	node = calloc(1, sizeof(struct node));
	if(node == NULL) {
		printf("Failed to allocate memory\n");
		exit(1);
	}

	node->value = value;
	return node;
}

/* Adds the node to the tail of the list and return the new node */
struct node* list_add_tail(struct node *head, int value)
{	
    struct node *curr = NULL;
    struct node *prev = NULL;

    curr = list_get_node(value);
	if(head == NULL){
	   return curr;
	}

    while(head) {
        prev = head;
        head = head->next;
    }

    prev->next = curr;
	return curr;
}

/* Adds the node to the head of the list and return the new head */
struct node* list_add_head(struct node *head, int value)
{   
    struct node *curr = NULL;

    curr = list_get_node(value);
    if(head == NULL){
       return curr;
    }

    curr->next = head;
    return curr;
}

/* Returns 0 on success and -1 on failure after delete */
int list_del_node(struct node *head, int value)
{	
	struct node *curr = NULL;
	struct node *prev = NULL;
	
	if(head == NULL) {
		printf("List empty \n");
		return -1;
	}

	curr = head;

	while(curr && curr->value != value) {
		prev = curr;
		curr = curr->next;
	}
	
	if(curr && curr->value == value){
		prev->next = curr->next;
		curr->next = NULL;
        free(curr);
		curr == NULL;
	}
	return 0;
}

/* Return 0 on success and -1 on failure after delete */
int list_del_node_at_pos(struct node *head, int pos)
{	
	struct node *curr = NULL;
	struct node *prev = NULL;
	int count = 0;
	
	if(head == NULL) {
		printf("Inavlid list \n");
		return -1;
	}

	curr = head->next;
	prev = head;

	while(curr) {
		count++;
        prev = curr;
        curr = curr->next;
		if(count == pos) break;
	}
	if(count == pos) {
		prev->next = curr->next;
		free(curr);
	}
	return 0;
}

/* print everthing from the head of list */
void list_print_all(struct node *head)
{
	struct node *curr = NULL;
	
	if(head == NULL) {
		printf("Invalid list head\n");
		return;
	}

	curr =  head->next;

	printf("Start of list \n");
	while(curr != NULL) {
		printf("value is %d \t", curr->value);
		curr = curr->next;
	}
	printf("\nEnd of list\n");
	return;
}


int main()
{
	struct node *head = NULL;

	int ret = 0;
	head = list_get_node(9);

	list_add_tail(head, 5);
	list_add_tail(head, 7);
	list_add_tail(head, 8);
	list_add_tail(head, 9);
	list_add_tail(head, 3);


	list_print_all(head);

	list_del_node_at_pos(head, 2);

	list_print_all(head);

	list_del_node(head, 9);
	list_del_node(head, 5);
	list_del_node(head, 7);

	list_print_all(head);

	return ret;
}
