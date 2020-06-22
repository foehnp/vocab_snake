About Vocab Snake

Vocab Snake lets you play "Snake" while practising vocabulary at the same time to reduce IQ loss associated with "Snake"!



Set-up:

1. Install the SFML graphics library as described here:
	https://www.sfml-dev.org/tutorials/2.5/start-linux.php

2. Type "make" in a terminal in the main directory of the game.



Run:

1. Type "./snake_game" in a terminal in the main directory of the game.



Rules of the Game:

Select a vocabulary list (see below on how to create one yourself) and speed (using cursor) and press "Let's go!" to start.

At the bottom of the window you see a bunch of words in language B. The letters of the corresponding words in language A are spread over the grid. Control the snake using the arrow keys and eat the the letters in the right order to spell a word in language A whose translation to language B is shown at the bottom of the window. After you've eaten such a word, the snake digests it and you get points.
Don't make the snake bite itself!
The game ends after all letters have been eaten or suicide.



Make your own vocabulary list:

Just make a csv file such that each line is a pair of a word in language A and its translation to language B, e.g.:

hello, Hallo
world, Welt
...

"hello and "world" are the words that the snake will have to eat, while "Hallo" and "Welt" will be shown at the bottom.
You can use Excel, LibreOffice Calc etc. to make CSV files more comfortably.

Save it in the "vocab" directory of the main directory

So far only ASCI words work!!!
