#include "button-map.hpp"

// Definition from Button.hpp
const unsigned int numOfButtons = int(Button::Cap);

// Implementation of the button mapping.


ButtonMap::ButtonMap () :
  buttons{sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left,
          sf::Keyboard::Right, sf::Keyboard::Space}
{}

ButtonMap::~ButtonMap ()
{}

// see header
Button ButtonMap::lookupKey (sf::Keyboard::Key const key) const
{
  unsigned int i;
  for (i = 0 ; i < numOfButtons ; ++i)
    if (key == buttons[i])
      break;
  return Button(i);
}
