FLAGS = -Wall -Werror -Wextra -std=c11

all:s21_cat

s21_cat: Makefile s21_cat.h s21_cat.c
	gcc $(FLAGS) s21_cat.c -o s21_cat

clang_style:
	clang-format -style=Google -i *.c *.h

clang_check:
	clang-format -style=Google -n *.c *.h

rebuild:
	make clean
	make all

clean:
	rm -f s21_cat s21_cat

style_check:
	clang-format -n *.c *.h

test:
	sh test.sh

cppcheck:
	cppcheck --enable=all --supress=missingIncludeSystem --checking config *.c

leaks:
	CK_FORK=no leaks -atExit -- ./s21_cat
