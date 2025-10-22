# Wordle
Game Wordle

Apart from normal Wordle Game, implemented the hard mode
where players are forced to use all information given by each guess:
1. Characters that are highlighted green in previous guesses must be used again in the same position in future guesses.
2. Characters that are yellow in the previous guess must be used again in a future guess, either turning green or remaining yellow. For simplicity, you only need to consider the yellow letters from the previous guess, instead of needing to track all possible yellow characters from all guesses.
3. Characters that were not yellow or green in previous guesses cannot be used again in future guesses
