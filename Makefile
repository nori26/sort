SRCS := main.c merge_sort.c quick_sort.c
CFLAGS :=  -Wall -Wextra -Werror -O2 #-g3 -fsanitize=address

run:
	gcc $(CFLAGS) $(SRCS) && ./a.out