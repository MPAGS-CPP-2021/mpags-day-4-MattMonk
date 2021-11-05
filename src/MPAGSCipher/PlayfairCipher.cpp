#include "PlayfairCipher.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

PlayfairCipher::PlayfairCipher(const std::string& key)
{
    this->setKey(key);
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
    // Change J -> I
    
    // Remove duplicated letters
    
    // Store the coords of each letter
    
    // Store the playfair cihper key map
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