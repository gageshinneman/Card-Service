#include <iostream>
#include <vector>   
#include <string> 
#include <fstream> 
#include <cmath> 
#include <utility>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

vector<string> populateDecks(int numDecks){
    vector<string> deck = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    //populates decks with numDecks iterations of deck
    vector<string> decks;
    for(int i = 0; i < numDecks*4; i++){
         for(int x = 0; x < deck.size(); x++){
            decks.push_back(deck[x]);
         }
    }
    return decks;
}

void pickCard(vector<string>& decks){
    //gets a random index, finds that card
    int index = rand() % decks.size(); 
    string randomCard = decks[index];

    //writes the card to the file
    ofstream WriteServiceFile("service.txt");
    WriteServiceFile << "cardDrawn: " << randomCard;
    WriteServiceFile.flush(); 
    WriteServiceFile.close();
    cout << "Your card is a " << randomCard << endl;
    cout << "deck size: " << decks.size() << endl;

    //removes the card from the deck
    decks.erase(decks.begin() + index); 
}

void checkSize(vector<string> decks, int deckLength){
    //checks to see if the amount of cards left in the deck is less than 80% of the deck's original length
    if(static_cast<double>(decks.size()) / static_cast<double>(deckLength) < 0.8){
        ofstream WriteServiceFile("service.txt");
        WriteServiceFile << "cutOffReached: true";
        WriteServiceFile.flush();
        WriteServiceFile.close();
        cout << "deck has reached 80%" << endl;
    }
}

int getNumDecks(){
    ifstream ReadServiceFile("service.txt");

    string numDecksStr;
    getline(ReadServiceFile, numDecksStr);
    if(numDecksStr == ""){
        return 0;
    }

    cout << "numDecksStr: " << numDecksStr << endl;

    size_t pos = numDecksStr.find("numDecks: "); //reads the string after "numDecks: ", extracts it, turns it into an int
    if (pos != string::npos) {
        numDecksStr = numDecksStr.substr(pos + 10);
    }

    int numDecks = stoi(numDecksStr); 
    ReadServiceFile.close();

    ofstream ClearServiceFile("service.txt", ios::trunc); //clears file line
    ClearServiceFile.close();

    return numDecks;
}

string getAction(){
    ifstream ReadServiceFile("service.txt");

    string action;
    getline(ReadServiceFile, action);

    size_t pos = action.find("action: "); //reads the string after "action: ", extracts it
    if (pos != string::npos) {
        action = action.substr(pos + 8);
        cout << "Action found" << endl;
        ReadServiceFile.close();

        ofstream ClearServiceFile("service.txt", ios::trunc); //clears file line
        ClearServiceFile.close();
    }
    
    return action;
}

int main(){
    srand(time(NULL));
    
    string response = "";
    while(response != "end"){ //repeats unless the response is end
        response = "";
        int numDecks = 0;
        
        while(numDecks == 0){ //continually checks for input
            numDecks = getNumDecks();
        }

        vector<string> decks = populateDecks(numDecks); //creates the decks
        int deckLength = numDecks * 52;

        //repeats unless the response is end or numDecks which means the program is requesting new decks
        while(response != "end" && response.find("numDecks: ") == string::npos){ 
            response = getAction(); //reads from the terminal to get the given action
            if(response == "draw"){
                pickCard(decks);
                checkSize(decks, deckLength); //checks to see if the cut off point has been met
            }
        }
    }
}