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
    vector<string> realWords = getWordVector("real_words.txt"); // "realistic" words taken from KleberPF on Github
    string wordle = realWords[getRandomNumber(0, realWords.size())]; // use "realistic" wordle
    vector<char> correct;
    vector<char> current;

    for(int i=0; i<5; i++) 
        correct.push_back('*');

    cout << endl;
    cout << "You have 6 attemps to guess the world" << endl;
    cout << endl;
    cout << "X - the letter does not exist" << endl;
    cout << "/ - the letter is in the incorrect position" << endl;
    cout << "* - the letter is in the correct position" << endl;

    cout << endl;
    for(int i=0; i<5; i++) 
        cout << "_ ";
    cout << endl;
    cout << endl;

    string word;
    // Reveal wordle for testing
    // cout << "wordle is " << wordle << endl; 
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

            for(int k=0; k<word.size(); k++) 
                cout << word[k] << " ";

            cout << endl;
            
            for(int k=0; k<current.size(); k++) 
                cout << current[k] << " ";
            
            cout << endl;
            cout << endl;

            if(equal(current.begin(), current.begin()+5, correct.begin()))  {
                cout << endl;
                cout << "You found the wordle!!" << endl;
                return 0;
            }
            
        } 

       
        cout << "#" << i+1 << " Enter a word: ";
        cin >> word; 
        cout << endl;
        while(!checkIfValid(word, words) || word.size() != 5) {
            cout << "Not a word, enter a new word please" << endl;
            cout << endl;
            cout << "#" << i+1 << " Enter a word: ";
            cin >> word; 
            cout << endl;
        }
    }

    cout << endl;
    cout << "You failed to find the wordle!!" << endl;
    cout << "The word was " << wordle << endl;
    return 0;


}