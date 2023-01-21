CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS =
LDLIBS = `pkg-config --libs sdl2 SDL2_image`

all: game

SRC = game_of_life.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

game: game_of_life.o
	$(CC) $(CFLAGS) $(SRC) $(LDLIBS) -o $(EXE) 

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}
# END
