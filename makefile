CC=gcc
CXX=g++
CPPFLAGS=-I include -L lib -l SDL2-2.0.0 -I include -L lib -l SDL2_image-2.0.0
DEPS = src/headers/game.h src/headers/graphics.h src/headers/sprite.h src/headers/player.h src/headers/lazer.h src/headers/enemy.h src/headers/rectangle.h
OBJ = main.o game.o graphics.o sprite.o player.o lazer.o enemy.o

%.o: src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CPPFLAGS)

play: $(OBJ)
	$(CXX) -o $@ $^ $(CPPFLAGS)

clean:
	rm -f *.o play
