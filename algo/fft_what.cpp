void fft(vector<int> &a, int low, int high) {
	if (low == high - 1)
		return;
	int len = (high - low) / 2, mid = low + len;
	fft(a, low, mid);
	fft(a, mid, high);
	for(int i = low; i < mid; i++) {
		int x1 = a[i];
		int x2 = a[i + len];
		a[i] = (x1 - x2);
		a[i + len] = (x1 + x2);
	}
}

void inv_fft(vector<int> &a, int low, int high) {
	if (low == high - 1)
		return;
	int len = (high - low) / 2, mid = low + len;
	for(int i = low; i < mid; i++) {
		int y1 = a[i];
		int y2 = a[i + len];
		a[i] = (y1 + y2) / 2;
		a[i + len] = (y2 - y1) / 2;
	}
	inv_fft(a, low, mid);
	inv_fft(a, mid, high);
}
