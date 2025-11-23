#pragma once

struct CrosswordCell {
    char letter = ' ';   // The correct letter
    char input = ' ';    // The user's input
    bool isBlock = true; // Is this a black square?
    bool isCorrect = false;
};
