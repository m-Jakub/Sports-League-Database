#include "declarations.h"
#include <iostream>

using namespace std;

Player::Player(string name, int ID)
    : Person(name, ID), pClub(nullptr), pAgent(nullptr), value(0)
{
}

Player::~Player() = default;

void Player::assignClub(SportsClub *club)
{
    pClub = club;
}

void Player::assignAgent(Agent *agent)
{
    pAgent = agent;
}

int Player::getValue() const
{
    return value;
}

bool Player::changeValue(int newValue)
{
    if (newValue >= 0)
    {
        value = newValue;
        return true;
    }
    return false;
}

string Player::getClubName() const
{
    if (pClub != nullptr)
        return pClub->getName();
    else
        return "no current club";
}

int Player::getAgentID() const
{
    if (pAgent != nullptr)
        return pAgent->getID();
    else
        return 0;
}

bool Player::hasClub()
{
    if (pClub == nullptr)
        return false;
    return true;
}

void Player::printNameIDandValue()
{
    cout << getFullName() << " (ID: " << getID() << ", value: " << value << ")" << endl;
}

void Player::print()
{
    Person::print();
    cout << "Value: " << value << endl;
    cout << "Current club: " << getClubName() << endl;
    if (pAgent == nullptr)
        cout << "Agent: no agent" << endl;
    else
        cout << "Agent: " << pAgent->getFullName() << " (ID: " << pAgent->getID() << ")" << endl;
}