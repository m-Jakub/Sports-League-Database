#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <string>
#include <list>
#include <fstream>

using namespace std;

class League;
class SportsClub;
class Person;
class Agent;
class Player;

class League
{
private:
    static int ID_counter;
    // counter for ID; increments by 1 after creation of Person
    struct Team
    {
        SportsClub *club;
        // pointer to the clas SportsClub
        int points;
        // number of points club has in the league, 0 by default

        Team(SportsClub *club) : club(club), points(0)
        {
        }
    };
    list<Team *> teamList;
    /* list of objects of type Team; list of all teams belonging to the league,
    it is clubs and their points in the current season;
    size of the list is limited by the capacity of the league*/
    list<Agent *> agentList;
    // list of pointers to Agent class; unlimited list of all agents belonging to the league
    list<Player *> playerList;
    // list of pointers to Player class; unlimited list of all players belonging to the league
    int capacity;
    // maximal number of clubs in a league; 20 by default; must be between 4 and 30
    SportsClub *findClub(string name);
    /* checks if a club of the given name exists on the league's teamList (list of structs Team containing clubs);
    if so, returns a pointer to this club; if not, nullptr*/
    Player *findPlayer(int ID);
    /* checks if a player of the given ID exists on the league's playerList;
    if so, returns a pointer to this player; if not, nullptr*/
    Agent *findAgent(int ID);
    /* checks if a agent of the given ID exists on the league's agentList;
    if so, returns a pointer to this agent; if not, nullptr*/
    template <typename T>
    bool exists(T pObject, string type_of_object, string type_of_operation);
    // helping function template; checks if the given pointer to object is not a nullptr; if it is: returns 0 and displays error message, of the unsuccesful operation

public:
    League(int capacity = 20);
    // constructor of League;
    ~League();
    // destructor of League
    bool inputDataFromFile();
    /* reads all the data given in the text file and adds it to the league;
    returns 0 if unsuccesful or 1 if succesful*/
    bool addClub(string name);
    /* creates a SportsClub and adds it to the league's teamList
    returns 0 if unsuccesful or 1 if succesful*/
    bool removeClub(string name);
    /* removes club from all lists and deallocate it's memory;
    returns 0 if unsuccesful or 1 if succesful*/
    int addPlayer(string full_name, int ID = 0);
    /* creates a Player and adds it to the league's list of players,
    returns his or her ID (which could change while created)*/
    bool assignPlayer(string club_name, int ID);
    /* assigns already created player to the club of the given name;
    if the player is already assigned to any club the club buys the player if it is possible;
    returns 0 if unsuccesful or 1 if succesful*/
    bool unassignPlayer(int ID);
    /* removes a player from a club's player list, changes player's pClub pointer to nullptr;
    returns 0 if unsuccesful or 1 if succesful*/
    bool removePlayer(int ID);
    /* removes player from all lists and deallocates it's memory;
    returns 0 if unsuccesful or 1 if succesful*/
    int addAgent(string full_name, int ID = 0);
    // creates an Agent and adds it to the league's list of agents, return ID
    bool assignAgent(int agent_ID, int player_ID);
    /* assigns already created agent to the player of the given ID;
    returns 0 if unsuccesful or 1 if succesful*/
    bool unassignAgent(int agent_ID, int player_ID);
    /* changes the player's pAgent pointer to nullptr,
    removes the player from the agent's playerList;
    returns 0 if unsuccesful or 1 if succesful*/
    bool removeAgent(int agent_ID);
    /* removes agent from all lists and deallocates it's memory;
    returns 0 if unsuccesful or 1 if succesful*/
    int getNumberOfClubs();
    /* returns a number of clubs present in the teamList*/
    int getNumberOfPlayers();
    /* returns a number of players present in the playerList*/
    int getNumberOfAgents();
    /* returns a number of agents present in the agentList*/
    bool payMonthlyIncome(string name);
    /* adds the value of the monthly income of the club of the given name to it's budget;
    returns 0 if the club doesn't exist or 1 if done succesfully*/
    void payAllClubIncomes();
    // does the same as payMonthlyIncome to all clubs
    bool changeSalary(int ID, int salary);
    /* changes the salary of a person with the given ID;
    returns 0 if unsuccesful or 1 if succesful*/
    bool changeBudget(string name, long long new_budget);
    /* changes the budget of a club with the given name;
    returns 0 if unsuccesful or 1 if succesful*/
    bool changeMonthlyIncome(string name, int new_income);
    /* changes the monthly income of a club with the given name;
    returns 0 if unsuccesful or 1 if succesful*/
    bool changeSalaryLeftAtDisposal(string name, int new_salary);
    /* changes the salary left at disposal of a club with the given name;
    returns 0 if unsuccesful or 1 if succesful*/
    bool changeTrophies(string name, int new_trophies);
    /* changes the trophies number of a club with the given name;
    returns 0 if unsuccesful or 1 if succesful*/
    bool changePoints(string name, int new_points);
    // changes number of points club has in the league
    bool buyPlayer(string name, int player_ID);
    /* purchase can be done only if the player belongs to the other club
    (if the player does not have a club we obviously can't buy him or her,
    if the player does not belong to any club we can use just assignPlayer method)
    adds the player of the given ID to the playerList of the club of the given name,
    sets player's pClub pointer to this club; performs money exchange between clubs;
    returns 0 if unsuccesful (a.o. player's value is higher than the club budget) or 1 if succesful*/
    void printClub(string name);
    // prints the club data of the given name
    void printClubPlayerList(string name);
    // prints the list of players belonging to the club o a given name
    void printClubPoints();
    /* prints all the clubs and their points*/
    void printTeamList();
    // prints club list sorted and their trophies, also prints this number
    void printAllClubs();
    // prints all clubs with all their data
    void printPlayerList();
    // prints the list of all players in the league with their data
    void printByID(int ID);
    // prints data of person with the given ID
    void printAgentList();
    // prints the list of all agents in the league with their data
    void printPlayersOfAgent(int agent_ID);
    // prints the list of players agent of the given ID works for
    void printAll();
    // prints all the data of the league
};

class SportsClub
{
private:
    string name;
    // name of the club, unique
    list<Player *> playerList;
    // list of players belonging to the club; size cannot be higher than 50
    int number_of_players;
    // number of players on the club's playerList
    int monthly_income;
    // monthly income of the club, which can be spent on salaries for players
    int salary_left_at_disposal;
    /* number indicating how much money is left at disposal of club
    for paying players' salaries; it is a value of monthly income
    minus the sum of all salaries of players belonging to the club*/
    int trophies;
    // number of trophies which indicates how many times team have won any league
    long long budget;
    // money that can be spent for buying players
    bool addPlayer(Player *player);
    /*helping function: adds player to the playerList; returns 0 if unsuccesful or 1 if succesful,
    there can't be more than 99 players on the list; manages the handling of salary*/

public:
    SportsClub(string name);
    // constructor of the club
    ~SportsClub();
    // destructor of the club
    string getName() const;
    // returns name
    int getMonthlyIncome() const;
    // returns mothly income
    int getSalaryAtDisposal() const;
    // returns salary left at disposal
    int getTrophies() const;
    // returns trophies
    long long getBudget() const;
    // returns budget
    bool hirePlayer(Player *player);
    /* if the player is already hired in another club, he or she must be bought, so:
    lowers the budget by the value of bought player and adds them to the playerList;
    if it's a free player, the budget stays the same; returns 0 if unsuccesful or 1 if succesful*/
    bool freePlayer(Player *player);
    /* removes the player from the playerList (if he or she is there);
     returns 0 if unsuccesful or 1 if succesful*/
    bool sellPlayer(Player *player);
    /* this method is called when the player is being bought by another club,
    it handles the increase of budget after the transfer, and removes them from the club's player list*/
    void clearPlayerList();
    // removes every pointer from the playerList
    void clearPlayersPointers();
    // sets pClub of every club's player to nullptr
    bool changeMonthlyIncome(int new_income);
    // changes the club's monthly income; returns 0 if unsuccesful or 1 if succesful
    void payMonthlyIncome();
    // adds one monthly_income to the club's budget
    bool changeSalaryAtDisposal(int new_salary);
    // changes salary at disposal; returns 0 if unsuccesful or 1 if succesful
    bool changeTrophies(int new_trophies);
    // changes value of trophies; returns 0 if unsuccesful or 1 if succesful
    bool changeBudget(long long new_budget);
    // changes value of budget; returns 0 if unsuccesful or 1 if succesful
    void printName();
    // prints the name of the club
    void printNameAndTrophies();
    // prints name of the club and it's number of trophies
    void printPlayerList();
    // prints the list of all players of the club
    void print();
    // prints all club data
};

class Person
{
private:
    int ID;
    // unique ID of person allowing indentification of person, increments of 1
    string full_name;
    // person's full name, not unique
    int salary;
    // person's salary

public:
    Person(string name, int ID);
    // constructor
    ~Person();
    // destructor
    int getID() const;
    // returns ID
    string getFullName() const;
    // returns full_name
    int getSalary() const;
    // returns salary
    bool changeSalary(int newSalary);
    // changes person's salary
    virtual void print();
    // prints person's data
    void printNameAndID();
    // prints player's name and ID
};

class Agent : public Person
{
private:
    list<Player *> playerList;
    // list of players agent works for; size of the list is limited by 5
public:
    Agent(string name, int ID);
    // constructor
    ~Agent();
    // destructor
    bool addPlayer(Player *player);
    /* adds a pointer to player to the playerList; returns 1, if done properly;
    returns 0, if cannot be done (if player would be 6 on the list or player does not exist)*/
    bool removePlayer(Player *player);
    // removes player from the agent's playerList
    void clearPlayersPointers();
    // sets pAgent of every agent's player to nullptr
    void print() override;
    // prints agent's data
    void printPlayerList();
    // prints data of all players agent works for
};

class Player : public Person
{
private:
    int value;
    // value of the player
    SportsClub *pClub;
    // pointer to the club player belongs to
    Agent *pAgent;
    // pointer to the agent of the player

public:
    Player(string name, int ID);
    // constructor
    ~Player();
    // destructor
    void assignClub(SportsClub *club);
    // sets the pointer pClub to the given club or nullptr
    void assignAgent(Agent *agent);
    // sets the pointer pAgent to the given agent or nullptr
    int getValue() const;
    // returns player's value
    bool changeValue(int newValue);
    // changes player's value
    string getClubName() const;
    // returns the name of the club person belongs to
    int getAgentID() const;
    // returns the ID of the player's agent, if the player has no agent returns 0
    bool hasClub();
    // returns 1 if a Player is hired in any club and 0 if not
    void printNameIDandValue();
    // printing used by club for listing it's players
    void print() override;
    // prints player data
};

#endif // DECLARATIONS_H