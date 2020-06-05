# Sodium Room

This is a game where there are different "lights" in the room that change the properties of the objects around it.

# Main Game Idea

This is definitely going to be some sort of Platformer (maybe Metroidvania?).
I want this project to be two things.

* I want this to be a project where I'm experimenting with shaders. As such, I want stuff to be somewhat shader heavy. I also want the ideas to be weird, due to the second point.

* I want the game to be very dream like. I want this game to introduce dream logic as time progresses, and then use or subvert that dream logic to mess with the player.
 
# Gameplay/Story
 
## Lore
???
 
## Gameplay Loop
Each area has a thing at the end which you need, but which alters the other areas. For example, the top of the tower could have a switch that swaps some kind of hidden blocks or something.
Taking a page from Celeste and teaching you mechanics as you go through which allows you to explore other areas.

The main mechanic will be the color lights that are going around; These lights will highlight different areas and change properties of different objects.
???

### Possible Mechanics
Rope - Allows you to climb to out of reach areas assuming your throw range is good. Also allows you to swing on the rope. (Maybe have it so you can jump and throw the rope?)


## End Goal
Find whatever you can to determine where you are when you're asleep? (If going with the Avatar-ish Unethical Turing Test idea)
See what's hiding in the middle of the void?

# Possible Areas
## Garden Demo (WIP)
Opening - A cityscape that starts out gloomy and then turns to rain as you go into the main door of the house. As you go in the house, the door erases itself? (Meant only as a tutorial, as well as a way to unlock a New Game+)

Rainforest/Garden - A garden where there's a ton of rain and honey around it. Possible enemies could include growing plants, or something like that. At the end of the garden will be a flashlight. 

## Other Possible Areas

Rooftops - On the top of the opening; Unsure what effect to put here yet...

The Tower - A tower that constructs itself up as you go near it. Could introduce doors that are drawn in? Could be part of the garden? Teaches you to look for hidden blocks.

Void - An area that's only available through a few weird means. Seems to appear whenever it wants. What will probably be the weirdest area.

# Build Instructions

## Setup
### OSX 
You can find the SDL framework here: https://www.libsdl.org/download-2.0.php

You can find the SDL-image framework here: https://www.libsdl.org/projects/SDL_image/

Make sure to get both of the binaries. From there, open the .dmgs, and move the frameworks into /Library/Frameworks.

(If you don't have admin access, move them to ~/Library/Frameworks)

## Compilation
Run make to compile the program.
Run `./game` to then run the game.

