#include  "PGM.h"
#include <fstream>
#include <sstream>

PGM::PGM(const std::string& fileName):
Image(FILE_TYPE_PGM){
  read(fileName);
}

PGM::PGM(const PGM & p):
		Image(p){}

void PGM::operator=(const PGM& pgm)
{
	_image=pgm._image;
}

void PGM::read(const std::string& fileName)
{	
  std::ifstream file(fileName, std::ifstream::in);
  if(!file.is_open()){
	 throw std::string("cannot open the file: "+fileName);
	return;
   }
  readPgmFile(file);
}
	  
void PGM::write(const std::string& fileName) const{
  std::ofstream file(fileName, std::ifstream::out|std::ifstream::trunc);
  if(!file.is_open()){
	 throw std::string("cannot open the file: "+fileName);
	 return;
  }
	  
  write(file);	
}
	  
void PGM::write(std::ostream& stream) const{
  stream<<"P2"<<"\n";
  stream<<_image.width<<" "<<_image.height<<"\n";
  stream<<_image.extra;
	  
  for(int i=0;i<_image.height;i++){
	  stream<<"\n"  ;
	for(int j=0;j<_image.width;j++){
		stream<<_image.data[i][j]<<" ";
     }
  }	
}

std::vector<int> PGM::readNumbersFromFile(std::istream& stream)
{ 

std::vector<int> numbers;
std::string line;
std::string token;
int val;

  numbers.clear();
  while (std::getline(stream, line)){
	    
	 //ignore line (or line parts with #)
	 auto pos=line.find("#");
	 line=line.substr(0, pos);
	    	
	 std::stringstream ss;
	 ss << line;
	 
	 //parse a line
	  while (!ss.eof() && ss){
	    ss >> token; 
	    if (std::stringstream(token) >> val) 
	    	numbers.push_back(val);  
	    token="";
	   }
   }	  
  return numbers;
}

void  PGM::readPgmFile(std::istream& stream)
{
   std::vector<int> numbers= readNumbersFromFile(stream);
   
   initFileFormat(_image, FILE_TYPE_PGM);
   
   if(numbers.size()<3){ 
	   throw std::string("No file info exist");
	   return ;
   }
   
   _image.width=numbers[0];
   _image.height=numbers[1];
   _image.extra=numbers[2];
   
   if(_image.width*_image.height!=static_cast<int>(numbers.size()-3)){
	   throw std::string("Invalid file size"); 
   }
   
   //resize the file
   _image.data.resize(_image.height);
   for(int i=0;i<_image.height;i++){
	   _image.data[i].resize(_image.width);
   }
   
   //copy the data part
   int k=3;
   for(int i=0;i<_image.height;i++){
   	  for(int j=0;j<_image.width;j++){
   		  
   		 
   		_image.data[i][j]=numbers[k++];
   		
   		if(_image.data[i][j]>_image.extra){
   			throw std::string("Bad pixel: "+std::to_string(_image.data[i][j]));
   		}
   	  }
   }    	
}
