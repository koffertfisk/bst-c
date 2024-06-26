C_COMPILER       = gcc
C_OPTIONS        = -Wall -pedantic -g -Iinclude
C_LINK_OPTIONS   = -lm
CUNIT_LINK       = -lcunit
VALGRIND         = valgrind
VALGRIND_FLAGS   = --leak-check=full

OBJ_DIR          = obj
SRC_DIR          = src
INCLUDE_DIR      = include
TESTS_DIR        = tests

BST_SRCS  = $(SRC_DIR)/bst.c
BST_OBJS  = $(BST_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: bst

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(C_COMPILER) $(C_OPTIONS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.c | $(OBJ_DIR)
	$(C_COMPILER) $(C_OPTIONS) -c $< -o $@

bst: $(BST_OBJS)
	$(C_COMPILER) $^ -o $@ $(C_LINK_OPTIONS) -c

bst_test: $(OBJ_DIR)/bst_test.o $(OBJ_DIR)/bst.o
	$(C_COMPILER) $^ -o $@ $(CUNIT_LINK)

memtest: all bst_test
	$(VALGRIND) $(VALGRIND_FLAGS) ./bst_test 

test: all bst_test
	./bst_test

clean:
	-$(RMDIR) $(OBJ_DIR) bst_test bst

RM = rm -f
RMDIR = rm -rf