# Sports League Management Simulation

## Console-based application written for an Object-Oriented Programming course project in college

![image](https://github.com/m-Jakub/Sports-League-Management-Simulation/assets/133584402/8d0cedab-37de-44f8-a34c-fe17f06b1786)


### Technologies Used:
* Developed in C++
* Utilizes object-oriented design principles, including encapsulation, inheritance, and polymorphism
* Implements basic data structures and algorithms for managing sports league, clubs and people

### Overview

* The Sports League Management Simulation project aims to provide a comprehensive management system for sports clubs, players, and agents. Its primary focus is on facilitating player transfers between clubs, enabling clubs to hire agents, and maintaining an up-to-date record of points that clubs have in the league. 

* The league contains information about sports clubs, players, and agents. Each club has its own profile, including details such as name, financial information, or number of trophies the club ever acquired. Players are also listed with information about their contracts, and salary requirements. Similarly, agents have their profiles, highlighting their services and fees. 

* The core functionality revolves around facilitating player transfers. Clubs have the option to hire players who are not currently associated with any club. In such cases, the hiring club takes responsibility for the player's salary. Alternatively, clubs can acquire players from other clubs by offering them a financial amount equivalent to the player's value. 

* Additionally, players can utilize a portion of their salary to pay their agent. This feature aims to simulate the real-world practice of players employing agents to negotiate contracts and handle their professional affairs. 

* There is also provided a visual representation of the current state of points for individual clubs. This feature allows administrators, club owners, and sports enthusiasts to keep track of club standings within a sports league. 

* Overall, the Sports League Management Simulation project offers a centralized platform for managing the intricacies of player transfers, agent assignments, and league standings. By utilizing this software, sports organizations can efficiently handle their operations, make informed decisions, and monitor the progress of their clubs within the league. 

### There exist the following classes: 

* League: represents a sports league and contains information about clubs, players, and agents. It provides various functions to manage the league, such as adding/removing clubs, players, and agents, assigning players to clubs, and performing operations like paying salaries, changing budgets, etc. It also has functions for printing different data related to the league. 

* SportsClub: represents a sports club within the league. It has member variables to store club-specific information like name, player list, monthly income, budget, etc. The class provides functions for managing players, such as hiring, selling, and freeing players, as well as changing club-related data like monthly income, budget, and trophies. It also includes functions to print club information. 

* Person: serves as a base class for other classes (Agent and Player) and represents an individual person involved in the league. It contains common attributes like ID, full name, and salary. It provides functions to get and change these attributes and has a print function to display a person's data. 

* Agent: represents an agent who manages players in the league. It inherits from the Person class and includes additional member variables like a list of players associated with the agent. The class provides functions to add/remove players from the agent's list and print agent data. 

* Player: represents a player in the league. It also inherits from the Person class and includes specific member variables like value (indicating player's worth), pointers to the club and agent the player belongs to. It provides functions to assign a club and agent to the player, change player value, check if the player has a club, and print player data.

### Limits and restrictions 

* Quantities like salary, value, monthly income, capacity, score cannot be lower than 0. 

* Club names must be unique, and they cannot have more than 99 players at the time 

* The sum of the salaries of all players cannot be higher than their club's monthly income (controlled with the use of “salary_left_at_disposal” member variable). 

* The salary of the player cannot be lower than the salary of his agent. 

* Agent cannot work for more than 5 players. 

* Club cannot buy a player of higher value than the club budget 

Operations that would result in any of the situations given above are not carried out or the wrong values are changed to the correct ones.

### Testing and instructions 

The program is able to read the data from a text file (no saving available). User can provide one, following the pattern given below:

![image](https://github.com/m-Jakub/Sports-League-Management-Simulation/assets/133584402/6ac6b59d-a43c-43c1-a3d0-c3d159fd4ecf)

which is also included along with the source code.

To compile the program the user should compile all the files. The correctness of program work is checked with the testing scenarios,
which are written in the main.cpp file in a main function. The assert macro is used. If all tests are passed, the message is displayed.
At the beggining the data is read from a file database.txt.

