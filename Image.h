#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "type.h"
#include<iostream>


// 1 - get rid of namespace std when done


class Image{
public:
  class iterator{
  public:
      iterator() : image(nullptr) ,i(0),j(0){} //constructor    
      iterator(const iterator &it)
      {
          i = it.i;
          j = it.j;              
          image = it.image;  
      }
      iterator(const Image *im,int a,int b) : image(im),i(a),j(b) {}
      
      iterator& operator++() 
      {
            if(j == image->height() - 1 && i == image->width() -1) //col width
            {
                std::string str = "can't go past iterator end";
                throw str;
            }
                      
            if(i < image->width() && j < image->height())
              i++;
            if(i == image->width() && j<image->height())
            {
                i = 0;j++;
            }
          return *this;
      }
      iterator operator++(int)
      {
        const auto save = *this;  
        ++*this;
        return save;
      }
      iterator &operator--()
      {
//           if(i == 0 && j == 0)
//               return *this;
          if(i == 0 && j>0)
          {   
//              cout<<" i : "<<i<<"  j : "<<j<<endl;
             j--;
             i = image->width()-1 ;
          }
          else if(i < image->width() && j >= 0)
          {
                    i--;
          }

          return *this;
      }
      iterator operator--(int)
      {
        const auto save = *this;  
        --*this;
        return save;
      }
      int operator*() const //does const on write prevent from writing to *it?
      {
          return (image->get(i,j));
      }
      bool operator==(const iterator& other) const
      {
          return (i == other.i && j == other.j && image == other.image);  
      }
      bool operator!=(const iterator& other) const
      {
          return(i != other.i || j != other.j || image != other.image); 
      }
      iterator& operator=(const iterator& other) //assignment op.
      {
          i = other.i;
          j = other.j;
          image = other.image;

          return *this;
      }
      ~iterator(){image = nullptr;delete image;}    
   private:
      const Image* image;
      int i,j;  //i is column , j is row
   };
  //----------------HW7 functions below -------------------------------------s
   friend std::ostream& operator<<(std::ostream& os, const Image& im)
   {
     im.write(os);
     return os;
   }
   friend std::istream& operator>>(std::istream& in, const Image& im)
   {
       bool streamType = 0,imType = 0; //0 alpha  1 PGM
       if(im.whatamI() == "P2")
           imType = 1;
   
       std::string s;
       std::getline(in,s);
       in>>s;
       if(s != "Alpha")
           streamType = 1;
       
       if(streamType == 1) //PGM 
       {
           
       }
       if(streamType != imType)
           in.setstate(std::ios::failbit);       
    return in;
    }
   
   Image::iterator begin() const
   {
     return iterator(this,0,0);
   }
   Image:: iterator end() const
   {
       return iterator(this,this->width(),this->height()-1);  
   }
  
  //--------------------------------------------------------------------------

  
  
  
  
  
  
  
  Image(const FileType& type);                           //constructor
  virtual ~Image(){}                 //destructor
  
  Image(const Image& image);
  static Image* create(const std::string &filename); // NEW FUNCTION  : static Factory method to create a PGM or Alpha image depending on the file given

  //HW 6 operators + functions -----------------------------------------------------------------------
  void min(Image& im2); 
  void min(int direction,Image& im2);
  void max(Image& im2);
  void max(int direction, Image& im2);
  explicit operator bool() const
  {return !this->empty();}
    
  
  Image& operator *=(const double& value) {this->resize(value); return *this; }

  Image& operator /=(const double& value) 
  {
     if(value <= 0.0)
     {std::cerr<<"Error! can't divide by 0"<<std::endl;
     }
     else
        this->resize(1.0/value); 
      return *this;         
  }
  Image& operator -=(Image& im2){ this->min(im2); return *this;}
  Image& operator +=(Image& im2){ this->max(im2); return *this;}
  
  //---------------------------------------------------------------------------------------------------------
  
 
 
  
  
  //returns true if and only if the image has no pixels. 
  virtual bool empty() const {return (_image.width==0 && _image.height==0);}
  
  //returns the int number of rows in the image
  virtual int height() const {return _image.height;}
  
  //returns the int number of columns in the image
  virtual int width() const {return _image.width;}
  
  //Returns the int number of gray levels
  virtual int range() const  {return _image.extra+1;}
  
  //Returns an int corresponding to the appropriate pixel.
  //get(0,0) returns the upper-left pixel. get(1,0) returns the pixel to the right of that one.
  //A black pixel is 0; a white pixel is range()-1;
  //intermediate pixels yield intermediate values.
  virtual int get(const int& column, const int& row) const; 
  
  virtual void set(const int& column, const int& row,int value); 

  //left-right reflects the image.
  virtual void mirror();
  
  //rotates the image that many degrees clockwise, which must be a multiple of 90°
  virtual void rotate(const int& degrees); 
  
  //Doubles the size of the image, as described in HW3, 
  //if factor is two. Halves the size of the image, as described in HW3, if factor is one-half. 
  virtual void resize(const double& factor);
  
  //Behaves as if the filename ctor were called. Replaces any existing image.
  virtual void read(const std::string& fileName)=0;
  
  //Writes the image to the file indicated by the std::string filename.
  //Throws an explanatory std::string upon problems. 
  virtual void write(const std::string& fileName) const=0;
  
  //Writes the image to the ostream given as an argument.
  virtual void write(std::ostream& stream) const =0; 
  
  void operator<<(std::ostream& out){write(out);}
  
  std::string whatamI() const{return _image.label;}
  const static int NW = 0;
  const static int NE = 1;
  const static int SW = 2;
  const static int SE = 3;

// 

protected:
  
  //initialize a new file
  //@input format type
  virtual void initFileFormat(const FileType& type);
  virtual void initFileFormat(FileFormat& file, const FileType& type);
  
  //check functions
  bool isValidChar(const char& ch);

  //return true if this file is a comment
  static bool isComment(const char& ch);

  //check if the given line is a header line (Alpha)
  //@input: line to check
  //@output: true if the line is header and false otherwise
  bool isHeaderLine(const Line& line);
  
  //roate a given file a number of degrees degree
  //@input: the given file to rotate
  //@input: the given degree to rotate
  //@output: rotated file
  FileFormat rotateFile(const FileFormat& file, const int& degree);


  //roate a given file 0 degree
  //@input: the given file to rotate
  //@output: rotated file
  FileFormat rotateFile0(const FileFormat& file);

  //roate a given file 90 degree
  //@input: the given file to rotate
  //@output: rotated file
  FileFormat rotateFile90(const FileFormat& file);

  //roate a given file 180 degree
  //@input: the given file to rotate
  //@output: rotated file
  FileFormat rotateFile180(const FileFormat& file);

  //roate a given file 270 degree
  //@input: the given file to rotate
  //@output: rotated file
  FileFormat rotateFile270(const FileFormat& file);
  
  //cut the input file by half
  //@input: file to half
  //@output the scaled file
  FileFormat average(const FileFormat& file);

  //double the input file by half
  //@input: file to half
  //@output the scaled file
  FileFormat doubleImage(const FileFormat& file);
  
  //get the average picture around a certain pixel
  int avrg(const FileFormat& file, const int& i, const int& j);
 
protected:
    FileFormat _image;                    //store the image data structure

	
};


#endif //_IMAGE_H_
