#ifndef INPUT_EVENT_HPP
#define INPUT_EVENT_HPP

/* Class that repersents events from the outside world.
 *
 * Convert to GameEvent and have it cover all events in the game? Will there
 * even be an event system for other parts of the game?
 */


struct InputEvent
{
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

  //struct PlayerButtonData
  //{
  //  Controls button;
  //  bool isPressed;
  //};

  //struct ConsolInputData
  //{
  //  ... text;
  //};

  TypeValue type;

  // Later this will be a rather complex union to save space.
  // For player events, was it a press or a release?
  bool buttonPressed;


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
