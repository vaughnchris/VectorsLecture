#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "utilities.h"

int main() {
    //variables to service the program
    std::vector<std::string> salesIds;
    std::vector<std::string> products;
    std::vector<int> quantities;
    std::vector<double> prices;
    //load the data or quit
    if (!loadSalesData(FILENAME, salesIds,
        products, quantities, prices)) {
        std::cout << "Check data file and reload" << std::endl;
        return -1;
    }
    //print the basic data that is in the file prettyfied
    printSalesData(salesIds, products, quantities, prices);
    //create a vector full of total sales (1 for each sales Id)
    std::vector<double> salesTotals =
        calculateSalesTotals(salesIds, products, quantities, prices);
    //use that to run an overloaded print that prints totals
    printSalesData(salesIds, products, quantities, prices, salesTotals);
    return 0;
}
