/*
---------------------------------------------------------------------------------------------------------------------------
Subject : CMPT 1010
Aurthor : Daniel Lee
Group: Kelsey Fourtin, Nick Crema
Last Update On: Dec 08 2015
Program description: This program is designed for a language game "Ubbi Dubbi".
                     In our simplified version of Ubbi dubbi, the cluster “ub” is added before every vowel in the word.
---------------------------------------------------------------------------------------------------------------------------
<Error handling>

Your program should be robust and display error messages for the user and
let user reenter information if they didn’t enter appropriate input.
For example, if the entered input file that doesn’t exist,
the user should be asked to reenter the name of the file.
If the file contains more than 100 words,
100 words should be read in and an error message displayed.
Also, display a warning message if the user is trying to write to a file,
but the array of words is empty.
---------------------------------------------------------------------------------------------------------------------------
<program requirements>

option 1: s/he is asked to input a word and then the word is translated to Ubbi dubbi and displayed.
option 2: s/he is asked to input a name of a file and the words from the file are read into an array of strings,
          one word per string.  You can assume that there will be at most 100 words in the file.
option 3: translate each word from the array of strings into Ubbi dubbi.
          The array of strings will then contain the translated words from the file.
option 4: write the content of the array of words to a file.
          The name of the file should be input from the user.
          Note that you might not have the same white space in your translated file as in the original file, which is OK.
          Also, it is not your responsibility to check if the user translated the words before writing them in the file.
---------------------------------------------------------------------------------------------------------------------------
*/

#include "iostream"
#include "cstring"
#include "fstream"
#include "cstdlib"
#include "cmath"

using namespace std;

/*Functions Initialization*/
void display_menu();
bool choice_valid(char);
bool is_a_vowel (char);

string translate_ubbi_dubbi(string);

void open_file(string[]); //option 2
void encode_file(string[]); //option 3
void write_to_file(string[]); //option 4

const int MAX_SIZE = 100;
const char QUIT = '0';
const char ENCODE_WORD = '1';
const char READ_FILE = '2';
const char ENCODE_FILE = '3';
const char WRITE_TO_A_FILE = '4';

int main()
{
    display_menu();

    return 0;
}
/*This function checks if the user's choice is valid
INPUT: A single character value from 0 to 4
OUTPUT: TURE(1) or FALSE(0)
*/
bool choice_valid(char ch)
{
   return (ch == QUIT || ch == READ_FILE || ch == ENCODE_FILE || ch == ENCODE_WORD || ch == WRITE_TO_A_FILE);
}
/*This function displays menu and gets the user's choice, then process following tasks
INPUT: An integer value from 0 to 4 entered by the user
OUTPUT: Display menu and the choice the user makes
*/
void display_menu()
{
    char choice; //used for the menu
    int count =0;
    string word; //used for option 1: encode word
    string words[MAX_SIZE];

do
{
    cout << "*****************************************" << endl;
    cout << "\tWelcome to Ubbi Dubbi Game!" << endl;
    cout << "*****************************************" << endl;
    cout << "Please select one of the following options." << endl;
    cout << endl;
    cout << "0 - Quit the Program" << endl;
    cout << "1 - Encode word" << endl;
    cout << "2 - Read file" << endl;
    cout << "3 - Encode file" << endl;
    cout << "4 - Write to a file" << endl;
    cout << endl;
    cout << "SELECT:";


    while(cin >> choice && !choice_valid(choice) ) //ask the user for an input, check if the input is valid, if no, asks for a new input
        cout << "SELECT:";

    switch(choice)
    {
        case QUIT:
            cout << "Closing the program . . ." << endl;
            break;

        case ENCODE_WORD:
            cout << "[1 - Encode word] was selected..." << endl;
            cout << "ENTER YOUR WORD (no space): "; // get a word from the user
            cin >> word;
            cout << translate_ubbi_dubbi(word);

            break;

        case READ_FILE:
            cout << "[2 - Read file] was selected..." << endl;
            open_file(words);
            break;

        case ENCODE_FILE:
            cout << "[3 - Encode file] was selected..." << endl;
            encode_file(words);
            break;

        case WRITE_TO_A_FILE:
            cout << "[4 - Write to a file] was selected..." << endl;
            write_to_file(words);
            break;
    }

    cout << endl;
    cout << endl;

}while(choice != QUIT);

}
/*------------------------------------FUNCTIONS FOR OPTION 1: ENCODE WORD-------------------------------*/
/* This function checks if the user's input has a vowel in it.
INPUT: A character
OUTPUT: TRUE(1) or FALSE(0)
*/
bool is_a_vowel (char input)
{
    return (input == 'a' || input == 'e' || input == 'i' || input == 'o' || input == 'u'||
            input == 'A' || input == 'E' || input == 'I' || input == 'O' || input == 'U');
}
/*This function translates a word entered by the user into ubbidubbi.
INPUT: The user's input stored as a string
OUTPUT: Display each character of a word with additions of the cluster "ub"before ever vowel in the word.
*/
string translate_ubbi_dubbi(string word)
{
    string translated;

    for (int i=0; i<word.length(); i++)
    {
        if ( is_a_vowel(word[i]) )
        {
            if (i != 0 )
                translated = word.insert(i, "ub");
            else // if the first letter of a word is a capital letter
                translated = word.insert(i, "Ub");
                i += 2;
        }
    }

    return translated;
}
/*----------------------------------------FUNCTIONS FOR OPTION 2 : READ FILE-----------------------------*/
/*This function opens the name of the file the user enters and stores each word into a string array.
INPUT: A string(file name)
OUTPUT: A string array
*/
void open_file(string word[])
{
    ifstream in_file;
    string f_name;
    int i=0;

    do
    {
        cout << "ENTER FILE NAME: ";
        cin >> f_name;

        in_file.open( f_name.c_str() );

        if ( in_file.fail() )
            cout << "Failed to open file" << endl;

    } while ( in_file.fail() ); // repeat until file is sucessfully opened

    cout << endl;
    cout << "File opened" << endl;
    cout << endl;
    cout << "CONTENT OF FILE: ";

    while ( !in_file.eof() && i <MAX_SIZE) // copy each word into a string array
    {
        in_file >> word[i];
        cout << word[i] << " "; //display words in the string array
        i++;
    }

    if (i > MAX_SIZE)
        cout << "The file contains more than 100 words!" << endl;
    else
        cout << "Completed !" << endl;

    in_file.close();
}
/*------------------------------------------FUNCTIONS FOR PART 3: ENCODE FILE---------------------------*/
/*This function gets the content of the file and translate each word into ubbi dubbi
INPUT: A string array
OUTPUT: A string array which has translated words
*/
void encode_file(string word[])
{
    cout << "TRANSLATED CONTENT OF FILE: ";

    for(int i = 0; i < MAX_SIZE; i++)
    {
        word[i] = translate_ubbi_dubbi(word[i]);
        cout << word[i] << " " ;
    }
}
/*-------------------------------FUNCTIONS FOR PART 4: WRITE TO FILE-----------------------*/
/*This function writes translated words from the file to a new file
INPUT: string array( contains translated words)
OUTPUT: translated content of the file
*/
void write_to_file(string word[])
{
    ofstream out_file;
    string f_name;

    do
    {
        cout << "ENTER FILE NAME: ";
        cin >> f_name;

        out_file.open( f_name.c_str() );

        if ( out_file.fail() )
            cout << "Failed to open file" << endl;

    } while ( out_file.fail() ); // repeat until file is sucessfully opened

    cout << endl;
    cout << "File opened" << endl;
    cout << endl;


    for (int i=0; i< MAX_SIZE; i++)
    {
        if ( word[i] == " " )
            cout << "Array empty";

        out_file << word[i] + " ";
    }

    cout << "Completed !" << endl;

    out_file.close();
}

