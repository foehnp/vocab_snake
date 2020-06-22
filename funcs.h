#ifndef funcs
#define funcs

#include <SFML/Graphics.hpp>
#include <time.h>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <algorithm>
#include <random>

//Struct for a position on snake grid
struct GridPoint{ 
  int x,y;
};
bool operator< (const GridPoint a, const GridPoint b);
bool operator== (const GridPoint a, const GridPoint b);

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

#endif
