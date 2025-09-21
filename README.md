# 🚀 TypeFast.cmd

<p align="center">
  <strong>A feature-rich terminal-based typing speed test application for Windows</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Windows-blue.svg" alt="Platform">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" alt="Language">
  <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License">
  <img src="https://img.shields.io/badge/Console-ANSI%20Colors-yellow.svg" alt="Console">
</p>

**TypeFast.cmd** is a comprehensive terminal-based typing speed test application written in C, designed specifically for Windows. Whether you're a beginner looking to improve your typing skills or an experienced typist wanting to track your progress, TypeFast.cmd offers multiple testing modes, user account management, and detailed performance analytics.

## ✨ Features

### 🔐 User Management
- **User Registration & Login System**
  - Secure password input with masking
  - Persistent user data storage
  - Support for up to 10 user accounts
  - Guest mode for anonymous practice

### ⌨️ Typing Test Modes
- **🕒 Timed Tests** - Challenge yourself with time-based typing tests
- **🎲 Random Words** - Practice with randomly selected words
- **💭 Quotes** - Type inspirational and famous quotes
- **📖 Paragraphs** - Test your skills with longer text passages
- **📚 Lessons** - Structured learning content for skill development

### 📊 Performance Tracking
- **Comprehensive Statistics**
  - Words Per Minute (WPM) tracking
  - Typing accuracy percentage
  - Personal best records (highest WPM & accuracy)
  - Average performance metrics
  - Test completion history

### 🎨 Interactive Console Interface
- **Intuitive Navigation**
  - Arrow key menu navigation
  - Color-coded typing feedback (correct/incorrect)
  - Real-time cursor positioning
  - ANSI color support for enhanced visual experience
  - ESC key for quick menu return

## 🛠️ Installation

### Prerequisites
- Windows operating system
- C compiler (GCC recommended via MinGW)
- Command Prompt or compatible terminal with ANSI support

### Quick Start

1. **Clone or download** this repository to your local machine
2. **Ensure required files** are present in the project directory:
   ```
   TypeFast.cmd/
   ├── TypeFast.c          # Main source code
   ├── words.txt           # Word list for random word tests
   ├── quotes.txt          # Collection of quotes
   ├── para.txt            # Paragraph content
   ├── lesson.txt          # Lesson materials
   └── README.md           # This file
   ```

3. **Compile the application**:
   ```bash
   gcc -o TypeFast.exe TypeFast.c
   ```
   
   Alternative compilation with MinGW:
   ```bash
   gcc -std=c99 -Wall -o TypeFast.exe TypeFast.c
   ```

4. **Run the application**:
   ```bash
   # From command line
   TypeFast.exe
   
   # Or double-click the executable in File Explorer
   ```

## 🚀 Usage

### Getting Started

1. **Launch TypeFast.exe**
2. **Choose your mode**:
   - **Register**: Create a new user account to track your progress
   - **Login**: Access your existing account and statistics
   - **Guest Mode**: Practice without creating an account

### Navigation
- Use **arrow keys** to navigate through menus
- Press **Enter** to select options
- Press **ESC** during typing tests to return to the menu
- Follow on-screen prompts for typing tests

### Test Modes Guide

| Mode         | Description                     | Best For           |
| ------------ | ------------------------------- | ------------------ |
| Timed Test   | Fixed duration typing challenge | Speed improvement  |
| Random Words | Type randomly selected words    | Accuracy practice  |
| Quotes       | Type famous quotes and sayings  | Engaging practice  |
| Paragraphs   | Type longer text passages       | Endurance building |
| Lessons      | Structured learning content     | Skill development  |

## 📁 File Structure

```
TypeFast.cmd/
├── TypeFast.c          # Main application source code
├── TypeFast.exe        # Compiled executable (after compilation)
├── users.dat           # User data storage (auto-generated)
├── words.txt           # Word database (500+ words)
├── quotes.txt          # Inspirational quotes collection
├── para.txt            # Paragraph content for testing
├── lesson.txt          # Structured lesson content
├── README.md           # Project documentation
└── LICENSE             # MIT License file
```

### Content Files
- **`words.txt`**: Contains 500+ common English words for random word tests
- **`quotes.txt`**: Collection of 15 motivational and famous quotes
- **`para.txt`**: Various paragraphs of different difficulty levels
- **`lesson.txt`**: Structured lessons for progressive skill building
- **`users.dat`**: Binary file storing user credentials and statistics (auto-generated)

## 🎯 Performance Metrics

TypeFast.cmd tracks comprehensive typing statistics:

- **Words Per Minute (WPM)**: Standard typing speed measurement
- **Accuracy Percentage**: Ratio of correctly typed characters
- **Personal Records**: Your highest WPM and accuracy achievements
- **Average Performance**: Running averages across all tests
- **Test History**: Number of completed typing tests

## 🔧 Troubleshooting

### Common Issues

**Application won't start**
- Ensure you're running on Windows
- Verify the executable was compiled successfully
- Check that all required text files are present

**Colors not displaying correctly**
- Use Command Prompt or Windows Terminal
- Ensure ANSI color support is enabled
- Avoid PowerShell ISE (limited ANSI support)

**Text files missing**
- Download or create the required `.txt` files
- Ensure files are in the same directory as the executable
- Check file permissions (read access required)

**User data not saving**
- Ensure write permissions in the application directory
- Check if `users.dat` can be created/modified
- Run as administrator if necessary

### Performance Optimization
- Use a dedicated terminal window for best experience
- Ensure adequate console window size (80x25 minimum recommended)
- Close unnecessary background applications during typing tests

## 🤝 Contributing

I welcome contributions to TypeFast.cmd! Here's how you can help:

### Ways to Contribute
- **🐛 Bug Reports**: Found an issue? Open a GitHub issue
- **💡 Feature Requests**: Have an idea? I'd love to hear it
- **📝 Content**: Add new words, quotes, or lessons
- **🔧 Code**: Submit pull requests for improvements
- **📚 Documentation**: Help improve this README or add code comments

### Development Setup
1. Fork the repository
2. Create a feature branch: `git checkout -b feature-name`
3. Make your changes and test thoroughly
4. Commit your changes: `git commit -m "Add feature description"`
5. Push to your branch: `git push origin feature-name`
6. Submit a pull request

### Code Style
- Use clear, descriptive variable names
- Add comments for complex logic
- Follow existing code formatting
- Test your changes on Windows

## 📋 Technical Specifications

- **Language**: C (C99 standard)
- **Platform**: Windows (uses Windows.h, conio.h)
- **Compiler**: GCC (MinGW recommended)
- **Dependencies**: Standard C libraries, Windows API
- **File I/O**: Binary and text file operations
- **Console**: ANSI escape sequences for colors and positioning

### Limits and Constants
- Maximum users: 10 (`MAX_USERS`)
- Maximum words in database: 500
- Maximum quotes: 15
- Maximum paragraphs: 20
- Username/password length: 30 characters
- Maximum text length: 2000 characters

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Inspired by the need for accessible typing practice tools
- Built with love for the typing community

---

<p align="center">
  <strong>Happy Typing! 🎯</strong><br>
  <em>Improve your speed, accuracy, and confidence with TypeFast.cmd</em>
</p>
