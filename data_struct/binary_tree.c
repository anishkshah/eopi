#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int value;
	struct node *left;
	struct node *right;
	int count;
};

struct node* get_node(int value)
{
	struct node *new = NULL;
	new = malloc(sizeof(struct node));
	if(new) {
		memset(new, 0 , sizeof(struct node));
		new->value = value;
	}
	return new;
}

int get_size(struct node* node)
{
	if(node) return node->count;
	return 0;
}

struct node* find_node(struct node *head, int value)
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
	if(head == NULL) return get_node(value);

	if(value > head->value) {
		head->right = add_node(head->right, value);

	} else if(value < head->value) {
		head->left = add_node(head->left, value);
	} else {
		head->value = value;
	}
	head->count = 1 + get_size(head->right) + get_size(head->right);
	return head;
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

void print_post_order(struct node *head)
{
	if(head == NULL) return;
	if(head->left) print_post_order(head->left);
	if(head->right) print_post_order(head->right);
	printf("%d \t", head->value);
	return;
}

void print_pre_order(struct node *head)
{
	if(head == NULL) return;
	printf("%d \t", head->value);
	if(head->left) print_pre_order(head->left);
	if(head->right) print_pre_order(head->right);
	return;
}


/* Delete min - del 1 from this tree
 *
 *			 5
 *			/ \
 *		   /   \
 *		  3	    9	 
 *		 /      /\
 * 		/      /  \
 * 	   1      8   11
 *	  	\		 /
 *       2		10
 *
 *	
 */

/* dont use the return value */
struct node* delete_min(struct node *root, bool free_memory)
{	
	struct node *replace = NULL;
	if(root && root->left == NULL) {
		replace = root->right;
		if(free_memory) free(root);
		return replace;
	}
	root->left = delete_min(root->left);
	root->count = 1 + get_size(root->left) + get_size(root->right);
	return root;
}

/* dont use the return value */
struct node* delete_max(struct node *root, bool free_memory)
{	
	struct node *replace = NULL;
	if(root && root->right == NULL) {
		replace = root->left;
		if(free_memory) free(root);
		return replace;
	}
	root->right = delete_max(root->right);
	root->count = 1 + get_size(root->left) + get_size(root->right);
	return root;
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

/* Returns the head of the bianry tree - Hibbard deletion  */
struct node *del_node(struct node *head, int value)
{
	struct node *curr = NULL;
	struct node *replace = NULL;

	if(head == NULL) return NULL;

	curr = head;

	if(value < curr->value && curr->left) {
		curr->left = del_node(curr->left, value);
	} else if(value > curr->value && curr->right) {
		curr->right = del_node(curr->right, value);
	} else {
		/* found the exact node*/
		if(curr->left == NULL)  {
			free(curr);
			return  curr->right;
		}

		if(curr->right == NULL)  {
			free(curr);
			return  curr->left;
		}

		/*  1: get_min right the repalcement node and save ptr
		 *  2: del the that from the location not from mremory
		 *  3: update it's children and its currents location
		 *	
		 * 	Eg: To delete 9 ->  repalce with node 11 
		 * 	and update node 11 left and right
		 */
		replace = get_min(curr->right);
		delete_min(curr->right, FALSE);
		replace->right = curr->right;
		replace->left = curr->left;
		free(curr);

	}

	return replace;
}


int main(int argc, char const *argv[])
{	
	struct node *temp = NULL;
	struct node *head = NULL;
	head = add_node(head, 5);
	add_node(head, 3);
	add_node(head, 9);
	add_node(head, 3);
	printf("Size %d\n", get_size(head));
	add_node(head, 7);
	add_node(head, 1);
	add_node(head, 4);
	add_node(head, 9);
	add_node(head, 13);
	add_node(head, 2);
	add_node(head, 0);
	delete_min(head);
	temp = add_node(head, 11);
	temp = add_node(head, 15);

	temp = find_node(head, 6);
	if(temp) printf("found %d\n", temp->value);
	temp = find_node(head, 7);
	if(temp) printf("found %d\n", temp->value);

	printf("Size %d\n", get_size(head));

	printf("print inorder\n"); print_inorder(head); printf("\n");
	printf("print pre_order\n"); print_pre_order(head); printf("\n");
	printf("print post_order\n"); print_post_order(head); printf("\n");

	printf("height %d\n", get_height(head));

	return 0;
}