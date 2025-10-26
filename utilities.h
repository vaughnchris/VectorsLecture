//
// Created by Christopher Vaughn on 10/26/25.
//
#pragma once

#include <string>
#include <vector>
#include <sstream>  // Added for stringstream
#include <iomanip>  // Added for setprecision, fixed
#include <vector>

// --- Global constants can also be moved here ---
const std::string FILENAME = "products.csv";
const bool FILE_HEADER = true;
const char SEPARATOR = ',';


// --- Helper Template Function for Column Width ---
// (Definitions must be in the header for templates)

/**
 * @brief Generic templated function to find the max string length of items in a vector.
 *
 * This version uses stringstream for general-purpose conversion (e.g., ints).
 */
template <typename T>
int getMaxColumnWidth(const std::vector<T>& items) {
    int maxWidth = 0;
    std::stringstream ss;
    if (items.empty()) {
        return 0;
    }
    for (const T& item : items) {
        ss.str("");  // Clear string content
        ss.clear(); // Clear error flags
        ss << item;
        int currentWidth = ss.str().length();
        if (currentWidth > maxWidth) {
            maxWidth = currentWidth;
        }
    }
    return maxWidth;
}

/**
 * @brief Template specialization for std::string.
 *
 * This is more efficient as it avoids stringstream and just uses .length().
 */
template <>
inline int getMaxColumnWidth<std::string>(const std::vector<std::string>& items) {
    int maxWidth = 0;
    if (items.empty()) {
        return 0;
    }
    for (const std::string& item : items) {
        int currentWidth = item.length();
        if (currentWidth > maxWidth) {
            maxWidth = currentWidth;
        }
    }
    return maxWidth;
}

/**
 * @brief Template specialization for double.
 *
 * This version respects the financial formatting (2 decimal places)
 * which is crucial for calculating the correct column width.
 */
template <>
inline int getMaxColumnWidth<double>(const std::vector<double>& items) {
    int maxWidth = 0;
    std::stringstream ss;
    if (items.empty()) {
        return 0;
    }
    for (double item : items) {
        ss.str("");  // Clear string content
        ss.clear(); // Clear error flags

        // Apply specific formatting for doubles
        ss << std::fixed << std::setprecision(2) << item;

        int currentWidth = ss.str().length();
        if (currentWidth > maxWidth) {
            maxWidth = currentWidth;
        }
    }
    return maxWidth;
}


/**
 * @brief Reads the sales data from the specified CSV file.
 * @return true if file was read successfully, false otherwise.
 */
bool loadSalesData(const std::string& filename,
                   std::vector<std::string>& salesIds,
                   std::vector<std::string>& products,
                   std::vector<int>& quantities,
                   std::vector<double>& prices);

/**
 * @brief Prints all sales receipts to the console with neat formatting.
 */
void printSalesData(const std::vector<std::string>& salesIds,
    const std::vector<std::string>& products,
    const std::vector<int>& quantities,
    const std::vector<double>& prices);

void printSalesData(const std::vector<std::string>& salesIds,
    const std::vector<std::string>& products,
    const std::vector<int>& quantities,
    const std::vector<double>& prices,
    const std::vector<double>& salesTotals);

std::vector<double> calculateSalesTotals(const std::vector<std::string>& salesIds,
    const std::vector<std::string>& products,
    const std::vector<int>& quantities,
    const std::vector<double>& prices);

