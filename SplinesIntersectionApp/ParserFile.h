#pragma once
#include <string>
#include "CrossSection.h"

/**
This class parse input data from the txt-file

*/
class ParserFile
{
  public:

    struct Result
    {
      bool Success;
      std::string Message = "";
    };

    /** \details
    \returns
    success true if reading file is successeful otherwise error message

    \param
    path and name of the input data file.
    */
    Result ReadFile( const std::string& fileName );

    /** \details
    \returns
    success true if writting file is successeful otherwise error message

    \param
    path and name of the output data file.
    */
    Result WriteFile( const std::string& fileName, const std::string& dataOutput );

     std::vector<Point> GetCurveA() { return curveA; }
     std::vector<Point> GetCurveB() { return curveB; }

  private:
    Result Parse();

    std::vector<Point> coordinates;
    std::vector<Point> curveA;
    std::vector<Point> curveB;
};

