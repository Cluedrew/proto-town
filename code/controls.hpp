#ifndef CONTROLS_HPP
#define CONTROLS_HPP

// An enumeration of the mappable/player controls.

enum class Controls
{
  Up,
  Down,
  Left,
  Right,
  Action,
  Cap
};

extern const unsigned int controlsSize;

template<typename T>
using ControlsArray = T [int(Controls::Cap)];

#endif//CONTROLS_HPP
