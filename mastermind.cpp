/* Mastermind -
 * The game created in C++.
 * Jake Gendreau
 * Section 01
 * Started 8/30/23 @ 10:40 AM
 * Finished 8/30/23 @ 7:04 PM
 * 
 * I made this in python several years ago.
 * We will see how it translates into C++
 * 
 * Update: solving for the white pins was a pain but it's done
 */


//Import libraries
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

//Define prototypes
string makesolution();
int cleaninput(string guess);

int main(){
    //Welcome message
    cout << "Welcome to Mastermind in C++!\n\nRules:\n1) White pin indicates right letter, wrong placement.\n2) Black pin indicates right letter, right placement.\n3) You get 10 guesses, each formatted as a series of 4 letters.\n\nCreated by Jake Gendreau\n" << endl;
    //Define vars
    string solution(makesolution().c_str());
    solution[4] = '\0';
    string guess;

    //Take the user's 10 guesses
    for(int i=0;i<10;i++){

        // Define rules
                // Get user input
        cout << i+1 << "/10 " << "Make your guess (4 characters, a,b,c,d,e,f): ";
        cin >> guess;
        int isValid = cleaninput(guess);

        //Clean user input
        while(isValid == 0){
            cout << "Invalid guess. Guess again: ";
            cin >> guess;
            for(int i=0; i<4; i++){
                guess[i] = tolower(guess[i]);
            }
            isValid = cleaninput(guess);
        }

        //Calculate black pins
        int black = 0;
        for(int i=0;i<4;i++){
            if(guess[i] == solution[i])
                black++;
        }
        cout << "Black pins: " << black << endl;

        //Calculate white pins
        int white = 0;
        string tmpsol = solution;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(guess[i] == tmpsol[j]){
                    white++;
                    tmpsol[j] = 'j';
                    i++;
                    j = -1;    
                }
            }
        }
        white -= black;
        cout << "White pins: " << white << endl;    

        //win detection
        if(black == 4){
            cout << "You won with " << i+1 << " guesses! The solution was " << solution.c_str() << endl;
            return 1;   
        }
    }

    //loss detection
    cout << "You ran out of guesses. The solution was " << solution << endl;

}

string makesolution(){

    //Make the solution
    string solution = "";
    srand(time(0));

    //Choose random numbers
    for(int i=0; i<4; i++){
        int tmp = rand() % 6;
        if(tmp == 0)
            solution[i] = 'a';
        if(tmp == 1)
            solution[i] = 'b';
        if(tmp == 2)
            solution[i] = 'c';
        if(tmp == 3)
            solution[i] = 'd';
        if(tmp == 4)
            solution[i] = 'e';
        if(tmp == 5)
            solution[i] = 'f';
    }
    return solution;
}

int cleaninput(string guess){

    //Verify answer is 4 chars
    if(strlen(guess.c_str()) != 4)
        return 0;

    //Verify answer uses correct characters
    for(int i=0; i<4; i++){
        if(guess[i] != 'a' && guess[i] != 'b' && guess[i] != 'c' && guess[i] != 'd' && guess[i] != 'e' && guess[i] !='f'){
            return 0;
        }
    }

    //Return 1 if it input passes all the tests
    return 1;
}