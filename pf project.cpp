#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// ===== Structures =====
struct Event {
    string name;
    string date;
    string time;
};

struct Venue {
    string name;
    bool isAvailable;
};

struct Participant {
    string name;
    int age;
    string department;
};

// ===== Global Variables =====
Event events[100]; // Array to store up to 100 events
Venue* venues;     // Dynamic array for venues
Participant participants[100][50]; // Max 100 events, 50 participants per event
int participantCounts[100] = {0};  // Tracks participant count per event
int eventCount = 0;                // Number of registered events
int venueCount = 0;                // Number of initialized venues

// ===== Function Prototypes =====
void registerEvent();
void initializeVenues();
void allocateVenue();
void addParticipant();
void searchParticipant();
void deleteParticipant();
void generateReport();
void mainMenu();

// ===== Main Function =====
int main() {
    // Display the welcome message
    cout << "===========================================\n";
    cout << "   Welcome to School Event Management System\n";
    cout << "===========================================\n";

    // Prompt user to initialize venues at the start
    cout << "Please initialize the venues for events.\n";
    initializeVenues(); // Initialize the venues for use

    // Launch the main menu to interact with the system
    mainMenu();

    // Clean up dynamically allocated memory for venues
    delete[] venues;

    // Display goodbye message after exiting the program
    cout << "System resources cleaned up. Goodbye!\n";

    return 0;
}

// ===== Function Implementations =====

// 1. Register an event
// This function fulfills the *Event Registration* point (Proposal Point 1)
void registerEvent() {
    if (eventCount >= 100) {
        cout << "Event limit reached. Cannot register more events.\n";
        return;
    }
    cout << "Enter event name: ";
    cin.ignore();
    getline(cin, events[eventCount].name);
    cout << "Enter event date (YYYY-MM-DD): ";
    cin >> events[eventCount].date;
    cout << "Enter event time (HH:MM): ";
    cin >> events[eventCount].time;

    cout << "Event registered successfully.\n";
    eventCount++;
}

// 2. Initialize venues
// This function fulfills the *Venue Allocation* point (Proposal Point 2)
void initializeVenues() {
    cout << "Enter the number of venues to initialize: ";
    cin >> venueCount;

    venues = new Venue[venueCount]; // Dynamically allocate memory for venues
    for (int i = 0; i < venueCount; i++) {
        cout << "Enter name for venue " << (i + 1) << ": ";
        cin.ignore();
        getline(cin, venues[i].name);
        venues[i].isAvailable = true; // Set all venues to available initially
    }
    cout << "Venues initialized successfully.\n";
}

// 3. Allocate a venue
// This function is part of *Venue Allocation* (Proposal Point 2)
void allocateVenue() {
    if (venueCount == 0) {
        cout << "No venues available. Please initialize venues first.\n";
        return;
    }

    cout << "Available venues:\n";
    for (int i = 0; i < venueCount; i++) {
        if (venues[i].isAvailable) {
            cout << i + 1 << ". " << venues[i].name << "\n";
        }
    }

    int choice;
    cout << "Enter the venue number to allocate: ";
    cin >> choice;

    if (choice > 0 && choice <= venueCount && venues[choice - 1].isAvailable) {
        venues[choice - 1].isAvailable = false;
        cout << "Venue allocated successfully.\n";
    } else {
        cout << "Invalid choice or venue is already allocated.\n";
    }
}

// 4. Add a participant
// This function is part of *Participant Management* (Proposal Point 3)
void addParticipant() {
    if (eventCount == 0) {
        cout << "No events available. Please register an event first.\n";
        return;
    }

    cout << "Available events:\n";
    for (int i = 0; i < eventCount; i++) {
        cout << i + 1 << ". " << events[i].name << "\n";
    }

    int eventId;
    cout << "Enter the event number (1 to " << eventCount << "): ";
    cin >> eventId;

    if (eventId < 1 || eventId > eventCount) {
        cout << "Invalid event number.\n";
        return;
    }
    eventId--; // Convert to zero-based index

    if (participantCounts[eventId] >= 50) {
        cout << "Participant limit reached for this event.\n";
        return;
    }

    Participant& participant = participants[eventId][participantCounts[eventId]];
    cout << "Enter participant name: ";
    cin.ignore();
    getline(cin, participant.name);
    cout << "Enter participant age: ";
    cin >> participant.age;
    cout << "Enter participant department: ";
    cin.ignore();
    getline(cin, participant.department);

    participantCounts[eventId]++;
    cout << "Participant added successfully.\n";
}

// 5. Search for a participant
// This function is part of *Participant Management* (Proposal Point 3)
void searchParticipant() {
    if (eventCount == 0) {
        cout << "No events available. Please register an event first.\n";
        return;
    }

    string name;
    cout << "Enter participant name to search: ";
    cin.ignore();
    getline(cin, name);

    for (int i = 0; i < eventCount; i++) {
        for (int j = 0; j < participantCounts[i]; j++) {
            if (participants[i][j].name == name) {
                cout << "Participant found: " << name << "\n";
                cout << "Event: " << events[i].name << ", Age: " << participants[i][j].age
                     << ", Department: " << participants[i][j].department << "\n";
                return;
            }
        }
    }
    cout << "Participant not found.\n";
}

// 6. Delete a participant
// This function is part of *Participant Management* (Proposal Point 3)
void deleteParticipant() {
    if (eventCount == 0) {
        cout << "No events available. Please register an event first.\n";
        return;
    }

    string name;
    cout << "Enter participant name to delete: ";
    cin.ignore();
    getline(cin, name);

    for (int i = 0; i < eventCount; i++) {
        for (int j = 0; j < participantCounts[i]; j++) {
            if (participants[i][j].name == name) {
                for (int k = j; k < participantCounts[i] - 1; k++) {
                    participants[i][k] = participants[i][k + 1];
                }
                participantCounts[i]--;
                cout << "Participant deleted successfully.\n";
                return;
            }
        }
    }
    cout << "Participant not found.\n";
}

// 7. Generate event report
// This function fulfills the *Report Generation and File Handling* point (Proposal Point 4)
void generateReport() {
    ofstream report("Event_Report.txt");
    if (!report) {
        cout << "Failed to create report file.\n";
        return;
    }

    report << "Event Report\n";
    report << "============\n\n";

    for (int i = 0; i < eventCount; i++) {
        report << "Event Name: " << events[i].name << "\n";
        report << "Date: " << events[i].date << "\n";
        report << "Time: " << events[i].time << "\n";
        report << "Participants:\n";
        for (int j = 0; j < participantCounts[i]; j++) {
            report << "- Name: " << participants[i][j].name
                   << ", Age: " << participants[i][j].age
                   << ", Department: " << participants[i][j].department << "\n";
        }
        report << "\n";
    }

    report.close();
    cout << "Event report generated successfully. Check 'Event_Report.txt'.\n";
}

// 8. Main menu
void mainMenu() {
    int choice;
    do {
        cout << "\n====== Main Menu ======\n";
        cout << "1. Register Event\n";
        cout << "2. Allocate Venue\n";
        cout << "3. Add Participant\n";
        cout << "4. Search Participant\n";
        cout << "5. Delete Participant\n";
        cout << "6. Generate Event Report\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerEvent(); break;
            case 2: allocateVenue(); break;
            case 3: addParticipant(); break;
            case 4: searchParticipant(); break;
            case 5: deleteParticipant(); break;
            case 6: generateReport(); break;
            case 7: cout << "Exiting system. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    }while (choice !=7);
}

