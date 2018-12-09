#include <iostream>
#include <vector>

int main() {
    using namespace std;
    int numChords;
    int numNotes ;
    int note;
    vector<int> chord;
    // user enters total number of chords
    cout << "Enter number of chords!" << endl;
    cin >> numChords; // variable for number of notes in the chord
    cout << "You entered " << numChords << endl;
    vector< vector<int> > chords; // array to store chord arrays

    // store notes for each chord in array
    for (int i = 0 ; i < numChords; i ++){
        cout << "enter number of notes in chord " << i+1 << endl;
        cin >> numNotes;
        for ( int j = 0 ; j <numNotes; j++){
            cout << " enter chord " << i+1 << " note number " << j+1 << endl ;
            cin >> note;
            chord.push_back(note); // store this note in array for this chord
        }
        chords.push_back(chord); // store the created chord in the chord array
        chord.clear(); // clear the temp chord and set it to null so next chord can be entered
    }

    cout << endl << "you entered: " << endl ;
    // print the results
    for (int i = 0; i< numChords; i++) {
        for ( int j = 0; j < chords[i].size(); j++) {
            cout << chords[i][j] << "," ;
        }
        cout << endl ;
    }

    return 0;
}