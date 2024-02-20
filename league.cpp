#include "declarations.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

int League::ID_counter = 1;

SportsClub *League::findClub(string name)
{
    for (list<Team *>::iterator it = teamList.begin(); it != teamList.end(); it++)
        if ((*it)->club->getName() == name)
            return (*it)->club;

    return nullptr;
}

Player *League::findPlayer(int ID)
{
    for (list<Player *>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        if ((*it)->getID() == ID)
            return *it;
    }

    return nullptr;
}

Agent *League::findAgent(int ID)
{
    for (list<Agent *>::iterator it = agentList.begin(); it != agentList.end(); it++)
    {
        if ((*it)->getID() == ID)
            return *it;
    }

    return nullptr;
}

template <typename T>
bool League::exists(T pObject, string type_of_object, string type_of_operation)
{
    if (pObject == nullptr)
    {
        cerr << "Warning given " << type_of_object << " does not exist, " << type_of_operation << " unsuccesful (line: " << __LINE__ << ")" << endl;
        return false;
    }
    else
        return true;
}

bool League::changePoints(string name, int new_points)
{
    if (new_points < 0)
    {
        cerr << "Warning: Imperfect database source file. Points can't be lower than 0 (line: " << __LINE__ << ")" << endl;
        return false;
    }
    for (list<Team *>::iterator it = teamList.begin(); it != teamList.end(); it++)
        if ((*it)->club->getName() == name)
        {
            (*it)->points = new_points;
            return true;
        }

    cerr << "Warning: Club of the given name not found (wrong file reading implementation (line: " << __LINE__ << ")" << endl;
    return false;
}

League::League(int capacity)
{
    if (capacity < 4 || capacity > 30)
    {
        this->capacity = 20;
        cerr << "Warning: capacity must be between 4 and 30, it was changed to the default 20 because of wrong value (line: " << __LINE__ << ")" << endl;
    }
    else
        this->capacity = capacity;
}

League::~League()
{
}

bool League::inputDataFromFile()
{
    string phase_of_reading;
    int counter = 0;
    int ID, tempID;
    SportsClub *club = nullptr;
    Player *player = nullptr;
    Agent *agent = nullptr;

    fstream myFile;
    myFile.open("database.txt", ios::in);
    if (myFile.is_open())
    {
        string line;
        while (getline(myFile, line))
        {
            if (line == "Clubs")
                phase_of_reading = line;
            if (line == "Agents")
                phase_of_reading = line;
            if (line == "Players")
                phase_of_reading = line;

            if (phase_of_reading == "Clubs")
            {
                if (line == "")
                    counter = 0;

                switch (counter)
                {
                case 1:
                    addClub(line); // adding new club with the name read from the file saved at line string
                    club = findClub(line);
                    break;
                case 2:
                    changePoints(club->getName(), atoi(line.c_str())); // changing points stored in Team struct with the use of string to int conversion
                    break;
                case 3:
                    changeMonthlyIncome(club->getName(), atoi(line.c_str()));
                    break;
                case 4:
                    changeSalaryLeftAtDisposal(club->getName(), atoi(line.c_str()));
                    break;
                case 5:
                    changeTrophies(club->getName(), atoi(line.c_str()));
                    break;
                case 6:
                    changeBudget(club->getName(), atoll(line.c_str()));
                    break;
                }
            }

            if (phase_of_reading == "Agents")
            {
                if (line == "")
                    counter = 0;

                switch (counter)
                {
                case 1:
                    ID = atoi(line.c_str());
                    break;
                case 2:
                    ID = addAgent(line, ID);
                    break;
                case 3:
                    changeSalary(ID, atoi(line.c_str()));
                    break;
                }
            }

            if (phase_of_reading == "Players")
            {
                if (line == "")
                    counter = 0;

                switch (counter)
                {
                case 1:
                    tempID = atoi(line.c_str());
                    break;
                case 2:
                    ID = addPlayer(line, tempID);
                    break;
                case 3:
                    changeSalary(ID, atoi(line.c_str()));
                    break;
                case 4:
                    if ((club = findClub(line)) == nullptr)
                        cerr << "Wrong database file, club does not exist" << endl;
                    else
                        assignPlayer(club->getName(), ID);
                    break;
                case 5:
                    if ((agent = findAgent(atoi(line.c_str()))) == nullptr)
                        cerr << "Wrong database file, agent does not exist" << endl;
                    else
                        assignAgent(agent->getID(), ID);
                    break;
                case 6:
                    findPlayer(ID)->changeValue(atoi(line.c_str()));
                    break;
                }
            }

            counter++;
        }
        myFile.close();
        return true;
    }
    else
    {
        cerr << "File does not exist (line: " << __LINE__ << ")" << endl;
        return false;
    }
}

bool League::addClub(string name)
{
    if (teamList.size() == capacity)
    {
        cerr << "Warning: the league has a full number of clubs, addition unsuccesful" << endl;
        return false;
    }
    if (findClub(name) != nullptr)
    {
        cerr << "Warning: club with the given name is already on the list, club was not created (line: " << __LINE__ << ")" << endl;
        return false;
    }

    SportsClub *newClub = new SportsClub(name);
    Team *newTeam = new Team(newClub);
    teamList.push_back(newTeam);
    return true;
}

bool League::removeClub(string name)
{
    for (list<Team *>::iterator it = teamList.begin(); it != teamList.end(); it++)
        if ((*it)->club->getName() == name)
        {
            SportsClub *club = (*it)->club;
            Team *team = (*it);

            club->clearPlayersPointers();
            teamList.erase(it);

            delete club;
            delete team;
            return true;
        }

    cerr << "Warning: club of the given name doesn't exist, it can't be remove (line: " << __LINE__ << ")" << endl;
    return false;
}

int League::addPlayer(string full_name, int ID)
{
    if (ID == 0)
        ID = ID_counter++;

    while (!((findPlayer(ID) == nullptr) && (findAgent(ID) == nullptr)))
        ID = ID_counter++;

    Player *newPlayer = new Player(full_name, ID);
    playerList.push_back(newPlayer);
    return ID;
}

bool League::assignPlayer(string club_name, int ID)
{
    SportsClub *club = findClub(club_name);
    if (!(exists<SportsClub *>(club, "club", "assignment"))) // checking existance of the club
        return false;

    Player *player = findPlayer(ID);
    if (!(exists<Player *>(player, "player", "assignment")))
        return false;

    if (club->hirePlayer(player))
    {
        player->assignClub(club);
        return true;
    }
    return false;
}

bool League::unassignPlayer(int ID)
{
    Player *player = findPlayer(ID);
    if (!(exists<Player *>(player, "player", "unassignment")))
        return false;

    SportsClub *club = findClub(player->getClubName());
    if (club == nullptr)
    {
        cerr << "Player does not belong to any club (line: " << __LINE__ << ")" << endl;
        return false;
    }

    if (club->freePlayer(player))
    {
        player->assignClub(nullptr);
        return true;
    }
    return false;
}

bool League::removePlayer(int ID)
{
    if (unassignPlayer(ID))
    {
        Player *player = findPlayer(ID);
        playerList.remove(player);
        delete player;
        return true;
    }
    else
        return false;
}

int League::addAgent(string full_name, int ID)
{
    if (ID == 0)
        ID = ID_counter++;

    while (!((findPlayer(ID) == nullptr) && (findAgent(ID) == nullptr)))
        ID_counter++;

    Agent *newAgent = new Agent(full_name, ID);
    agentList.push_back(newAgent);
    return ID;
}

bool League::assignAgent(int agent_ID, int player_ID)
{
    Player *player = findPlayer(player_ID);
    if (!(exists<Player *>(player, "player", "unassignment")))
        return false;

    Agent *agent = findAgent(agent_ID);
    if (!(exists<Agent *>(agent, "agent", "unassignment")))
        return false;

    if (agent->addPlayer(player))
    {
        player->assignAgent(agent);
        return true;
    }
    else
        return false;
}

bool League::unassignAgent(int agent_ID, int player_ID)
{
    Player *player = findPlayer(player_ID);
    if (!(exists<Player *>(player, "player", "unassignment")))
        return false;

    Agent *agent = findAgent(agent_ID);
    if (!(exists<Agent *>(agent, "agent", "unassignment")))
        return false;

    if (agent->removePlayer(player))
    {
        player->assignAgent(nullptr);
        return true;
    }
    else
        return false;
}

bool League::removeAgent(int agent_ID)
{
    Agent *agent = findAgent(agent_ID);
    if (!(exists<Agent *>(agent, "agent", "unassignment")))
        return false;

    agent->clearPlayersPointers();
    agentList.remove(agent);
    delete agent;
    return true;
}

int League::getNumberOfClubs()
{
    return teamList.size();
}

int League::getNumberOfPlayers()
{
    return playerList.size();
}

int League::getNumberOfAgents()
{
    return agentList.size();
}

bool League::payMonthlyIncome(string name)
{
    SportsClub *club = findClub(name);
    if (club != nullptr)
        club->payMonthlyIncome();

    cerr << "Club does not exist, payment unsuccesful (line: " << __LINE__ << ")" << endl;
    return false;
}

void League::payAllClubIncomes()
{
    for (Team *team : teamList) // range-based loop iterating through the whole teamList
        team->club->payMonthlyIncome();
}

bool League::changeSalary(int ID, int salary)
{
    Person *person = findPlayer(ID);

    if (person == nullptr)
        person = findAgent(ID);

    if (person == nullptr)
    {
        cerr << "Warning: Person does not exist, change unsuccesful (line: " << __LINE__ << ")" << endl;
        return false;
    }

    if (salary < 0)
    {
        cerr << "Warning: salary can't be lower than 0, operation not done (line: " << __LINE__ << ")" << endl;
        return false;
    }

    if (salary > 2'000'000'000)
    {
        cerr << "Warning: salary can't be higher than 2 000 000 000, operation not done (line: " << __LINE__ << ")" << endl;
        return false;
    }

    if (person->changeSalary(salary))
        return true;
    return false;
}

bool League::changeMonthlyIncome(string name, int new_income)
{
    if (new_income < 0)
    {
        cerr << "Warning: income can't be lower than 0, operation not done (line: " << __LINE__ << ")" << endl;
        return false;
    }

    if (new_income > 2'000'000'000)
    {
        cerr << "Warning: income can't be higher than 2 000 000 000, operation not done (line: " << __LINE__ << ")" << endl;
        return false;
    }

    SportsClub *club = findClub(name);
    if (club != nullptr)
    {
        if (club->changeMonthlyIncome(new_income))
            return true;
        else
            return false;
    }
    else
    {
        cerr << "Warning: Club does not exist, change unsuccesful (line: " << __LINE__ << ")" << endl;
        return false;
    }
}

bool League::changeSalaryLeftAtDisposal(string name, int new_salary)
{
    if (new_salary < 0)
    {
        cerr << "Warning: salary can't be lower than 0, operation not done (line: " << __LINE__ << ")" << endl;
        return false;
    }

    if (new_salary > 2'000'000'000)
    {
        cerr << "Warning: salary can't be higher than 2 000 000 000, operation not done (line: " << __LINE__ << ")" << endl;
        return false;
    }

    SportsClub *club = findClub(name);
    if (club != nullptr)
    {
        if (club->changeSalaryAtDisposal(new_salary))
            return true;
        else
            return false;
    }
    else
    {
        cerr << "Warning: Club does not exist, change unsuccesful (line: " << __LINE__ << ")" << endl;
        return false;
    }
}

bool League::changeTrophies(string name, int new_trophies)
{
    if (new_trophies < 0)
    {
        cerr << "Warning: trophies can't be lower than 0, operation not done (line: " << __LINE__ << ")" << endl;
        return false;
    }

    if (new_trophies > 2'000'000'000)
    {
        cerr << "Warning: trophies can't be higher than 2 000 000 000, operation not done (line: " << __LINE__ << ")" << endl;
        return false;
    }

    SportsClub *club = findClub(name);
    if (club != nullptr)
    {
        if (club->changeTrophies(new_trophies))
            return true;
        else
            return false;
    }
    else
    {
        cerr << "Warning: Club does not exist, change unsuccesful (line: " << __LINE__ << ")" << endl;
        return false;
    }
}

bool League::changeBudget(string name, long long new_budget)
{
    if (new_budget < 0)
    {
        cerr << "Warning: budget can't be lower than 0, operation not done (line: " << __LINE__ << ")" << endl;
        return false;
    }

    if (new_budget > 1'000'000'000'000'000'000)
    {
        cerr << "Warning: budget can't be higher than 2 000 000 000, operation not done (line: " << __LINE__ << ")" << endl;
        return false;
    }

    SportsClub *club = findClub(name);
    if (club != nullptr)
    {
        if (club->changeBudget(new_budget))
            return true;
        else
            return false;
    }
    else
    {
        cerr << "Warning: Club does not exist, change unsuccesful" << endl;
        return false;
    }
}

bool League::buyPlayer(string name, int player_ID)
{
    SportsClub *new_club = findClub(name);
    if (new_club == nullptr)
    {
        cerr << "Warning: Club does not exist, purchase unsuccesful (line: " << __LINE__ << ")" << endl;
        return false;
    }

    Player *player = findPlayer(player_ID);
    if (!(exists<Player *>(player, "player", "purchase")))
        return false;

    if (!(player->hasClub()))
    {
        cerr << "Warning: Player can't be bought, he or she does not have a club, purchase unsuccesful (line: " << __LINE__ << ")" << endl;
        return false;
    }

    SportsClub *previous_club = findClub(player->getClubName());

    if (new_club->hirePlayer(player))
    {
        previous_club->sellPlayer(player);
        player->assignClub(new_club);
        return true;
    }
    else
        return false;
}

void League::printClub(string name)
{
    SportsClub *club = findClub(name);
    if (club == nullptr)
        cerr << "Club of the given name does not exist" << endl;

    else
        club->print();
}

void League::printClubPlayerList(string name)
{
    SportsClub *club = findClub(name);
    if (club == nullptr)
        cout << "Club of the given name does not exist" << endl;

    else
        club->printPlayerList();
}

void League::printClubPoints()
{
    for (list<Team *>::iterator it = teamList.begin(); it != teamList.end(); it++)
        cout << (*it)->club->getName() << " ( " << (*it)->points << " points )" << endl;
}

void League::printTeamList()
{
    for (list<Team *>::iterator it = teamList.begin(); it != teamList.end(); it++)
        cout << (*it)->club->getName() << " ( " << (*it)->club->getTrophies() << " trophies )" << endl;
}

void League::printAllClubs()
{
    cout << "\tPRINTING ALL CLUBS:" << endl;
    for (list<Team *>::iterator it = teamList.begin(); it != teamList.end(); it++)
    {
        (*it)->club->print();
        cout << endl;
    }
}

void League::printPlayerList()
{
    cout << "\tPRINTING ALL PLAYERS:" << endl;
    for (Player *player : playerList)
    {
        player->print();
        cout << endl;
    }
}

void League::printByID(int ID)
{
    if (findPlayer(ID) != nullptr)
    {
        findPlayer(ID)->print();
    }
    else if (findAgent(ID) != nullptr)
    {
        findAgent(ID)->print();
    }
    else
        cout << "Person of the given ID does not exist" << endl;
}

void League::printAgentList()
{
    cout << "\tPRINTING ALL AGENTS:" << endl;
    for (Agent *agent : agentList)
    {
        agent->print();
        cout << endl;
    }
}

void League::printPlayersOfAgent(int agent_ID)
{
    if (findAgent(agent_ID) != nullptr)
    {
        findAgent(agent_ID)->printPlayerList();
    }
    else
        cout << "Agent of the given ID does not exist" << endl;
}

void League::printAll()
{
    cout << "\t PRINTING ALL DATA" << endl
         << endl;
    printAllClubs();
    cout << endl
         << endl;
    printPlayerList();
    cout << endl
         << endl;
    printAgentList();
    cout << endl
         << endl;
}