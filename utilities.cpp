//
// Created by Christopher Vaughn on 10/26/25.
//
#include "utilities.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>

bool loadSalesData(const std::string& filename,
                   std::vector<std::string>& salesIds,
                   std::vector<std::string>& products,
                   std::vector<int>& quantities,
                   std::vector<double>& prices) {

    std::stringstream ss;
    std::string line, salesId, product, qtyStr, priceStr;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return false;
    }
    // Skip header
    if (FILE_HEADER) std::getline(file, line);

    // Read in a line of data until either there is no data
    // or the maximum number of products is reached. (MAX_PRODUCTS)
    while (std::getline(file, line)) {
        //clear out the stream for new input
        ss.clear();
        //load the line into the stream
        ss.str(line);
        //read each sales item from the file into its temporary variables
        //and if that succeeds, then place the values in their vectors
        if (std::getline(ss, salesId, SEPARATOR) &&
            std::getline(ss, product, SEPARATOR) &&
            std::getline(ss, qtyStr, SEPARATOR) &&
            std::getline(ss, priceStr)) {
            salesIds.push_back(salesId);
            products.push_back(product);
            quantities.push_back(std::stoi(qtyStr));
            //convert the string into a float
            prices.push_back(std::stod(priceStr));
            }
    }
    //close the file
    file.close();
    // --- NEW DATA INTEGRITY CHECK ---
    const size_t s = salesIds.size(); // Use size_t for sizes
    bool sizes_match = (s == products.size()) &&
                       (s == quantities.size()) &&
                       (s == prices.size());

    if (!sizes_match) {
        std::cerr << "Error: Data file is corrupt. Vector sizes do not match." << std::endl;
        std::cerr << "  Sales IDs: " << salesIds.size() << std::endl;
        std::cerr << "  Products:  " << products.size() << std::endl;
        std::cerr << "  Quantities:" << quantities.size() << std::endl;
        std::cerr << "  Prices:    " << prices.size() << std::endl;
        return false; // Exit with an error
    }
    return true;
}

void printSalesData(const std::vector<std::string>& salesIds,
    const std::vector<std::string>& products,
    const std::vector<int>& quantities,
    const std::vector<double>& prices) {

    //get the max width for each field
    int maxProductWidth = getMaxColumnWidth(products);
    int maxPriceWidth = getMaxColumnWidth(prices);
    //keep track of the current sales id being printed
    std::string id = "";
    //print the tape heading
    std::cout << std::endl << std::right <<
        std::setw(((maxProductWidth + maxPriceWidth) / 2) + 8) <<
            "SALES RECIEPTS" << std::endl;
    //print out the sales receipts
    for (int i = 0; i < salesIds.size(); i++) {
        //if the id is a new id number then create a sales id heading
        if (id != salesIds[i]) {
            std::cout << "Sale-" << salesIds[i];
            for (int j = 0; j < maxPriceWidth + maxProductWidth - 2; j++)
                std::cout << "-";
            std::cout << std::endl;
            id = salesIds[i];
        } //end of sales id heading

        //print the current item data from there vectors
        std::cout << "  " << std::left << std::setw(maxProductWidth)
        << products[i] << " " << quantities[i] << " "
        << std::right << std::setw(maxPriceWidth + 2)
        << std::fixed <<  std::setprecision(2) << prices[i] << std::endl;
    }
}

void printSalesData(const std::vector<std::string> &salesIds,
    const std::vector<std::string> &products,
    const std::vector<int> &quantities,
    const std::vector<double> &prices,
    const std::vector<double> &salesTotals) {
    //get the max width for each field
    int maxProductWidth = getMaxColumnWidth(products);
    int maxPriceWidth = getMaxColumnWidth(prices);
    int maxQuantityWidth = getMaxColumnWidth(quantities);
    int maxSaleTotalWidth = getMaxColumnWidth(salesTotals);
    //keep track of the current sales id being printed
    std::vector<double> subTotals;
    double totalSales = 0;
    for (int i = 0; i < salesIds.size(); i++) {
        subTotals.push_back(quantities[i]*prices[i]);
        totalSales += subTotals[i];
    }
    int maxSubTotalWidth = getMaxColumnWidth(subTotals);
    int totalWidth = maxPriceWidth + maxQuantityWidth + maxSubTotalWidth + maxProductWidth;

    std::string id = "";
    int totalPos = 0;
    //print the tape heading
    std::cout << std::endl << std::right <<
        std::setw((totalWidth / 2)) <<
            "SALES RECEIPTS" << std::endl;
    //print out the sales receipts
    for (int i = 0; i < salesIds.size(); i++) {
        //if the id is a new id number then create a sales id heading
        if (id != salesIds[i]) {
            if (i >0) {
                //print the tail of the sales record

                std::cout << std::endl << std::right << std::setw(totalWidth)
               << "Sales Total: " << std::setw(maxSubTotalWidth) << salesTotals[totalPos] << std::endl;
                totalPos++;
            }
            std::cout << "Sale -" << salesIds[i];
            for (int j = 0; j < totalWidth; j++)
                std::cout << "-";
            std::cout << std::endl;
            id = salesIds[i];

        } //end of sales id heading

        //print the current item data from there vectors
        std::cout << "  " << std::left << std::setw(maxProductWidth)
        << products[i] << std::left << std::setw(maxProductWidth)
        << std::left << std::setw(maxQuantityWidth) << quantities[i] << " "
        << std::right << std::setw(maxPriceWidth + 2) <<  std::setprecision(2) << prices[i]
        << std::right << std::setw(maxSubTotalWidth + 2) << std::setprecision(2) << subTotals[i] << std::endl;
    }
    std::cout << std::endl << std::right << std::setw(totalWidth)
                << "Sales Total: " << std::setw(maxSubTotalWidth) << salesTotals[totalPos] << std::endl;
    std::cout << std::endl << std::right << std::setw(totalWidth - 1) << "TOTAL DAY'S SALE: $" << std::fixed << std::setprecision(2)
    << totalSales << std::endl;
}

std::vector<double> calculateSalesTotals(const std::vector<std::string>& salesIds,
                                        const std::vector<std::string>& products,
                                        const std::vector<int>& quantities,
                                        const std::vector<double>& prices) {
    std::vector<double> subtotals;

    // Handle case where vector is empty
    if (salesIds.empty()) {
        return subtotals;
    }
    // Start with the first item's ID and a total of 0
    std::string currentId = salesIds[0];
    double currentSubtotal = 0.0;

    for (size_t i = 0; i < salesIds.size(); i++) {

        // --- STEP 1: Check if the ID has changed ---
        // If we are on a new sales ID...
        if (currentId != salesIds[i]) {
            // ...push the (now complete) total for the *previous* ID.
            subtotals.push_back(currentSubtotal);

            // ...and reset our trackers for the new ID.
            currentSubtotal = 0.0;
            currentId = salesIds[i];
        }
        currentSubtotal += quantities[i] * prices[i];
    }
    subtotals.push_back(currentSubtotal);

    return subtotals;
}

