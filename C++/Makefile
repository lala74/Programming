# Compile under Linux desktop
VERSION := $(shell python3 -E ../Python/version.py)
USER:= $(shell git config user.name)
CC = gcc
CXX = g++
INC = ./ ./include/
INC_PARAMS=$(INC:%=-I%) $(shell pkg-config --cflags glib-2.0 gio-unix-2.0)
CXXFLAGS += -c -Wall -Werror -std=c++11 -O2
CFLAGS += -c -Werror -O2
LDLIBS = -lcrypt -lcrypto $(shell pkg-config --libs glib-2.0 gio-unix-2.0)

BASE_OBJECTS = 		src/file.o \
					src/HLT_CAppProperties.o \
					src/HLT_shell_utils.o \
					src/HLT_crypto.o \
					src/HLT_CConfigFileManager.o \
					src/CString.o \
					src/HLT_UsbServiceControl.o \
					src/HLT_Cprocess.o \
					main.o

BASE_TARGET = main


ifeq ($(USE_CLANG),1)
	ifeq ($(shell clang++ -v 2>&1 | grep -c "clang version"), 1)
		CC=clang
		CXX=clang++
	endif
endif
CXXFLAGS += -g -DTEST_ON_LINUX_DESKTOP

.MAKE: all

.PHONY: all_ all
all_: $(BASE_TARGET) ; $(info Compiling with ${CXX})
	@echo 
	@echo Version $(VERSION) built by $(USER)
	@echo -n $(HLT_VERSION) > $(FACTORY_APP_TARGET).version.txt
	@echo

all:
	make -j $(shell grep -c "^processor" /proc/cpuinfo) all_

# Add -L./lib before -Llib to override Actia dynamic libraries linking with your own libraries
$(BASE_TARGET): $(BASE_OBJECTS)
	$(CXX) $^ -Llib -o $(BASE_TARGET) $(LDFLAGS) $(LDLIBS)

src/HLT_CAppProperties.o: src/HLT_CAppProperties.cpp
	$(CXX) $(CXXFLAGS) -DHLT_VERSION="\"$(HLT_VERSION)\"" -DHLT_USER="\"$(HLT_USER)\"" $(INC_PARAMS) $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC_PARAMS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INC_PARAMS) $< -o $@

HLT_CAppProperties.o: FORCE
#force recompilation of HLT_CAppProperties.cpp to refresh build time and version

.PHONY: FORCE
FORCE:

.PHONY: clean
clean:
	rm -f ${FILENAME}.o
	rm -f $(BASE_TARGET) $(BASE_OBJECTS) $(DBUSOBJECTS)
	rm -f main.version.txt

run: all
	./$(BASE_TARGET)