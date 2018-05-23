#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define TREE_MAX_SIZE	(20)

struct bst_node {
	int data;
	struct bst_node *lchild, *rchild;
};


void bst_insert(struct bst_node **root, int data);
void bst_destroy(struct bst_node **root);

void bst_level_walk(struct bst_node *root);


void bst_insert(struct bst_node **root, int data)
{
	while(*root) {
		if(data == (*root)->data)
			return ;

		if(data < (*root)->data)
			root = &(*root)->rchild;
		else
			root = &(*root)->lchild;
	}

	if(!(*root = malloc(sizeof(struct bst_node))))
		exit(ENOMEM);

	(*root)->data = data;
	(*root)->lchild = (*root)->rchild = NULL;
}

void bst_destroy(struct bst_node **root)
{
	if(*root) {
		bst_destroy(&(*root)->lchild);
		bst_destroy(&(*root)->rchild);

		free(*root);
		*root = NULL;
	}
}

void bst_level_walk(struct bst_node *root)
{
	int front = 0, rear = 0, nil_flg = 0, after_nil_flg = 0;
	struct bst_node *queue[TREE_MAX_SIZE] = {0} , *ptr;

	queue[rear++] = root;

	while(front != rear) {
		ptr	= queue[front++];

		if(ptr->lchild) {
			queue[rear++] = ptr->lchild;
			after_nil_flg = nil_flg;
		}
		else
			nil_flg = 1;

		if(ptr->rchild) {
			queue[rear++] = ptr->rchild;
			after_nil_flg = nil_flg;
		}
		else
			nil_flg = 1;
		

		printf("%s%d", 1 == front ? "" : " ", ptr->data);
	}

	printf("\n%s\n", after_nil_flg ? "NO" : "YES");
}

int main(int argc, char *argv[])
{
	struct bst_node *root = NULL;
	int i, cnts, data;

	scanf("%d", &cnts);

	for(i = 0; i < cnts; ++i) {
		scanf("%d", &data);
		bst_insert(&root, data);
	}

	bst_level_walk(root);

	return EXIT_SUCCESS;
}
