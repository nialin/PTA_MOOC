#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


struct node {
	int data;
	struct node *next;
};


struct node *list_creat(void);
void list_destroy(struct node *head);

struct node *list_mix(struct node *head1, struct node *head2);


struct node *list_creat(void)
{
	int data;
	struct node *head, *new, *ptr;

	if(!(ptr = head = malloc(sizeof(struct node))))
		exit(ENOMEM);
	head->next = NULL;

	while(scanf("%d", &data) != EOF && data >= 0) {
		if(!(new = malloc(sizeof(struct node))))
			exit(ENOMEM);

		new->data = data;
		new->next = NULL;

		ptr->next = new;
		ptr = new;
	}

	return head;
}

void list_destroy(struct node *head)
{
	struct node *del;

	while(head) {
		del = head;
		head = head->next;
		free(del);
	}
}

struct node *list_mix(struct node *head1, struct node *head2)
{
	struct node *head, *new, *ptr;

	if(!(ptr = head = malloc(sizeof(struct node))))
		exit(ENOMEM);
	head->next = NULL;

	for(head1 = head1->next, head2 = head2->next; head1 && head2; ) {
		if(head1->data == head2->data) {
			if(!(new = malloc(sizeof(struct node))))
				exit(ENOMEM);

			new->data = head1->data;
			new->next = NULL;

			ptr->next = new;
			ptr = new;

			head1 = head1->next;
			head2 = head2->next;
		}
		else if(head1->data < head2->data)
			head1 = head1->next;
		else
			head2 = head2->next;
	}

	return head;
}

int main(int argc, char *argv[])
{
	struct node *head1, *head2, *head3, *ptr;

	head1 = list_creat();
	head2 = list_creat();

	head3 = list_mix(head1, head2);

	ptr = head3->next;

	if(!ptr)
		printf("NULL\n");
	else {
		printf("%d", ptr->data);

		for(ptr = ptr->next; ptr; ptr = ptr->next)
			printf(" %d", ptr->data);

		printf("\n");
	}

	list_destroy(head1);
	list_destroy(head2);
	list_destroy(head3);

	return EXIT_SUCCESS;
}
