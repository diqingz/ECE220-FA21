student: shape.hpp main.cpp
	g++ main.cpp shape.hpp -o mp12

verify: check.cpp shape.hpp verify.cpp
	g++ -g -c check.cpp -o check.o
	g++ -g -c shape.hpp -o shape.o
	g++ -g -c verify.cpp -o verify.o
	ar rvs check.a check.o
	g++ -g verify.o check.a -o verify_mp12

clean:
	rm *.a *.o verify_mp12 mp12

#all: 
#	$(MAKE) verify.cpp