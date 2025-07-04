#ifndef GBFIGHTER_CORE_H
#define GBFIGHTER_CORE_H

#include <iostream>
#include <map>
#include <memory>
#include <stdio.h>
#include <unordered_map>
#include <vector>

template <typename T>
using unique = std::unique_ptr<T>;

template <typename T>
using shared = std::shared_ptr<T>;

template <typename T>
using weak = std::weak_ptr<T>;

template <typename T>
using vector = std::vector<T>;

template <typename keyType, typename valType, typename Pr = std::less<keyType>>
using map = std::map<keyType, valType, Pr>;

template <typename keyType, typename valType, typename hasher = std::hash<keyType>>
using unordered_map = std::unordered_map<keyType, valType, hasher>;

template<typename T>
class Singleton
{
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& getInstance()
    {
        static T instance;
        return instance;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;
};



//macro to print a message to the console
#define LOG(...) (std::cout << ... << __VA_ARGS__) << std::endl


#endif //GBFIGHTER_CORE_H
