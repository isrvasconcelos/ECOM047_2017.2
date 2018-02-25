BLOCKCHAIN=ICBlockchain
MAIN=main.c
TARGET=test

BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj
EXEC=$(BUILD_DIR)/$(TARGET)
CFLAGS=-lssl -lcrypto

OBJECTS:=ICBlock.o $(BLOCKCHAIN).o 

all: $(OBJECTS)
	gcc $(MAIN) $(addprefix $(OBJ_DIR)/, $(OBJECTS)) -o $(EXEC) $(CFLAGS)

%.o: %.c | mkdirobjdir
	gcc -c -o $(OBJ_DIR)/$@ $<

mkdirobjdir:
	mkdir -p $(OBJ_DIR)

run:
	$(EXEC)

clean:
	rm -f -r $(BUILD_DIR)/