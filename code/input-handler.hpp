#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

/* Translates SFML Events to InputEvents depending on the user's control
 * options.
 */

#include <SFML/Window/Event.hpp>
#include "input-event.hpp"

class InputHandler
{
private:
  // I know of some stuff that will go here, but currently nothing does.

protected:
public:
  InputHandler ();

  virtual InputHandler ();

  //void eventTranslate (sf::Event const &, InputEvent &) const;
  InputEvent eventTranslate (sf::Event const &) const;
  /* Given an SFML Event return the InputEvent it repersents.
   *   Depends on the current control settings and input modes.
   * Params:
   * Return:
   *
   * This function is ment to follow sf::window::pollEvent.
   */

  //bool pollEventFrom (sf::Window &, InputEvent &) const;
  // Should I wrap up pollEvent + eventTranslate?
};

#endif//INPUT_HANDLER_HPP
