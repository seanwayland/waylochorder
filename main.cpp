#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

int main() {
    using namespace std;
    int numChords;

    vector<vector<int> > chords; // array to store chord arrays

    int numNotes;
    int note;
    vector<int> chord;
    // DISPLAY MIDI NOTE NUMBERS
    cout << "Waylo Chorder Utility" << endl;
    cout << endl;
    cout << "MIDI NOTE NUMBERS : 60 is MIDDLE C !" << endl;
    cout << endl;
    cout << "     C# 25      D# 27           F#30     G# 32      A# 34" << endl;
    cout << "C0 24 	    D 26       E 28 F 29      G 31      A 33       B 35" << endl;
    cout << endl;
    cout << "     C# 37      D# 39           F# 42    G# 44      A# 46" << endl;
    cout << "C1 36      D 38       E 40 F 41      G 43      A 45       B 47" << endl;
    cout << endl;
    cout << "     C# 49      D# 51           F# 54    G# 56      A# 58" << endl;
    cout << "C2 48      D 50       E 52 F 53      G 55      A 57       B 59" << endl;
    cout << " " << endl;
    cout << "     C# 61      D# 63           F# 66    G# 6       A# 70" << endl;
    cout << "C3 60      D 62       E 64 F 65      G 67      A 69       B 71" << endl;
    cout << endl;
    cout << "     C# 73      D# 75           F# 78    G#80       A#82" << endl;
    cout << "C4 72      D 74       E 76 F 77      G 79      A 81       B 83 " << endl;

    cout << "Enter number of chords!" << endl;
    cin >> numChords; // variable for number of notes in the chord
    cout << "You entered " << numChords << endl;


// store notes for each chord in array
    for (int i = 0; i < numChords; i++) {
        cout << "enter number of notes in chord " << i + 1 << endl;
        cin >> numNotes;
        for (int j = 0; j < numNotes; j++) {
            cout << " enter chord " << i + 1 << " note number " << j + 1 << endl;
            cin >> note;
            chord.push_back(note); // store this note in array for this chord
        }
        chords.push_back(chord); // store the created chord in the chord array
        chord.clear(); // clear the temp chord and set it to null so next chord can be entered
    }



    // print the array
    cout << endl << "you entered: " << endl;
    // print the results
    for (int i = 0; i < numChords; i++) {
        for (int j = 0; j < chords[i].size(); j++) {
            cout << chords[i][j] << ",";
        }
        cout << endl;
    }

    { //<--
        // store the array to a file
        std::ofstream ofs("dump.dat");
        boost::archive::text_oarchive oa(ofs);
        oa & chords;
    }

    chords.clear(); // clear the original array

    { // <--
        // restore the array from the file
        std::ifstream ifs("dump.dat");
        boost::archive::text_iarchive ia(ifs);
        ia & chords;
    }

    cout << endl << "you saved: " << endl;
    // print the restored array
    for (int i = 0; i < numChords; i++) {
        for (int j = 0; j < chords[i].size(); j++) {
            cout << chords[i][j] << ",";
        }
        cout << endl;
    }

    return 0;
}

