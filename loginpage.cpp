#include <iostream>
#include <fstream>
using namespace std;

class temp
{
    string username, Email, Password;
    string newname, newEmail, newpassword;
    fstream file;

public:
    void sighup();
    void login();
    void forgot();
} obj;

int main()
{
    char choice;
    cout << "\n1 - Sigh-up";
    cout << "\n2 - Login";
    cout << "\n3 - Forgot password";
    cout << "\n4 - Exit";
    cout << "\nEnter Your choice :: ";
    cin >> choice;

    switch (choice)
    {
    case '1':
        obj.sighup();
        break;

    case '2':
        obj.login();
        break;

    case '3':
        obj.forgot();
        break;

    case '4':
        return 0;
        break;

    default:
        cout << "Invalid selection....!";
    }
    return 0;
}

void temp ::sighup()
{
    cout << "\nEnter Your UserName :: ";
    cin.ignore();
    getline(cin, username);

    cout << "\nEnter your Email :: ";
    getline(cin, Email);

    cout << "\nEnter Your Password :: ";
    getline(cin, Password);

    if (username.empty() || Email.empty() || Password.empty())
    {
        cout << "\nAll fields are required!";
        return;
    }

    file.open("logindata.txt", ios::in);

    if (file)
    {
        while (getline(file, newname, '|'))
        {
            getline(file, newEmail, '|');
            getline(file, newpassword);

            if (newname == username)
            {
                cout << "Username Already Exists";
                file.close();
                return;
            }
        }
    }

    file.close();

    file.open("logindata.txt", ios ::out | ios ::app);

    if (!file)
    {
        cout << "\nUnable to open file!";
        return;
    }

    file << username << "|" << Email << "|" << Password << '\n';
    file.close();
    cout << "\nAccount Created Successfully!";
};

void temp ::login()
{
    cout << "------------LOGIN---------";

    cout << "\nEnter Your User Name :: ";
    cin.ignore();
    getline(cin, newname);

    cout << "Enter Your Password :: ";
    getline(cin, newpassword);

    file.open("logindata.txt", ios ::in);

    if (!file)
    {
        cout << "Unable to open file!";
        return;
    }

    while (getline(file, username, '|'))
    {
        getline(file, Email, '|');
        getline(file, Password);

        if (username == newname)
        {
            if (Password == newpassword)
            {
                cout << "Login Successful";
                cout << "\nYour password is :: " << Password;
                file.close();
                return;
            }
            else
            {
                cout << "Incorrect Password";
                file.close();
                return;
            }
        }
    }
    file.close();
    cout << "\nUsername Not Found";
};

void temp ::forgot()
{
    cout << "\nEnter Your user Name :: ";
    cin.ignore();
    getline(cin, newname);
    cout << "Enter Your Email :: ";
    getline(cin, newEmail);

    file.open("logindata.txt", ios ::in);

    if (!file)
    {
        cout << "Unable to open file!";
        return;
    }

    bool found = false;

    while (getline(file, username, '|'))
    {
        getline(file, Email, '|');
        getline(file, Password);

        if (username == newname)
        {
            found = true;

            if (Email == newEmail)
            {
                cout << "Account Login successful....!";
                cout << "\nYour password is :: " << Password;
            }
            else
            {
                cout << "Incorrect Email...!";
            }
        }
    }
    file.close();

    if (!found)
    {
        cout << "Username Not Found";
    }
};