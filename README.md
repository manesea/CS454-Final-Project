
# DFA String Validator

This C++ program calculates the number of valid strings of a specified length accepted by a deterministic finite automaton (DFA). It performs checks to ensure that strings satisfy specific rules, such as including all required characters and maintaining valid states during transitions.

## Features

- Convert integers to string sequences (`intToString`) and vice versa (`stringToInt`).
- Check if a string contains all required characters (`hasAllChars`).
- Simulate DFA state transitions (`changeState`).
- Calculate the number of valid strings of a given length using memoization for efficiency (`validStrings`).

## Time Complexity

1. **`hasAllChars`**: **O(n * m)** where `n` is the length of the string being checked and `m` is the size of the subset (`abcd`, which is constant). Each character in the subset is checked against the string.

2. **`intToString`**: **O(k)** where `k` is the maximum sequence length (constant here, 5). String operations are constant for fixed alphabet sizes.

3. **`stringToInt`**: **O(k)** similar to `intToString`.

4. **`changeState`**: **O(k)** for the conversion operations and validations. Effective complexity is constant since `k` is bounded.

5. **`validStrings`**: **O(length * MAX)** where `length` is the string length and `MAX` is the number of states (1367). This is because memoization reduces redundant calculations.

## How to Run

1. Compile the code using:
   ```bash
   g++ -o dfa_validator dfa_validator.cpp -lgmpxx -lgmp
   ```

2. Run the program:
   ```bash
   ./dfa_validator
   ```

3. Follow the prompts to enter the string length or test pre-defined cases.


