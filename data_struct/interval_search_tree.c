#include <stdio.h>
#include <stdlib.h>

/*
 *
 * Given Input : (17, 19) - (5, 8) - (4, 8) - (15, 18) - (7, 10) - (16, 22) - (21, 24)
 *
 *                      (17, 19) -  Y_max 24
 *                      /       \
 *                     /         \  
 *        Y_max 22 (5, 8)       (21, 24) - Y_max 24
 *                 /    \
 *                /      \
 *     Y_max 8 (4, 8)    (15, 18) Y_max 22
 *                      /       \
 *                     /         \
 *                (7, 10)       (16, 22) Y_max 22
 *
 */

struct node {
    int X;
    int Y;
    int Y_max;

    struct node *left;
    struct node *right;
};

struct node * create(int X, int Y)
{
    struct node * temp = NULL;
    temp = calloc(1, sizeof(struct node));

    if(temp == NULL)
    {
        exit(-1);
    }

    temp->X = X;
    temp->Y = Y;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}


int intersects(struct node *a, struct node *b)
{
    int valid = 0;
    if((a->X <= b->Y) && (b->X <= a->Y))
    {
        return 1;
    }
    return valid;
}

/* Use the X co-ordinate as the key */
struct node * insert(struct node* head, int X, int Y)
{
    if(head == NULL) return create(X, Y);

    if(X < head->X)
    {
        head->left = insert(head->left, X, Y);
    }
    else
    {
        head->right = insert(head->right, X, Y);
    }

    if(head->Y_max < Y) head->Y_max = Y;
    return head;
}

/* Search the given X and Y in the interval search tree */
/*
    1.  if interval in node intersects query interval
    2.  if left subtree is null
    3.  if max endpoint in left subtree is less than lo, go right.
    4.  go left
*/
struct node * search(struct node* head, int X, int Y)
{   
    struct node input= {0};
    input.X =X;
    input.Y =Y;

    if(head == NULL) return NULL;

    if(intersects(head, &input))
    {
        return head;
    }

    if(head->left == NULL)
    {
        return search(head->right, X, Y);
    }
    else if(head->left->Y_max < Y)
    {
        return search(head->right, X, Y);
    }
    else
    {
        return search(head->left, X, Y);
    }

    return NULL;
}


int main()
{
    struct node * head = insert(NULL, 17, 19);

    insert(head, 17, 19);
    insert(head, 5, 8);
    insert(head, 4, 8);
    insert(head, 15, 18);
    insert(head, 7, 10);
    insert(head, 16, 22);
    insert(head, 21, 24);

    struct node *intersecting = search(head, 21, 23);

    printf("Intersection for (21, 23) --> (%d, %d)\n", intersecting->X, intersecting->Y);

    return 0;
}