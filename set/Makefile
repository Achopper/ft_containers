NAME = setTest.cpp

all:
	sed 's/ft::/std::/g' $(NAME) > std_$(NAME)
	clang++  -std=c++11 -Wall -Wextra -Werror  setTest.cpp  -o my.out
	clang++  -std=c++11 -Wall -Wextra -Werror std_setTest.cpp  -o std.out

test: all
	@echo "STD"
	@time -p ./std.out > std.txt
	@echo ""
	@echo "MY"
	@time -p ./my.out > my.txt
	@echo ""
	@echo "DIFF"
	@diff my.txt std.txt > diff.txt
	@echo ""
	@cat diff.txt

leaks:
	clang++ -std=c++11 -Wall -Wextra -Werror setTest.cpp -o my.out && leaks --atExit -- ./my.out

clean:
	rm my.out std.out std_setTest.cpp std.txt my.txt diff.txt
