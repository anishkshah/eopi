#include <stdio.h>
#include <stdlib.h>


struct node {
	int value;
	struct node *left;
	struct node *right;
}

/* Returns head of the tree after adding the vaue in the tree*/
struct node* add_node(struct node *head, int value)
{
	struct node *temp = NULL;
	struct node *curr = NULL;

	temp = find_node(head, value);
	if(temp) {
		printf("Value %d exists\n", value);
		return head;
	}

	temp = malloc(sizeof(struct node));
	temp->left = NULL;
	temp->right = NULL;
	temp->value = value;

	if(head == NULL){
		return temp;
	}

	curr = head;

	while(curr) {
		if(value < curr->value && curr->left)
			curr = curr->left;
		else if(value > curr->value && curr->right)
			curr = curr->right;
	}

	if(curr->value < value)
		curr->left = temp;
	else
		curr->right = temp;

	return head;
}


struct node *find_node(struct node *head, int value)
{
	struct node* curr = NULL;

	if(head == NULL)
		return NULL;

	curr = head;

	while(curr) {
		if(value < curr->value && curr->left)
			curr = curr->left;
		else if(value > curr->value && curr->right)
			curr = curr->right;
	}

	if(curr->value == value)
		return curr;
	else
		return NULL;
}



/*   Input stream: 5 3 9 7 1 13 2 0 11 15
 *
 *			 5
 *			/ \
 *		   /   \
 *		  3	    9	 
 *		 /      /\
 * 		/      /  \
 * 	   1      8   11
 *	  /\     /
 *   0  2   7
 *		   /
 *		  6	
 */

int get_height(struct node *head)
{
	int height = 0;
	int height_left = 0;
	int height_right = 0;

	if(head == NULL) return height;
	height = 1;
	height_left = height + get_height(head->left);
	height_right = height +  get_height(head->right);

	if(height_right > height_left)
		return height_right; 
	else 
		return height_left;
}

void print_tree(struct node *head)
{	
	struct node *curr = NULL;

	if(head == NULL)
		printf("Invalid tree\n");

	curr = head
	while(curr) {

	}

}

/*   Input stream: 5 3 9 7 1 4 13 2 0 11 15
 *
 *			 5
 *			/ \
 *		   /   \
 *		  3	    9	 
 *		 /\     /\
 * 		/  \   /  \
 * 	   1    4 7   13  
 *	  /\    /  \   /\
 *   0  2       8 11 15  
 *
 */

/* Returns the head of the bianry tree */
struct node *del_node(struct node *head, int value)
{
	struct node *curr = NULL;
	struct node *prev = NULL;

	if(curr == NULL) {
		printf("Element value %d  not found\n", value );
		return head;
	}

	curr = head;

	while(curr) {
		if(value < curr->value && curr->left) {
			prev = curr;
			curr = curr->left;
		} else if(value > curr->value && curr->right) {
			prev = curr;
			curr = curr->right;
		}
	}

	if(curr->value != value) {
		printf("Node node found %d\n", value);
		return NULL
	}

	if(curr->left && curr->right) {
		// fix me;
	} else if(curr->left == NULL && curr->right) {
		prev = curr->right;
	}else if(curr->left == NULL && curr->left) {
		prev = curr->left;
	}
	free(curr);
	printf("Node deleted %d\n", value);
	return head;
}


int main(int argc, char const *argv[])
{
	return 0;
}