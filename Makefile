SRCS = src/main.c src/mx_strlen.c src/mx_printerr.c src/mx_atoi.c src/mx_isdigit.c src/mx_isspace.c src/mx_printint.c src/mx_printchar.c src/mx_printstr.c
SRCSOB = main.c mx_strlen.c mx_printerr.c mx_atoi.c mx_isdigit.c mx_isspace.c mx_printint.c mx_printchar.c mx_printstr.c
INC = inc/mainhead.h
INCOB = mainhead.h
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

PROGA = race04

all: install clean

install: 
	@cp $(SRCS) .
	@cp $(INC) .
	@clang $(CFLAGS) -o $(PROGA) $(SRCSOB) -I $(INCOB)

uninstall: clean
	@rm $(PROGA)

clean: 
	@rm -rf $(INCOB)
	@rm -rf $(SRCSOB)

reinstall: uninstall all
