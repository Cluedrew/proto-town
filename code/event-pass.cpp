#include "event-pass.hpp"

/* Implement the EventPass class.
 * Text entered events come in after key down events.
 *
 */

#include <SFML/Window.hpp>
#include "event-queue.hpp"
#include "input-event.hpp"

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

static PlayerEvent::PlayerEnum lookUpButton (Button button)
{
  switch (button)
  {
  case Button::Left:
    return PlayerEvent::KeyLeft;
  case Button::Right:
    return PlayerEvent::KeyRight;
  case Button::Up:
    return PlayerEvent::KeyUp;
  case Button::Down:
    return PlayerEvent::KeyDown;
  case Button::Action:
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

// Handler for KeyDown and TextEntered events.
void EventPass::handleEvent (InputEvent const & event)
{
  // Regester an event with the player EventQueue
  PlayerEvent pEvent = {PlayerEvent::KeyAction, event.buttonPressed};
  switch (event.type)
  {
  case InputEvent::PlayerLeft:
    pEvent.type = PlayerEvent::KeyLeft;
    break;
  case InputEvent::PlayerRight:
    pEvent.type = PlayerEvent::KeyRight;
    break;
  case InputEvent::PlayerUp:
    pEvent.type = PlayerEvent::KeyUp;
    break;
  case InputEvent::PlayerDown:
    pEvent.type = PlayerEvent::KeyDown;
    break;
  case InputEvent::PlayerAction:
    break;
  case InputEvent::Player:
    pEvent.type = lookUpButton(event.player.button);
    pEvent.pressed = event.player.isPress;
    break;
  default:
    pEvent.type = PlayerEvent::KeyAction;
  }
  playerEvents.regesterEvent(pEvent);
}
