CC = gcc
CFLAGS = -I../src -I../src/internal -Wall -Wextra -g

COMMON_SRCS = ../src/fat.c ../src/onboard_clock.c ../src/usb.c
COMMON_OBJS = $(COMMON_SRCS:.c=.o)

DEMO_SRCS = demo.c
DEMO_OBJS = $(DEMO_SRCS:.c=.o)
DEMO_OUT = demo

TEST_SRCS = tests.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_OUT = test_suite

.PHONY: all clean

all: $(DEMO_OUT) $(TEST_OUT)

$(DEMO_OUT): $(COMMON_OBJS) $(DEMO_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_OUT): $(COMMON_OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(COMMON_OBJS) $(DEMO_OBJS) $(TEST_OBJS) $(DEMO_OUT) $(TEST_OUT)
