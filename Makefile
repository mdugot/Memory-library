ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
PREFIX= ft_malloc
NAME= $(PREFIX)_$(HOSTTYPE)
LIB= lib$(NAME).so
LINK= lib$(PREFIX).so
CC= gcc
CFLAGS= -fno-builtin -Wall -Werror -Wextra
SRC_NAME= malloc.c
SRC_PATH= ./sources/
INC_PATH= ./includes/
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

.PHONY: all
all: $(LINK)

$(LINK): $(LIB)
	ln -s $(LIB) $(LINK)

$(LIB): $(OBJ)
	gcc -o $(LIB) -shared $(OBJ)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) -I$(INC_PATH) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH)

.PHONY: fclean
fclean: clean
	rm -fv $(LIB)
	rm -fv $(LINK)

.PHONY: re
re: fclean all

.PHONY: check
check:
	@echo "hostype = $(HOSTTYPE)"
	@echo "lib = $(LIB)"

.PHONY: test
test:
	rm -f test
	$(CC) $(CFLAGS) -I$(INC_PATH)  -L. -l$(PREFIX) -o test test.c
