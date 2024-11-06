/*
Name: Anvesha Goydani
Roll No.: 8
PRN - F23112008
Class: SE Comp 2
Batch - P
*/

/*
Problem Statement:
Implement and execute Phonebook using linked lists.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iomanip> // For setw() to format columns
using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
    string gender;
    string address;
    Contact* next;
};

class PhoneBook {
public:
    Contact* head;

    void saveToFile() {
        ofstream file("phonebook.txt");
        Contact* temp = head;
        while (temp != nullptr) {
            file << temp->name << " " << temp->phone << " " << temp->email << " " 
                 << temp->gender << " " << temp->address << endl;
            temp = temp->next;
        }
        file.close();
    }

    bool isValidPhone(const string& phone) {
        // Check if the phone number has exactly 10 digits
        if (phone.length() != 10 || !all_of(phone.begin(), phone.end(), ::isdigit)) {
            return false;
        }
        return true;
    }

    bool isValidEmail(const string& email) {
        // Check if email ends with @gmail.com or @yahoo.co.in
        regex emailPattern("^[\\w\\.-]+@(gmail\\.com|yahoo\\.co\\.in)$");
        return regex_match(email, emailPattern);
    }

public:
    string getGender() {
        // Get valid gender input
        int genderChoice;
        while (true) {
            cout << "Enter gender:\n1. Male\n2. Female\nYour choice: ";
            cin >> genderChoice;
            if (genderChoice == 1) {
                return "Male";
            } else if (genderChoice == 2) {
                return "Female";
            } else {
                cout << "Invalid choice. Please select 1 for Male or 2 for Female.\n";
            }
        }
    }

    PhoneBook() : head(nullptr) {}

    void addContact(string name, string phone, string email, string gender, string address) {
        // Check if contact already exists
        Contact* temp = head;
        while (temp != nullptr) {
            if (temp->name == name) {
                cout << "Contact with this name already exists!" << endl;
                return;
            }
            temp = temp->next;
        }

        // Validate and prompt for phone number until valid
        while (!isValidPhone(phone)) {
            cout << "Invalid phone number! Please enter exactly 10 digits: ";
            cin >> phone;
        }

        // Validate and prompt for email until valid
        while (!isValidEmail(email)) {
            cout << "Invalid email! Email must be @gmail.com or @yahoo.co.in. Please enter again: ";
            cin >> email;
        }

        // Add new contact
        Contact* newContact = new Contact{name, phone, email, gender, address, nullptr};
        if (head == nullptr) {
            head = newContact;
        } else {
            temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newContact;
        }
        saveToFile();
        cout << "Contact added successfully!" << endl;
    }

    void modifyContact(string name) {
        Contact* temp = head;
        while (temp != nullptr) {
            if (temp->name == name) {
                cout << "Enter new phone number: ";
                cin >> temp->phone;
                if (!isValidPhone(temp->phone)) {
                    cout << "Invalid phone number! Please enter exactly 10 digits." << endl;
                    return;
                }

                cout << "Enter new email: ";
                cin >> temp->email;
                if (!isValidEmail(temp->email)) {
                    cout << "Invalid email! Email must be @gmail.com or @yahoo.co.in." << endl;
                    return;
                }

                temp->gender = getGender();

                cout << "Enter new address: ";
                cin.ignore();  // To handle newline issues
                getline(cin, temp->address);
                saveToFile();
                cout << "Contact modified successfully!" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Contact not found!" << endl;
    }

    void deleteContact(string name) {
        Contact* temp = head;
        Contact* prev = nullptr;
        while (temp != nullptr && temp->name != name) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "Contact not found!" << endl;
            return;
        }
        if (prev == nullptr) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        delete temp;
        saveToFile();
        cout << "Contact deleted!" << endl;
    }

    void searchContact(string name) {
        Contact* temp = head;
        while (temp != nullptr) {
            if (temp->name == name) {
                cout << "Name: " << temp->name << ", Phone: " << temp->phone 
                     << ", Email: " << temp->email << ", Gender: " << temp->gender 
                     << ", Address: " << temp->address << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Contact not found!" << endl;
    }

    void displayContacts() {
        Contact* temp = head;
        
        if (temp == nullptr) {
            cout << "No contacts to display!" << endl;
            return;
        }

        // Display header with column names
        cout << left << setw(15) << "Name" 
             << setw(15) << "Phone" 
             << setw(25) << "Email" 
             << setw(10) << "Gender" 
             << setw(30) << "Address" << endl;

        cout << "-------------------------------------------------------------------------------" << endl;

        // Loop through contacts and display each contact's details in tabular format
        while (temp != nullptr) {
            cout << left << setw(15) << temp->name 
                 << setw(15) << temp->phone 
                 << setw(25) << temp->email 
                 << setw(10) << temp->gender 
                 << setw(30) << temp->address << endl;
            temp = temp->next;
        }
    }

    void loadFromFile() {
        ifstream file("phonebook.txt");
        string name, phone, email, gender, address;
        while (file >> name >> phone >> email >> gender) {
            getline(file, address); // Read the rest of the address (can contain spaces)
            addContact(name, phone, email, gender, address);
        }
        file.close();
    }

    ~PhoneBook() {
        while (head != nullptr) {
            Contact* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    PhoneBook phonebook;
    phonebook.loadFromFile();
    int choice;
    string name, phone, email, gender, address;
    
    do {
        cout << "\nPhonebook Menu:\n";
        cout << "1. Add Contact\n2. Modify Contact\n3. Search Contact\n4. Delete Contact\n5. Display All Contacts\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone number (10 digits): ";
                cin >> phone;
                // Use the phonebook object to call isValidPhone
                while (!phonebook.isValidPhone(phone)) {
                    cout << "Invalid phone number! Please enter exactly 10 digits: ";
                    cin >> phone;
                }
                cout << "Enter email (@gmail.com or @yahoo.co.in): ";
                cin >> email;
                // Use the phonebook object to call isValidEmail
                while (!phonebook.isValidEmail(email)) {
                    cout << "Invalid email! Email must be @gmail.com or @yahoo.co.in. Please enter again: ";
                    cin >> email;
                }
                gender = phonebook.getGender();  // Use gender selection method
                cout << "Enter address: ";
                cin.ignore();  // To handle newline issues
                getline(cin, address);
                phonebook.addContact(name, phone, email, gender, address);
                break;
            case 2:
                cout << "Enter name to modify: ";
                cin >> name;
                phonebook.modifyContact(name);
                break;
            case 3:
                cout << "Enter name to search: ";
                cin >> name;
                phonebook.searchContact(name);
                break;
            case 4:
                cout << "Enter name to delete: ";
                cin >> name;
                phonebook.deleteContact(name);
                break;
            case 5:
                phonebook.displayContacts();
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);

    return 0;
}

/*
OUTPUT:
Phonebook Menu:
1. Add Contact
2. Modify Contact
3. Search Contact
4. Delete Contact
5. Display All Contacts
6. Exit
Enter your choice: 1
Enter name: Abcd
Enter phone number (10 digits): 1234567890
Enter email (@gmail.com or @yahoo.co.in): abcd@yahoo.co.in
Enter gender:
1. Male
2. Female
Your choice: 2
Enter address: 123 street
Contact added successfully!

Phonebook Menu:
1. Add Contact
2. Modify Contact
3. Search Contact
4. Delete Contact
5. Display All Contacts
6. Exit
Enter your choice: 1
Enter name: XYZ
Enter phone number (10 digits): 0987654321
Enter email (@gmail.com or @yahoo.co.in): xyz.12@gmail.com
Enter gender:
1. Male
2. Female
Your choice: 1
Enter address: 456 city
Contact added successfully!

Phonebook Menu:
1. Add Contact
2. Modify Contact
3. Search Contact
4. Delete Contact
5. Display All Contacts
6. Exit
Enter your choice: 1
Enter name: EFGH
Enter phone number (10 digits): 7654
Invalid phone number! Please enter exactly 10 digits: 1122334455
Enter email (@gmail.com or @yahoo.co.in): 128c
Invalid email number! Please enter email again: efgh@yahoo.co.in
Enter gender:
1. Male
2. Female
Your choice: 2
Enter address: 1245 street

Phonebook Menu:
1. Add Contact
2. Modify Contact
3. Search Contact
4. Delete Contact
5. Display All Contacts
6. Exit
Enter your choice: 1
Enter name: wxvt
Enter phone number (10 digits): 1234567098
Enter email (@gmail.com or @yahoo.co.in): wxyt@gmail.com
Enter gender:
1. Male
2. Female
Your choice: 1
Enter address: 1234 street
Contact added successfully!

Phonebook Menu:
1. Add Contact
2. Modify Contact
3. Search Contact
4. Delete Contact
5. Display All Contacts
6. Exit
Enter your choice: 2
Enter name to modify: wxvt
Enter new phone number: 8899007654
Enter new email: qwert@gmail.com
Enter gender:
1. Male
2. Female
Your choice: 1
Enter new address: 1287 street
Contact modified successfully!

Phonebook Menu:
1. Add Contact
2. Modify Contact
3. Search Contact
4. Delete Contact
5. Display All Contacts
6. Exit
Enter your choice: 3
Enter name to search: ABCD
Contact not found!

Phonebook Menu:
1. Add Contact
2. Modify Contact
3. Search Contact
4. Delete Contact
5. Display All Contacts
6. Exit
Enter your choice: 4
Enter name to delete: XYZ
Contact deleted!

Phonebook Menu:
1. Add Contact
2. Modify Contact
3. Search Contact
4. Delete Contact
5. Display All Contacts
6. Exit
Enter your choice: 4
Enter name to delete: EFGH
Contact deleted!


Phonebook Menu:
1. Add Contact
2. Modify Contact
3. Search Contact
4. Delete Contact
5. Display All Contacts
6. Exit
Enter your choice: 5
Name           Phone                         Email                    Gender      Address                       
-------------------------------------------------------------------------------------------------
Abcd           1234567890     abcd@yahoo.co.in         Female     123 street                    
wxvt           8899007654     qwert@gmail.com          Male         1287 street                   

Phonebook Menu:
1. Add Contact
2. Modify Contact
3. Search Contact
4. Delete Contact
5. Display All Contacts
6. Exit
Enter your choice: 6
Exiting...
*/