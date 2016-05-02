# proto-town
A side scrolling town management game.

### About
I created this game more as a programming project than for the game.
In particular it is an exersise in making orginized code. Hence I only use one
library, SFML which provides a good interface to work with things outside the
program, such as the screen and keyboard, but little else. Everything else is
part of the language standard or something I made myself.

After 8 months of regular and irregular work I eventually reached the point
where I realized I didn't actually know what is going on inside the project
anymore. The last few bugs have either not been fixed, or fixed by luck.

I am closing this project, although it may recive a few more updates as I
settle on my next project. Hopefully that one will go better as I apply what
I learned in this endevor.

### Closing Remarks
Some important lessons I feel one can take away from this project:
* Messaging: Make sure that the parts of the code base that need to talk to
  each other can, the global EventQueue was really just a hack to connect two
  things that where far appart in code, but linked together in purpose.
* Interface: Not the user interface, but the interface between modules. The
  physics system was almost an afterthought and how it messed with the rest
  of the code base never recived the attention it should have until it was too
  late. As a result, getting the physics system to do even simple things
  required extra wrapper code and essental physics code can be found one or
  two steps from the physics classes themselves.
* Physics: Is hard. To say something insightful: In practise projects keep
  things not related to the goal as simple as possible, even if that means
  changing the question.
* Glass Box: Try to have a way of getting information out of the system as you
  go. There were many times when I could not tell where along the chain things
  were breaking and had to output information every frame to see what was
  going on. This was a passing solution, but there where many issues.
* Testing: OK, this one was never really an issue and a lot of my code is so
  simple that unit tests would really help. But (besides good practice) I
  don't actually know that because I never tracked down some of those bugs.

I learned a couple of things about the language as I went, but most of the
important lessons were on a practice level.
