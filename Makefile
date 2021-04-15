.PHONY: clean mrproper
CXX = g++
CXXFLAGS = -c -I include -Wextra -Wall -std=c++14
LDFLAGS = -Llib -lsfml-graphics -lsfml-window -lsfml-system
EXEC = Ants

all: bin/$(EXEC)

bin/$(EXEC): bin/prog
	echo "#!/bin/bash\nexport LD_LIBRARY_PATH=lib\n./bin/prog" > bin/$(EXEC)
	chmod +x bin/$(EXEC)

bin/prog: bin/obj/main.o bin/obj/ant.o bin/obj/space.o
	export LD_LIBRARY_PATH=lib
	$(CXX) bin/obj/space.o bin/obj/main.o bin/obj/ant.o -o bin/prog $(LDFLAGS)

bin/obj/main.o: src/main.cpp
	$(CXX) src/main.cpp -o bin/obj/main.o $(CXXFLAGS)

bin/obj/ant.o: src/ant.cpp
	$(CXX) src/ant.cpp -o bin/obj/ant.o $(CXXFLAGS)

bin/obj/space.o: src/space.cpp
	$(CXX) src/space.cpp -o bin/obj/space.o $(CXXFLAGS)

clean:
	rm -rf bin/obj/*

mrproper: clean
	rm -f bin/$(EXEC) bin/prog
