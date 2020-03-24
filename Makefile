all: bin/chess format

bin/chess: build/main.o build/board.o build/board_print_plain.o
	gcc -Wall -Werror build/main.o build/board.o build/board_print_plain.o -o bin/chess

build/main.o: src/main.c src/board_print_plain.h src/board.h
	clang-format -i src/main.c
	gcc -Wall -Werror -I src -c src/main.c -o build/main.o

build/board.o: src/board.c
	gcc -Wall -Werror -I src -c src/board.c -o build/board.o

build/board_print_plain.o: src/board_print_plain.c
	clang-format -i src/board_print_plain.c
	gcc -Wall -Werror -I src -c src/board_print_plain.c -o build/board_print_plain.o

format: src/board.c src/board.h src/board_print_plain.c src/board_print_plain.h src/main.c
		clang-format -i src/main.c src/board_print_plain.c src/board.c src/board.h src/board_print_plain.h

clean:
	rm -rf build/*.o bin/chess bin/*.o *.o		