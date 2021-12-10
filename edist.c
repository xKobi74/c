#include <stdio.h> 	
#include <stdio.h>
#include <stdlib.h>

struct map_t {
	long long **a;
	long long n, m;
};

struct seq_t {
	long long n;
	long long *s;
};

struct seq_t inputseq(FILE *fp) {
	long long n, k, i;
	long long *s;
	struct seq_t x;
	k = fscanf(fp, "%lld", &n);
	if (k != 1ll)
		abort();
	s = malloc((n + 1) * sizeof(long long));
	if (s == NULL)
		abort();
	for (i = 0; i < n; ++i)
		k += fscanf(fp, "%lld", s + i);
	if (k != n + 1ll)
		abort();
	x.s = s;
	x.n = n;
	return x;
}

void freeseq(struct seq_t *x) {
	x->n = 0;
	free(x->s);
}

void input(struct seq_t *a, struct seq_t *b, FILE *fp) {
	*a = inputseq(fp);
	*b = inputseq(fp);
}

struct map_t createmap(struct seq_t a, struct seq_t b) {
	struct map_t map;
	long long i;
	map.a = malloc((a.n + 1) * sizeof(long long *));
	map.n = a.n;
	map.m = b.n;
	for (i = 0; i <= a.n; ++i)
		map.a[i] = malloc((b.n + 1) * sizeof(long long));
	for (i = 0; i <= a.n; ++i) 
		map.a[i][0] = 0;
	for (i = 0; i <= b.n; ++i) 
		map.a[0][i] = 0;
	return map;
}

void freemap(struct map_t *map) {
	long long i;
	for (i = 0; i <= map->n; ++i)
		free(map->a[i]);
	free(map->a);
	map->n = 0;
	map->m = 0;
}

long long max(long long x, long long y) {
	if (x > y)
		return x;
	return y;
}

void feelmap(struct map_t *map, struct seq_t a, struct seq_t b) {
	long long i, j;
	for (i = 1ll; i <= map->n; ++i)
		for (j = 1ll; j <= map->m; ++j) {
			if (a.s[i - 1] == b.s[j - 1])
				map->a[i][j] = map->a[i - 1][j - 1] + 1;
			else
				map->a[i][j] = max(map->a[i - 1][j], map->a[i][j - 1]);
		}
}

long long getans(struct map_t map) {
	return map.a[map.n][map.m];
}

int main() {
	struct seq_t a, b;
	struct map_t map;
	long long ans = 0;
	FILE *fin = fopen("edist.dat", "r");
	input(&a, &b, fin);
	fclose(fin);

	map = createmap(a, b);
	feelmap(&map, a, b);
	ans = getans(map);
	freeseq(&a);
	freeseq(&b);
	freemap(&map);

	FILE *fout = fopen("edist.ans", "w");
	fprintf(fout, "%lld\n", ans);
	printf("%lld\n", ans);
	fclose(fout);
	return 0;
}
