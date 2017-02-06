/*
 *	Red black tree: LEFT leaning RED links
 * 
 * 	Rules:
 *		1.	No node has two red links connected to it. 
 * 		2.  Every path form the root to the null link has same number of black links.
 * 		3.  Red links lean left.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BLACK_NODE 0
#define RED_NODE 1
#define boolean int

struct node {
    int key;
    int value;
    struct node *right;
    struct node *left;
    boolean color;			// color of the parent link
};

struct node * get_node(struct node* root, int key)
{
    if(root == NULL) return NULL;

	if(root->key == key)
		return root;

	if(key < root->key) {
		return find_node(root->left, key);
	} else if(key > root->key) {
		return find_node(root->right, key);
    }
}

boolean is_red(struct node * node)
{
	if(node == NULL) return 0;
	return node->color;
}

boolean is_black(struct node * node)
{
	if(node == NULL) return 0;
	return !(node->color);
}

/*
 *	rotate_left : RED link to left
 *
 *	in - given node to be rotated
 *  ret - new root instead of in
 *
 *		E  					       I
 *	   / \_____\    red     /____ / \
 *	  /   \    /    link    \    /   \
 *	 B	   I 					E     Z
 * 		   /\				   / \
 *		  /  \				  /   \
 *        F   Z				 B     F
 */

struct node* rotate_left(struct node *in)
{
	/* in = I and temp = E */
	struct node *temp = NULL;

    if(in == NULL) return NULL;
    /* Should be true */
	assert(is_red(root->right));

    temp = in->right;
	temp->left = in;
	in->right = temp->left;
	temp->color = in->color;
	in->color = RED_NODE;
	return temp;
}


/*
 *	rotate_right : RED link to right
 *
 *	in - given node to be rotated
 *  ret - new root instead of in
 *
 *						I       		E
 *	     red 	 /____ / \			   / \______\  red
 *	     link    \    /   \           /   \     /  link
 *	       			 E     Z         B 	   I
 * 		            / \					  / \
 *	    		   /   \				 /   \
 *          	  B     F               F     Z
 */

struct node* rotate_right(struct node *in)
{
	/* in = I and temp = E */
	struct node *temp = NULL;

    if(in == NULL) return NULL;
    /* Should be true */
    assert(is_red(root->left));

	temp = in->left;
	temp->right = in;
	in->left = temp->right;
	temp->color = in->color;
	in->color = RED_NODE;
	return temp;
}

/*
 *  flip_colors: change the colors of a temp four node root
 *               The root has two red links to the child
 *
 *          Black link---|                      red link ---|
 *                       I                                  I
 *                      / \                                / \
 *       red     /____ /   \ ______\ red      black /____ /   \________\ black 
 *       link    \    /     \      / link      link \    /     \       / link
 *                   E       T                          E       T
 *                  / \     / \                        / \     / \
 *                 /   \   /   \                      /   \   /   \           
 *                B     F K     Z                    B     F K     Z       
 */
void flip_colors(struct node *root)
{
    assert (!is_red(root));
    assert (is_red(root->left));
    assert (is_red(root->right));
    root->color = RED_NODE;
    root->left->color = BLACK_NODE;
    root->right->color = BLACK_NODE;
}

struct node* new_node(int key, int value, boolean color)
{
    struct node *temp = NULL;
    temp = malloc(sizeof(struct node));
    if(temp == NULL) return NULL;

    temp->left = NULL;
    temp->right = NULL;
    temp->color = color;
    temp->value = value;
    temp->key = key;
    return temp;
}

/* Returns pointer to the new node pointing to the value */
struct node* insert_node(struct node *head, int key, int value)
{
    if(head == NULL) return get_node(key, value, RED_NODE);

    if(key > head->key) {
        head->right = insert_node(head->right, key, value);

    } else if(value < head->value) {
        head->left = insert_node(head->left, key, value);

    } else {
        head->value = value;

    }

    /* Left leaning RED-BLACK tree*/
    if(is_red(head->right) && is_black(head->left)) {
        head = rotate_left(head);
    }
    if(is_red(head->right) && is_red(head->left->left)) {
        head = rotate_right(head);
    }
    if(is_red(head->right) && is_red(head->left)) {
        head = flip_colors(head);
    }

    return head;
}
