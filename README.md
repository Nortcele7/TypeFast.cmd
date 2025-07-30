# TypeFast.cmd

**TypeFast.cmd** is a terminal-based typing speed test application written in C, designed to run on Windows. It allows users to Register, Login, and track typing performance over time, or practice anonymously in Guest Mode.

---

## Features

- **User Registration & Login**
  - Save and load user credentials with stats.
  - Password input masking.
- **Typing Tests**
  - Modes include: Timed Test, Random Words, Quotes, Paragraphs, and Lessons.
- **Performance Tracking**
  - Track average WPM, accuracy, highest WPM, and accuracy.
  - View detailed stats after each session.
- **Interactive Console UI**
  - Arrow key menu navigation.
  - Color-coded typing feedback.
  - Cursor control and console customization.

---

## Files Required

Ensure the following text files exist in the same directory as the executable:

- `words.txt` – A list of words (for the Random Words test)
- `quotes.txt` – Quotes for typing
- `para.txt` – Paragraphs for typing
- `lesson.txt` – Lesson content for typing

Also ensure:

- `users.dat` – This will be generated automatically for storing user credentials and stats.

---

## Compilation

Compile using a Windows-compatible C compiler such as GCC from MinGW:

```
gcc -o TypeFast.exe your_source_file.c
```

Make sure you link necessary libraries if using certain compilers.

---

## Running

Double-click the compiled `TypeFast.exe` or run it from the terminal:

```
TypeFast.exe
```

Use arrow keys to navigate menus. Press `ESC` during a typing test to return to the menu.

---

## Notes

- Maximum of 10 user accounts (`MAX_USERS` defined).
- Console dimensions may affect text layout.
- Best run in Command Prompt or compatible terminal with ANSI support.

---

## License

MIT License - free to use and modify.
