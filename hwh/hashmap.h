#ifndef __HASHMAP_H__
#define __HASHMAP_H__

struct hashmap_t;

struct hashmap_t *hashmap_create(int p, int r);
void hashmap_destroy(struct hashmap_t *hm);
int nstr_hash(const struct hashmap_t *hm, const char *key, int n);
int str_hash(const struct hashmap_t *hm, const char *key);
void hashmap_add(struct hashmap_t *hm, int hash, const char *key, int count);
int hashmap_find(const struct hashmap_t *hm, int hash, const char *key);
void hashmap_rehash(struct hashmap_t *hm, int p, int r);
void hashmap_print(struct hashmap_t *hm);

#endif