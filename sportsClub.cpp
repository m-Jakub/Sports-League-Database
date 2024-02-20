#include "declarations.h"
#include <iostream>
#include <algorithm> // for a.o. find function

using namespace std;

SportsClub::SportsClub(string name)
    : name(name), budget(0), monthly_income(0),
      number_of_players(0), salary_left_at_disposal(0), trophies(0)
{
}

SportsClub::~SportsClub()
{
}

string SportsClub::getName() const
{
    return name;
}

int SportsClub::getMonthlyIncome() const
{
    return monthly_income;
}

void SportsClub::payMonthlyIncome()
{
    budget = budget + monthly_income;
}

int SportsClub::getSalaryAtDisposal() const
{
    return salary_left_at_disposal;
}

int SportsClub::getTrophies() const
{
    return trophies;
}

long long SportsClub::getBudget() const
{
    return budget;
}

bool SportsClub::addPlayer(Player *player)
{
    if (playerList.size() == 99)
        return false;

    if (find(playerList.begin(), playerList.end(), player) != playerList.end())
    {
        cerr << "Player can't be added to the club, he or she is already on the list" << endl;
        return false;
    }

    if (player == nullptr)
    {
        cerr << "Warning: given pointer is a nullptr, employment unsuccesfull" << endl;
        return false;
    }

    if (salary_left_at_disposal < player->getSalary())
    {
        cerr << "Warning: Club can't afford paying salary for this player, employment unsuccesful " << endl;
        return false;
    }

    number_of_players++;
    salary_left_at_disposal -= player->getSalary();
    playerList.push_front(player);
    return true;
}

bool SportsClub::hirePlayer(Player *player)
{
    if (player == nullptr)
    {
        cerr << "Warning: The given pointer is nullptr and cannot be added to the list" << endl;
        return false;
    }

    if ((player->hasClub() == 1) && (budget < player->getValue()))
    {
        cerr << "Warning: Club cannot afford buying this player, transaction unsuccesful" << endl;
        return false;
    }

    if (addPlayer(player))
    {
        if (player->hasClub())
            budget -= player->getValue();
        return true;
    }
    return false;
}

bool SportsClub::freePlayer(Player *player)
{
    if (find(playerList.begin(), playerList.end(), player) == playerList.end())
        return false;

    playerList.remove(player);
    return true;
}

bool SportsClub::sellPlayer(Player *player)
{
    if (freePlayer(player)) // removes player and pays club the value if he or she is on the list
    {
        budget += player->getValue();
        return true;
    }
    return false;
}

void SportsClub::clearPlayerList()
{
    playerList.clear();
}

void SportsClub::clearPlayersPointers()
{
    for (Player *player : playerList)
        player->assignClub(nullptr);
}

bool SportsClub::changeMonthlyIncome(int new_income)
{
    if (new_income >= 0)
    {
        monthly_income = new_income;
        return true;
    }
    else
    {
        monthly_income = -new_income; // Assigning the positive value
        return true;
    }
    return false;
}

bool SportsClub::changeSalaryAtDisposal(int new_salary)
{
    if (new_salary >= 0)
    {
        salary_left_at_disposal = new_salary;
        return true;
    }
    else
    {
        salary_left_at_disposal = -new_salary; // Assigning the positive value
        return true;
    }
    return false;
}

bool SportsClub::changeTrophies(int new_trophies)
{
    if (new_trophies >= 0)
    {
        trophies = new_trophies;
        return true;
    }
    else
    {
        cerr << "Warning, number of trophies can't be lower than 0, change unsuccesful" << endl;
        return false;
    }
}

bool SportsClub::changeBudget(long long new_budget)
{
    if (new_budget >= 0)
    {
        budget = new_budget;
        return true;
    }
    else
    {
        cerr << "Warning, budget can't be lower than 0, change unsuccesful" << endl;
        return false;
    }
}

void SportsClub::printName()
{
    cout << getName() << endl;
}

void SportsClub::printNameAndTrophies()
{
    cout << getName() << "\t" << getTrophies() << endl;
}

void SportsClub::printPlayerList()
{
    cout << "\t" << name << " player list:" << endl;
    for (list<Player *>::iterator it = playerList.begin(); it != playerList.end(); it++)
        (*it)->printNameIDandValue();
}

void SportsClub::print()
{
    cout << "Name: " << name << endl;
    cout << "Number of players: " << number_of_players << endl;
    cout << "Monthly income: " << monthly_income << endl;
    cout << "Salary left at disposal: " << salary_left_at_disposal << endl;
    cout << "Trophies: " << trophies << endl;
    cout << "Budget: " << budget << endl;
}