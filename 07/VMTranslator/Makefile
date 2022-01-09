CC := g++
COMPILER_FLAGS := -std=c++2a
HEADERS_FLAG := -I./src/headers
SRCS := $(shell find ./src -name '*.cpp')

all : $(SRCS)
	$(CC) $(COMPILER_FLAGS) $(HEADERS_FLAG) $(SRCS) -o vmTranslator
