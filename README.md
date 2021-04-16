# antsimulator
A simple poorly optimized ant simulator. Ants start from their "home", represented by a white cell, they then spread out looking for food.
If an ant doesn't have any food on it, it leaves a red pheromone trail which becomes less and less intense as the ant makes more moves. Ants that aren't
carrying food will tend to follow blue pheromones. 
If an ant finds food, it carries it back "home" by following red pheromones,
if it reaches its goal the score will increment and she will start looking for food again. Ants carrying food leave a blue trail which is less and less intense as the ant makes more moves.
Pheromones evaporate as time goes on.
# launching the simulation
You should have 'make' installed. Go to the project's folder in a terminal and enter "make all" then launch the simulation by typing "./bin/Ants &".
Note that this has been made for Linux, if you want to run it on another OS be sure to modify the makefile and lib files accordingly. If something goes wrong 
try typing "make mrproper" before "make all".
# Features
Pressing the space bar pauses/runs the simulation.
Left clicking somewhere on the screen will place either empty cells, walls or food.
Pressing "1" switches to empty cells mode, pressing "2" switches to walls mode and "3" switches to food mode.
# some variables:
In include/globals.hpp you can find a list of constants which you can change according to your needs, here's a brief explanation of each:
## evaporation:
how fast pheromones evaporate, the higher this values is, the faster pheromones disappear.
## maxSteps:
the maximum amount of steps an ant can perform after which it doesn't leave any pheromones
## sense:
the "radius" of the ants' vision.
## home:
the coordinates of the "home" cell
## W:
the width of the simulation (in terms of cells)
## H:
the height of the simulation (in terms of cells)
## S:
the length of each cell (in terms of pixels), the higher this values is, the bigger cells are.
## numAnts:
the number of ants. This simulation is pretty slow so keep in mind that this number shouldn't be very high
