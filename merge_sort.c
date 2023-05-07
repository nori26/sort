#include <stdlib.h>
#include <string.h>

static void merge(int *dest, int *a, int *a_end, int *b, int *b_end)
{
	while (a < a_end && b < b_end) {
		if (*a <= *b) {
			*dest = *a++;
		} else {
			*dest = *b++;
		}
		dest++;
	}
	memcpy(dest, a, (a_end - a) * sizeof(int));
	memcpy(dest, b, (b_end - b) * sizeof(int));
}

static void msort_recursive(int *begin, int *end, int *buf)
{
	if (end - begin < 2) {
		return;
	}
	int *left      = begin;
	int *left_end  = left + (end - begin) / 2;
	int *right     = left_end;
	int *right_end = end;
	msort_recursive(left, left_end, buf);
	msort_recursive(right, right_end, buf);
	merge(buf, left, left_end, right, right_end);
	memcpy(begin, buf, (end - begin) * sizeof(int));
}

int m_sort(int *begin, int *end)
{
	int *p = malloc((end - begin) * sizeof(int));
	if (!p) {
		return -1;
	}
	msort_recursive(begin, end, p);
	free(p);
	return 0;
}
