
#ifndef _ALPHA_H_
#define _ALPHA_H_

#include "Image.h"
#include <string>

//A header file for Alpha class

class Alpha : public Image {
	
public:
  Alpha()=delete;
  //constructor	
  Alpha(const std::string& fileName);
  Alpha(std::istream& stream);
 
  Alpha(const Alpha& alpha);
  
  void operator=(const Alpha& alpha);
  
  //Behaves as if the filename ctor were called. Replaces any existing image.
  virtual void read(const std::string& fileName);
	  
  //Writes the image to the file indicated by the std::string filename.
  //Throws an explanatory std::string upon problems. 
  virtual void write(const std::string& fileName) const;
	  
  //Writes the image to the ostream given as an argument.
  virtual void write(std::ostream& stream) const;
  
  //overrided
  virtual int get(const int& colmn, const int& row) const; 
  
  virtual int range() const  {return 26;}   //will always be 26 for Alpha
    
  virtual void set(const int&column,const int&row,int value);

	  
protected:
  
  //read all lines from the input stream
  LineList readFile(std::ifstream& file);
  
  //read one ine from the given stream
  std::string readLine(std::istream& file);
  
  //preprocess a given file (i.e., remove space and comments)
  //@Input: input file data
  //@output preprocessed file
  LineList preProcessFile(const LineList& file);

  //preprocess a single line
  //@input: the input line
  //@output: preprocessed line. INVLID_LINE is returned if this file is not valid
  Line preProcessLine(const Line& line,  bool& autoComplete);
  
  //auto complete lines ends with *
  //@input: the list of lines to autocomplete
  //@input: the list of line indices that need auto complete
  //@output: the state of th auto complete operation
  bool processAutoCompleteList(LineList& lineList, const std::vector<size_t>& autoComplet);
  
  //check if the given line is valid
  //@input: line to check
  //@output: true if this line is valid
  bool isValidLine(const Line& line);

  //checks if the given files has lines of the same size
  bool isValidEqualSize(const LineList& file);
  
  //convert file list to matirx format
  //@input lineList line list to cnvert
  //@output the converted format
  FileFormat fromFileList2MatrixFormat(const LineList& lineList);

private:
};


#endif //_ALPHA_H_
