#include <stdio.h>
#include <stdlib.h>

#define SUCCESS	0;
#define FAILED -1;

/*
 *	Double Linked LIST
 *
 *	|head| <-> | n1 | <-> | n2 | <-> | n3 | <-> | n4 | ->
 *
 */


struct node {
	int value;
	struct node *next;
	struct node *prev;
};

/* Allocates and returns a new node from the list */
struct node *list_get_node(int value)
{
	struct node *node = NULL;
	node = malloc(sizeof(struct node));
	if(node == NULL) {
		printf("Failed to allocate memory\n");
		exit(1);
	}

	node->next = node->prev;
	node->prev = node->next;
	node->value = value;
	return node;
}

/* Clean's up the head node of the linked list */
int list_put_node(struct node * node)
{
	if(node == NULL) {
		printf("Invalid node pointer\n");
		return -1;
	}

	if(node->next = node->prev) {
		printf("Head of the list\n");
		return -1;
	}
	free(node);
	return 0;
}


/* Adds the node to the list */
int list_add_tail(struct node *head, int value)
{	
	struct node *curr = NULL;
    struct node *prev = NULL;
    struct node *next = NULL;

    /*
     *
     * |head| <-> | n1 | <-> | n2 | <-> | n3 | <-> | n4 |<- | n5 | -> |head|
 	 */
	if(!head){
		printf("Invalid head list not initalized\n");
		return -1;
	}

	curr = list_get_node(value);

	prev = head->prev;
	next = head;

	prev->next = curr;
	next->prev = curr;
	curr->next = next;
	curr->prev = prev;
	
	prev->next = curr;
	return 0;
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

	curr = head->next;
	prev = head;

	while(curr && curr->value != value) {
		prev = curr;
		curr = curr->next;
	}
	
	if(curr && curr->value == value){
		prev->next = curr->next;
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

	if(head->next == NULL) {
		printf("No elemets in the list \n");
		return -1;
	}

	curr = head->next;
	prev = head;

	while(curr) {
		count++;
		if(count == pos) break;
		prev = curr;
		curr = curr->next;
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
