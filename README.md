# Poker Hand Evaluator

A robust command-line tool written in C that evaluates, ranks, and compares Texas Hold'em style poker hands. The program processes a list of 5-card hands, determines the exact poker rank of each (from High Card to Poker), resolves any tie-breakers, and outputs the row number of the absolute winning hand.

## Features
* **Comprehensive Ranking:** Accurately identifies all standard poker hands.
* **Deep Tie-Resolution:** Implements full kicker checking. For example, if two players have Two Pair, the program checks the highest pair, then the second pair, and finally the 5th "kicker" card.
* **Ace-Low Straight Support:** Correctly processes the "wheel" straight (A-2-3-4-5) by dynamically adjusting the Ace's value from 14 to 1 during sequence checks.
* **Dynamic Input Reading:** Robustly handles formatting and continues to read and compare hands until the End of File (EOF) is reached.

## How the Algorithm Works
1. **Data Parsing:** Reads the card values and suits, converting face cards (`T`, `J`, `Q`, `K`, `A`) into internal integer values (`10` to `14`).
2. **Sorting:** Cards in each hand are sorted in descending order by value, which simplifies sequence checking and tie-breaking.
3. **Evaluation (`get_rank`):** The program counts the number of unique card values and checks for flush and straight conditions. It assigns a base score from `1` (High Card) to `9` (Straight Flush).
4. **Comparison (`compare_hands`):** If the base scores match, the program compares the individual card values one by one until a winner is found based on standard poker rules.

---

## Input Data Formatm
To make the program robust and easy to use, data entry ignores all whitespace (spaces, tabs, and newlines). 

A single card is always represented by exactly **two characters**:
1. **Value:** `2`, `3`, `4`, `5`, `6`, `7`, `8`, `9`, `T` (Ten), `J` (Jack), `Q` (Queen), `K` (King), `A` (Ace).
2. **Suit:** Can be any distinct character (e.g., `H` for Hearts, `S` for Spades, `C` for Clubs, `D` for Diamonds).
## Compilation
gcc poker.c -o poker

A
