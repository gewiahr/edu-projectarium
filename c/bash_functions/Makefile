COMPILE = gcc -std=c99 -g
FLAGS = -Wall -Werror -Wextra
CLANG_PATH = common/.clang-format

all: cat grep

cat:
	@$(COMPILE) $(FLAGS) cat.c -o cat
	@echo " #### Cat Compilation #### "

grep:
	@$(COMPILE) $(FLAGS) grep.c -o grep
	@echo " #### Grep Compilation #### "

cat_test: cat
	@echo " #### Cat Test #### "
	@bash ./tests/cat_test.sh

grep_test: grep
	@echo " #### Grep Test #### "
	@bash ./tests/grep_test.sh

clang:
	@echo " #### MAKING CLANG FORMAT #### "
	@clang-format -i *.c *.h

clang-check:
	@echo " #### CHECKING CLANG #### "
	@clang-format -n *.c *.h

clean:
	clear
	@rm -f cat grep *.log *.a *.out *.exe
	@rm -f tests/*.log
	@echo " #### Cleaned! #### "

rebuild: 
	make clean
	make all
