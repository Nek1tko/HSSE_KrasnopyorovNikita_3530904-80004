#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <ball.hpp>
#include <axis.hpp>

class Game;

class Block
{
public:
  Block(const Block&);
  Block(Block&&);

  static size_t getHeight();
  static size_t getWidth();
  bool isDeleted();

  enum Color
  {
    GREY,
    DESTROYEDGREY,
    ORANGE,
    BLUE,
    GREEN,
    RED,
    PINK,
    YELLOW,
    LIGHTBLUE,
    WHITE
  };

  friend class Game;
private:
  static const size_t height_ = 22;
  static const size_t width_ = 44;

  Color color_;

  bool isDeleted_;

  sf::Sprite spriteBlock_;
  sf::Texture textureBlock_;

  Block(const Color&);
  void draw(sf::RenderWindow&) const;
  void setPosition(const sf::Vector2f&);
  Axis getInterAxes(const sf::Vector2f& posBall);
};

#endif // BLOCK_HPP
