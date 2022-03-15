#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <iterator>

using namespace std;

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

int main() {

    vector<string> words = getWordVector("valid_words.txt");
    string wordle = words[getRandomNumber(0, words.size())];

    // string word;
    // cout << "Enter a word: " << endl;
    // cin >> word;
}