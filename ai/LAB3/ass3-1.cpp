#include <bits/stdc++.h>
using namespace std;

/*
Rule Table for Simple Reflex Vacuum Cleaner Agent

 Percept (Location, Status)    Action       
--------------------------------------
 (A, Dirty)                   Clear                      
 (A, Clean)                   Move Right                 
 (B, Dirty)                   Clear                      
 (B, Clean)                   Move Right                             
 (C, Dirty)                   Clear                     
 (C, Clean)                   Move Left                

- Total performance cost is calculated based on Clear=2, Move=1.
*/

int main() {
    vector<string> rooms(3); 
    char location = 'A';     
    int totalCost = 0;

    cout << "Vacuum Cleaner Simple Reflex Agent\n\n";

    
    cout << "Enter status of Room A, B, C : ";
    for (int i = 0; i < 3; i++) {
        cin >> rooms[i];
        
        if (rooms[i] != "Clean" && rooms[i] != "Dirty") {
            cout << "Wrong input of status. Please enter Clean or Dirty." << endl;
            return 0;
        }
    }

    
    for(int step = 0; step < 3; step++){
        int index = location - 'A';      
        string currentStatus = rooms[index]; 

        cout << "\nAgent at Room " << location
             << " | Status: " << currentStatus;

        
        if(currentStatus == "Dirty") {
            cout << " | Action: Clear";
            totalCost += 2;
            rooms[index] = "Clean"; 
        }

        if(location != 'C') {
            cout << " | Action: Move Right";
            totalCost += 1;
            if (location == 'A') location = 'B';
            else if (location == 'B') location = 'C';
        }
        
    }
    cout << "\n\n--- All Rooms Are Clean ---";
    cout << "Total Performance Cost: " << totalCost << endl;

    return 0;
}
