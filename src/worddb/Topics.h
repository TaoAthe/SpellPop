#pragma once
#include <string>
#include <vector>
#include <map>

struct WordEntry {
    std::string word;
    std::string clue;
};

struct Topic {
    std::string name;
    std::vector<WordEntry> words;
};

class WordDB {
public:
    static void Initialize();
    static const Topic& GetTopic(const std::string& name);
    static std::vector<std::string> GetTopicNames();
    static std::string GetRandomWord(const std::string& topicName);
    
    // New method for Chapter-based retrieval
    static std::vector<WordEntry> GetWordsForChapter(int chapter);

private:
    static std::map<std::string, Topic> m_topics;
    static std::map<int, std::vector<WordEntry>> m_cppChapters;
};
