#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;


// map<string, string> configuration;

class User{

    public:
        int balance;
        std::map<int, string> transactionHistoryMap;
        int phno;
        int password;
        int i = 1;

        void  retrieveData( int userTypedPhno)
        {

            string line;
            ifstream file(to_string(userTypedPhno) + ".txt");
            
            string key, value;
            while(getline(file, line)){ // loop through every line in the file
                stringstream ss(line);
                getline(ss, key, ':');
                getline(ss, value);
                if(key == "phno")
                {
                    phno = stoi(value);
                }

                else if(key == "password")
                {
                    password = stoi(value);
                }

                else if(key == "balance")
                {
                    balance = stoi(value);
                }
                else{
                    //cout << value << key ;
                    transactionHistoryMap[i]= value;
                    i += 1;
                }
                

            }

            file.close();
        }
       
    
        void checkUser(int userTypedPhno , int userTypedPassword)
        {
            retrieveData(userTypedPhno);
            if(userTypedPhno == phno)
            {
                if(userTypedPassword == password)
                {
                    cout << "correct" << endl;
                    menu();
                }
                else
                {
                    cout << "Incorrect password" << endl;
                }
            }
            else
            {
                cout << "Incorrect phno" << endl;
            }
        }


        void menu()
        {
            int choice;
            while(1)
            {
                cout << endl;
                cout << "================================================" << endl;
                cout << "       Press 1 to Deposit" << endl;
                cout << "       Press 2 to Withdrawal" << endl;
                cout << "       Press 3 to Transfer" << endl;
                cout << "       Press 4 to Show Transaction History" << endl;
                cout << "       Press 5 to Show Balance " << endl;
                cout << "       Press 6 to Cancel (or) EXit" << endl;
                cout << "================================================" << endl;
                cout << "Enter your choice : ";
                cin >> choice;
                

                switch (choice)
                {
                case 1:
                    toDeposit();
                    break;
                    
                case 2:
                    toWithDrawal();
                    break;
                    
                case 3:
                    toTransfer();
                    break;
                
                case 4:
                    showTransactionHistory();
                    break;
                
                case 5:
                    showBalance();
                    break;
                    
                case 6:
                    cout << "Thankyou!" << endl;
                    exit(1);
                    break;
                
                default:
                    cout << "Enter the correct choice" << endl;
                    break;
                }
            }

        }


        void save()
        {
            ofstream fout(to_string(phno) + ".txt");
            fout << "balance:" << balance << endl;
            fout << "phno:" << phno << endl;
            fout << "password:" << password << endl;
            for(auto collection : transactionHistoryMap){
                fout << "Transcation" << collection.first << ": " << collection.second << endl;
            }
            fout.close();
        }

    private:

        void toDeposit()
        {
            int depositAmount;
            cout << "Enter the amount to deposit : ";
            cin >> depositAmount;
            balance += depositAmount;
            save();
            cout << "================================================" << endl;
            cout << "Your amount is deposit successfully" << endl << "Your balance is : " << balance << endl;
            
        }


        void toWithDrawal()
        {
            int withDrawalAmount;
            cout << "Enter the amount to Withdrawal : ";
            cin >> withDrawalAmount;
            if( balance > withDrawalAmount)
            {
                balance -= withDrawalAmount;
                save();
                cout << "================================================" << endl;
                cout << "Your amount is deposit successfully" << endl << "Your balance is : " << balance << endl;
            }
            else
            {
                cout << "! Insufficient balance" << endl;
            }
            
        }


        void toTransfer()
        {
            int transferAmount;
            string transactionId;
            cout << "Enter the transaction id to transfer : ";
            cin >> transactionId;
            cout << endl << "Enter the amount ro transfer : ";
            cin >> transferAmount;
            
            if( balance > transferAmount)
            {
            balance -= transferAmount;

                time_t ttime = time(0);
                char* dt = ctime(&ttime);

                transactionHistoryMap.insert( {i,"nam->" + transactionId + "        Amount->" + to_string(transferAmount) +  "      At->" + dt} );
                save();
                
                User user1;
                user1.retrieveData(stoi(transactionId));
                user1.balance += transferAmount;
                user1.save();

                i += 1;
                cout << "================================================" << endl;
                cout << "Amount is Transfer successfully\a" << endl << "Your balance is : " << balance << endl;
            }
            else
            {
                cout << "! Insufficient balance" << endl;
            }
            
            
        }

        void showTransactionHistory()
        {
            cout << "Your Transaction History is:" << endl;
            for(auto collection : transactionHistoryMap){
                cout << collection.first << " " << collection.second << endl;
            }
        }


        void showBalance()
        {

            cout <<"Your balance is : " <<  balance << endl;
        }


};



int main()
{
    
    int userTypedPhno, userTypedPassword;

    int option;

    cout << endl;
    cout << "================================================" << endl;
    cout << "       Press 1 to Create a account" << endl;
    cout << "       Press 2 to Login your account" << endl;
    cout << "       Press 3 to Cancel" << endl;
    cout << "================================================" << endl;
    cout << "Enter your choice : ";
    cin >> option;


    if(option == 1)             // To create a new account
    {

        cout << "Enter the phone no to create Account details : ";       // Getting phno from user to create account
        cin >> userTypedPhno;

        cout << endl << "Enter the new password : ";                     // Getting password for login purpose
        cin >> userTypedPassword;

        ofstream fout(to_string(userTypedPhno) + ".txt");
        fout << "phno:" << userTypedPhno << endl;
        fout << "password:" << userTypedPassword << endl;
        fout << "balance:" << 1000 << endl;

        cout << "Created account Successfully";

    }
    else if(option == 2)     // User already has an account
    {

        cout << "Enter the phone no to serarch Account details : ";     // identifying his/her account
        cin >> userTypedPhno;

        cout << endl << "Enter the phone no to serarch Account details : ";
        cin >> userTypedPassword;

        User user;
        user.checkUser(userTypedPhno, userTypedPassword);               // checking password and phno from the file

    }
    else if(option == 3)
    {
        cout << "Thank you!" << endl;
    }
    else
    {
        cout << "Invaild choice , Thank you" << endl;
    }

    return 0;
}
