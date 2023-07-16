.PHONY: sanitycheck all clean prepare tests cppcheck clangformat lizard flawfinder docs debug release flash 

sanitycheck:
	./scripts/sanity.sh

all: 
	@echo "Building keyfob firmware ... "	
	cmake --build build --config Debug --target clangformat
	cmake --build build --config Debug --target cppcheck_analysis
	cmake --build build --config Debug --target lizard
	cmake --build build --config Debug --target flawfinder
	cmake --build build --config Debug --target keyfob_tests
	cmake --build build/tests --config Debug --target coverage
	cmake --build build/src --config Release
	cmake --build build --config Debug --target docs
	@echo "Done!"	

clean:
	rm -rf build
	mkdir build

prepare:
	cmake --preset=Debug 
	cmake -S src/ -B build/src --preset=Debug 

tests:
	cmake --build build --config Debug --target keyfob_tests
	cmake --build build/tests --config Debug --target coverage

cppcheck:
	cmake --build build --config Debug --target cppcheck_analysis

clangformat:
	cmake --build build --config Debug --target clangformat

lizard:
	cmake --build build --config Debug --target lizard

flawfinder:
	cmake --build build --config Debug --target flawfinder

docs:
	cmake --build build --config Release --target docs

debug:
	cmake --build build/src --config Debug 

release:
	cmake -S src/ -B build/src --preset=Release
	cmake --build build/src --config Release

flash:
	@echo "Flashing..."
	STM32_Programmer_CLI -c port=SWD -e all
	STM32_Programmer_CLI -c port=SWD -w ./build/src/keyfob_firmware.bin 0x08000000 --verify
	@echo "Done!"
	@echo "Please restart the board and enjoy:)"


