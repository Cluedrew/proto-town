#include "input-event.hpp"

// Implementation of the InputEvent predicate functions.

bool InputEvent::isImmediate () const
{
  return type == Quit;
}

bool InputEvent::isIgnored () const
{
  return type == Ignored;
}
