#include "contact.hpp"

// Implementation of the constact header.

// Constructor
Contact::Contact () :
  sides()
{}

// Deconstructor
Contact::~Contact() {}



// Set one the contact flags on one of the sides.
void Contact::set (Side side, bool to)
{
  sides.set(side, to);
}

// Get a reference to a contact flag.
std::bitset<8>::reference Contact::operator[] (Side side)
{
  return sides[side];
}

// Get the constact flag for side.
bool Contact::operator[] (Side side) const
{
  return sides[side];
}

// Check for contact on a given side.
bool Contact::hasContact(Side side) const
{
  return sides[side];
}

// Check for contact with the ground.
bool Contact::isOnGround() const
{
  return sides[BottomLeft] || sides[Bottom] || sides[BottomRight];
}
