#include "ParserFile.h"

#include <fstream>

ParserFile::Result ParserFile::ReadFile( const std::string& fileName )
{
  std::ifstream in( fileName );
  if ( !in.is_open() )
    return { false, "File read error." };

  while ( !in.eof() ) // чтении из файла
  {
     Point point;
     if ( !in.good() )
       return { false, "Input data error." };
     in >> point.x >> point.y;

     coordinates.push_back( point );
  }

  if ( coordinates.empty() )
    return { false, "Input data file is incorrect." };

  in.close();
  Parse();

  return { true };
}

ParserFile::Result ParserFile::WriteFile( const std::string& fileName, const std::string& dataOutput )
{
  std::ofstream out( fileName );
  if ( !out.is_open() )
    return { false, "File write error." };

  out << dataOutput << std::endl;
  out.close();

  return { true };
}

ParserFile::Result ParserFile::Parse( )
{
  int index = coordinates.size() / 2;
  for ( auto& cor : coordinates )
  {
    index-- > 0 ? curveA.push_back( cor ) : curveB.push_back( cor );
  }
  return { true };
}
