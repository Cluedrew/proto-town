#ifndef CONTACT_HPP
#define CONTACT_HPP

/* Contact class, a wrapper for the bit set that repersents the 8 contact
 * flags for the sides of a mob.
 *
 * A contact flag here is just a boolean that says weither or not there is
 * something in contact with that side of the mob. The 4 flat sides (Top,
 * Right, Bottom & Left) means something is pressed against that side. The 4
 * corners (TopRight, BottomRight, BottomLeft & TopLeft) repersent some
 * diagonal contact with the rectangular mob.
 */

#include <bitset>

class Contact
{
public:
  // The 8 sides for which the contact flags are stored.
  enum Side
  {
    Top,
    TopRight,
    Right,
    BottomRight,
    Bottom,
    BottomLeft,
    Left,
    TopLeft
  };

private:
  std::bitset<8> sides;

protected:
public:
  Contact();
  /* Creates a new Contact object with all flags at zero.
   */

  Contact(Contact const & other);
  /* Create a copy of an existing Contact.
   */

  virtual ~Contact();

  Contact & operator= (Contact const & other);
  bool operator== (Contact const & other) const;
  bool operator!= (Contact const & other) const;

  void set (Side side, bool to);
  /* Set one the contact flags on one of the sides.
   * Params: The side to set the contact flag for and the value to set it to.
   * Effect: After call the flag for side is set to to.
   */

  std::bitset<8>::reference operator[] (Side side);
  /* Get a reference to a contact flag.
   * Params: The side to get the contact flag for.
   * Return: A mutable refrence to the flag.
   */

  bool operator[] (Side side) const;
  /* Get the constact flag for side.
   * Params: The side of the contact flag to check.
   * Return: The value of the contact flag.
   */

  bool hasContact(Side s) const;
  /* Check for contact on a given side.
   * Params: The side of the contact flag to check.
   * Return: The value of the contact flag.
   */

  bool hasSupportingContact() const;
  /* Check for contact on a 'supporting' side.
   * Return: True if there is contact on any bottom side, false otherwise.
   */
};

#endif//CONTACT_HPP
