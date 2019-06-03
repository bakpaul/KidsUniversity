# Kid's University 

This project has been done for a project in collaboration with Strasbourg University. The project is called Kid's University and its purpose is to introduce robotics to young students (13-14 years old). 

## Presentation

It is a little game representing a labyrinth. The goal is to go from D to A by giving simple orders. If the user make the robot go into a wall or an obstacle, he gains "points", the goal beiing to have as few points as possible. 
The game can also be solved automatically.

## How to use it

Call the KidsUni compiled executable following this schem :
>path/to/KidsUni path/to/config/file *(only if you wan to solve it autmatically)* a

The config file should contain some informations and should be formatted as follow : configurationName configurationArg

* robot path/to/RobotImage.png
* controller path/to/PointsImage.png
* parcours path/to/parcoursConfig.txt

The parcoursConfig file should be formated as follow:

>labyrinthHeight labyrinthWidth  
>1 1 1 ... 1 1 1  
>1 0 0 ... 4 0 1  
>: : : : : : : : : : : : :  
>1 0 4 ... 0 0 1  
>1 1 1 ... 1 1 1

With :

* 0 : Path
* 1 : Wall
* 2 : Departure
* 3 : Finish
* 4 : Obstacle

The numbers on the border should only be ones (wall) and one 2 (a departure) and one 3 (a finish) which should be linked by a path. Moreover, if you want the automated solving to work, you shouldn't put a obstacle in front of a wall otherwise the robot will indefinitelly crash into it, such as :

>1 1 1 3 1  
>1 0 0 4 1  
>1 2 1 1 1  
