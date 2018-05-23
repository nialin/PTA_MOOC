#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


struct goods {
	int weight;
	int no;
};

int main(int argc, char *argv[])
{
	struct goods *goods;
	int i, j, goods_cnts, *boxes, box_cnts = -1;

	scanf("%d", &goods_cnts);

	if(!(goods = malloc(goods_cnts * sizeof(struct goods))))
		exit(ENOMEM);

	if(!(boxes = malloc(goods_cnts * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < goods_cnts; ++i) {
		scanf("%d", &goods[i].weight);
		boxes[i] = 100;
	}

	for(i = 0; i < goods_cnts; ++i) {
		for(j = 0; j < goods_cnts; ++j) {
			if(boxes[j] >= goods[i].weight) {
				boxes[j] -= goods[i].weight;
				goods[i].no = j + 1;

				if(box_cnts < j)
					box_cnts = j;

				break;
			}
		}
	}

	for(i = 0; i < goods_cnts; ++i)
		printf("%d %d\n", goods[i].weight, goods[i].no);

	printf("%d\n", box_cnts + 1);

	free(goods);
	free(boxes);

	return EXIT_SUCCESS;
}
