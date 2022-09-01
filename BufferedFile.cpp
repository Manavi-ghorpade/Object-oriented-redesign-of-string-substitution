#include "BufferedFile.h"
#include<unistd.h>
#include<sys/types.h>
#include<cassert>

BufferedFile::BufferedFile(const char* fname)
  : FStream(fname), filename(fname), getpos(0), putpos(0), hit_file_eof(false), hit_empty_buffer(false)
{
  assert(std::fstream::good());
}

std::istream& BufferedFile::raw_get(char& c)
{
  assert(!FStream::eof());
  FStream::seekg(getpos);
  getpos=FStream::get(c).tellg();
  if(FStream::eof())
  {
    FStream::clear();
    hit_file_eof=true;
  }
  return *this;
}

BufferedFile& BufferedFile::get (char& c)
{
  if(buffer.size()>0)
  {
    c=buffer.front();
    buffer.pop_front();
    return *this;
  }
  raw_get(c);
  if(hit_file_eof)
    hit_empty_buffer=true;
  return *this;
}

std::ostream& BufferedFile::put (char c)
{
  if(getpos==putpos && !hit_file_eof)
  {
    char ch='#';
    raw_get(ch);
    if(!hit_file_eof)
      buffer.push_back(ch);
  }
  FStream::seekp(putpos);
  putpos=FStream::put(c).tellp();
  return *this;
}

void BufferedFile::putback(char ch)
{
  buffer.push_front(ch);
}

bool BufferedFile::eof() const
{
  return hit_file_eof && hit_empty_buffer;
}

BufferedFile::~BufferedFile()
{
  assert(buffer.size()==0);
  FStream::close();
  truncate(filename, putpos);
}
