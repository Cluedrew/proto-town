#include "input-event.hpp"

// Implementation of the InputEvent.

// There are some structural pieces I laid out to make sure they fit but they
// aren't all used yet. The consol for instance is not in the game yet.

// Constructors and Deconstructor:
InputEvent::InputEvent (TypeValue type = Ignored) :
    type(type)/*, consolUp(false)*/
{}


InputEvent::~InputEvent ()
{}


// Implementation Functions:

/* controlsLookUp(event)
 * Handles KeyPressed and KeyReleased events, mapping them by the current
 * control scheme.
 * Params: Constant reference to an initialized SFML KeyPressed/KeyReleased
 *   event.
 * Effect: Mutates this InputEvent.
 */
void InputEvent::controlsLookUp(sf::Event const & event)
{
  // Currently the system is hardwired.
  switch (event.key.code)
  {
  case sf::Keyboard::Left:
    type = PlayerLeft;
    break;
  case sf::Keyboard::Right:
    type = PlayerRight;
    break;
  case sf::Keyboard::Up:
    type = PlayerUp;
    break;
  case sf::Keyboard::Down:
    type = PlayerDown;
    break;
  case sf::Keyboard::Space:
    type = PlayerAction;
    break;
  default:
    type = Ignored;
    return;
  }
}

void InputEvent::lookUp(sf::Event const & event)
{
  switch (event.type)
  {
  case sf::Event::Closed:
    type = Quit;
    break;
  case sf::Event::KeyPressed:
  case sf::Event::KeyReleased:
    //if (consolUp)
    //  type = Ignored;
    //else
      controlsLookUp(event);
    //
    break;
  case sf::Event::TextEntered:
    //if (consolUp)
    //{}
    //else
      type = Ignored;
    //
    break;
  default:
    type = Ignored;
    break;
  }
}

TypeValue InputEvent::getType () const
{
  return type;
}

bool InputEvent::isImmediate () const
{
  return type == Quit;
}

bool InputEvent::isIgnored () const
{
  return type == Ignored
}
