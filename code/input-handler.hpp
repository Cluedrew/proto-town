#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

/* Translates SFML Events to InputEvents depending on the user's control
 * options.
 */

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include "input-event.hpp"

class InputHandler
{
private:
  // I know of some stuff that will go here, but currently nothing does.

protected:
public:
  virtual ~InputHandler ();

  void eventTranslate (sf::Event const & sfEvent, InputEvent & iEvent) const;
  InputEvent eventTranslate (sf::Event const & sfEvent) const;
  /* Given an SFML Event return the InputEvent it repersents.
   *   Depends on the current control settings and input modes.
   * Params: The sfEvent to translate. Optionally a reference to store the
   *   translated iEvent in.
   * Effect: If iEvent is provided it is mutated to hold the translated event.
   * Return: If iEvent is not provided, the translated event is returned.
   */

  bool pollEventFrom (sf::Window &, InputEvent &) const;
  /* Poll an event and translate it to an InputEvent.
   * Params: A mutable reference to the Window to poll from and mutable
   *   reference to the location to store the translated event in.
   * Effect: Polls from the Window, mutates the InputEvent.
   * Return: True if a non-ignored event was found, false otherwise.
   *   If function returns false the InputEvent should be considered invalid.
   */
};

#endif//INPUT_HANDLER_HPP
