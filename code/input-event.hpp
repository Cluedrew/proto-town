#ifndef INPUT_EVENT_HPP
#define INPUT_EVENT_HPP

/* Class that repersents events from the outside world.
 *
 * Convert to GameEvent and have it cover all events in the game? Will there
 * even be an event system for other parts of the game?
 */

#include <SFML/Window/Event.hpp>

class InputEvent
{
public:
  // Enumeration of all the types of events that the InputEvent can repersent.
  enum TypeValue
  {
    // Any command to quit the game.
    Quit,

    // Events for the in game Consol. [Unused until the Consol appears.]
    //ConsolMode,
    //ConsolInput,

    // Player action keys.
    PlayerUp,
    PlayerRight,
    PlayerDown,
    PlayerLeft,
    PlayerAction,

    // Non-Event, inputs that we don't care about are translated to this.
    Ignored
  };
private:
  TypeValue type;

  void controlsLookUp(sf::Event const &);

protected:
public:
  InputEvent (TypeValue type = Ignored);
  /* Constructor
   */

  virtual ~InputEvent ();

  void lookUp(sf::Event const &);
  /* Look-Up the given SFML event and set this InputEvent to its mapped value.
   *   Note that the lookUp is not stable, it includes all control mappings
   *   and other bits of state.
   * Params: Constant reference to an initialized SFML event.
   * Effect: Changes this class to the lookUp
   */

  TypeValue getType () const;
  /* Get the type of this event.
   */

  bool isImmediate () const;
  /* Does this event have to be handled immediatly (by main)?
   * Return: True if this is an event that is handled by main.
   * (Is this too much coupling?)
   */

  bool isIgnored () const;
  /* Is the event the ignored event?
   * Return: True if this event is Ignored, false otherwise.
   */
};

#endif//INPUT_EVENT_HPP
