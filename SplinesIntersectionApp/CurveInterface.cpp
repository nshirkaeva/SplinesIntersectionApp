#include "CurveInterface.h"

CurveInterface* CurveBesier::subCurve( double t1, double t2 )
{
  const std::vector<Point> points = this->getVector();
  std::vector<Point> result = subCurve( points, t1, t2 );
  CurveBesier* curv = new CurveBesier( result );
  return curv;
}

Curve* CurveBesier::getCurve()
{
  return this->get();
}

std::vector<Point> CurveBesier::subCurve( const std::vector<Point>& curve, double t1, double t2 )
{
  std::vector<Point> result( curve.size() );
  for ( auto k = result.size(); k-- > 0;) {
    result[ k ] = point( curve, t1, curve.size() - 1, curve.size() - 1, t2, curve.size() - 1 - k );
  }
  return result;
}

Point CurveBesier::point( const std::vector<Point>& curve, double t, size_t n, size_t i )
{
  return n == 0 ? curve[ i ] : ( point( curve, t, n - 1, i - 1 ) * ( 1 - t ) + point( curve, t, n - 1, i ) * t );
}

Point CurveBesier::point( const std::vector<Point>& curve, double t )
{
  return point( curve, t, curve.size() - 1, curve.size() - 1 );
}

Point CurveBesier::point( const std::vector<Point>& curve, double t1, size_t n, size_t i, double t2, size_t k )
{
  return n > k ? ( point( curve, t1, n - 1, i - 1, t2, k ) * ( 1 - t2 ) +
    point( curve, t1, n - 1, i, t2, k ) * t2 )
    : point( curve, t1, n, i );
}
