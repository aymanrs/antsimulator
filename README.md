# antsimulator
A simple poorly optimized ant simulator. Ants start from their "home", represented by a white pixel, they then spread out looking for food.
If an ant doesn't have any food on it, it leaves a red pheromone trail which becomes less and less intense as the ant makes more moves. Ants that aren't
carrying food will tend to follow blue pheromones. 
If an ant finds food, it carries it back "home" by following red pheromones,
if it reaches its goal the score will increment and she will start looking for food again. Ants carrying food leave a blue trail which is less and less intense as the ant makes more moves.
Clicking somewhere on the screen will put walls there, ants can't traverse walls. Finally pheromones evaporate over time
# launching the simulation
You should have 'make' installed. Go to the project's folder in a terminal and enter "make all" then launch the simulation by typing "./bin/Ants &".
Note that this has been made for Linux, if you want to run it on another OS be sure to modify the makefile and lib files accordingly.
