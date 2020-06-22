all: vocab_snake_game

# compile
ded.o funcs.o game.o gameclass.o main.o parser.o welcome.o widgets.o: ded.cpp funcs.cpp game.cpp gameclass.cpp main.cpp parser.cpp welcome.cpp widgets.cpp
	 g++ -c ded.cpp funcs.cpp game.cpp gameclass.cpp main.cpp parser.cpp welcome.cpp widgets.cpp

#link to make executable "snake_game"
vocab_snake_game: ded.o funcs.o game.o gameclass.o main.o parser.o welcome.o widgets.o
	 g++ ded.o funcs.o game.o gameclass.o main.o parser.o welcome.o widgets.o -o vocab_snake_game -lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs

	 
clean :
	 rm ded.o funcs.o game.o gameclass.o main.o parser.o welcome.o widgets.o vocab_snake_game
