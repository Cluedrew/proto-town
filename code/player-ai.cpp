#include "player-ai.hpp"

// Implementation of the player's IA component.

#include <iostream>
#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "event-queue.hpp"
#include "player-event.hpp"
#include "accel-request.hpp"
#include "utils.hpp"

// Constructors and Deconstructor ============================================
PlayerAI::PlayerAI () :
  fallTimer(sf::Time::Zero), buttons{false}
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
  PhysicsMob & physics = getPhysicsMob(mob);

  static const AccelRequest failingAccel(blocksToPixels(15),
                                         blocksToPixels(10),
                                         blocksToPixels(10));

  static const AccelRequest walkingAccel(blocksToPixels(10),
                                         blocksToPixels(7),
                                         blocksToPixels(7));

  static const AccelRequest standAccel(blocksToPixels(0),
                                       blocksToPixels(10),
                                       blocksToPixels(10));

  InputEvent iEvent;
  while (inputEventQueue.pollEvent(iEvent))
  {
    if (InputEvent::Player == iEvent.type)
    {
      buttons[int(iEvent.player.button)] = iEvent.player.isPress;
    }
  }

  physics.ddx = physics.ddy = 0;


  if (physics.isOnGround())
  {
    if (buttons[int(Button::Up)])
      accelMob(mob, 0.0f, -250.f);

    if (buttons[int(Button::Left)] && !buttons[int(Button::Right)])
      physics.accelLeft(walkingAccel, fr);

    else if (buttons[int(Button::Right)] && !buttons[int(Button::Left)])
      physics.accelRight(walkingAccel, fr);

    else if (!buttons[int(Button::Left)] && !buttons[int(Button::Right)])
      physics.accelRight(standAccel, fr);
  }
  else
    physics.accelDown(failingAccel, fr);
}
