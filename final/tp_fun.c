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