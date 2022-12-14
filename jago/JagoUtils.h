//
// Created by creep on 12/13/2022.
//

#ifndef JAGO_JAGOUTILS_H
#define JAGO_JAGOUTILS_H

#include <vector>
#include <cstdint>
#include <exception>
#include <stdexcept>
#include <iostream>

namespace Jago {
    bool IsSymbol(std::string value, uint32_t from, uint32_t to, std::string symbol);
    bool StringEquals(const std::string_view& left, const std::string_view& right);
    bool IsNumber(char c);

    namespace Internal {
        template<typename T>
        int BinarySearchInternal(T *arr, int low, int high, T value);
    }

    template<typename T>
    [[maybe_unused]] int BinarySearch(T* arr, std::uint32_t length, T value);
    template<typename T>
    [[maybe_unused]] int BinarySearch(std::vector<T> arr, T value);
    template<typename T>
    [[maybe_unused]] int BinarySearch(T* arr, std::uint32_t from, std::uint32_t to, T value);
    template<typename T>
    [[maybe_unused]] int BinarySearch(std::vector<T> arr, std::uint32_t from, std::uint32_t to, T value);

    template<typename T>
    [[maybe_unused]] bool Contains(T* arr, int length, T value);
    template<typename T>
    [[maybe_unused]] bool Contains(std::vector<char> arr, T value);

    [[maybe_unused]] void SortByLength(std::vector<std::string>& strings);

    namespace Char {
        namespace Internal {
            template<typename T>
            std::uint32_t Partition(void *arr, std::int32_t low, std::int32_t high);

            template<typename T>
            void QuickSortNoCheck(void *arr, std::int32_t low, std::int32_t high);
        }

        [[maybe_unused]] void QuickSort(void *arr, std::uint32_t start, std::uint32_t end);
        [[maybe_unused]] void QuickSort(void *arr, std::uint32_t length);
        [[maybe_unused]] void QuickSort(std::vector<char>& chars, std::uint32_t start, std::uint32_t end);
        [[maybe_unused]] void QuickSort(std::vector<char>& chars);
    }
}

template<typename T>
int Jago::Internal::BinarySearchInternal(T *arr, int low, int high, T value) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == value)
            return mid;

        if (arr[mid] > value)
            return BinarySearchInternal(arr, low, mid - 1, value);

        return BinarySearchInternal(arr, mid + 1, high, value);
    }

    return -1;
}

template<typename T>
[[maybe_unused]] int Jago::BinarySearch(T *arr, std::uint32_t length, T value) {
    if(length == 0)
        return -1;

    return Jago::Internal::BinarySearchInternal(arr, 0, static_cast<int>(length)-1, value);
}

template<typename T>
[[maybe_unused]] int Jago::BinarySearch(std::vector<T> arr, T value) {
    if(arr.empty())
        return -1;

    return Jago::Internal::BinarySearchInternal(arr.data(), 0, static_cast<int>(arr.size())-1, value);
}

template<typename T>
[[maybe_unused]] int Jago::BinarySearch(T *arr, std::uint32_t from, std::uint32_t to, T value) {
    if(from == to)
        return -1;

    return Jago::Internal::BinarySearchInternal(arr, from, to-1, value);
}

template<typename T>
[[maybe_unused]] int Jago::BinarySearch(std::vector<T> arr, std::uint32_t from, std::uint32_t to, T value) {
    if(from == to)
        return -1;

    return Jago::Internal::BinarySearchInternal(arr.data(), from, to-1, value);
}

template<typename T>
[[maybe_unused]] bool Jago::Contains(T *arr, int length, T value) {
    return BinarySearch(arr, length, value) != -1;
}

template<typename T>
[[maybe_unused]] bool Jago::Contains(std::vector<char> arr, T value) {
    return BinarySearch(arr, value) != -1;
}

template<typename T>
std::uint32_t Jago::Char::Internal::Partition(void *arr, std::int32_t low, std::int32_t high) {
    T* typedArray = ((T*)arr);

    T pivot = typedArray[high];

    std::uint32_t i = (low - 1);

    for(std::uint32_t j = low; j < high; j++) {
        if(typedArray[j] <= pivot) {
            i++;
            std::swap(typedArray[i], typedArray[j]);
        }
    }

    std::swap(typedArray[i+1], typedArray[high]);

    return (i+1);
}

template<typename T>
void Jago::Char::Internal::QuickSortNoCheck(void *arr, std::int32_t low, std::int32_t high) {
    if(low < high) {
        std::uint32_t p = Partition<T>(arr, low, high);

        QuickSortNoCheck<T>(arr, low, p - 1);
        QuickSortNoCheck<T>(arr, p + 1, high);
    }
}

template <typename T>
void PrintArray(std::vector<T> arr) {
    std::cout << "[";

    for(int i = 0; i < arr.size(); i++) {
        if(i != 0)
            std::cout << ", ";

        std::cout << "\"" << arr[i] << "\"";
    }

    std::cout << "]" << std::endl;
}

#endif //JAGO_JAGOUTILS_H
