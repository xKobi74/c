
void foo(int *arr,int n) {
	int i;
	int *ptr;
	int sec = arr[2];

	for (ptr = arr + 4; 1; ++ptr) {
		if (ptr == arr + 6)
			break;
		arr[ptr[0]] = arr[ptr[1]];
	}
	arr[6] = sec;

	
	for (i = 1; i < n; ++i) {
		arr[i] += arr[i - 1];
	}
	return;
}