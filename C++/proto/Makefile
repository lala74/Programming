# Compile under Linux desktop
CC = gcc
CXX = g++
INC = ./
INC_PARAMS=$(INC:%=-I%) $(shell pkg-config --cflags protobuf)
CXXFLAGS += -c -Wall -std=c++11 -O2
CFLAGS += -c -Wall -O2
LDLIBS = $(shell pkg-config --libs protobuf)

PROTO_FORMAT	= 			addressbook

BASE_OBJECTS 	=			$(PROTO_FORMAT).pb.o 

TARGET_READ 	=			read
TARGET_WRITE 	=			write



.PHONY: all all_
all_: $(TARGET_WRITE) $(TARGET_READ); $(info Compiling with ${CXX})

all:
	$(shell protoc -I=. --cpp_out=. $(PROTO_FORMAT).proto)
	make -j $(shell grep -c "^processor" /proc/cpuinfo) all_

$(TARGET_WRITE): $(TARGET_WRITE).o $(BASE_OBJECTS)
	$(CXX) $^ -Llib -o $(TARGET_WRITE) $(LDLIBS)

$(TARGET_READ): $(TARGET_READ).o $(BASE_OBJECTS)
	$(CXX) $^ -Llib -o $(TARGET_READ) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC_PARAMS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INC_PARAMS) $< -o $@

%.o: %.cc
	$(CXX) $(CFLAGS) $(INC_PARAMS) $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET_READ) $(TARGET_READ).o
	rm -f $(TARGET_WRITE) $(TARGET_WRITE).o
	rm -f $(BASE_OBJECTS)
	rm -f $(PROTO_FORMAT).pb.*

run: all;
	# ./server 8080