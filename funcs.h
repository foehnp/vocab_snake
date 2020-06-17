#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <map>
#include <iostream>

//Struct for a position on snake grid
struct GridPoint{ 
  int x,y;
};
bool operator< (const GridPoint a, const GridPoint b){
  return (a.x<b.x or (a.x==b.x and a.y<b.y));
}
bool operator== (const GridPoint a, const GridPoint b){
  return (a.x==b.x and a.y==b.y);
}

//Struct to summarise game settings
struct Settings{
  int M;
  int N;
  int size;
  int h;
  int w;
  int score_w;
  int trans_h;
  int total_w;
  int total_h;
  sf::Font font;
  sf::RectangleShape empty_square;
  sf::RectangleShape snake_square;
  sf::RectangleShape letter_square;
  float delay;
  int min_letters;
  sf::Color color_bg;
  
};

class Game{
public:
  Game(Settings& set0,
       std::vector<std::string> words0,
       std::vector<std::string> transs0,
       sf::RenderWindow* window_pointer0){
    set = set0;
    words = words0;
    transs = transs0;
    window_pointer = window_pointer0;
    score = 0;
    dir=0;
    status = "alive";
    digest = 0;
    //Choose first words and translations
    int i=0;  
    while (i<set.min_letters and words.size()){
      curr_words.push_back(words.back());
      i += words.back().size();
      words.pop_back();
      curr_transs.push_back(transs.back());
      transs.pop_back();
    }
    
    (*window_pointer).clear(set.color_bg);
    (*window_pointer).display();
    draw_score();  //Initialize score board
    draw_trans();  //Initialize translation board
    //Initialize grid
    for (int i=0; i<set.N; i++){
      for (int j=0; j<set.M; j++){
        set.empty_square.setPosition(i*set.size, j*set.size);
        (*window_pointer).draw(set.empty_square);
      }
    }
    // Position the letters of the first words
    for (auto word : curr_words){
      spread_word(word);
    }
    draw_letters();
    sn = {{set.N/2, set.M/2}}; // initial position of snake
    draw_snake();
    (*window_pointer).display();
  }
  
  void step(int ndir){
    if ((ndir+dir)%2==1){ //Update actual direction for next step, if it is allowed
      dir = ndir;
    }
    if (digest){
      set.empty_square.setPosition(sn.back().x*set.size, sn.back().y*set.size);
      (*window_pointer).draw(set.empty_square);
      sn_word.erase(sn_word.size()-digest,1);
      set.empty_square.setPosition(sn.back().x*set.size, sn.back().y*set.size);
      (*window_pointer).draw(set.empty_square);
      sn.pop_back();
      digest--;

      draw_snake();
      score++;
      draw_score();  //update score board
    } 
    else {
      GridPoint next = {(sn[0].x+ (dir==0)-(dir==2)+set.N)%set.N, (sn[0].y+(dir==1)-(dir==3)+set.M)%set.M}; //Coordinates of next tile
      // 3 possibilities:
      if (find(sn.begin(),sn.end()-1,next)!=sn.end()-1){
        // snake bites itself
        status = "dead";
        die();
        (*window_pointer).display();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
        return;
      }
      else if (words.size()==0 and letters.size()==0) {
        status = "finished";
      }
      else if (letters.count(next)){
        // snake eats a letter
        sn.insert(sn.begin(),next);
        sn_word.push_back(letters[next]);
        letters.erase(next);
        int i = check_word();
        if (i>0){
          draw_letters();
          draw_score();  //update score board
          digest = i;
        }
        if (letters.size()<set.min_letters and words.size()>0){
          curr_words.push_back(words.back());
          words.pop_back();
          curr_transs.push_back(transs.back());
          transs.pop_back();
          spread_word(curr_words.back());
          draw_letters();
        }
        draw_trans();
        draw_snake(); //draw new snake
      }
      else{
        // snake moves normally
        sn.insert(sn.begin(),next);
        set.empty_square.setPosition(sn.back().x*set.size, sn.back().y*set.size);
        (*window_pointer).draw(set.empty_square);
        sn.pop_back();
        draw_snake(); //draw new snake
      }
    }

    (*window_pointer).display();
  }
  
  std::string get_status(){
    return status;
  }
  int get_score(){
    return score;
  }
  bool digesting(){
    return digest>0;
  }
       
  
  
private:
  sf::RenderWindow* window_pointer;
  Settings set;
  std::vector<GridPoint> sn; //location of the snake
  std::string sn_word = " "; //word displayed by snake
  std::map<GridPoint, char> letters; //map of (coordinate, char) of the letters currently on field
  std::vector<std::string> words;
  std::vector<std::string> transs;
  std::vector<std::string> curr_words;
  std::vector<std::string> curr_transs;
  int dir;
  int score;
  std::string status; // "alive", "dead" or "finished"
  int digest;
  
  void spread_word(std::string word){
    std::srand(time(NULL));
    for (char c : word){
      while (true){
        GridPoint p{std::rand()%set.N, std::rand()%set.M};
        if (letters.count(p)==0 and find(sn.begin(),sn.end(),p)==sn.end()){
          letters[p] = c;
          break;
        }
      }
    }
  }
  
  int check_word(){
    for (int i=0; i<curr_words.size(); i++){
      int curr_size = curr_words[i].size();
      if (sn_word.size()-1<curr_size){
        continue;
      }
      if (sn_word.substr(sn_word.size()-curr_size, curr_size)==curr_words[i]){
//         curr_words.erase(curr_words.begin()+i);
        curr_transs.erase(curr_transs.begin()+i);
        curr_words.erase(curr_words.begin()+i);
        digest = curr_size;
        return curr_size;
      }
    }
    return 0;
  }
  
  void draw_snake(){
    for (int i=0; i<sn.size(); i++){
      set.snake_square.setPosition(sn[i].x*set.size, sn[i].y*set.size);
      if (i<digest){
        set.snake_square.setFillColor(sf::Color::Yellow);
        (*window_pointer).draw(set.snake_square);
        set.snake_square.setFillColor(sf::Color::Red);
      }else{
        (*window_pointer).draw(set.snake_square);
      }
      sf::Text text;
      text.setFont(set.font);
      text.setString(sn_word[sn.size()-i-1]);
      text.setCharacterSize(10);
      text.setFillColor(sf::Color::Black);
      text.setPosition(sn[i].x*set.size+2, sn[i].y*set.size+1);
      (*window_pointer).draw(text);
    }
  }
  
  void draw_letters(){
    for (auto const& letter : letters){
      set.letter_square.setPosition(letter.first.x*set.size, letter.first.y*set.size);  
      (*window_pointer).draw(set.letter_square);
      sf::Text text;
      text.setFont(set.font);
      text.setString(letter.second);
      text.setCharacterSize(10);
      text.setFillColor(sf::Color::Black);
      text.setPosition(letter.first.x*set.size+2, letter.first.y*set.size+1);
      (*window_pointer).draw(text);      
    }
  }
  
  void draw_score(){
    sf::RectangleShape score_rect(sf::Vector2f(set.score_w, set.total_h));
    score_rect.setFillColor(set.color_bg);
    score_rect.setPosition(set.w, 0);
    (*window_pointer).draw(score_rect);
    sf::Text text;
    text.setFont(set.font);
    text.setString(std::to_string(score));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Red);
    text.setPosition(set.w+20, 20);
    (*window_pointer).draw(text);
  }
  
  void draw_trans(){
    std::string s = "";
    for (auto trans : curr_transs){
      s += trans + ", ";
    }
    if (s.size()>2){
      s.erase(s.size()-2,2);
    }
    sf::RectangleShape trans_rect(sf::Vector2f(set.w, set.trans_h));
    trans_rect.setFillColor(set.color_bg);
    trans_rect.setPosition(0, set.h);
    (*window_pointer).draw(trans_rect);
    sf::Text text;
    text.setFont(set.font);
    text.setString(s);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Black);
    text.setPosition(20, set.h+20);
    (*window_pointer).draw(text); 
  }
  
  void die(){
    sf::RectangleShape score_rect(sf::Vector2f(set.score_w, set.h));
    score_rect.setFillColor(set.color_bg);
    score_rect.setPosition(set.w, 0);
    (*window_pointer).draw(score_rect);
    sf::Text text;
    text.setFont(set.font);
    text.setString(std::to_string(score));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Red);
    text.setPosition(set.w+20, 20);
    (*window_pointer).draw(text); 

    sf::Text text_ded;
    text_ded.setFont(set.font);
    text_ded.setString("SNEK\nDED!");
    text_ded.setCharacterSize(30);
    text_ded.setFillColor(sf::Color::Red);
    text_ded.setPosition(set.w+20, 100);
    (*window_pointer).draw(text_ded);
  }
};
