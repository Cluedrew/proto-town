#include "mob.hpp"

// Implementation of the Mob class.

#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "image-lib.hpp"
#include "image-def.hpp"
#include "part-ai.hpp"
#include "player-ai.hpp"
#include "physics.hpp"

// Constructors and Deconstructor ============================================
Mob::Mob (ImageLib const & imgLib, MobID id, unsigned int x, unsigned int y) :
  sprite(imgLib.GetMobTex(), imgLib.GetMobRect(id, MobStateID::standing)),
  ai(selectAI(id)), phys(x,y, 0,0, 0,0, 0,0)
{
  // Move the sprite to the Mob's starting location.
  sf::Vector2f msPosition(x, y);
  sprite.setPosition(msPosition);
  // Get the size of the Mob from the size of the sprite.
  sf::FloatRect bounds(sprite.getGlobalBounds());
  phys.w = bounds.width;
  phys.h = bounds.height;
}

/*/ Copy Constructor
Mob::Mob (Mob const & other) :
  sprite(other.sprite), ai(other.ai->duplicate())
{}

// Move Constructor
Mob::Mob (Mob && other) :
  sprite(other.sprite), ai(other.ai)
{
  other.ai = nullptr;
}// */

Mob::~Mob ()
{
  delete ai;
}

// Implementation Functions ==================================================
void Mob::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(sprite, states);
}

// Create the approprate AI for a mob with the given ID.
PartAI * Mob::selectAI (MobID id)
{
  switch (id)
  {
  case MobID::player:
    return new PlayerAI();
    break;
  case MobID::cap:
    throw std::invalid_argument("Mob: MobID::cap is not a mob type.");
  }
  // break to get a NullAI
  return new NullAI();
}

// Move the mob one frame forward in time.
void Mob::update (sf::Time const & fr, Map & map)
{
  // Run the AI and perform the local updates.
  ai->update(*this, fr, map);

  // Run forward through time according to physics.
  phys = Physics::singleEntityWithWorld(*this, fr, map);

  // Move the sprite to the Mob's currant location.
  // Sort of wanted this to be in draw, but that has to be constant.
  sprite.setPosition(phys.x, phys.y);
}

// Getter Functions ----------------------------------------------------------
// Get the bounding rectangle around the mob.
sf::FloatRect Mob::getBounds () const
{
  return sf::FloatRect(phys.x, phys.y, phys.w, phys.h);
}

// Get the currant movement rate of the Mob.
sf::Vector2f Mob::getVelocity () const
{
  return sf::Vector2f(phys.dx, phys.dy);
}

// Get the currant PhysicsMob for the Mob.
PhysicsMob Mob::getPhysics () const
{
  return phys;
}
