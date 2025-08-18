window_cli: main.cpp CLIWindowManager.h
	g++ -std=c++17 main.cpp -o window_cli

clean:
	rm -f window_cli

run: window_cli
	./window_cli
