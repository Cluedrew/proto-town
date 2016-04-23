#include "control-map.hpp"

// Definition from controls.hpp
const unsigned int controlsSize = int(Controls::Cap);

// Implementation of the control mapping.


ControlMap::ControlMap () :
  buttons{sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left,
          sf::Keyboard::Right, sf::Keyboard::Space}
{}

ControlMap::~ControlMap ()
{}

// see header
Controls ControlMap::lookupKey (sf::Keyboard::Key const key) const
{
  unsigned int i;
  for (i = 0 ; i < controlsSize ; ++i)
    if (key == buttons[i])
      break;
  return Controls(i);
}
