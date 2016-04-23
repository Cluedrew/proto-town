#ifndef CONTROL_MAP_HPP
#define CONTROL_MAP_HPP

/* A class that maps SFML keys to player controls,
 * physical keys to logical buttons.
 */

#include <SFML/Window/Keyboard.hpp>
#include "controls.hpp"



class ControlMap
{
private:
  //sf::Keyboard::Key buttons[int(Controls::Cap)];
  ControlsArray<sf::Keyboard::Key> buttons;

protected:
public:
  ControlMap();
  /* Create a new ControlMap with the default mapping.
   */

  virtual ~ControlMap();

  Controls lookupKey (sf::Keyboard::Key key) const;
  /* Get the button paired with the key.
   *   If the key is not paired with anything, Controls::Cap is returned.
   * Return: A Controls value.
   */
};

#endif//CONTROL_MAP_HPP
