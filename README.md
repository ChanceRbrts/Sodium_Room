# Sodium Room

This is a game where there are different "lights" in the room that change the properties of the objects around it. For example, rain could have things melt if they stand still in this game; however, shining a red light shining on rain could have the rain melt things instantly.

## Early Ideas
* I want this to be a project where I'm experimenting with shaders. As such, I want stuff to be somewhat shader heavy. I also want the ideas to be weird, due to the second point.

* I want the game to be very dream like. I want this game to introduce dream logic as time progresses, and then use or subvert that dream logic to mess with the player.
 
# Gameplay/Story
 
## Lore
???
 
## Gameplay Loop
Each area has a thing at the end which you need, but which alters the other areas. For example, the top of the tower could have a switch that swaps some kind of hidden blocks or something.
It would also be cool to learn from games like Celeste and slowly teach mechanics as the game progresses.

The main mechanic will be the color lights that are going around; These lights will highlight different areas and change properties of different objects. This includes the player eventually picking up items that can affect lighting.

???

### Mechanics

Lighter - This mechanic emits a "normalizing" light. This light reveals what everything actually looks like and restores everything back to its default behavior, but it runs out after a few seconds.

Flashlight - This mechanic emits a light of a color specified by batteries that you will (eventually be able to) pick up 

#### Possible Mechanics
Rope - Allows you to climb to out of reach areas assuming your throw range is good. Also allows you to swing on the rope. (Maybe have it so you can jump and throw the rope?)


## End Goal
TBD

# Possible Areas
## Garden Demo (WIP)
Opening - A cityscape that starts out gloomy and then turns to rain as you go into the main door of the house. As you go in the house, the door erases itself? (Meant only as a tutorial, as well as a way to unlock a New Game+)

Rainforest/Garden - A garden where there's a ton of rain and honey around it. Possible enemies could include growing plants, or some sort of wildlife. At the end of the garden will be a flashlight, which is explained up above. 

## Other Possible Areas

Rooftops - On the top of the opening; Unsure what effect to put here yet...

The Tower - A tower that constructs itself up as you go near it. Could introduce doors that are drawn in? Could be part of the garden? Teaches you to look for hidden blocks.

Space/Null/Void - An area that's only available through a few weird means. Seems to appear whenever it wants. What will probably be the weirdest area.

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

