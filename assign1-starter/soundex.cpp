#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 * The buggy version does not consider the situation that the first character is not alphabet.
 *
 */
string removeNonLetters(string s) {
    //string result = charToString(s[0]);//buggy version
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s.at(i))) {
            result += s.at(i);
        }
    }
    return result;
}
/*This function is intended to code each letter according to Soundex.
 */
string codeBySoundex(string s){
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        if (s.at(i)=='A'||s.at(i)=='a'||s.at(i)=='E'||s.at(i)=='e'
                ||s.at(i)=='I'||s.at(i)=='i'||s.at(i)=='O'
                ||s.at(i)=='o'||s.at(i)=='U'||s.at(i)=='u'
                ||s.at(i)=='H'||s.at(i)=='h'||s.at(i)=='W'
                ||s.at(i)=='w'||s.at(i)=='Y'||s.at(i)=='y') {
            s.at(i) = '0';
        }
        else if (s.at(i)=='B'||s.at(i)=='b'||s.at(i)=='F'
                 ||s.at(i)=='f'||s.at(i)=='P'||s.at(i)=='p'
                 ||s.at(i)=='V'||s.at(i)=='v'){
            s.at(i) = '1';
        }
        else if (s.at(i)=='C'||s.at(i)=='c'||s.at(i)=='G'
                 ||s.at(i)=='g'||s.at(i)=='J'||s.at(i)=='j'
                 ||s.at(i)=='K'||s.at(i)=='k'||s.at(i)=='Q'
                 ||s.at(i)=='q'||s.at(i)=='S'||s.at(i)=='s'
                 ||s.at(i)=='X'||s.at(i)=='x'||s.at(i)=='Z'
                 ||s.at(i)=='z'){
            s.at(i) = '2';
        }
        else if (s.at(i)=='D'||s.at(i)=='d'||s.at(i)=='T'
                 ||s.at(i)=='t'){
            s.at(i) = '3';
        }
        else if (s.at(i)=='L'||s.at(i)=='l'){
            s.at(i) = '4';
        }
        else if (s.at(i)=='M'||s.at(i)=='m'||s.at(i)=='N'
                 ||s.at(i)=='n'){
            s.at(i) = '5';
        }
        else if (s.at(i)=='R'||s.at(i)=='r'){
            s.at(i) = '6';
        }
        result += s.at(i);
    }
    return result;
}
/*This function is intended to merge adjacent repeating numbers.
 */

string mergeRepeatNumbers(string s) {
    for (int i = 0; i < s.length()-1; ) {
        if (s.at(i) == s.at(i+1)) {
            //judge the boundary conditions
            if (i == 0) {
                s = s.substr(i+1);
            }
            //judge the boundary conditions
            else if (i == s.length()-2){
                s = s.substr(0,s.length()-1);
            }
            else {
                s = s.substr(0,i)+ s.substr(i+1);
            }
        }
        else {
            i++;
        }
    }
    return s;
}
/*This function is intended to remove all '0' character in the soundex.
 */
string modifyFirstCharacter(string s) {
    string firstCharacterString = charToString(toupper(removeNonLetters(s).at(0)));
    firstCharacterString = firstCharacterString.substr(0,1);
    s = firstCharacterString + mergeRepeatNumbers(codeBySoundex(removeNonLetters(s))).substr(1);
    return s;
}
//*This function is intended to remove all '0' character in the soundex.
// */
string removeZeroInSoundex(string s) {
    for (int i = 1; i < s.length();){
        if(s.at(i) =='0'){
            s = s.erase(i,1);
        }
        else{
             i++;
        }
    }
    return s;
}
/*This function is intended to fill '0' or cut the excess section to make the length of soundex exactly four.
 */
string modifySoundexLength(string s) {
    if (s.length() < 4){
    string a ="0000";
    s = s + a.substr(s.length());
    }
    else if (s.length() > 4){
        s =s.substr(0,4);
    }
    return s;
}

/* This function is to calculate the soundex of the surnames.
 */
string soundex(string s) {
    s= modifySoundexLength(removeZeroInSoundex(modifyFirstCharacter(s)));
    return s;
}


/*This function is intended to prompt the user for input the surname and
 * give the surnames with the same soundex code in the name database.
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;
    cout << endl;
    // The names in the database are now stored in the provided
    // vector named databaseNames
    while(1){
        string surname = getLine("Enter a surname (RETURN to quit): ");
        if(surname!=""){
            string nameSoundex = soundex(surname);
            cout << "Soundex code is "<< nameSoundex << endl;
            Vector<string> temp;
            for( string elem : databaseNames){
                if (soundex(elem) == nameSoundex){
                    temp.add(elem);
                }
            }
            temp.sort();
            cout << "Matches from database: "<< temp <<endl;
            cout << endl;
        }
        else{
            cout << "All done!" << endl;
            break;
        }
    }
}


/* * * * * * Test Cases * * * * * */
PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

/* * * * * * Test Cases * * * * * */
STUDENT_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
    s = "'OHara";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "9Planet";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "");
    s = "34 ' ";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "");
}

STUDENT_TEST("Test code the names by soundex.") {
    string s = "O'Hara";
    string result = codeBySoundex(removeNonLetters(s));
    EXPECT_EQUAL(result, "00060");
    s = "Planet9";
    result = codeBySoundex(removeNonLetters(s));
    EXPECT_EQUAL(result, "140503");
    s = "tl dr";
    result = codeBySoundex(removeNonLetters(s));
    EXPECT_EQUAL(result, "3436");
    s = "Curie";
    result = codeBySoundex(removeNonLetters(s));
    EXPECT_EQUAL(result, "20600");
}

STUDENT_TEST("Test removing repeating numbers in the soundex code.") {
    string s = "O'Hara";
    string result = mergeRepeatNumbers(codeBySoundex(removeNonLetters(s)));
    EXPECT_EQUAL(result, "060");
    s = "Planet9";
    result = mergeRepeatNumbers(codeBySoundex(removeNonLetters(s)));
    EXPECT_EQUAL(result, "140503");
    s = "tl dr";
    result = mergeRepeatNumbers(codeBySoundex(removeNonLetters(s)));
    EXPECT_EQUAL(result, "3436");
    s = "Curie";
    result = mergeRepeatNumbers(codeBySoundex(removeNonLetters(s)));
    EXPECT_EQUAL(result, "2060");
    s = "Cugjdtlm";
    result = mergeRepeatNumbers(codeBySoundex(removeNonLetters(s)));
    EXPECT_EQUAL(result, "202345");
}

STUDENT_TEST("Test modifying the first character in the soundex code.") {
    string s = "O'Hara";
    string result = modifyFirstCharacter(s);
    EXPECT_EQUAL(result, "O60");
    s = "Planet9";
    result = modifyFirstCharacter(s);
    EXPECT_EQUAL(result, "P40503");
    s = "tl dr";
    result = modifyFirstCharacter(s);
    EXPECT_EQUAL(result, "T436");
    s = "Curie";
    result = modifyFirstCharacter(s);
    EXPECT_EQUAL(result, "C060");
    s = "Cugjdtlm";
    result = modifyFirstCharacter(s);
    EXPECT_EQUAL(result, "C02345");
}

STUDENT_TEST("Test remove all '0' character in the soundex.") {
    string s = "O'Hara";
    string result = removeZeroInSoundex(modifyFirstCharacter(s));
    EXPECT_EQUAL(result, "O6");
    s = "Planet9";
    result = removeZeroInSoundex(modifyFirstCharacter(s));
    EXPECT_EQUAL(result, "P453");
    s = "tl dr";
    result = removeZeroInSoundex(modifyFirstCharacter(s));
    EXPECT_EQUAL(result, "T436");
    s = "Curie";
    result = removeZeroInSoundex(modifyFirstCharacter(s));
    EXPECT_EQUAL(result, "C6");
    s = "Cugjdtlm";
    result = removeZeroInSoundex(modifyFirstCharacter(s));
    EXPECT_EQUAL(result, "C2345");
}

STUDENT_TEST("Test modify soundex length to exactly four.") {
    string s = "O'Hara";
    string result = modifySoundexLength(removeZeroInSoundex(modifyFirstCharacter(s)));
    EXPECT_EQUAL(result, "O600");
    s = "Planet9";
    result = modifySoundexLength(removeZeroInSoundex(modifyFirstCharacter(s)));
    EXPECT_EQUAL(result, "P453");
    s = "tl dr";
    result = modifySoundexLength(removeZeroInSoundex(modifyFirstCharacter(s)));
    EXPECT_EQUAL(result, "T436");
    s = "Curie";
    result = modifySoundexLength(removeZeroInSoundex(modifyFirstCharacter(s)));
    EXPECT_EQUAL(result, "C600");
    s = "Cugjdtlm";
    result = modifySoundexLength(removeZeroInSoundex(modifyFirstCharacter(s)));
    EXPECT_EQUAL(result, "C234");
}


