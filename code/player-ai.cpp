#include "player-ai.hpp"

// Implementation of the player's IA component.

#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "event-queue.hpp"
#include "player-event.hpp"

// Constructors and Deconstructor ============================================
PlayerAI::PlayerAI () :
  fallTimer(sf::Time::Zero)
{}

PlayerAI::~PlayerAI ()
{}

// Create a duplicate of a PlayerAI.
PartAI * PlayerAI::duplicate ()
{
  return new PlayerAI();
}

// Implementation Functions ==================================================
// Updates the player according to the situation and input.

void PlayerAI::update (Mob & mob, sf::Time const & fr, Map & map)
{
  accelMob(mob, 0.0f, 0.0625f);

  // Mini-event loop for the player events.
  PlayerEvent pEvent = {PlayerEvent::KeyAction, false};
  while (playerEvents.pollEvent(pEvent))
  {
    switch (pEvent.type)
    {
      // Jump
    case PlayerEvent::KeyUp:
      if (pEvent.pressed)
        accelMob(mob, 0.0f, -5.f);
      break;
      // Move Left
    case PlayerEvent::KeyLeft:
      //if (pEvent.pressed)
      break;
      // Move Right
    case PlayerEvent::KeyRight:
      //if (pEvent.pressed);
      break;
    default:
      break;
    }
  }
}
/*
void PlayerAI::update (Mob & mob, sf::Time const & fr, Map & map)
{
  // This is from the temparary class Fall AI, and should atleast be modified
  // to fit the new context. (The mutable static might be a problem.)
  //static sf::Time fallTimer = sf::Time::Zero;
  static sf::Time fallAt = sf::milliseconds(250);

  // tileSize = 25;
  // Get the possition of the mob in tiles.
  sf::FloatRect mobBounds = mob.getBounds();
  unsigned int row = ((mobBounds.top + mobBounds.height) / tileSize) - 1;
  unsigned int col = ((mobBounds.left + mobBounds.width) / tileSize) - 1;

  // Check to see if we can fall.
  if (row < mapHeight - 1 && map.at(col, row + 1).passableEh())
  {
    fallTimer += fr;
    if (fallTimer >= fallAt)
    {
      fallTimer -= fallAt;
      moveMob(mob, 0, tileSize);
    }
  }
  else
  {
    fallTimer = sf::Time::Zero;
  }

}*/
