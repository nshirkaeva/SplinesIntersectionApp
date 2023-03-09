#include "Point.h"

class CurveInterface
{
public:
  virtual ~CurveInterface() {}
  virtual CurveInterface* subCurve( double t1, double t2 ) = 0;
  virtual Curve* getCurve() = 0;
};

class CurveBesier : public CurveInterface, Curve
{
public:
  CurveBesier( const std::vector<Point>& curve ) : Curve( curve ) {}
  CurveInterface* subCurve( double t1, double t2 ) override;
  Curve* getCurve() override;

private:
  std::vector<Point> subCurve( const std::vector<Point>& curve, double t1, double t2 );
  Point point( const std::vector<Point>& curve, double t, size_t n, size_t i );
  Point point( const std::vector<Point>& curve, double t );
  Point point( const std::vector<Point>& curve, double t1, size_t n, size_t i, double t2, size_t k );
};