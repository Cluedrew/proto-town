#ifndef PLAYER_EVENT_HPP
#define PLAYER_EVENT_HPP

/* Player events, that is to say events that have been processed by the input
 * loop for the player. They serve the same role as sfml events and even
 * follow a similar pattern in design.
 */

struct PlayerEvent
{
  // Enumeration of the types of player events.
  // Currantly these all map to an input key.
  enum PlayerEnum
  {
    KeyUp,
    KeyRight,
    KeyDown,
    KeyLeft,
    KeyAction
  };

  // The key that was hit.
  PlayerEnum type;
  // Was the key pressed (true) or released (false)?
  bool pressed;
};

#endif//PLAYER_EVENT_HPP

