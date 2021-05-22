CXX       := gcc
CXX_FLAGS := -ggdb

BIN     := bin
SRC     := .
INCLUDE := include

LIBRARIES   :=
EXECUTABLE  := main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

# $^ => all files (nanoml.c & $(SRC)/**/*.c) 
# $@ => target ($(BIN)/$(EXECUTABLE))

$(BIN)/$(EXECUTABLE): main.c $(SRC)/**/*.c
	mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*