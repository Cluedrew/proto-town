#ifndef BUTTON_HPP
#define BUTTON_HPP

// An enumeration of the mappable/player controls.

enum class Button
{
  Up,
  Down,
  Left,
  Right,
  Action,
  Cap
};

// The number of valid button codes, excludes Button::Cap.
extern const unsigned int numOfButtons;

template<typename T>
using ButtonArray = T [int(Button::Cap)];

#endif//BUTTON_HPP
