#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hashmap.h"

void hashmap_fill(struct hashmap_t *hm, /*const*/char *str) {
	int i;
	while (str[0] != '\0') {
		for (i = 0; str[i] != '\0' && str[i] != ' '; ++i);
		if (str[i] == ' ') {
			str[i] = '\0';
			hashmap_add(hm, -1, str, 1);
			str[i] = ' ';
			for (i; str[i] == ' '; ++i);
		}
		else
			hashmap_add(hm, -1, str, 1);
		str = str + i;
	}
}

void hashmap_search(struct hashmap_t *hm, /*const*/char *str) {
	int i;
	while (str[0] != '\0') {
		for (i = 0; str[i] != '\0' && str[i] != ' '; ++i);
		if (str[i] == ' ') {
			str[i] = '\0';
			printf("%d ", hashmap_find(hm, -1, str));
			str[i] = ' ';
			for (i; str[i] == ' '; ++i);
		}
		else
			printf("%d\n", hashmap_find(hm, -1, str));
		str = str + i;
	}
}

void input(int *n, int *n1, char **s1, int *n2, char **s2) {
	int i, k = 0;
	char c;
	k = scanf("%d%d", n, n1);
	if (k != 2)
		abort();
	*s1 = malloc((*n1 + 1) * sizeof(char));
	if (*s1 == NULL)
		abort();
	k = scanf("%c", &c);
	if (k == 0)
		abort();
	while (isgraph(c) == 0) {
		k = scanf("%c", &c);
		if (k == 0)
			abort();
	}
	(*s1)[0] = c;
	for (i = 1; i < *n1; ++i)
		k += scanf("%c", *s1 + i);
	(*s1)[*n1] = '\0';
	if (k != *n1)
		abort();
	k = scanf("%d", n2);
	if (k != 1)
		abort();
	*s2 = malloc((*n2 + 1) * sizeof(char));
	if (*s2 == NULL)
		abort();
	k = scanf("%c", &c);
	if (k == 0)
		abort();
	while (isgraph(c) == 0) {
		k = scanf("%c", &c);
		if (k == 0)
			abort();
	}
	(*s2)[0] = c;
	for (i = 1; i < *n2; ++i)
		k += scanf("%c", *s2 + i);
	(*s2)[*n2] = '\0';
	if (k != *n2)
		abort();
}

int main() {
	int n, n1, n2;
	char *text, *keys;
	struct hashmap_t *hm;
	input(&n, &n1, &text, &n2, &keys);
	hm = hashmap_create(0, 0);
	hashmap_fill(hm, text);
	hashmap_search(hm, keys);
	hashmap_destroy(hm);
	free(text);
	free(keys);
	return 0;
}
