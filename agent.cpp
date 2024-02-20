#include "declarations.h"
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

Agent::Agent(string name, int ID) : Person(name, ID)
{
}

Agent::~Agent() = default;

bool Agent::addPlayer(Player *player)
{
    if (playerList.size() == 5)
        return false;

    if (player != nullptr)
    {
        playerList.push_front(player);
        return true;
    }
    return false;
}

bool Agent::removePlayer(Player *player)
{
    if (find(playerList.begin(), playerList.end(), player) == playerList.end())
        return false;

    playerList.remove(player);
    return true;
}

void Agent::clearPlayersPointers()
{
    for (Player *player : playerList)
        player->assignAgent(nullptr);
}

void Agent::print()
{
    Person::print();
    printPlayerList();
}

void Agent::printPlayerList()
{
    cout << "\tList of employers of agent " << getFullName() << ":" << endl;
    for (list<Player *>::iterator it = playerList.begin(); it != playerList.end(); it++)
        (*it)->printNameAndID();
}