#pragma once
#include "CrosswordCell.h"
#include <vector>
#include <string>

#include "../worddb/Topics.h"

class CrosswordPuzzle {
public:
    CrosswordPuzzle();
    void LoadSimplePuzzle();
    void GenerateFromChapter(int chapter);
    
    static const int ROWS = 15;
    static const int COLS = 15;
    
    CrosswordCell& GetCell(int r, int c);
    bool IsSolved();
    
    std::string GetClue(int r, int c, bool across);

private:
    bool CanPlaceWord(const std::string& word, int r, int c, bool across);
    void PlaceWord(const std::string& word, const std::string& clue, int r, int c, bool across);

    CrosswordCell m_grid[ROWS][COLS];
    
    struct ClueInfo {
        int r, c;
        bool across;
        std::string clueText;
        std::string word; // Store the word for validation/debugging
    };
    std::vector<ClueInfo> m_clues;
};
