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
using List = std::vector<T>;

template <typename keyType, typename valType, typename Pr = std::less<keyType>>
using Map = std::map<keyType, valType, Pr>;
template <typename keyType, typename valType, typename hasher = std::hash<keyType>>
using Dictionary = std::unordered_map<keyType, valType, hasher>;

//macro to print a message to the console
#define LOG(...) (std::cout << ... << __VA_ARGS__) << std::endl


#endif //GBFIGHTER_CORE_H
