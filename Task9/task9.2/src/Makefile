CC = gcc
CFLAGS = -lncurses
SRCS = main.c signal.c read_dir.c globals.c move_cursor.c draw.c
OBJS = $(SRCS:%.c=../build/%.o)

all: $(OBJS)
	$(CC) $(OBJS) -lncurses -o ../build/program.out

objs: $(OBJS)

../build/%.o: %.c
	$(CC) -c $< -o $@ -I../include/

clean:
	rm -f ../build/*.o ../build/*.out