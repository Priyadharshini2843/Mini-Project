#include <iostream>
#include <string>
#include <limits>
using namespace std;

class ATM {
protected:
    string userName;
    int pin;
    double balance;

public:
    ATM(string name, int pin, double balance) {
        this->userName = name;
        this->pin = pin;
        this->balance = balance;
    }

    string getName() const {
        return userName;
    }

    bool validatePin(int enteredPin) {
        return enteredPin == pin;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful! New balance: " << balance << endl;
        } else {
            cout << "Invalid amount!" << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful! New balance: " << balance << endl;
            return true;
        } else {
            cout << "Insufficient balance or invalid amount!" << endl;
            return false;
        }
    }

    void changePin(int newPin) {
        pin = newPin;
        cout << "PIN changed successfully! Please remember your new PIN." << endl;
    }
};

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    ATM users[] = {
        ATM("John Doe", 1234, 5000.0),
        ATM("Jane Smith", 5678, 3000.0),
        ATM("Alice Brown", 4321, 7000.0)
    };
    const int userCount = sizeof(users) / sizeof(users[0]);

    bool running = true;
    bool firstLogin = true;

    while (running) {
        int enteredPin;
        bool authenticated = false;
        int currentUserIndex = -1;

        if (firstLogin) {
            cout << "Welcome to the ATM System" << endl;
            firstLogin = false;
        }

        // User login loop
        while (!authenticated) {
            cout << "\nEnter your PIN: ";
            cin >> enteredPin;

            if (cin.fail()) {
                clearInputBuffer();
                cout << "Invalid input. Please enter a numeric PIN." << endl;
                continue;
            }

            for (int i = 0; i < userCount; ++i) {
                if (users[i].validatePin(enteredPin)) {
                    authenticated = true;
                    currentUserIndex = i;
                    break;
                }
            }

            if (!authenticated) {
                cout << "Invalid PIN! Try again." << endl;
            }
        }

        cout << "\nWelcome, " << users[currentUserIndex].getName() << "!" << endl;

        int choice;
        do {
            cout << "\nATM Menu:" << endl;
            cout << "1. Check Balance" << endl;
            cout << "2. Deposit Money" << endl;
            cout << "3. Withdraw Money" << endl;
            cout << "4. Change PIN" << endl;
            cout << "5. Logout" << endl;
            cout << "6. Exit Program" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                clearInputBuffer();
                cout << "Invalid input! Please enter a number between 1 and 6." << endl;
                continue;
            }

            switch (choice) {
                case 1:
                    cout << "Current Balance: " << users[currentUserIndex].getBalance() << endl;
                    break;
                case 2: {
                    double amount;
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    if (cin.fail()) {
                        clearInputBuffer();
                        cout << "Invalid amount!" << endl;
                        break;
                    }
                    users[currentUserIndex].deposit(amount);
                    break;
                }
                case 3: {
                    double amount;
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    if (cin.fail()) {
                        clearInputBuffer();
                        cout << "Invalid amount!" << endl;
                        break;
                    }
                    users[currentUserIndex].withdraw(amount);
                    break;
                }
                case 4: {
                    int newPin;
                    cout << "Enter new PIN: ";
                    cin >> newPin;
                    if (cin.fail()) {
                        clearInputBuffer();
                        cout << "Invalid input! PIN must be numeric." << endl;
                        break;
                    }
                    users[currentUserIndex].changePin(newPin);
                    break;
                }
                case 5:
                    cout << "Logging out...\n" << endl;
                    authenticated = false;
                    currentUserIndex = -1;
                    firstLogin = true;
                    break;
                case 6:
                    cout << "Thank you for using the ATM. Goodbye!" << endl;
                    running = false;
                    return 0;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        } while (authenticated);
    }

    return 0;
}
