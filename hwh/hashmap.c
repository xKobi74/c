#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chain.h"
#include "hashmap.h"

const int P = 10000, R = 132; //default setting of hashmap 

struct hashmap_t {
	int r, p;
	struct chain_t *tale, *head;
	struct chain_t **map;
	int *mapn;
};

struct hashmap_t *hashmap_create(int p, int r) {
	struct hashmap_t *hm = malloc(sizeof(struct hashmap_t));
	if (hm == NULL)
		abort();
	if (p == 0 || r == 0) {
		p = P;
		r = R;
	}
	hm->p = p;
	hm->r = r;
	hm->tale = NULL;
	hm->head = NULL;
	hm->map = calloc(hm->p, sizeof(struct chain_t *));
	if (hm->map == NULL)
		abort();
	hm->mapn = calloc(hm->p, sizeof(int));
	if (hm->mapn == NULL)
		abort();
	return hm;
}

void hashmap_destroy(struct hashmap_t *hm) {
	int i;
	chain_destroy(hm->tale);
	free(hm->map);
	free(hm->mapn);
	free(hm);
}

int nstr_hash(const struct hashmap_t *hm, const char *key, int n) {
	int i, mult = 1, hash = 0;
	for (i = 0; i < n; ++i) {
		hash = (hash + (mult * key[i]) % hm->p) % hm->p;
		mult = (mult * hm->r) % hm->p;
	}
	return hash;
}

int str_hash(const struct hashmap_t *hm, const char *key) {
	int i, mult = 1, hash = 0;
	for (i = 0; key[i] != '\0'; ++i) {
		hash = (hash + (mult * key[i]) % hm->p) % hm->p;
		mult = (mult * hm->r) % hm->p;
	}
	return hash;
}

void hashmap_add(struct hashmap_t *hm, int hash, const char *key, int count) {
	struct chain_t *ch;
	if (hash < 0)
		hash = nstr_hash(hm, key, strlen(key));
	if (hm->map[hash] == NULL) {
		if (hm->tale == NULL) {
			hm->tale = chain_create(key, count);
			hm->head = hm->tale;
		}
		else {
			hm->head->next = chain_create(key, count);
			hm->head = hm->head->next;
		}
		hm->map[hash] = hm->head;
		hm->mapn[hash] = 1;
	}
	else {
		ch = chain_find(hm->map[hash], key, hm->mapn[hash]);
		if (ch == NULL) {
			ch = chain_create(key, count);
			ch->next = hm->map[hash]->next;
			hm->map[hash]->next = ch;
			if (ch->next == NULL)
				hm->head = ch;
			++(hm->mapn[hash]);
		}
		else 
			ch->count += count;
	}
}

int hashmap_find(const struct hashmap_t *hm, int hash, const char *key) {
	struct chain_t *ch;
	if (hash < 0)
		hash = nstr_hash(hm, key, strlen(key));
	ch = chain_find(hm->map[hash], key, hm->mapn[hash]);
	if (ch == NULL)
		return 0;
	return ch->count;
}

void hashmap_rehash(struct hashmap_t *hm, int p, int r) {
	struct chain_t *ch = hm->tale, *next;
	int hash;
	if (p == 0 || r == 0) {
		p = P;
		r = R;
	}
	hm->p = p;
	hm->r = r;
	hm->tale = NULL;
	hm->head = NULL;
	free(hm->map);
	hm->map = calloc(hm->p, sizeof(struct chain_t *));
	if (hm->map == NULL)
		abort();
	free(hm->mapn);
	hm->mapn = calloc(hm->p, sizeof(int));
	if (hm->mapn == NULL)
		abort();
	for (; ch != NULL; ch = next) {
		next = ch->next;
		hash = str_hash(hm, ch->key);
		if (hm->map[hash] == NULL) {
			if (hm->tale == NULL)
				hm->tale = ch;
			else
				hm->head->next = ch;
			hm->head = ch;
			hm->head->next = NULL;
			hm->map[hash] = ch;
			hm->mapn[hash] = 1;
		}
		else {
			ch->next = hm->map[hash]->next;
			if (ch->next == NULL)
				hm->head = ch;
			hm->map[hash]->next = ch;
			++(hm->mapn[hash]);
		}
	}
}

void hashmap_print(struct hashmap_t *hm) {
	struct chain_t *ch;
	for (ch = hm->tale; ch != NULL; ch = ch->next)
		printf("%d - '%d': '%s' - %d\n", hm->mapn[str_hash(hm, ch->key)], str_hash(hm, ch->key), ch->key, ch->count);
}