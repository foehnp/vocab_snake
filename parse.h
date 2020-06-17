#include <string>
#include <fstream>

void parse(std::string path, std::vector<std::string>& words, std::vector<std::string>& transs){
  std::ifstream file;
  file.open("vocab/"+path);
  std::string line;
  while (file){
    std::getline (file, line);
    std::string word, trans;
    int side = 0;
    for (char c : line){
      if (c==','){
        side+=1;
        continue;
      }
      if (side==0){
        word += c;
      } else{
        trans += c;
      }
    }
    words.push_back(word);
    transs.push_back(trans);
  }
}
