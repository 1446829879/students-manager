C=gcc
CFLAGS=-I./include
objects=./lib/stu.c ./lib/manager.c
main:./lib/libms.so
		$(CC) -g -o main main.c $(CFLAGS) -L./lib/ -Wl,-rpath=lib/ -lms
./lib/libms.so : $(objects)
		$(CC) -fPIC -shared $(CFLAGS) $(objects) -o ./lib/libms.so 
clean :
		rm -f *.o main *.so *.a

