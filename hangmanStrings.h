#ifndef HANGMANSTRINGS_H_
#define HANGMANSTRINGS_H_

#include <string>
using std::string;

#define INTRO "Welcome to the exciting game of secret word\none player will enter a word\nand the other player will have to guess it one letter at a time"
#define READY "Are you ready to play"
#define GOODBYE_STR "Thank you for playing"
#define PLAY_AGAIN_STR 	"would you like to play again"
#define ENTER_WORD_STR 	"Tell me what the secret word will be:"
#define MAX_GUESSES_STR 	"How many guesses do you want the other player to have:"
#define GUESS_PROMPT "Enter Your Guess:"
#define ENTERED_BEFORE "You have entered this guess already"
#define NO_STR "something went wrong"
#define LONG_STR "Please keep it to one letter at a time"
#define NOT_ALPHA "That was not a letter"
#define STILL_WRONG "That letter is not in the word, keep trying"
#define GOOD_JOB "Good Job that letter was in the Secret Word"
#define TOO_LONG "The secret word cannot be that long"
#define NOT_IN_DICT "That was not a word, I searched the whole dictionary for it"
#define YOU_WIN "CONGRADULATIONS YOU WIN!!!!"
#define YOU_LOSE "You ran out of guesses without guessing the Secret Word"

#define WORD_REVEAL "\nFrom the Secret Word: "

//special display

#define LINE_SEPERATE "***************************************************************************"
#define SECRET_WORD_LABEL "*    SECRET WORD    * "
#define GUESS_MADE_LABEL "*   GUESSES MADE    * "
#define LETTERS_LABEL "* LETTERS AVAILABLE * "
#define GUESS_REMAINING_LABEL "* GUESSES REMAINING * "

#define LETTERS_UNREAVEALED_LABEL "*  LETTERS MISSING  * "
#define REVEAL_WORD_LABEL "*  SECRET WORD WAS  * "

#endif /* HANGMANSTRINGS_H_ */

/*
****|****|****|****|****|****|****|****|****|****|****|****|****|****|****| 75 WIDE
***************************************************************************
***************************************************************************
*    SECRET WORD    * - - - - - - - - - - - - - - -                       *
***************************************************************************
* LETTERS AVAILABLE * A B C D E F G H I J K L M N O P Q R S T U V W X Y Z *
***************************************************************************
*   GUESSES MADE    *                                                     *
***************************************************************************
* GUESSES REMAINING * ? ? ? ? ?                                           *
***************************************************************************
****         msg here                           ***************************
***************************************************************************
***************************************************************************
What is your guess:


***************************************************************************
***************************************************************************
*    SECRET WORD    * B - A N - O N S - A N S O N                         *
***************************************************************************
*  LETTERS MISSING  *   R     D       W                                   *
***************************************************************************
*   GUESSES MADE    * A B                       N O       S               *
***************************************************************************
*  SECRET WORD WAS  * BRANDONSWANSON                                      *
***************************************************************************
****         msg here                           ***************************
***************************************************************************
***************************************************************************

 */
