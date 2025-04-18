#include <iostream>
#include <stdexcept>
#include <cfloat>
#include "MathUtils.h"

using namespace std;

// === PART A: FuelTransaction with static data ===
class FuelTransaction {
private:
    double litersAdded;
    int transactionID;
    static int totalTransactions;
public:
    explicit FuelTransaction(double liters)
        : litersAdded(liters), transactionID(++totalTransactions) {}

    static int get_total_transactions() {
        return totalTransactions;
    }

    void display_transaction() const {
        cout << "Transaction #" << transactionID
            << ": " << litersAdded << " L" << endl;
    }
};
int FuelTransaction::totalTransactions = 0;


// === PART B: Friend function to transfer fuel ===
class PortableCan {
private:
    double liters;
public:
    explicit PortableCan(double l) : liters(l) {}

    friend void transfer_fuel(class CarTank& tank, PortableCan& can);

    void display() const {
        cout << liters << " L in portable can" << endl;
    }
};

class CarTank {
private:
    double litersInTank;
public:
    explicit CarTank(double l) : litersInTank(l) {}

    friend void transfer_fuel(CarTank& tank, PortableCan& can) {
        tank.litersInTank += can.liters;
        can.liters = 0.0;
    }

    void display() const {
        cout << litersInTank << " L in car tank" << endl;
    }
};


// === PART C: Overload + for trip distances ===
class TripDistance {
private:
    int kilometers;
public:
    explicit TripDistance(int km) : kilometers(km) {}

    TripDistance operator+(const TripDistance& other) const {
        return TripDistance(kilometers + other.kilometers);
    }

    void display() const {
        cout << "Total trip distance: " << kilometers << " km" << endl;
    }
};


// === PART D: Overload < for Driver ===
class Driver {
private:
    string name;
    int hoursDriven;
public:
    Driver(const string& n, int h)
        : name(n), hoursDriven(h) {}

    bool operator<(const Driver& other) const {
        return hoursDriven < other.hoursDriven;
    }

    string get_name() const { return name; }
    int get_hours() const { return hoursDriven; }
};


// === PART E: Inheritance – Vehicle & ElectricCar ===
class Vehicle {
protected:
    string brand;
private:
    string vin;
public:
    Vehicle(const string& b, const string& v)
        : brand(b), vin(v) {}

    string get_vin() const {
        return vin;
    }
};

class ElectricCar : public Vehicle {
public:
    ElectricCar(const string& b, const string& v)
        : Vehicle(b, v) {}

    void show_info() const {
        cout << "Electric Car – Brand: " << brand
            << ", VIN: " << get_vin() << endl;
    }
};


// === PART F: Exception handling for fuel efficiency ===
struct FuelError {
    string message;
    double value;
};

double calculate_efficiency(double km, double liters) {
    if (liters <= 0.0)
        throw FuelError{ "Invalid liters amount", liters };
    if (km <= 0.0)
        throw string("Invalid distance value");

    double efficiency = km / liters;
    if (efficiency > DBL_MAX)
        throw runtime_error("Efficiency value overflow");

    return efficiency;
}


// === MAIN ===
int main() {
    cout << "=== PART A: Fuel Transactions ===" << endl;
    FuelTransaction ft1(15.0), ft2(22.5), ft3(7.75);
    ft1.display_transaction();
    ft2.display_transaction();
    ft3.display_transaction();
    cout << "Total transactions: "
        << FuelTransaction::get_total_transactions()
        << "\n\n";

    cout << "=== PART B: Fuel Transfer ===" << endl;
    CarTank car(20.0);
    PortableCan can(5.0);
    cout << "Before transfer:" << endl;
    car.display();
    can.display();
    transfer_fuel(car, can);
    cout << "After transfer:" << endl;
    car.display();
    can.display();
    cout << "\n";

    cout << "=== PART C: Trip Addition ===" << endl;
    TripDistance trip1(120), trip2(180);
    TripDistance totalTrip = trip1 + trip2;
    totalTrip.display();
    cout << "\n";

    cout << "=== PART D: Driver Comparison ===" << endl;
    Driver d1("Alice", 5), d2("Bob", 8);
    const Driver& lessExp = (d1 < d2) ? d1 : d2;
    cout << lessExp.get_name()
        << " has driven fewer hours ("
        << lessExp.get_hours() << "h)"
        << "\n\n";

    cout << "=== PART E: Electric Car Info ===" << endl;
    ElectricCar tesla("Tesla", "5YJSA1E26HF000000");
    tesla.show_info();
    cout << "\n";

    cout << "=== PART F: Fuel Efficiency ===" << endl;
    cout << "Enter distance (km) and liters used: ";
    double km, liters;
    cin >> km >> liters;
    try {
        double eff = calculate_efficiency(km, liters);
        cout << "Efficiency: " << eff << " km/L" << endl;
    }
    catch (const FuelError& fe) {
        cout << "FuelError: " << fe.message
            << " (" << fe.value << ")" << endl;
    }
    catch (const string& s) {
        cout << "Error: " << s << endl;
    }
    catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error occurred." << endl;
    }
    cout << "\n";

    cout << "=== PART G: Math Utilities ===" << endl;
    showResult();
    cout << "Enter two integers to multiply: ";
    int x, y;
    cin >> x >> y;
    cout << x << " * " << y << " = " << multiply(x, y) << endl;

    cout << "Enter two numbers to divide (a / b): ";
    double a, b;
    cin >> a >> b;
    try {
        cout << a << " / " << b << " = " << divide(a, b) << endl;
    }
    catch (const invalid_argument& ia) {
        cout << "Division error: " << ia.what() << endl;
    }

    return 0;
}
