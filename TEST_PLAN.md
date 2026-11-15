# Test Plan

| # | Test | Expected result |
|---|---|---|
| 1 | Admin login with wrong password | "Invalid admin credentials." |
| 2 | Admin login with correct credentials | Admin menu appears |
| 3 | Register customer with empty name | Error: Name cannot be empty |
| 4 | Register customer with phone `123` | Error: Phone must be exactly 10 digits |
| 5 | Register valid customer | Customer ID shown (C1) |
| 6 | Create Savings account with balance `-5` | Error: Opening balance cannot be negative |
| 7 | Create Savings account with balance `abc` | Error: Please enter a valid number |
| 8 | Create Savings and Current accounts | Account numbers shown |
| 9 | Search account with unknown number | "Account not found." |
| 10 | Update only the phone, other fields blank | Phone changes, name and address stay |
| 11 | Customer login with wrong phone | "Invalid customer ID or phone number." |
| 12 | Customer searches another customer's account | "Account not found." |
| 13 | Invalid menu choice such as `abc` | "Invalid choice." with no crash |
| 14 | Deposit and withdraw (after integration) | Balance changes correctly |
| 15 | Withdraw more than the balance (after integration) | Error, balance unchanged |
| 16 | Transfer between two accounts (after integration) | One balance falls, one rises |
| 17 | Transaction history (after integration) | All operations are listed |
