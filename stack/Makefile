NAME = stackTest.cpp

all:
	sed 's/ft/std/g' $(NAME) > std_$(NAME)
	clang++ -Wall -Wextra -Werror stackTest.cpp -fsanitize=address -o my.out
	clang++ -Wall -Wextra -Werror std_stackTest.cpp -fsanitize=address -o std.out

test: all
	@echo "STD"
	time -p ./std.out > std.txt
	@echo ""
	@echo "MY"
	time -p ./my.out > my.txt
	@echo ""
	@echo "DIFF"
	@diff std.txt my.txt > diff.txt
	@cat diff.txt

leaks:
	clang++ -Wall -Wextra -Werror stackTest.cpp -o my.out && leaks --atExit -- my.out

clean:
	rm my.out std.out std_stackTest.cpp std.txt my.txt diff.txt
