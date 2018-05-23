#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


struct node {
	int data;
	struct node *next;
};


int main(int argc, char *argv[])
{
	int i, k, data;
	struct node *head, *new, *ptr, *kptr;

	scanf("%d", &k);

	if(!(head = malloc(sizeof(struct node))))
		exit(ENOMEM);

	ptr = head;

	while(scanf("%d", &data) != EOF && data >= 0) {
		if(!(new = malloc(sizeof(struct node))))
			exit(ENOMEM);

		new->data = data;
		new->next = NULL;

		ptr->next = new;
		ptr = new;
	}

	for(i = 0, ptr = head; i < k && ptr; ++i, ptr = ptr->next)
		;

	if(!ptr)
		printf("NULL\n");
	else {
		for(kptr = head; ptr; ptr = ptr->next, kptr = kptr->next)
			;

		printf("%d\n", kptr->data);
	}

	while(head) {
		ptr = head;
		head = head->next;

		free(ptr);
	}

	return EXIT_SUCCESS;
}
