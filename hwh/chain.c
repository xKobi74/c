#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chain.h"

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

void chain_destroy(struct chain_t *ch) {
	if (ch == NULL)
		return;
	chain_destroy(ch->next);
	free(ch->key);
	free(ch);
}

void chain_add(struct chain_t *cur, const char *key, int count) {
	struct chain_t *pr = NULL;
	for (cur; cur != NULL && strcmp(key, cur->key) != 0; pr = cur, cur = cur->next);
	if (cur == NULL)
		pr->next = chain_create(key, count);
	else
		cur->count += count;
}

int chain_find(const struct chain_t *ch, const char *key) {
	for (ch; ch != NULL && strcmp(key, ch->key) != 0; ch = ch->next);
	if (ch == NULL)
		return 0;
	return ch->count;
}