##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Arcade
##

SFMLSRC	=	sources/graphic/sfml/sfml.cpp 	\

SDLSRC	=	sources/graphic/sdl2/sdl2.cpp	\

NCURSESSRC	=	sources/graphic/ncurses/ncurses.cpp	\

NIBBLERSRC	=	sources/games/nibbler/nibbler.cpp 	\

PACMANSRC	=	sources/games/pacman/pacman.cpp 	\


SRC	=	sources/core/main.cpp	\
		sources/core/core.cpp	\

CC	=	g++

CPPFLAGS	= -I./includes/ -I./sources/graphic -I./sources/graphic/sfml -I./sources/games/nibbler -I./sources/games/pacman -I./errors

SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SDLFLAGS = `sdl2-config --cflags --libs`

SFMLOBJ = $(SFMLSRC:.cpp=.o)

SDLOBJ = $(SDLSRC:.cpp=.o)

NCURSESOBJ = $(NCURSESSRC:.cpp=.o)

ARCADEOBJ = $(SRC:.cpp=.o)

NIBBLEROBJ = $(NIBBLERSRC:.cpp=.o)

PACMANOBJ = $(PACMANSRC:.cpp=.o)

NAMENIB = arcade_nibbler.so

NAMEPAC = arcade_pacman.so

NAMESFML = arcade_sfml.so

NAMESDL = arcade_sdl2.so

NAMENCURSE = arcade_ncurses.so

NAMEPACMAN = arcade_pacman.so

all: core graphicals games

core: arcade

graphicals: sfml sdl ncurses
			if test -d lib; then mv *.so ./lib/; else mkdir lib && mv *.so lib; fi

games:  nibbler pacman
		if test -d lib; then mv *.so ./lib/; else mkdir lib && mv *.so lib; fi
	   

nibbler: $(NIBBLEROBJ)
	$(CC) $(NIBBLERSRC) -o $(NAMENIB) --shared -fPIC -fno-gnu-unique $(CPPFLAGS)

pacman: $(PACMANOBJ)
	$(CC) $(PACMANSRC) -o $(NAMEPACMAN) --shared -fPIC -fno-gnu-unique $(CPPFLAGS)

sfml: $(SFMLOBJ)
	$(CC) $(SFMLSRC) -o $(NAMESFML)  --shared -fPIC -fno-gnu-unique $(CPPFLAGS) $(SFMLFLAGS)

sdl: $(SDLOBJ)
	$(CC) $(SDLSRC) -o $(NAMESDL)  --shared -fPIC -fno-gnu-unique -lSDL2_image -lSDL2_ttf $(CPPFLAGS) $(SDLFLAGS)

ncurses: $(NCURSESOBJ)
	$(CC) $(NCURSESSRC) -o $(NAMENCURSE)  --shared -fPIC -fno-gnu-unique -lncurses $(CPPFLAGS)

arcade: $(ARCADEOBJ)
	$(CC) $(SRC) -o arcade -ldl -lstdc++fs $(CPPFLAGS)

clean:
		rm -f sources/graphic/ncurses/*.o
		rm -f sources/graphic/sfml/*.o
		rm -f sources/graphic/sdl2/*.o
		rm -f sources/core/*.o
		rm -f sources/games/nibbler/*.o
		rm -f sources/games/pacman/*.o
		rm -f errors/*.o
		rm -f *.so

fclean: clean
		rm -rf ./lib
		rm -f arcade

re: fclean all

.PHONY: all clean fclean re