#include "polygons.h"
#include <iostream>

// constructor
Polygon::Polygon(const std::string &name, const std::vector<Point> &points)
  : name_(name), points_(points)
{
}

// destructor
Polygon::~Polygon()
{
}

bool Polygon::HasAllEqualSides() const
{
    if (points_.size() < 3) return true; // A polygon with less than 3 sides has all equal sides

    double first_side = sqrt(pow(points_[0].x() - points_[1].x(), 2) + pow(points_[0].y() - points_[1].y(), 2));
    for (size_t i = 1; i < points_.size(); ++i)
    {
        double side = sqrt(pow(points_[i].x() - points_[(i+1)%points_.size()].x(), 2) + pow(points_[i].y() - points_[(i+1)%points_.size()].y(), 2));
        if (side != first_side)
            return false;
    }
    return true;
}

bool Polygon::HasAllEqualAngles() const
{
    if (points_.size() < 3) return true; // A polygon with less than 3 sides has all equal angles

    std::vector<double> angles;
    for (size_t i = 0; i < points_.size(); ++i)
    {
        Point p1 = points_[i];
        Point p2 = points_[(i+1)%points_.size()];
        Point p3 = points_[(i+2)%points_.size()];

        double a = sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));
        double b = sqrt(pow(p2.x() - p3.x(), 2) + pow(p2.y() - p3.y(), 2));
        double c = sqrt(pow(p3.x() - p1.x(), 2) + pow(p3.y() - p1.y(), 2));
        double cos_angle = (a*a + b*b - c*c) / (2*a*b);
        double angle = acos(cos_angle) * 180.0 / M_PI;
        angles.push_back(angle);
    }

    double first_angle = angles[0];
    for (size_t i = 1; i < angles.size(); ++i)
    {
        if (angles[i] != first_angle)
            return false;
    }
    return true;
}
// print polygon details
void Polygon::print() const
{
  std::cout << "Polygon " << getName() << " with vertices: ";
  for (const auto& p : getPoints()) {
    std::cout << "(" << p.x() << ", " << p.y() << ") ";
  }
  std::cout << std::endl;
  std::cout << "  Area: " << area() << std::endl;
  std::cout << "  All sides are equal: " << (HasAllEqualSides() ? "Yes" : "No") << std::endl;
  std::cout << "  All angles are equal: " << (HasAllEqualAngles() ? "Yes" : "No") << std::endl;
}