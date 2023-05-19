.PHONY: all build clean

all: clean build

build:
	mkdir build && cd build && cmake .. && make && cd ..

clean:
	rm -rf build