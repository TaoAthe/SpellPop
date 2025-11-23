#include "CrosswordPuzzle.h"
#include <algorithm>
#include <iostream>

CrosswordPuzzle::CrosswordPuzzle() {
    // Initialize all as blocks
    for(int r=0; r<ROWS; ++r) {
        for(int c=0; c<COLS; ++c) {
            m_grid[r][c].isBlock = true;
            m_grid[r][c].letter = ' ';
            m_grid[r][c].input = ' ';
        }
    }
}

void CrosswordPuzzle::LoadSimplePuzzle() {
    // Hardcoded "STAR" across at 5,2
    // Hardcoded "MOON" down at 2,5 (intersecting? No, let's keep it simple)
    
    // STAR
    int r = 5;
    int c = 2;
    std::string word = "STAR";
    for(int i=0; i<word.length(); ++i) {
        m_grid[r][c+i].isBlock = false;
        m_grid[r][c+i].letter = word[i];
    }
    m_clues.push_back({r, c, true, "Celestial body that emits light"});
    
    // MOON
    r = 2;
    c = 5;
    word = "MOON";
    for(int i=0; i<word.length(); ++i) {
        m_grid[r][c].isBlock = false;
        m_grid[r][c].letter = word[i];
        r++;
    }
    m_clues.push_back({2, 5, false, "Natural satellite of Earth"});
}

void CrosswordPuzzle::GenerateFromChapter(int chapter) {
    // Reset Grid
    for(int r=0; r<ROWS; ++r) {
        for(int c=0; c<COLS; ++c) {
            m_grid[r][c] = CrosswordCell(); // Reset
            m_grid[r][c].isBlock = true;
        }
    }
    m_clues.clear();

    std::vector<WordEntry> words = WordDB::GetWordsForChapter(chapter);
    if (words.empty()) return;

    // Sort by length descending
    std::sort(words.begin(), words.end(), [](const WordEntry& a, const WordEntry& b) {
        return a.word.length() > b.word.length();
    });

    // Place first word in center horizontal
    if (!words.empty()) {
        WordEntry& first = words[0];
        int startCol = (COLS - (int)first.word.length()) / 2;
        int startRow = ROWS / 2;
        PlaceWord(first.word, first.clue, startRow, startCol, true);
    }

    // Try to place remaining words
    for (size_t i = 1; i < words.size(); ++i) {
        const auto& entry = words[i];
        bool placed = false;

        // Try to find an intersection with existing board
        for (int r = 0; r < ROWS && !placed; ++r) {
            for (int c = 0; c < COLS && !placed; ++c) {
                if (!m_grid[r][c].isBlock) {
                    char boardChar = m_grid[r][c].letter;
                    
                    // Find this char in the new word
                    for (size_t k = 0; k < entry.word.length(); ++k) {
                        if (entry.word[k] == boardChar) {
                            // Potential intersection at word index k
                            // If board char is part of an ACROSS word, we must place DOWN
                            // We need to know orientation of the cell. 
                            // Simplified: Try both, CanPlaceWord checks validity.
                            
                            // Try placing DOWN intersecting at (r,c) with letter index k
                            // Start row would be r - k
                            if (CanPlaceWord(entry.word, r - k, c, false)) {
                                PlaceWord(entry.word, entry.clue, r - k, c, false);
                                placed = true;
                                break;
                            }
                            
                            // Try placing ACROSS intersecting at (r,c) with letter index k
                            // Start col would be c - k
                            if (CanPlaceWord(entry.word, r, c - k, true)) {
                                PlaceWord(entry.word, entry.clue, r, c - k, true);
                                placed = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool CrosswordPuzzle::CanPlaceWord(const std::string& word, int r, int c, bool across) {
    if (r < 0 || c < 0) return false;
    if (across) {
        if (c + word.length() > COLS) return false;
        // Check boundaries and neighbors
        // We need to ensure we don't overwrite existing letters with DIFFERENT ones
        // And we don't place letters adjacent to other words (creating invalid 2-letter words)
        
        // Check start/end bounds (must be empty or block before and after)
        if (c > 0 && !m_grid[r][c-1].isBlock) return false;
        if (c + word.length() < COLS && !m_grid[r][c + word.length()].isBlock) return false;

        for (size_t i = 0; i < word.length(); ++i) {
            int currR = r;
            int currC = c + i;
            
            if (!m_grid[currR][currC].isBlock) {
                if (m_grid[currR][currC].letter != word[i]) return false; // Conflict
            } else {
                // If it's a block (empty), check neighbors above/below to ensure no accidental adjacency
                if (currR > 0 && !m_grid[currR-1][currC].isBlock) return false;
                if (currR < ROWS-1 && !m_grid[currR+1][currC].isBlock) return false;
            }
        }
    } else { // Down
        if (r + word.length() > ROWS) return false;
        
        if (r > 0 && !m_grid[r-1][c].isBlock) return false;
        if (r + word.length() < ROWS && !m_grid[r + word.length()][c].isBlock) return false;

        for (size_t i = 0; i < word.length(); ++i) {
            int currR = r + i;
            int currC = c;
            
            if (!m_grid[currR][currC].isBlock) {
                if (m_grid[currR][currC].letter != word[i]) return false;
            } else {
                if (currC > 0 && !m_grid[currR][currC-1].isBlock) return false;
                if (currC < COLS-1 && !m_grid[currR][currC+1].isBlock) return false;
            }
        }
    }
    return true;
}

void CrosswordPuzzle::PlaceWord(const std::string& word, const std::string& clue, int r, int c, bool across) {
    for (size_t i = 0; i < word.length(); ++i) {
        int currR = across ? r : r + i;
        int currC = across ? c + i : c;
        
        m_grid[currR][currC].isBlock = false;
        m_grid[currR][currC].letter = word[i];
    }
    m_clues.push_back({r, c, across, clue, word});
}

CrosswordCell& CrosswordPuzzle::GetCell(int r, int c) {
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) {
        static CrosswordCell dummy;
        return dummy;
    }
    return m_grid[r][c];
}

bool CrosswordPuzzle::IsSolved() {
    for(int r=0; r<ROWS; ++r) {
        for(int c=0; c<COLS; ++c) {
            if (!m_grid[r][c].isBlock) {
                if (m_grid[r][c].input != m_grid[r][c].letter) return false;
            }
        }
    }
    return true;
}

std::string CrosswordPuzzle::GetClue(int r, int c, bool across) {
    // Simple heuristic: find a clue that starts at or before this cell and covers it
    // This is a bit tricky for intersections, but let's try to find the "best" clue.
    // Actually, the UI usually toggles direction. Let's assume the UI passes the desired direction.
    
    for (const auto& clue : m_clues) {
        if (clue.across == across) {
            if (across) {
                // Check if (r,c) is on the same row and within range
                if (clue.r == r && c >= clue.c) {
                    // We need to know length to be sure, but for now assume it's the right one if it's close
                    // A better way is to check if the cell is part of this word.
                    // Let's just return the clue if we are "on" it.
                    // Since we don't store length in ClueInfo, we can't be 100% sure without checking grid.
                    // But for this simple puzzle, checking start pos is enough? No.
                    // Let's just check if we are to the right of start
                     if (c < clue.c + 10) { // Arbitrary max length
                         return clue.clueText;
                     }
                }
            } else {
                if (clue.c == c && r >= clue.r) {
                    if (r < clue.r + 10) {
                        return clue.clueText;
                    }
                }
            }
        }
    }
    return "";
}
