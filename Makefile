PROJECT = cyshell
#H_SOURCE = $(wildcard ./src/*.h)

DIR_OUT = obj
DIR_SRC += .
DIR_SRC = ./src
DIR_INC += $(addprefix -I, $(DIR_SRC))

C_SOURCE += $(wildcard $(addsuffix /*.c, $(DIR_SRC)))

OBJ := $(patsubst %.c, %.o, $(C_SOURCE))
 
CC = gcc

EXE := obj/$(PROJECT)
 
CC_FLAGS =		-c		\
		 					-Wall		\
							-O0		\
							-Werror		\
							-std=c11	\
							-Wextra	\
							-Wno-sign-compare		\
							-Wno-unused-parameter		\
							-Wno-unused-variable		\
							-Wshadow

RM = rm -rf
MD = $(shell mkdir -p $(DIR_OUT))

.PHONY:all

all:$(OBJ) $(EXE)
%.o: %.c
	@ echo 'Building target using GCC compiler:$@'
	$(MD)
	$(CC) $(DIR_INC) $(CC_FLAGS) $< -o $@
	@ echo ' '

$(EXE): $(OBJ)
	@ echo 'Building binary using GCC linker: $<'
	$(CC) $(OBJ) -lm -o $@ $(DIR_INC)
	@ echo 'Finished building binary: $@'
	@ echo ' '

	@ echo 'Removing remaining objects...'
	$(RM) $(DIR_SRC)/*.o
	@ echo 'Done!'
	@ echo ' '

clean:
	cd obj && $(RM) $(PROJECT)

memcheck: $(EXE)
	make && cd obj && valgrind --tool=memcheck --leak-check=full ./$(PROJECT) -e -s ../test/expressoes.txt

run: $(EXE)
	cd obj && ./${PROJECT} $(args)