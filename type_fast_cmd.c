#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_USERS 10
#define CREDENTIAL_LENGTH 15
#define FILE_NAME "users.dat"

typedef struct
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
    float avg_wpm;
    float highest_wpm;
    float avg_accuracy;
    float highest_accuracy;
    int tests_taken;
} User;

User users[MAX_USERS];
int user_count = 0;

const char *YELLOW = "\033[1;33m";
const char *BLUE = "\033[1;34m";
const char *GREEN = "\033[1;32m";
const char *CYAN = "\033[1;36m";
const char *RED = "\033[1;31m";
const char *WHITE = "\033[1;37m";
const char *COLOR_END = "\033[0m";

#define BLUE_T 1
#define GREEN_T 2
#define CYAN_T 3
#define RED_T 4
#define YELLOW_T 6
#define WHITE_T 7

#define MAX_WORDS 500
#define MAX_QUOTES 15
#define MAX_PARAGRAPHS 20
#define WORD_LENGTH 50
#define MAX_TEXT_LENGTH 2000

typedef enum
{
    WORDS,
    QUOTES,
    PARAGRAPHS,
    LESSON,
} Mode;

void setConsoleTitle(char *);
int getConsoleWidth();
void setCursorPos(int, int);
void hide_cursor();
void show_cursor();
void setColor(int);

void register_user();
int login_user();
void input_credentials(char *, char *);
void get_password(char *, int);

int menu_navigation(char *[], int);

void load_users_from_file();
void save_users_to_file();
void update_stats(const char *, float, float);
void view_stats(const char *);

void generateRandomText(Mode, int, char *);
void startTypingTest(char *, int);
void start_timed_mode(int);
void showTimer(int);

int main()
{
    system("cls");
    setConsoleTitle("TypeFast.cmd");
    load_users_from_file();

    printf("%sWelcome to TYPEFAST.cmd%s\n", YELLOW, COLOR_END);

    int user_index = -1;

    char *OptionsDefaultRegLogout[] = {"Register/Sign Up", "Login/Sign In", "Take a typing test (Guest Mode)", "Exit"};
    char *OptionsGuestMode[] = {"Timed Test", "Random Words", "Quotes", "Paragraphs"};
    char *OptionsLogin[] = {"Start Typing", "Your Typing Stats", "Logout"};
    char *OptionsType[] = {"Timed", "Random Words", "Quotes", "Paragraphs", "Lessons"};

    while (1)
    {
        int option;
        if (user_index == -1)
        {
            option = menu_navigation(OptionsDefaultRegLogout, 4);
        }
        else
        {
            option = menu_navigation(OptionsLogin, 3);
        }

        switch (option)
        {
        case 1:
            if (user_index == -1)
            {
                register_user();
            }
            else
            {
                int optionTyp = menu_navigation(OptionsType, 5);

                char result[MAX_TEXT_LENGTH];
                int numWords = 50;

                switch (optionTyp)
                {
                case 1:
                    start_timed_mode(user_index);
                    break;
                case 2:
                    generateRandomText(0, 20, result);
                    startTypingTest(result, user_index);
                    break;
                case 3:
                    generateRandomText(1, numWords, result);
                    startTypingTest(result, user_index);
                    break;
                case 4:
                    generateRandomText(2, numWords, result);
                    startTypingTest(result, user_index);
                    break;
                case 5:
                    generateRandomText(LESSON, numWords, result);
                    startTypingTest(result, user_index);
                    break;
                default:
                    break;
                }
            }
            break;
        case 2:
            if (user_index == -1)
            {
                user_index = login_user();
                if (user_index >= 0)
                {
                    printf("%sLogin successful! Welcome, %s%s%s!%s\n", GREEN, COLOR_END, YELLOW, users[user_index].username, COLOR_END);
                }
                else
                {
                    printf("%sLogin Failed! Incorrect username or password%s\n", RED, COLOR_END);
                }
            }
            else
            {
                view_stats(users[user_index].username);
            }
            break;
        case 3:
            if (user_index == -1)
            {
                int optionGuest = menu_navigation(OptionsGuestMode, 4);
                char result[MAX_TEXT_LENGTH];
                int numWords = 50;

                switch (optionGuest)
                {
                case 1:
                    start_timed_mode(user_index);
                    break;
                case 2:
                    generateRandomText(0, 20, result);
                    startTypingTest(result, user_index);
                    break;
                case 3:
                    generateRandomText(1, numWords, result);
                    startTypingTest(result, user_index);
                    break;
                case 4:
                    generateRandomText(2, numWords, result);
                    startTypingTest(result, user_index);
                    break;
                }
            }
            else
            {
                user_index = -1;
                printf("%sLogged out successfully!%s\n", BLUE, COLOR_END);
            }
            break;
        case 4:
            if (user_index == -1)
            {
                printf("%s\nExiting program.%s\n", BLUE, COLOR_END);
                return 0;
            }
            break;
        }
    }
    getch();
    return 0;
}

void setConsoleTitle(char *title)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTitle(title);
}

int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwSize.X;
}

void setCursorPos(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(hConsole, coord);
}

void hide_cursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void show_cursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void register_user()
{
    if (user_count == MAX_USERS)
    {
        printf("\n%sMaximum %d users are supported! No more registrations allowed!!!%s\n", RED, MAX_USERS, COLOR_END);
        return;
    }

    char temp_username[CREDENTIAL_LENGTH];
    char temp_password[CREDENTIAL_LENGTH];

    printf("\n%sRegister a new user: %s\n", CYAN, COLOR_END);

    while (1)
    {
        printf("%s\nEnter username: %s", CYAN, COLOR_END);
        fgets(temp_username, CREDENTIAL_LENGTH, stdin);
        temp_username[strcspn(temp_username, "\n")] = '\0';

        int is_unique = 1;
        for (int i = 0; i < user_count; i++)
        {
            if (strcmp(temp_username, users[i].username) == 0)
            {
                is_unique = 0;
                printf("\n%sUsername already taken! Please choose another.%s\n", RED, COLOR_END);
                break;
            }
        }

        if (is_unique)
        {
            break;
        }
    }

    printf("%sEnter password (masking enabled): %s", CYAN, COLOR_END);
    get_password(temp_password, CREDENTIAL_LENGTH);

    strcpy(users[user_count].username, temp_username);
    strcpy(users[user_count].password, temp_password);
    users[user_count].avg_wpm = 0;
    users[user_count].highest_wpm = 0;
    users[user_count].tests_taken = 0;
    users[user_count].avg_accuracy = 0;
    users[user_count].highest_accuracy = 0;
    user_count++;

    save_users_to_file();
    printf("%s\nRegistration successful! User: '%s'%s\n", GREEN, temp_username, COLOR_END);
}

int login_user()
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];

    printf("\n%sLogin: %s\n", CYAN, COLOR_END);

    input_credentials(username, password);

    for (int i = 0; i < user_count; i++)
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0)
        {
            return i;
        }
    }
    return -1;
}

void input_credentials(char *username, char *password)
{
    printf("\n%sEnter username: %s", CYAN, COLOR_END);
    fgets(username, CREDENTIAL_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';
    printf("%sEnter password (masking enabled): %s", CYAN, COLOR_END);
    get_password(password, CREDENTIAL_LENGTH);
}

void get_password(char *password, int maxLength)
{
    int i = 0;
    char ch;

    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
        else if (i < maxLength - 1)
        {
            password[i++] = ch;
            printf("*");
        }
    }

    password[i] = '\0';
    printf("\n");
}

int menu_navigation(char *options[], int size)
{
    int selected = 1;
    int ch;

    while (1)
    {
        for (int i = 0; i < size; i++)
        {
            printf("%s%s%d. %s%s\n",
                   selected == i + 1 ? "\033[1;42m" : "",
                   selected == i + 1 ? ">> " : "   ",
                   i + 1,
                   options[i],
                   COLOR_END);
        }

        ch = getch();
        if (ch)
        {
            system("cls");
        }
        if (ch == 224)
        {
            ch = getch();
            if (ch == 72 && selected > 1)
                selected--;
            else if (ch == 80 && selected < size)
                selected++;
        }
        else if (ch == 13)
        {
            return selected;
        }
    }
}

void load_users_from_file()
{
    FILE *file = fopen(FILE_NAME, "rb");
    if (file != NULL)
    {
        fread(&user_count, sizeof(int), 1, file);
        fread(users, sizeof(User), user_count, file);
        fclose(file);
    }
}

void save_users_to_file()
{
    FILE *file = fopen(FILE_NAME, "wb");
    if (file != NULL)
    {
        fwrite(&user_count, sizeof(int), 1, file);
        fwrite(users, sizeof(User), user_count, file);
        fclose(file);
    }
}

void update_stats(const char *username, float wpm, float accuracy)
{
    FILE *file = fopen(FILE_NAME, "rb+");
    if (!file)
    {
        printf("Error opening file!\n");
        return;
    }

    int file_user_count;
    fread(&file_user_count, sizeof(int), 1, file);

    User user;
    int found = 0;

    for (int i = 0; i < file_user_count; i++)
    {
        fread(&user, sizeof(User), 1, file);

        if (strcmp(user.username, username) == 0)
        {
            found = 1;

            user.tests_taken++;
            user.avg_wpm = ((user.avg_wpm * (user.tests_taken - 1)) + wpm) / user.tests_taken;
            user.avg_accuracy = ((user.avg_accuracy * (user.tests_taken - 1)) + accuracy) / user.tests_taken;
            if (wpm > user.highest_wpm)
            {
                user.highest_wpm = wpm;
            }
            if (accuracy > user.highest_accuracy)
            {
                user.highest_accuracy = accuracy;
            }

            fseek(file, -(long)sizeof(User), SEEK_CUR);
            fwrite(&user, sizeof(User), 1, file);
            break;
        }
    }
    fclose(file);
}

void view_stats(const char *username)
{
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file)
    {
        printf("Error opening file!\n");
        return;
    }

    int file_user_count;
    fread(&file_user_count, sizeof(int), 1, file);

    User user;
    int found = 0;

    for (int i = 0; i < file_user_count; i++)
    {
        fread(&user, sizeof(User), 1, file);

        if (strcmp(user.username, username) == 0)
        {
            found = 1;
            printf("%s\nStats for: %s%s\n\n", BLUE, user.username, COLOR_END);
            printf("TESTS TAKEN: %d\n", user.tests_taken);
            printf("AVERAGE WPM: %.2f\n", user.avg_wpm);
            printf("HIGHEST WPM: %s%.2f%s\n", GREEN, user.highest_wpm, COLOR_END);
            printf("AVERAGE ACCURACY: %.2f%%\n", user.avg_accuracy);
            printf("HIGHEST ACCURACY: %s%.2f%%%s\n", GREEN, user.highest_accuracy, COLOR_END);
            break;
        }
    }

    fclose(file);
}

void generateRandomText(Mode mode, int numWords, char *result)
{
    FILE *file;
    char words[MAX_WORDS][WORD_LENGTH];
    char quotes[MAX_QUOTES][MAX_TEXT_LENGTH];
    char paragraphs[MAX_PARAGRAPHS][MAX_TEXT_LENGTH];
    char lesson[MAX_PARAGRAPHS][MAX_TEXT_LENGTH];
    int count = 0;

    switch (mode)
    {
    case WORDS:
        file = fopen("words.txt", "r");
        break;
    case QUOTES:
        file = fopen("quotes.txt", "r");
        break;
    case PARAGRAPHS:
        file = fopen("para.txt", "r");
        break;
    case LESSON:
        file = fopen("lesson.txt", "r");
        break;
    default:
        printf("Invalid mode!\n");
        return;
    }

    if (!file)
    {
        printf("Error opening file.\n");
        return;
    }

    if (mode == WORDS)
    {
        while (count < MAX_WORDS && fscanf(file, "%49s", words[count]) == 1)
        {
            count++;
        }
    }
    else
    {
        while (count < (mode == QUOTES ? MAX_QUOTES : MAX_PARAGRAPHS) &&
               fgets(mode == QUOTES ? quotes[count] : (mode == LESSON ? lesson[count] : paragraphs[count]),
                     MAX_TEXT_LENGTH, file))
        {
            count++;
        }
    }
    fclose(file);

    if (count == 0)
    {
        printf("No data found in file.\n");
        return;
    }

    srand(time(NULL));
    result[0] = '\0';

    if (mode == WORDS)
    {
        for (int i = 0; i < numWords; i++)
        {
            int randIndex = rand() % count;
            strcat(result, words[randIndex]);
            if (i < numWords - 1)
            {
                strcat(result, " ");
            }
        }
    }
    else
    {
        int randIndex = rand() % count;
        strcat(result, mode == QUOTES ? quotes[randIndex] : (mode == LESSON ? lesson[randIndex] : paragraphs[randIndex]));
    }
}
void startTypingTest(char *text, int user_index)
{
    system("cls");
    printf("%s", text);
    setCursorPos(0, 0);

    int len = strlen(text);
    int i = 0, mistakes = 0, totalKeystrokes = 0;
    int x = 0, y = 0;

    time_t startTime = time(NULL);

    int console_width = getConsoleWidth();

    while (i < len)
    {
        char ch = getch();

        if (ch == 27)
        {
            system("cls");
            return;
        }

        if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                if (x == 0 && y > 0)
                {
                    y--;
                    x = console_width - 1;
                }
                else
                {
                    x--;
                }

                setCursorPos(x, y);
                setColor(WHITE_T);
                printf("%c", text[i]);
                setCursorPos(x, y);
            }
            continue;
        }

        totalKeystrokes++;

        if (ch == ' ' && text[i] != ' ')
        {
            mistakes++;
            continue;
        }

        if (ch == text[i])
        {
            setColor(GREEN_T);
        }
        else
        {
            setColor(RED_T);
            mistakes++;
        }

        printf("%c", ch);
        setColor(WHITE_T);

        i++;

        if (x == console_width - 1)
        {
            x = 0;
            y++;
        }
        else
        {
            x++;
        }

        setCursorPos(x, y);
    }

    time_t endTime = time(NULL);
    double elapsedTime = difftime(endTime, startTime);
    double wordsTyped = len / 5.0;
    double WPM = (wordsTyped / elapsedTime) * 60.0;
    double accuracy = ((double)(totalKeystrokes - mistakes) / totalKeystrokes) * 100.0;

    if (user_index >= 0)
    {
        update_stats(users[user_index].username, WPM, accuracy);
    }

    printf("\n%sTyping Complete!%s\n", BLUE, COLOR_END);
    printf("TOTAL TIME: %.2f seconds\n", elapsedTime);
    printf("Words Per Minute (WPM): %.2f\n", WPM);
    printf("ACCURACY: %.2f%%\n", accuracy);
    printf("MISTAKES: %d\n", mistakes);
    printf("\n");
    printf("%sPress Enter to Return to Main Menu: %s", CYAN, COLOR_END);
    getch();
    system("cls");
}

void start_timed_mode(int user_index)
{
    system("cls");

    char result[MAX_TEXT_LENGTH];
    generateRandomText(WORDS, 50, result);
    int len = strlen(result);

    printf("%s", result);
    setCursorPos(0, 0);

    int i = 0, mistakes = 0, totalKeystrokes = 0;
    time_t startTime = time(NULL);
    time_t endTime = startTime + 15;

    int lastTimeLeft = 15;

    while (i < len)
    {
        time_t currentTime = time(NULL);
        int timeLeft = (int)(endTime - currentTime);

        if (timeLeft != lastTimeLeft)
        {
            showTimer(timeLeft);
            lastTimeLeft = timeLeft;
        }

        if (timeLeft <= 0)
        {
            break;
        }

        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 27)
            {
                system("cls");
                return;
            }
            if (ch == 8)
            {
                if (i > 0)
                {
                    i--;
                    setCursorPos(i, 0);
                    setColor(WHITE_T);
                    printf("%c", result[i]);
                    setCursorPos(i, 0);
                }
                continue;
            }

            totalKeystrokes++;
            if (ch == ' ' && result[i] != ' ')
            {
                mistakes++;
                continue;
            }
            if (ch == result[i])
            {
                setColor(GREEN_T);
            }
            else
            {
                setColor(RED_T);
                mistakes++;
            }

            setCursorPos(i, 0);
            printf("%c", result[i]);
            setCursorPos(i + 1, 0);
            setColor(WHITE_T);
            i++;
        }
    }

    double elapsedTime = 15 - (endTime - time(NULL));
    double wordsTyped = i / 5.0;
    double WPM = (wordsTyped / elapsedTime) * 60.0;
    double accuracy = ((double)(totalKeystrokes - mistakes) / totalKeystrokes) * 100.0;

    int textLines = (len / getConsoleWidth()) + 1;
    setCursorPos(0, textLines + 2);

    printf("\n%sTIMES'S UP!%s\n\n", BLUE, COLOR_END);
    printf("Words Per Minute (WPM): %.2f\n", WPM);
    printf("ACCURACY: %.2f%%\n", accuracy);

    if (user_index >= 0)
    {
        update_stats(users[user_index].username, WPM, accuracy);
    }

    printf("\n%sPress Enter to Return to Main Menu: %s\n", CYAN, COLOR_END);
    while (_getch() != 13)
        ;
    system("cls");
}

void showTimer(int timeLeft)
{
    static int lastTimeLeft = -1;

    if (timeLeft != (lastTimeLeft + 1))
    {
        COORD cursorPos;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        cursorPos = csbi.dwCursorPosition;

        setCursorPos(0, 10);
        setColor(WHITE_T);
        printf("%sTime Left: %2d seconds  %s", YELLOW, timeLeft, COLOR_END);

        SetConsoleCursorPosition(hConsole, cursorPos);
        lastTimeLeft = timeLeft;
    }
}