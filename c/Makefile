.DEFAULT_GOAL := all

CC = gcc
CFLAGS = -I. -Wall

BUILD_DIR = ./_build
BIN_DIR = $(BUILD_DIR)/bin
OBJ_DIR = $(BUILD_DIR)/obj

DEPS = $(wildcard utils/*.c)
DEPSO = $(foreach dep,$(DEPS),$(OBJ_DIR)/$(basename $(notdir $(dep))).o)

PROGRAMS = $(basename $(wildcard *.c))

_build/bin:
	$(shell mkdir -p $(BIN_DIR))

_build/obj:
	$(shell mkdir -p $(OBJ_DIR))

_build: _build/bin _build/obj

$(DEPSO): $(OBJ_DIR)/%.o: utils/%.c _build
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN_DIR)/%: %.c $(DEPSO)
	$(CC) -o $@ $(DEPSO) $< $(CFLAGS)

deps: $(DEPSO)

all: $(foreach program,$(PROGRAMS),$(BIN_DIR)/$(program))

.PHONY: clean
clean:
	rm -fr $(BUILD_DIR) *.o
