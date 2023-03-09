#include "Point.h"

double Point::distance( Point b ) const
{
  return sqrt( pow( ( b.x - x ), 2 ) + pow( ( b.y - y ), 2 ) );
}

void Curve::setVector( std::vector<Point> curve )
{
  this->curve.reserve( curve.size() );

  std::copy( curve.begin(), curve.end(), std::back_inserter( this->curve ) ); 
}

double Curve::distance( Curve* curve ) const
{
  auto vPoints1 = this->getVector();
  auto vPoints2 = curve->getVector();

  auto flag = true;
  auto min = -1.;
  for ( auto& points : vPoints1 )
  {
    for ( auto& pointsy : vPoints2 )
    {
      min = flag ? points.distance( pointsy )
        : points.distance( pointsy ) < min
        ? points.distance( pointsy ) : min;
      flag = false;
    }
  }
  return min;
}
