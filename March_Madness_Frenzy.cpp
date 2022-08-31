/*--------------------------------------------
    Program 5: March Madness Frenzy
    The objective of this program is to analyze a dataset
    from the NCAA Basketball Tournaments (aka March Madness)
    and providing information regarding that data in multiple different ways.

    Course: CS 141, Spring 2022
    System: VS Code
    Author: Anis Yahya
 ---------------------------------------------*/

#include <iostream> // For input and output
#include <vector>   // For vectors
#include <fstream>  // For file input and output
#include <cassert>  // For the assert statement used to validate file open
#include <sstream>  // For stringstream
#include <cctype>   // For toupper/tolower
#include <cstdlib>  // For abs

using namespace std;

void welcomeMessage(string &fileName) // Function to output the welcome message and take in user selected file name.
{
    cout << "Program 5: March Madness Frenzy\n"
            "CS 141, Spring 2022, UIC\n"
            "\nThis program reads in data from NCAA Basketball Tournaments (aka \n"
            "March Madness). It provides overall information regarding the data, allows you to \n"
            "see the path taken to the championship, uses rankings of teams to determine \n"
            "which region is expected to win at a given round and to find the best underdog \n"
            "team, and calculates point differences within the games. You can also compare \n"
            "the actual brackets to your own predictions!\n"
            "\nEnter the name of the file with the data for the NCAA tournament: \n";
    cin >> fileName;
}

void menuOptionMessage(int &menuOption) // Funtion to output message for menu options and take in user input for menu option.
{
    cout << "\nSelect a menu option: \n"
            "   1. Display overall information about the data\n"
            "   2. Display the path of the winning team to the championship\n"
            "   3. Determine which region is expected to win the championship based on a given round\n"
            "   4. Identify the best underdog within a given round\n"
            "   5. Find the shoo-in and nail-biting games within a given round, or overall\n"
            "   6. Compare the actual brackets to your predicted brackets\n"
            "   7. Exit\n"
            "Your choice --> \n";
    cin >> menuOption;
}

class marchMadness // Main class used to seperate each individual data from the database.
{
private: // All variables in the csv file are set to private.
    string region, team1, team2, winningTeam;
    int rank1, rank2, score1, score2, roundNumber, gameNumber;

public:
    // Setter functions
    void setRegion(string region) { this->region = region; }
    void setTeam1(string team1) { this->team1 = team1; }
    void setTeam2(string team2) { this->team2 = team2; }
    void setWinningTeam(string winningTeam) { this->winningTeam = winningTeam; }
    void setRank1(int rank1) { this->rank1 = rank1; }
    void setRank2(int rank2) { this->rank2 = rank2; }
    void setScore1(int score1) { this->score1 = score1; }
    void setScore2(int score2) { this->score2 = score2; }
    void setRoundNumber(int roundNumber) { this->roundNumber = roundNumber; }
    void setGameNumber(int gameNumber) { this->gameNumber = gameNumber; }

    // Getter functions
    string getRegion() const { return region; }
    string getTeam1() const { return team1; }
    string getTeam2() const { return team2; }
    string getWinningTeam() const { return winningTeam; }
    int getRank1() const { return rank1; }
    int getRank2() const { return rank2; }
    int getScore1() const { return score1; }
    int getScore2() const { return score2; }
    int getRoundNumber() const { return roundNumber; }
    int getGameNumber() const { return gameNumber; }
};

// Function used to read in csv file and assign the appropriate variables to its correct positions.
void readInFile(vector<marchMadness> &marchMadnessList, string marchMadnessFile)
{
    marchMadness marchMadnessLine; // Creates an object
    string endLine;
    marchMadnessList.clear();      // Clears the parameter just in case it is full from before
    ifstream file;                 // Declare an input stream for reading
    file.open(marchMadnessFile);   // Opens file
    assert(file.fail() == false);  // Ensures file opens correctly
    getline(file, endLine);        // Gets the first row before looping through since first row is not needed.
    while (getline(file, endLine)) // While loop that repeats until no more values can be read
    {
        stringstream copyString(endLine);
        string secondaryString = "";
        getline(copyString, secondaryString, ','); // Runs until ',' is found and stores that value into the specified variable
        marchMadnessLine.setRegion(secondaryString);
        getline(copyString, secondaryString, ',');
        marchMadnessLine.setRank1(stoi(secondaryString));
        getline(copyString, secondaryString, ',');
        marchMadnessLine.setTeam1(secondaryString);
        getline(copyString, secondaryString, ',');
        secondaryString != "" ? marchMadnessLine.setScore1(stoi(secondaryString)) : marchMadnessLine.setScore1(0); // Sets value to 0 if empty.
        getline(copyString, secondaryString, ',');
        marchMadnessLine.setRank2(stoi(secondaryString));
        getline(copyString, secondaryString, ',');
        marchMadnessLine.setTeam2(secondaryString);
        getline(copyString, secondaryString, ',');
        secondaryString != "" ? marchMadnessLine.setScore2(stoi(secondaryString)) : marchMadnessLine.setScore2(0); // Uses stoi to convert number string to int type
        getline(copyString, secondaryString, ',');
        marchMadnessLine.setWinningTeam(secondaryString);
        getline(copyString, secondaryString, ',');
        marchMadnessLine.setRoundNumber(stoi(secondaryString));
        getline(copyString, secondaryString, ',');
        marchMadnessLine.setGameNumber(stoi(secondaryString));
        marchMadnessList.push_back(marchMadnessLine); // Pushes back the whole thing into the vector
    }

    file.close(); // Closes the file
}

class menuOption1Class // Extra class used specifically for menu option 1
{
private:
    string region;
    string team;

public:
    // Setters
    void setRegion(string region) { this->region = region; }
    void setTeam(string team) { this->team = team; }
    // Getters
    string getRegion() const { return region; }
    string getTeam() const { return team; }
};

class menuOption3Class // Extra class used specifically for menu option 3
{
private:
    string region;
    int totalRank;

public:
    // Setters
    void setRegion(string region) { this->region = region; }
    void setTotalRank(int totalRank) { this->totalRank = totalRank; }
    // Getters
    string getRegion() const { return region; }
    int getTotalRank() const { return totalRank; }
};

// This function is for menu option 1. It uses the class for menu option 1 to find the final 4 teams in order.
void menuOption1(vector<marchMadness> marchMadnessList, menuOption1Class objFor1, vector<menuOption1Class> vecFor1, vector<string> finalFourTeams)
{
    for (int i = 3; i < marchMadnessList.size(); i++) // Loops through starting at 3 so that the championship and final 4 regions are neglected
    {
        bool checkForRepeat = false; // Bool variables checks if there is already the same region in the vector

        for (int j = 0; j < vecFor1.size(); j++) // Loops through the vector of regions
        {

            if (marchMadnessList[i].getRegion() == vecFor1[j].getRegion()) // If there is already a certain region, bool will be true.
            {
                checkForRepeat = true;
            }
        }

        if (checkForRepeat == false) // Only runs if there is no repeated region.
        {
            objFor1.setRegion(marchMadnessList[i].getRegion());
            vecFor1.push_back(objFor1); // Pushes back each unique regions in order.
        }
    }
    for (int i = 1; i <= 2; i++) // Runs through only the final four
    {
        if (marchMadnessList[i].getRegion() == "Final Four")
        {
            finalFourTeams.push_back(marchMadnessList[i].getTeam1()); // Gets all final four teams
            finalFourTeams.push_back(marchMadnessList[i].getTeam2());
        }
    }

    for (int i = 0; i < vecFor1.size(); i++)
    {
        for (int j = 0; j < marchMadnessList.size(); j++)
        { // This statement checks to find each time in order with respect to their region that are in the final four
            if (vecFor1[i].getRegion() == marchMadnessList[j].getRegion() && (marchMadnessList[j].getTeam1() == finalFourTeams[0] ||
                marchMadnessList[j].getTeam1() == finalFourTeams[1] || marchMadnessList[j].getTeam1() == finalFourTeams[2] ||
                marchMadnessList[j].getTeam1() == finalFourTeams[3]))
            {
                vecFor1[i].setTeam(marchMadnessList[j].getTeam1()); // After finding one, it sets it in the vector
            }
            // This statement checks to find each time in order with respect to their region that are in the final four with respect to the getTeam2 variable
            if (vecFor1[i].getRegion() == marchMadnessList[j].getRegion() && (marchMadnessList[j].getTeam2() == finalFourTeams[0] ||
                marchMadnessList[j].getTeam2() == finalFourTeams[1] || marchMadnessList[j].getTeam2() == finalFourTeams[2] ||
                marchMadnessList[j].getTeam2() == finalFourTeams[3]))
            {
                vecFor1[i].setTeam(marchMadnessList[j].getTeam2()); // After finding one, it sets it in the vector
            }
        }
    }
    // Printing out all regions and teams.
    cout << "\nThe Final Four contestants are: \n"
         << "        " << vecFor1[0].getRegion() << " region: " << vecFor1[0].getTeam() << endl
         << "        " << vecFor1[1].getRegion() << " region: " << vecFor1[1].getTeam() << endl
         << "        " << vecFor1[2].getRegion() << " region: " << vecFor1[2].getTeam() << endl
         << "        " << vecFor1[3].getRegion() << " region: " << vecFor1[3].getTeam() << endl;
}
// This function is used exclusively for menu option 2. It has a winner and counter parameter to keep track
void menuOption2(vector<marchMadness> marchMadnessList, string winner, int counter)
{
    for (int i = marchMadnessList.size(); i >= 0; i--) // Loops backwards so that it is in order
    {
        if ((marchMadnessList[i].getTeam1() == winner && marchMadnessList[i].getRoundNumber() == counter) ||
            (marchMadnessList[i].getTeam2() == winner && marchMadnessList[i].getRoundNumber() == counter))
        {
            cout << "Round " << counter << ", Game " << marchMadnessList[i].getGameNumber() << ": " 
            << marchMadnessList[i].getTeam1() << " vs " << marchMadnessList[i].getTeam2() << ". Winner: "
            << winner << endl; // Prints out each game
            counter++; // Increments counter to get every game in order
        }
    }
}
// This function is for menu option 3 and if the round selected is the final four. The parameters are used to keep track of winning team
void menuOption3P1(vector<marchMadness> marchMadnessList, int winningRank, string winningTeam, string winningRegion)
{
    for (int i = 1; i <= 2; i++) // Runs only through the final four teams
    {
        // If statements find the lowest rank/winning rank
        if (marchMadnessList[i].getRank1() < winningRank)
        {
            winningRank = marchMadnessList[i].getRank1();
            winningTeam = marchMadnessList[i].getTeam1();
        }
        if (marchMadnessList[i].getRank2() < winningRank)
        {
            winningRank = marchMadnessList[i].getRank2();
            winningTeam = marchMadnessList[i].getTeam2();
        }
    }
    for (int i = 3; i < marchMadnessList.size(); i++)
    {
        // Finds the winning region based on the rank
        if (marchMadnessList[i].getTeam1() == winningTeam)
        {
            winningRegion = marchMadnessList[i].getRegion();
            break;
        }
        else if (marchMadnessList[i].getTeam2() == winningTeam)
        {
            winningRegion = marchMadnessList[i].getRegion();
            break;
        }
    }
    cout << "\nThe region expected to win is: " << winningRegion << endl; // Prints out the region found thats expected to win
}
// This function is for menu option 3 and if the round selected is 2-4. The parameters are used to keep track of winning team
void menuOption3P2(vector<marchMadness> marchMadnessList, int userOption3, vector<menuOption3Class> vecFor3, menuOption3Class objFor3)
{
    for (int i = 0; i < marchMadnessList.size(); i++)
    {
        bool checkForRepeat = false; // Bool var used to keep track of repeats

        if (marchMadnessList[i].getRoundNumber() == userOption3)
        {

            for (int j = 0; j < vecFor3.size(); j++)
            {
                // If a region is found that is repeated in the temp vector, bool will be true
                if (marchMadnessList[i].getRegion() == vecFor3[j].getRegion())
                {
                    checkForRepeat = true;
                }
            }

            if (checkForRepeat == false) // Adds all unique regions to vector and sets the total rank temporarily to 0
            {
                objFor3.setRegion(marchMadnessList[i].getRegion());
                objFor3.setTotalRank(0);
                vecFor3.push_back(objFor3);
            }
        }
    }

    for (int i = 0; i < vecFor3.size(); i++)
    {
        for (int j = 0; j < marchMadnessList.size(); j++)
        {
            if (vecFor3[i].getRegion() == marchMadnessList[j].getRegion() &&
                marchMadnessList[j].getRoundNumber() == userOption3)
            {
                if (marchMadnessList[j].getWinningTeam() == marchMadnessList[j].getTeam1())
                {
                    // Sets the rank to its appropriate number looping through original vector and using if statements to make sure it is in the correct line
                    vecFor3[i].setTotalRank(vecFor3[i].getTotalRank() + marchMadnessList[j].getRank1());
                }
                else if (marchMadnessList[j].getWinningTeam() == marchMadnessList[j].getTeam2())
                {
                    // Sets the rank to its appropriate number looping through original vector and using if statements to make sure it is in the correct line
                    vecFor3[i].setTotalRank(vecFor3[i].getTotalRank() + marchMadnessList[j].getRank2());
                }
            }
        }
    }

    string expectedWinner = vecFor3[0].getRegion();
    int lowestRank = vecFor3[0].getTotalRank();
    for (int i = 0; i < vecFor3.size(); i++)
    {
        if (vecFor3[i].getTotalRank() < lowestRank) // Finds the lowest rank in the temp vector.
        {
            expectedWinner = vecFor3[i].getRegion(); // Sets it to the var expectedWinner
            lowestRank = vecFor3[i].getTotalRank();
        }
    }

    cout << "\nThe region expected to win is: " << expectedWinner << endl; // Prints out the winner region
}
// Function used exclusively for menu option 4. Parameters are used to keep track of underdog team.
void menuOption4(vector<marchMadness> marchMadnessList, int userOption4, int highestRank, string underdogTeam)
{
    for (int i = 0; i < marchMadnessList.size(); i++)
    {
        if (marchMadnessList[i].getRoundNumber() == userOption4) // Only goes through if the round number given is correct
        {
            if (marchMadnessList[i].getRank1() > highestRank) // Checks both ranks to find the highest one.
            {
                highestRank = marchMadnessList[i].getRank1(); // If rank found is higher than the previous highest found, it will set the parameters to the appropriate underdog
                underdogTeam = marchMadnessList[i].getTeam1();
            }
            if (marchMadnessList[i].getRank2() > highestRank)
            {
                highestRank = marchMadnessList[i].getRank2();
                underdogTeam = marchMadnessList[i].getTeam2();
            }
        }
    }
    cout << "The best underdog team is " << underdogTeam << " which has rank " << highestRank << ".\n"; // After finding the underdog, it will print it out
}
// Function used exclusively for menu option 5 when user selects to analyze the overall tournamnent. Many parameters are needed to print all information needed by the shooinGame and nailbitingGame
void menuOption5P1(vector<marchMadness> marchMadnessList, int scoreForShooInGame, int gameForShooInGame,
                   int roundForShooInGame, string team1ForShooInGame, string team2ForShooInGame, string winnerForShooInGame, int scoreForNailBitingGame,
                   int gameForNailBitingGame, int roundForNailBitingGame, string team1ForNailBitingGame, string team2ForNailBitingGame, string winnerForNailBitingGame)
{
    cout << "\nAnalyzing the overall tournament...\n";
    for (int i = 0; i < marchMadnessList.size(); i++)
    {
        if (abs(marchMadnessList[i].getScore1() - marchMadnessList[i].getScore2()) > scoreForShooInGame) // Checks each game's difference of score and sees if it is greater then the already found highest score.
        {
            // If yes, it sets all these variables to the specific info needed for that game.
            scoreForShooInGame = abs(marchMadnessList[i].getScore1() - marchMadnessList[i].getScore2());
            roundForShooInGame = marchMadnessList[i].getRoundNumber();
            gameForShooInGame = marchMadnessList[i].getGameNumber();
            team1ForShooInGame = marchMadnessList[i].getTeam1();
            team2ForShooInGame = marchMadnessList[i].getTeam2();
            winnerForShooInGame = marchMadnessList[i].getWinningTeam();
        }

        if (abs(marchMadnessList[i].getScore1() - marchMadnessList[i].getScore2()) < scoreForNailBitingGame) // Checks each game's difference of score and sees if it is less than then the already found lowest score.
        {
            // If yes, it sets all these variables to the specific info needed for that game.
            scoreForNailBitingGame = abs(marchMadnessList[i].getScore1() - marchMadnessList[i].getScore2());
            roundForNailBitingGame = marchMadnessList[i].getRoundNumber();
            gameForNailBitingGame = marchMadnessList[i].getGameNumber();
            team1ForNailBitingGame = marchMadnessList[i].getTeam1();
            team2ForNailBitingGame = marchMadnessList[i].getTeam2();
            winnerForNailBitingGame = marchMadnessList[i].getWinningTeam();
        }
    }
    cout << "\nThe shoo-in game was: \n" // Then uses the parameters to print out the information needed for the shooin and nail biting games
            "Round "
         << roundForShooInGame << ", Game " << gameForShooInGame << ": " << team1ForShooInGame << " vs "
         << team2ForShooInGame << ". Winner: " << winnerForShooInGame << "\nThe difference was " << scoreForShooInGame << " points.\n";

    cout << "\nThe nail-biting game was: \n"
            "Round "
         << roundForNailBitingGame << ", Game " << gameForNailBitingGame << ": " << team1ForNailBitingGame << " vs "
         << team2ForNailBitingGame << ". Winner: " << winnerForNailBitingGame << "\nThe difference was " << scoreForNailBitingGame << " points.\n";
}
// Function used exclusively for menu option 5 rounds 1-6. Many parameters are needed to print all information needed by the shooinGame and nailbitingGame
void menuOption5P2(vector<marchMadness> marchMadnessList, int userOption5, int scoreForShooInGame, int gameForShooInGame,
                   int roundForShooInGame, string team1ForShooInGame, string team2ForShooInGame, string winnerForShooInGame, int scoreForNailBitingGame,
                   int gameForNailBitingGame, int roundForNailBitingGame, string team1ForNailBitingGame, string team2ForNailBitingGame, string winnerForNailBitingGame)
{
    for (int i = 0; i < marchMadnessList.size(); i++)
    {
        if (marchMadnessList[i].getRoundNumber() == userOption5) // Only goes through if the user round number given is in the data.
        {
            if (abs(marchMadnessList[i].getScore1() - marchMadnessList[i].getScore2()) > scoreForShooInGame) // Checks each game's difference of score and sees if it is greater then the already found highest score.
            {
                // If yes, it sets all these variables to the specific info needed for that game.
                scoreForShooInGame = abs(marchMadnessList[i].getScore1() - marchMadnessList[i].getScore2());
                roundForShooInGame = marchMadnessList[i].getRoundNumber();
                gameForShooInGame = marchMadnessList[i].getGameNumber();
                team1ForShooInGame = marchMadnessList[i].getTeam1();
                team2ForShooInGame = marchMadnessList[i].getTeam2();
                winnerForShooInGame = marchMadnessList[i].getWinningTeam();
            }

            if (abs(marchMadnessList[i].getScore1() - marchMadnessList[i].getScore2()) < scoreForNailBitingGame) // Checks each game's difference of score and sees if it is less than then the already found lowest score.
            {
                // If yes, it sets all these variables to the specific info needed for that game.
                scoreForNailBitingGame = abs(marchMadnessList[i].getScore1() - marchMadnessList[i].getScore2());
                roundForNailBitingGame = marchMadnessList[i].getRoundNumber();
                gameForNailBitingGame = marchMadnessList[i].getGameNumber();
                team1ForNailBitingGame = marchMadnessList[i].getTeam1();
                team2ForNailBitingGame = marchMadnessList[i].getTeam2();
                winnerForNailBitingGame = marchMadnessList[i].getWinningTeam();
            }
        }
    }
    cout << "\nThe shoo-in game was: \n" // Then uses the parameters to print out the information needed for the shooin and nail biting games
            "Round "
         << roundForShooInGame << ", Game " << gameForShooInGame << ": " << team1ForShooInGame << " vs "
         << team2ForShooInGame << ". Winner: " << winnerForShooInGame << "\nThe difference was " << scoreForShooInGame << " points.\n";

    cout << "\nThe nail-biting game was: \n"
            "Round "
         << roundForNailBitingGame << ", Game " << gameForNailBitingGame << ": " << team1ForNailBitingGame << " vs "
         << team2ForNailBitingGame << ". Winner: " << winnerForNailBitingGame << "\nThe difference was " << scoreForNailBitingGame << " points.\n";
}
// Function used exclusively for menu option 6. Creates another vector for predictions and uses parameters to keep track of score and amount games predicted
void menuOption6(vector<marchMadness> marchMadnessList, vector<marchMadness> option6Vec, int gamesPredicted, int score)
{
    for (int i = 0; i < marchMadnessList.size(); i++)
    {
        if (marchMadnessList[i].getWinningTeam() == option6Vec[i].getWinningTeam()) // Compares the two vectors winning team variable and determines if prediction is correct
        {
            // If correct, amount of games predicted adds by 1 and the score increments based on the round number * 5
            gamesPredicted += 1;
            score += (marchMadnessList[i].getRoundNumber() * 5);
        }
    }
    cout << "You correctly predicted the winner for " << gamesPredicted << " games.\n"
            "This means that you have a score of " << score << ".\n"; // Prints out total score when done.
    if (score >= 250) // If the score is above 250, you win!
    {
        cout << "Great job! You could consider entering your predictions to win money!\n";
    }
    else // If not, you lose:(
    {
        cout << "You may want to learn more about basketball to improve your predictions next year.\n";
    }
}
int main() // Start of main
{
    int menuOption;
    string fileName;
    welcomeMessage(fileName);               // Prints out welcome message
    vector<marchMadness> marchMadnessList;  // Vector object to read in the file
    readInFile(marchMadnessList, fileName); // Calls vector to read in file
    while (true)
    {
        menuOptionMessage(menuOption); // Calls function to portray menu options and gets user input
        if (menuOption == 7)
        {
            cout << "\nExiting program..."; // Exits if menu option is 7
            break;
        }
        else if (menuOption == 1) // For menu option 1
        {
            cout << "Total number of games played in tournament: " << marchMadnessList.size(); // Uses size() to get total games
            // Creates temp objects using the menuOption1Class to keep track of the correct order of regions
            vector<menuOption1Class> vecFor1;
            menuOption1Class objFor1;
            vector<string> finalFourTeams;
            vecFor1.clear(); // Clears the vectors just in case they are full from other attempts
            finalFourTeams.clear();
            menuOption1(marchMadnessList, objFor1, vecFor1, finalFourTeams); // Calls the menuOption1 function
        }

        else if (menuOption == 2) // For menu option 2
        {
            cout << "Path to the championship: \n";
            string winner = marchMadnessList[0].getWinningTeam(); // Gives the winner variable to first line winner as a default
            int counter = 1;                                      // Counter default is 1
            menuOption2(marchMadnessList, winner, counter);       // Calls the menu option 2 function
        }

        else if (menuOption == 3) // If menu option is 3
        {
            int userOption3; // Tells user to select a certain round
            cout << "Enter a round to be evaluated: \n"
                    "   Select 2 for round 2\n"
                    "   Select 3 for round 3 'Sweet 16'\n"
                    "   Select 4 for round 4 'Elite 8'\n"
                    "   Select 5 for round 5 'Final 4'\n"
                    "Your choice --> ";
            cin >> userOption3;
            cout << "\nAnalyzing round " << userOption3 << "...\n";

            if (userOption3 == 5) // If round is in final four
            {
                // Gives default values to variables
                string winningTeam = marchMadnessList[0].getTeam1();
                int winningRank = marchMadnessList[0].getRank1();
                string winningRegion = "";
                menuOption3P1(marchMadnessList, winningRank, winningTeam, winningRegion); // Calls the menuOption3P1 function
            }
            else // If round is not the final four round
            {
                // Creates temp objects to keep track
                vector<menuOption3Class> vecFor3;
                menuOption3Class objFor3;
                vecFor3.clear();                                                // Clears the vector just in case
                menuOption3P2(marchMadnessList, userOption3, vecFor3, objFor3); // Calls the menuOption3P2 function
            }
        }

        else if (menuOption == 4) // If menu option is 4
        {
            int userOption4; // Allows the user to select certain round
            cout << "Enter a round to be evaluated: \n"
                    "   Select 2 for round 2\n"
                    "   Select 3 for round 3 'Sweet 16'\n"
                    "   Select 4 for round 4 'Elite 8'\n"
                    "   Select 5 for round 5 'Final 4'\n"
                    "   Select 6 for round 6 'Championship'\n"
                    "Your choice --> ";
            cin >> userOption4;
            // Default value for the variables
            int highestRank = 1;
            string underdogTeam = marchMadnessList[0].getTeam1();
            menuOption4(marchMadnessList, userOption4, highestRank, underdogTeam); // Calls the menuOption4 function
        }

        else if (menuOption == 5) // For menu option 5
        {
            int userOption5; // Allows the user to select a round
            cout << "Enter a round to be evaluated: \n"
                    "   Select 1 for round 1\n"
                    "   Select 2 for round 2\n"
                    "   Select 3 for round 3 'Sweet 16'\n"
                    "   Select 4 for round 4 'Elite 8'\n"
                    "   Select 5 for round 5 'Final 4'\n"
                    "   Select 6 for round 6 'Championship'\n"
                    "   Select 7 for the overall tournament\n"
                    "Your choice --> ";
            cin >> userOption5;

            // Gives all these variables default values so that they can be compared to when run in the loop
            int scoreForShooInGame = 0;
            int gameForShooInGame = marchMadnessList[0].getGameNumber();
            int roundForShooInGame = marchMadnessList[0].getRoundNumber();
            string team1ForShooInGame = marchMadnessList[0].getTeam1();
            string team2ForShooInGame = marchMadnessList[0].getTeam2();
            string winnerForShooInGame = marchMadnessList[0].getWinningTeam();

            int scoreForNailBitingGame = 200;
            int gameForNailBitingGame = marchMadnessList[0].getGameNumber();
            int roundForNailBitingGame = marchMadnessList[0].getRoundNumber();
            string team1ForNailBitingGame = marchMadnessList[0].getTeam1();
            string team2ForNailBitingGame = marchMadnessList[0].getTeam2();
            string winnerForNailBitingGame = marchMadnessList[0].getWinningTeam();

            if (userOption5 == 7) // If user wants to analyze the whole tournament
            {
                // Calls the menuOption5P1 function
                menuOption5P1(marchMadnessList, scoreForShooInGame, gameForShooInGame,
                              roundForShooInGame, team1ForShooInGame, team2ForShooInGame, winnerForShooInGame, scoreForNailBitingGame,
                              gameForNailBitingGame, roundForNailBitingGame, team1ForNailBitingGame, team2ForNailBitingGame, winnerForNailBitingGame);
            }

            else // If a specific round is analyzed
            {
                cout << "\nAnalyzing round " << userOption5 << "...\n";
                // Calls the menuOption5P2 function
                menuOption5P2(marchMadnessList, userOption5, scoreForShooInGame, gameForShooInGame,
                              roundForShooInGame, team1ForShooInGame, team2ForShooInGame, winnerForShooInGame, scoreForNailBitingGame,
                              gameForNailBitingGame, roundForNailBitingGame, team1ForNailBitingGame, team2ForNailBitingGame, winnerForNailBitingGame);
            }
        }

        else if (menuOption == 6) // If menu option is 6
        {
            vector<marchMadness> option6Vec;
            string option6FileName;
            cout << "Enter the name of the file with your predicted brackets: \n";
            cin >> option6FileName;                  // Gets predicted file name
            readInFile(option6Vec, option6FileName); // Reads in predicted files into vector.
            int score = 0;                           // Default variables
            int gamesPredicted = 0;
            menuOption6(marchMadnessList, option6Vec, gamesPredicted, score); // Calls the menuOption6 function
        }

        else // If incorrect menu option is given
        {
            cout << "\nInvalid value.  Please re-enter a value from the menu options below.\n";
        }
    }

    return 0;
    //Thanks!
}