CC=c++
LDLIBS=-lglfw -lglew -framework OpenGL

foo: foo.o

clean:
	rm -f foo *.o
