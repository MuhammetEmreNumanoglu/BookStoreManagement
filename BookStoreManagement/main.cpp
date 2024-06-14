#include <iostream>
#include <list>

using namespace std;

// INFORMATION
class Information {

protected:

    string arr[8] = {"1-The Bible", "2-Don Quixote", "3-A Tale of Two Cities", "4-The Lord of the Rings", "5-The Book of Mormon", "6-The Little Prince", "7-Harry Potter and the Sorcerer’s Stone", "8-Alice in Wonderland"};

public:

    string Name;
    string Password;

    string *ptr = &Password;

    static int Value1;
    static string status;


    list<string> cart;

    Information(string _name, string _password) : Name(_name), Password(_password) {}

      void AddCart(){
            cout<<" Select the book: "<<endl;
            int a;
            cin>>a;
            cart.push_back(arr[a-1]);

        }


    void DeleteCart(){
        cart.pop_back();

    }

     void ShowBookList() {
        cout << "**************************" << endl;
        cout << "THE BOOK LIST: :" << endl;

        for (string i : arr) {
            cout << i << endl;
        }

        cout << "**************************" << endl;
    }

    static void ShowStatus() {
        cout << "**************************" << endl;
        cout << "Cargo status:" << status << endl;
        cout << "You are being redirected to the menu." << endl;
        cout << "**************************" << endl;
    }

    void ShowCart() {
        cout << "**************************" << endl;
        if (cart.empty()) {
            cout << "Your cart is empty." << endl;
            cout << "You are being redirected to the menu." << endl;
        }
        else{
            cout << "Items in your cart:" << endl;
            for (auto it = cart.begin(); it != cart.end(); ++it) {
                cout << *it << endl;
            }
        }
        ShowStatus();

    }

    virtual void changePassword() {
        string new_password;
        cout << "Enter the new password: ";
        cin >> new_password;
        Password = new_password;
        ptr = &Password;
        cout << "Password changed successfully!" << endl;
    }

    virtual void Welcome( ){

        cout<<"welcome"<<endl;

    }
};

string Information::status;


// USER
class User : public Information {
private:

    string ScoreStatus[2]={"1-I like ","2-I do not like"};

public:

    static string score;
    int z;
    string userAdress;

    User(string _name, string _password, string _userAdress) : Information(_name, _password) {
        userAdress = _userAdress;
    }
    User(string _name, string _password) : Information(_name, _password) {}


    friend void GetScore( User& obj);


    void AddCart(string a) {
        cart.push_back(a);
    }


    void Welcome( ) override{

        cout<<" WELCOME USER! "<<endl;
    }

    void MenuUser() {
        cout << "**************************" << endl;
        cout << "MENU: " << endl;
        cout << "1-Show the Cart" << endl;
        cout << "2-Show the status of cargo" << endl;
        cout << "3-Show the book list" << endl;
        cout << "4-Change the password" << endl;
        cout << "5-Delete the cart " << endl;
        cout << "6-Exit" << endl;
        cout << "**************************" << endl;
        cin >> z;
        SelectedMenuUser(z);
    }

    void SelectedMenuUser(int n) {
        switch (n) {
            case 1:
                ShowCart();
                MenuUser();
                break;
            case 2:
                Information::ShowStatus();
                MenuUser();
                break;

            case 3:
                ShowBookList();
                Information::AddCart();
                MenuUser();
                break;
            case 4:
                changePassword();
                MenuUser();
                break;
            case 5:
                DeleteCart();
                cout << "Deleted the cart" << endl;
                MenuUser();
                break;
            default:
                break;
        }
    }
};

string User::score;

void GetScore( User& obj){

    int f;
    cout << "**************************" << endl;
    cout<<"Score the System "<<endl;
    for(int i = 0; i < 2; i++){
        cout<<obj.ScoreStatus[i]<<endl;
    }
    cin>>f;

    User::score = obj.ScoreStatus[f];

}

// ADMIN
class Admin : public User {
private:
    string statuses[4] = {"Getting ready...(estimated delivery date -> 2-5 days later) ", "Set Out(estimated delivery date -> 1-3 days later)", "delivered", "Cancelled"};


public:

    Admin() : User("admin", "123") {}
    int t, y;


    void Welcome( ) override{

        cout<<" WELCOME ADMIN ! "<<endl;
    }

    friend void SetStatus(Admin& admin, int s);

    void UpdateStatus(int s = 1) {
        switch (s) {
            case 1:
                status = statuses[0];
                break;
            case 2:
                status = statuses[1];
                break;
            case 3:
                status = statuses[2];
                break;
            case 4:
                status = statuses[3];
                break;
        }
    }


    void MenuAdmin() {
        while (true) {
            cout << "**************************" << endl;
            cout << "MENU: " << endl;
            cout << "1-Show the Cart" << endl;
            cout << "2-Change the status of cargo" << endl;
            cout << "3-Show the status of cargo" << endl;
            cout << "4-Show the book list" << endl;
            cout << "5-Change the password" << endl;
            cout << "6-Exit" << endl;
            cout << "**************************" << endl;

            cin >> t;

            switch (t) {
                case 1:
                    ShowCart();
                    break;
                case 2:
                    cout << "**************************" << endl;
                    cout << "You are being redirected to status of the cargo menu." << endl;
                    cout << "Please select the status of cargo:" << endl;
                    for (int i = 0; i < 4; ++i) {
                        cout << i + 1 << "- " << statuses[i] << endl;
                    }
                    cout << "**************************" << endl;
                    cin >> y;
                    if (y >= 1 && y <= 4) {
                        SetStatus(*this, y);
                        cout << "The status of your cargo has been changed." << endl;
                        cout << "You are being redirected to the menu." << endl;
                    } else {
                        cout << "Invalid option! Please try again." << endl;
                    }
                    break;

                case 3:
                    Information::ShowStatus();
                    break;


                case 4:
                    ShowBookList();
                    cout << "You are being redirected to the menu." << endl;
                    break;
                case 5:
                    changePassword();
                    break;
                case 6:
                    return;
                default:
                    cout << "Invalid option! Please try again." << endl;
                    break;
            }
        }
    }
} admin;

int Information::Value1 = 0;

void SetStatus(Admin& admin, int s) {
    admin.UpdateStatus(s);
}

int main() {

    User us1("muhammet", "123", "Üsküdar");
    User us2("emre", "123");

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
        cin >> loginType;

        if (loginType == 1) {
            while (true) {
                cout << "**************************" << endl;
                cout << "Enter username:";
                cin >> username;
                cout << "Enter Password:";
                cin >> password;
                cout << "**************************" << endl;

                if (username == "admin" && password == admin.Password) {
                    admin.Welcome();
                    admin.MenuAdmin();
                    break;

                } else {
                    cout << "**************************" << endl;
                    cout << "Invalid username or password! Please try again." << endl;
                    cout << "**************************" << endl;
                }
            }
        } else if (loginType == 2) {
            while (true) {
                cout << "**************************" << endl;
                cout << "Enter username:";
                cin >> username;
                cout << "Enter Password:";
                cin >> password;
                cout << "**************************" << endl;

                if (username == "muhammet" && password == us1.Password) {
                    us1.Welcome();
                    us1.MenuUser();
                    GetScore(us1);
                    break;
                }
                if (username == "emre" && password == us2.Password) {
                    us2.Welcome();
                    us2.MenuUser();
                    GetScore(us2);
                    break;
                }
                    else {
                    cout << "**************************" << endl;
                    cout << "Invalid username or password! Please try again." << endl;
                    cout << "**************************" << endl;
                }
            }
        } else if (loginType == 3) {
            break;
        } else {
            cout << "**************************" << endl;
            cout << "Invalid login type! Please try again." << endl;
            cout << "***************************" << endl;
        }
    }

    return 0;
}


