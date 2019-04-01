
#ifndef _PGM_H_
#define _PGM_H_

#include "Image.h"

//header file for PGM class
class PGM: public Image{
	
public:
  //constructors
   PGM()=delete;
   PGM(const std::string& fileName);
  ~PGM(){}
  //copy constructor
  PGM(const PGM & p);
  PGM(std::ifstream& stream);

  void operator=(const PGM& pgm);
  
  //Behaves as if the filename ctor were called. Replaces any existing image.
  virtual void read(const std::string& fileName);
	  
  //Writes the image to the file indicated by the std::string filename.
  //Throws an explanatory std::string upon problems. 
  virtual void write(const std::string& fileName) const;
	  
  //Writes the image to the ostream given as an argument.
  virtual void write(std::ostream& stream) const;

//   virtual void set(const int&column,const int&row,int value);
  
protected:
  std::vector<int> readNumbersFromFile(std::istream& stream);
  void  readPgmFile(std::istream& stream);
};


#endif //_PGM_H_
