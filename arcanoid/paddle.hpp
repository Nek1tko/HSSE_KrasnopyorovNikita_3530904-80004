#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

const int STEP = 7;

class Paddle
{
public:
  static size_t getHeight();
  static size_t getWidth();

protected:
  Paddle();
  void move(sf::Event& event);
  void draw(sf::RenderWindow& window);
  sf::Vector2f getPosition() const;
  void setStartPos();

  bool isIntersected(const sf::Vector2f&) const;

private:
  static const size_t height_ = 22;
  static const size_t width_ = 105;

  sf::Sprite spritePaddle_;
  sf::Texture texturePaddle_;
};

#endif // PADDLE_HPP
