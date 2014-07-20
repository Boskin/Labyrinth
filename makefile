CC := g++ 

BIN := bin
INC := -I./include
LIB := lib
OBJ := obj
SRC := src

INCLUDE := $(addprefix -I./,$(wildcard $(SRC)/*/*)) 
LIBRARIES := $(wildcard $(LIB)/*.a)
OBJECTS := $(addprefix $(OBJ)/,$(addsuffix .o,$(basename $(notdir $(wildcard $(SRC)/*/*/*.cpp)))))

all: $(BIN)/main.exe

release: clean
	@echo Release...
	@rm $(BIN)/*.exe -f

clean:
	@echo Cleaning objects
	@rm $(OBJ)/*.o -f

test: $(BIN)/test.exe

$(BIN)/main.exe: $(OBJ)/main.o $(OBJECTS)
	@echo Linking main.exe
	@$(CC) $(OBJ)/main.o $(OBJECTS) $(LIBRARIES) -o $(BIN)/main.exe

$(BIN)/test.exe: $(OBJ)/test.o $(OBJECTS)
	@echo Linking test.exe
	@$(CC) -Wall $(OBJ)/test.o $(OBJECTS) $(LIBRARIES) -o $(BIN)/test.exe

# Entitiy build
$(OBJ)/%.o: $(SRC)/Entities/*/%.cpp $(SRC)/Entities/*/%.hpp $(SRC)/Entities/Object/object.cpp $(SRC)/Entities/Object/object.hpp
	@echo Compiling $*.cpp *Entity*
	@$(CC) -Wall $< -c -o $(OBJ)/$*.o $(INCLUDE) $(INC)

# Event build
$(OBJ)/%.o: $(SRC)/Events/*/%.cpp $(SRC)/Events/*/%.hpp $(SRC)/Events/Event/event.cpp $(SRC)/Events/Event/event.hpp
	@echo Compiling $*.cpp *Event*
	@$(CC) -Wall $< -c -o $(OBJ)/$*.o $(INCLUDE) $(INC)

$(OBJ)/%.o: $(SRC)/*/*/%.cpp $(SRC)/*/*/%.hpp
	@echo Compiling $*.cpp
	@$(CC) -Wall $< -c -o $(OBJ)/$*.o $(INCLUDE) $(INC)

$(OBJ)/main.o: $(SRC)/main.cpp
	@echo Compiling main.cpp
	@$(CC) $(SRC)/main.cpp -c -o $(OBJ)/main.o $(INCLUDE) $(INC)

$(OBJ)/test.o: $(SRC)/test.cpp
	@echo Compiling test.cpp
	@$(CC) $(SRC)/test.cpp -c -o $(OBJ)/test.o $(INCLUDE) $(INC)
