#include <stddef.h>
#include <stdio.h>

typedef struct s_boundary
{
	int *left_end;
	int *right_begin;
} t_boundary;

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
	size_t   size  = end - begin;
	int     *front = begin;
	int     *mid   = begin + size / 2;
	int     *back  = end - 1;
	unsigned avg   = abs((*front + *mid + *back) / 3);
	return begin + avg % size;
}

static t_boundary partition_by_pivot(int *begin, int *end)
{
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
	return (t_boundary){.left_end = left, .right_begin = left + 1};
}

void q_sort(int *begin, int *end)
{
	if (begin == end) {
		return;
	}
	t_boundary b = partition_by_pivot(begin, end);
	q_sort(begin, b.left_end);
	q_sort(b.right_begin, end);
}
