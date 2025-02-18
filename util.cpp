#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <functional>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> words;
    string word;
    for (unsigned int i = 0; i < rawWords.size(); i++) {
        if (ispunct(rawWords[i]) || isspace(rawWords[i])) {
            if (word.size() >= 2) {
                word = convToLower(word);
                words.insert(word);
            }
            word = "";
        } else {
            word += rawWords[i];
        }
    }
    
    if (word.size() >= 2) {
        word = convToLower(word);
        words.insert(word);
    }
    return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
            std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    return s;
}

std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), 
            s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
