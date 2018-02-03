DRIVER=answer
MAIN=main.c
TARGET=test

BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj
EXEC=$(BUILD_DIR)/$(TARGET)

OBJECTS:=accelerometer.o $(DRIVER).o 

all: $(OBJECTS)
	$(CC) $(MAIN) $(addprefix $(OBJ_DIR)/, $(OBJECTS)) -o $(EXEC)

%.o: %.c | mkdirobjdir
	gcc -c -o $(OBJ_DIR)/$@ $<

mkdirobjdir:
	mkdir -p $(OBJ_DIR)

clean:
	rm -f -r $(BUILD_DIR)/