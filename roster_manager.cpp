#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_CAPACITY = 50;

struct Student {
    int id;
    string name;
};

int findStudentById(const Student roster[], int count, int targetId, int &comparisons);
    bool addStudent(Student roster[], int &count, int id, const string &name);
    bool removeStudentById(Student roster[], int &count, int id);
    bool safeGetRecord(const Student roster[], int count, int index, Student &outStudent);
    void printRoster(const Student roster[], int count);

int main() {
    Student roster[MAX_CAPACITY];
    int currentCount = 0;
    int choice = 0;

    do {
        cout << "\n=========================================\n";
        cout << "   NTC CC105: STUDENT ROSTER MANAGER    \n";
        cout << "=========================================\n";
        cout << "1. Add Student Record\n";
        cout << "2. Search Student by ID\n";
        cout << "3. Remove Student by ID\n";
        cout << "4. Safe Inspect Record by Index\n";
        cout << "5. Display Full Roster\n";
        cout << "6. Exit\n";
        cout << "Enter selection [1-6]: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name;
                cout << "\nEnter Student ID: ";
                cin >> id;
                cout << "\nEnter Student Name: ";
                cin.ignore();
                getline(cin, name);

                if (addStudent(roster, currentCount, id, name)) {
                    cout << "\nSuccess: Student record added successfully.\n";
                } else {
                    cout << "\nError: Failed to add student record.\n";
                }
                break;
            }
            case 2: {
                if (currentCount == 0) {
                    cout << "\nWarning: Roster is currently empty.\n";
                    break;
                }
                int targetId, comparisons = 0;
                cout << "\nEnter Student ID to search: ";
                cin >> targetId;

                int index = findStudentById(roster, currentCount, targetId, comparisons);
                cout << "\nTotal comparisons performed: " << comparisons << "\n";
                if (index != -1) {
                    cout << "\nStudent found at index " << index << ": ID = "
                         << roster[index].id << ", Name = " << roster[index].name << "\n";
                } else {
                    cout << "\nError: Student ID " << targetId << " not found.\n";
                }
                break;
            }
            case 3: {
                if (currentCount == 0) {
                    cout << "\nWarning: Roster is currently empty.\n";
                    break;
                }
                int targetId;
                cout << "\nEnter Student ID to remove: ";
                cin >> targetId;

                if (removeStudentById(roster, currentCount, targetId)) {
                    cout << "\nSuccess: Student ID " << targetId << " removed successfully.\n";
                } else {
                    cout << "\nError: Student ID " << targetId << " not found.\n";
                }
                break;
            }
            case 4: {
                if (currentCount == 0) {
                    cout << "\nWarning: Roster is currently empty.\n";
                    break;
                }
                int index;
                Student tempStudent;
                cout << "\nEnter index to inspect: ";
                cin >> index;

                if (safeGetRecord(roster, currentCount, index, tempStudent)) {
                    cout << "\nRecord at index " << index << " -> ID: "
                         << tempStudent.id << ", Name: " << tempStudent.name << "\n";
                } else {
                    cout << "\nError: Index " << index << " is out of bounds!\n";
                }
                break;
            }
            case 5: {
                printRoster(roster, currentCount);
                break;
            }
            case 6:
                break;
            default:
                cout << "\nInvalid selection. Please enter a number between 1 and 6.\n";}
    } while (choice != 6);

    cout << "\nExiting system. Memory cleaned successfully.\n";
    return 0;
}
bool addStudent(Student roster[], int &count, int id, const string &name) {
    if (count >= MAX_CAPACITY) {
        cout << "\nWarning: Roster capacity reached (MAX_CAPACITY = " << MAX_CAPACITY << ").\n";
        return false;
    }
    int dummyComparisons = 0;
    if (findStudentById(roster, count, id, dummyComparisons) != -1) {
        cout << "\nError: Student ID " << id << " already exists. IDs must be strictly unique.\n";
        return false;
    }
    roster[count].id = id;
    roster[count].name = name;
    count++;
    return true;
}
int findStudentById(const Student roster[], int count, int targetId, int &comparisons) {
    comparisons = 0;
    for (int i = 0; i < count; i++) {
        comparisons++;
        if (roster[i].id == targetId) {
            return i;}}
    return -1;
}
bool removeStudentById(Student roster[], int &count, int id) {
    int dummyComparisons = 0;
    int targetIndex = findStudentById(roster, count, id, dummyComparisons);

    if (targetIndex == -1) {
        return false;
    }
    for (int i = targetIndex; i < count - 1; i++) {
        roster[i] = roster[i + 1];
    }
    count--;
    return true;
}
bool safeGetRecord(const Student roster[], int count, int index, Student &outStudent) {
    if (index < 0 || index >= count) {
        return false;
    }
    outStudent = roster[index];
    return true;
}
void printRoster(const Student roster[], int count) {
    if (count == 0) {
        cout << "\nWarning: Roster is currently empty.\n";
        return;
    }
    cout << "\n-----------------------------------------\n";
    cout << left << setw(10) << "Index" << setw(12) << "ID" << "Name\n";
    cout << "-----------------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << left << setw(10) << i << setw(12) << roster[i].id << roster[i].name << "\n";
    }
    cout << "-----------------------------------------\n";
    cout << "Total Active Records: " << count << "\n";
}

/*
================================================================================
5. Performance Reflection (Written Task)
================================================================================
11. Random Access vs. Linear Search:
    - safeGetRecord executes in O(1) time complexity because array elements reside
      in contiguous memory locations. The exact memory address is computed instantly
      using constant arithmetic: Base Address + (Index * Element Size).
    - findStudentById requires O(n) worst-case time complexity because the array is
      unsorted. To locate an ID (or confirm it doesn't exist), the system must sequentially
      compare the target ID against each element up to all 'n' active records in the array.

12. Deletion Cost:
    - Deleting an element at index 0 requires left-shifting all remaining (n - 1)
      elements to close the gap and keep storage contiguous, leading to an O(n) operation.
    - Deleting an element at index currentCount - 1 (the last element) requires 0 shifts;
      only the active record count needs to be decremented (currentCount--), resulting in
      an O(1) constant-time operation.
================================================================================
*/
