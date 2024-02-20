#include "declarations.h"
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    system("cls"); // clearing the console for better view

    League *league = new League(10);

    cout << "=====1=====" << endl; // indicator printed in the code to be able to easily find currently checked sitation
    // Reading from the file and printing all data

    assert(league->inputDataFromFile() == true); // program uses assert to end the program, if unwanted behaviour occurs

    league->printAll();

    cout << endl;

    cout << "=====2=====" << endl;
    // Transactions between clubs

    // The two clubs before the transactions:
    league->printClubPlayerList("FC Barcelona");
    cout << endl;
    league->printClubPlayerList("Manchester City");
    cout << endl;

    assert(league->buyPlayer("FC Barcelona", 679857) == true);    // correct purchase
    assert(league->buyPlayer("Manchester City", 452190) == true); // correct purchase
    assert(league->buyPlayer("Manchester City", -452190) == false);
    /* incorrect ID, logical statement changed to ... == false,
     we want to see if the program gives an error message, and if continues it's work*/

    // Clubs after transactions (to see if players changed their clubs):
    league->printClubPlayerList("FC Barcelona");
    cout << endl;
    league->printClubPlayerList("Manchester City");
    cout << endl;

    cout << "=====3=====" << endl;
    // Removing a club

    assert(league->removeClub("FC Barcelona") == true); // correct removal

    // Trying to print again the club's player list, to see if it was removed
    league->printClubPlayerList("FC Barcelona");
    cout << endl;

    // Trying to change the budget to see if the club was removed
    assert(league->changeBudget("FC Barcelona", 330000000) == false);

    cout << "=====4=====" << endl;
    // Creating clubs

    // Trying to add a club of a name, that already exists
    assert(league->addClub("Manchester City") == false);
    assert(league->addClub("Legia Warszawa") == true); // correct creation
    // Trying to add 11th club when the capacity is 10
    assert(league->addClub("Atletico Madrid") == false);

    assert(league->changeMonthlyIncome("Legia Warszawa", 7000000) == true); // correct change
    // Trying to change value to a negative value
    assert(league->changeBudget("Legia Warszawa", -300000) == false);

    cout << "=====5=====" << endl;
    // Creating players
    // Correct creation, equating to the returned ID
    assert(league->addPlayer("Jan Kowalski", 46376) == 46376);
    // Correct creation, but without giving the ID and with the already existing name
    assert(league->addPlayer("Jan Kowalski") == 1);
    // Player is created not with the given ID, which is already taken, but with first unique ID using ID_counter
    assert(league->addPlayer("Jan Kowalski", 46376) == 2);

    cout << "=====6=====" << endl;
    // Assigning players to clubs

    assert(league->changeSalary(2, 50000) == true); // correct change

    assert(league->assignPlayer("Legia Warszawa", 46376) == true); // correct assignment
    assert(league->assignPlayer("Legia Warszawa", 1) == true);     // correct assignment
    // trying to assign player which club cannot afford to pay salary (salary_at_disposal < salary)
    assert(league->assignPlayer("Legia Warszawa", 2) == false);

    // Displaying the club player list to see if they are added
    league->printClubPlayerList("Legia Warszawa");
    league->printByID(1);

    cout << "=====7=====" << endl;
    // Trying to buy player club cannot afford to
    assert(league->buyPlayer("Legia Warszawa", 452190) == false);

    cout << "=====8=====" << endl;
    // Paying money

    // Trying to pay monthly income to the non exixsting club
    assert(league->payMonthlyIncome("Non existing club") == false);

    // Printing all clubs data before the payment
    league->printAllClubs();
    // Paying all club incomes
    league->payAllClubIncomes();
    // Printing after the payment
    league->printAllClubs();

    delete league;
    cout << "End of tests" << endl;
}
