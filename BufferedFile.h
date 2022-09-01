#ifndef BUFFEREDFILE_H
#define BUFFEREDFILE_H
#include<string>
#include<ios>
#include"FStream.h"
#include"GradingDeque"

class BufferedFile : private FStream {
  public:
    BufferedFile(const char* fname);
    BufferedFile& get(char& c);
    ~BufferedFile();
    std::ostream& put (char c);
    bool eof() const;
    void putback(char ch);
  private:
    std::istream& raw_get(char& c);
    const char* filename;
    std::streampos getpos;
    std::streampos putpos;
    GradingDeque<char> buffer;
    bool hit_file_eof;
    bool hit_empty_buffer;
};
#endif
