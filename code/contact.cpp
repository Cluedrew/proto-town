#include "contact.hpp"

// Implementation of the constact header.

// Constructor
Contact::Contact () :
  sides()
{}

Contact::Contact(Contact const & other) :
  sides(other.sides)
{}

// Deconstructor
Contact::~Contact() {}


// Assignment
Contact & Contact::operator= (Contact const & other)
{
  sides = other.sides;

  return *this;
}


// Equality
bool Contact::operator== (Contact const & other) const
{
  return sides == other.sides;
}

// Inequality
bool Contact::operator!= (Contact const & other) const
{
  return sides != other.sides;
}


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

// see header
bool Contact::hasBottomContact() const
{
  return sides[BottomLeft] || sides[Bottom] || sides[BottomRight];
}
