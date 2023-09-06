CC=gcc

INC_DEFAULT := -Iinclude
INC_CRITERION := -Ideps/criterion/include

CFLAGS := $(INC_DEFAULT) $(INC_CRITERION)

SRCS := $(wildcard src/**/*.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
BINS := src/libengine.a

TEST_SRCS := $(wildcard test/*.c)
TEST_OBJS := $(patsubst %.c, %.o, $(TEST_SRCS))
TEST_BINS := $(patsubst %.c, %.exe, $(TEST_SRCS))

CRITERION_LIB := deps/criterion/libcriterion.dll.a
CRITERION_DLL := deps/criterion/libcriterion-3.dll

test/%: test/%.o src/libengine.a | test/libcriterion-3.dll
	@$(CC) $(CFLAGS) $^ $(CRITERION_LIB) -o $@
	@echo $@ compiled.
	@"$@"

.SECONDARY: $(TEST_OBJS)

test/%.o: test/%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

src/libengine.a: $(OBJS)
	@ar rcs $@ $^

test/libcriterion-3.dll:
	@copy $(subst /,\,$(CRITERION_DLL)) .\test

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@del $(patsubst %, .\\%, $(subst /,\,$(OBJS)))
	@del $(patsubst %, .\\%, $(subst /,\,$(BINS)))
	@del $(patsubst %, .\\%, $(subst /,\,$(TEST_OBJS)))
	@del $(patsubst %, .\\%, $(subst /,\,$(TEST_BINS)))
	@del test\libcriterion-3.dll