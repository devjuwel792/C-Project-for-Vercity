# IQ Quiz Application Documentation

## Overview
This C program implements an IQ quiz application with user authentication, multiple difficulty levels, timed quizzes, result storage, and leaderboard display. The application allows users to sign up or log in, select a quiz level (Easy, Medium, Hard), answer 10 randomized questions within a 60-second time limit, and view their results along with a leaderboard of top scorers.

## Features
- **User Authentication**: Sign up and log in functionality with username and password stored in `users.txt`.
- **Multiple Difficulty Levels**: Easy, Medium, and Hard question pools with 15 questions each.
- **Randomized Questions**: Selects 10 random questions from the chosen pool for each quiz.
- **Timed Quiz**: Overall time limit of 60 seconds; quiz ends if time expires.
- **Result Storage**: Saves quiz results to `iq_results.txt` with name, level, score, time, and date.
- **Leaderboard**: Displays top 10 scorers sorted by score (descending) and time (ascending).
- **Feedback Messages**: Provides encouraging messages based on score.
- **Cross-Platform Compatibility**: Uses standard C libraries; runs on Windows (with `system("pause")`).

## Requirements
- C Compiler (e.g., GCC)
- Standard C libraries: `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<time.h>`, `<ctype.h>`
- Files: `users.txt` (for user credentials), `iq_results.txt` (for quiz results)

## Data Structures

### Question Struct
```c
typedef struct {
    char question[256];      // The question text
    char options[4][100];    // Four answer options (A, B, C, D)
    int correct;             // Index of correct option (0-3)
} Question;
```
Represents a single quiz question with its options and correct answer.

### Result Struct
```c
typedef struct {
    char name[50];           // User's name
    char level[10];          // Quiz level (Easy/Medium/Hard)
    int score;               // Score out of 10
    double time;             // Time taken in seconds
} Result;
```
Stores the result of a quiz attempt.

## Functions

### getImprovingMessage(int score)
- **Purpose**: Returns an encouraging message based on the quiz score.
- **Parameters**: `score` - Integer score (0-10).
- **Return**: Const char pointer to the message string.
- **Logic**: Categorizes score into ranges and returns appropriate feedback.

### selectRandomQuestions(Question pool[], Question selected[])
- **Purpose**: Randomly selects 10 questions from a pool of 15.
- **Parameters**:
  - `pool[]` - Array of 15 Question structs.
  - `selected[]` - Array to store 10 selected questions.
- **Return**: Void.
- **Logic**: Shuffles indices using Fisher-Yates algorithm and copies selected questions.

### loadResults(Result results[])
- **Purpose**: Loads quiz results from `iq_results.txt`.
- **Parameters**: `results[]` - Array to store loaded results (up to 100).
- **Return**: Integer count of loaded results.
- **Logic**: Reads file line by line, parses using `sscanf`, and populates the array.

### compareResults(const void *a, const void *b)
- **Purpose**: Comparison function for sorting results (used with `qsort`).
- **Parameters**: Two void pointers to Result structs.
- **Return**: Integer (-1, 0, 1) for sorting order.
- **Logic**: Sorts by score descending, then by time ascending.

### displayTopScorers(Result results[], int count, char *currentName)
- **Purpose**: Displays the top 10 scorers in a formatted table.
- **Parameters**:
  - `results[]` - Array of results.
  - `count` - Number of results.
  - `currentName` - Current user's name to mark their score.
- **Return**: Void.
- **Logic**: Sorts results, prints table with rank, name, level, score, time, and marks current user's entry.

### sign_up(char *username, char *password)
- **Purpose**: Registers a new user.
- **Parameters**:
  - `username` - String for username.
  - `password` - String for password.
- **Return**: Integer (1 for success, 0 for failure).
- **Logic**: Checks if username exists in `users.txt`; if not, appends username and password.

### log_in(char *username, char *password)
- **Purpose**: Authenticates an existing user.
- **Parameters**:
  - `username` - String for username.
  - `password` - String for password.
- **Return**: Integer (1 for success, 0 for failure).
- **Logic**: Reads `users.txt` and matches username and password.

### main()
- **Purpose**: Entry point of the program; handles authentication, quiz logic, and result display.
- **Logic**:
  - Seeds random number generator.
  - Prompts for sign up or log in (up to 3 attempts).
  - Prompts for quiz level and selects questions.
  - Runs timed quiz loop, checks answers, calculates score.
  - Saves and displays results, shows leaderboard.
  - Uses `system("pause")` to prevent immediate exit.

## How to Run
1. Compile the program: `gcc test.c -o test`
2. Run the executable: `./test` (on Linux/Mac) or `test.exe` (on Windows).
3. Follow on-screen prompts for authentication and quiz.

## File Descriptions
- **test.c**: Main source code file.
- **users.txt**: Stores user credentials (username password per line).
- **iq_results.txt**: Stores quiz results in CSV-like format.
- **document.md**: This documentation file.

## Notes
- Question pools are hardcoded; can be expanded by modifying the arrays.
- Time limits are enforced using `time.h` functions.
- Input validation is basic; assumes correct formats.
- Leaderboard shows up to 10 entries; sorted by score and time.
- Program uses `goto` for early quiz termination on time out.

## Future Improvements
- Add per-question time limits.
- Implement more secure password storage (e.g., hashing).
- Allow dynamic question loading from files.
- Add GUI interface.
- Improve input validation and error handling.
