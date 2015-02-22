
GPP=g++-4.9 -std=c++14

OBJ=cppshell.o

all: $(OBJ)
	$(GPP) $(OBJ) demo.cpp -o demo


%.o: %.cpp %.hpp
	$(GPP) -c $< -o $@

clean:
	$(RM) $(OBJ) demo
