# C++ Sales Receipt Generator

## Project Description

This is a simple C++ command-line program that reads sales data from a CSV file (`products.csv`) and generates formatted sales receipts, grouped by Sales ID, directly to the console.

The program automatically calculates column widths based on the data (product names and prices) to ensure the output is neatly aligned, regardless of string lengths.

## Features

* Parses a comma-separated values (CSV) file.
* Groups items by their `Sales ID`.
* Calculates and applies dynamic column widths for clean formatting.
* Formats and prints a readable receipt for each sale to the standard output.

## Requirements

* A C++ compiler (e.g., g++, Clang)
* The C++ Standard Library (no external libraries are needed).

## Data File Format

The program expects a `products.csv` file to be present in the same directory as the executable.

* **Columns:** The CSV file **must** follow this exact column order:
    1.  `Sales ID`
    2.  `Product Name`
    3.  `Quantity`
    4.  `Price`
* **Header:** The program is configured to skip the first line (header row) by default (controlled by the `FILE_HEADER = true` constant in `main.cpp`).
* **Delimiter:** Fields must be separated by a comma (`,`).

### Example (`products.csv`):

```csv
Sales ID,Product Name,Quantity,Price
1001,Laptop Pro X,1,1200.00
1001,Ergonomic Mouse,1,25.50
1001,Wireless Keyboard,1,75.00
1002,4K Monitor 27in,2,350.99
1002,USB-C Hub,3,15.99
1003,Noise Cancelling Headphones,1,199.99
1003,Portable SSD 1TB,1,89.50
1003,Webcam HD,1,45.00
1004,Gaming Chair Deluxe,1,299.00
1004,Smart Watch S2,1,150.00