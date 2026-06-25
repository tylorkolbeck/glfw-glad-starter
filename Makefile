.PHONY: all build run sync clean

# Default rule when you just type 'make'
all: sync build

# 1. Complete project synchronization (Fixes tracking and updates Neovim LSP)
sync:
	@echo "Checking files and updating Neovim compilation flags..."
	@cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	@ln -sf build/compile_commands.json .

# 2. Compile the binaries
build:
	@echo "Compiling code..."
	@cmake --build build

# 3. Execute the binary target
run:
	@./build/App

# 4. Wipe out the cache directories if things get weird
clean:
	@echo "Cleaning build cache..."
	@rm -rf build compile_commands.json
