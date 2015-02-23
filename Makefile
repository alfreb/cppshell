
GPP=g++-4.9 -std=c++14

OBJ=cppshell.o subprocess.o

# NOTE: subprocess need pthread
LIB=-pthread

all: $(OBJ)
	$(GPP) $(OBJ) $(LIB) demo.cpp -o demo


%.o: %.cpp %.hpp
	$(GPP) -c  $< -o $@

clean:
	$(RM)  $(OBJ)  demo
