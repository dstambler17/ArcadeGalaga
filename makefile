CC=gcc
CXX=g++
CPPFLAGS= -I include -L lib -l SDL2-2.0.0 -I include -L lib -l SDL2_image-2.0.0 -I include -L lib -l SDL2_ttf-2.0.0 \
-I include -L lib -l SDL2_mixer-2.0.0
#COMPILEFLAGS = -I include -L lib -l SDL2_ttf-2.0.0
#CPPFLAGS=-I include -l SDL2-2.0.0 -I include -l SDL2_image-2.0.0
DEPS = src/headers/game.h src/headers/graphics.h src/headers/sprite.h src/headers/player.h \
 	   src/headers/lazer.h src/headers/enemy.h src/headers/rectangle.h src/headers/level.h src/headers/textmanager.h \
	   src/headers/audio.h src/headers/endscreen.h src/headers/music.h src/headers/titlescreen.h
OBJ = main.o game.o level.o graphics.o sprite.o player.o lazer.o enemy.o textmanager.o audio.o endscreen.o music.o titlescreen.o

%.o: src/%.cpp $(DEPS)
	$(CXX) -std=c++11 -c -o $@ $<

play: $(OBJ)
	$(CXX) -o $@ $^ $(CPPFLAGS)

clean:
	rm -f *.o play
