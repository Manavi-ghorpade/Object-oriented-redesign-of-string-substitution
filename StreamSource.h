#ifndef STREAMSOURCE_H
#define STREAMSOURCE_H
#include "BufferedFile.h"
using namespace std;
class StreamSource{
  public:
    //Functions needed:
    //ctor
    StreamSource(const char* search_word, const char* file);
    //get
    StreamSource& get(char& c);
    //put
    ostream& put (char c);
    //eof
    bool eof() const;
    //found_partial_match
    void found_partial_match(int match_count,char ch);
  private:
    BufferedFile bf;
    const char* search_string;
    const char* file_name;
    int character_remaining;
    bool search_from_string;
    int search_origin;
    int word_length;
};
#endif
