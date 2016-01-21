GPP=g++-4.9 -std=c++14 -O3 -Wall -Wextra
INC=-I../inc/
SRC = ../src/cppshell.cpp ../src/pipe.cpp ../src/subprocess.cpp

# NOTE: subprocess need pthread
LIB=-pthread

all: demo dep

demo: demo.cpp
	${GPP} ${INC} -odemo demo.cpp ${SRC} ${LIB}

dep: two_way_test_program.cpp
	${GPP} -otwo_way_test_program two_way_test_program.cpp

clean:
	rm -f demo two_way_test_program
