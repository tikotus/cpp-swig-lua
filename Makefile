OBJ_FOLDER = obj
BIN_FOLDER = bin
SRC_FOLDER = src
O = main

SRC_FILES := $(wildcard $(SRC_FOLDER)/*.cpp)
OBJ_FILES := $(addprefix $(OBJ_FOLDER)/,$(notdir $(SRC_FILES:.cpp=.o)))

SWIG_I_FILES := $(wildcard $(SRC_FOLDER)/*.i)
SWIG_OBJS := $(addprefix $(OBJ_FOLDER)/,$(notdir $(SWIG_I_FILES:.i=_wrap.o)))

all: directories main

directories:
	mkdir -p $(OBJ_FOLDER)
	mkdir -p $(BIN_FOLDER)

main: $(OBJ_FILES) $(SWIG_OBJS)
	$(CXX) $^ -llua -Llib -Isrc -Isrc/lua -std=c++11 -o $(BIN_FOLDER)/$(O)

$(OBJ_FOLDER)/%.o: src/%.cpp
	$(CXX) -c -o $@ $<

$(OBJ_FOLDER)/%_wrap.o: src/%.i
	swig -c++ -lua -o $@.cxx $<
	$(CXX) -Isrc -c -o $@ $@.cxx

clean:
	rm -rf ./$(OBJ_FOLDER)/*
	rm ./$(BIN_FOLDER)/$(O)
