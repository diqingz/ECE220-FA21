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

/*
	Partners netID: staceyl2

*/

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		  name_ = name;
	}
	
  	string getName() {
		  return name_;
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
		  width_ = width;
		  length_ = length;
	}
	
  	double getArea() const {
		  return (double) width_*length_;
	}
	
  	double getVolume() const {
		  return 0;
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		double l = length_ + rec.getLength();
		double w = width_ + rec.getWidth();
		return Rectangle<T>(w,l);
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {
		double l = max((T)0, length_ - rec.getLength());
		double w = max((T)0, width_ - rec.getWidth());
		return Rectangle<T>(w,l);
	} 
	
	T getWidth() const { 
		return width_;
	}
	
	T getLength() const { 
		return length_;
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
		radius_ = radius;
	}
	
  	double getArea() const{
		return radius_*radius_*M_PI;
	}
	
 	double getVolume() const{
		return 0;
	}
	
  	Circle operator + (const Circle& cir){
		  double r = radius_ + cir.getRadius();
		  return Circle(r);
	}
	
	Circle operator - (const Circle& cir){
		  double r = radius_ - cir.getRadius();
		  return Circle(r);
	} 

	double getRadius() const { 
		return radius_;
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
		  radius_ = radius;
	}

  	double getVolume() const {
		  return (4.0/3.0)*radius_*radius_*radius_*M_PI;
	}	
	
  	double getArea() const {
		  return 4*M_PI*radius_*radius_;
	}

	Sphere operator + (const Sphere& sph) {
		  double r = radius_ + sph.getRadius();
		  return Sphere(r);
	}

	Sphere operator - (const Sphere& sph) {
		  double r = radius_ - sph.getRadius();
		  return Sphere(r);
	} 
	
	double getRadius() const {
		return radius_;
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
		length_ = length;
		width_ = width;
		height_ = height;
	}
	
  	double getVolume() const {
		  return length_*width_*height_;
	}
  	
	double getArea() const {
		return 2*(length_*width_+length_*height_+width_*height_);
	}
	
	RectPrism operator + (const RectPrism& rectp){
		double l = length_ + rectp.getLength();
		double w = width_ + rectp.getWidth();
		double h = height_ + rectp.getHeight();
		return RectPrism(w,l,h);
	}
	
	RectPrism operator - (const RectPrism& rectp){
		double l = max(0.0, length_ - rectp.getLength());
		double w = max(0.0, width_ - rectp.getWidth());
		double h = max(0.0, height_ - rectp.getHeight());
		return RectPrism(w,l,h);
	}	
	
	double getWidth() const { 
		return width_;
	}
	
	double getLength() const { 
		return length_;
	}
	
	double getHeight() const { 
		return height_;
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
	int totalNum = 0;
	ifstream myFile (file_name, ifstream::in);
	myFile >> totalNum;
	list<Shape*>myShape;
	string shape = "";
	getline(myFile, shape);
	for(int i = 0; i < totalNum; i++) {
		getline(myFile, shape, ' ');
		if(shape.compare("Circle") == 0){
			double r;
			myFile >> r;
			myShape.push_back(new Circle(r));
			
		} else if(shape.compare("Rectangle") == 0){
			double w;
			double l;
			myFile >> w >> l;
			myShape.push_back(new Rectangle<double>(w,l));
			
		} else if(shape.compare("Sphere") == 0){
			double r;
			myFile >> r;
			myShape.push_back(new Sphere(r));

		} else if(shape.compare("RectPrism") == 0){
			double w,l,h;
			myFile >> w >> l >> h;
			myShape.push_back(new RectPrism(w,l,h));
		}
		getline(myFile, shape); // blank line
	}
	myFile.close();
	return myShape;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	list<Shape*>:: iterator it;
	//@@Insert your code here
	for (it = shapes.begin(); it != shapes.end(); it++){
		if (((*it)->getArea()) > max_area) {
			max_area = (*it)->getArea();
		}
	}
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	list<Shape*>:: iterator it;
	//@@Insert your code here
	for (it = shapes.begin(); it != shapes.end(); it++){
		if (((*it)->getVolume()) > max_volume) {
			max_volume = (*it)->getVolume();
		}
	}
	return max_volume;
}
#endif
