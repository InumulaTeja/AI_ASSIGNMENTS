#include <bits/stdc++.h>
using namespace std;

/*
Rule Table for Indian Railways Level Crossing Simple Reflex Agent

Percept (TrackSensors, ObstacleSensors, ManualInput)      Actions
---------------------------------------------------------------------
(Train Detected, No Obstacle, Neutral)                   Lower Gate, siren On, Signal Red
(Train Detected, Obstacle Detected, Neutral)             Lower Gate, siren On, Signal Red
(No Train, No Obstacle, Neutral)                         Raise Gate, siren Off, Signal Green
(No Train, Obstacle Detected, Neutral)                   Keep Gate Lowered, siren On, Signal Red
(Any, Any, Emergency Active)                             Lower Gate, siren On, Signal Red
- Priorities: Emergency Active >  Obstacle Detected > Train Detected
*/

int main() {
    string trackInbound, trackOutbound, obstacle, manualInput;
    
    cout << "Indian Railways Level Crossing Simple Reflex Agent\n\n";

    cout << "Enter Track Sensor Inbound (Train/NoTrain): ";
    cin >> trackInbound;
    cout << "Enter Track Sensor Outbound (Train/NoTrain): ";
    cin >> trackOutbound;
    cout << "Enter Obstacle Sensor (Clear/Obstacle): ";
    cin >> obstacle;
    cout << "Enter Manual Emergency Input (Neutral/Active): ";
    cin >> manualInput;

    if((trackInbound != "Train" && trackInbound != "NoTrain") ||
        (trackOutbound != "Train" && trackOutbound != "NoTrain") ||
        (obstacle != "Clear" && obstacle != "Obstacle") ||
        (manualInput != "Neutral" && manualInput != "Active")) {
        cout << "Wrong input! Please enter valid percepts." << endl;
        return 0;
    }


    if(manualInput == "Active"){
        cout << "Emergency Active! Lower Gate, siren On, Signal Red to train" << endl;
    }
    else if(obstacle == "Obstacle"){
        cout << "Obstacle Detected on Road! Keep Gate Lowered, siren On, Signal Red to train" << endl;
    }
    else if(trackInbound == "Train" || trackOutbound == "Train"){
        cout << "Train Detected! Lower Gate, siren On, Signal green to train" << endl;
    }
    else{
        cout << "No Train, Road Clear. Raise Gate, siren Off, Signal Green to level crossing" << endl;
    }
    return 0;
}
