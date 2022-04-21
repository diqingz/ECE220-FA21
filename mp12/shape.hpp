#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {

	}
	
  	string getName() {

	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {

	}
	
  	double getArea() const {

	}
	
  	double getVolume() const {

	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {

	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {

	} 
	
	T getWidth() const { 
	
	}
	
	T getLength() const { 
	
	}
private:
	T width_;
    T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {

	}
	
  	double getArea() const{

	}
	
 	double getVolume() const{

	}
	
  	Circle operator + (const Circle& cir){

	}
	
	Circle operator - (const Circle& cir){

	} 

	double getRadius() const { 
	
	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {

	}

  	double getVolume() const {

	}	
	
  	double getArea() const {

	}

	Sphere operator + (const Sphere& sph) {

	}

	Sphere operator - (const Sphere& sph) {

	} 
	
	double getRadius() const {
		
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {

	}
	
  	double getVolume() const {

	}
  	
	double getArea() const {

	}
	
	RectPrism operator + (const RectPrism& rectp){

	}
	
	RectPrism operator - (const RectPrism& rectp){

	}	
	
	double getWidth() const { 
	
	}
	
	double getLength() const { 
	
	}
	
	double getHeight() const { 

	}
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
	
	return list<Shape*>(0, NULL);;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here

	
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here

	
	return max_volume;
}
#endif

