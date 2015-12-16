#ifndef SUPER_GRID_HPP
#define SUPER_GRID_HPP

/* The SuperGrid is a 2d container of fixed size. It will cluster data in small
 * groups for better memory access (in theory). In terms of use it should act
 * just like a Grid.
 * 
 * NOTE: This class is not currantly used because the only thing it offers over
 * a Grid is some data locality and the game wasn't big enough for that to be
 * an issue. So I took it out but left it here so if the game does get big enough
 * I can add it back in. Hopefully by then it Grid will stop changing so I don't
 * have to duplicate all the changes.
 * 
 * It was only used once as the Map's data container.
 */

#include <vector>
#include <string>
#include "grid.hpp"

template<typename T>
class SuperGrid
{
private:
  int const xLen;
  int const yLen;
  int const xPart;
  int const yPart;
  int const xSecs;
  int const ySecs;
  
  std::vector<Grid<T> > data;
  
  static std::string outOfRangeAt;
  static std::string outOfRangeSb;
  
protected:
public:
  SuperGrid (int xTotal, int yTotal, int xPart, int yPart,
             T const & fill = T());
  /* Create a SuperGrid with of a given size and with the parts of a given size.
   * Params: xTotal and yTotal give the total size of the SuperGrid, the xPart
   *   and yPart give the size of the sub-grids used.
   * Note: If possible have xPart divide xTotal and yPart divide yTotal.
   */

  SuperGrid (SuperGrid<T> const &);
  // Copy constructor.

  virtual ~SuperGrid ();

  SuperGrid<T> & operator= (SuperGrid<T> const & other);
  // Assignment operator

  int xSize() const;
  int ySize() const;
  /* Return the size of the Grid in one of the two given axis.
   * Return: A integer greater than 0.
   */

  T & at (int x, int y);
  T const & at (int x, int y) const;
  /* Returns a reference to the element at possition (x,y).
   * Params: 0 <= x < xSize() & 0 <= y < ySize()
   * Return: A reference, const if on the object is const.
   * Except: Throws std::out_of_range if x or y are out of range.
   */

  Grid<T> subGrid (int x1, int y1, int x2, int y2) const;
  /* Returns a new Grid containing a subsection of this Grid.
   * Params: 0 <= x1 < x2 <= xSize() & 0 <= y1 < y2 <= ySize(), followed by a
   *   mapping function, the results of which will be used in the new Grid.
   *   The subsection used to create the new grid goes from x1 to, but not
   *   including x2 on the x axis and the same for y1, y2 and the y axis.
   * Return: A new Grid. Size x2-x1 by y2-y1
   * Except: Throws std::out_of_range if any coordinate is out of range.
   */

  template<typename U>
  Grid<U> subGrid (int x1, int y1, int x2, int y2, U (*)(T const &)) const;
  /* Returns a new Grid containing a mapped setion of this Grid.
   * Params: 0 <= x1 < x2 <= xSize() & 0 <= y1 < y2 <= ySize()
   *   The subsection used to create the new grid goes from x1 to, but not
   *   including x2 on the x axis and the same for y1, y2 and the y axis.
   * Return: A new Grid. Size x2-x1 by y2-y1
   * Except: Throws std::out_of_range if any coordinate is out of range.
   */
};

// A very scary hack-like thing to get the template to work.
#include "super-grid.epp"

#endif//SUPER_GRID_HPP
