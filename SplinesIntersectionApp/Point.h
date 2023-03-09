#pragma once

#include<vector>
#include <iterator>

class Point
{
  public:
    Point() { x = NULL; y = NULL; }
    Point( double x, double y ) : x( x ), y( y ) {}

    double distance( Point b) const;

    // открытый элемент, допускающий обновление
    double x;
    double y;

  Point operator*( double b )
  {
    this->x *= b;
    this->y *= b;

    return *this;
  }

  Point operator+( Point b )
  {
    this->x += b.x;
    this->y += b.y;

    return *this;
  }

  static bool compX( Point const& lhs, Point const& rhs ) {
    return lhs.x < rhs.x;
  }

  static bool compY( Point const& lhs, Point const& rhs ) {
    return lhs.y < rhs.y;
  }

};

class Curve
{
  public:
    Curve( std::vector<Point> curve ) : curve( curve ) {}

    inline size_t size() { return curve.size(); }

    inline std::vector<Point>::const_iterator begin() { return curve.begin(); }
    inline std::vector<Point>::const_iterator end() { return curve.end(); }

    inline Curve* get() { return this; }
    inline void set( Curve* curve ) { this->setVector( curve->getVector() ); }

    inline std::vector<Point> getVector() const { return curve; }
    void setVector( std::vector<Point> curve );

    double distance( Curve* curve ) const;

  private:
    std::vector<Point> curve;
};
