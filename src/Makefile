CC = gcc
TEST_LIBS = -lcheck
FLAGS = -Wall -Werror -Wextra -std=c11
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

all: clean test

test: clean s21_decimal.a
	$(CC) $(CFLAGS) tests/*.c s21_decimal.a $(TEST_LIBS) -o test
	./test
	rm -rf *.o tests/*.o

s21_decimal.a: $(OBJECTS)
	ar rcs s21_decimal.a $(OBJECTS)

gcov_flag:
	$(eval CFLAGS += -fprofile-arcs -ftest-coverage)

gcov_report: clean gcov_flag test
	gcov $(SOURCES)
	rm -rf html_report
	gcov -b *.c 
	lcov -d . -c -o coverage.info
	genhtml -o html_report coverage.info
	open ./html_report/index.html

clang:
	cp ../materials/linters/.clang-format ../src
	clang-format -i *.h *.c
	rm -rf .clang-format

style : 
	clang-format --style=google -i *.c *.h
	clang-format --style=google -i tests/*.c

test_leaks: test
	leaks --atExit -- ./test

clean : 
	rm -rf *.a *.o tests/*.o test *.gcno *.gcda *.gcov *.info coverage* *.dSYM
