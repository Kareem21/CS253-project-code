#include "Image.h"
#include "Alpha.h"
#include <fstream>
#include "PGM.h"
using namespace std;    

    //what is going on in this >> thing



Image* Image::create(const std::string &filename) //static factory method 
{    
    //Check if file is alpha or PGM 
    bool filetype = 0; // 0 for alpha 1 for PGM
    std::ifstream in(filename);
    std::string line;
    std::string newLine="";
    while(in>>line) 
    {
        for(auto ch: line)
        {
        if(isComment(ch)) break;
        newLine += ch;
        }
        
        if(newLine == "Alpha"){
            filetype = 0;break;}
         if(newLine == "P2"){
            filetype = 1;break;}
    }
    
    if(filetype == 0) //if Alpha
    {
        Alpha *alpha = new Alpha(filename);
        return alpha;
    }
    if(filetype)// if P2
    {
     PGM *test = new PGM(filename);
     return test;
    }
    return NULL; //if it's neither
}

Image::Image(const FileType& type)
{
	 initFileFormat(type);
}
 
 Image::Image(const Image& image)
{
	 _image=image._image;
 }
void Image::min(Image& im2) // returns ptr to current Image 
{
     min(Image::NW,im2); //assuming im2 is smaller
}
void Image::min(const int direction,Image& im2)     //returns ptr to current Image
{

    std::string thisImage;
    std::string secondImage;
    if(this->whatamI() == "P2")
        thisImage = "P2";
    else
        thisImage = "Alpha";
    
    if(im2.whatamI() == "P2")
        secondImage = "P2";
    else
        secondImage = "Alpha";
    
    bool smaller = 0; //this ptr is smaller image
    if(im2.height() * im2.width() < this->height() * this->width())  
        smaller = 1;    //2nd image is smaller

    //All work for PGM - > PGM
    if(direction == NW)
    {
        if(smaller == 1) //2nd image is smaller
        {
                for(int i = 0;i<im2.height();i++)
                {
                    for(int j = 0;j<im2.width();j++)
                    {
                        if(im2.get(j,i) < this->get(j,i))
                         {
                             this->set(i,j,im2.get(j,i));
                         }
                    }                   
                }
        }
    }
    
    if(direction == NE)
    {
        if(smaller == 1) //2nd image is smaller
        {                           
            int limitHeight = im2.height();
            int limitWidth = this->width() - im2.width();     
            
            for(int i = 0;i<limitHeight;i++)   //height is correct
            {
                     for(int j = limitWidth;j<this->width();j++)
                     {
                          if(im2.get(j-limitWidth,i) < this->get(j,i))
                           {                            
                             this->set(i,j,im2.get(j-limitWidth,i));
                           }
                     }                   
            }            
        }        
    }
    if(direction == SE)
    {
        if(smaller == 1) //2nd image is smaller
        {                           
            int limitHeight = this->height() - im2.height();
            

            int limitWidth = this->width() - im2.width();     
            
            for(int i = limitHeight;i<this->height();i++)   //height is correct
            {             
                     for(int j = limitWidth;j<this->width();j++)
                     {
                           
                           if(im2.get(j-limitWidth,i-limitHeight) < this->get(j,i))
                           {                            
                              this->set(i,j,im2.get(j-limitWidth,i-limitHeight));
                           }
                     }                
            }            
        }        
    }
    
    if(direction == SW)
    {
        if(smaller == 1) //2nd image is smaller
        {                           
             int limitHeight = this->height() - im2.height();
//             int limitWidth = this->width() - im2->width();     
            
            for(int i = limitHeight;i<this->height();i++)   //height is correct
            {             
                     for(int j = 0;j<im2.width();j++)
                     {                           
                           if(im2.get(j,i-limitHeight) < this->get(j,i))
                           {                            
                              this->set(i,j,im2.get(j,i-limitHeight));
                           }
                     }                
            }            
        }        
    }
}
void Image::max(Image& im2)
{
    max(Image::NW,im2);
}
void Image::max(int direction, Image& im2)
{
    std::string thisImage;
    std::string secondImage;
    if(this->whatamI() == "P2")
        thisImage = "P2";
    else
        thisImage = "Alpha";
    
    if(im2.whatamI() == "P2")
        secondImage = "P2";
    else
        secondImage = "Alpha";
    
    bool smaller = 0; //this ptr is smaller image
    if(im2.height() * im2.width() < this->height() * this->width())  
        smaller = 1;    //2nd image is smaller

    //All work for PGM - > PGM
    if(direction == NW)
    {
        if(smaller == 1) //2nd image is smaller
        {
                for(int i = 0;i<im2.height();i++)
                {
                    for(int j = 0;j<im2.width();j++)
                    {
                        if(im2.get(j,i) > this->get(j,i))
                         {
                             this->set(i,j,im2.get(j,i));
                         }
                    }                   
                }
        }
    }
    
    if(direction == NE)
    {
        if(smaller == 1) //2nd image is smaller
        {                           
            int limitHeight = im2.height();
            int limitWidth = this->width() - im2.width();     
            
            for(int i = 0;i<limitHeight;i++)   //height is correct
            {
                     for(int j = limitWidth;j>this->width();j++)
                     {
                          if(im2.get(j-limitWidth,i) < this->get(j,i))
                           {                            
                             this->set(i,j,im2.get(j-limitWidth,i));
                           }
                     }                   
            }            
        }        
    }
    if(direction == SE)
    {
        if(smaller == 1) //2nd image is smaller
        {                           
            int limitHeight = this->height() - im2.height();
            

            int limitWidth = this->width() - im2.width();     
            
            for(int i = limitHeight;i<this->height();i++)   //height is correct
            {             
                     for(int j = limitWidth;j<this->width();j++)
                     {
                           
                           if(im2.get(j-limitWidth,i-limitHeight) > this->get(j,i))
                           {                            
                              this->set(i,j,im2.get(j-limitWidth,i-limitHeight));
                           }
                     }                
            }            
        }        
    }
    
    if(direction == SW)
    {
        if(smaller == 1) //2nd image is smaller
        {                           
             int limitHeight = this->height() - im2.height();
//             int limitWidth = this->width() - im2->width();     
            
            for(int i = limitHeight;i<this->height();i++)   //height is correct
            {             
                     for(int j = 0;j<im2.width();j++)
                     {                           
                           if(im2.get(j,i-limitHeight) > this->get(j,i))
                           {                            
                              this->set(i,j,im2.get(j,i-limitHeight));
                           }
                     }                
            }            
        }        
    }
}


void Image::initFileFormat(const FileType& type)
{
  _image.type=type;
  _image.width=0;
  _image.height=0;
  _image.extra=0;
   
  if(type==FILE_TYPE_ALPHA) _image.label="Alpha";
  if(type==FILE_TYPE_PGM) _image.label="P2";
   
  _image.data.clear();
}

void Image::initFileFormat(FileFormat& file, const FileType& type)
{ 	
  file.type=type;
  file.width=0;
  file.height=0;
  file.extra=0;
   
  if(type==FILE_TYPE_ALPHA) file.label="Alpha";
  if(type==FILE_TYPE_PGM) file.label="P2";
   
  file.data.clear();
}


int Image::get(const int& column, const int& row) const 
{
  if(row<0 || column<0) throw std::string("Invalid index for get(): ("+std::to_string(column)+","+std::to_string(row)+")");
  
  if(row>=static_cast<int>(_image.data.size()) || column>=static_cast<int>(_image.data[row].size()))
	  throw std::string("Invalid index for get() ("+std::to_string( column)+","+std::to_string(row)+")");
  return _image.data[row][column];
}

void Image::set(const int& row, const int& column,int value)
{
    _image.data[row][column] = value;
}

void Image::rotate(const int& degrees)
{
  if(degrees%90!=0)  throw std::string("Invalid rotation degree"+std::to_string(degrees));
   
  int newDegree=degrees%360;
  _image=rotateFile(_image, newDegree);
}

void Image::mirror(){
  size_t rows=_image.data.size();
  size_t cols=rows==0? 0: _image.data[0].size();
	  
  FileFormat rotatedFile;
  initFileFormat(rotatedFile, FILE_TYPE_ALPHA);
  rotatedFile.extra=_image.extra;
	  
  //new  rows=old columns
  rotatedFile.data.resize(rows);
	  
  for(size_t i=0; i<rows;i++)
	  rotatedFile.data[i].resize(cols);
			  
  for(size_t i=0; i<rows;i++){
	  for(size_t j=0; j<cols;j++){
		 rotatedFile.data[i][j]=  _image.data[i][cols-j-1];
	  }
   }
  
  _image=rotatedFile;
  _image.width= cols;
  _image.height= rows;   
}

void Image::resize(const double& factor){
  if(factor==2)
  {
	 _image=doubleImage(_image);
  }
  else if(factor==0.5){
	  _image=average(_image);  
  }
  else{
	  throw std::string("Invalid resize parameter: "+std::to_string(factor));
  }
}

bool Image::isValidChar(const char& ch){
  return std::isalpha(ch);
}
bool Image::isComment(const char& ch){
  return ch=='#';
}

bool Image::isHeaderLine(const Line& line){
  return (line=="alpha");
}

FileFormat Image::rotateFile(const FileFormat& file, const int& degree){
  switch (degree){
     case 0:
    	  return rotateFile0(file);
     case 90:
           return rotateFile90(file); 
     case 180:
           return rotateFile180(file);
     case 270:
           return  rotateFile270(file);   
     default:
    	 throw std::string("Invalid rotation degree: "+std::to_string(degree));
    	  
  }
}

FileFormat Image::rotateFile0(const FileFormat& file){
  return file;
}

FileFormat Image:: rotateFile90(const FileFormat& file)
{	
  size_t rows=file.data.size();
  size_t cols=rows==0? 0: file.data[0].size();
  
  FileFormat rotatedFile;
  initFileFormat(rotatedFile, file.type);
  rotatedFile.extra=file.extra;
  
  //new  rows=old columns
  rotatedFile.data.resize(cols);
  
  for(size_t i=0; i<cols;i++)
	  rotatedFile.data[i].resize(rows);
		  
  for(size_t i=0; i<rows;i++){
	  for(size_t j=0; j<cols;j++){
		  rotatedFile.data[j][i]=  file.data[i][j];
	  }
  }
  
  //add a termination char for each line
  for(size_t i=0;i<rotatedFile.data.size(); i++){
	  auto oldLine=rotatedFile.data[i];
	  auto len=oldLine.size();
	  
	  for(size_t j=0;j<len;j++)
		 rotatedFile.data[i][j]=oldLine[len-j-1];
  }
  
  //update file size
  rotatedFile.width=rows;
  rotatedFile.height= cols; 
  
  return rotatedFile;
}

FileFormat Image::rotateFile180(const FileFormat& file){
	
  size_t rows=file.data.size();
  size_t cols=rows==0? 0: file.data[0].size();
  
  FileFormat rotatedFile;
  initFileFormat(rotatedFile, file.type);
  rotatedFile.extra=file.extra;
  
  //new  rows=old columns
  rotatedFile.data.resize(rows);
  
  for(size_t i=0; i<rows;i++)
	  rotatedFile.data[i].resize(cols);
		  
  for(size_t i=0; i<rows;i++){
	  for(size_t j=0; j<cols;j++){
		  rotatedFile.data[i][j]=  file.data[rows-i-1][cols-j-1];
	  }
  }
  
  rotatedFile.width=cols;
  rotatedFile.height= rows; 
  
  return rotatedFile;
}

FileFormat Image::rotateFile270(const FileFormat& file){
	
  size_t rows=file.data.size();
  size_t cols=rows==0? 0: file.data[0].size();
    
  FileFormat rotatedFile;
  
  //new  rows=old columns
  initFileFormat(rotatedFile, file.type);
  rotatedFile.data.resize(cols);
 
  
  for(size_t i=0; i<cols;i++)
	  rotatedFile.data[i].resize(rows);
		  
  for(size_t i=0; i<rows;i++){
	  for(size_t j=0; j<cols;j++){
		  rotatedFile.data[j][i]=  file.data[rows-i-1][j];
	  }
  }
  
  //add a termination char for each line
  for(size_t i=0;i<rotatedFile.data.size(); i++){
	  auto oldLine=rotatedFile.data[i];
	  auto len=oldLine.size();
	  
	 for(size_t j=0;j<len;j++)
		rotatedFile.data[i][j]=oldLine[len-j-1];
  }
  
  FileFormat finalFile;
  initFileFormat(finalFile, file.type);
  finalFile.extra=file.extra;
  
  finalFile.data.reserve(rotatedFile.data.size());
  
   
  for(int i=rotatedFile.data.size()-1; i>=0;i--)
	  finalFile.data.push_back(rotatedFile.data[i]);
  
  //update file size
  finalFile.width=rows;
  finalFile.height= cols; 
  
  return finalFile;
}

int Image::avrg(const FileFormat& file, const int& i, const int& j){
	int sume=file.data[i][j]+file.data[i+1][j]+file.data[i][j+1]+file.data[i+1][j+1];
	return static_cast<int> (sume/4.0);
}

FileFormat Image::average(const FileFormat& file){

  FileFormat newFile;
  initFileFormat(newFile, file.type);
  newFile.extra=file.extra;
  
  int width=file.width;
  int height= file.height;
  
  int newWidth=static_cast<int> (width/2);
  int newHeight=static_cast<int> (height/2);
  
  newFile.width=newWidth;
  newFile.height=newHeight;
  
  newFile.data.resize(newHeight);
  for(int i=0;i<newHeight;i++){
	  newFile.data[i].resize(newWidth);
  }
  
  for (int i=0,m=0;i<height-1;i+=2, m++){
	  for(int j=0, n=0;j<width-1;j+=2, n++){
		  newFile.data[m][n]=avrg(file,i,j);
		  
	  }
  }
  
  return newFile;
}

FileFormat Image::doubleImage(const FileFormat& file){
  FileFormat newFile=file;
 	  
  int width=file.width;
  int height= file.height;
	  
  int newWidth=width*2;
  int newHeight=height*2;
	  
  newFile.width=newWidth;
  newFile.height=newHeight;
  newFile.extra=file.extra;
  
  //resize the new file
  newFile.data.resize(newHeight);
  for(int i=0;i<newHeight;i++)
	  newFile.data[i].resize(newWidth);
  
  //double the image
  for(int i=0;i<height;i++){
	  
	  //double the collumns
	  for(int j=0;j<width;j++){
		  newFile.data[2*i][2*j]=newFile.data[2*i][2*j+1]=file.data[i][j];
		  newFile.data[2*i+1][2*j]=newFile.data[2*i+1][2*j+1]=file.data[i][j];
	  }
  }
	
  //add more rows
  /*for(int i=0;i<height;i++){
	 newFile.data.push_back(file.data[i]);
  }
  
  //add more collumns
  for(int i=0;i<newHeight;i++){
      for(int j=0;j<width;j++){
  	      newFile.data[i].push_back(newFile.data[i][j]);
       }
  }*/
  
  return newFile;
}


