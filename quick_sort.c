#include <stddef.h>
#include <stdio.h>

static void swap(int *a, int *b)
{
	int tmp = *a;
	*a      = *b;
	*b      = tmp;
}

static unsigned abs(int n)
{
	if (n > 0) {
		return n;
	} else {
		return -(n + 1) + 1U;
	}
}

static int *select_pivot(int *begin, int *end)
{
	size_t   size = end - begin;
	int     *a    = begin;
	int     *b    = begin + size / 2;
	int     *c    = end - 1;
	unsigned avg  = abs((*a + *b + *c) / 3);
	return begin + avg % size;
}

void q_sort(int *begin, int *end)
{
	if (begin == end) {
		return;
	}
	int *left  = begin;
	int *right = end - 1;
	int *pivot = right;
	swap(select_pivot(begin, end), pivot);
	while (left < right) {
		while (*left < *pivot && left < right) {
			left++;
		}
		while (*right >= *pivot && right > left) {
			right--;
		}
		swap(left, right);
	}
	swap(pivot, left);
	q_sort(begin, left);
	q_sort(left + 1, end);
}
