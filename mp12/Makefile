student: shape.hpp main.cpp
	g++ main.cpp shape.hpp -o mp12 -Wall -Werror

verify:  shape.hpp verify.cpp
	g++ -g -c shape.hpp -o shape.o -Wall -Werror
	g++ -g -c verify.cpp -o verify.o
	g++ -g verify.o shape.hpp check.a -o verify_mp12

clean:
	rm  *.o mp12
