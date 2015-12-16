#ifndef EVENT_PASS_HPP
#define EVENT_PASS_HPP

/* A class that passes events to structures that need it, it is a part of
 * the event handling loop
 */

#include <SFML/Window.hpp>
class Mob;

class EventPass
{
private:
  static bool directToConsol;
  static Mob * player;
  /*static Consol * consol;*/
protected:
public:
  static void loadTargets (Mob */*, Consol*/);
  /* Load in pointers for the targets of the events.
   * Params: A pointer to a Mob repersenting the player. (???)
   * Effect: Saves the pointers and will send approperate events to those
   *   locations.
   */
  
  static void handleEvent (sf::Event const & event);
  /* Handler for KeyDown and TextEntered events.
   * Params: A constant reference to an Event.
   * Effect: Varies with the Event.
   */
};

#endif//EVENT_PASS_HPP
