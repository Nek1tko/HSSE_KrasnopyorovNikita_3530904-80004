#include "block.hpp"
#include <unordered_map>
#include <functional>

const int OFFSET = 14;

Block::Block(Block&& rhs)
{
   std::swap(spriteBlock_, rhs.spriteBlock_);
   std::swap(textureBlock_, rhs.textureBlock_);
   std::swap(isDeleted_, rhs.isDeleted_);
   std::swap(color_, rhs.color_);
   spriteBlock_.setTexture(textureBlock_);
}

Block::Block(const Block& rhs):
  color_(rhs.color_),
  isDeleted_(rhs.isDeleted_),
  spriteBlock_(rhs.spriteBlock_),
  textureBlock_(rhs.textureBlock_)
{
  spriteBlock_.setTexture(textureBlock_);
}

Block::Block(const Color& color):
  color_(color),
  isDeleted_(false),
  spriteBlock_(),
  textureBlock_()
{
  textureBlock_.loadFromFile("sprites.png");
  spriteBlock_.setTexture(textureBlock_);

  std::unordered_map<Color, std::function<void()>> map = {
    {Color::WHITE, [&](){spriteBlock_.setTextureRect(sf::IntRect(0, 0, width_, height_));}},
    {Color::ORANGE, [&](){spriteBlock_.setTextureRect(sf::IntRect(OFFSET + width_, 0, width_, height_));}},
    {Color::LIGHTBLUE, [&](){spriteBlock_.setTextureRect(sf::IntRect((OFFSET + width_) * 2, 0, width_, height_));}},
    {Color::GREEN, [&](){spriteBlock_.setTextureRect(sf::IntRect((OFFSET + width_) * 3, 0, width_, height_));}},
    {Color::RED, [&](){spriteBlock_.setTextureRect(sf::IntRect(0, OFFSET + height_, width_, height_));}},
    {Color::BLUE, [&](){spriteBlock_.setTextureRect(sf::IntRect((OFFSET + width_) * 1, OFFSET + height_, width_, height_));}},
    {Color::PINK, [&](){spriteBlock_.setTextureRect(sf::IntRect((OFFSET + width_) * 2, OFFSET + height_, width_, height_));}},
    {Color::YELLOW, [&](){spriteBlock_.setTextureRect(sf::IntRect((OFFSET + width_) * 3, OFFSET + height_, width_, height_));}},
    {Color::GREY, [&](){spriteBlock_.setTextureRect(sf::IntRect((OFFSET + width_) * 13, 0, width_, height_));}}
  };

  auto iter = map.find(color);

  iter->second();
}

void Block::draw(sf::RenderWindow& window) const
{
  if (!isDeleted_)
  {
    window.draw(spriteBlock_);
  }
}

void Block::setPosition(const sf::Vector2f& pos)
{
  spriteBlock_.setPosition(pos);
}

size_t Block::getHeight()
{
  return height_;
}

size_t Block::getWidth()
{
  return width_;
}

Axis Block::getInterAxes(const sf::Vector2f& posBall)
{
  if (isDeleted_)
  {
    return NOPE;
  }

  sf::Vector2f posBlock = spriteBlock_.getPosition();

  const double x1 = std::max(posBall.x, posBlock.x);
  const double y1 = std::max(posBall.y, posBlock.y);
  const double x2 = std::min(posBall.x + Ball::getSide(), posBlock.x + getWidth());
  const double y2 = std::min(posBall.y + Ball::getSide(), posBlock.y + getHeight());
  if (x1 > x2 || y1 > y2)
  {
    return NOPE;
  }

  if (color_ == Color::GREY)
  {
    spriteBlock_.setTextureRect(sf::IntRect((OFFSET + width_) * 14, 0, width_, height_));
    color_ = Color::DESTROYEDGREY;
  }
  else
  {
    spriteBlock_.setPosition(-100, -100);
    isDeleted_ = true;
  }

  if (x2 - x1 > y2 - y1)
  {
    return HORIZONTAL;
  }
  else
  {
    return VERTICAL;
  }
}

bool Block::isDeleted()
{
  return isDeleted_;
}
