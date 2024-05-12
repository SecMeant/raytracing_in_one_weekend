CXX:=clang++

CXX_FLAGS:=-Wall -Wextra -std=c++20 -O2

LINK_OPTS:=-lfmt

all: ppm

ppm: ppm.cc
	$(CXX) $< -o $@ $(LINK_OPTS) $(CXX_FLAGS)

clean:
	rm -f ppm image.ppm

.PHONY: clean
