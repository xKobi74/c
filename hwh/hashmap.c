#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chain.h"
#include "hashmap.h"

const int P = 10000, R = 132; //default setting of hashmap 

struct hashmap_t *hashmap_create(int p, int r) {
	struct hashmap_t *hm = malloc(sizeof(struct hashmap_t));
	if (hm == NULL)
		abort();
	if (p * r == 0) {
		hm->p = P;
		hm->r = R;
	}
	else {
		hm->p = p;
		hm->r = r;	
	}
	hm->map = calloc(hm->p, sizeof(struct chain_t *));
	if (hm->map == NULL)
		abort();
	return hm;
}

void hashmap_destroy(struct hashmap_t *hm) {
	int i;
	for (i = 0; i < hm->p; ++i)
		chain_destroy(hm->map[i]);
	free(hm->map);
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

void hashmap_add(struct hashmap_t *hm, int hash, const char *key, int count) {
	if (hash < 0)
		hash = nstr_hash(hm, key, strlen(key));
	if (hm->map[hash] == NULL)
		hm->map[hash] = chain_create(key, count);
	else
		chain_add(hm->map[hash], key, count); 
}

int hashmap_find(const struct hashmap_t *hm, int hash, const char *key) {
	if (hash < 0)
		hash = nstr_hash(hm, key, strlen(key));
	return chain_find(hm->map[hash], key);
}
