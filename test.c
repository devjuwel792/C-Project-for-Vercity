#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_QUESTIONS 10
#define QUESTION_TIME_LIMIT 30 // seconds per question
#define OVERALL_TIME_LIMIT 900 // 15 minutes in seconds
#define POOL_SIZE 15           // questions per level

// Struct for a question
typedef struct
{
    char question[256];
    char options[4][100];
    int correct; // 0-3 for A-D
} Question;

// Sample questions for each level (expand as needed)
Question easyPool[POOL_SIZE] = {
    {"What is 2 + 2?", {"A. 3", "B. 4", "C. 5", "D. 6"}, 1},
    {"Which is the odd one out: Apple, Banana, Carrot, Orange?", {"A. Apple", "B. Banana", "C. Carrot", "D. Orange"}, 2},
    // Add 13 more similar easy questions...
    {"What comes next: 1, 3, 5, ?", {"A. 6", "B. 7", "C. 8", "D. 9"}, 1},
    {"If A=1, B=2, C=3, what is D?", {"A. 4", "B. 5", "C. 6", "D. 7"}, 0},
    {"How many sides does a triangle have?", {"A. 2", "B. 3", "C. 4", "D. 5"}, 1},
    {"Which word is a synonym of 'happy'?", {"A. Sad", "B. Joyful", "C. Angry", "D. Tired"}, 1},
    {"What is 10 - 3?", {"A. 6", "B. 7", "C. 8", "D. 9"}, 1},
    {"Which shape has 4 equal sides?", {"A. Circle", "B. Triangle", "C. Square", "D. Rectangle"}, 2},
    {"If today is Monday, what is tomorrow?", {"A. Sunday", "B. Tuesday", "C. Wednesday", "D. Thursday"}, 1},
    {"What is the color of the sky on a clear day?", {"A. Red", "B. Blue", "C. Green", "D. Yellow"}, 1},
    {"How many fingers on one hand?", {"A. 4", "B. 5", "C. 6", "D. 7"}, 1},
    {"Which animal is known as the 'King of the Jungle'?", {"A. Lion", "B. Tiger", "C. Elephant", "D. Bear"}, 0},
    {"What is 5 x 2?", {"A. 7", "B. 10", "C. 12", "D. 15"}, 1},
    {"Which is larger: Elephant or Mouse?", {"A. Same", "B. Mouse", "C. Elephant", "D. None"}, 2},
    {"What is the opposite of 'hot'?", {"A. Warm", "B. Cold", "C. Wet", "D. Dry"}, 1}};

Question mediumPool[POOL_SIZE] = {
    {"What is 15 + 27?", {"A. 40", "B. 42", "C. 44", "D. 46"}, 1},
    {"Which is the odd one out: 2, 4, 6, 9?", {"A. 2", "B. 4", "C. 6", "D. 9"}, 3},
    // Add 13 more medium questions...
    {"What comes next: 2, 4, 8, 16, ?", {"A. 18", "B. 24", "C. 32", "D. 64"}, 2},
    {"If A=2, B=4, C=6, what is D?", {"A. 8", "B. 10", "C. 12", "D. 14"}, 0},
    {"How many degrees in a right angle?", {"A. 45", "B. 90", "C. 180", "D. 360"}, 1},
    {"Which word is an antonym of 'brave'?", {"A. Cowardly", "B. Strong", "C. Fast", "D. Smart"}, 0},
    {"What is 50 - 17?", {"A. 33", "B. 35", "C. 37", "D. 39"}, 0},
    {"Which shape has all sides equal but no right angles?", {"A. Square", "B. Rectangle", "C. Rhombus", "D. Triangle"}, 2},
    {"If 3 cats catch 3 mice in 3 minutes, how many cats to catch 100 mice in 100 minutes?", {"A. 3", "B. 33", "C. 100", "D. 300"}, 0},
    {"What is the square root of 81?", {"A. 7", "B. 8", "C. 9", "D. 10"}, 2},
    {"How many continents are there?", {"A. 5", "B. 6", "C. 7", "D. 8"}, 2},
    {"Which planet is known as the Red Planet?", {"A. Venus", "B. Mars", "C. Jupiter", "D. Saturn"}, 1},
    {"What is 7 x 8?", {"A. 54", "B. 56", "C. 58", "D. 60"}, 1},
    {"Which is heavier: 1 kg of feathers or 1 kg of gold?", {"A. Feathers", "B. Gold", "C. Same", "D. None"}, 2},
    {"What is the opposite of 'up'?", {"A. Down", "B. Left", "C. Right", "D. Side"}, 0}};

Question hardPool[POOL_SIZE] = {
    {"What is 123 + 456?", {"A. 579", "B. 589", "C. 599", "D. 609"}, 0},
    {"Which is the odd one out: 1, 8, 27, 64, 125?", {"A. 1", "B. 8", "C. 27", "D. 64"}, 0}, // 1 is not a cube
    // Add 13 more hard questions...
    {"What comes next: 1, 1, 2, 3, 5, 8, ?", {"A. 10", "B. 11", "C. 12", "D. 13"}, 3},
    {"If A=3, B=6, C=9, what is D?", {"A. 12", "B. 15", "C. 18", "D. 21"}, 0},
    {"How many sides does a dodecagon have?", {"A. 10", "B. 12", "C. 14", "D. 16"}, 1},
    {"Which word means 'fear of heights'?", {"A. Claustrophobia", "B. Acrophobia", "C. Arachnophobia", "D. Hydrophobia"}, 1},
    {"What is 1000 - 237?", {"A. 763", "B. 773", "C. 783", "D. 793"}, 0},
    {"Which logic gate outputs 1 only if both inputs are 1?", {"A. OR", "B. AND", "C. NOT", "D. XOR"}, 1},
    {"If a train leaves at 60 mph and another at 40 mph, how long to meet if 100 miles apart?", {"A. 1h", "B. 1.5h", "C. 2h", "D. 2.5h"}, 0},
    {"What is 2^10?", {"A. 512", "B. 1024", "C. 2048", "D. 4096"}, 1},
    {"How many elements in the periodic table (approx)?", {"A. 100", "B. 118", "C. 150", "D. 200"}, 1},
    {"Which particle has no charge?", {"A. Proton", "B. Electron", "C. Neutron", "D. Positron"}, 2},
    {"What is 13 x 17?", {"A. 221", "B. 231", "C. 241", "D. 251"}, 0},
    {"Which paradox involves a barber shaving all who don't shave themselves?", {"A. Zeno", "B. Russell", "C. Epimenides", "D. Sorites"}, 1},
    {"What is the integral of x dx?", {"A. x", "B. x^2", "C. x^2/2", "D. 2x"}, 2}};

// Function to get improving message based on score
const char *getImprovingMessage(int score)
{
    if (score >= 9)
        return "Excellent! You're a genius. Keep it up!";
    if (score >= 7)
        return "Great job! You're improving steadily.";
    if (score >= 5)
        return "Good effort! Practice more to improve.";
    return "Keep trying! Focus on basics to get better.";
}

// Function to randomize and select 10 questions from pool
void selectRandomQuestions(Question pool[], Question selected[])
{
    int indices[POOL_SIZE];
    for (int i = 0; i < POOL_SIZE; i++)
        indices[i] = i;
    // Shuffle indices
    for (int i = POOL_SIZE - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
   
    for (int i = 0; i < TOTAL_QUESTIONS; i++)
    {
        selected[i] = pool[indices[i]];
    }
}

int main()
{
    srand(time(NULL)); // Seed random
    char name[50], level[10];
    int score = 0;
    time_t startTime = time(NULL), endTime;
    Question selected[TOTAL_QUESTIONS];

    // Get user details
    printf("Enter your name: ");
    // fgets(name, sizeof(name), stdin);
    scanf("%s", name);
    printf("\nSelect level (Easy/Medium/Hard): ");
    scanf("%s", level);

    // Select pool and randomize questions
    if (level == "Easy" || level == "easy")
    {
        selectRandomQuestions(easyPool, selected);
    }
    else if (level == "Medium" || level == "medium")
    {
        selectRandomQuestions(mediumPool, selected);
    }
    else if (level == "Hard" || level == "hard")
    {
        selectRandomQuestions(hardPool, selected);
    }
    else
    {
        printf("Invalid level. Defaulting to Easy.\n");
        selectRandomQuestions(easyPool, selected);
        // strcpy(level, "Easy");
    }

    printf("Quiz starts now! You have 15 minutes total. Each question has 30 seconds.\n");

    // Quiz loop
    for (int i = 0; i < TOTAL_QUESTIONS; i++)
    {
        time_t questionStart = time(NULL);
        printf("\nQuestion %d: %s\n", i + 1, selected[i].question);
        for (int j = 0; j < 4; j++)
        {
            printf("%s\n", selected[i].options[j]);
        }
        printf("Your answer (A/B/C/D): ");

        // Timer loop for question
        char answer = 0;
        while (difftime(time(NULL), questionStart) < QUESTION_TIME_LIMIT)
        {
            if (difftime(time(NULL), questionStart) > QUESTION_TIME_LIMIT - 10)
            {
                printf("10 seconds left!\n");
            }
            if (kbhit())
            { // Non-blocking input (Windows-specific; for cross-platform, use threads or select)
                answer = getchar();
                break;
            }
            // Check overall time
            if (difftime(time(NULL), startTime) >= OVERALL_TIME_LIMIT)
            {
                printf("Time's up! Quiz ended early.\n");
                goto endQuiz;
            }
        }

        if (answer == 0)
        {
            printf("Time out! Moving to next.\n");
        }
        else
        {
            getchar(); // Consume newline
            int choice = answer - 'A';
            if (choice == selected[i].correct)
            {
                score++;
                printf("Correct!\n");
            }
            else
            {
                printf("Wrong! Correct is %c.\n", 'A' + selected[i].correct);
            }
        }

        // Check overall time again
        if (difftime(time(NULL), startTime) >= OVERALL_TIME_LIMIT)
        {
            printf("Overall time's up!\n");
            break;
        }
    }

endQuiz:
    endTime = time(NULL);
    double totalTime = difftime(endTime, startTime);

    // Store results in file
    FILE *file = fopen("iq_results.txt", "a");
    if (file)
    {
        fprintf(file, "Name: %s, Level: %s, Score: %d/10, Time: %.0f seconds, Date: %s\n",
                name, level, score, totalTime, ctime(&endTime));
        fclose(file);
    }
    else
    {
        printf("Error saving results.\n");
    }

    // Display results
    printf("\n--- Results ---\n");
    printf("Name: %s\n", name);
    printf("Level: %s\n", level);
    printf("Score: %d/10\n", score);
    printf("Time Taken: %.0f seconds\n", totalTime);
    printf("Message: %s\n", getImprovingMessage(score));

    return 0;
}
