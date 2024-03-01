# -------- 文件目录 --------
SRC_DIR=./src
LIB_DIR=./build
TEST_DIR=./tests
LCTHW_DIR=./src/lcthw
OBJ_DIR=./obj

# -------- 编译选项 --------
CFLAGS=-g -O2 -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
CC=gcc
# LIBS=-ldl $(OPTLIBS)
LIBS=-ldl -lbsd $(OPTLIBS)
PREFIX?=/usr/local

# -------- 变量 --------
SOURCES=$(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
# 修改OBJECTS变量，将生成的.o文件放到src/lcthw/build目录中
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard $(TEST_DIR)/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=$(LIB_DIR)/liblcthw.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# -------- 脚本执行 --------
# The Target Build
all: $(TARGET) $(SO_TARGET) tests objs 

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

# Static Lib
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

# Dynamic Lib
$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

# obj files
objs:$(OBJECTS)
	@mv $^ $(OBJ_DIR)

build:
	@mkdir -p build
	@mkdir -p bin
	@mkdir -p obj

# The Unit Tests
.PHONY: tests
tests: CFLAGS += -Isrc
tests: $(TESTS)
$(TESTS): $(TARGET) $(TEST_SRC) 
	$(CC) $(CFLAGS) $@.c  -o $@  $(TARGET)


run_test:
	sh ./tests/runtests.sh

# valgrind
valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS) $(OBJ_DIR)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true
