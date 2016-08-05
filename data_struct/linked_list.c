#include <stdio.h>

#define SUCCESS	0;
#define FAILED	-1;

struct node {
	int value;
	struct node *next;
}

/* Returns the pointer to the new node */
struct node *add_node(struct node *head ,int value)
{	
	struct node *temp = NULL;
	struct node *curr = NULL;
	
	curr = head;
	
	temp = malloc(sizeof(struct node));
	if(temp == NULL) {
		printf("Failed to allocate memory\n");
		return NULL;
	}
	temp->next = NULL;
	temp->value = value;
	if(head == NULL) return temp;
	
	while(head->next != NULL) {
		curr = curr->next;
	}
	
	curr->next = temp;
	return temp;
}

/* Returns the head of the linked list after delete */
struct node *del_node(struct node *head, int value)
{	
	struct node *curr = head;
	struct node *prev = NULL;
	
	if(head == NULL) {
		printf("List empty \n");
		return NULL;
	}
	
	if(head->next == NULL) {
		if(head->value == value) {
			/* List is now empty */
			free(head);
			return NULL;
		} else {
			return head;
		}
	}

	while(curr && curr->value != value) {
		prev = curr;
		curr = curr->next;
	}
	
	if(curr && curr->value == value){
		prev->next = curr->next;
		free(curr);
		curr == NULL;
	}
	return head;
}

/* Return the head of the linked list after delete */
struct node *del_node_at_pos(struct node *head, int pos)
{	
	struct new_head = head;
	struct node *curr = head;
	struct ndoe *prev = NULL;
	int count = 0;	

	if(head == NULL) {
                printf("List empty"\n);
                return NULL;
        }
	
	if((head->next == NULL) && (pos == 1)) {
                /* List is now empty */
                free(head);
                return NULL;            
       	} else {
        	return head;
        }
	
	if(pos == 1) {
		new_head = head->next;
		free(head);
		return new_head;
	}
	while(curr) {
		count++;
		if(count == pos) break;
		prev = curr;
		curr = curr->next;
	}
	
	/* make sure pos is not greater than no of elements in the list*/
	if(count == pos) {
		prev->next = curr->next;
		free(curr);
	}
	retun new_head;
}
}

/* print everthing from the head of list */
void print_all(struct node *head)
{
	struct node *curr = head;
	
	if(head == NULL) printf("Empty list\n");
	
	printf("Start of list \n");
	while(head->next!=NULL) {
		printf("value is %d \t", curr->value);
		curr = curr->next;
	}
	printf("\nEnd of list\n")
}


int main()
{
	/* add test later on */
	return 0;
}
