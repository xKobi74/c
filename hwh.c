#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct chain_t {
	char *key;
	int count;
	struct chain_t *next;
};

struct hashmap_t {
	int r, p;
	int size;
	struct chain_t **map;
};

struct chain_t *chain_create(const char *key, int count) {
	struct chain_t *ch = malloc(sizeof(struct chain_t));
	if (ch == NULL)
		abort(); 
	ch->next = NULL;
	ch->count = count;
	ch->key = malloc((strlen(key) + 1) * sizeof(char));
	if (ch->key == NULL)
		abort();
	strcpy(ch->key, key);
	return ch;
}

struct hashmap_t *hashmap_create(int size) {
	struct hashmap_t *hm = malloc(sizeof(struct hashmap_t));
	if (hm == NULL)
		abort();
	hm->size = size;
	hm->map = calloc(size, sizeof(struct chain_t *));
	if (hm->map == NULL)
		abort();
	return hm;
}

void chain_destroy(struct chain_t *ch) {
	if (ch == NULL)
		return;
	chain_destroy(ch->next);
	free(ch->key);
	free(ch);
}

void hashmap_destroy(struct hashmap_t *hm) {
	int i;
	for (i = 0; i < hm->size; ++i)
		chain_destroy(hm->map[i]);
	free(hm->map);
	free(hm);
}

void chain_add(struct chain_t *cur, const char *key, int count) {
	struct chain_t *pr = NULL;
	for (cur; cur != NULL && strcmp(key, cur->key) != 0; pr = cur, cur = cur->next);
	if (cur == NULL)
		pr->next = chain_create(key, count);
	else
		cur->count += count;
}

int nstr_hash(const struct hashmap_t *hm, const char *key, int n) {
	int i, mult = 1, hash = 0;
	for (i = 0; i < n; ++i) {
		hash = (hash + (mult * key[i]) % hm->p) % hm->p;
		mult = (mult * hm->r) % hm->p;
	}
	return hash;
}

void hashmap_add(struct hashmap_t *hm, int hash, const char *key, int count) {
	if (hash < 0)
		hash = nstr_hash(hm, key, strlen(key));
	if (hm->map[hash] == NULL)
		hm->map[hash] = chain_create(key, count);
	else
		chain_add(hm->map[hash], key, count); 
}

int chain_find(const struct chain_t *ch, const char *key) {
	for (ch; ch != NULL && strcmp(key, ch->key) != 0; ch = ch->next);
	if (ch == NULL)
		return 0;
	return ch->count;
}

int hashmap_find(const struct hashmap_t *hm, int hash, const char *key) {
	if (hash < 0)
		hash = nstr_hash(hm, key, strlen(key));
	return chain_find(hm->map[hash], key);
}

struct hashmap_t *hashmap_init(int n) {
	struct hashmap_t *hm;
	int p = 10000;	
	hm = hashmap_create(p);
	hm->p = p;
	hm->r = 132;
	return hm;
}

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
	int n, n1, n2, i;
	char *text, *keys;
	struct hashmap_t *hm;
	input(&n, &n1, &text, &n2, &keys);
	hm = hashmap_init(n);
	hashmap_fill(hm, text);
	hashmap_search(hm, keys);
	hashmap_destroy(hm);
	free(text);
	free(keys);
	return 0;
}
