
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

#include "TreeNode.h"
#include "CrossSection.h"
#include "ParserFile.h"

int main()
{
  std::cout << "Enter path to data file (../Data/DataInput.txt): ";
  std::string filename;
  std::cin >> filename;

  ParserFile parseFile;
  auto result = parseFile.ReadFile( filename );

  if ( !result.Success )
  {
    std::cout << "It is not possible to read data: " << result.Message << std::endl;
    system( "pause" );
    return 0;
  }

  auto curve1 = parseFile.GetCurveA();
  auto curve2 = parseFile.GetCurveB();

  auto* CurveBesier1( new CurveBesier( curve1 ) );
  auto* CurveBesier2( new CurveBesier( curve2 ) );

  CrossSection cross( CurveBesier1, CurveBesier2 );

  double tminA = 0.;
  double tminB = 0.;
  double tmax = 1.;

  cross.Find( tminA, tminB, tmax );

  auto res = cross.GetResult();
  
  delete CurveBesier1;
  delete CurveBesier2;

  std::string resStr;
  if ( res.empty() )
  {
    resStr = "Results not found ";
    resStr += " Min distance between curves = " + std::to_string( cross.GetDistanceMin() );
  }
  else
  {
    resStr = "Point Intersections : count " + std::to_string( res.size() ) + "\n";
    for ( auto& aData : res )
    {
      resStr += " x = " + std::to_string( aData.x ) + "  y = " + std::to_string( aData.y ) + "\n";
    }
  }
  std::cout << resStr << std::endl;

  std::cout << "Enter path file to out data (../Data/DataOutput.txt): ";
  std::string filenameOut;
  std::cin >> filenameOut;
  auto resultWrite = parseFile.WriteFile( filenameOut, resStr );

  if ( !resultWrite.Success )
    std::cout << "\nIt is not possible to write result: " << resultWrite.Message << std::endl;
  else
    std::cout << "\nThe result is written to a file \"" << filenameOut << "\"" << std::endl;

  system( "pause" );
  return 0;
}

