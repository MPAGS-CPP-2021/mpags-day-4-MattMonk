#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include "CipherMode.hpp"

#include <cstddef>
#include <string>
#include <vector>
#include <map>

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */
class PlayfairCipher {
  public:
    /**
     * \brief Create a new PlayfairCipher with the given key (placeholder for now)
     *
     * \param key the key to use in the cipher
     */
    explicit PlayfairCipher(const std::string& key);

    /**
     * \brief Set the private key for the PlayfairCipher
     * 
     * \param key the key to use in the cipher
     */
      void setKey(const std::string& key);

    /**
     * \brief Apply the cipher to the provided text (placeholder for now)
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher(const std::string& inputText,
                            const CipherMode cipherMode);
    
    /**
     * \brief Convert all occurences of char 'J' in a string to 'I'
     * 
     * \param inputText the string to be modified such that J->I
     */ 
    void changeJstoIs(std::string& inputText);

  private:
    /// The length of the grid in 1D
    const size_t gridLength_{5};
    /// The size of the grid (square grid)
    const size_t gridSize_{gridLength_*gridLength_};
    /// The cipher key, a string in this case
    std::string key_{0};
    /// The alphabet to append to the key
    const std::string alphabet_{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    /// The map from letter -> coordinates
    using Char2IntPairMap = std::map<char, std::pair<int, int>>;
    Char2IntPairMap letterToCoords_;
    /// The map from coordinates -> letter
    using IntPair2CharMap = std::map<std::pair<int, int>, char>;
    IntPair2CharMap coordsToLetter_;
};

#endif