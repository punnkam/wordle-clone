#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;
enum color { grey, yellow, green };

vector<string> getWordVector(const char* path) {
    ifstream is(path);
    istream_iterator<string> start(is), end;
    vector<string> words(start, end);

    return words;
}

int getRandomNumber(const int from, const int to) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(from, to);

    return dist(rng);
}

color getLetterColor(const char letter, string wordle, const int index) {
    
    // int letterIndex = wordle.find(letter);
    size_t n = count(wordle.begin(), wordle.end(), letter);
    if(n) {
        if(wordle[index] == letter) {
            return green;
        } else {
            return yellow;
        }
    } else {
        return grey;
    }
}

bool checkIfValid(string word, vector<string> words) {
    return find(words.begin(), words.end(), word) != words.end();
}

int main() {

    vector<string> words = getWordVector("valid_words.txt");
    string wordle = words[getRandomNumber(0, words.size())];
    vector<char> correct;
    vector<char> current;

    for(int i=0; i<5; i++) 
        correct.push_back('*');

    for(int i=0; i<5; i++) 
        cout << "_ ";
    cout << endl;

    string word;
    cout << "wordle is " << wordle << endl;
    for(int i=0; i<6; i++) {

        // When there are no entries
        if(word.size()) {
            current.clear();

            // Reprocess the word.
            for(int j=0; j<5; j++) {
                switch (getLetterColor(word[j], wordle, j)) {
                    case grey: current.push_back('X'); break;
                    case yellow: current.push_back('/'); break;
                    case green: current.push_back('*'); break;
                }
            }

            // Print out the word again
            for(int k=0; k<current.size(); k++) {
                cout << current[k] << " ";
            }
            cout << endl;

            if(equal(current.begin(), current.begin()+5, correct.begin()))  {
                cout << "You found the wordle!!" << endl;
                return 0;
            }
            
        } 

       
        cout << "Enter a word: " << endl;
        cin >> word; 
        while(!checkIfValid(word, words) || word.size() != 5) {
            cout << "Not a word, enter a new word please" << endl;
            cout << "Enter a word: " << endl;
            cin >> word; 
        }
    }

    cout << "You failed to find the wordle!!" << endl;
    return 0;


}