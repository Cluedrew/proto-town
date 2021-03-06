/* Main function for InkV.7.3
 *
 * It handles any command line arguments (currantly, all are ignored) and
 * contains the five stages and the main loop.
 *
 * For errors it will print out a label if this is a debug build and will
 * catch and print out the what messages from any exceptions, returning
 * a failure exit code in these cases.
 */

#include <iostream>
#include <exception>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "super-grid.hpp"
#include "map.hpp"
#include "image-lib.hpp"
#include "loop-clock.hpp"
#include "mob-collect.hpp"
#include "image-def.hpp"
#include "event-queue.hpp"
#include "input-event.hpp"
#include "input-handler.hpp"

int main (int argc, char * argv[])
{
#ifdef DEBUG
  std::cerr << "Debug Build" << std::endl;
#endif
  try
  {
    // === set-up ===
    bool running = true;

    // The image library: contains all of the loaded textures.
    // Will throw an exception if they don't all load.
    ImageLib imageLib;

    // The window that the game takes place in.
    sf::RenderWindow window(sf::VideoMode(800, 600), "inkv7",
                            sf::Style::Titlebar | sf::Style::Close);

    // The factory for in game mobs.
    MobCollect mobs(imageLib);
    mobs.spawn(MobID::player, 50, 50);

    // The map, its "tile set" comes from the imageLib.
    Map map(imageLib);

    // Part of the input handler.
    InputHandler inHandle;

    // Start the game clock right before hitting the main loop. 60fps
    LoopClock loopClock(60);

    // === main loop ===
    while (running)
    {
      // === event handler ===
      InputEvent event;
      while (inHandle.pollEventFrom(window, event))
      {
        switch (event.type)
        {
          case InputEvent::Quit:
            running = false;
            break;
          case InputEvent::Ignored:
            std::cerr << "Ignored event appeared in the event loop.\n";
            break;
          default:
            inputEventQueue.regesterEvent(event);
            break;
        }
      }
      // === update ===
      mobs.update(loopClock.getIncrement(), map);

      // === render ===
      window.clear(sf::Color::Black);
      window.draw(map);
      window.draw(mobs);
      window.display();

      // === wait ===
      loopClock.wait();
    }

    // === clean up ===
    window.close();

    return 0;
  }
  catch (std::exception & e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
