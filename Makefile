CC=gcc
CFLAGS=-Iinclude

SRCS := $(wildcard src/**/*.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
BINS := src/libengine.a

TEST_SRCS := $(wildcard test/*.c)
TEST_OBJS := $(patsubst %.c, %.o, $(TEST_SRCS))
TEST_BINS := $(patsubst %.c, %.exe, $(TEST_SRCS))

test/%: test/%.o src/libengine.a
	@$(CC) $(CFLAGS) $^ -o $@
	@echo $@ compiled.
	@"$@"

.SECONDARY: $(TEST_OBJS)

test/%.o: test/%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

src/libengine.a: $(OBJS)
	@ar rcs $@ $^

src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@del $(patsubst %, .\\%, $(subst /,\,$(OBJS)))
	@del $(patsubst %, .\\%, $(subst /,\,$(BINS)))
	@del $(patsubst %, .\\%, $(subst /,\,$(TEST_OBJS)))
	@del $(patsubst %, .\\%, $(subst /,\,$(TEST_BINS)))