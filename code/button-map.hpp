#ifndef BUTTON_MAP_HPP
#define BUTTON_MAP_HPP

/* A class that maps SFML keys to player controls,
 * physical keys to logical buttons.
 */

#include <SFML/Window/Keyboard.hpp>
#include "button.hpp"



class ButtonMap
{
private:
  ButtonArray<sf::Keyboard::Key> buttons;

protected:
public:
  ButtonMap();
  /* Create a new ButtonMap with the default mapping.
   */

  virtual ~ButtonMap();

  Button lookupKey (sf::Keyboard::Key key) const;
  /* Get the button paired with the key.
   *   If the key is not paired with anything, Button::Cap is returned.
   * Return: A Button value.
   */
};

#endif//BUTTON_MAP_HPP
