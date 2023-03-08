#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int convertToNum(char card)
{
    switch (card)
    {
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case '1': return 10;
    case 'J': return 11;
    case 'Q': return 12;
    case 'K': return 13;
    case 'A': return 14;
    }
    return 0;
}


void moveToWinner(vector<int>& winner, vector<int>& defeated, int &numWar, bool allCards = true)
{
    copy(winner.begin(), winner.begin() + (numWar * 4) + 1, back_inserter(winner));
    winner.erase(winner.begin(), winner.begin() + (numWar * 4) + 1);

    if (allCards)
    {
        copy(defeated.begin(), defeated.begin() + (numWar * 4) + 1, back_inserter(winner));
        defeated.erase(defeated.begin(), defeated.begin() + (numWar * 4) + 1);
    }
    else
    {
        copy(defeated.begin(), defeated.end(), back_inserter(winner));
        defeated.erase(defeated.begin(), defeated.end());
    }
}


bool hasCards(vector<int>& pcards, int& numWar)
{
    return  ((numWar * 4) + 2) > pcards.size();
}


void battle(int& p1_score, int& p2_score, vector<int>& pc1, vector<int>& pc2, bool &isPAT, int numWar = 0)
{
    if (*(pc1.begin() + (numWar * 4)) > *(pc2.begin() + (numWar * 4)))
    {
        if (numWar > 0)
        {
            moveToWinner(pc1, pc2, numWar);
        }
        else
        {
            pc1.push_back(pc1.front());
            pc1.push_back(pc2.front());
            pc1.erase(pc1.begin());
            pc2.erase(pc2.begin());
        }
        ++p1_score;
       
    }
    else if (*(pc1.begin() + (numWar * 4)) < *(pc2.begin() + (numWar * 4)))
    {
        if (numWar > 0)
        {
            moveToWinner(pc2, pc1, numWar);
        }
        else
        {
            pc2.push_back(pc2.front());
            pc2.push_back(pc1.front());
            pc1.erase(pc1.begin());
            pc2.erase(pc2.begin());
        }
        ++p2_score;
    }
    else if (*(pc1.begin() + (numWar * 4)) == *(pc2.begin() + (numWar * 4)))
    {
        if (hasCards(pc1, numWar))
        {
            moveToWinner(pc2, pc1, numWar, false);
            isPAT = true;
            return;
        }
        else if (hasCards(pc2, numWar))
        {
            moveToWinner(pc1, pc2, numWar, false);
            isPAT = true;
            return;
        }
        else
        {
            battle(p1_score, p2_score, pc1, pc2, isPAT, ++numWar);
        }
    }
}


int main()
{
    cout << "Number cards player 1" << endl;
    int n; // the number of cards for player 1
    cin >> n; cin.ignore();
    vector<int> pcards;
    pcards.reserve(n * 2);

    for (int i = 0; i < n; i++) {
        cout << "Enter card #" << i << endl;
        string cardp_1; // the n cards of player 1
        cin >> cardp_1; cin.ignore();
        pcards.push_back(convertToNum(cardp_1[0]));
    }

    cout << "Number cards player 2" << endl;
    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
    vector<int> pcards2;
    pcards2.reserve(m * 2);

    for (int i = 0; i < m; i++) {
        cout << "Enter card #" << i << endl;
        string cardp_2; // the m cards of player 2
        cin >> cardp_2; cin.ignore();
        pcards2.push_back(convertToNum(cardp_2[0]));
    }
    cout << "Begin" << endl;
    // game process
    int p1_score = 0;
    int p2_score = 0;
    int round = 0;
    bool isPAT = false;

    while (!pcards.empty() && !pcards2.empty())
    {
        cout << "Player 1" << endl;
        for (auto el : pcards)
        {
            cout << el << " ";
        }
        cout << "\n\nPlayer 2" << endl;
        for (auto el : pcards2)
        {
            cout << el << " ";
        }
        cout << endl;

        ++round;
        battle(p1_score, p2_score, pcards, pcards2, isPAT);
    }

    if (isPAT)
    {
        cout << "PAT" << endl;
    }
    else
    {
        cout << (p1_score > p2_score ? "1 " : "2 ") + to_string(round) << endl;
    }

    return 0;
}