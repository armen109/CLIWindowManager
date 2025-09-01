SRC = {wildcard src/*.cpp}
OBJ = {patsubst src/%.cpp,obj/%.o,$(SRC)}

.PHONY:program

program : $(OBJ)
	@mkdir -p bin
	g++ $^ main.cpp -o bin/program  

obj/%.o : src/%.cpp
	g++ -c $< -o $@

window_cli: main.cpp CLIWindowManager.h
	g++ -std=c++17 main.cpp -o window_cli

clean:
	rm -f window_cli

run: window_cli
	./window_cli
