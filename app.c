#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DONOR_FILE "donors.txt"
#define DONATION_FILE "donations.txt"
#define FUND_FILE "fund_usage.txt"

typedef struct Donor {
    char donorId[20];
    char name[50];
    char email[50];
    double totalDonated;
    struct Donor* next;
} Donor;

Donor* donorList = NULL;

void trimNewline(char* str) {
    str[strcspn(str, "\n")] = 0;
}

void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
}

// ---------- File Handling ----------
void loadDonors() {
    FILE* fp = fopen(DONOR_FILE, "r");
    if (!fp) return;

    Donor temp;
    while (fscanf(fp, "%[^,],%[^,],%[^,],%lf\n", temp.donorId, temp.name, temp.email, &temp.totalDonated) == 4) {
        Donor* newDonor = (Donor*)malloc(sizeof(Donor));
        *newDonor = temp;
        newDonor->next = donorList;
        donorList = newDonor;
    }
    fclose(fp);
}

void saveDonors() {
    FILE* fp = fopen(DONOR_FILE, "w");
    if (!fp) return;
    for (Donor* d = donorList; d; d = d->next) {
        fprintf(fp, "%s,%s,%s,%.2f\n", d->donorId, d->name, d->email, d->totalDonated);
    }
    fclose(fp);
}

Donor* findDonor(const char* id) {
    for (Donor* d = donorList; d; d = d->next) {
        if (strcmp(d->donorId, id) == 0) return d;
    }
    return NULL;
}

void registerDonor() {
    char id[20], name[50], email[50];
    getchar(); // flush newline
    printf("\n=== Register Donor ===\n");
    printf("Enter Donor ID: "); fgets(id, sizeof(id), stdin); trimNewline(id);
    printf("Enter Name: "); fgets(name, sizeof(name), stdin); trimNewline(name);
    printf("Enter Email: "); fgets(email, sizeof(email), stdin); trimNewline(email);

    if (findDonor(id)) {
        printf("\nDonor ID already exists!\n");
        pauseScreen();
        return;
    }

    Donor* newDonor = (Donor*)malloc(sizeof(Donor));
    strcpy(newDonor->donorId, id);
    strcpy(newDonor->name, name);
    strcpy(newDonor->email, email);
    newDonor->totalDonated = 0;
    newDonor->next = donorList;
    donorList = newDonor;
    saveDonors();

    printf("\nDonor Registered Successfully!\n");
    pauseScreen();
}

void logDonation(const char* donorId, double amount) {
    FILE* fp = fopen(DONATION_FILE, "a");
    if (!fp) return;
    time_t now = time(NULL);
    fprintf(fp, "%s,Donated ₹%.2f on %s", donorId, amount, ctime(&now));
    fclose(fp);
}

void addDonation() {
    char id[20];
    double amount;
    getchar();
    printf("\n=== Add Donation ===\n");
    printf("Enter Donor ID: "); fgets(id, sizeof(id), stdin); trimNewline(id);

    Donor* donor = findDonor(id);
    if (!donor) {
        printf("\nDonor not found!\n");
        pauseScreen();
        return;
    }

    printf("Enter donation amount: ");
    if (scanf("%lf", &amount) != 1) {
        printf("Invalid amount!\n");
        return;
    }

    donor->totalDonated += amount;
    saveDonors();
    logDonation(id, amount);

    getchar(); // clear leftover newline
    printf("\nDonation recorded successfully!\n");
    pauseScreen();
}

void logFundUsage() {
    char purpose[100];
    double amount;
    getchar();
    printf("\n=== Log Fund Usage ===\n");
    printf("Enter Purpose: "); fgets(purpose, sizeof(purpose), stdin); trimNewline(purpose);
    printf("Enter Amount Used: ");
    if (scanf("%lf", &amount) != 1) {
        printf("Invalid amount!\n");
        return;
    }

    FILE* fp = fopen(FUND_FILE, "a");
    if (!fp) return;
    time_t now = time(NULL);
    fprintf(fp, "Used ₹%.2f for %s on %s", amount, purpose, ctime(&now));
    fclose(fp);

    getchar(); // flush newline
    printf("\nFund usage logged!\n");
    pauseScreen();
}

void viewDonations() {
    char id[20], line[200];
    getchar();
    printf("\n=== View Donations ===\n");
    printf("Enter Donor ID: ");
    fgets(id, sizeof(id), stdin); trimNewline(id);

    FILE* fp = fopen(DONATION_FILE, "r");
    if (!fp) {
        printf("\nNo donations found.\n");
        pauseScreen();
        return;
    }

    printf("\nDonation History for %s:\n", id);
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, id, strlen(id)) == 0) {
            printf("%s", line + strlen(id) + 1);
            found = 1;
        }
    }
    if (!found) printf("No records found.\n");
    fclose(fp);
    pauseScreen();
}

void viewFundUsage() {
    char line[200];
    printf("\n=== Fund Usage Records ===\n");
    FILE* fp = fopen(FUND_FILE, "r");
    if (!fp) {
        printf("No fund usage data found.\n");
        pauseScreen();
        return;
    }
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
    pauseScreen();
}

int loginScreen() {
    char user[20], pass[20];
    getchar();
    printf("=== Donation System Login ===\n");
    printf("Username: "); fgets(user, sizeof(user), stdin); trimNewline(user);
    printf("Password: "); fgets(pass, sizeof(pass), stdin); trimNewline(pass);

    if (strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0) {
        printf("\nLogin successful!\n");
        pauseScreen();
        return 1;
    } else {
        printf("\nInvalid credentials!\n");
        pauseScreen();
        return 0;
    }
}

void showMenu() {
    int choice;
    while (1) {
        printf("\n=== Donation Management System ===\n");
        printf("1. Register Donor\n");
        printf("2. Add Donation\n");
        printf("3. View Donations\n");
        printf("4. Log Fund Usage\n");
        printf("5. View Fund Usage\n");
        printf("6. Exit\n");
        printf("Select option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            getchar(); // flush
            continue;
        }

        switch (choice) {
            case 1: registerDonor(); break;
            case 2: addDonation(); break;
            case 3: viewDonations(); break;
            case 4: logFundUsage(); break;
            case 5: viewFundUsage(); break;
            case 6: printf("Exiting...\n"); return;
            default: printf("\nInvalid choice!\n"); pauseScreen();
        }
    }
}

int main() {
    loadDonors();
    if (loginScreen()) {
        showMenu();
    }
    return 0;
}

