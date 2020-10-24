/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Drew Remmenga

    last modified: 3/7/2019
*/

#include "hangman.h"
#include <cstring>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

// constructor
hangman::hangman() 
{ 
    ifstream myfile ("dictionary.txt");
    if (!myfile.is_open())
    {
        cout << "Could not open file" << endl;
    }
    while (!myfile.eof())
    {
        string buff;
        getline(myfile, buff);
        _dictionary.push_back(buff);
    }
    
}


// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int num_guesses, bool see_words, int word_length) 
{
    num_guesses_remaining = num_guesses;
    for (int i = 0; i < _dictionary.size(); i++)
    {
        if (_dictionary[i].length() == word_length)
        {
            current_dictionary.push_back(_dictionary[i]);
        }
    }
    see_words = see_words;
    currentword = "";
    for (int i = 0; i < word_length; i++)
    {
        currentword += ('-');
    }
    guessed_characters = "";

}


void hangman::display_current_dictionary(bool see_words)
{
    if (see_words)
    {
        cout << "Words in current dictionary: " << current_dictionary.size();
    }
    
}

// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {
    num_guesses_remaining--;
    int words_with_c =0;
    for (int i = 0; i < current_dictionary.size(); i++)
    {
        string word = current_dictionary[i];
        for (int j = 0; j < word.length(); j++)
        {
            if (c == word[j])
            {
                words_with_c++;
                break;
            }
        }
    }
    int words_without_c = current_dictionary.size() - words_with_c;
    if (words_without_c > words_with_c)

    {
        for (int i = 0; i < current_dictionary.size(); i++)
        {
            string word = current_dictionary[i];
            for (int j = 0; j < word.length(); j++)
            {
                if (c == word[j])
                {
                    current_dictionary[i].erase();
                }
            }
        }

        return false;
    }
    else
    {
        for (int i = 0; i < current_dictionary.size(); i++)
        {
            if (current_dictionary[i].find(c) == std::string::npos)
            {
                current_dictionary[i].erase();
            }
        }
        map< int, int> m1;
        for (int i = 0; i < current_dictionary.size(); i++)
        {
            m1[current_dictionary[i].find(c)] += 1;
        }
        int _words_with_c = -1;
        int position = -1;
        for (int i = 0; i < current_dictionary[1].length(); i++)
        {
            if (m1[i] > _words_with_c)
            {
                _words_with_c = m1[i];
                position = i;
            }
        }
        currentword[position] = c;
        return true;
    }
    
}

void hangman::addguesstobank(char c)
{
    guessed_characters += c;
}


// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {

    return this->currentword;
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return this->num_guesses_remaining;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {
    sort(guessed_characters.begin(), guessed_characters.end());
    return guessed_characters;
}


// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    if (guessed_characters.find(c) == string::npos) 
    {
        return false;
    }
    else
    {
        return true;
    }
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    if (currentword == current_dictionary[0])
    {
        return true;
    }
    else
    {
        return false;
    }
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() 
{
    if (num_guesses_remaining == 0)
    {
        return true;
    }
    else
    {
        return  false;
    }
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    string word;
    word = current_dictionary[0];
    return word;
}


