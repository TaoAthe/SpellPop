#include "Topics.h"
#include <cstdlib>
#include <ctime>
#include <algorithm> // For std::shuffle
#include <random>    // For std::default_random_engine

std::map<std::string, Topic> WordDB::m_topics;
std::map<int, std::vector<WordEntry>> WordDB::m_cppChapters;

void WordDB::Initialize() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // --- Existing Topics ---
    Topic astronomy;
    astronomy.name = "Astronomy";
    astronomy.words = {
        {"GANYMEDE", "Largest moon of Jupiter"},
        {"SAGITTARIUS", "Black hole at galactic center"}, 
        {"ENTROPY", "Degree of disorder"},
        {"SPECTROSCOPY", "Analysis of light spectra"},
        {"NEBULA", "Interstellar cloud of dust"},
        {"PULSAR", "Rotating neutron star"},
        {"QUASAR", "Active galactic nucleus"},
        {"ORBIT", "Curved path of a celestial object"},
        {"ECLIPSE", "Obscuring of light from a celestial body"},
        {"GALAXY", "System of stars, gas, and dust"}
    };
    m_topics["Astronomy"] = astronomy;

    Topic biology;
    biology.name = "Biology";
    biology.words = {
        {"MITOCHONDRIA", "Powerhouse of the cell"},
        {"CHIRALITY", "Molecular mirror-asymmetry"},
        {"HOMEOSTASIS", "Internal biological balance"},
        {"OSMOSIS", "Movement of solvent molecules"},
        {"ENZYME", "Biological catalyst"},
        {"GENOME", "Complete set of genes"},
        {"MITOSIS", "Cell division process"}
    };
    m_topics["Biology"] = biology;

    // --- C++ Chapters (Malik 8th Ed Placeholder Data) ---
    
    // Chapter 1: An Overview of Computers and Programming Languages
    m_cppChapters[1] = {
        {"ALGORITHM", "Step-by-step problem-solving process"},
        {"COMPILER", "Translates source code to object code"},
        {"LINKER", "Combines object code with libraries"},
        {"LOADER", "Loads executable into memory"},
        {"CPU", "Brain of the computer (Central Processing Unit)"},
        {"RAM", "Main memory (Random Access Memory)"},
        {"BIT", "Smallest unit of data (0 or 1)"},
        {"BYTE", "Sequence of 8 bits"},
        {"ASCII", "Standard character encoding scheme"},
        {"MNEMONIC", "Instruction used in assembly language"},
        {"SOURCECODE", "Program written in high-level language"},
        {"OBJECTCODE", "Machine language version of source code"},
        {"PREPROCESSOR", "Processes directives before compilation"},
        {"IDE", "Integrated Development Environment"},
        {"SYNTAX", "Grammar rules of a programming language"}
    };

    // Chapter 2: Basic Elements of C++
    m_cppChapters[2] = {
        {"VARIABLE", "Memory location with a name and type"},
        {"CONSTANT", "Value that cannot change during execution"},
        {"IDENTIFIER", "Name of a variable, function, or class"},
        {"KEYWORD", "Reserved word with special meaning"},
        {"INTEGER", "Whole number data type"},
        {"FLOAT", "Floating-point number data type"},
        {"CHAR", "Single character data type"},
        {"BOOLEAN", "True or False data type"},
        {"OPERATOR", "Symbol that performs an action (+, -, *)"},
        {"EXPRESSION", "Combination of operands and operators"},
        {"ASSIGNMENT", "Storing a value in a variable (=)"},
        {"INITIALIZATION", "Assigning a value at declaration"},
        {"COMMENT", "Text ignored by compiler (// or /* */)"},
        {"STREAM", "Sequence of characters (cin, cout)"},
        {"NAMESPACE", "Declarative region for identifiers (std)"}
    };

    // Placeholder for 3-9
    for(int i=3; i<=9; ++i) {
        m_cppChapters[i] = {
            {"PLACEHOLDER", "Content for this chapter not yet loaded"},
            {"TODO", "Please add flashcards for Chapter " + std::to_string(i)}
        };
    }
}

const Topic& WordDB::GetTopic(const std::string& name) {
    return m_topics[name];
}

std::vector<std::string> WordDB::GetTopicNames() {
    std::vector<std::string> names;
    for (const auto& pair : m_topics) {
        names.push_back(pair.first);
    }
    return names;
}

std::string WordDB::GetRandomWord(const std::string& topicName) {
    if (m_topics.find(topicName) == m_topics.end()) return "ERROR";
    const auto& words = m_topics[topicName].words;
    if (words.empty()) return "EMPTY";
    return words[std::rand() % words.size()].word;
}

std::vector<WordEntry> WordDB::GetWordsForChapter(int chapter) {
    if (m_cppChapters.find(chapter) != m_cppChapters.end()) {
        std::vector<WordEntry> words = m_cppChapters[chapter];
        // Scramble the words
        auto rng = std::default_random_engine(static_cast<unsigned int>(std::time(nullptr)));
        std::shuffle(words.begin(), words.end(), rng);
        return words;
    }
    return {};
}
