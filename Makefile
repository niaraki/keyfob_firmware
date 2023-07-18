# Author: M.Niaraki
# Date : 07/18/2023

.PHONY: sanitycheck all clean prepare tests cppcheck clangformat lizard flawfinder docs debug release flash sure format

format:
	cmake --build build --config Debug --target clangformat_apply

sure: lizard clangformat cppcheck flawfinder
	@echo "Super, everything was perfect!"

sanitycheck:
	./scripts/sanity.sh

all: sure tests release docs
	@echo "Done!"	

clean:
	rm -rf build
	mkdir build

prepare:
	cmake --preset=Debug 
	cmake -S src/ -B build/src --preset=Debug 

tests:
	cmake --build build --config Debug 
	cd build && ctest --verbose
	cd ..
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

debug: format sure
	cmake --build build/src --config Debug 

release: format sure
	cmake -S src/ -B build/src --preset=Release
	cmake --build build/src --config Release

dependency:
	cd build/src && cmake ../src --graphviz=graph.dot && dot -Tpng graph.dot -o graph_image.png

flash:
	@echo "Flashing..."
	STM32_Programmer_CLI -c port=SWD -e all
	STM32_Programmer_CLI -c port=SWD -w ./build/src/keyfob_firmware.bin 0x08000000 --verify
	@echo "Done!"
	@echo "Please restart the board and enjoy:)"


