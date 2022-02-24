#ifndef __HASHMAP_H__
#define __HASHMAP_H__

struct hashmap_t {
	int r, p;
	struct chain_t **map;
};

struct hashmap_t *hashmap_create(int p, int r);
void hashmap_destroy(struct hashmap_t *hm);
int nstr_hash(const struct hashmap_t *hm, const char *key, int n);
void hashmap_add(struct hashmap_t *hm, int hash, const char *key, int count);
int hashmap_find(const struct hashmap_t *hm, int hash, const char *key);

#endif