<p align="center">
  <img src="https://www.ultraboardgames.com/img/slideshow/othello.jpg" />
</p>
     

# Othello Game in C++

Here is a C++ implementation of the well-known board game Othello. In this game, two players compete against each other in order to have at the end the larger number of tiles on the board. 

For more information about the rules of this game, for example the set of allowed moves, please refer to [Othello's official rules](https://www.worldothello.org/about/about-othello/othello-rules/official-rules/english).

## Getting Started

To set up a local copy and make it work, follow these simple steps.

### Prerequisites

Make sure you have a C++ IDE that supports CMake.

### Installation

1. Clone this repository
   ```sh
   git clone https://github.com/aelskens/Othello_game_C.git
   ```
3. Open a terminal, make sure you are in the appropriate folder location, typically

   *for Mac users*   
   ```sh
   ...:Othello_game_C username$
   ```
   *for Windows users*
   ```sh
   ..\Othello_game_C>
   ```
4. Type in the following command
   ```sh
   make all
   ```
5. To launch the game, type in
   ```sh
   ./main
   ```
<p align="right">(<a href="#top">back to top</a>)</p>

## Usage

The user is invited to choose a 'player type' for each opponent. 
Three types of players have been implemented:
* **human**: the user can play this type of player by typing a valid token position when it is its turn
* **ai**: this is an automated player (more about it in [Documentation](#documentation))
* **folder**: the choice of this type of player allows the user to play his moves in a .txt file; it also allows to use a script containing a set of commands written in advance

Any combination of these player types for both opponents is possible.

As there is no suitable user interface for this project yet, the game is played in the terminal. For this reason, in order to represent the two colors, the following characters have been used: "**X**" for black and "**O**" for white.

### Commands

Using any mode except ai mode, the user can type special commands:
* *help* this will display all the legal moves that the player can play
* *00* this allows the player to skip his turn
<p align="right">(<a href="#top">back to top</a>)</p>

## Documentation

For the AI implementation, the algorithmic choice was a branch-and-bound method, specifically an [alpha-beta pruning algorithm](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning). The AI player evaluates all board states 5 turns later in the game. As a result, the number of computations is quickly non-negligible and this can lead to a maximum delay of 20s for the AI to make its move.
<p align="right">(<a href="#top">back to top</a>)</p>

## References
* [Image](https://www.ultraboardgames.com/img/slideshow/othello.jpg)
* Russell, S. J. and Norvig, P. (2009). *Artificial Intelligence: A Modern Approach*. Prentice Hall, Third Edition. p.161-175.
* Sannidhanam, V. and Annamalai, M. (2015). *An Analysis of Heuristics in Othello*. Washington University, Department of Computer Science and Engineering.
<p align="right">(<a href="#top">back to top</a>)</p>
