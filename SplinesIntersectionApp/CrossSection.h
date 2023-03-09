#pragma once

#include <vector>
#include<algorithm>
#include "TreeNode.h"
#include "Point.h"
#include "CurveInterface.h"

const double R = 0.000000001;

class CrossSection
{
  public:
    CrossSection( CurveInterface* curveA, CurveInterface* curveB ) : curveA( curveA ), curveB( curveB ) {}
    ~CrossSection() 
    {
      if ( curveA != nullptr )
        delete curveA;

      if ( curveB != nullptr )
        delete curveB;
    }

    void Find( double tminA, double tminB, double Timemax ) const;

    double GetDistanceMin() const;
    std::vector<Point> GetResult() const { return result; }

    //добавляет точку
    static void AddCrossPoint( Point& point )
    {
      auto isNearExist = false;
      for ( auto& m_res : result )
      {
        if ( abs( m_res.x - point.x ) < R
          && abs( m_res.y - point.y ) < R )
        {
          isNearExist = true;
          break;
        }
      }

      if ( !isNearExist )
        result.push_back( point );
    }

    static void Distance( Curve* curveA, Curve* curveB )
    {
      if ( curveA != curveB )
        CrossSection::distance.push_back( curveA->distance( curveB ) );
    }

  private:
    CurveInterface* curveA;
    CurveInterface* curveB;

    static std::vector<Point> result;
    static std::vector<double> distance;
};

class Rect
{
  public:
    Rect( Curve* curve ) { create( curve ); }
    ~Rect()
    {
      if ( topLeft != nullptr )
        delete topLeft;

      if ( bottomRight != nullptr )
        delete bottomRight;
    }

     bool isCross( const Rect* rect, const double& edge ) const;
     bool isNear( const double& edge ) const;

  private:
    void create( Curve* curve );
    Point* topLeft,* bottomRight;
};
