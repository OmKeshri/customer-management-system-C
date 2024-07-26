# Customer Management System / Restaurant Billing System

__This C program is a Cafe Billing System designed to manage customer orders, calculate bills, apply discounts, and print receipts. The system handles order taking, item cancellation, and payment processing, making it a comprehensive solution for small cafe operations.__


# Features
- __Menu Display__: Displays a menu of available items with their prices.
- __Order Management__: Allows customers to place orders and specify quantities.
- __Cancellation__: Customers can cancel items from their orders.
- __Billing and Discount Calculation__: Calculates the total bill, applies discounts based  on the bill amount, and adds GST.
- __Receipt Printing__: Prints a detailed receipt with all order details, cancellations, and final amount including taxes.
- __Customer Information__: Records customer name, address, and mobile number.

# Files
- __Menu.txt__: Contains the menu items and their prices.
- __Order.txt__: Stores the details of the current order.
- __Delete.txt__: Stores the details of cancelled items.
- __CustomerInfo.txt__: Records customer information.

# Installation
1. Clone the repository `git clone https://github.com/OmKeshri/customer-management-system-C.git`
2. Navigate to the project directory `cd customer-management-system`
3. Compile the C prorgram `gcc customer_management_system.c -o customer_management_system`


# Usage
1. Run the compiled program `./customer_management_system`
2. Follow the on-screen prompts to place orders, cancel items, and receive your bill.

# Code Overview
- Global Variables: Variables to store billing amounts, discounts, item details, etc.
- __Functions__:
    - displayitems(): Reads and displays the menu from Menu.txt.
    - additems(): Takes customer orders and writes them to Order.txt.
    - deleteitems(): Allows customers to cancel items and writes cancellations to Delete.txt.
    - dis_count(): Applies discounts based on the total bill amount.
    - payment_mode(): Prints the final receipt with all details, including cancelled items and taxes.
- Main Function: Manages the overall flow of the program, including customer information input and calling other functions as needed.

