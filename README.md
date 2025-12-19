# IQ Quiz Application

## Overview
This is a console-based IQ Quiz application written in C. It provides an interactive quiz experience with user authentication, multiple difficulty levels, timed questions, scoring, and result tracking. The application is designed to test general knowledge and provide feedback based on performance.

## Features
- **User Authentication**: Sign up and log in functionality with username and password storage in `users.txt`.
- **Difficulty Levels**: Three levels - Easy, Medium, and Hard - each with a pool of 15 questions, from which 10 are randomly selected per quiz.

- **Randomized Questions**: Questions are shuffled each time to ensure variety.
- **Scoring and Feedback**: Tracks correct answers, calculates percentage, and provides encouraging messages based on score.
- **Result Storage**: Saves quiz results to `iq_results.txt` with name, level, score, time, and date.
- **Top Scorers Leaderboard**: Displays the top 10 scorers sorted by score (descending) and time (ascending).
- **Authentication Attempts**: Allows up to 3 login/signup attempts before exiting.

## Requirements
- C compiler (e.g., GCC)
- Standard C libraries: stdio.h, stdlib.h, string.h, time.h, ctype.h

## Setup and Installation
1. **Clone or Download**: Ensure all files are in the same directory: `test.c`, `users.txt`, `iq_results.txt`, etc.
2. **Compile the Program**:
   ```
   gcc test.c -o iq_quiz
   ```
   On Windows, you can use MinGW or similar.
3. **Run the Program**:
   ```
   ./iq_quiz
   ```
   Or on Windows: `iq_quiz.exe`

## Usage
1. **Authentication**:
   - Choose to Sign Up (create a new account) or Log In (existing account).
   - Enter username and password.
   - Up to 3 attempts allowed.

2. **Level Selection**:
   - Choose Easy, Medium, or Hard.
   - Invalid input defaults to Easy.

3. **Quiz**:
   - Answer 10 multiple-choice questions (A/B/C/D).
   - Each question has a 30-second timer (not enforced in code, but recommended).
   - Total quiz time is tracked.

4. **Results**:
   - View your score, percentage, time taken, and feedback message.
   - See the top scorers leaderboard.

## File Structure
- `test.c`: Main source code containing all logic.
- `users.txt`: Stores user credentials (username password).
- `iq_results.txt`: Stores quiz results in CSV-like format.
- `text.txt`: Feature requirements list (for reference).
- `TODO.md`: Development progress tracker.
- `test.exe`: Compiled executable (generated after compilation).

## Sample Output
```
Choose an option:
1. Sign Up
2. Log In
Enter choice (1 or 2): 2
Enter username: juwel
Enter password: 123
Login successful!

Select level (Easy/Medium/Hard): Easy
Quiz starts now! You have 15 minutes total. Each question has 30 seconds.

Question 1: What is 2 + 2?
A. 3
B. 4
C. 5
D. 6
Your answer (A/B/C/D): B
Correct!

... (more questions)

--- Results ---
Name: juwel
Level: Easy
Score: 8/10 (80.00% accuracy)
Time Taken: 120 seconds
Message: Great job! You're improving steadily.

--- Top Scorers ---
Rank | Name          | Level   | Score | Time (s)
-----|---------------|---------|-------|---------
1    | juwel         | Easy    | 10/10 | 69.0
2    | robiul        | Medium  | 6/10  | 383.0
...
```

## Known Issues and TODO
- Time limits are not strictly enforced (questions don't auto-timeout).
- Level input is case-sensitive in some parts (fixed in code).
- Expand question pools for more variety.
- Add more robust error handling.

## Contributing
Feel free to fork and improve the code. Ensure changes are tested before submission.

## License
This project is open-source. Use at your own risk.
