#include "StreamSource.h"

StreamSource::StreamSource(const char* search_word, const char* file):bf(file)
{
    search_string=search_word;
    file_name=file;
}

StreamSource& StreamSource::get(char& c)
{
    if(character_remaining==0)
    {
        search_from_string=false;
        bf.get(c); 
    }
    else
    {
        c=search_string[word_length-character_remaining--];
        // bf.get(c);
    }
    return *this;
}

ostream& StreamSource::put(char c)
{
    return bf.put(c);
    // return *this;
}

bool StreamSource::eof() const
{
    return bf.eof();
}

void StreamSource:: found_partial_match(int match_count,char ch)
{
    if(search_from_string==true)
    {
        search_origin++;
    }
    else{
        search_origin=0;
        word_length=match_count;
        bf.putback(ch);
    }
    search_from_string=true;
    bf.put(search_string[search_origin]);
    character_remaining=word_length-search_origin-1;
}

