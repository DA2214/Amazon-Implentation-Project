#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> intersectionSet;
    typename std::set<T>::iterator it1 = s1.begin();
    typename std::set<T>::iterator it2 = s2.begin();

    while(it1 != s1.end() && it2 != s2.end()){
        if (*it1 == *it2){
            intersectionSet.insert(*it1);
            it1++;
            it2++;
        }
        else if (*it1 < *it2){
            it1++;
        }
        else{
            it2++;
        }
    }
   
    return intersectionSet;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> unionSet;
    typename std::set<T>::iterator it1 = s1.begin();
    typename std::set<T>::iterator it2 = s2.begin();

    while(it1 != s1.end() && it2 != s2.end()){
        if (*it1 == *it2){
            unionSet.insert(*it1);
            it1++;
            it2++;
        }
        else if (*it1 < *it2){
            unionSet.insert(*it1);
            it1++;
        }
        else{
            unionSet.insert(*it2);
            it2++;
        }
    }
    
    return unionSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
