
GPP=g++ -std=c++14

OBJ = cppshell.o subprocess.o 
PROG = two_way_test_program


# NOTE: subprocess need pthread
LIB=-pthread

all: $(OBJ) $(PROG)
	$(GPP) $(OBJ) $(LIB) demo.cpp -o demo


%.o: %.cpp %.hpp
	$(GPP) -c  $< -o $@

%:%.cpp
	$(GPP) $< -o $@

clean:
	$(RM)  $(OBJ)  $(PROG) demo
