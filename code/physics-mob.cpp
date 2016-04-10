#include "physics-mob.hpp"

// Implementation of the PhysicsMob.

#include "physics-n.hpp"
#include "accel-request.hpp"

#include <iostream>


// see header
void PhysicsMob::accelUp (AccelRequest const & request, sf::Time const & dt)
{
  ddy = -request.process(-dy, dt);
}

// see header
void PhysicsMob::accelDown (AccelRequest const & request, sf::Time const & dt)
{
  ddy = request.process(dy, dt);
}

// see header
void PhysicsMob::accelLeft (AccelRequest const & request, sf::Time const & dt)
{
  ddx = -request.process(-dx, dt);
}

// see header
void PhysicsMob::accelRight (AccelRequest const & request, sf::Time const & dt)
{
  ddx = request.process(dx, dt);
}


// see header
PhysicsMob PhysicsMob::forwardCopy(sf::Time const & time) const
{
  float dt = time.asSeconds();
  return PhysicsMob(x + dx * dt + 0.5f * ddx * dt * dt,
                    y + dy * dt + 0.5f * ddy * dt * dt,
                    w, h,
                    dx + ddx * dt, dy + ddy * dt,
                    ddx, ddy);
}


#ifdef DEBUG
// see header
void PhysicsMob::print(bool line) const
{
  return print(std::cout, line);
}

// see header
void PhysicsMob::print(std::ostream & out, bool line) const
{
  out << "[(" << x << ',' << y << ")(" << w << ',' << h << ")(";
  out << dx << ',' << dy << ")(" << ddx << ',' << ddy << ")]";

  if (line)
    out << '\n';
}

// see header
std::ostream & operator<< (std::ostream & out, PhysicsMob const & physMob)
{
  physMob.print(out);
  return out;
}
#endif//DEBUG
