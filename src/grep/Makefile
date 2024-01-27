FLAGS = -Wall -Wextra -Werror -std=c11

all: s21_grep

s21_grep: Makefile s21_grep.h s21_grep.c
	gcc $(FLAGS) s21_grep.c -o s21_grep

clang_style:
	clang-format -style=Google -i *.c *.h

clang_check:
	clang-format -style=Google -n *.c *.h

rebuild:
	make clean
	make all
clean:
	rm -f s21_grep s21_grep

test:
	sh test.sh

style_check:
	clang-format -n *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --check-config *.c

leaks:
	CK_FORK=no leaks -atExit -- ./s21_grep