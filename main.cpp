#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
const std::string FILENAME = "products.csv";
bool FILE_HEADER = true;
const char SEPARATOR = ',';

void printReciepts(std::vector<std::string> &salesIds,
    std::vector<std::string> &products,
    std::vector<double> &prices,
    std::vector<int> & quantities) {
    //find the max width of the product and price columns
    std::string id = "";
    int maxProductWidth = 0;
    for (std::string product : products)
        if (product.length() > maxProductWidth) maxProductWidth = product.length();
    int maxPriceWidth = 0;
    for (double price : prices)
        if (std::to_string(price).length() > maxPriceWidth) maxPriceWidth = std::to_string(price).length();
    //print the heading for sales
    std::cout << std::endl << std::right << std::setw(((maxProductWidth + maxPriceWidth) / 2) + 8) << "SALES RECIEPTS" << std::endl;
    //print out the sales receipts
    for (int i = 0; i < salesIds.size(); i++) {
        //if the id is new then create an id heading
        if (id != salesIds[i]) {
            std::cout << "Sale-" << salesIds[i];
            for (int j = 0; j < maxPriceWidth + maxProductWidth - 2; j++)
                std::cout << "-";
            std::cout << std::endl;
            id = salesIds[i];
        }
        //print the current items from the vectors
        std::cout << "  " << std::left << std::setw(maxProductWidth) << products[i]
            << " " << quantities[i] << " " << std::right << std::setw(maxPriceWidth + 2)
            << std::fixed <<  std::setprecision(2) << prices[i] << std::endl;
    }
}


int main() {
    //try to open the file
    std::ifstream file(FILENAME);
    //if the file fails to open, notify and close
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    //if the file is opened, continue
    //variables to service the program
    std::vector<std::string> products;
    std::vector<double> prices;
    std::vector<std::string> salesIds;
    std::vector<int> quantities;
    std::stringstream ss;
    std::string line, salesId, product, qtyStr, priceStr;

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
    printReciepts(salesIds, products, prices, quantities);

    return 0;
}
