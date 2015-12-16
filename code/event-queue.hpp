#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

/* Defines an event queue class template and instances of that template class.
 * Each of these instances, that is the ones defined at the bottem of this
 * file, are globably avaible creating a many-to-many queue.
 *
 * Currantly, this is just a wrapper around a standard queue, but I might add
 * more functionality later (particulaly for viewing elements without deleting
 * them from the queue).
 * 
 * Its not a perfect solution but better than passing messages across every
 * container and component.
 */

#include <queue>
#include "player-event.hpp"

// Event Queue Class =========================================================
template<typename T>
class EventQueue
{
private:
  std::queue<T> data;
protected:
public:
  EventQueue ();
  /* Creates an empty EventQueue.
   */

  virtual ~EventQueue ();

  void regesterEvent (T const &);
  /* Add a new event to the EventQueue.
   * Params: A constant reference to the new element of the EventQueue.
   * Effect: Increases the size of the EventQueue by one with a new oldest
   *   element.
   */

  bool pollEvent (T &);
  /* Check the first element in the EventQueue, copying and removing it if
   *   possible and returning the success.
   * Params: A reference to the
   * Effect: If the queue is non-empty, mutates the parameter to match the
   *   first element in the queue and then removes that element.
   * Return: If the queue was non-empty returns true, otherwise returns false.
   */
};

#include "event-queue.epp"

// Event Queue Instances =====================================================

// Holds input events colleted from the main loop for the player
extern EventQueue<PlayerEvent> playerEvents;

#endif//EVENT_QUEUE_HPP
