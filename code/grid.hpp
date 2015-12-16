#ifndef GRID_HPP
#define GRID_HPP

/* The Grid is a container for 2d data of fixed size. It is essentually an wrapper
 * around a 2d array.
 */

#include <vector>
#include <string>
#include <SFML/Graphics/Rect.hpp>

template <typename T>
class SuperGrid;

template<typename T>
class Grid
{
private:
  int const xLen;
  int const yLen;

  std::vector<T> data;

  static std::string outOfRangeAt;
  static std::string outOfRangeSb;

protected:
public:
  Grid (int x, int y, T const & fill = T());
  /* Basic constructor, creates a x by y Grid.
   * Params: The size in the primary axis, x, and the secondary axis, y. Data
   *   is grouped by the primary access first. Optionally provide a value to
   *   fill the grid with.
   */

  Grid (int x, int y, std::vector<T> const & fill);
  /* Vector to Grid constructor, fill a grid with the contents of the vector.
   * Params: The size in the primary axis, x, and the secondary axis, y. fill
   *   should be x*y in size and contain the initial values of the Grid.
   *
   * The ordering of elements in the vector should look like this:
   *  (0,0), (1,0), ..., (x-1,0), (0,1), ..., (x-1,y-2), (0,y), ..., (x-1,y-1)
   */

  Grid (int x, int y, T(*fill)(int xi, int yi));
  /* Mapping constructor, fill each item in the Grid with the result of a map.
   *   from the location in the Grid to the data type.
   * Params: The size in the primary axis, x, and the secondary axis, y. A
   *   function which takes the location in the Grid and returns a value to
   *   fill that location of the grid with.
   */

  Grid (Grid<T> const &);
  // Copy constructor

  virtual ~Grid();

  Grid<T> & operator= (Grid<T> const & other);
  /* Assignment operator
   * Except: [Strong] Throws ivalid_argument if other is not the same size of
   *   Grid as this.
   */
  int xSize() const;
  int ySize() const;
  /* Return the size of the Grid in one of the two given axis.
   * Return: A integer greater than 0.
   * Except: [No Throw]
   */

  T & at (int x, int y);
  T const & at (int x, int y) const;
  /* Returns a reference to the element at possition (x,y).
   * Params: 0 <= x < xSize() & 0 <= y < ySize()
   * Return: A reference, const if on the object is const.
   * Except: Throws std::out_of_range if x or y are out of range.
   */

  bool inRange (sf::IntRect const & bounds) const;
  bool inRange (int x1, int y1, int x2, int y2) const;
  /* Check to see if a given area is with the grid.
   * Params: Give the area to check.
   * - bounds: A rectangle, gives the area starting at the left top (x,y) and
   *   extending for width in the primary x axis and height in the secondary y
   *   axis.
   * - x1: The first x location included in the area.
   * - y1: The first y location included in the area.
   * - x2: The first x location after x1 not in the area.
   * - y2: The first y location after y1 not in the area.
   * Return: Equiliant to the following:
   *   0 <= bounds.left <= bounds.left + bounds.width <= this->xSize() AND
   *   0 <= bounds.top <= bounds.top + bounds.height <= this->ySize() OR
   *   0 <= x1 <= x2 <= this->xSize() && 0 <= y1 <= y2 <= this->ySize()
   * Except: [No Throw]
   */

  Grid<T> subGrid (sf::IntRect const & bounds) const;
  Grid<T> subGrid (int x1, int y1, int x2, int y2) const;
  /* Returns a new Grid containing a subsection of this Grid.
   * Params: bounds or (x1,y1,x2,y2) must give an area the Grid, see inRange.
   * Return: A new Grid containing copied elements.
   * Except: Throws std::out_of_range if any coordinate is out of range.
   */

  template<typename U>
  Grid<U> subGrid (sf::IntRect const & bounds, U (*mapping)(T const &)) const;
  template<typename U>
  Grid<U> subGrid (int x1, int y1, int x2, int y2,
                   U (*mapping)(T const &)) const;
  /* Returns a new Grid containing a mapped setion of this Grid.
   * Params: bounds or (x1,y1,x2,y2) must give an area the Grid, see inRange.
   *   mapping is a function to copy and convert items for the new Grid.
   * Return: A new Grid, containing copies of the return values of mapping.
   * Except: Throws std::out_of_range if any coordinate is out of range.
   */

  template<typename U>
  Grid<U> subGrid (sf::IntRect const & bounds,
                   U (*mapping)(T const &), U const & asNil) const;
  template<typename U>
  Grid<U> subGrid (int x1, int y1, int x2, int y2,
                   U (*mapping)(T const &), U const & asNil) const;
  /* Return a new Grid containing a filled map of this grid.
   * Params: bounds or (x1,y1,x2,y2) giving a rectangluar area.
   *   mapping is a function to copy and convert items for the new Grid and
   *   asNil is copied to fill in items that are out of range of the old Grid.
   * Return: A new Grid, containing copies from mapping or of asNil.
   */

  friend class SuperGrid<T>;
};

// I was going to template the x & y as well but I didn't want to risk having to
// know the height and width at compile time being a problem.

#include "grid.epp"

#endif//GRID_HPP
