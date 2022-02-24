#ifndef __CHAIN_H__
#define __CHAIN_H__

struct chain_t {
	char *key;
	int count;
	struct chain_t *next;
};

struct chain_t *chain_create(const char *key, int count);
void chain_destroy(struct chain_t *ch);
void chain_add(struct chain_t *cur, const char *key, int count);
int chain_find(const struct chain_t *ch, const char *key);

#endif