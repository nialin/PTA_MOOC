#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEFT	(0)
#define RIGHT	(1)

struct symbol{
	char *name;
	size_t len, sqn, type;
};


const struct symbol symbol_tab[] = {
	{"(",	1,	0,	LEFT}, 	{")",	1,	0,	RIGHT},
	{"[",	1,	1,	LEFT},	{"]",	1,	1,	RIGHT},
	{"{",	1,	2,	LEFT},	{"}",	1,	2,	RIGHT},
	{"/*",	2,	3,	LEFT},	{"*/",	2,	3,	RIGHT}
};

void errno_msg(size_t sqn, size_t type);


void errno_msg(size_t sqn, size_t type)
{
	printf("NO\n");

	if(LEFT == type)
		printf("%s-?\n", symbol_tab[sqn * 2 + type].name);
	else
		printf("?-%s\n", symbol_tab[sqn * 2 + type].name);

	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t i, j, len, top = 0, stack[100] = {0};

	while(getline(&line, &len, stdin) != -1) {
		if(0 == strncmp(line, ".\n", 2))
			break;

		for(i = 0; i < len; ++i) {
			for(j = 0; j < sizeof(symbol_tab) / sizeof(symbol_tab[0]); ++j) {
				if(0 == strncmp(&line[i], symbol_tab[j].name, symbol_tab[j].len)) {
					if(LEFT == symbol_tab[j].type)
						stack[top++] = symbol_tab[j].sqn;
					else {
						if(0 == top)
							errno_msg(symbol_tab[j].sqn, RIGHT);

						if(symbol_tab[j].sqn != stack[--top])
							errno_msg(stack[top], LEFT);
					}

					i += symbol_tab[j].len - 1;
					break;
				}
			}
		}

		memset(line, 0, len);
	}

	if(0 == top)
		printf("YES\n");
	else
		errno_msg(stack[top], LEFT);
	
	return EXIT_SUCCESS;
}
