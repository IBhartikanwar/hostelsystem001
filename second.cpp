#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// ===== CLASS 1: STUDENT =====
class student {
protected:
    string name;
    long phone;

public:
    student() {
        name = "Unknown";
        phone = 0;
    }
    student(string n, long p) {
        name = n;
        phone = p;
    }
    virtual void getDetails() {
        cout << "Enter student Name: ";
        cin >> name;
        cout << "Enter Phone Number: ";
        cin >> phone;
    }
    virtual void showDetails() const {
        cout << "Name: " << name << " | Phone: " << phone;
    }
    virtual ~student() {}
};

// ===== CLASS 2: ROOM =====
class Room {
protected:
    int roomNo;
    string type;
    float pricePeryear;

public:
    Room(int r = 0, string t = "Standard", float p = 1000.0) {
        roomNo = r;
        type = t;
        pricePeryear = p;
    }
    void showroom() const {
        cout << "Room No: " << roomNo << " | Type: " << type
             << " | Price: " << pricePeryear << endl;
    }
};

// ===== CLASS 3: VIP STUDENT =====
class VIPstudent : public student {
    int scholarship;

public:
    VIPstudent() : scholarship(15) {}
    void getDetails() override {
        student::getDetails();
        cout << "Scholarship is 15%\n";
    }
    void showDetails() const override {
        cout << "VIP Name: " << name << " | Phone: " << phone
             << " | Scholarship: " << scholarship << "%" << endl;
    }
};

// ===== CLASS 4: BOOKING =====
class Booking : public student, public Room {
    int year;
    float totalBill;
    static int totalBookings;

public:
    Booking() {
        year = 0;
        totalBill = 0;
    }

    void makeBooking() {
        getDetails();
        cout << "Enter Room No: ";
        cin >> roomNo;
        cout << "Enter Room Type (AC/Duct/NonAC/Residential): ";
        cin >> type;

        // Auto price based on type of the rooms
        if (type == "AC" || type == "ac")
            pricePeryear = 20000;
        else if (type == "Duct" || type == "duct")
            pricePeryear = 15000;
        else if (type == "NonAC" || type == "nonac" || type == "Non-Ac")
            pricePeryear = 10000;
        else if (type == "Residential" || type == "residential")
            pricePeryear = 5000;
        else
            pricePeryear = 8000; // default

        cout << "Enter Number of years: ";
        cin >> year;
        totalBill = pricePeryear * year;

        ofstream fout("bookings.txt", ios::app);
        fout << name << " " << phone << " " << roomNo << " " << type << " "
             << year << " " << totalBill << endl;
        fout.close();

        cout << "\nStudent Booking Saved Successfully!\n";
        totalBookings++;
    }

    float getTotalBill() const { return totalBill; }

    void showBooking() const {
        cout << "Customer: " << name << " | Phone: " << phone
             << " | Room: " << roomNo << " | Type: " << type
             << " | Price/year: ₹" << pricePeryear << " | Years: " << year
             << " | Total: ₹" << totalBill << endl;
    }

    static void showTotalBookings() { cout << totalBookings; }

    // Operator Overloading (+)
    Booking operator+(Booking b2) {
        Booking temp;
        temp.name = name + "_" + b2.name;
        temp.phone = phone + b2.phone;
        temp.totalBill = totalBill + b2.totalBill;
        return temp;
    }
};

int Booking::totalBookings = 0;

// ===== CLASS 5: ABSTRACT CLASS =====
class Basedetail {
public:
    virtual void displaydetail() = 0;
};

// ===== CLASS 6: HOSTEL DETAILS =====
class Hosteldetails : public Basedetail {
public:
    void displaydetail() override {
        cout << "\n--- HOSTEL DETAILS ---\n";
        cout << "1. AC Room - ₹20,000/year\n";
        cout << "2. Duct Room - ₹15,000/year\n";
        cout << "3. Non-AC Room - ₹10,000/year\n";
        cout << "4. Residential Room - ₹5,000/year\n";
    }
};

// ===== CLASS 7: FRIEND FUNCTION =====
class Bill {
    float amount;
    friend void showbill(Bill);

public:
    Bill(float a = 0) { amount = a; }
    void setAmount(float a) { amount = a; }
};
void showbill(Bill b) {
    cout << "\nTotal Bill Amount This Session: ₹" << b.amount << endl;
}

// ===== TEMPLATE CLASS =====
template <class T> class warden {
    T arr[3];

public:
    void setItem(int i, T val) { arr[i] = val; }
    void showItems() {
        cout << "\nWardens: ";
        for (int i = 0; i < 3; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

// ===== MAIN FUNCTION =====
int main() {
    int ch;
    Booking b1, b2, b3;
    Booking sessionBookings[10];
    int bookingCount = 0;
    float sessionTotalBill = 0; // Total bill for this session

    VIPstudent vis;
    Hosteldetails displaydetail;
    Bill bill; 
    warden<string> hostelWardens;

    hostelWardens.setItem(0, "warden1");
    hostelWardens.setItem(1, "warden2");
    hostelWardens.setItem(2, "warden3");

    cout << "==== HOSTEL MANAGEMENT SYSTEM ====\n";

    do {
        cout << "\n1. Make Booking";
        cout << "\n2. View Current Session Bookings";
        cout << "\n3. Combine Two Bookings (+)";
        cout << "\n4. VIP STUDENT";
        cout << "\n5. Show HOSTEL DETAILS";
        cout << "\n6. Show Total Bill (This Session)";
        cout << "\n7. Show Wardens";
        cout << "\n8. Exit\nEnter Choice: ";

        cin >> ch;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input! Please enter a valid number.\n";
            continue;
        }

        switch (ch) {
        case 1:
            b1.makeBooking();
            if (bookingCount < 10) {
                sessionBookings[bookingCount++] = b1;
                sessionTotalBill += b1.getTotalBill(); // total of the bill students logged
                bill.setAmount(sessionTotalBill);      
            } else {
                cout << "Maximum session bookings reached!\n";
            }
            break;

        case 2:
            if (bookingCount == 0) {
                cout << "\nNo bookings made yet in this session.\n";
            } else {
                cout << "\nCurrent Session Bookings:\n";
                for (int i = 0; i < bookingCount; i++)
                    sessionBookings[i].showBooking();
                cout << "\nTotal Bookings This Session: ";
                Booking::showTotalBookings();
                cout << endl;
            }
            break;

        case 3:
            cout << "\nEnter first booking:\n";
            b1.makeBooking();
            cout << "\nEnter second booking:\n";
            b2.makeBooking();
            b3 = b1 + b2;
            cout << "\nCombined Booking:\n";
            b3.showBooking();
            break;

        case 4:
            vis.getDetails();
            vis.showDetails();
            break;

        case 5:
            displaydetail.displaydetail();
            break;

        case 6:
            showbill(bill);
            break;

        case 7:
            hostelWardens.showItems();
            break;

        case 8:
            cout << "\nGoodbye!\n";
            break;

        default:
            cout << "\nInvalid choice! Please select between 1-8.\n";
        }

    } while (ch != 8);

    return 0;
}


