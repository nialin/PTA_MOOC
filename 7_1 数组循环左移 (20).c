#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void reverse(int *nums, int cnts);


void reverse(int *nums, int cnts)
{
	int i, tmp;

	for(i = 0; i < cnts / 2; ++i) {
		tmp = nums[i];
		nums[i] = nums[cnts - 1 - i];
		nums[cnts - 1 - i] = tmp;
	}
}

int main(int argc, char *argv[])
{
	int i, m, n, *nums;

	scanf("%d%d", &n, &m);

	if(!(nums = malloc(n * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < n; ++i)
		scanf("%d", &nums[i]);

	reverse(nums, m % n);
	reverse(nums + m % n, n - m % n);
	reverse(nums, n);

	for(i = 0; i < n; ++i)
		printf("%s%d", i ? " " : "", nums[i]);
	printf("\n");

	free(nums);

	return EXIT_SUCCESS;
}
