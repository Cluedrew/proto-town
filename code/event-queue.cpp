#include "event-queue.hpp"

// The implementation is now in event-queue.epp (include through the .hpp).

// External Definitions ======================================================

// Holds input events colleted from the main loop for the player
EventQueue<PlayerEvent> playerEvents;

EventQueue<InputEvent> inputEvents;
