# Expense-Tracker-Tool
A fully functional expense tracking tool implemented by leveraging Linked Lists and Binary Search Trees coupled with File Handling. 
Here’s an **attractive, polished README** you can use to upload this C project on GitHub.

---

# 💸 Expense Tracker in C

A **feature-rich console-based Expense Tracker** written in C using data structures like **Linked Lists, Binary Search Trees (BSTs), and Quick Sort**.
It helps you **manage, view, and analyze your expenses** with persistence using CSV files.

---

## 🚀 Features

✅ Add expenses with date, category, name, and amount
✅ Save expenses to a `.csv` file
✅ Load expenses from the file automatically
✅ View all expenses in a tabular format
✅ View expenses **by category** with totals
✅ Display **category-wise percentage** with a neat bar chart
✅ Sort expenses:

* By **date** (using BST in-order traversal)
* By **price** (using Quick Sort)
  ✅ Persistent storage (`expenses2.csv`)

---

## 📂 Data Structures Used

* **Singly Linked List (SLL)** → stores expenses in memory
* **Binary Search Tree (BST)** → sorts expenses by date
* **Quick Sort on array** → sorts expenses by price

---

## 💻 How to Run

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/expense-tracker-c.git
   cd expense-tracker-c
   ```

2. Compile the code:

   ```bash
   gcc expense_tracker.c -o expense_tracker
   ```

3. Run the program:

   ```bash
   ./expense_tracker
   ```

---

## 📑 Predefined Categories

* Food
* Travel
* Shopping
* Entertainment
* Bills
* Investments
* Medical
* Other

---

## 📊 Sample Bar Chart Output

```
Category       Percentage    Total Expense    Bar Chart

Food           : 25.0%       Rs. 500.00      ||||||||
Travel         : 15.0%       Rs. 300.00      |||||
Shopping      : 30.0%        Rs. 600.00      |||||||||
...
```

---

## ⚙️ File Location

* The expenses are saved in:

  ```
  Your file path
  ```

> 📢 **Tip:** You can change the `FILENAME` macro in the code to adjust the file path.

---

## 🛠 Possible Improvements

* Add **delete** and **update** expense features
* Support **monthly reports**
* Export summary as **PDF** or **Excel**
* Build a simple **GUI frontend**
* Add **password protection**

---

## 🤝 Contributing

1. Fork the repo
2. Create a new branch (`feature/awesome-feature`)
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

---

## 📄 License

This project is licensed under the MIT License.

---

### 🌟 If you like this project, don’t forget to ⭐ the repository and share it!

---

