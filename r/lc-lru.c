#include <stdio.h>
#include <stdlib.h>

struct node_t {
	int data;
	struct node_t *prev, *next;
};

struct chain_t {
	int key;
	struct node_t *ptr;
	struct chain_t *next;
};

struct hashmap_t {
	int r, p;
	struct chain_t *tale, *head;
	struct chain_t **map;
	int *mapn;
};

struct cash_t {
	int capacity, size;
	struct node_t *top, *back;
	struct hashmap_t *freq;	
};

struct chain_t *chain_create(int key, struct node_t *ptr) {
	struct chain_t *ch = malloc(sizeof(struct chain_t));
	if (ch == NULL)
		abort(); 
	ch->next = NULL;
	ch->ptr = ptr;
	ch->key = key;
	return ch;
}

void chain_destroy(struct chain_t *ch) {
	if (ch == NULL)
		return;
	chain_destroy(ch->next);
	free(ch);
}

void chain_add(struct chain_t *cur, int key, struct node_t *ptr) {
	struct chain_t *pr = NULL;
	for (cur; cur != NULL; pr = cur, cur = cur->next);
	pr->next = chain_create(key, ptr);
}

struct chain_t *chain_find(struct chain_t *ch, int key, int n) {
	struct chain_t *st = ch;
	for (ch; ch != NULL && key != ch->key && n != 0; ch = ch->next, --n);
	if (ch == NULL || ch - st > n - 1)
		return NULL;
	return ch;
}

struct hashmap_t *hashmap_create(int p, int r) {
	struct hashmap_t *hm = malloc(sizeof(struct hashmap_t));
	if (hm == NULL)
		abort();
	if (p == 0)
		p = 10000;
	if (r == 0)
		r = 132;
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

int int_hash(const struct hashmap_t *hm, int key) {
	return key % (hm->p);
}

void hashmap_update(struct hashmap_t *hm, int hash, int key, struct node_t *ptr) {
	struct chain_t *ch;
	if (hash < 0)
		hash = int_hash(hm, key);
	if (hm->map[hash] == NULL) {
		if (hm->tale == NULL) {
			hm->tale = chain_create(key, ptr);
			hm->head = hm->tale;
		}
		else {
			hm->head->next = chain_create(key, ptr);
			hm->head = hm->head->next;
		}
		hm->map[hash] = hm->head;
		hm->mapn[hash] = 1;
	}
	else {
		ch = chain_find(hm->map[hash], key, hm->mapn[hash]);
		if (ch == NULL) {
			ch = chain_create(key, ptr);
			ch->next = hm->map[hash]->next;
			hm->map[hash]->next = ch;
			if (ch->next == NULL)
				hm->head = ch;
			++(hm->mapn[hash]);
		}
		else 
			ch->ptr = ptr;
	}
}

struct node_t *hashmap_find(const struct hashmap_t *hm, int hash, int key) {
	struct chain_t *ch;
	if (hash < 0)
		hash = int_hash(hm, key);
	if (hm->map[hash] == NULL)
		return NULL;
	ch = chain_find(hm->map[hash], key, hm->mapn[hash]);
	if (ch == NULL)
		return NULL;
	return ch->ptr;
}

struct node_t *node_create(int data, struct node_t *prev, struct node_t *next) {
	struct node_t *node;
	node = malloc(sizeof(struct node_t));
	node->data = data;
	node->prev = prev;
	node->next = next;
	return node;
}

void node_destroyfromtop(struct node_t *top) {
	if (top == NULL)
		return;
	node_destroyfromtop(top->prev);
	free(top);
}

void node_deleteonefromback(struct node_t *back) {
	back->next->prev = NULL;
	free(back);
}

void node_copy(struct node_t *nodea, struct node_t *nodeb) {
	nodea->data = nodeb->data;
	nodea->prev = nodeb->prev;
	nodea->next = nodeb->next;
}

void node_print(struct node_t *top) {
	if (top == NULL) {
		return;
	}
	printf("%d ", top->data);
	node_print(top->prev);
}

void node_printr(struct node_t *back) {
	if (back == NULL) {
		return;
	}
	printf("%d ", back->data);
	node_print(back->next);
}

struct cash_t *cash_create(int capacity) {
	struct cash_t *cash = malloc(sizeof(struct cash_t));
	cash->capacity = capacity;
	cash->size = 0;
	cash->top = NULL;
	cash->back = NULL,
	cash->freq = hashmap_create(capacity, 0);
	return cash;
}

void cash_destroy(struct cash_t *cash) {
	node_destroyfromtop(cash->top);
	hashmap_destroy(cash->freq);
	free(cash);
}

void cash_print(struct cash_t *cash) {
	printf("#%d %d:\n", cash->capacity, cash->size);
	node_print(cash->top);
	printf("\n");
	node_printr(cash->back);
	printf("\n");
}

void input(int *m, int *n) {
	int k;
	k = scanf("%d%d", m, n);
	if (k != 2)
		abort();
}
void hashmap_print(struct hashmap_t *hm) {
	struct chain_t *ch;
	for (ch = hm->tale; ch != NULL; ch = ch->next)
		printf("%d - '%d': '%d' - %d\n", hm->mapn[int_hash(hm, ch->key)], int_hash(hm, ch->key), ch->key, ch->ptr);
}

int req(struct cash_t *cash) {
	int k, data;
	struct node_t *tmp, *ptr;
	k = scanf("%d", &data);
	if (k != 1)
		abort();
	ptr = hashmap_find(cash->freq, -1, data);
									//printf("--%d\n", data);
									//cash_print(cash);
									hashmap_print(cash->freq);
									//printf("##%d\n", ptr);
	if (ptr == NULL) {
		printf("!!!\n");
		tmp = node_create(data, NULL, NULL);
		hashmap_update(cash->freq, -1, data, tmp);
		if (cash->size == 0) {
			cash->top = tmp;
			cash->back = tmp;
			++(cash->size);
			return 0;
		}
		tmp->prev = cash->top;
		cash->top->next = tmp;
		cash->top = tmp;
		if (cash->size == cash->capacity) {
			printf("sfddfa\n");
			node_deleteonefromback(cash->back);
			hashmap_update(cash->freq, -1, cash->back->data, NULL);
			hashmap_print(cash->freq);
		}
		else
			++(cash->size);
		return 0;
	}
	else {
		printf("+++\n");
		printf("+%d\n", ptr->data);
		if (cash->size == 1)
			return 1;
		if (cash->top == ptr)
			return 1;
		if (cash->back == ptr)
			cash->back = ptr->next;
		if (ptr->prev != NULL)
			ptr->prev->next = ptr->next;
		//printf("##%d\n", ptr->prev);
		ptr->next->prev = ptr->prev;
		ptr->prev = cash->top;
		ptr->next = NULL;
		cash->top = ptr;
		return 1;
	}
	return -1;
}

int proc(struct cash_t *cash, int n) {
	int res = 0, i;
	for (i = 0; i < n; ++i)
		res += req(cash);
	return res;
}

int main() {
	int m, n, res;
	struct cash_t *cash;
	input(&m, &n);
	cash = cash_create(m);
	res = proc(cash, n);
	printf("%d\n", res);
	cash_destroy(cash);
	return 0;
}