.PHONY: build run install test

build: install
	@cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=./conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
	@cd build && cmake --build .

run: build
	@cd build && ./poker-engine

install:
	@conan install . --output-folder=build --build=missing -s build_type=Release
	@conan install . --output-folder=build --build=missing -s build_type=Debug

test: build
	cd build && ctest --output-on-failure

debug: install
	@cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=./conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
	@cd build && cmake --build .
	lldb build/poker-engine

lint:
	find src test -name '*.cpp' -o -name '*.hpp' | xargs clang-format --style=file --dry-run -Werror
	run-clang-tidy -j $(shell sysctl -n hw.ncpu) -p build

format:
	find src test -name '*.cpp' -o -name '*.hpp' | xargs clang-format --style=file -i
	run-clang-tidy -fix -j $(shell sysctl -n hw.ncpu) -p build