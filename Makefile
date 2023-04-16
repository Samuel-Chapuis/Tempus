CC = gcc
CFLAGS = -Wall -Wextra -I.
SDL_path = sdl
LDFLAGS =  -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf # -lSDL2main #-lSDL2_image -lSDL2_ttf -lSDL2_mixer
CPPFLAGS = -I $(SDL_path)/include -L $(SDL_path)/lib 

EXEC = Tempus.exe
SRC = $(wildcard *.c) $(wildcard lib/*/*.c) 
OBJ = $(SRC:.c=.o)
DEPS = definition.h


%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

go: $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(EXEC) $(OBJ) $(LDFLAGS)

# all:
#$(CC) $(CFLAGS) $(CPPFLAGS) -o $(EXEC) $(SRC) $(DEPS)  $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)