#include <cstring>
#include "StreamSource.h"

int main(int argc, char**argv)
{
  if(argc!=4)
  {
    //                        argv[1]     argv[2]          argv[3]
    std::cerr << argv[0] << " search_word replacement_word filename" << std::endl;
    return(1);
  }

  if(strlen(argv[1])==0)//do no processing if search_word is empty
    return(0);
 
  StreamSource ss(argv[1], argv[3]);

  const char*  search_word{argv[1]};
  const char* replace_word{argv[2]};


  unsigned int match_count=0;
  char ch;
  while(!ss.get(ch).eof())
  {
    if(ch==search_word[match_count])
    {
      ++match_count;
      if(match_count < strlen(search_word))
        continue;
    }
    if(match_count==strlen(search_word))
      for(int i=0; i<strlen(replace_word); ++i)
        ss.put(replace_word[i]);
    else if(match_count > 0)
      ss.found_partial_match(match_count,ch);
    else //match_count==0
      ss.put(ch);
    match_count=0;
  }
  return 0;
}
