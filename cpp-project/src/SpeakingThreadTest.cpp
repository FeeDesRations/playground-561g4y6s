#include "Exercises/SpeakingThread.h"
#include "Exercises/MainUtil.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void Message(string channel, string msg) {
    stringstream ss(msg);
    string line;
    while (getline(ss, line, '\n')) {
        cout << "TECHIO> message --channel \"" << channel << "\" \"" << line << "\"" << endl;
    }
}

void Success(bool success) {
    cout << "TECHIO> success " << (success ? "true" : "false") << endl;
}

// check if a string exists in a text file
bool ExistsInFile(string str, string filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (line.find(str) != string::npos ) {
            return true;
        }
    }
    
    return false;
}

void AssertEquals(int expected, int found, string message) {
    if(expected != found) {
        ostringstream error;
        error << message << " Expected: " << expected << ", Found: " << found  << endl;
        throw logic_error(error.str());
    }
}

int main() {
    try
    {
        initThread();


        //AssertEquals(5, Universe::CountAllStars(galaxy1), "Running Universe::CountAllStars(2, 3)...");

        //AssertEquals(6, Universe::CountAllStars(galaxy2), "Running Universe::CountAllStars(9, -3)...");
        Success(true);



        /*
        if (ExistsInFile("accumulate", "src/Exercises/Universe.cpp")) {
            Message("My personal Yoda, you are. π", "* β ΒΈ .γΒΈ. :Β° βΎ Β° γΒΈ. β ΒΈ .γγΒΈ.γ:. β’ ");
            Message("My personal Yoda, you are. π", "           γβ Β°  β ΒΈ. ΒΈ γβγ :.γ .   ");
            Message("My personal Yoda, you are. π", "__.-._     Β° . .γγγγ.γβΎ Β° γ. *   ΒΈ .");
            Message("My personal Yoda, you are. π", "'-._\\7'      .γγΒ° βΎ  Β° γΒΈ.β  β .γγγ");
            Message("My personal Yoda, you are. π", " /'.-c    γ   * β  ΒΈ.γγΒ°     Β° γΒΈ.    ");
            Message("My personal Yoda, you are. π", " |  /T      γγΒ°     Β° γΒΈ.     ΒΈ .γγ  ");
            Message("My personal Yoda, you are. π", "_)_/LI");
        } else {
            Message("Kudos π", "Did you know that you can use the accumulate method to sum up a vector? Try it!");
            Message("Kudos π", " ");
            Message("Kudos π", "#include <numeric>");
            Message("Kudos π", " ");
            Message("Kudos π", "vector<int> galaxies {37, 3, 2};");
            Message("Kudos π", "int totalStars = accumulate(galaxies.begin(), galaxies.end(), 0); // 42");
        }
        */


    } catch (const exception& e)
    {
        Success(false);
        Message("Oops! π", e.what());
        Message("Hint π‘", "Did you properly made the thread discuss? π€");
    }

  return 0;
}
