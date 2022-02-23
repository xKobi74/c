int check(char const * needle, int n, int k) {
	int i;
	for (i = 0; i < k; ++i)
		if (tolower(needle[i]) != tolower(needle[n - k + i]))
			return 0;
	return 1;
}

int nmatch(char const * needle, int n) {
	int k, kmax = 0;
	for (k = 1; k < n; ++k) 
		if (check(needle, n, k))
			kmax = k;
	return kmax;
}

void patpreproc(char const * needle, int * needle_lps) {
	int i;
	for (i = 0; needle[i] != '\0' ; ++i)
		needle_lps[i] = nmatch(needle, i + 1);
}

char * strstrci(char const * needle, int const * needle_lps, char const * haystack) {
	int k = 0, i = 0, nh = strlen(haystack);
	while (i < nh) {
		while (tolower(haystack[i + k]) == tolower(needle[k]) && i + k < nh)
			k++;
		if (needle[k] == '\0')
			return haystack + i;
		if (k == 0)
			++i;
		else {
			i += k - needle_lps[k - 1];
			k = needle_lps[k - 1];
		}
	}
	return NULL;
}
