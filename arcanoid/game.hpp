#ifndef GAME_HPP
#define GAME_HPP
#include "ball.hpp"
#include "paddle.hpp"
#include "block.hpp"

class Game: public Ball, Paddle
{
public:
  Game();
  void mainMenu(sf::RenderWindow& window);

private:
  std::vector<std::vector<Block>> blocks_;
  sf::Texture textureBG_;
  sf::Sprite spriteBG_;
  size_t count_;
  size_t score_;
  sf::Font font_;

  void newGame(sf::RenderWindow&);
  void update(sf::RenderWindow &window, sf::Event &event);
  void makeLevel(std::vector<std::vector<Block>>&);
  void gameOver(sf::RenderWindow& window);
  void win(sf::RenderWindow& window);

  void addPoints(Block& block);
};

#endif // GAME_HPP
