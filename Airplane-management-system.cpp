#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <cctype>

using namespace std;

// ===================== DATA STRUCTURES =====================
/** **Struct**: Stores flight details */
struct Flight {
    string flightNo, destination, dayTime, distance, plane, duration;
    int seats;
    float price;
};

/** **Struct**: Stores passenger information */
struct Passenger {
    string name, passport, id, contact;
};

/** **Struct**: Manages booking records */
struct Booking {
    string bookingId, flightNo, passengerId;
    time_t bookingTime;
    bool isPaid;
};

/** **Struct**: Aircraft inventory */
struct Aircraft {
    string model;
    int totalSeats;
    vector<string> features;
};

// ===================== GLOBAL VARIABLES =====================
vector<Flight> flights = {
    // African Destinations (10)
    {"AF101", "Cairo", "Mon 08:00 AM", "1200 km", "Boeing 737", "2h", 40, 250},
    {"AF202", "Nairobi", "Tue 10:30 AM", "1800 km", "Airbus A320", "3h", 40, 300},
    {"AF303", "Cape Town", "Wed 09:15 AM", "3500 km", "Boeing 787", "5h", 40, 450},
    {"AF404", "Lagos", "Thu 11:20 AM", "2200 km", "Airbus A330", "3h", 40, 320},
    {"AF505", "Johannesburg", "Fri 03:45 PM", "4000 km", "Boeing 777", "6h", 40, 500},
    {"AF606", "Casablanca", "Sat 08:10 AM", "1500 km", "Airbus A350", "2h30m", 40, 280},
    {"AF707", "Addis Ababa", "Sun 10:50 PM", "3000 km", "Boeing 747", "4h45m", 40, 420},
    {"AF808", "Accra", "Mon 01:15 PM", "1800 km", "Airbus A380", "3h15m", 40, 350},
    {"AF909", "Dakar", "Tue 04:30 PM", "2000 km", "Boeing 737", "3h30m", 40, 380},
    {"AF110", "Kigali", "Wed 07:25 AM", "1600 km", "Airbus A320", "2h45m", 40, 310},

    // International Destinations (10)
    {"IN101", "Paris", "Mon 06:00 AM", "3500 km", "Airbus A380", "6h", 40, 600},
    {"IN202", "New York", "Tue 09:30 PM", "7000 km", "Boeing 777", "8h", 40, 850},
    {"IN303", "Dubai", "Wed 02:15 AM", "4000 km", "Boeing 787", "5h30m", 40, 550},
    {"IN404", "London", "Thu 10:20 AM", "4500 km", "Airbus A350", "7h", 40, 700},
    {"IN505", "Tokyo", "Fri 04:45 PM", "9000 km", "Boeing 747", "12h", 40, 1200},
    {"IN606", "Sydney", "Sat 09:10 PM", "11000 km", "Airbus A380", "14h", 40, 1500},
    {"IN707", "Singapore", "Sun 11:50 AM", "6000 km", "Boeing 787", "8h", 40, 950},
    {"IN808", "Hong Kong", "Mon 03:15 PM", "6500 km", "Airbus A350", "9h", 40, 1000},
    {"IN909", "Mumbai", "Tue 05:30 AM", "4000 km", "Boeing 737", "5h", 40, 500},
    {"IN110", "Istanbul", "Wed 08:25 PM", "3000 km", "Airbus A320", "4h", 40, 450}
};

vector<Passenger> passengers;
vector<Booking> bookings;
vector<Aircraft> aircrafts = {
    {"Boeing 737", 40, {"WiFi", "Snacks"}},
    {"Airbus A320", 40, {"Entertainment"}},
    {"Boeing 787", 40, {"WiFi", "Entertainment", "Luxury"}},
    {"Airbus A380", 40, {"First Class", "Spa"}}
};

// ===================== UTILITY FUNCTIONS =====================
/** **Function**: Gets current system time */
time_t getCurrentTime() { return time(nullptr); }

/** **Function**: Formats time as string */
string timeToString(time_t t) {
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return string(buffer);
}

/** **Function**: Validates phone numbers (max 15 digits) */
bool validatePhone(const string& phone) {
    return phone.length() <= 15 && all_of(phone.begin(), phone.end(), ::isdigit);
}

/** **Function**: Validates passport (max 10 alphanumeric) */
bool validatePassport(const string& passport) {
    return passport.length() <= 10 && all_of(passport.begin(), passport.end(), ::isalnum);
}

/** **Function**: Validates ID (max 10 digits) */
bool validateID(const string& id) {
    return id.length() <= 10 && all_of(id.begin(), id.end(), ::isdigit);
}

/** **Function**: Validates general input (max 20 chars) */
bool validateInput(const string& input) {
    return !input.empty() && input.length() <= 20;
}

// ===================== FILE HANDLING =====================
/** **Function**: Saves all data to files */
void saveData() {
    // Save flights
    ofstream ffile("flights.txt");
    for (const auto& f : flights) {
        ffile << f.flightNo << "," << f.destination << "," << f.dayTime << ","
              << f.distance << "," << f.plane << "," << f.duration << ","
              << f.seats << "," << f.price << "\n";
    }
    ffile.close();

    // Save passengers
    ofstream pfile("passengers.txt");
    for (const auto& p : passengers) {
        pfile << p.name << "," << p.passport << "," << p.id << "," << p.contact << "\n";
    }
    pfile.close();

    // Save bookings
    ofstream bfile("bookings.txt");
    for (const auto& b : bookings) {
        bfile << b.bookingId << "," << b.flightNo << "," << b.passengerId << ","
              << b.bookingTime << "," << b.isPaid << "\n";
    }
    bfile.close();
}

/** **Function**: Loads data from files */
void loadData() {
    // Load flights
    ifstream ffile("flights.txt");
    if (ffile) {
        flights.clear();
        string line;
        while (getline(ffile, line)) {
            stringstream ss(line);
            Flight f;
            getline(ss, f.flightNo, ',');
            getline(ss, f.destination, ',');
            getline(ss, f.dayTime, ',');
            getline(ss, f.distance, ',');
            getline(ss, f.plane, ',');
            getline(ss, f.duration, ',');
            ss >> f.seats;
            ss.ignore();
            ss >> f.price;
            flights.push_back(f);
        }
        ffile.close();
    }

    // Load passengers
    ifstream pfile("passengers.txt");
    if (pfile) {
        passengers.clear();
        string line;
        while (getline(pfile, line)) {
            stringstream ss(line);
            Passenger p;
            getline(ss, p.name, ',');
            getline(ss, p.passport, ',');
            getline(ss, p.id, ',');
            getline(ss, p.contact, ',');
            passengers.push_back(p);
        }
        pfile.close();
    }

    // Load bookings
    ifstream bfile("bookings.txt");
    if (bfile) {
        bookings.clear();
        string line;
        while (getline(bfile, line)) {
            stringstream ss(line);
            Booking b;
            getline(ss, b.bookingId, ',');
            getline(ss, b.flightNo, ',');
            getline(ss, b.passengerId, ',');
            ss >> b.bookingTime;
            ss.ignore();
            ss >> b.isPaid;
            bookings.push_back(b);
        }
        bfile.close();
    }
}

// ===================== FLIGHT FUNCTIONS =====================
/** **Function**: Displays all available flights */
void viewAllFlights() {
    cout << "\n===== AVAILABLE FLIGHTS (20 DESTINATIONS) =====";
    cout << "\n\n---------- AFRICAN DESTINATIONS ----------\n";
    cout << left << setw(8) << "Code" << setw(15) << "Destination"
         << setw(14) << "Departure" << setw(10) << "Distance"
         << setw(10) << "Duration" << setw(12) << "Aircraft"
         << setw(6) << "Seats" << "Price\n";

    for (int i = 0; i < 10; i++) {
        cout << setw(8) << flights[i].flightNo << setw(15) << flights[i].destination
             << setw(14) << flights[i].dayTime << setw(10) << flights[i].distance
             << setw(10) << flights[i].duration << setw(12) << flights[i].plane
             << setw(6) << flights[i].seats << "$" << flights[i].price << "\n";
    }

    cout << "\n-------- INTERNATIONAL DESTINATIONS --------\n";
    for (int i = 10; i < 20; i++) {
        cout << setw(8) << flights[i].flightNo << setw(15) << flights[i].destination
             << setw(14) << flights[i].dayTime << setw(10) << flights[i].distance
             << setw(10) << flights[i].duration << setw(12) << flights[i].plane
             << setw(6) << flights[i].seats << "$" << flights[i].price << "\n";
    }
}

/** **Function**: Searches flights by destination */
void searchByDestination() {
    string dest;
    cout << "Enter destination: ";
    cin.ignore();
    getline(cin, dest);
    transform(dest.begin(), dest.end(), dest.begin(), ::tolower);

    cout << "\n===== SEARCH RESULTS =====\n";
    bool found = false;
    for (const auto& f : flights) {
        string fdest = f.destination;
        transform(fdest.begin(), fdest.end(), fdest.begin(), ::tolower);
        if (fdest.find(dest) != string::npos) {
            cout << "Flight: " << f.flightNo << " | " << f.destination
                 << " | " << f.dayTime << " | " << f.duration
                 << " | Seats: " << f.seats << " | Price: $" << f.price << "\n";
            found = true;
        }
    }
    if (!found) cout << "No flights found!\n";
}

// ===================== BOOKING FUNCTIONS =====================
/** **Function**: Handles flight booking */
void bookFlight() {
    viewAllFlights();
    string flightNo;
    cout << "\nEnter flight number: ";
    cin >> flightNo;
    
    auto flight = find_if(flights.begin(), flights.end(), 
        [&flightNo](const Flight& f) { return f.flightNo == flightNo; });
    
    if (flight == flights.end()) {
        cout << "Flight not found!\n";
        return;
    }

    if (flight->seats <= 0) {
        cout << "No seats available!\n";
        return;
    }

    Passenger p;
    do {
        cout << "Enter your name (max 20 chars): ";
        cin.ignore();
        getline(cin, p.name);
    } while (!validateInput(p.name));

    do {
        cout << "Enter passport (max 10 chars): ";
        cin >> p.passport;
    } while (!validatePassport(p.passport));

    do {
        cout << "Enter ID (max 10 digits): ";
        cin >> p.id;
    } while (!validateID(p.id));

    do {
        cout << "Enter phone (max 15 digits): ";
        cin >> p.contact;
    } while (!validatePhone(p.contact));

    cout << "\nTotal to pay: $" << flight->price;
    cout << "\nConfirm payment? (1=Yes, 0=No): ";
    int confirm;
    cin >> confirm;

    if (confirm == 1) {
        Booking b;
        b.bookingId = "B" + to_string(bookings.size() + 1000);
        b.flightNo = flightNo;
        b.passengerId = p.id;
        b.bookingTime = getCurrentTime();
        b.isPaid = true;

        flight->seats--;
        passengers.push_back(p);
        bookings.push_back(b);
        saveData();

        cout << "\nBooking successful! Your Booking ID: " << b.bookingId << "\n";
    } else {
        cout << "Booking cancelled.\n";
    }
}
/** **Function**: Cancels a booking */
void cancelBooking() {
    string bookingId;
    cout << "Enter booking ID: ";
    cin >> bookingId;

    auto booking = find_if(bookings.begin(), bookings.end(), 
        [&bookingId](const Booking& b) { return b.bookingId == bookingId; });

    if (booking == bookings.end()) {
        cout << "Booking not found!\n";
        return;
    }

    auto flight = find_if(flights.begin(), flights.end(), 
        [&booking](const Flight& f) { return f.flightNo == booking->flightNo; });

    if (flight != flights.end()) {
        flight->seats++;
    }

    bookings.erase(booking);
    saveData();
    cout << "Booking cancelled successfully!\n";
}

// ===================== ADMIN FUNCTIONS =====================
/** **Function**: Verifies admin password */
bool authenticateAdmin() {
    string password;
    cout << "Enter admin password: ";
    cin >> password;
    if (password != "ela2121") {
        cout << "Access denied!\n";
        return false;
    }
    return true;
}

/** **Function**: Adds new aircraft */
void addAircraft() {
    Aircraft a;
    cout << "Enter plane model: ";
    cin.ignore();
    getline(cin, a.model);
    
    cout << "Enter total seats: ";
    cin >> a.totalSeats;
    
    cout << "Enter features (comma separated): ";
    string features;
    cin.ignore();
    getline(cin, features);
    
    stringstream ss(features);
    string feature;
    while (getline(ss, feature, ',')) {
        a.features.push_back(feature);
    }
    
    aircrafts.push_back(a);
    cout << "Aircraft added successfully!\n";
}

/** **Function**: Adds new flight */
void addFlight() {
    if (aircrafts.empty()) {
        cout << "No aircrafts available! Add one first.\n";
        return;
    }

    cout << "\nAvailable Aircrafts:\n";
    for (const auto& a : aircrafts) {
        cout << "- " << a.model << " (" << a.totalSeats << " seats)\n";
    }

    Flight f;
    cout << "\nEnter flight number: ";
    cin >> f.flightNo;
    
    cout << "Select plane model: ";
    string selectedModel;
    cin.ignore();
    getline(cin, selectedModel);
    
    auto plane = find_if(aircrafts.begin(), aircrafts.end(),
        [&selectedModel](const Aircraft& a) { return a.model == selectedModel; });
    
    if (plane == aircrafts.end()) {
        cout << "Invalid plane model!\n";
        return;
    }

    f.plane = plane->model;
    f.seats = plane->totalSeats;
    
    cout << "Enter destination: ";
    getline(cin, f.destination);
    
    cout << "Enter day/time: ";
    getline(cin, f.dayTime);
    
    cout << "Enter distance: ";
    getline(cin, f.distance);
    
    cout << "Enter duration: ";
    getline(cin, f.duration);
    
    cout << "Enter price: $";
    cin >> f.price;

    flights.push_back(f);
    saveData();
    cout << "Flight added successfully using " << plane->model << "!\n";
}
/** **Function**: Views all passengers */
void viewAllPassengers() {
    cout << "\n===== ALL PASSENGERS =====\n";
    cout << left << setw(20) << "Name" << setw(12) << "Passport" 
         << setw(12) << "ID" << "Contact\n";
    for (const auto& p : passengers) {
        cout << setw(20) << p.name << setw(12) << p.passport 
             << setw(12) << p.id << p.contact << "\n";
    }
}

/** **Function**: Views all bookings */
void viewAllBookings() {
    cout << "\n===== ALL BOOKINGS =====\n";
    cout << left << setw(10) << "Booking ID" << setw(10) << "Flight" 
         << setw(12) << "Passenger ID" << setw(20) << "Booking Time" 
         << "Status\n";
    for (const auto& b : bookings) {
        cout << setw(10) << b.bookingId << setw(10) << b.flightNo 
             << setw(12) << b.passengerId << setw(20) << timeToString(b.bookingTime) 
             << (b.isPaid ? "Paid" : "Unpaid") << "\n";
    }
}

/** **Function**: Admin cancels any booking */
void adminCancelBooking() {
    viewAllBookings();
    string bookingId;
    cout << "Enter booking ID to cancel: ";
    cin >> bookingId;

    auto booking = find_if(bookings.begin(), bookings.end(), 
        [&bookingId](const Booking& b) { return b.bookingId == bookingId; });

    if (booking == bookings.end()) {
        cout << "Booking not found!\n";
        return;
    }

    auto flight = find_if(flights.begin(), flights.end(), 
        [&booking](const Flight& f) { return f.flightNo == booking->flightNo; });

    if (flight != flights.end()) {
        flight->seats++;
    }

    bookings.erase(booking);
    saveData();
    cout << "Admin: Booking cancelled successfully!\n";
}

/** **Function**: Auto-cancels unpaid bookings after 24 hours */
void autoCancelUnpaid() {
    const time_t now = getCurrentTime();
    const time_t twentyFourHours = 24 * 60 * 60;

    int cancelled = 0;
    for (auto it = bookings.begin(); it != bookings.end(); ) {
        if (!it->isPaid && (now - it->bookingTime) > twentyFourHours) {
            auto flight = find_if(flights.begin(), flights.end(), 
                [&it](const Flight& f) { return f.flightNo == it->flightNo; });
            if (flight != flights.end()) flight->seats++;
            it = bookings.erase(it);
            cancelled++;
        } else {
            ++it;
        }
    }

    if (cancelled > 0) {
        saveData();
        cout << "Admin: Cancelled " << cancelled << " unpaid bookings.\n";
    } else {
        cout << "No unpaid bookings to cancel.\n";
    }
}
// ===================== MENU FUNCTIONS =====================
/** **Function**: Displays passenger menu */
void passengerMenu() {
    int choice;
    do {
        viewAllFlights();
        cout << "\n===== PASSENGER MENU =====\n";
        cout << "1. Search by Destination\n";
        cout << "2. Book a Flight\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: searchByDestination(); break;
            case 2: bookFlight(); break;
            case 3: cancelBooking(); break;
            case 4: break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);
}

/** **Function**: Displays admin menu */
void adminMenu() {
    if (!authenticateAdmin()) return;

    int choice;
    do {
        cout << "\n===== ADMIN MENU =====\n";
        cout << "1. Add Aircraft\n";
        cout << "2. Add Flight\n";
        cout << "3. View All Passengers\n";
        cout << "4. View All Bookings\n";
        cout << "5. Cancel Any Booking\n";
        cout << "6. Auto-Cancel Unpaid\n";
        cout << "7. Return to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addAircraft(); break;
            case 2: addFlight(); break;
            case 3: viewAllPassengers(); break;
            case 4: viewAllBookings(); break;
            case 5: adminCancelBooking(); break;
            case 6: autoCancelUnpaid(); break;
            case 7: break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 7);
}

/** **Function**: Main menu */
int main() {
    loadData();

    int choice;
    do {
        cout << "\n===== AIRPLANE MANAGEMENT SYSTEM =====\n";
        cout << "1. Admin Login\n";
        cout << "2. Passenger Menu\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: adminMenu(); break;
            case 2: passengerMenu(); break;
            case 3: cout << "Exiting system...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}