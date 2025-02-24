**Card_Service**

How to request data: 
Create something along the lines of: ofstream WriteServiceFile("service.txt");
- To request a certain number of decks to be made: WriteServiceFile << "numDecks: " << numDecks << endl;
- To request a card to be drawn: WriteServiceFile << "action: draw" << endl;
- To request to end the microservice: WriteServiceFile << "action: end" << endl;

How to receive data:
Create something along the lines of: ifstream ReadServiceFile("service.txt");
- string data;
- getline(ReadServiceFile, data);

If the decks' cutoff point has been reached, the microservice will print an alert. The main program can then choose to either 
request a new number of decks to be made or end the microservice.
