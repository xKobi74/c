#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct dagnode_t {
	int nodeid;
	int nchilds;
	int userinfo;
	struct dagnode_t **childs;
};

struct schedarray_t {
	int ndevices;
	int *devicesizes;
};

struct schedarray_t task_schedule(struct dagnode_t **topnodes, int ntopnodes);

int max(int x, int y) {
	if (x > y)
		return x;
	return y;
}

int tasktree_init(struct dagnode_t *topnode) {
	if (topnode == NULL)
		return 0;
	int i, deep = 0;
	for (i = 0; i < topnode->nchilds; ++i)
		deep = max(deep, tasktree_init((topnode->childs)[i]));
	topnode->userinfo = -1;
	return deep + 1;
}

//return deep of tasks tree
int task_init(struct dagnode_t **topnodes, int ntopnodes) {
	assert(topnodes != NULL);
	int i, deep = 0;
	for (i = 0; i < ntopnodes; ++i) 
		deep = max(deep, tasktree_init(topnodes[i]));
	return deep;
}

int tasktree_calc(struct dagnode_t *topnode, struct schedarray_t *schedarr) {
	if (topnode == NULL)
		return -1;
	if (topnode->userinfo >= 0)
		return topnode->userinfo;
	int i, step = -1;
	for (i = 0; i < topnode->nchilds; ++i)
		step = max(step, tasktree_calc((topnode->childs)[i], schedarr));
	topnode->userinfo = step + 1;
	assert(0 <= topnode->userinfo && topnode->userinfo <= schedarr->ndevices);
	++(schedarr->devicesizes[topnode->userinfo]);
	return topnode->userinfo;
}

void task_calc(struct dagnode_t **topnodes, int ntopnodes, struct schedarray_t *schedarr) {
	assert(topnodes != NULL);
	int i;
	for (i = 0; i < ntopnodes; ++i) 
		tasktree_calc(topnodes[i], schedarr);
}

struct schedarray_t task_schedule(struct dagnode_t **topnodes, int ntopnodes) {
	assert(topnodes != NULL); 
	int nsteps = task_init(topnodes, ntopnodes);
	struct schedarray_t schedarr;
	schedarr.ndevices = nsteps;
	schedarr.devicesizes = calloc(nsteps, sizeof(int));
	task_calc(topnodes, ntopnodes, &schedarr);
	return schedarr;
}

void push_child(struct dagnode_t *from, struct dagnode_t *to) {
	assert(from != NULL);
	assert(to != NULL);
	if (from->nchilds == 0) {
		from->childs = malloc(sizeof(struct dagnode_t *));
		assert(from->childs);
	} else {
		struct dagnode_t **res = (struct dagnode_t **)realloc(
				from->childs, sizeof(struct dagnode_t *) * (from->nchilds + 1));
		assert(res);
		from->childs = res;
	}
	from->childs[from->nchilds] = to;
	from->nchilds += 1;
}

int main() {
	int i, res;
	struct schedarray_t answ;
	struct dagnode_t **nodes;
	struct dagnode_t **topnodes;
	int nnodes, ntopnodes, nlinks;

	res = scanf("%d%d", &nnodes, &ntopnodes);
	assert(res == 2);
	assert(nnodes > 0);
	assert(ntopnodes > 0);

	nodes = (struct dagnode_t **)calloc(nnodes, sizeof(struct dagnode_t *));
	assert(nodes != NULL);

	for (i = 0; i < nnodes; ++i) {
		nodes[i] = (struct dagnode_t *)calloc(1, sizeof(struct dagnode_t));
		nodes[i]->nodeid = i;
	}

	topnodes = (struct dagnode_t **)calloc(ntopnodes, sizeof(struct dagnode_t *));
	assert(topnodes != NULL);

	for (i = 0; i < ntopnodes; ++i) {
		int nnode = 0;
		res = scanf("%d", &nnode);
		assert(res == 1);
		assert(nnode < nnodes);
		topnodes[i] = nodes[nnode];
	}

	res = scanf("%d", &nlinks);
	assert(res == 1);

	for (i = 0; i < nlinks; ++i) {
		int from, to;
		res = scanf("%d->%d", &from, &to);
		assert(res == 2);
		push_child(nodes[from], nodes[to]);
	}

	answ = task_schedule(topnodes, ntopnodes);

	for (i = 0; i < answ.ndevices; ++i)
		printf("%d ", answ.devicesizes[i]);
	printf("\n");

	for (i = 0; i < nnodes; ++i) {
		if (nodes[i]->nchilds > 0)
			free(nodes[i]->childs);
		free(nodes[i]);
	}
	free(nodes);
	free(topnodes);
	free(answ.devicesizes);
}
