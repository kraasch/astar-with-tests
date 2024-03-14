
all:
	@make clean
	@make build
	@make run

clean:
	@rm -rf ./build/
	@mkdir -p ./build/

.PHONY: build
build:
	#clang++ -v ./src/main.cpp -o ./build/test
	g++ -Wall -g -pthread ./test/findpath_unittest.cpp -lgtest_main -lgtest -lpthread -o ./build/test
	#g++ -g -O2 -std=gnu++17 -static -o {executable} -lrt -Wl,--whole-archive -lpthread -Wl,--no-whole-archive {files}

run:
	@echo
	@./build/test
	@echo

setup:
	sudo apt-get install libgtest-dev

