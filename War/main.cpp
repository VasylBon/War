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


void moveToWinner(int& winner_score, vector<int>& winner, vector<int>& defeated, int part = 1, bool allCards = true)
{
    copy(winner.begin(), winner.begin() + (part * 3) + 1, back_inserter(winner));
    winner.erase(winner.begin(), winner.begin() + (part * 3) + 1);

    if (allCards)
    {
        copy(defeated.begin(), defeated.begin() + (part * 3) + 1, back_inserter(winner));
        defeated.erase(defeated.begin(), defeated.begin() + (part * 3) + 1);
    }
    else
    {
        copy(defeated.begin(), defeated.end(), back_inserter(winner));
        defeated.erase(defeated.begin(), defeated.end());
    }
    ++winner_score;
}

void war(int& p1_score, int& p2_score, vector<int>& p1, vector<int>& p2, int part = 1)
{
    int warScore = 0;
    int warScore2 = 0;

    for (int i = 1; i <= (part * 3) && !p1.empty() && !p2.empty(); ++i)
    {
        if (i > (p1.size() - 1))
        {
            moveToWinner(p2_score, p2, p1, part, false);
            return;
        }
        else if (i > (p2.size() - 1))
        {
            moveToWinner(p1_score, p1, p2, part, false);
            return;
        }
        else if (p1.at(i) == p2.at(i))
        {
            break;
        }

        (p1.at(i) > p2.at(i)) ? ++warScore : ++warScore2;
    }

    if (warScore > warScore2)
    {
        moveToWinner(p1_score, p1, p2, part);
    }
    else if (warScore < warScore2)
    {
        moveToWinner(p2_score, p2, p1, part);
    }
    else if (warScore == warScore2)
    {
        war(p1_score, p2_score, p1, p2, ++part);
    }
}


void battle(int& p1_score, int& p2_score, vector<int>& pc1, vector<int>& pc2)
{
    if (pc1.front() > pc2.front())
    {
        pc1.push_back(pc1.front());
        pc1.push_back(pc2.front());
        pc1.erase(pc1.begin());
        pc2.erase(pc2.begin());
        ++p1_score;
    }
    else if (pc1.front() < pc2.front())
    {
        pc2.push_back(pc2.front());
        pc2.push_back(pc1.front());
        pc1.erase(pc1.begin());
        pc2.erase(pc2.begin());
        ++p2_score;
    }
    else if (pc1.front() == pc2.front())
    {
        war(p1_score, p2_score, pc1, pc2);
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

        battle(p1_score, p2_score, pcards, pcards2);
    }

    if (p1_score == p2_score)
    {
        cout << "PAT" << endl;
    }
    else
    {
        cout << to_string(p1_score) + " " + to_string(p2_score) << endl;
    }

    return 0;
}