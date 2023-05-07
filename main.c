#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

static void print(int *ary, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		printf("%d ", ary[i]);
	}
	puts("");
}

static bool is_sorted(int *ary, size_t size)
{
	for (size_t i = 0; i + 1 < size; i++) {
		if (ary[i] > ary[i + 1]) {
			return false;
		}
	}
	return true;
}

static bool is_sort_working(int *ary, size_t size, void (*sort)(int *, int *))
{
	int *p = malloc(size * sizeof(int));
	memcpy(p, ary, size * sizeof(int));
	sort(p, p + size);
	bool is_ok = is_sorted(p, size);
	free(p);
	return is_ok;
}

static void test(int *ary, size_t size, void (*sort)(int *, int *))
{
	if (is_sort_working(ary, size, sort)) {
		puts("OK");
	} else {
		puts("KO");
		print(ary, size);
	}
}

#define SIZE 8

static bool dfs(int *ary, unsigned depth, void (*sort)(int *, int *))
{
	if (depth == SIZE) {
		return is_sort_working(ary, SIZE, sort);
	}
	for (int i = 0; i < SIZE; i++) {
		ary[depth] = i;
		if (!dfs(ary, depth + 1, sort)) {
			return false;
		}
	}
	return true;
}

static void brute_force(void (*sort)(int *, int *))
{
	printf("brute_force: ");
	fflush(stdout);
	int ary[SIZE] = {};
	if (dfs(ary, 0, sort)) {
		puts("OK");
	} else {
		puts("KO");
		print(ary, SIZE);
	}
}

static void test_sort(void (*sort)(int *, int *))
{
	int a[] = {1, 2, 3};
	test(a, ARRAY_SIZE(a), sort);
	int aa[] = {-1, -2, -3};
	test(aa, ARRAY_SIZE(aa), sort);
	int b[] = {3, 2, 1};
	test(b, ARRAY_SIZE(b), sort);
	int c[] = {1, 3, 2};
	test(c, ARRAY_SIZE(c), sort);
	int d[] = {1, 4, 2, 3, 10, 6};
	test(d, ARRAY_SIZE(d), sort);
	int e[] = {2, 1};
	test(e, ARRAY_SIZE(e), sort);
	int f[] = {1};
	test(f, ARRAY_SIZE(f), sort);
	int g[] = {1, 4, 2, 3};
	test(g, ARRAY_SIZE(g), sort);
	int h[] = {1, 4, 2, 3, 5, 7, 100, 9, 2, 9, 13, 3};
	test(h, ARRAY_SIZE(h), sort);
	int i[] = {1, 2, 3, 7, 8, 6};
	test(i, ARRAY_SIZE(i), sort);
	int j[] = {-1, 4, -2, 3, -5, -7, 100, -9, 2, 9, -13, 3};
	test(j, ARRAY_SIZE(j), sort);
}

void test_qsort()
{
	puts("====================");
	puts("====== q_sort ======");
	puts("====================");
	test_sort(q_sort);
	brute_force(q_sort);
}

static void wrap_m_sort(int *begin, int *end)
{
	m_sort(begin, end);
}

void test_msort()
{
	puts("====================");
	puts("====== m_sort ======");
	puts("====================");
	test_sort(wrap_m_sort);
	brute_force(wrap_m_sort);
}

void test_insertion_sort()
{
	puts("============================");
	puts("====== insertion_sort ======");
	puts("============================");
	test_sort(insertion_sort);
	brute_force(insertion_sort);
}

int main()
{
	test_qsort();
	test_msort();
	test_insertion_sort();
}
