#ifndef __POLYGONS_H__
#define __POLYGONS_H__

#include <string>
#include <vector>

// ------------------------------------------------------------------------------

class Point {
public:
  Point(double x=0, double y=0) : x_(x), y_(y) {}
  double x() const { return x_; }
  double y() const { return y_; }
private:
  double x_;
  double y_;
};

// ------------------------------------------------------------------------------

class Polygon {
public:
  // constructor and destructor
  Polygon(const std::string &name, const std::vector<Point> &points);
  virtual ~Polygon();
  // accessors
  std::string getName() const { return name_; }
  std::vector<Point> getPoints() const { return points_; }
  // generic properties
  virtual double area() const = 0;
  virtual bool HasAllEqualSides() const;
  virtual bool HasAllEqualAngles() const;
  // output
  void print() const;
private:
  std::string name_;
  std::vector<Point> points_;
};

// ------------------------------------------------------------------------------

class Triangle : public Polygon {
public:
  Triangle(const std::string &name, const std::vector<Point> &points);
  virtual ~Triangle();
  virtual double area() const;
  virtual bool HasAllEqualAngles() const;
};

// ------------------------------------------------------------------------------

class IsoscelesTriangle : public Triangle {
public:
  IsoscelesTriangle(const std::string &name, const std::vector<Point> &points);
  virtual ~IsoscelesTriangle();
  virtual bool HasAllEqualSides() const;
};

// ------------------------------------------------------------------------------

class EquilateralTriangle : public IsoscelesTriangle {
public:
  EquilateralTriangle(const std::string &name, const std::vector<Point> &points);
  virtual ~EquilateralTriangle();
  virtual bool HasAllEqualSides() const;
};

// ------------------------------------------------------------------------------

class Quadrilateral : public Polygon {
public:
  Quadrilateral(const std::string &name, const std::vector<Point> &points);
  virtual ~Quadrilateral();
  virtual double area() const;
};

// ------------------------------------------------------------------------------

class Rectangle : public Quadrilateral {
public:
  Rectangle(const std::string &name, const std::vector<Point> &points);
  virtual ~Rectangle();
  virtual bool HasAllEqualAngles() const;
};

// ------------------------------------------------------------------------------

class Square : public Rectangle {
public:
  Square(const std::string &name, const std::vector<Point> &points);
  virtual ~Square();
  virtual bool HasAllEqualSides() const;
};

#endif // __POLYGONS_H__