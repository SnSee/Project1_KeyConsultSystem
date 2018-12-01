src = $(wildcard *.cpp)
target = $(patsubst %.cpp, %.o, $(src))

IPath = -I/usr/local/include
LPath = -L/usr/local/lib
lName = -lssl -lcrypto

all:$(target)
	g++ $^ -o srvMain $(IPath) $(LPath) $(lName)

%.o:%.cpp
	g++ -c $< -o $@

clean:$(target)
	rm $(target)

.PHONY: all clean
