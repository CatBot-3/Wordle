#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string RESET = "\033[0m";
const int MAX_GUESSES = 6;
const int WORD_LENGTH = 6;

//check if word exists in words.txt
bool word_valid_check (string word) {
    string s;
    ifstream ifs{"words.txt"};
    while (getline(ifs, s)) {
        if (s == word) {
            return true;
        }
    }
    return false;
}

//return the coded coloring of guess 
string coloring (string guess, string secret_word) {
    string color = "RRRRRR"; //default： all in reset color
    string secret_word_copy = secret_word;
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == secret_word[i]) {
            color[i] = 'G'; //green
            secret_word_copy[i] = '*'; //mark as used
        }
    }
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (color[i] == 'R') { //not green, test for yellow
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (guess[i] == secret_word_copy[j]) {
                    color[i] = 'Y'; //yellow
                    secret_word_copy[j] = '*'; //mark as used
                    break;
                }
            }
        }
    }
    return color;
}

//print guess with colors
void print_colored_guess (string guess, string color) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (color[i] == 'G') {
            cout << GREEN << guess[i] << RESET;
        } else if (color[i] == 'Y') {
            cout << YELLOW << guess[i] << RESET;
        } else {
            cout << guess[i];
        }
    }
    cout << endl;
}

void easymode (string secret_word) {
    int num_guesses = 1;
    string current_guess = "";
    cout << "Welcome to Wordle: (Easy mode)" << endl;

    while (num_guesses <= MAX_GUESSES) {
        cout << "Guess (" << num_guesses << "/" << MAX_GUESSES << "): ";
        if (getline(cin, current_guess)) {   // get one guess
            if (num_guesses > MAX_GUESSES) {
                cout << "You lost, the word was " << secret_word << endl;
                return;
            }
            if (current_guess.length() != WORD_LENGTH) {    // check length of guess
                cerr << "Error: Guess must be length 6" << endl;
                continue;
            }
            if (!word_valid_check(current_guess)) {   // check guess's validity if len = 6
                cerr << "Error: Guess is not a valid word" << endl;
                continue;
            }
            if (current_guess == secret_word) { //win?
                cout << "Congratulations, you won in " << num_guesses <<  " guesses" << endl;
                return;
            }
            string color = coloring(current_guess, secret_word);
            print_colored_guess(current_guess, color);
            num_guesses++;

        } else { // no more input
            cout << endl;
            cout << "You lost, the word was " << secret_word << endl;
            return;
        }
    }
    // out of guesses, l
    cout << "You lost, the word was " << secret_word << endl;
    return;
};

void hardmode (string secret_word) {
    int num_guesses = 1;
    string current_guess = "", previous_color = "", previous_guess = "";
    cout << "Welcome to Wordle: (Hard mode)" << endl;

    while (num_guesses <= MAX_GUESSES) {
        cout << "Guess (" << num_guesses << "/" << MAX_GUESSES << "): ";
        if (getline(cin, current_guess)) {  // get one guess
            if (num_guesses > MAX_GUESSES) {
                cout << "You lost, the word was " << secret_word << endl;
                return;
            }
            if (current_guess.length() != WORD_LENGTH) {    // check length of guess
                cerr << "Error: Guess must be length 6" << endl;
                continue;
            }
            if (!word_valid_check(current_guess)) {   // check guess's validity if len = 6
                cerr << "Error: Guess is not a valid word" << endl;
                continue;
            }
            if (current_guess == secret_word) { //win?
                cout << "Congratulations, you won in " << num_guesses <<  " guesses" << endl;
                return;
            }
            if (num_guesses == 1) { // first guess, no restriction
                string color = coloring(current_guess, secret_word);
                print_colored_guess(current_guess, color);
                previous_color = color;
                previous_guess = current_guess;
                num_guesses++;
                continue;
            }
            if (num_guesses > 1) { // check for hard mode from second guess
                // check green letters
                bool hardmode_violation = false;
                for (int i = 0; i < WORD_LENGTH; ++i) {
                    if (previous_color[i] == 'G' && current_guess[i] != previous_guess[i]) {
                        hardmode_violation = true;
                        break;
                    }
                }
                if (hardmode_violation) {
                    cerr << "Error: Your guess is not valid for hard mode" << endl;
                    continue;
                }
                // if no violation so far, check yellow letters
                // check yellow letters
                for (int i = 0; i < WORD_LENGTH; ++i) {
                    if (previous_color[i] == 'Y') {
                        bool found = false;  // there exists a yellow letter
                        for (int j = 0; j < WORD_LENGTH; ++j) {
                            if (previous_guess[i] == current_guess[j] && previous_color[j] != 'G') {
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            hardmode_violation = true;
                            break;
                        }
                    }
                }
                if (hardmode_violation) {
                    cerr << "Error: Your guess is not valid for hard mode" << endl;
                    continue;
                }
                // check for R letters
                for (int i = 0; i < WORD_LENGTH; ++i) {
                    if (previous_color[i] == 'R') {
                        bool found = false;  // there exists a R letter
                        for (int j = 0; j < WORD_LENGTH; ++j) {
                            if (previous_guess[i] == current_guess[j]) {
                                found = true;
                                break;
                            }
                        }
                        if (found) {
                            hardmode_violation = true;
                            break;
                        }
                    }
                }
                if (hardmode_violation) {
                    cerr << "Error: Your guess is not valid for hard mode" << endl;
                    continue;
                }
                // if no violation, print colored guess and update previous guess and color
                string color = coloring(current_guess, secret_word);
                print_colored_guess(current_guess, color);
                previous_color = color;
                previous_guess = current_guess;
                num_guesses++;
                continue;
            }
        } else { // no more input
            cout << endl;
            cout << "You lost, the word was " << secret_word << endl;
            return;
        }
    }
}

int main (int argc, char *argv[]) {
    int gamemode = 0 ; // default gamemode is 0

    if (argc != 2 && argc != 3) {   // check number of arguments
        cerr << "Error: No secret word provided!" << endl;
        return 1;
    }
    string secret_word = argv[1];
    if (secret_word.length() != 6) {    // check length of secret word
        cerr << "Error: Secret word is not length 6" << endl;
        return 2;
    }
    if (argc == 3) {    // check gamemode if provided
        char first_char_of_arg2 = argv[2][0];
        string arg2 = argv[2];
        if (!(first_char_of_arg2 >= '0' && first_char_of_arg2 <= '9')) {
            cerr << "Error: mode must be an integer" << endl;
          return 3;
       }
       if (arg2.length() != 1) {
           cerr << "Error: mode must be 0 or 1" << endl;
           return 4;
       }
       if (first_char_of_arg2 == '0') {
           gamemode = 0;
       } else if (first_char_of_arg2 == '1') {
           gamemode = 1;
       } else {
           cerr << "Error: mode must be 0 or 1" << endl;
           return 4;
       }
    }
    if (!word_valid_check(secret_word)) {   // check secret word's validity
        cerr << "Error: Secret word is not in words.txt" << endl;
        return 5;
    }

    if (gamemode == 0) {
        easymode(secret_word);
    } else {
        hardmode(secret_word);
    }
}

