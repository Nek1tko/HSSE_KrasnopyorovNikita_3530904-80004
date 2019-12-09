#ifndef BALL_HPP
#define BALL_HPP
#include <SFML/Graphics.hpp>
#include <axis.hpp>

class Ball
{
public:
  static size_t getSide();
protected:
  Ball();

  void draw(sf::RenderWindow&);
  sf::Vector2f getPosition();
  void setStartPos();

  bool move();
  void move(sf::Event);
  void changeDirection(const Axis &);
  void genNewAngle(const sf::Vector2f &);

private:
  const static size_t side_ = 20;

  int angle_;
  int delta_;

  sf::Texture textureBall_;
  sf::Sprite spriteBall_;
};

#endif // BALL_HPP
