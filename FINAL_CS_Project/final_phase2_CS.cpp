//DONE BY "AAROHI SHAH", "SHIVAM KHARANGATE" AND "PRATYUSH SRIVASTAVA"//


#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include <bits/stdc++.h>
using namespace std;

class DATE
{
    int d, m, y;
    const int days_in_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

public:

    void wait()
    {
        cout << "\n Press any letter and enter.\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
    }
    int counting_Leapyears(DATE d)
    {
        int years = d.y;
        if (d.m <= 2)
            years--;
        return years / 4 - years / 100 + years / 400;
    }

    int difference_obtain(DATE dt1, DATE dt2)
    {
        int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        int days1 = dt1.d;
        for (int month = 0; month < dt1.m - 1; month++)
        {
            days1 += days_in_month[month];
        }
        days1 += counting_Leapyears(dt1);

        int days2 = dt2.d;
        for (int month = 0; month < dt2.m - 1; month++)
        {
            days2 += days_in_month[month];
        }
        days2 += counting_Leapyears(dt2);

        int total_days = (dt2.y - dt1.y) * 365 + (days2 - days1);
        return total_days;
    }
    string enter_date(int k) {
        string currentdate;
        string buffer1;
        time_t rawtime;
        tm* timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime((char*)buffer1.c_str(), 80, "%Y-%m-%d-%H-%M-%S", timeinfo);
        string buffer(buffer1.c_str());
        string currentyear = buffer.substr(0, 4);
        string currentmonth = buffer.substr(5, 2);
        string currentday = buffer.substr(8, 2);
        currentdate = currentmonth + "/" + currentday + "/" + currentyear;

        string prompt = (k == 0) ? "Enter today's date (MM/DD/YYYY):: " : "Enter your date of birth (MM/DD/YYYY):: ";
        string error_msg = (k == 0) ? "Please enter the correct date, which is " + currentdate : "You must be of at least 18 years to open an account.";

        while (true) {
            string cdate;
            cout << prompt;
            cin >> cdate;
            DATE DOB;
            DATE td;
            DOB.y = stoi(currentyear);
            DOB.d = stoi(currentday);
            DOB.m = stoi(currentmonth);
            td.y = stoi(cdate.substr(6, 4));
            td.d = stoi(cdate.substr(3, 2));
            td.m = stoi(cdate.substr(0, 2));
            if ((k == 0 && currentdate == cdate) || (k == 1 && difference_obtain(td, DOB) >= 365 * 18)) {
                return cdate;
            }
            else {
                cout << error_msg << endl;
                wait();
            }
        }
        return "";
    }


};
class Customer : public DATE
{

    int customer_id = 0;
    string customer[500][11];
    float interest;
    vector<string> admin;
    vector<vector<float>> transaction;
    vector<vector<string>> msg;

public:
    // int adminrequired();
    //  string enter_num(int);
    //  string enter_password();
    //  string enter_date(int, string);
    //  string enter_emailID();

    void wait()
    {
        cout << "\n Press any letter and enter.\n";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
    }
    int enter_Bank_info()
    {
        cout << "Enter the interest rate for customer :: ";
        cin >> interest;
        cout << "Following information is required by customer to sign in\n";
        cout << "1: Name \n";
        cout << "2: Username \n";
        cout << "3: SSN \n";
        cout << "4: Status \n";
        cout << "5: Type\n";
        cout << "6: Organization \n";
        cout << "7: DOJ \n";
        cout << "8: DOB \n";
        cout << "9: EmailID \n";
        cout << "10: Phone Number \n";
        cout << "11: Password \n";
        return 0;
    }

    string enter_username()
    {
        string username;
        bool exist = true;
        while (exist)
        {
            exist = false;
            cout << "Enter your username::";
            cin >> username;
            for (int i = 0; i < customer_id; i++)
            {
                if (customer[i][1] == username)
                {
                    exist = true;
                    break;
                }
            }
            if (exist)
                cout << "This username already exists, please enter a different username.\n";
        }
        return username;
    }

    int interest_pay()
    {
        float totalPaidInterest = 0.0f;
        float positiveInterest = 0.0f;
        float negativeInterest = 0.0f;

        for (int i = 0; i < customer_id; i++)
        {
            float currentBalance = transaction[i].back();
            float interestAmount = (interest * currentBalance) / 100.0f;
            float newBalance = currentBalance + interestAmount;

            if (interestAmount < 0)
            {
                negativeInterest -= interestAmount;
            }
            else
            {
                positiveInterest += interestAmount;
            }

            transaction[i].push_back(newBalance);
            msg[i].push_back("The interest of " + to_string(interestAmount) + " has been added to your account.");
        }

        cout << "The interest payment is done." << endl;
        cout << "The total positive interest paid is: " << positiveInterest << endl;
        cout << "The total negative interest paid is: " << negativeInterest << endl;
        cout << "The net interest paid is: " << (positiveInterest - negativeInterest) << endl;

        wait();
        return 0;
    }

    int popup_caution()
    {
        for (int i = 0; i < customer_id; i++)
        {
            if (transaction[i].back() < 0)
            {
                std::string message = "Please make your account balance positive to avoid the account to be frozen.";
                std::cout << "The warning has been sent to " << customer[i][0] << " with a negative balance of: " << transaction[i].back() << std::endl;
            }
        }
        return 0;
    }

    int disp_neg_balance_accounts()
    {
        bool hasNegativeBalance = false;
        for (int i = 0; i < customer_id; i++)
        {
            if (transaction[i].back() < 0)
            {
                if (!hasNegativeBalance)
                {
                    cout << "The accounts with negative balance are:\n";
                    hasNegativeBalance = true;
                }
                cout << customer[i][0] << " has a negative balance of :: " << transaction[i].back() << endl;
            }
        }
        if (!hasNegativeBalance)
        {
            cout << "No accounts have a negative balance.\n";
        }
        wait();
        return 0;
    }

    int disp_pos_balance_accounts()
    {
        bool has_positive_balance[customer_id] = { false };
        int num_positive_balances = 0;

        for (int i = 0; i < customer_id; i++)
        {
            for (int j = 0; j < transaction[i].size(); j++)
            {
                if (transaction[i][j] > 0)
                {
                    has_positive_balance[i] = true;
                    num_positive_balances++;
                    break;
                }
            }
        }

        for (int i = 0; i < customer_id; i++)
        {
            if (has_positive_balance[i])
            {
                cout << customer[i][0] << " has a positive balance of :: " << transaction[i].back() << endl;
            }
        }

        wait();
        return num_positive_balances;
    }

    int stop_accounts()
    {
        for (int i = 0; i < customer_id; i++)
        {
            if (transaction[i].size() >= 2 && transaction[i][transaction[i].size() - 1] < 0 && transaction[i][transaction[i].size() - 2] < 0)
            {
                std::string message = "Your account has been frozen due to having negative balance from the last two transactions.";
                std::cout << "This account is blocked for " << customer[i][0] << " with a current balance of: " << transaction[i].back() << std::endl;
                customer[i][9] = "inactive";
            }
        }
        return 0;
    }

    int numfinal_transactions(int mainuser)
    {
        cout << "Enter the value of N::";
        int N;
        cin >> N;
        int previousbalance = 0;
        if (N >= transaction[mainuser].size())
        {
            for (auto t : transaction[mainuser])
            {
                if (t > previousbalance)
                {
                    cout << "Deposit of :: $" << t - previousbalance << endl;
                }
                else
                {
                    cout << "Withdrawal of :: $" << t - previousbalance << endl;
                }
                previousbalance = t;
            }
        }
        else
        {
            previousbalance = transaction[mainuser][transaction[mainuser].size() - N];
            for (int i = transaction[mainuser].size() - N; i < transaction[mainuser].size(); i++)
            {
                if (transaction[mainuser][i] > previousbalance)
                {
                    cout << "Deposit of :: $" << transaction[mainuser][i] - previousbalance << endl;
                }
                else
                {
                    cout << "Withdrawal of :: $" << transaction[mainuser][i] - previousbalance << endl;
                }
                previousbalance = transaction[mainuser][i];
            }
        }
        wait();
        return 0;
    }

    int summary()
    {
        std::cout << "This bank has a total customer base of: " << customer_id << std::endl;
        int active = 0, inactive = 0;
        int negative = 0, positive = 0;
        for (int i = 0; i < customer_id; i++)
        {
            if (customer[i][9] == "active")
            {
                active++;
            }
            else
            {
                inactive++;
            }
            if (transaction[i].back() < 0)
            {
                negative++;
            }
            else
            {
                positive++;
            }
        }
        std::cout << "Total number of active customers are: " << active << std::endl;
        std::cout << "Total number of inactive customers are: " << inactive << std::endl;
        std::cout << "Total number of accounts with positive balance are: " << positive << std::endl;
        std::cout << "Total number of accounts with negative balance are: " << negative << std::endl;
        return 0;
    }

    int admin_domain()
    {
        cout << "Main Admin Portal::\n";
        int so = 0;

        while (so != 7)
        {
            system("clear");
            cout << "WELCOME TO THE BANK MANGEMENT SYSTEM!\n";
            cout << "1. Pay monthly interest\n";
            cout << "2. Check accounts with negative balance\n";
            cout << "3. Check accounts with positive balance\n";
            cout << "4. Warning messages to negative balance accounts\n";
            cout << "5. Repeated negative balance block account\n";
            cout << "6. Generate summary report\n";
            cout << "7. Logout\n";

            cout << "Please enter your option::";
            cin >> so;
            switch (so)
            {
            case 1:
                cout << "Monthly interest payment portal::\n";
                interest_pay();
                break;
            case 2:
                cout << "The accounts with negative balance are::\n";
                disp_neg_balance_accounts();
                break;
            case 3:
                cout << "The accounts with positive balance are::\n";
                disp_pos_balance_accounts();
                break;
            case 4:
                cout << "Warning messages to negative balance accounts\n";
                popup_caution();
                break;
            case 5:
                cout << "Repeated negative balance block account\n";
                stop_accounts();
                break;
            case 6:
                cout << "Generated summary report\n";
                summary();
                wait();
                break;

            case 7:
                cout << "Thank You\n";
                break;

            default:
                cout << "Please enter a valid option::\n";
                wait();
                break;
            }
        }
        return 0;
    }

    int disp_present_balance(int mainuser)
    {
        if (transaction[mainuser].empty())
        {
            cout << "There are no transactions found for the user " << mainuser << endl;
        }
        else
        {
            cout << "The current balance is :: " << transaction[mainuser].back() << endl;
        }
        wait();
        return 0;
    }

    int deposit(int mainuser)
    {
        cout << "Enter the amount to be deposited ::";
        float dep = 0;
        do
        {
            cin >> dep;
            if (dep <= 0)
            {
                cout << "Enter a positive amount to be deposited ::" << endl;
            }
        } while (dep <= 0);

        float currentbal = transaction[mainuser].back();
        float newbalance = currentbal + dep;
        transaction[mainuser].push_back(newbalance);

        if (currentbal < 0 && newbalance > 0)
        {
            cout << "Your account balance has become positive and the account is in active state again\n";
            customer[mainuser][9] = "active";
        }

        msg[mainuser].push_back("The amount deposited is :: $" + to_string(dep));
        cout << "\nThe deposit has been successful" << endl;
        wait();
        return 0;
    }

    int withdraw(int mainuser)
    {
        float withdraw_amount;
        do
        {
            cout << "Enter the amount to be withdrawn: ";
            cin >> withdraw_amount;
            if (withdraw_amount <= 0)
            {
                cout << "The withdrawal amount must be positive." << endl;
            }
        } while (withdraw_amount <= 0);

        float current_balance = transaction[mainuser].back();
        if (withdraw_amount > current_balance)
        {
            current_balance -= 10;
            transaction[mainuser].push_back(current_balance);
            cout << "\nThis account does not have enough balance :: Overdraft fee of $10 is charged" << endl;
        }
        else
        {
            current_balance -= withdraw_amount;
            transaction[mainuser].push_back(current_balance);
            cout << "\nThe withdrawal has been successful" << endl;
        }

        msg[mainuser].push_back("The amount withdrawn is:: $" + to_string(withdraw_amount));
        wait();
        return 0;
    }

    int transfer(int mainuser)
    {
        cout << "Enter the destination account number ::";
        int desid;
        do
        {
            cin >> desid;
            if (desid - 9999999 > customer_id && desid - 9999999 < 0)
            {
                cout << " The given destination customer account does not exist" << endl;
            }
            else
                break;
        } while (true);
        cout << "Enter the desired amount to transfer";
        float trans = 0;
        while (trans <= 0)
        {
            cin >> trans;
            cout << "Enter a positive amount to transfer" << endl;
        }
        transaction[mainuser].push_back(transaction[mainuser].back() - trans);
        transaction[desid - 9999999].push_back(transaction[desid - 9999999].back() + trans);
        msg[mainuser].push_back("$" + to_string(trans) + " The amount has been transferred to " + to_string(desid));
        msg[desid - 9999999].push_back("$" + to_string(trans) + " The amount has been received from " + to_string(mainuser + 9999999));
        if (transaction[desid - 9999999].back() > 0)
        {
            cout << "Your destination account balance has become positive and account is in active state again\n";
            customer[desid - 9999999][9] = "active";
        }
        cout << "The transfer was successful";
        wait();
        return 0;
    }

    int inbox(int mainuser)
    {
        cout << "How many messages do you wish to read?";
        int count;
        cin >> count;
        if (count > msg[mainuser].size())
        {
            cout << "There are not enough messages. Reading all messages:\n";
            for (auto message : msg[mainuser])
            {
                cout << message << endl;
            }
        }
        else
        {
            cout << "Reading " << count << " messages:\n";
            int startIndex = msg[mainuser].size() - count;
            for (int i = startIndex; i < msg[mainuser].size(); i++)
            {
                cout << msg[mainuser][i] << endl;
            }
        }
        wait();
        return 0;
    }
    int customerinfo_updation(string Name, string username, string password, string Email_Id, string phonenumber, string SSN, string org, string doj, string dob, string status, string type)
    {
        if (customer_id < 100)
        {
            customer[customer_id][0] = Name;
            customer[customer_id][1] = username;
            customer[customer_id][2] = password;
            customer[customer_id][3] = Email_Id;
            customer[customer_id][4] = phonenumber;
            customer[customer_id][5] = SSN;
            customer[customer_id][6] = org;
            customer[customer_id][7] = doj;
            customer[customer_id][8] = dob;
            customer[customer_id][9] = status;
            customer[customer_id][10] = type;
            cout << "Congratulations, the sign up process has been completed. Your Customer ID is " << customer_id + 1 << endl;
            customer_id++;
        }
        else
        {
            cout << "Bank Overflow:: Unable to register:: Sorry for the inconvenience:: we are increasing our scope and resources" << endl;
        }
        return 0;
    }

    int Disp_Admin()
    {
        string username;
        string password;
        int attempts = 3;

        while (attempts > 0)
        {
            cout << "\n Admin username ::: ";
            cin >> username;
            cout << "\n Password ::: ";
            cin >> password;
            if (username == admin[1] && password == admin[2])
            {
                cout << "\n Welcome to the admin portal.\n";
                admin_domain();
                return 0;
            }
            attempts--;
            cout << "\n The given username or password is invalid. " << attempts << " attempts left.\n";
        }
        cout << "\n Too many failed attempts. Please try again later.\n";
        return 0;
    }

    int Disp_Customer()
    {
        if (customer_id == 0)
        {
            cout << "This bank has no customer:: Please signup first\n";
            return 0;
        }
        string username;
        string password;
        int i = 0;
        bool matching = false;
        while (!matching)
        {
            cout << "\n Customer username ::: ";
            cin >> username;
            cout << "\n Password ::: ";
            cin >> password;
            for (i = 0; i < customer_id; i++)
            {
                if (customer[i][1] == username)
                    if (customer[i][2] == password)
                    {
                        matching = true;
                        if (customer[i][9] == "inactive")
                        {
                            cout << "This account is blocked";
                            matching = false;
                        }
                        break;
                    }
                    else
                    {
                        matching = false;
                        cout << "\nThe given username and password do not match";
                        break;
                    }
            }
            if (!matching)
                cout << "\nPlease enter the correct customer info\n";
        }
        customer_domain(i);
        return 0;
    }

    int showcustomersignup()
    {
        system("clear");
        string name;
        cout << "Customer signup information page\n";
        cout << "Enter your name\n";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your username\n";
        string username;
        username = enter_username();
        cout << "Enter your password[Must have a number,upper and lower case letter and minimum length of 6 characters]\n";
        string password;
        password = enter_password();
        cout << "Enter your email ID\n";
        string emailid;
        emailid = enter_emailID();
        cout << "Enter your phone number\n";
        string phonenumber;
        phonenumber = enter_num(10);
        cout << "Enter your SSN\n";
        string SSN;
        SSN = enter_num(9);
        cout << "Enter your organization\n";
        string org;
        cin >> org;
        cout << "Enter today's date DOJ(date of Joiing in format (MM/DD/YYYY))\n";
        string doj;
        doj = enter_date(0);
        cout << "Enter today's date DOB(date of Birth in format (MM/DD/YYYY))\n";
        string dob;
        dob = enter_date(1);
        string status = "active";
        cout << "Is a business account or personal\n";
        string type;
        cin >> type;
        customerinfo_updation(name, username, password, emailid, phonenumber, SSN, org, doj, dob, status, type);
        vector<float> trans;
        string id;
        cout << "\nPlease enter the initial deposit amount::";
        cin >> id;
        trans.push_back(stof(id));
        transaction.push_back(trans);
        vector<string> message;
        message.push_back("Welcome to the Bank");
        message.push_back("Initial deposit of $" + id + "has been deposited");
        msg.push_back(message);
        return 0;
    }

    string enter_password()
    {
        bool valid = false;
        string password;
        while (!valid)
        {
            bool leng = false, hasnumber = false, hasupperletter = false, haslowerletter = false;
            cout << "Password::";
            cin >> password;
            if (password.length() > 6)
                leng = true;
            for (int i = 0; i < password.length(); i++)
            {
                if (password[i] >= '0' and password[i] <= '9')
                    hasnumber = true;
                if (password[i] >= 'A' and password[i] <= 'Z')
                    hasupperletter = true;
                if (password[i] >= 'a' and password[i] <= 'z')
                    haslowerletter = true;
            }
            valid = (leng && hasnumber && hasupperletter && haslowerletter ? true : false);
            if (!valid)
                cout << "Please enter a valid password ";
        }
        return password;
    }

    string enter_emailID()
    {
        bool valid = false;
        string emailid;
        while (!valid)
        {
            bool hasatsymbol = false;
            cout << "email ID::";
            cin >> emailid;
            for (int i = 0; i < emailid.length(); i++)
                if (emailid[i] == '@')
                {
                    hasatsymbol = true;
                    break;
                }

            valid = (hasatsymbol ? true : false);
            if (!valid)
                cout << "Please enter a valid emailid";
        }
        return emailid;
    }

    string enter_num(int length1)
    {
        bool valid = false;
        string phonenumber;
        while (!valid)
        {
            bool leng = false, hasallnumber = false;
            if (length1 == 10)
                cout << "Phone Number::";
            else
                cout << "SSN Number::";
            cin >> phonenumber;
            cin.ignore();
            if (phonenumber.length() == length1)
                leng = true;
            for (int i = 0; i < phonenumber.length(); i++)
                if (phonenumber[i] >= '0' and phonenumber[i] <= '9')
                {
                    hasallnumber = true;
                }
                else
                {
                    hasallnumber = false;
                    break;
                }
            valid = (leng && hasallnumber ? true : false);
            if (!valid)
                cout << "Please enter a valid phone number(number of length " << length1 << ")";
        }
        return phonenumber;
    }

    int setupadmininfo()
    {
        system("clear");
        string name;
        cout << "Admin information page\n";
        cout << "Enter your name\n";
        getline(cin, name);
        admin.push_back(name);
        cout << "Enter your username\n";
        string username;
        cin >> username;
        admin.push_back(username);
        cout << "Enter your password[Must have a number,upper and lower case letter and minimum length of 6 characters]\n";
        string password;
        password = enter_password();
        admin.push_back(password);
        cout << "Enter your email ID\n";
        string emailid;
        emailid = enter_emailID();
        admin.push_back(emailid);
        cout << "Enter your phone number\n";
        string phonenumber;
        phonenumber = enter_num(10);
        admin.push_back(phonenumber);
        cout << "Enter your SSN\n";
        string referencenumber;
        cin >> referencenumber;
        admin.push_back(referencenumber);

        return 0;
    }

    int customer_domain(int mainuser)
    {
        int choice = 0;

        cout << "Main Customer Portal:\n";
        do
        {
            cout << "WELCOME TO THE BANK MANGEMENT SYSTEM!\n";
            cout << "1. Statement summary last N transactions\n";
            cout << "2. Show the current balance\n";
            cout << "3. Withdraw amount\n";
            cout << "4. Deposit amount\n";
            cout << "5. Transfer to another account\n";
            cout << "6. Check inbox\n";
            cout << "7. Exit\n";

            cout << "Enter your choice: ";
            cin >> choice;
            cout << endl;

            switch (choice)
            {
            case 1:
            {
                cout << "Statement summary last N transactions:\n";
                numfinal_transactions(mainuser);
                break;
            }
            case 2:
            {
                cout << "Current balance: ";
                disp_present_balance(mainuser);
                break;
            }
            case 3:
            {
                cout << "Withdraw amount:\n";
                withdraw(mainuser);
                break;
            }
            case 4:
            {
                cout << "Deposit amount:\n";
                deposit(mainuser);
                break;
            }
            case 5:
            {
                cout << "Transfer to another account:\n";
                transfer(mainuser);
                break;
            }
            case 6:
            {
                cout << "Check inbox:\n";
                inbox(mainuser);
                break;
            }
            case 7:
            {
                cout << "Thank You. Goodbye.\n";
                break;
            }
            default:
            {
                cout << "Invalid Choice. Please try again.\n";
                break;
            }
            }
        } while (choice != 7);

        return 0;
    }

    int adminrequired()
    {
        cout << "=== Your system requires a few parameters to be set up before starting ===\n";
        cout << "1: Admin Information\n";
        cout << "2: Interest Rate\n";
        cout << "3: Customer signup information requirement\n";
        cout << "4: Maximum initial targeted customer base\n";
        cout << "Are you ready to get started? (Enter 1 if ready or else press any other key to exit)\n";
        int k;
        cin >> k;
        cin.ignore();
        if (k != 1)
        {
            wait();
            exit(0);
        }
        else
            setupadmininfo();
        for (auto x : admin)
            cout << x << "\n";
        cout << "Verify the given information above.";
        wait();
        enter_Bank_info();
        wait();
        return 0;
    }





};



int main()
{
    Customer client;

    client.adminrequired();

    int so = 0;
    while (so != 4)
    {
        system("clear");
        cout << "WELCOME TO THE BANK MANAGEMENT SYSTEM!\n";
        cout << "1. Admin signin\n";
        cout << "2. Customer signin\n";
        cout << "3. Customer signup\n";
        cout << "4. Exit\n";

        cout << "Enter your option::";
        cin >> so;
        switch (so)
        {
        case 1:
            cout << "Admin signin page::\n";
            client.Disp_Admin();
            client.wait();
            break;
        case 2:
            cout << "Customer signin page::\n";
            client.Disp_Customer();
            client.wait();
            break;
        case 3:
            cout << "Customer signup page::\n";
            client.showcustomersignup();
            client.wait();
            break;
        case 4:
            cout << "Thank you for using our bank\n";
            client.wait();
            break;
        default:
            cout << "Please enter a valid option::\n";
            client.wait();
            break;
        }
    }

    return 0;
}

int encriptionoffest = 5;
struct BankCustomer {
    int ssn;
    std::string name;
    std::vector<int> DOB;
    std::string org;
    std::vector<std::string> messages;
    std::vector<double> transactions;
};
std::string encrypt(std::string input, int offset) {
    char encstrig[20];
    int j = 0;
    for (auto i : input) {
        encstrig[j] = input[j] + offset;
        j++;
    }
    return std::string(encstrig);
}
BankCustomer encrypt(BankCustomer c) {
    BankCustomer encryptrdobject;
    encryptrdobject.name = encrypt(c.name, encriptionoffest);
    encryptrdobject.org = encrypt(c.org, encriptionoffest);
    encryptrdobject.DOB = c.DOB;
    encryptrdobject.ssn = c.ssn;
    std::vector<std::string> encmessages;
    for (auto i : c.messages)
        encmessages.push_back(encrypt(i, encriptionoffest));
    encryptrdobject.messages = encmessages;
    encryptrdobject.transactions = c.transactions;
    return encryptrdobject;
}
std::ofstream& operator << (std::ofstream& out, BankCustomer& c)
{

    out << "Name :: " << c.name << "\n";
    out << "Organization :: " << c.org << "\n";
    out << "DOB :: ";
    int k = 0;
    for (auto i : c.DOB) {
        if (k < 2)
            out << i << "/";
        else
            out << i;
        k++;
    }
    out << "\n";
    out << "SSN :: " << encrypt(std::to_string(c.ssn), encriptionoffest)
        << "\n";
    out << "Transactions :: ";
    for (auto i : c.transactions)
        out << i << ",";
    out << "\n";
    out << "Messages :: ";
    for (auto i : c.messages)
        out << i << ",";
    out << "\n";
    return out;
}
int encrypt_main() {
    BankCustomer sapAccount;
    sapAccount.transactions.push_back(234.234);
    sapAccount.transactions.push_back(24.234);
    sapAccount.transactions.push_back(-24.234);
    sapAccount.messages.push_back("Welcome");
    sapAccount.messages.push_back("Withdrawal of 100$");
    sapAccount.name = "SAP";
    sapAccount.org = "UC";
    std::vector<int> dob = { 12,14,1995 };
    sapAccount.DOB = dob;
    sapAccount.ssn = 3251235;
    BankCustomer pasAccount;
    pasAccount.transactions.push_back(235);
    pasAccount.transactions.push_back(235);
    pasAccount.transactions.push_back(-125);
    pasAccount.messages.push_back("Welcome");
    pasAccount.messages.push_back("Withdrawal of 1450$");
    pasAccount.name = "PAS";
    pasAccount.org = "PG";
    std::vector<int> dob1 = { 12,214,1896 };
    pasAccount.DOB = dob1;
    pasAccount.ssn = 346457;
    std::ofstream file1;
    file1.open("exampleoutput1.txt");
    if (!file1.is_open()) {
        std::cout << "The file is not opened";
    }
    auto y = encrypt(sapAccount);
    file1 << y;
    y = encrypt(pasAccount);
    file1 << y;
    return 0;
}