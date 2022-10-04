/**
 * File: soundex.h
 *
 * This is just here to communicate the prototype 
 * information for the functions in soundex.cpp that 
 * will be called from main.cpp
 */
#pragma once
#include <string>


void soundexSearch(std::string filepath);
std::string soundex(std::string s);
std::string removeNonLetters(std::string s);
std::string codeBySoundex(std::string s);
std::string mergeRepeatNumbers(std::string s);
std::string modifyFirstCharacter(std::string s);
