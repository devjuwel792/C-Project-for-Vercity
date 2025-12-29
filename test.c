#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define TOTAL_QUESTIONS 10
// #define QUESTION_TIME_LIMIT 30
#define OVERALL_TIME_LIMIT 60*10 // 10 minutes
#define POOL_SIZE 15

// Struct for a question
typedef struct
{
    char question[256];
    char options[4][100];
    int correct; // 0-3 for A-D
} Question;

// Struct for quiz result
typedef struct
{
    char name[50];
    char level[10];
    int score;
    double time;
} Result;

// Sample questions for each level (expand as needed)
Question easyPool[POOL_SIZE] = {
    {"What is 2 + 2?", {"A. 3", "B. 4", "C. 5", "D. 6"}, 1},
    {"Which is the odd one out: Apple, Banana, Carrot, Orange?", {"A. Apple", "B. Banana", "C. Carrot", "D. Orange"}, 2},
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
    {"Which is the odd one out: 1, 8, 27, 64, 125?", {"A. 1", "B. 8", "C. 27", "D. 64"}, 0}, 
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

// Function to load results from file
int loadResults(Result results[])
{
    FILE *file = fopen("iq_results.txt", "r");
    if (!file)
    {
        return 0;
    }
    char line[512];
    int count = 0;
    while (fgets(line, sizeof(line), file) && count < 100)
    {
        char name[50], level[10], date[50];
        int score;
        double time;
        if (sscanf(line, "Name: %49[^,], Level: %9[^,], Score: %d/10, Time: %lf seconds, Date: %[^\n]",
                   name, level, &score, &time, date) == 5)
        {
            strcpy(results[count].name, name);
            strcpy(results[count].level, level);
            results[count].score = score;
            results[count].time = time;
            count++;
        }
    }
    fclose(file);
    return count;
}

// Function to compare results for sorting (higher score first, then lower time)
int compareResults(const void *a, const void *b)
{
    Result *r1 = (Result *)a;
    Result *r2 = (Result *)b;
    if (r1->score != r2->score)
        return r2->score - r1->score; // descending score
    return r1->time - r2->time;       // ascending time
}

// Function to display top scorers
void displayTopScorers(Result results[], int count, char *currentName)
{
    if (count == 0)
    {
        printf("No results available yet.\n");
        return;
    }
    qsort(results, count, sizeof(Result), compareResults);
    printf("\n--- Top Scorers ---\n");
    printf("Rank | Name          | Level   | Score | Time (s)\n");
    printf("-----|---------------|---------|-------|---------\n");
    int displayCount = count < 10 ? count : 10;
    for (int i = 0; i < displayCount; i++)
    {
        char marker = (strcmp(results[i].name, currentName) == 0) ? '*' : ' ';
        printf("%4d%c| %-13s | %-7s | %2d/10 | %.1f\n",
               i + 1, marker, results[i].name, results[i].level, results[i].score, results[i].time);
    }
    if (strcmp(results[0].name, currentName) == 0)
    {
        printf("* Indicates your score.\n");
    }
}
// Authentication functions
int sign_up(char *username, char *password)
{
    FILE *file = fopen("users.txt", "a+");
    if (!file)
    {
        printf("Error opening users file.\n");
        return 0;
    }
    char line[256];
    rewind(file);
    while (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, " ");
        if (token && strcmp(token, username) == 0)
        {
            printf("Username already exists. Try logging in.\n");
            fclose(file);
            return 0;
        }
    }
    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    printf("Sign up successful!\n");
    return 1;
}

int log_in(char *username, char *password)
{
    FILE *file = fopen("users.txt", "r");
    if (!file)
    {
        printf("No users registered yet. Please sign up first.\n");
        return 0;
    }
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char *stored_username = strtok(line, " ");
        char *stored_password = strtok(NULL, "\n");
        if (stored_username && stored_password && strcmp(stored_username, username) == 0 && strcmp(stored_password, password) == 0)
        {
            fclose(file);
            printf("Login successful!\n");
            return 1;
        }
    }
    fclose(file);
    printf("Invalid username or password.\n");
    return 0;
}

int main()
{
    srand(time(NULL)); // Seed random
    char name[50], level[10];
    int score = 0;
    time_t startTime = time(NULL), endTime;
    Question selected[TOTAL_QUESTIONS];
    int validInput = 0;
    int answered = 0;

    // Authentication
    int authenticated = 0;
    int attempts = 0;

    while (!authenticated && attempts < 3)
    {

        printf("Choose an option:\n1. Sign Up\n2. Log In\n");

        int choice;
        printf("Enter choice (1 or 2): ");

        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Enter username: ");
            scanf("%s", name);
            char password[50];
            printf("Enter password: ");
            scanf("%s", password);
            if (sign_up(name, password))
            {
                authenticated = 1;
            }
        }
        else if (choice == 2)
        {
            printf("Enter username: ");
            scanf("%s", name);
            char password[50];
            printf("Enter password: ");
            scanf("%s", password);
            if (log_in(name, password))
            {
                authenticated = 1;
            }
        }
        else
        {
            printf("Invalid choice.\n");
        }

        attempts++;
        if (!authenticated && attempts < 3)
        {
            printf("Try again.\n");
        }
    }

    if (!authenticated)
    {
        printf("Too many failed attempts. Exiting.\n");
        return 1;
    }

    printf("\nSelect level (Easy/Medium/Hard): ");
    scanf("%s", level);

    // Select pool and randomize questions
    if (strcmp(level, "Easy") == 0 || strcmp(level, "easy") == 0)
    {
        selectRandomQuestions(easyPool, selected);
    }
    else if (strcmp(level, "Medium") == 0 || strcmp(level, "medium") == 0)
    {
        selectRandomQuestions(mediumPool, selected);
    }
    else if (strcmp(level, "Hard") == 0 || strcmp(level, "hard") == 0)
    {
        selectRandomQuestions(hardPool, selected);
    }
    else
    {
        printf("Invalid level. Defaulting to Easy.\n");
        selectRandomQuestions(easyPool, selected);
        strcpy(level, "Easy");
    }

    printf("Quiz starts now! You have %d minutes to answer 10 questions. Good luck!\n", OVERALL_TIME_LIMIT / 60);


    
    // Quiz loop
    for (int i = 0; i < TOTAL_QUESTIONS; i++)
    {
        if (difftime(time(NULL), startTime) >= OVERALL_TIME_LIMIT)
        {
            printf("Time's up!\n");
            goto endQuiz;
        }
        time_t questionStart = time(NULL);
        char answer;
        printf("\nQuestion %d: %s\n", i + 1, selected[i].question);
        for (int j = 0; j < 4; j++)
        {
            printf("%s\n", selected[i].options[j]);
        }
        int choice;

        printf("Your answer (A/B/C/D): ");

        scanf(" %c", &answer);
        answer = toupper(answer);

        choice = answer - 'A';

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
    printf("Score: %d/%d (%.2f%% accuracy)\n", score, TOTAL_QUESTIONS, (float)score / TOTAL_QUESTIONS * 100);
    printf("Time Taken: %.0f seconds\n", totalTime);
    printf("Message: %s\n", getImprovingMessage(score));

    // Load and display top scorers
    Result allResults[100];
    int resultCount = loadResults(allResults);
    displayTopScorers(allResults, resultCount, name);

    // Prevent terminal from closing immediately
    // printf("\nPress any key to exit...\n");
    system("pause");


    return 0;
}
