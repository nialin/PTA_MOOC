#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define TREE_MAX_SIZE	30


struct node {
	int data;
	struct node *lchild, *rchild;
};


struct node *tree_creat(int *in, int *post, int len);
void tree_destroy(struct node **root);

void tree_level_walk(struct node *root);


struct node *tree_creat(int *in, int *post, int len)
{
	int i;
	struct node *root = NULL;

	if(len > 0) {
		if(!(root = malloc(sizeof(struct node))))
			exit(ENOMEM);

		root->data = post[len - 1];

		for(i = 0; i < len && in[i] != post[len - 1]; ++i)
			;

		root->lchild = tree_creat(in, post, i);
		root->rchild = tree_creat(in + i + 1, post + i, len - 1 - i);
	}

	return root;
}

void tree_destroy(struct node **root)
{
	if(*root) {
		tree_destroy(&(*root)->lchild);
		tree_destroy(&(*root)->rchild);

		free(*root);
		*root = NULL;
	}
}

void tree_level_walk(struct node *root)
{
	int front = 0, rear = 0;
	struct node *queue[TREE_MAX_SIZE] = {NULL}, *ptr;

	queue[rear++] = root;

	while(rear != front) {
		ptr = queue[front++];

		if(ptr->lchild)
			queue[rear++] = ptr->lchild;

		if(ptr->rchild)
			queue[rear++] = ptr->rchild;

		printf("%s%d", 1 == front ? "" : " ", ptr->data);
	}

	printf("\n");
}

int main(int argc, char *argv[])
{
	struct node *root;
	int i, cnts, in[TREE_MAX_SIZE] = {0}, post[TREE_MAX_SIZE] = {0};

	scanf("%d", &cnts);

	for(i = 0; i < cnts; ++i)
		scanf("%d", &post[i]);

	for(i = 0; i < cnts; ++i)
		scanf("%d", &in[i]);

	root = tree_creat(in, post, cnts);

	tree_level_walk(root);

	tree_destroy(&root);

	return EXIT_SUCCESS;
}
