#include "mob-collect.hpp"

// Implementation of the Mob collection

#include "image-lib.hpp"
#include "image-def.hpp"

// Constructors and Deconstructor ============================================
MobCollect::MobCollect (ImageLib const & imgLib_) :
  imgLib(imgLib_)
{}

MobCollect::~MobCollect ()
{}

// Implementation Functions ==================================================
// Draws the mobs to the target.
void MobCollect::draw (sf::RenderTarget & target, sf::RenderStates states)
    const
{
  // Drawn in reverse order so the player (in possition zero) goes on top.
  //for (unsigned int i = mobs.size() - 1 ; i >= 0 ; ++i)
  //  target.draw(mobs[i]);
  //for (std::vector<Mob>::reverse_iterator rit = mobs.rbegin() ;
  //     rit != mobs.rend() ; ++rit)
  //  target.draw(*rit);
  // The reverse order thing is not working right now.
  for (unsigned int i = 0 ; i < mobs.size() ; ++i)
    target.draw(mobs[i], states);
}

// Spawn a new mob and add it to the collection.
void MobCollect::spawn (MobID id, unsigned int x, unsigned int y)
{
  if (MobID::player == id)
    mobs.emplace(mobs.begin(), imgLib, id, x, y);
  else
    mobs.emplace_back(imgLib, id, x, y);
}

// Send the update command to all of the mobs in the collection.
void MobCollect::update (sf::Time const & fr, Map & map)
{
  for (unsigned int i = 0 ; i < mobs.size() ; ++i)
    mobs[i].update(fr, map);
}
