#include "PlayfairCipher.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

PlayfairCipher::PlayfairCipher(const std::string& key)
{
    this->setKey(key);
}

void PlayfairCipher::changeJstoIs(std::string& inputText)
{
    auto jToI = [] (char c)
    {
        if (c=='J') return 'I';
        else return c;
    };
    std::transform(std::begin(inputText), std::end(inputText), std::begin(inputText), jToI);
}

void PlayfairCipher::setKey( \
    const std::string& key)
{
    // store the original key
    key_ = key;
    
    // Append the alphabet
    key_ += alphabet_;

    // Make sure the key is upper case
    std::transform(std::begin(key_), std::end(key_), std::begin(key_), ::toupper);

    // Remove non-alpha characters
    auto notIsAlpha = [] (const char c)
    {
        return !std::isalpha(c);
    };
    auto rmNotAlphaIter = std::remove_if(std::begin(key_), std::end(key_), notIsAlpha);
    key_.erase(rmNotAlphaIter, std::end(key_));

    // Change J -> I
    this->changeJstoIs(key_);

    // Remove duplicated letters
    std::string encounteredLetters{""};
    auto rmDuplicateLam = [&] (char c)
    {
        auto found = encounteredLetters.find(c);
        if (found == std::string::npos)
        {
            encounteredLetters += c;
            return false;
        }
        else return true;
    };
    auto rmDuplicateIter = std::remove_if(std::begin(key_), std::end(key_), rmDuplicateLam);
    key_.erase(rmDuplicateIter, std::end(key_));

    // Store the coords of each letter

    int row{0}, column{0};
    for (std::size_t i{0}; i<key_.length();i++)
    {
        row = i / 5;
        column = i % 5;
        std::pair<int, int> coords{row, column};
        Char2IntPairMap::value_type c2IPair {key_[i], coords};
        IntPair2CharMap::value_type i2CPair {coords, key_[i]};
        // Store the playfair cihper key map
        letterToCoords_.insert(c2IPair);
        coordsToLetter_.insert(i2CPair);
    }

}

std::string PlayfairCipher::applyCipher( \
    const std::string& inputText, \
    const CipherMode cipherMode ) const
{
    // Change J → I
    
    // If repeated chars in a digraph add an X or Q if XX
    
    // if the size of input is odd, add a trailing Z
    
    // Loop over the input in Digraphs
    
    //   - Find the coords in the grid for each digraph
    //   - Apply the rules to these coords to get 'new' coords
    //   - Find the letter associated with the new coords
    // return the text
    std::string mode {""};
    switch (cipherMode) {
                    case CipherMode::Encrypt:
                        mode += "Encrypt";
                        break;
                    case CipherMode::Decrypt:
                        mode += "Decrypt";
                        break;
                }

    std::cout << "Apply the Playfair cipher with input text: " << inputText << " and with cipher mode: " << mode << " and key: " << key_ << std::endl;
    return inputText;
}