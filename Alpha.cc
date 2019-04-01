#include "Alpha.h"
#include <fstream>

Alpha::Alpha(const std::string& fileName):
Image(FILE_TYPE_ALPHA){ 
   
	read(fileName);	
}

Alpha::Alpha(const Alpha& alpha):
	Image(alpha){
}

void Alpha::operator=(const Alpha& alpha){
	_image=alpha._image;
}
void Alpha::read(const std::string& fileName){
	
  std::ifstream file(fileName, std::ifstream::in);
  if(!file.is_open()){
	 throw std::string("cannot open the file: "+fileName);
	 return;
  }
  
  LineList lineList=readFile(file);
 
  LineList preocessedFile=preProcessFile(lineList);
		
  //check if all rows have the same number of characters
  if(!isValidEqualSize(preocessedFile)) return;
 
  _image=fromFileList2MatrixFormat(preocessedFile);
  
}
	  
void Alpha::write(const std::string& fileName) const{
	
  std::ofstream file(fileName, std::ifstream::out|std::ifstream::trunc);
  if(!file.is_open()){
	  throw std::string("cannot open the file: "+fileName);
	 return;
  }
  
  write(file);
}
	  
void Alpha::write(std::ostream& stream) const{
  stream<<"Alpha";
		  
  for(int i=0;i<_image.height;i++){
	  stream<<"\n";
    for(int j=0;j<_image.width;j++){
		stream<<static_cast<char>(_image.data[i][j]);
	 }  
  }	
}

LineList Alpha::readFile(std::ifstream& file){
	
  LineList lines;
  lines.clear();

  while(!file.eof()){
	  lines.push_back(readLine(file));
   }
  
  return lines;
}

std::string Alpha::readLine(std::istream& file){
  Line line("");
  char ch;
  
  do{
	  file>>std::noskipws>>ch; 
	  
	  if(file.eof()) break;
		  
	  line +=ch;
	  
  }while(!file.eof() && ch!='\n');
  
  return line;
}

Line Alpha::preProcessLine(const Line& line, bool& autoComplete){
	
  Line newLine("");
  autoComplete=false;
  for(auto ch: line){
			
	  
	 if(std::isspace(ch)) continue;
			  
	  auto lowerCh=std::tolower(ch);
			  
	 //the remaining of the file is a comment
	 if(isComment(lowerCh)) break;
	 
	 if(autoComplete) throw std::string("line contains *, but not at end");
	 
	 if(lowerCh=='*') {
		 autoComplete=true;
			 
		 continue;
	 }
			
	  newLine.push_back(lowerCh);
	}	 
  
   // std::cout<<newLine<<std::endl;
   return newLine;
}

LineList Alpha::preProcessFile(const LineList& file)
{	
  LineList newFile;
  newFile.clear();
  bool headerFound=false;
  
  std::vector<size_t> linesToAutoComplet;
	
  linesToAutoComplet.clear();
  
  //remove the first line of the 
  for(size_t i=0; i<file.size();i++){
	  
	  Line line =file[i];
	  
	  
	  bool autoComplete=false;
	  Line newLine=preProcessLine(line, autoComplete);
	  
	  //we escape header line and add it manually later
	  if(isHeaderLine(newLine) && newFile.empty()){ 
		  headerFound=true;
		  continue;
	  }
	  if(newLine=="") continue;
	  
	  
	  //check if this line is valid
	  if(!isValidLine(newLine)){
		  throw std::string("Invalid line:  "+std::to_string(i+1));
		  throw std::string("Not an Alpha file.");
	  }
	  
	  //ends with *
	  if(autoComplete==true && !newLine.empty()){
		  linesToAutoComplet.push_back(newFile.size());
	  }
		  
	  newFile.push_back(newLine);
  }
  
  if(!headerFound){
	  throw std::string("bad alpha file");
  }
  
  processAutoCompleteList(newFile,linesToAutoComplet);
 
  
  return newFile;
}

bool Alpha::processAutoCompleteList(LineList& lineList, const std::vector<size_t>& autoComplet){
	
	//nothing to do
	if(autoComplet.empty()) return true;
	if(lineList.empty()) return true;
	
	size_t maxLineSize=0;
	for (auto line: lineList){
		maxLineSize=std::max(maxLineSize, line.size());
	}
	
	if(maxLineSize==0) return true;
	
	for(auto i: autoComplet){
		
		auto lineSize=lineList[i].size();
		size_t diff=maxLineSize-lineSize;
		auto ch=lineList[i][lineSize-1];
				
		if(maxLineSize>lineSize) {
			for(size_t j=0;j<diff;j++) lineList[i] +=ch;
		 }
	}
	
	return true;
}


bool Alpha::isValidLine(const Line& line){
	
 for(auto ch: line){
	 if(!isValidChar(ch)){
		 throw std::string("bad charcter");
		return false;
	 }
 }
  return true;
}

bool Alpha::isValidEqualSize(const LineList& file){
	
  //0x0 file is valid
  if(file.empty()) return true;
  
  size_t rowSize=file[0].length();
  
  int i=1;
  for(auto line: file)
  {
	  if(line.length()!=rowSize){
		  throw std::string("Invalid line:  "+std::to_string(i+1));
		  throw std::string("Not an Alpha file.");
		return false;
	  }	  
	  i++;
  }
  
  return true;
}

FileFormat Alpha::fromFileList2MatrixFormat(const LineList& lineList){
	
  FileFormat format;
  
  format.width= format.height=0;
  if (lineList.empty()) return format;
  
  format.width=lineList[0].size();
  format.height=lineList.size();
  
  format.data.resize(format.height);
  for(int i=0;i<format.height;i++)
	  format.data[i].resize(format.width);
  
  int max=0;
  int min=1000;
  for(int i=0;i<format.height;i++)
	  for(int j=0;j<format.width;j++){
		  format.data[i][j]=lineList[i][j];
		  
		  int val=format.data[i][j];
		  max=max<val?val:max;
		  min=min>val? val: min;
	  }
  format.extra=(max-min);
  
  return format;
}

void Alpha::set(const int&column,const int& row,int value)
{
    _image.data[column][row] = value;
}
int Alpha::get(const int& column, const int& row) const {
  if(row<0 || column<0) throw std::string("Invalid index for get(): ("+std::to_string(column)+","+std::to_string(row)+")");
  if(row>=static_cast<int>(_image.data.size()) || column>=static_cast<int>(_image.data[row].size()))
	  throw std::string("Invalid index for get() ("+std::to_string( column)+","+std::to_string(row)+")");
  return (122 - _image.data[row][column]);
}

