#include "input-handler.hpp"


// Constructors and Deconstructor:
InputHandler::InputHandler ()
{}

InputHandler::~InputHandler ()
{}


// Implementation Functions:

/* Given a key press
 */
/* controlsLookUp(event)
 * Handles KeyPressed and KeyReleased events, mapping them by the current
 * control scheme.
 * Params: Constant reference to an initialized SFML KeyPressed/KeyReleased
 *   event.
 * Return: A new InputEvent.
 *
 * Note: This is a temperary placeholder for a more robust system that allows
 *   for control mapping. It will probably be a key->button translation, from
 *   physical to purpose, and so have a slightly different interface, but
 *   this is close enough for now.
 */
static InputEvent controlsLookUp(sf::Event const & event)
{
  InputEvent ievent;

  switch (event.key.code)
  {
  case sf::Keyboard::Left:
    ievent.type = PlayerLeft;
    break;
  case sf::Keyboard::Right:
    ievent.type = PlayerRight;
    break;
  case sf::Keyboard::Up:
    ievent.type = PlayerUp;
    break;
  case sf::Keyboard::Down:
    ievent.type = PlayerDown;
    break;
  case sf::Keyboard::Space:
    ievent.type = PlayerAction;
    break;
  default:
    ievent.type = Ignored;
    return;
  }

  if (sf::Event::KeyPressed == event.type)
    ievent.buttonPressed = true;
  else
    ievent.buttonPressed = false;

  return ievent;
}


InputEvent InputHandler::eventTranslate (sf::Event const & event)
{
  switch (event.type)
  {
  case sf::Event::Closed:
    return InputEvent{InputEvent::TypeValue::Quit, false};
  case sf::Event::KeyPressed:
  case sf::Event::KeyReleased:
    //if (consolUp)
    //  type = Ignored;
    //else
      // Temperary, although it might be a while before we get
      // a proper system for the controls.
      return controlslookUp(event);
    //
    break;
  case sf::Event::TextEntered:
    //if (consolUp)
    //{}
    //else
    //{
      return InputEvent{InputEvent::TypeValue::Ignored, false};
    //}
    //break;
  default:
    return InputEvent{InputEvent::TypeValue::Ignored, false};
  }
}
