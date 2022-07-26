#pragma once
#ifndef _UTILS_HPP_
#define _UTILS_HPP_
#include <string>
#include <cstddef>

namespace dby
{
  class Utils
  {
    static std::size_t randSize(std::size_t bottom, std::size_t top) 
    {
      return rand() % (top - bottom + 1) + bottom;
    }
  public:
    static int randInt(int bottom, int top) 
    {
      return rand() % (top - bottom + 1) + bottom;
    }

    static char randChar(char first, char last)
    {
      return (char)(rand() % (last - first + 1) + first);
    }

    static char randUpperLetterOrDigitCharacter()
    {
      if (Utils::randInt(1, 36) <= 26) 
      {
        return Utils::randChar('A', 'Z');
      }

      return Utils::randChar('0', '9');
    }

    static std::string randString(std::size_t minLength, std::size_t maxLength)
    {
      const std::string ASCII_LETTERS_AND_DIGITS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
      const std::size_t asciiLength = 63;
      std::size_t currentLength = Utils::randSize(minLength, maxLength);
      std::string str = "";

      for (int i = 0; i < currentLength; ++i)
      {
        str += ASCII_LETTERS_AND_DIGITS.at(Utils::randInt(0, asciiLength - 1));
      }

      return str;
    }

    static bool isPrime(long long num)
    {
      for (long long i = 2; i * i <= num; ++i)
      {
        if (num % i == 0)
        {
          return false;
        }
      }
      return true;
    }

    static long long nextPrime(long long num)
    {
      if (num <= 2)
      {
        return (num != 2 ? 2 : 3);
      }

      long long init, end, ans;

      init = num + 1 + (num % 2);
      end = 2 * init - 2;

      for (ans = init; ans < end; ans = ans + 2)
      {
        if (Utils::isPrime(ans))
        {
          break;
        }
      }

      return ans;
    }
  };
}

#endif