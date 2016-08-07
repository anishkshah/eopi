#include <stdio.h>
#include <stdlib.h>

#define SUCCESS	0;
#define FAILED	-1;

struct node {
	int value;
	struct node *next;
};

struct node *init_list()
{
	struct node *head = NULL;

	head = malloc(sizeof(struct node));
	if(head == NULL) {
		printf("Failed to allocate memory\n");
		return NULL;
	}

	return head;
}

int cleanup_list(struct node * head)
{
	if(head == NULL) {
		printf("Invalid head pointer\n");
		return -1;
	}

	if(head->next != NULL) {
		printf("List not empty\n");
		return -1;
	}

	free(head);
	printf("List deleted\n");
	return 0;

}


/* Returns 0 on success else -1 */
int add_node(struct node *head ,int value)
{	
	struct node *temp = NULL;
	struct node *curr = NULL;
    struct node *prev = NULL;

	if(head){
		curr = head;
	} else {
		printf("Invalid head list not initalized\n");
		return -1;
	}

	temp = malloc(sizeof(struct node));
	if(temp == NULL) {
		printf("Failed to allocate memory\n");
		return -1;
	}

	temp->next = NULL;
	temp->value = value;
	
	while(curr) {
		prev = curr;
		curr = curr->next;
	}
	
	prev->next = temp;
	return 0;
}

/* Returns 0 on success and -1 on failure after delete */
int del_node(struct node *head, int value)
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
int del_node_at_pos(struct node *head, int pos)
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
void print_all(struct node *head)
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
	head = init_list();

	add_node(head, 5);
	add_node(head, 7);
	add_node(head, 8);
	add_node(head, 9);
	add_node(head, 3);


	print_all(head);

	del_node_at_pos(head, 2);

	print_all(head);

	del_node(head, 9);
	del_node(head, 5);
	del_node(head, 7);

	cleanup_list(head);

	print_all(head);

	return ret;
}
