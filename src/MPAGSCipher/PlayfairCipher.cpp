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
        row = i / gridLength_;
        column = i % gridLength_;
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
    const CipherMode cipherMode )
{
    std::string outputText {""};
    // Change J → I
    std::string newText = inputText;
    //To do this, I had to make applyCipher no longer const,
    //although I don't really understand why
    this->changeJstoIs(newText);
    // If repeated chars in a digraph add an X or Q if XX
    std::string pairedText{newText[0]};
    char currentChar{'x'};
    char lastChar{newText[0]};
    for(std::size_t i{1};i<newText.length();i++)
    {
        currentChar = newText[i];
        lastChar = newText[i-1];
        //Only worried about digraphs having repeated letter
        //if its the second (odd) letter in the pair, except
        //if it's the last character in the string which will
        //have a Z appended if it's odd overall
        if (i%2 != 0 && i != newText.length()-1)
        {
            if (currentChar != lastChar)
            {
                pairedText += currentChar;
            }
            else
            {
                if (currentChar != 'X')
                {
                    pairedText += 'X';
                    pairedText += currentChar;
                }
                else
                {
                    pairedText += 'Q';
                    pairedText += currentChar;
                }
            }
        }
        else
        {
            pairedText += currentChar;
        }
    }
    // if the size of input is odd, add a trailing Z
    if (pairedText.length()%2 != 0) pairedText += 'Z';
    
    // Loop over the input in Digraphs
    std::pair<int, int> coords1{0,0};
    std::pair<int, int> coords2{0,0};
    std::pair<int, int> newCoords1{0,0};
    std::pair<int, int> newCoords2{0,0};
    for (std::size_t i{0}; i<pairedText.length(); i+=2)
    {
        //   - Find the coords in the grid for each digraph
        char letter1{pairedText[i]};
        char letter2{pairedText[i+1]};
        auto l2cIter1 = letterToCoords_.find(letter1);
        //Check it is not pointing to the end of the container
        //i.e. not in the container
        auto l2cIter2 = letterToCoords_.find(letter2);
        if(l2cIter1 == letterToCoords_.end() || l2cIter2 == letterToCoords_.end()) std::cerr << "[Error] Letter not found in Letter->Coordinates map." ;
        coords1 = (*l2cIter1).second;
        coords2 = (*l2cIter2).second;
        //   - Apply the rules to these coords to get 'new' coords
        //First, check to see if they are in the same row
        if(coords1.first == coords2.first)
        {
            newCoords1.first = coords1.first;
            newCoords2.first = coords2.first;
            switch (cipherMode)
            {
                case CipherMode::Encrypt:
                    newCoords1.second = (coords1.second + 1) % gridLength_;
                    newCoords2.second = (coords2.second + 1) % gridLength_;
                    break;
                case CipherMode::Decrypt:
                    newCoords1.second = (coords1.second + gridLength_ - 1) % gridLength_;
                    newCoords2.second = (coords2.second + gridLength_ - 1) % gridLength_;
                    break;
            }
        }
        //Check if they are in the same column
        else if(coords1.second == coords2.second)
        {
            newCoords1.second = coords1.second;
            newCoords2.second = coords2.second;
            switch (cipherMode)
            {
                case CipherMode::Encrypt:
                    newCoords1.first = (coords1.first + 1) % gridLength_;
                    newCoords2.first = (coords2.first + 1) % gridLength_;
                    break;
                case CipherMode::Decrypt:
                    newCoords1.first = (coords1.first + gridLength_ - 1) % gridLength_;
                    newCoords2.first = (coords2.first + gridLength_ - 1) % gridLength_;
                    break;
            }
        }
        //Otherwise, must be in a rectangle
        else
        {
            newCoords1.first = coords1.first;
            newCoords2.first = coords2.first;
            //Symmetric under encryption/decryption
            newCoords1.second = coords2.second;
            newCoords2.second = coords1.second;
        }
        //   - Find the letter associated with the new coords
        auto c2lIter1 = coordsToLetter_.find(newCoords1);
        //Check it is not pointing to the end of the container
        //i.e. not in the container
        auto c2lIter2 = coordsToLetter_.find(newCoords2);
        if(c2lIter1 == coordsToLetter_.end() || c2lIter2 == coordsToLetter_.end()) std::cerr << "[Error] Coordinates not found in Coordinates->Letters map." ;
        outputText += (*c2lIter1).second;
        outputText += (*c2lIter2).second;
    }
    // return the text
    return outputText;
    /*
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
    std::cout << "Modified text = " << pairedText << std::endl;
    return inputText;
    */
}