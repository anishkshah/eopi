#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

struct node {
	int 		value;
	int 		count;				// number of child nodes
	struct node *left;
	struct node *right;
};

struct node* get_node(int value)
{
	struct node *new = NULL;
	new = calloc(1, sizeof(struct node));
	if(new) {
		new->value = value;
	}
	return new;
}

int get_size(struct node* node)
{
	if(node) return node->count;
	return 0;
}

/* Returns the node pointer with the value else NULL */
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
 *           5
 *          / \
 *         /   \
 *        3	    9	 
 *       /      /\
 *      /      /  \
 *     1      8   11
 *    / \    /
 *   0   2  7
 *         /
 *        6	
 */

int get_height(struct node *head)
{
	int height_left = 0;
	int height_right = 0;

	if(head == NULL) return 0;
	height_left = 1 + get_height(head->left);
	height_right = 1 +  get_height(head->right);

	if(height_right > height_left) {
		return height_right;
	} else {
		return height_left;
	}
}

/*
 *  Get the number of nodes < key/value.
 *            S  (8) ->size
 *           / \
 *          /   \
 *         /     \
 *     (4)E       W(3)
 *       / \      /\
 *      /   \    /  \
 *  (2)A     H  T    Z (1)
 *	    \
 *       C
 *
 *  For E -> rank is get_size(A) = 2
 */
int get_rank(struct node *head, int value)
{
	if(head ==  NULL) return 0;

	if(value < head->value) {
		return get_rank(head->left, value);
	} else if(value > head->value) {
		return 1 + get_size(head->left) + get_rank(head->right, value);
	} else {
		// value == head->value
		return get_size(head->left);
	}
}

/*
 *    Tree Traversal
 *           7
 *          / \
 *         /   \
 *        4     8	 
 *       / \
 *      /   \
 *     1     6
 *
 *   Depth first search
 */

/*  Inorder (Left, Root, Right) : 1 4 6 7 8     */
void print_inorder(struct node *head)
{
	if(head == NULL) return;
	if(head->left) print_inorder(head->left);
	printf("%d \t", head->value);
	if(head->right) print_inorder(head->right);
	return;
}

/*  Postorder (Left, Right, Root) : 1 6 4 8 7   */
void print_post_order(struct node *head)
{
	if(head == NULL) return;
	if(head->left) print_post_order(head->left);
	if(head->right) print_post_order(head->right);
	printf("%d \t", head->value);
	return;
}

/*  Preorder (Root, Left, Right) : 7 4 1 6 8    */
void print_pre_order(struct node *head)
{
	if(head == NULL) return;
	printf("%d \t", head->value);
	if(head->left) print_pre_order(head->left);
	if(head->right) print_pre_order(head->right);
	return;
}

/*
 * Tree Traversal Breath First Search/ Level Order Traversal
 */

struct node_fifo {
	void *data;
	struct node_fifo *next;
};

void put_fif0(struct node_fifo **queue, struct node *bt_node)
{
	struct node_fifo *new = NULL;
	new = calloc(1, sizeof(struct node_fifo));
	new->data = bt_node;
	new->next = *queue;
	*queue = new;

}

void get_fif0(struct node_fifo **queue, struct node *bt_node)
{
	struct node_fifo *new_head = NULL;
	struct node_fifo *curr_head = *queue;
	void *data = NULL;

	if(curr_head == NULL) return;

	data = curr_head->data;
	new_head =  curr_head->next;
	free(curr_head)
	*queue = new_head;
}

void bfs(struct node* head)
{
    struct node *traveler = head;
    struct node **queue = NULL;

    while(traveler) {
        printf("%d\n", traveler->value);

        if(traveler->left) {
            put_fif0(queue, traveler->left);
        }

        if(traveler->right) {
            put_fif0(queue, traveler->right);
        }

        traveler = (struct node *)get_fifo(queue);
    }
}

/* Delete min - del 1 from this tree
 *
 *           5
 *          / \
 *         /   \
 *        3     9	 
 *       /      /\
 *      /      /  \
 *     1      8   11
 *	    \        /
 *       2     10
 */

/* dont use the return value */
struct node* get_min(struct node *root)
{	
    struct node *min = NULL;
        if(root) {
            if(root->left == NULL) {
                min = root;
		} else {
			min = get_min(root->left);
		}
	}

	return min;
}

/* dont use the return value */
struct node* delete_min(struct node *root, int free_memory)
{	
	struct node *replace = NULL;
	if(root && root->left == NULL) {
		replace = root->right;
		if(free_memory) free(root);
		return replace;
	}
	root->left = delete_min(root->left, free_memory);
	root->count = 1 + get_size(root->left) + get_size(root->right);
	return root;
}

/* dont use the return value */
struct node* delete_max(struct node *root, int free_memory)
{	
	struct node *replace = NULL;
	if(root && root->right == NULL) {
		replace = root->left;
		if(free_memory) free(root);
		return replace;
	}
	root->right = delete_max(root->right, free_memory);
	root->count = 1 + get_size(root->left) + get_size(root->right);
	return root;
}

/*   Input stream: 5 3 9 7 1 4 13 2 11
 *
 *           5
 *          / \
 *         /   \
 *        3     9	 
 *       /\     /\
 *      /  \   /  \
 *     1    4 7    13  
 *     \       \   /
 *      2       8 11
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

		/*  1: get_min from curr's right, this is the repalcement node so save ptr
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

	head->count = get_size(head->left) + get_size(head->right) + 1;
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
	delete_min(head, TRUE);
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

	del_node(head, 9);
	printf("print inorder\n"); print_inorder(head); printf("\n");
	
	bfs(head);
	return 0;
}
