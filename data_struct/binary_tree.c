#include <stdio.h>
#include <stdlib.h>


struct node {
	int value;
	struct node *left;
	struct node *right;
};

struct node *find_node(struct node *head, int value)
{
	if(head == NULL) return NULL;

	if(head->value == value)
		return head;

	if(value < head->value) {
		return find_node(head->left, value);
	} else if(value > head->value) {
		return find_node(head->right, value);
	}
}

/* Returns pointer to the node pointing to the value */
struct node* add_node(struct node *head, int value)
{
	struct node *temp = NULL;
	struct node *curr = NULL;

	if(head == NULL) return NULL;

	temp = find_node(head, value);

	if(temp) return temp;

	temp = malloc(sizeof(struct node));
	temp->left = NULL;
	temp->right = NULL;
	temp->value = value;

	curr = head;

	while(curr) {
		if(value < curr->value && curr->left) 
			curr = curr->left;
		else if(value > curr->value && curr->right)
			curr = curr->right;
		else 
			break;
	}

	if(curr->value > value)
		curr->left = temp;
	else
		curr->right = temp;

	return temp;
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

void print_inorder(struct node *head)
{
	if(head == NULL) return;
	if(head->left) print_inorder(head->left);
	printf("%d \t", head->value);
	if(head->right) print_inorder(head->right);
	return;
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
	struct node *parent = NULL;

	if(head == NULL) {
		printf("Empty tree \n");
		return NULL;
	}

	curr = head;

	while(curr) {
		if(value < curr->value && curr->left) {
			parent = curr;
			curr = curr->left;
		} else if(value > curr->value && curr->right) {
			parent = curr;
			curr = curr->right;
		} else {
			break;
		}
	}

	if(curr->value != value) {
		printf("Node node found %d\n", value);
		return NULL;
	}

	if(curr->left && curr->right) {
		// fix me;
	} else if(curr->left == NULL && curr->right) {
		parent = curr->right;
	} else if(curr->left == NULL && curr->left) {
		parent = curr->left;
	}
	free(curr);
	printf("Node deleted %d\n", value);
	return head;
}


int main(int argc, char const *argv[])
{	
	struct node *head = NULL;
	struct node *temp = NULL;
	head = malloc(sizeof(struct node));
	head->left = NULL;
	head->right = NULL;
	head->value = 5;
	add_node(head, 3);
	add_node(head, 9);
	add_node(head, 3);
	add_node(head, 7);
	add_node(head, 1);
	add_node(head, 4);
	add_node(head, 9);
	add_node(head, 13);
	add_node(head, 2);
	add_node(head, 0);
	add_node(head, 11);
	add_node(head, 15);

	temp = find_node(head, 6);
	if(temp) printf("found %d\n", temp->value);
	temp = find_node(head, 7);
	if(temp) printf("found %d\n", temp->value);

	print_inorder(head); printf("\n");

	printf("height %d\n", get_height(head));

	return 0;
}