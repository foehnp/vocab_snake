#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>
// #include "funcs.h"
#include "game.h"
#include "welcome.h"
#include "ded.h"
#include "parse.h"


// Function to shuffle 2 vectors using the same random permutation
void shuffle2(std::vector<std::string>& v1, std::vector<std::string>& v2){
  std::vector<int> indices{};
  for (int i=0; i<v1.size(); i++){
    indices.push_back(i);
  }
  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(indices), std::end(indices), rng);
  std::vector<std::string> w1{};
  std::vector<std::string> w2{};
  for (auto i : indices){
    w1.push_back(v1[i]);
    w2.push_back(v2[i]);
  }
  v1=w1;
  v2=w2;
}


int main(){
  Settings set;
  set.N=30; set.M=20; //Number of tiles
  set.size=16; //Size of each tile
  set.w = set.size*set.N; //width of grid
  set.h = set.size*set.M; //height of grid
  set.min_letters = 6; //minimal number of letters on grid
  set.score_w = 150; //width of score board
  set.trans_h = 100;  //height of translation board
  set.total_w = set.w + set.score_w;
  set.total_h = set.h + set.trans_h;
  set.delay=0.2; //Duration of game step
  set.color_bg = sf::Color{170,230,240,255};
  
//   std::vector<std::string> words = {"HELLO","NO","YES","HOUSE","ROOF"};
//   std::vector<std::string> transs = {"HALLO","NEIN", "JA","HAUS","DACH"};
  std::vector<GridPoint> sn; //location of the snake
  std::string sn_word = "."; //word displayed by snake
  std::map<GridPoint, char> letters; //map of (coordinate, char) of the letters currently on field
  
  std::srand(time(0));

  // Empty square on grid
  sf::RectangleShape empty_square(sf::Vector2f(set.size, set.size));
  empty_square.setFillColor(sf::Color::White);
  empty_square.setOutlineColor(sf::Color::Black);
  empty_square.setOutlineThickness(-1);
  // Snake square
  sf::RectangleShape snake_square(sf::Vector2f(set.size, set.size));
  snake_square.setFillColor(sf::Color::Red);
  snake_square.setOutlineColor(sf::Color::Black);
  snake_square.setOutlineThickness(-1);
  // Letter square
  sf::RectangleShape letter_square(sf::Vector2f(set.size, set.size));
  letter_square.setFillColor(sf::Color::Green);
  letter_square.setOutlineColor(sf::Color::Black);
  letter_square.setOutlineThickness(-1);
  // Add square shapes to set
  set.empty_square = empty_square;
  set.snake_square = snake_square;
  set.letter_square = letter_square;
  
  
  
  //Fonts
  sf::Font font;
  if (!set.font.loadFromFile("fonts/OpenSans-Regular.ttf")){
    std::cout << "Font not found!";
  }
  

  
  //Initialize window
  sf::RenderWindow window(sf::VideoMode(set.w+set.score_w, set.h+set.trans_h), "Word Snake", sf::Style::Close);
  //Start menu
while (window.isOpen()){
  sf::Event e;
  while (window.pollEvent(e)){
    if (e.type == sf::Event::Closed){   
      window.close();
    }
  }
  std::string path;
  welcome(set, path, window);
  std::vector<std::string> words{};
  std::vector<std::string> transs{};
  parse(path, words, transs);
  shuffle2(words, transs);
  int score = play(set, words, transs, window);
  std::string choice;
  choice = ded(set, score, window);
  if (choice=="quit"){
    break;
  }
}
  


  return 0;
}
