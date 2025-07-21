CC = gcc
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
LIBSRC = add.c sub.c mul.c div.c
LIBOBJ = $(patsubst %.c, %.o, $(LIBSRC))
TARGET = a.out

# Зависит от main.o и libcalc.a.
# Сначала make соберёт все необходимые объектники, потом библиотеку, 
# после этого слинкует main.c с библиотекой
all: main.o libcalc.a
	$(CC) main.c -o $(TARGET) -L. -lcalc

# Просто соберёт все объектники из исходников.
objs: $(OBJ)

# Зависит от объектников.
# Библиотека будет пересобрана только, если 
# какой-то из арифметических .o изменился.
libcalc.a: $(LIBOBJ)
	ar rc libcalc.a $(LIBOBJ)

# псевдоним для сборки библиотеки
static_lib: libcalc.a

# Общее правило сборки объектных файлов из исходных
%.o: %.c
	$(CC) -c $< -o $@

# Удаляет все объектники, бинарник и статическую библиотеку.
clean:
	rm -f *.o a.out libcalc.a