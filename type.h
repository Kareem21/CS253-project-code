
//contain type definition 
#ifndef _TYPE_H_
#define _TYPE_H_

#include <iostream>
#include <vector>
#include <string>

#include "constants.h"

//a structure to hold  command line options
struct CommandLineOptions{
  bool doubleOutputSize;
  bool halfOutputSize;
  bool mirrorImage;
  
  bool rotateImage;
  int rotateDegree;
  
  bool                      readFromFile;
  std::vector<std::string>  fileNames;
};
//our data structure to represent one line of the file
typedef std::string Line ;

//our data type to represent an array of lines
typedef std::vector<Line> LineList;

typedef std::vector< std::vector<int>> MatrixInt;

struct FileFormat{
	
  FileType type;
  std::string label;   //Alpha or P2
		 
  bool isValid;   //is this file valid
  
  int width;      //file width
  int height;     //file height
  int extra;      //extra field
  
  MatrixInt data; //data section
};

#endif //_TYPE_H_