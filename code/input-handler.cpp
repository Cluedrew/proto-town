#include "input-handler.hpp"


// Constructors and Deconstructor:
//InputHandler::InputHandler () :{}

InputHandler::~InputHandler ()
{}


// Implementation Functions:

/* controlsLookUp(event, ievent)
 * Handles KeyPressed and KeyReleased events, mapping them by the current
 *   control scheme.
 * Params: Constant reference to an initialized SFML KeyPressed/KeyReleased
 *   event.
 * Effect: Mutates ievent.
 *
 * Note: This is a temperary placeholder for a more robust system that allows
 *   for control mapping. It will probably be a key->button translation, from
 *   physical to purpose, and so have a slightly different interface, but
 *   this is close enough for now.
 */
static void controlsLookUp(sf::Event const & event, InputEvent ievent)
{
  switch (event.key.code)
  {
  case sf::Keyboard::Left:
    ievent.type = InputEvent::PlayerLeft;
    break;
  case sf::Keyboard::Right:
    ievent.type = InputEvent::PlayerRight;
    break;
  case sf::Keyboard::Up:
    ievent.type = InputEvent::PlayerUp;
    break;
  case sf::Keyboard::Down:
    ievent.type = InputEvent::PlayerDown;
    break;
  case sf::Keyboard::Space:
    ievent.type = InputEvent::PlayerAction;
    break;
  default:
    ievent.type = InputEvent::Ignored;
    return;
  }

  if (sf::Event::KeyPressed == event.type)
    ievent.buttonPressed = true;
  else
    ievent.buttonPressed = false;
}


void InputHandler::eventTranslate (sf::Event const & event, Input & ievent)
{
  switch (event.type)
  {
  case sf::Event::Closed:
    ievent.type = InputEvent::Quit;
    break;
  case sf::Event::KeyPressed:
  case sf::Event::KeyReleased:
    //if (consolUp)
    //  type = Ignored;
    //else
      // Temperary, although it might be a while before we get
      // a proper system for the controls.
      controlslookUp(event, ievent);
    //
    break;
  case sf::Event::TextEntered:
    //if (consolUp)
    //{}
    //else
    //{
      ievent.type = InputEvent::Ignored;
    //}
    break;
  default:
    ievent.type = InputEvent::Ignored;
    break;
  }
}


InputEvent InputHandler::eventTranslate (sf::Event const & event) const
{
  InputEvent ievent;
  eventTranslate(event, ievent);
  return ievent;
}


bool InputHandler::pollEventFrom (sf::Window & win, InputEvent & ie) const
{
  sf::Event sfEvent;
  while (win.pollEvent(sfEvent))
  {
    eventTranslate(sfEvent, ie);
    if (!ie.isIgnored())
      return true;
  }
  return false;
}
