# 🩵 Donation Management System (C Language)

This project is a **Donation Management System** written in C.  
It allows an admin to:
- Register donors
- Record donations
- View donation history
- Log fund usage
- View fund usage records  

It uses:
- **File handling** to store and retrieve data.
- A **linked list** to manage donors in memory.
- A simple **login system** for access control.

---

## 📂 Files Used

| File Name | Purpose |
|------------|----------|
| `donors.txt` | Stores donor information |
| `donations.txt` | Stores donation transaction history |
| `fund_usage.txt` | Stores fund usage logs |

---

## 🧠 Code Explanation (Line-by-Line)

### 1. Header Inclusions
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
```
- **stdio.h** → for input/output (e.g., `printf`, `scanf`, `fopen`)
- **stdlib.h** → for memory functions (`malloc`, `free`) and exit controls.
- **string.h** → for string manipulation functions like `strcmp`, `strcpy`, `fgets`.
- **time.h** → to get the current date/time for logging.

---

### 2. File Name Macros
```c
#define DONOR_FILE "donors.txt"
#define DONATION_FILE "donations.txt"
#define FUND_FILE "fund_usage.txt"
```
- Defines constants (macros) for filenames to avoid hardcoding file names multiple times.

---

### 3. Donor Structure (Linked List Node)
```c
typedef struct Donor {
    char donorId[20];
    char name[50];
    char email[50];
    double totalDonated;
    struct Donor* next;
} Donor;
```
- Defines the **Donor** data type.
- Contains donor details and a pointer `next` to the next donor (linked list node).

---

### 4. Global Pointer to Head of Linked List
```c
Donor* donorList = NULL;
```
- Keeps track of the first node (head) of the donor linked list.

---

### 5. Utility Functions

#### (a) `trimNewline`
```c
void trimNewline(char* str) {
    str[strcspn(str, "\n")] = 0;
}
```
- Removes the trailing newline (`\n`) from strings read by `fgets`.

#### (b) `pauseScreen`
```c
void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
}
```
- Pauses execution so the user can read messages before continuing.

---

### 6. File Handling Functions

#### (a) `loadDonors`
Reads donors from the file and loads them into a linked list.

#### (b) `saveDonors`
Writes all donors from the linked list back to the file.

---

### 7. Donor Search
Searches the linked list to find a donor by their ID.

---

### 8. Registering a New Donor
Prompts for donor details, validates uniqueness, and adds the new donor to the linked list and file.

---

### 9. Logging Donations
Appends donation records to `donations.txt` with a timestamp.

---

### 10. Adding a Donation
Finds the donor, updates total donated amount, saves, and logs the transaction.

---

### 11. Logging Fund Usage
Records purpose and amount of fund usage in `fund_usage.txt`.

---

### 12. Viewing Donations
Displays all donations made by a particular donor.

---

### 13. Viewing Fund Usage
Prints all fund usage records from `fund_usage.txt`.

---

### 14. Login System
Allows access only for the admin user (`admin` / `admin123`).

---

### 15. Main Menu
Displays options and routes user choices to appropriate functions.

---

### 16. Main Function
Initializes data, handles login, and starts the main menu loop.

---

## 🔗 Linked List Summary

| Operation | Function | Description |
|------------|-----------|-------------|
| Create Node | `registerDonor()` | Adds a new donor to the list |
| Load List | `loadDonors()` | Loads donors from file into linked list |
| Save List | `saveDonors()` | Writes linked list back to file |
| Search Node | `findDonor()` | Finds a donor by ID |
| Traverse | `saveDonors()`, `findDonor()` | Loops through each donor |

---

## 🧾 Example Console Output
```
=== Donation System Login ===
Username: admin
Password: admin123

Login successful!

=== Donation Management System ===
1. Register Donor
2. Add Donation
3. View Donations
4. Log Fund Usage
5. View Fund Usage
6. Exit
Select option:
```

---

## 🧩 Concepts Used
- File I/O (`fopen`, `fclose`, `fprintf`, `fscanf`, `fgets`)
- Linked List (Dynamic memory, node creation, traversal)
- String handling (`fgets`, `strcmp`, `strcpy`)
- Time handling (`time`, `ctime`)
- Basic authentication
- Menu-driven console interface

---

## 🪶 Author
**Janhavi Sharma**  
*(Project: Donation Management System — Linked List + File Handling in C)*
