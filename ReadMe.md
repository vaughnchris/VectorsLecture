# C++ Sales Data Processor & Receipt Generator

This C++ project reads sales data from a CSV file (`products.csv`), processes the data, calculates totals for each sale, and prints neatly formatted sales receipts to the console. It demonstrates file I/O with `ifstream`, string parsing with `stringstream`, data handling with parallel `std::vector` containers, and advanced output formatting using the `<iomanip>` library.

---

## Features

* **CSV Parsing**: Reads data from `products.csv`, correctly skipping the header row.
* **Data Integrity Check**: Includes a check in `loadSalesData` to ensure all parallel vectors (sales IDs, products, quantities, prices) are of equal size after loading, preventing corrupted data from being processed.
* **Sales Total Calculation**: The `calculateSubtotals` function correctly aggregates item prices (quantity \* price) to find the total for each unique sales ID.
* **Dynamic Output Formatting**: Automatically calculates the required column widths for products, prices, and quantities using template helper functions (`getMaxColumnWidth`) to produce aligned, readable receipts.
* **Overloaded Print Function**: Provides two versions of `printSalesData`:
  1.  A simple version that lists items under each sale.
  2.  An advanced version that includes item-level subtotals (quantity \* price) and a final, formatted "Sales Total" for each receipt.

---

## File Structure

* **`main.cpp`**: The main driver of the program. It initializes the data vectors, calls `loadSalesData` to populate them, and then calls `calculateSubtotals` and `printSomeSalesData` to process and display the results.
* **`utilities.h`**: The header file defining all function prototypes, global constants (like `SEPARATOR`), and the helper template functions (`getMaxColumnWidth`) used for formatting.
* **`utilities.cpp`**: The implementation file containing the complete logic for `loadSalesData`, `calculateSubtotals`, and both `printSalesData` functions.
* **`products.csv`**: The sample input data file containing sales records.

---

## How to Compile & Run

### Compilation

You can compile this project using a C++ compiler like `g++`. Make sure to link both `.cpp` files.

```bash
# Compile the main program and utility functions
g++ main.cpp utilities.cpp -o sales_reporter -std=c++17