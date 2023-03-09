#include "CrossSection.h"
#include<vector>

std::vector<Point> CrossSection::result = {};
std::vector<double> CrossSection::distance = {};

template <class T>
void find_intersections( T& itemA, T& itemB )
{
  auto curveAtemp = static_cast<CurveInterface*>( itemA );
  auto curveBtemp = static_cast<CurveInterface*>( itemB );

  //1. ѕроверить, что эти кривые ещЄ не отмечены как подобные.
  if ( curveAtemp == curveBtemp ||Time::m_isSimilarCurve )
    return;

  //2. ѕроверить, что ограничивающие пр€моугольники кривых пересекаютс€
  Rect* aRect(new Rect( curveAtemp->getCurve() ) );
  Rect* bRect( new Rect( curveBtemp->getCurve() ) );

  if ( !aRect->isCross( bRect, R ) )
  {
    //2.1 ≈сли не пр€моугольники не пересекаютс€ найти минимальное рассто€ние между точками кривых
    CrossSection::Distance( curveAtemp->getCurve() , curveBtemp->getCurve() );
    return;
  }

  //3. ≈сли отрезки кривых меньше R / 2, то можно считать, что пересечение найдено
  if ( aRect->isNear( R / 2 ) && bRect->isNear( R / 2 ) )
  {
    // 3.1 ƒл€ найденного пересечени€ сохранить наиболее близкое значение
    CrossSection::AddCrossPoint( curveAtemp->getCurve()->getVector().front() );
    Time::m_isSimilarCurve = true;
  Time::dt = 1.;
    return;
  }

  //4. –азделить кривые левую и правую часть
  Time::dt = Time::dt / 2.;

  CurveInterface* left = curveAtemp->subCurve( 0, 0.5 );
  CurveInterface* right = curveAtemp->subCurve( 0.5, 1.0 );

  auto pleft = new TreeNode<CurveInterface*>( left );
  auto pright = new TreeNode<CurveInterface*>( right );

  auto a = new TreeNode<CurveInterface*>( curveAtemp, pleft, pright );

  CurveInterface* Bleft = curveBtemp->subCurve( 0, 0.5 );
  CurveInterface* Bright = curveBtemp->subCurve( 0.5, 1.0 );

  pleft = new TreeNode<CurveInterface*>( Bleft );
  pright = new TreeNode<CurveInterface*>( Bright );

  auto b = new TreeNode<CurveInterface*>( curveBtemp, pleft, pright );

  //5. ѕродолжить поиск дл€ каждого отрезка кривой
  TreeNode<CurveInterface*>::Inorder( a, b, find_intersections );
}

void CrossSection::Find( double tminA, double tminB, double Timemax ) const
{
  CurveInterface* left = curveA->subCurve( tminA, Timemax / 2. );
  CurveInterface* right = curveA->subCurve( Timemax / 2., Timemax );

 auto pleft = new TreeNode<CurveInterface*>( left );
 auto pright = new TreeNode<CurveInterface*>( right );

 auto pA = new TreeNode<CurveInterface*>( curveA, pleft , pright );

  CurveInterface* Bleft = curveB->subCurve( tminB, Timemax / 2. );
  CurveInterface* Bright = curveB->subCurve( Timemax / 2., Timemax );

 pleft = new TreeNode<CurveInterface*>( Bleft );
 pright = new TreeNode<CurveInterface*>( Bright );

 auto pB = new TreeNode<CurveInterface*>( curveB, pleft, pright );

  Time::tA = tminA;
  Time::tB = tminB;
  Time::dt = Timemax;

 TreeNode<CurveInterface*>::Inorder( pA, pB, find_intersections );
}

double CrossSection::GetDistanceMin() const
{
  return *std::min_element( distance.begin(), distance.end() );
}

bool Rect::isCross( const Rect* rect, const double& edge ) const
{
  if ( topLeft->x > rect->bottomRight->x + edge
    || bottomRight->x + edge < rect->topLeft->x )
    return false;

  if ( topLeft->y > rect->bottomRight->y + edge
    || bottomRight->y + edge < rect->topLeft->y )
    return false;

  return true;
}

bool Rect::isNear( const double& edge ) const
{
  return ( pow( ( this->bottomRight->x - this->bottomRight->x ), 2 )
         + pow( this->topLeft->y - this->bottomRight->y, 2 ) < edge );
}

void Rect::create( Curve* curve )
{
  auto xmin = *std::min_element( curve->begin(), curve->end(), Point::compX );
  auto ymin = *std::min_element( curve->begin(), curve->end(), Point::compY );

  auto xmax = *std::max_element( curve->begin(), curve->end(), Point::compX );
  auto ymax = *std::max_element( curve->begin(), curve->end(), Point::compY );

  topLeft = new Point( xmin.x, ymin.y );
  bottomRight = new Point( xmax.x, ymax.y );
}

