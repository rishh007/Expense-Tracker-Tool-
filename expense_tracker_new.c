#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define FILENAME "C:/Desktop/coding/c/Data Structures/CP/expenses2.csv"
#define MAX_BAR_LENGTH 20  // max length of the horizontal percentage bar
#define CATEGORY_COUNT 8

// expense structure
typedef struct {
    char date[11];      // dd/mm/yyyy
    char category[20];  // predefined categories
    char name[50];      // name of the expense
    double amount;
} Expense;


// linked List for expenses
typedef struct ExpenseNode {
    Expense expense;
    struct ExpenseNode* next;
} ExpenseNode;

// BST for sorted expenses
typedef struct BSTNode {
    Expense data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

const char* categories[] = {"Food", "Travel", "Shopping", "Entertainment", "Bills", "Investments", "Medical", "Other"};

// Linked list and BST heads
ExpenseNode* head = NULL;
BSTNode* bstRoot = NULL;

// --- Utility Functions ---
void getCurrentDate(char* buffer) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(buffer, 11, "%d/%m/%Y", tm_info); // format: dd/mm/yyyy
}


// --- Core Functions ---
void loadExpensesFromFile() {
    
    ExpenseNode* current = head;
    while (current) {
        ExpenseNode* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
    
    bstRoot = NULL;
    
        FILE* file = fopen(FILENAME, "r");
    if (!file){

// file doesn't exist yet, which is fine for a new user
        return;
    }

    char date[11], category[20], name[50];
    double amount;

    // read each line from the file
    while (fscanf(file, "%10[^,],%19[^,],%49[^,],%lf\n", date, category, name, &amount) == 4) {
        Expense e;
        strcpy(e.date, date);
        strcpy(e.category, category);
        strcpy(e.name, name);
        e.amount = amount;

        ExpenseNode* newNode = (ExpenseNode*)malloc(sizeof(ExpenseNode));
        if (!newNode) {
            printf("Memory allocation failed!\n");
            continue;
        }
        newNode->expense = e;
        newNode->next = head;
        head = newNode;

        BSTNode* newNodeBST = (BSTNode*)malloc(sizeof(BSTNode));
        if (!newNodeBST) {
            printf("Memory allocation failed!\n");
            continue;
        }
        newNodeBST->data = e;
        newNodeBST->left = newNodeBST->right = NULL;

        if (!bstRoot){
            bstRoot = newNodeBST;
        }else{
            BSTNode* current = bstRoot;
            BSTNode* parent = NULL;
            int direction = 0; // 0 for left, 1 for right
            
            while (current) {
                parent = current;
                if (strcmp(e.date, current->data.date) < 0) {
                    current = current->left;
                    direction = 0;
                } else {
                    current = current->right;
                    direction = 1;
                }
            }
            
            if (direction == 0) {
                parent->left = newNodeBST;
            } else {
                parent->right = newNodeBST;
            }
        }
    }
    
    fclose(file);
}

void saveExpenseToFile(Expense* expense) {
    FILE* file = fopen(FILENAME, "a");  // Append mode
    if (!file) {
        printf("Error saving expense to file.\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%.2f\n", expense->date, expense->category, expense->name, expense->amount);
    fclose(file);
}

void printCategories(){
    printf("Select Category:\n");
    for (int i = 0; i < CATEGORY_COUNT; i++) {
        printf("%d. %s\n", i + 1, categories[i]);
    }
}

void addExpense(){
    Expense e;
    getCurrentDate(e.date); // date is updated 
    printCategories();
    int choice;
    do{
        printf("Enter category number: ");
        scanf("%d", &choice);
    } while(choice < 1 || choice > CATEGORY_COUNT);
    strcpy(e.category, categories[choice - 1]);

    printf("Enter expense name: ");
    getchar();  // consume leftover newline
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = '\0';  // remove newline (from fgets) by finding position and assigning '\0'

    do{ // input validation 
        printf("Enter amount: ");
        scanf("%lf", &e.amount);
        if (e.amount < 0) printf("Amount cannot be negative.\n");
    }while(e.amount < 0);

    char saveChoice;
    printf("Do you want to save this expense to file? (y/n): ");
    getchar();  // Consume leftover newline
    scanf("%c", &saveChoice);

    if (saveChoice == 'y' || saveChoice == 'Y') {
        // Step 9: Save the expense to file
        saveExpenseToFile(&e);
        printf("Expense saved to file.\n");
    } else {
        printf("Expense not saved to file.\n");
    }

    // add to SLL
    ExpenseNode* newNode = (ExpenseNode*)malloc(sizeof(ExpenseNode));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->expense = e;
    newNode->next = head;
    head = newNode;

    //add to BST
    BSTNode* newNodeBST = (BSTNode*)malloc(sizeof(BSTNode));
    if(!newNodeBST){
        printf("Memory allocation failed!\n");
        return;
    }
    newNodeBST->data = e;
    newNodeBST->left = newNodeBST->right = NULL;

    if(!bstRoot){
        bstRoot = newNodeBST;
    } else {
        BSTNode* current = bstRoot;
        BSTNode* parent = NULL;
        int direction = 0; // 0 for left, 1 for right (for easy insertion when current reaches leaf)
            
        while(current){
            parent = current;
            if(strcmp(e.date, current->data.date) < 0){
                current = current->left;
                direction = 0;
            } else {
                current = current->right;
                direction = 1;
            }
        }

        if(direction == 0){
            parent->left = newNodeBST;
        } else {
            parent->right = newNodeBST;
        }
    }

    printf("Expense added successfully!\n");
}

void viewExpenses() {
    if(!head){
        printf("No expenses to show.\n");
        return;
    }

    printf("\n%-5s %-12s %-15s %-20s %-10s\n", "No.", "Date", "Category", "Name", "Amount");
    ExpenseNode* current = head;
    int i = 1;
    while (current != NULL) {
        printf("%-5d %-12s %-15s %-20s Rs.  %.2f\n", i++, current->expense.date, current->expense.category, current->expense.name, current->expense.amount);
        current = current->next;
    }
}

void viewCategoryExpenses() {
    printf("\n--- View Expenses by Category ---\n");
    printCategories();
    int choice;
    do{
        printf("Enter category number: ");
        scanf("%d", &choice);
    }while(choice < 1 || choice > CATEGORY_COUNT); 

    const char* selectedCategory = categories[choice - 1];

    if(!head){
        printf("No expenses to show.\n");
        return;
    }

    printf("\n%-5s %-12s %-15s %-20s %-10s\n", "No.", "Date", "Category", "Name", "Amount");
    ExpenseNode* current = head;
    double category_total = 0.0; 
    int i = 1;
    int found = 0;
    
    while(current != NULL){
        if (strcmp(current->expense.category, selectedCategory) == 0) {
            printf("%-5d %-12s %-15s %-20s Rs. %.2f\n", i++, current->expense.date, current->expense.category, current->expense.name, current->expense.amount);
            found = 1;

            category_total += current->expense.amount;
        }
        current = current->next;
    }

    printf("\nTotal expense for Category : %s = %.2f \n", selectedCategory, category_total); 
    
    
    if(!found){
        printf("No expenses found in this category.\n");
    }
}

void viewTotal(){
    double total = 0;
    ExpenseNode* current = head;
    while (current != NULL) {
        total += current->expense.amount;
        current = current->next;
    }

    printf("Total Expense: Rs. %.2f\n", total);
}

void displayCategoryPercentage(){
    double totalExpense = 0;
    double categoryAmounts[CATEGORY_COUNT] = {0};

    ExpenseNode* current = head;
    while (current != NULL) {
        totalExpense += current->expense.amount;
        for (int j = 0; j < CATEGORY_COUNT; j++) {
            if (strcmp(current->expense.category, categories[j]) == 0) {
                categoryAmounts[j] += current->expense.amount;
                break;
            }
        }
        current = current->next;
    }

    if (totalExpense == 0){
        printf("No expenses recorded yet.\n");
        return;
    }

    printf("\n--- Category Expense Percentage ---\n");
    printf("\nCategory\tPercentage\tTotal Expense\tBar Chart\n\n"); 
    for (int i = 0; i < CATEGORY_COUNT; i++){
        double percentage = (categoryAmounts[i] / totalExpense) * 100;
        int barLength = (int)((percentage / 100) * MAX_BAR_LENGTH);
        if (barLength == 0 && percentage > 0) barLength = 1;

        printf("%-12s\t: %.1f%%\t\tRs.  %.2f\t", categories[i], percentage, categoryAmounts[i]);
        for (int j = 0; j < barLength; j++) {
            printf("|");
        }
        printf("\n");
    }
}

//BST Traversal for Sorted View by Date 
void inOrderTraversal(BSTNode* root) {
    static int i = 1;
    
    if (root == NULL) return;
    inOrderTraversal(root->left);
    printf("%-5d %-12s %-15s %-20s Rs.  %.2f\n", i++, root->data.date, root->data.category, root->data.name, root->data.amount);
    inOrderTraversal(root->right);
}

void viewExpensesByDate() {
    if (!bstRoot) {
        printf("No expenses to show.\n");
        return;
    }
    
    printf("\n--- Expenses Sorted by Date ---\n");
    printf("\n%-5s %-12s %-15s %-20s %-10s\n", "No.", "Date", "Category", "Name", "Amount");
    int i = 1; // Reset the static counter
    inOrderTraversal(bstRoot);
}

int partitionByPrice(Expense arr[], int low, int high) {
    double pivotPrice = arr[high].amount;
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j].amount < pivotPrice) {
            i++;
            Expense temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    Expense temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

void quickSortByPrice(Expense arr[], int low, int high) {
    if (low < high) {
        int pi = partitionByPrice(arr, low, high);
        quickSortByPrice(arr, low, pi - 1);
        quickSortByPrice(arr, pi + 1, high);
    }
}

void sortExpensesMenu() {
    int sortChoice;
    printf("\nSort by:\n1. Date (Using BST)\n2. Price\n");
    printf("Enter your choice: ");
    scanf("%d", &sortChoice);

    if (sortChoice == 1) {
        viewExpensesByDate();
    } else if (sortChoice == 2) {
        int count = 0;
        ExpenseNode* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        
        if (count == 0) {
            printf("No expenses to sort.\n");
            return;
        }

        // Create array for sorting
        Expense* arr = (Expense*)malloc(sizeof(Expense) * count);
        if (!arr) {
            printf("Memory allocation failed!\n");
            return;
        }
        
        current = head;
        for (int i = 0; i < count; i++) {
            arr[i] = current->expense;
            current = current->next;
        }

        quickSortByPrice(arr, 0, count - 1);

        // Display sorted expenses
        printf("\n--- Expenses Sorted by Price ---\n");
        printf("\n%-5s %-12s %-15s %-20s %-10s\n", "No.", "Date", "Category", "Name", "Amount");
        for (int i = 0; i < count; i++) {
            printf("%-5d %-12s %-15s %-20s Rs.  %.2f\n", 
                i + 1, arr[i].date, arr[i].category, arr[i].name, arr[i].amount);
        }

        free(arr);
    } else {
        printf("Invalid choice. Exiting sort.\n");
    }
}

void freeBST(BSTNode* node) {// free all allocated memory
    if (node) {
        freeBST(node->left);
        freeBST(node->right);
        free(node);
    }
}

void cleanupMemory() {
    
    ExpenseNode* current = head;
    while (current) {
        ExpenseNode* temp = current;
        current = current->next;
        free(temp);
    }
    
    freeBST(bstRoot);
}
void deleteExpense() {
    if (!head) {
        printf("No expenses to delete.\n");
        return;
    }

    // Display current expenses
    viewExpenses();

    int deleteIndex;
    printf("\nEnter the serial number of the expense to delete: ");
    scanf("%d", &deleteIndex);

    if (deleteIndex < 1) {
        printf("Invalid index.\n");
        return;
    }

    ExpenseNode* current = head;
    ExpenseNode* prev = NULL;
    int currentIndex = 1;

    // Traverse to the selected node
    while (current != NULL && currentIndex < deleteIndex) {
        prev = current;
        current = current->next;
        currentIndex++;
    }

    if (!current) {
        printf("Expense not found.\n");
        return;
    }

    // Delete node from the linked list
    if (!prev) {
        head = current->next; // deleting head
    } else {
        prev->next = current->next;
    }
    free(current);

    // rewriting the file with updated expenses
    FILE* file = fopen(FILENAME, "w");
    if (!file) {
        printf("Failed to update the file.\n");
        return;
    }

    ExpenseNode* temp = head;
    while (temp) {
        fprintf(file, "%s,%s,%s,%.2f\n", temp->expense.date, temp->expense.category, temp->expense.name, temp->expense.amount);
        temp = temp->next;
    }
    fclose(file);

    // Rebuild BST
    bstRoot = NULL;
    temp = head;
    while(temp){
        BSTNode* newNodeBST = (BSTNode*)malloc(sizeof(BSTNode));
        if (!newNodeBST) {
            printf("Memory allocation failed!\n");
            return;
        }
        newNodeBST->data = temp->expense;
        newNodeBST->left = newNodeBST->right = NULL;

        if (!bstRoot) {
            bstRoot = newNodeBST;
        } else {
            BSTNode* current = bstRoot;
            BSTNode* parent = NULL;
            int direction = 0;
            while (current) {
                parent = current;
                if (strcmp(temp->expense.date, current->data.date) < 0) {
                    current = current->left;
                    direction = 0;
                } else {
                    current = current->right;
                    direction = 1;
                }
            }
            if (direction == 0)
                parent->left = newNodeBST;
            else
                parent->right = newNodeBST;
        }

        temp = temp->next;
    }

    printf("Expense deleted successfully!\n");
}

void clearAllExpenses(){
    FILE* file = fopen(FILENAME, "w");

    head = NULL;

    if(file == NULL) printf("\nError in erasing\n");  
    fclose(file);
    printf("\nAll expenses erased.\n");
}

void mainMenu(){
    int choice;
    do {    
        printf("\n=== Expense Tracker ===\n");
        printf("1. Add Expense\n2. View Expenses\n3. View Total\n4. View Category Percentages\n");
        printf("5. View Expenses by Category\n6. Sort Expenses\n7. Exit\n8. Clear all the expenses\n9. Delete an Expense\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: viewTotal(); break;
            case 4: displayCategoryPercentage(); break;
            case 5: viewCategoryExpenses(); break;
            case 6: sortExpensesMenu(); break;
            case 7: printf("\nGoodbye!\n"); break;
            case 8: clearAllExpenses(); cleanupMemory(); break; 
            case 9: deleteExpense(); break; 
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 7);
}

int main(){
    
    FILE* file = fopen(FILENAME, "a");
    if (!file) {
        printf("Error creating expenses file.\n");
        return 1;
    }
    fclose(file);

    loadExpensesFromFile();
    
    mainMenu();
    cleanupMemory();
    
    return 0;
}