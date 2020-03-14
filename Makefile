all: bin/chess

bin/chess: build/main.o build/board.o build/board_print_plain.o
	gcc -Wall -Werror build/main.o build/board.o build/board_print_plain.o -o chess

build/main.o: src/main.c src/board_print_plain.h src/board.h
	clang-format -i src/main.c
	gcc -Wall -Werror -I src -c src/main.c -o build/main.o

build/board.o: src/board.c
	gcc -Wall -Werror -I src -c src/board.c -o build/board.o

build/board_print_plain.o: src/board_print_plain.c
	clang-format -i src/board_print_plain.c
	gcc -Wall -Werror -I src -c src/board_print_plain.c -o build/board_print_plain.o


clean:
	rm -rf build/*.o bin/chess bin/*.o *.o		