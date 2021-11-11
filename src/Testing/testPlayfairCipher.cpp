//! Unit Tests for MPAGSCipher PlayfairCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PlayfairCipher.hpp"

TEST_CASE("Caesar Cipher encryption", "[caesar]")
{
    PlayfairCipher cc{"playfair"};
    REQUIRE(cc.applyCipher("HELLOWORLD", CipherMode::Encrypt) == "KGYVRVVQGRMF");
}

TEST_CASE("Caesar Cipher decryption", "[caesar]")
{
    PlayfairCipher cc{"playfair"};
    REQUIRE(cc.applyCipher("KGYVRVVQGRMF", CipherMode::Decrypt) == "HELXLOWORLDZ");
}