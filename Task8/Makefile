CC = gcc
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
LIBSRC = add.c sub.c mul.c div.c
LIBOBJ = $(patsubst %.c, %.o, $(LIBSRC))
TARGET = a.out

# Зависит от main.o и libcalc.a.
# Сначала make соберёт все необходимые объектники, потом библиотеку, 
# после этого слинкует main.c с библиотекой
task1: main.o libcalc.so calc.h
	$(CC) main.c -o $(TARGET) -L. -lcalc -Wl,-rpath=.

task2: libcalc.so calc.h
	$(CC) main_dlfcn.c -o $(TARGET) -ldl -Wl,-rpath=.

# Просто соберёт все объектники из исходников.
objs: $(OBJ)

# Зависит от объектников.
# Библиотека будет пересобрана только, если 
# какой-то из арифметических .o изменился.
libcalc.so: $(LIBOBJ) calc.h
	$(CC) -shared $(LIBOBJ) -o libcalc.so

# псевдоним для сборки библиотеки
dynamic_lib: libcalc.so

# Общее правило сборки объектных файлов из исходных
%.o: %.c
	$(CC) -c -fPIC $< -o $@

# Удаляет все объектники, бинарник и библиотеку.
clean:
	rm -f *.o a.out libcalc.so



