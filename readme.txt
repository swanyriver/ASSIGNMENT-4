Hello TA/Proffesor/Classmates

RECURSION EXTRA CREDIT
see attached documents: RecusionReport.pdf and some picrtures in /DesignPics
(I tried endlesly to make a pdf of images, but they kept upscalling to a 100mb+ file, so they are submitted as a folder of .jpegs, my apologies)

Here are my submissions,  I understand that you have made a makefile to be used, so while I have 2 makefiles of my own in this folder they are not titled makefile.
they are PhraseMake and execMake
so make -f PhraseMake will play my guessing game
and make -f execMake will compile all 9 exercise components, as well as run them one after another

but im confident this will all compile with your provided make file
My code is very multi file based, but I have endeavored to move all included sources into .hpp (compining interface and implementaiton sadly)


About my game,
Command line arguments:
'-s'  =  simple mode, game will run without calls to system()
'-d'  -  DEBUG,  a readout of the secret phrase is incorporated into the display, for the purposes of observing recursive guess check algorithm


I wished to make a -help for my game but have come to the deadline, so I will explain some of the weirder parts of the rules:
-You are only allowed to guess words and letters that occur in the dictionary being used
-This means that if the maximum word lenght in the phrase is 6 letters, 7 letter guesses will be rejected
-If you guess a word, then other words in the phrase may still have those same letters hidden in it
-Then you are free to guess those letters, but if they are only in words you have already guessed, it is a guess deducted.


Please explore the dictionary sub-menu
Right now the game can be played with a dictionary pruned down to 6 letter words from 80,000 words
Or with words from Moby Dick
or from the TV show Friends
or from any text that you put in a .txt file and supply the filename to my program (via a menu and string input)
Please give this a try as it is very entertaining!
 