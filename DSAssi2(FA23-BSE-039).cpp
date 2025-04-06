#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// this is  a Structure to represent a patient
struct Patient {
    string name;
    string condition;
    int priority;   // Lower value means more critical
    int arrival;    // Used to break ties (lower means arrived earlier)
};

int arrivalCounter = 0;  // Global counter for arrival order

// Function to map emergency condition to a priority value (1 = highest priority)
int getPriority(const string &condition) {
    if (condition == "Heart Attack" || condition == "Stroke")
        return 1;
    else if (condition == "Broken Leg" || condition == "Severe Burn" || condition == "Fractured Arm")
        return 2;
    else if (condition == "Fever" || condition == "Food Poisoning" || condition == "Migraine")
        return 3;
    else if (condition == "Mild Cold" || condition == "Small Cut")
        return 4;
    else {
        cout << "Invalid condition. Defaulting to lowest priority.\n";
        return 4; // Default to lowest priority if unrecognized
    }
}

// Comparator: returns true if patient a should be served before patient b.
bool isHigher(const Patient &a, const Patient &b) {
    if (a.priority != b.priority)
        return a.priority < b.priority; // lower number means higher priority
    return a.arrival < b.arrival; // if equal priority, earlier arrival wins
}

// Heapify-up: restore min-heap property based on our custom comparator
void heapifyUp(vector<Patient>& heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (isHigher(heap[parent], heap[index]))
            break;
        swap(heap[parent], heap[index]);
        index = parent;
    }
}

// Heapify-down: restore min-heap property after removal
void heapifyDown(vector<Patient>& heap, int index) {
    int n = heap.size();
    while (true) {
        int best = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < n && isHigher(heap[left], heap[best]))
            best = left;
        if (right < n && isHigher(heap[right], heap[best]))
            best = right;
        if (best != index) {
            swap(heap[index], heap[best]);
            index = best;
        } else {
            break;
        }
    }
}

// Add a patient to the priority queue (min-heap)
void pushPatient(vector<Patient>& heap, Patient p) {
    heap.push_back(p);
    heapifyUp(heap, heap.size() - 1);
}

// Remove and return the patient with the highest priority (lowest numeric value)
Patient popPatient(vector<Patient>& heap) {
    Patient top = heap.front();
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty())
        heapifyDown(heap, 0);
    return top;
}

// Display the treatment order without modifying the original queue
void displayQueue(const vector<Patient>& heap) {
    cout << "\nCurrent Treatment Order:\n";
    // Create a copy so we can simulate removals
    vector<Patient> copy = heap;
    while (!copy.empty()) {
        Patient p = popPatient(copy);
        cout << "Patient: " << p.name
             << ", Condition: " << p.condition
             << ", Priority: " << p.priority << "\n";
    }
    cout << endl;
}

int main() {
    vector<Patient> priorityQueue;
    int choice;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Patient\n";
        cout << "3. Display Treatment Order\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline from the input buffer

        if (choice == 1) {
            Patient p;
            cout << "Enter patient name: ";
            getline(cin, p.name);
            cout << "Enter emergency condition (e.g., Heart Attack, Stroke, Broken Leg, Severe Burn, Fractured Arm, Fever, Food Poisoning, Migraine, Mild Cold, Small Cut): ";
            getline(cin, p.condition);
            p.priority = getPriority(p.condition);
            p.arrival = arrivalCounter++;  // Assign arrival order and increment counter
            pushPatient(priorityQueue, p);
            cout << "Patient added successfully.\n";
            displayQueue(priorityQueue);
        }
        else if (choice == 2) {
            if (priorityQueue.empty()) {
                cout << "No patients in the queue.\n";
            } else {
                Patient served = popPatient(priorityQueue);
                cout << "Serving patient: " << served.name
                     << ", Condition: " << served.condition
                     << ", Priority: " << served.priority << "\n";
                displayQueue(priorityQueue);
            }
        }
        else if (choice == 3) {
            if (priorityQueue.empty())
                cout << "No patients in the queue.\n";
            else
                displayQueue(priorityQueue);
        }
        else if (choice == 4) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}


