#include "input-handler.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include "input-event.hpp"
#include "control-map.hpp"

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
static void controlsLookup(sf::Event const & event, InputEvent & iEvent)
{
  /*
  static ControlMap mapping;
  Controls button = mapping.lookupKey(event.key.code);
  switch (button)
  {
  case Controls::Up:
    ievent.type = InputEvent::PlayerUp;
    break;
  case Controls::Down:
    ievent.type = InputEvent::PlayerDown;
    break;
  case Controls::Left:
    ievent.type = InputEvent::PlayerLeft;
    break;
  case Controls::Right:
    ievent.type = InputEvent::PlayerRight;
    break;
  case Controls::Action:
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
  */
  static ControlMap mapping;
  iEvent.player.button = mapping.lookupKey(event.key.code);
  if (iEvent.player.button == Controls::Cap)
    iEvent.type = InputEvent::Ignored;
  else
  {
    iEvent.type = InputEvent::Player;
    iEvent.player.isPress = (sf::Event::KeyPressed == event.type);
  }
}

void InputHandler::eventTranslate
    (sf::Event const & sfEvent, InputEvent & iEvent) const
{
  switch (sfEvent.type)
  {
  case sf::Event::Closed:
    iEvent.type = InputEvent::Quit;
    break;
  case sf::Event::KeyPressed:
  case sf::Event::KeyReleased:
    controlsLookup(sfEvent, iEvent);
    break;
  case sf::Event::TextEntered:
    iEvent.type = InputEvent::Ignored;
    break;
  default:
    iEvent.type = InputEvent::Ignored;
    break;
  }
}


InputEvent InputHandler::eventTranslate (sf::Event const & sfEvent) const
{
  InputEvent iEvent;
  eventTranslate(sfEvent, iEvent);
  return iEvent;
}


bool InputHandler::pollEventFrom
    (sf::Window & window, InputEvent & iEvent) const
{
  sf::Event sfEvent;
  while (window.pollEvent(sfEvent))
  {
    eventTranslate(sfEvent, iEvent);
    if (!iEvent.isIgnored())
      return true;
  }
  return false;
}
