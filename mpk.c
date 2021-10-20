#include <stdio.h>
#include <stdlib.h>

#define MAGIC_CONSTANT 256

struct pol_t {
	int nmax;
	int n;
	int *c;
};

struct pol_t init_pol(int nmax) {
	struct pol_t p;
	p.nmax = nmax;
	p.n = 0;
	p.c = calloc(nmax, sizeof(int));
	if (p.c == NULL)
		abort();
	return p;
}

void free_pol(struct pol_t *p) {
	p->nmax = 0;
	p->n = 0;
	free(p->c);
} 

void move_pol(struct pol_t *p, struct pol_t *p1) {
	p->nmax = p1->nmax;
	p->n = p1->n;
	p->c = p1->c;
}

void nrecount_pol(struct pol_t *p) {
	int n = p->nmax - 1;
	while (n > 0 && (p->c)[n] == 0)
		n--;
	p->n = n + 1;
}

void split_pol(struct pol_t *p0, struct pol_t *p1, struct pol_t *p) {
	p0->c = p->c;
	p0->n = p->n / 2;
	p1->c = p->c + p->n / 2;
	p1->n = p->n - p->n / 2;
}

void input(struct pol_t *pa, struct pol_t *pb) {
	int i, k, n;
	k = scanf("%d", &n);
	if (k != 1)
		abort();
	*pa = init_pol(n);
	pa->n = n;
	k += scanf("%d", &n);
	if (k != 2)
		abort();
	*pb = init_pol(n);
	pb->n = n;
	for (i = 0; i < pa->n; i++)
		k += scanf("%d", pa->c + i);
	for (i = 0; i < pb->n; i++)
		k += scanf("%d", pb->c + i);
	if (k != pa->n + pb->n + 2)
		abort();
}

void output(struct pol_t *p) {
	int i;
	for (i = 0; i < p->n; i++) {
		printf("%d ", (p->c)[i]);
	}
	printf("\n");
}

void addk(struct pol_t *pc, struct pol_t *p, int k, int d) {
	int i;
	for (i = 0; i < p->n; i++) {
		(pc->c)[i + d] += (p->c)[i] * k;
	}
	nrecount_pol(pc);
}

void mult(struct pol_t *pc, struct pol_t *pa, struct pol_t *pb) {
	struct pol_t tmp = init_pol(pa->n * 2);
	int i, j;
	for (i = 0; i < pa->n; i++)
		for (j = 0; j < pb->n; j++)
			(tmp.c)[i + j] += (pa->c)[i] * (pb->c)[j];
	nrecount_pol(&tmp);
	move_pol(pc, &tmp);
}

void multc(struct pol_t *pc, struct pol_t *pa, struct pol_t *pb) {
	struct pol_t pa0, pa1, pb0, pb1, psa, psb, pm1, pm0, pms, tmp;
	free_pol(pc);
	if (pa->n <= MAGIC_CONSTANT) {
		mult(pc, pa, pb);
		return;
	}
	split_pol(&pa0, &pa1, pa);
	split_pol(&pb0, &pb1, pb);
	psa = init_pol(pa->n / 2), psb = init_pol(pa->n / 2);
	pms = init_pol(pa->n), tmp = init_pol(pa->n * 2);
	addk(&psa, &pa0, 1, 0); addk(&psa, &pa1, 1, 0);
	addk(&psb, &pb0, 1, 0); addk(&psb, &pb1, 1, 0);
	multc(&pms, &psa, &psb);
	free_pol(&psa); free_pol(&psb);
	pm1 = init_pol(pa->n), pm0 = init_pol(pa->n);
	multc(&pm0, &pa0, &pb0); multc(&pm1, &pa1, &pb1);

	addk(&tmp, &pm1, 1, pa->n);
	addk(&tmp, &pms, 1, pa->n / 2);
	addk(&tmp, &pm1, -1, pa->n / 2); 
	addk(&tmp, &pm0, -1, pa->n / 2);
	addk(&tmp, &pm0, 1, 0);
	free_pol(&pm1); free_pol(&pm0);
	free_pol(&pms);

	move_pol(pc, &tmp);
}

int main() {
	struct pol_t pa, pb, pc = init_pol(0);
	input(&pa, &pb);
	abort();
	multc(&pc, &pa, &pb);
	output(&pc);
	free_pol(&pa);
	free_pol(&pb);
	free_pol(&pc);
	return 0;
}

