#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int median(int *nums1, int *nums2, int cnts);


int median(int *nums1, int *nums2, int cnts)
{
	int mid;

	while(cnts > 2) {
		mid = (cnts - 1) / 2;

		if(nums1[mid] == nums2[mid])
			return nums1[mid];

		if(nums1[mid] < nums2[mid])
			nums1 += mid;
		else
			nums2 += mid;

		cnts -= mid;
	}

	if(2 == cnts)
		*nums1 < *nums2 ? ++nums1 : ++nums2;

	return *nums1 < *nums2 ? *nums1 : *nums2;
}

int main(int argc, char *argv[])
{
	int i, cnts, *nums1, *nums2;

	scanf("%d", &cnts);

	if(!(nums1 = malloc(cnts * sizeof(int))))
		exit(ENOMEM);

	if(!(nums2 = malloc(cnts * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnts; ++i)
		scanf("%d", &nums1[i]);

	for(i = 0; i < cnts; ++i)
		scanf("%d", &nums2[i]);

	printf("%d\n", median(nums1, nums2, cnts));

	free(nums1);
	free(nums2);

	return EXIT_SUCCESS;
}
