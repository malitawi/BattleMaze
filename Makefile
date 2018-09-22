CC = clang++
LD = clang++

CFLAGS = -c -m64 -Wall -Werror -pedantic -std=c++11 -stdlib=libc++
LFLAGS = -m64 -pedantic
SFML_LIBS = -lsfml-graphics.2.3.0 -lsfml-window.2.3.0 -lsfml-system.2.3.0

SRCS = main.cpp Player.cpp Tile.cpp GameMap.cpp GameModel.cpp GameController.cpp
OBJS = $(SRCS:.cpp=.o)

PROG = battlemaze

default: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) -o $(PROG) $(OBJS) -L /usr/local/lib $(SFML_LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) -I /usr/local/include main.cpp

GameModel.o: GameModel.cpp
	$(CC) $(CFLAGS) -I /usr/local/include GameModel.cpp

GameController.o: GameController.cpp
	$(CC) $(CFLAGS) -I /usr/local/include GameController.cpp

Player.o: Player.cpp
	$(CC) $(CFLAGS) Player.cpp

Tile.o: Tile.cpp
	$(CC) $(CFLAGS) Tile.cpp

GameMap.o: GameMap.cpp
	$(CC) $(CFLAGS) GameMap.cpp


.PHONY: clean
clean:
	-rm -f *.o battlemaze
