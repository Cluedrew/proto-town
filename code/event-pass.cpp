#include "event-pass.hpp"

/* Implement the EventPass class.
 * Text entered events come in after key down events.
 *
 */

#include <SFML/Window.hpp>
#include "event-queue.hpp"

// Static Field Declaration ==================================================
bool EventPass::directToConsol = false;
Mob * EventPass::player = nullptr;

// Static Functions ==========================================================
// Load in pointers for the targets of the events.
void EventPass::loadTargets (Mob * player_/*, Consol*/)
{
  player = player_;
}

// Get the 'processed' keycode from the keystroke.
static PlayerEvent::PlayerEnum lookUpKey (sf::Keyboard::Key key)
{
  switch (key)
  {
  case sf::Keyboard::Left:
    return PlayerEvent::KeyLeft;
  case sf::Keyboard::Right:
    return PlayerEvent::KeyRight;
  case sf::Keyboard::Up:
    return PlayerEvent::KeyUp;
  case sf::Keyboard::Space:
  default:
    return PlayerEvent::KeyAction;
  }
}

// Handler for KeyDown and TextEntered events.
void EventPass::handleEvent (sf::Event const & event)
{
  /*static bool directToConsol = false;
  if (sf::Event::KeyPressed == event.type &&
      sf::KeyBoard::Return == event.key.code)
  {
    directToConsol = !directToConsol;
  }
  else if (sf::Event::TextEntered == event.type &&
      '\n' == event.text.unicode)
  {}*/
  
  // Regester an event with the player EventQueue
  if (sf::Event::KeyPressed == event.type)
  {
    PlayerEvent pEvent = {lookUpKey(event.key.code), true};
    playerEvents.regesterEvent(pEvent);
  }
  else if (sf::Event::KeyReleased == event.type)
  {
    PlayerEvent pEvent = {lookUpKey(event.key.code), false};
    playerEvents.regesterEvent(pEvent);
  }
}