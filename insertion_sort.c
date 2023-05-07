#include <stddef.h>

static void swap(int *a, int *b)
{
	int tmp = *a;
	*a      = *b;
	*b      = tmp;
}

void insertion_sort(int *begin, int *end)
{
	for (int *first = begin + 1; first != end; first++) {
		for (int *p = first; p != begin && p[-1] > p[0]; p--) {
			swap(p - 1, p);
		}
	}
}
