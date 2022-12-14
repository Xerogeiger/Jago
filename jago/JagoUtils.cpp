//
// Created by creep on 12/13/2022.
//

#include "JagoUtils.h"

bool Jago::IsNumber(char c) {
    return c >= '0' && c <= '9';
}

bool Jago::StringEquals(const std::string_view& left, const std::string_view& right) {
    if(left.length() != right.length())
        return false;
    if(left.length() == 0) //Since the right and left strings have the same length if left is empty so is right
        return false;

    for(uint32_t i = 0; i < left.length(); i++) {
        if(left[i] != right[i])
            return false;
    }

    return true;
}

bool Jago::IsSymbol(std::string value, uint32_t from, uint32_t to, std::string symbol) {
    if(symbol.length() == 0 || from == to)
        return false;
    if(from + symbol.length() >= to)
        return false;

    for(uint32_t i = 0; i < symbol.length(); i++) {
        if(symbol[i] != value[from + i])
            return false;
    }

    return true;
}

[[maybe_unused]] void Jago::Char::QuickSort(void *arr, std::uint32_t start, std::uint32_t end) {
    if(start < 0)
        throw std::invalid_argument("Start for QuickSort should not be less than 0");
    if(end < 0)
        throw std::invalid_argument("End for QuickSort should not be less than 0");
    if(end < start)
        throw std::invalid_argument("End for QuickSort should not be less than the start");

    if(start == end)
        return;

    Internal::QuickSortNoCheck<char>(arr, static_cast<std::int32_t>(start), static_cast<std::int32_t>(end)-1);
}

[[maybe_unused]] void Jago::Char::QuickSort(void *arr, std::uint32_t length) {
    QuickSort(arr, 0, length);
}

[[maybe_unused]] void Jago::Char::QuickSort(std::vector<char>& chars, std::uint32_t start, std::uint32_t end) {
    uint32_t len = chars.size();

    if(start > len)
        throw std::invalid_argument("Start of vector for QuickSort should be less than the length");
    if(end > len)
        throw std::invalid_argument("End of vector for QuickSort should be less than the length");

    QuickSort(chars.data(), start, end);
}

[[maybe_unused]] void Jago::Char::QuickSort(std::vector<char>& chars) {
    QuickSort(chars.data(), 0, chars.size());
}

std::int32_t PartitionForLength(std::vector<std::string> &strings, std::int32_t low, std::int32_t high) {
    std::string pivot = strings[high];

    std::int32_t i = (low - 1);

    for(std::int32_t j = low; j < high; j++) {
        if(strings[j].length() > pivot.length()) {
            i++;
            std::swap(strings[i], strings[j]);
        }
    }

    std::swap(strings[i+1], strings[high]);

    return (i+1);
}

void QuickSortForLength(std::vector<std::string> &strings, std::int32_t low, std::int32_t high) {
    if(low < high) {
        std::int32_t p = PartitionForLength(strings, low, high);

        QuickSortForLength(strings, low, p - 1);
        QuickSortForLength(strings, p + 1, high);
    }
}

[[maybe_unused]] void Jago::SortByLength(std::vector<std::string> &strings) {
    if(strings.empty())
        return;

    QuickSortForLength(strings, 0, static_cast<int32_t>(strings.size())-1);
}
