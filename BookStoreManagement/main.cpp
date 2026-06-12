#include <iostream>
#include <list>
#include <string>

using namespace std;

class Information {
protected:
    string bookList[8] = {
        "1-The Bible", "2-Don Quixote", "3-A Tale of Two Cities", 
        "4-The Lord of the Rings", "5-The Book of Mormon", 
        "6-The Little Prince", "7-Harry Potter and the Sorcerer’s Stone", 
        "8-Alice in Wonderland"
    };

public:
    string Name;
    string Password;
    list<string> cart;
    
    static string status;

    Information(string _name, string _password) : Name(_name), Password(_password) {}
    virtual ~Information() = default;

    void AddCart() {
        cout << "Select the book (1-8): " << endl;
        int a;
        cin >> a;
        if (a >= 1 && a <= 8) {
            cart.push_back(bookList[a - 1]);
            cout << "Book added to cart." << endl;
        } else {
            cout << "Invalid book selection!" << endl;
        }
    }

    void DeleteCart() {
        if (!cart.empty()) {
            cart.pop_back();
            cout << "Last item removed from cart." << endl;
        } else {
            cout << "Your cart is already empty." << endl;
        }
    }

    void ShowBookList() {
        cout << "**************************" << endl;
        cout << "THE BOOK LIST:" << endl;
        for (const string& book : bookList) {
            cout << book << endl;
        }
        cout << "**************************" << endl;
    }

    static void ShowStatus() {
        cout << "**************************" << endl;
        cout << "Cargo status: " << (status.empty() ? "No active cargo" : status) << endl;
        cout << "**************************" << endl;
    }

    void ShowCart() {
        cout << "**************************" << endl;
        if (cart.empty()) {
            cout << "Your cart is empty." << endl;
        } else {
            cout << "Items in your cart:" << endl;
            for (const string& item : cart) {
                cout << item << endl;
            }
        }
        cout << "**************************" << endl;
    }

    virtual void changePassword() {
        string new_password;
        cout << "Enter the new password: ";
        cin >> new_password;
        Password = new_password;
        cout << "Password changed successfully!" << endl;
    }

    virtual void Welcome() {
        cout << "Welcome!" << endl;
    }
};

string Information::status = "Getting ready...";

class User : public Information {
private:
    string ScoreStatus[2] = {"I like", "I do not like"};

public:
    string userAddress;
    static string score;

    User(string _name, string _password, string _userAddress = "") 
        : Information(_name, _password), userAddress(_userAddress) {}

    friend void GetScore(User& obj);

    void Welcome() override {
        cout << "WELCOME USER: " << Name << "!" << endl;
    }

    void MenuUser() {
        int choice;
        while (true) {
            cout << "**************************" << endl;
            cout << "USER MENU: " << endl;
            cout << "1-Show the Cart" << endl;
            cout << "2-Show the status of cargo" << endl;
            cout << "3-Show the book list & Add to Cart" << endl;
            cout << "4-Change the password" << endl;
            cout << "5-Delete last item from cart" << endl;
            cout << "6-Logout & Score System" << endl;
            cout << "**************************" << endl;
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
                case 1: ShowCart(); break;
                case 2: Information::ShowStatus(); break;
                case 3: ShowBookList(); AddCart(); break;
                case 4: changePassword(); break;
                case 5: DeleteCart(); break;
                case 6: return;
                default: cout << "Invalid option!" << endl; break;
            }
        }
    }
};

string User::score = "Not Scored Yet";

void GetScore(User& obj) {
    int f;
    cout << "**************************" << endl;
    cout << "Score the System" << endl;
    cout << "1- " << obj.ScoreStatus[0] << endl;
    cout << "2- " << obj.ScoreStatus[1] << endl;
    cout << "Your choice (1-2): ";
    cin >> f;

    if (f == 1 || f == 2) {
        User::score = obj.ScoreStatus[f - 1];
        cout << "Thank you for your feedback! Result saved as: " << User::score << endl;
    } else {
        cout << "Invalid score choice." << endl;
    }
    cout << "**************************" << endl;
}

class Admin : public Information {
private:
    string statuses[4] = {
        "Getting ready...(estimated delivery date -> 2-5 days later)", 
        "Set Out(estimated delivery date -> 1-3 days later)", 
        "Delivered", 
        "Cancelled"
    };

public:
    Admin() : Information("admin", "123") {}

    void Welcome() override {
        cout << "WELCOME ADMIN!" << endl;
    }

    void UpdateStatus() {
        int y;
        cout << "**************************" << endl;
        cout << "Please select the status of cargo:" << endl;
        for (int i = 0; i < 4; ++i) {
            cout << i + 1 << "- " << statuses[i] << endl;
        }
        cout << "**************************" << endl;
        cout << "Choice: ";
        cin >> y;

        if (y >= 1 && y <= 4) {
            status = statuses[y - 1];
            cout << "The status of cargo has been changed." << endl;
        } else {
            cout << "Invalid option!" << endl;
        }
    }

    void MenuAdmin() {
        int choice;
        while (true) {
            cout << "**************************" << endl;
            cout << "ADMIN MENU: " << endl;
            cout << "1-Change the status of cargo" << endl;
            cout << "2-Show the status of cargo" << endl;
            cout << "3-Show the book list" << endl;
            cout << "4-Change Admin password" << endl;
            cout << "5-Logout" << endl;
            cout << "**************************" << endl;
            cout << "Choice: ";
            cin >> choice;

            switch (choice) {
                case 1: UpdateStatus(); break;
                case 2: Information::ShowStatus(); break;
                case 3: ShowBookList(); break;
                case 4: changePassword(); break;
                case 5: return;
                default: cout << "Invalid option!" << endl; break;
            }
        }
    }
};

int main() {
    User us1("muhammet", "123", "Uskudar");
    User us2("emre", "123");
    Admin adminObj;

    int loginType;
    string username, password;

    while (true) {
        cout << "**************************" << endl;
        cout << "Welcome to BookStore" << endl;
        cout << "Choose the login type" << endl;
        cout << "1-Admin" << endl;
        cout << "2-User" << endl;
        cout << "3-Exit" << endl;
        cout << "**************************" << endl;
        cout << "Choice: ";
        cin >> loginType;

        if (loginType == 1) {
            cout << "Enter username: "; cin >> username;
            cout << "Enter Password: "; cin >> password;

            if (username == adminObj.Name && password == adminObj.Password) {
                adminObj.Welcome();
                adminObj.MenuAdmin();
            } else {
                cout << "Invalid admin credentials!" << endl;
            }
        } 
        else if (loginType == 2) {
            cout << "Enter username: "; cin >> username;
            cout << "Enter Password: "; cin >> password;

            if (username == us1.Name && password == us1.Password) {
                us1.Welcome();
                us1.MenuUser();
                GetScore(us1);
            } else if (username == us2.Name && password == us2.Password) {
                us2.Welcome();
                us2.MenuUser();
                GetScore(us2);
            } else {
                cout << "Invalid username or password!" << endl;
            }
        } 
        else if (loginType == 3) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        } 
        else {
            cout << "Invalid login type! Please try again." << endl;
        }
    }

    return 0;
}
