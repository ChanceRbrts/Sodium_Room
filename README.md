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
???

### Possible Mechanics
Rope - Allows you to climb to out of reach areas assuming your throw range is good. Also allows you to swing on the rope. (Maybe have it so you can jump and throw the rope?)


## End Goal
Find whatever you can to determine where you are when you're asleep? (If going with the Avatar-ish Unethical Turing Test idea)
See what's hiding in the middle of the void?

# Possible Areas
Opening - A cityscape that starts out gloomy and then turns to rain as you go into the main door of the house. As you go in the house, the door erases itself? (Meant only as a tutorial, as well as a way to unlock a New Game+)

Colored Area (The Studio?) - Starts out dark, has colored lights that change the properties of things around it until you end up turning the lights back on.

Rainforest/Garden - A garden where there's a ton of rain and growing plants. Possible enemy could be a venus fly trap that grows from a red rain or something?

Rooftops - On the top of the opening; Unsure what effect to put here yet...

The Tower - A tower that constructs itself up as you go near it. Could introduce doors that are drawn in? Could be part of the garden? Teaches you to look for hidden blocks.



Void - An area that's only available through a few weird means. Seems to appear whenever it wants. What will probably be the weirdest area.
 
# Shader Stuff
 
## Rain (Done)
Rain that melts you down. There's a red variation that melts you down instantly, rather than if you stop moving that will go a little later in the game.
 
## Solid Blocks (Done)
Useful for some sort of puzzle and platforming section. Also useful for hidden blocks of some sort. Definitely have some sort of idea on how I might make a level out of this.

## Transportation (Done)
A wall that collapses and goes in on itself. The most dreamlike of the effects, I might have it start by doing only half a screen to make it look like you've gone on the ceiling and use some collision changes or something to keep that effect?

## Cut Screen (Not Started)
A screen that's cut into four parts, but which is seamless to get in and out of. Shouldn't be too hard to do? Could be more dream-like by forcing a player split during a later part of the game.

## Anti-Chamber Portals (Not Started)
Of course, to make it non-euclidean, we should have seamless portals. This could also be used to do different variations of each room to make slight alterations anytime someone visits that room?

## Hidden Chambers (Mostly Done)
Parts of the level that stretch and depress from the view of the player. If you're in one of these rooms, you either go to a void or you see a fade in for another part of the level? Either that, or the player could enter these areas as a form of fast travel?

## Walls that close and open up to something different (Not Started)
A different version of the hidden chambers, perhaps?

## Rooms that act different when illuminated in different light (Not Started)
This could be an interesting set of rooms to explore.

## Reset Rooms (Not Started)
A button that you push to reset the state of the room (except for your position). Could make it so we could make some interesting non-euclidean puzzles without horribly soft locking the player.

## Visual Shader Effects (Not Started)
So stuff like the sin wave effect could show up a little later in the game or something. (Maybe caused by some sort of emitter?)

## Doors that you can only enter when they're formed. (Not Started)
Doors that are normally not there but can be entered if the light is shined just right or everything aligns to create a door. Could help with the dream logic of this all. (Need to add some sort of texture first or something.)

# Build Instructions
If I decide to make this public at some point, I should add some stuff to it. But I'll at least add some OS X build instructions for now. (Especially if I re-add GLUT support.)

## Setup
### OSX 
You can find the SDL framework here: https://www.libsdl.org/download-2.0.php

You can find the SDL-image framework here: https://www.libsdl.org/projects/SDL_image/

Make sure to get both of the binaries. From there, open the .dmgs, and move the frameworks into /Library/Frameworks.

(If you don't have admin access, move them to ~/Library/Frameworks)

## Compilation
Run make to compile the program.
Run `./game` to then run the game.

