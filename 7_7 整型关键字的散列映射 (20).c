#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(int argc, char *argv[])
{
	int i, cnts, p, key, key_pos, *hash, *pos;

	scanf("%d%d", &cnts, &p);

	if(!(hash = malloc(p * sizeof(int))))
		exit(ENOMEM);

	memset(hash, -1, p * sizeof(int));

	if(!(pos = malloc(cnts * sizeof(int))))
		exit(ENOMEM);

	for(i = 0; i < cnts; ++i) {
		scanf("%d", &key);

		for(key_pos = key % p; hash[key_pos] != -1 && hash[key_pos] != key; key_pos = (key_pos + 1) % p)
			;

		hash[key_pos] = key;
		pos[i] = key_pos;
	}

	for(i = 0; i < cnts; ++i)
		printf("%s%d", i ? " " : "", pos[i]);

	printf("\n");

	free(hash);
	free(pos);

	return EXIT_SUCCESS;
}
