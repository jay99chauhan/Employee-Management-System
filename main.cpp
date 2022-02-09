#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <chrono>
#include <unistd.h>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "class.h"
#include "search.h"

using namespace std;

//employee check
int employee::search_employee(char *t){
    //system("cls");
    ifstream file_search;
    char emp_id[5];
    
    file_search.open("employee_info.txt", ios::in); 
    if (!file_search) {
        cout << "\n\t\t\tNo Data is Present... ";
        file_search.close();
    } else {
        //cout<<"emp id "<<t<<endl;
        //cout<<"before while"<<endl;
        
        //cout<<"test "<<endl;
        //cout<<" before while emp id "<<t<<endl;
        file_search >> emp_id;
        while (!file_search.eof()) {
            //cout<<"inside while"<<endl;
            //cout<<"emp id "<<t<<endl;
            if (strcmp(t, emp_id) == 0) {
                cout << "\n---------------------\n";    
                //cout<<"emp id "<<t<<endl;          
                return 1;
            }
            file_search >> emp_id;
        }
    }
    file_search.close();
    return 0;
}
//department check
int employee::search_department(char *t){
    //system("cls");
    fstream file;
    //char checkId[5];

    file.open("department_info.txt", ios::in);
    if (!file) {
        cout << "\n\t\t\tNo Data is Present... ";
        file.close();
    } else {
        cout<<" before while dept id "<<t<<endl;
        file >> dept_id;
        cout<<" before while dept id "<<t<<endl;
        while (!file.eof()) {
            if (strcmp(t, dept_id) == 0) {
                cout<<" dept id "<<t<<endl;
                cout << "\n---------------------\n";              
                return 1;
            }
            file >> dept_id;
        }
    }
    file.close();
    return 0;
}



//search
void employee::search(){
    system("cls");
    fstream file;
    char checkId[5];
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Employee Search Data -------------------------------------------" << endl;
    file.open("employee_info.txt", ios::in);
    cout << "\n\nEnter Employee ID: ";
    cin >> checkId;
    if (!file) {
        cout << "\n\t\t\tNo Data is Present... ";
        file.close();
    } else {
        file >> emp_id >> emp_name >> emp_gender;
        while (!file.eof()) {
            if (strcmp(checkId, emp_id) == 0) {
                cout << "\n---------------------\n";
                cout << "Employee ID: " << emp_id << "\n";
                cout << "Employee Name.: " << emp_name << "\n";
                cout << "Employee Gender: " << emp_gender << "\n";                
                cout << "---------------------\n";
            }
            file >> emp_id >> emp_name >> emp_gender;
        }
    }
    file.close();
}


//update
void employee::update() {
    system("cls");
    char checkId[5];
    int found = 0;
    fstream file, file1;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Employee Modify Data ------------------------------------------" << endl;
    file.open("employee_info.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\tNo Data is Present..";
        file.close();
    }
    else
    {
        cout << "\nEnter employee id: ";
        cin >> checkId;
        file1.open("record.txt", ios::app | ios::out);
        file >> emp_id >> emp_name >> emp_gender;
        while (!file.eof())
        {
            if (strcmp(checkId, emp_id) == 0)
            {
                cout << "\n Enter Employee ID: ";
                cin >> emp_id;
                cout << "\n Enter Employee Name: ";
                cin >> emp_name;
                cout << "\n Enter Gender: ";
                cin >> emp_gender;               
                cout << "\n\nSuccessfully Updated Details Of Employee";
                file1 << " " << emp_id << " " << emp_name << " " << emp_gender << "\n";
                found++;
            }
            else
            {
                file1 << " " << emp_id << " " << emp_name << " " << emp_gender << "\n";
            }
            file >> emp_id >> emp_name >> emp_gender;
        }
        if (found == 0)
        {
            cout << "\n\n\tEmployee ID Not Found.. Please Try Again";
        }
        file1.close();
        file.close();
        remove("employee_info.txt");
        rename("record.txt", "employee_info.txt");
    }
    waitForEnter();
}

//delete
void employee::del(){
    system("cls");
    del_checkpoint:
    char checkId[5];
    fstream file, file1;
    int found = 0;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Delete Employee Data ------------------------------------------" << endl;
    file.open("employee_info.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\tNo Data is Present..";
        file.close();
    }
    else
    try
    {
        cout << "\nEnter Employee Id To Remove Data: ";
        cin >> checkId;
        file1.open("record.txt", ios::app | ios::out);
        file >> emp_id >> emp_name >> emp_gender;
        while (!file.eof())
        {
            if (strcmp(checkId, emp_id) != 0)
            {
                file1 << " " << emp_id << " " << emp_name << " " << emp_gender << "\n";
            }
            else
            {
                found++;
                cout << "\n\t\t\tSuccessfully Deleted Data";
            }
            file >> emp_id >> emp_name >> emp_gender;
        }
        if(found==0){
            
            throw found;
        }
    } catch(int ex){
            cout << "\n\n\tEmployee ID Not Found.. Please Try Again";
            goto del_checkpoint;
    }
        /*
        if (found == 0)
        {
            cout << "\n\n\tEmployee ID Not Found.. Please Try Again";
        }
        */
        file1.close();
        file.close();
        remove("employee_info.txt");
        rename("record.txt", "employee_info.txt");
        waitForEnter();
}


// function to read from attendance file.
DWORD ReadFromAFile(PVOID lpParam){
    char buffer[1024] = { 0 };  
   
    ifstream fileReader;
    fileReader.open("attendance.txt");
    
    if (fileReader.is_open()){  
      string tp;
      while(getline(fileReader, tp)){  
         cout << tp << "\n";   
      }
    }

    cout << buffer << endl;
    fileReader.close();
    return 1;
}





//main function
int main(){
    system("cls");
    time_t my_time = time(NULL);

    char buffer[1024];
    DWORD tid;
    ifstream fileReader;
    HANDLE t1;

    string username, password;
    string login_username, login_password;

    fstream log_file; //log file
    fstream log_attendance; //attendance log file

    department dept; //object creation
    employee emp; //object creation
    salary sal; // object creation

    int first_choice;
    first_checkpoint:
    cout << "\n\t\t\t -------------------------------------------";
    cout << "\n\t\t\t||  WELCOME TO EMPLOYEE MANAGEMENT SYSTEM  ||";
    cout << "\n\t\t\t -------------------------------------------";
    cout << "\n\n\t Press 1 for Employee :  "<<endl;
    cout << "\n\n\t Press 2 for Admin: "<<endl;
    cout << "\n\n\t Your Choice:  ";
    cin>>first_choice;
    if(first_choice == 1){ // employee reg and login
{
    string pass_reg = "";
    string name_reg = "";
    string pass = "";
    string name = "";
    fstream file, file1;
    char ch;
    emp_checkpoint:
    system("cls");
    cout << "\n\t\t\t -------------------------------------------";
    cout << "\n\t\t\t||  WELCOME TO EMPLOYEE MANAGEMENT SYSTEM  ||";
    cout << "\n\t\t\t -------------------------------------------";
    cout << "\n\n\t\t\t   -| Press: [1] Register & [2] Login  |-";
    int selection;
    cout << "\n\nPlease Enter Value: ";
    cin >> selection;
    // if user press [1], then it would lead them to register.
    if (selection == 1) {
        system("cls");
        cout << "\n\t\t\t\t\t---------------------------";
        cout << "\n\t\t\t\t\t>> REGISTRATION EMPLOYEE <<";
        cout << "\n\t\t\t\t\t---------------------------";
        cout << "\n\n\t\t\t\t\tEnter Your Name: ";
        cin >> name_reg;
        cout << "\n\t\t\t\t\tEnter Your Password: ";
        ch = _getch();
        while (ch != 13) {
            pass_reg.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        file.open("Ep_data.txt", ios::app);
        file << " " << name_reg << " " << pass_reg << "\n";
        file.close();
        cout << "\nRegistration Succesfully save";
        getch();
        goto emp_checkpoint;
                    log_file.open("Logs.txt", ios::app | ios::in | ios::out);
                    log_file << ctime(&my_time);
                    std::cout << ctime(&my_time) << '\n';
                    log_file << "  Username: "<<  name_reg << " has registerd with password: " << pass_reg <<" \n";
                    log_file.close();
    }
    // if user press [2], then it would lead them to login.
    else if (selection == 2) {
        system("cls");
        string emp_name;
        file.open("Ep_data.txt", ios::in);
        file1.open("employee_info.txt", ios::in);
        cout << "\n\t\t\t\t\t--------------------";
        cout << "\n\t\t\t\t\t>> LOGIN EMPLOYEE <<";
        cout << "\n\t\t\t\t\t--------------------";
        cout << "\n\n\t\t\t\t\tEnter Your Name: ";
        cin >> name;
        cout << "\n\t\t\t\t\tEnter Your Password: ";
        ch = _getch();
        while (ch != 13) {
            pass.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        file >> name_reg >> pass_reg;
        while (!file.eof()) {
            if (pass == pass_reg && name == name_reg) {
                cout << "\n\n\n\t\t\t\t\t| Verfiying EMPLOYEE |\n\t\t\t\t\t";
                for (int a = 1; a < 8; a++) {
                    cout << "...";
                }
                cout << "\n\nAccess Granted..\n\n";
                system("PAUSE");
                    log_file.open("Logs.txt", ios::app | ios::in | ios::out);
                    log_file << ctime(&my_time);
                    std::cout << ctime(&my_time) << '\n';
                    log_file << "  Username: "<<  name_reg << " has logged in with password " << pass_reg <<" \n";
                    log_file.close();

                    log_attendance.open("attendance.txt", ios::app | ios::in | ios::out);
                    log_attendance << ctime(&my_time);
                    std::cout << ctime(&my_time) << '\n';
                    log_attendance << "  Username: "<<  name_reg << " has logged in with password: " << pass_reg <<" \n";
                    log_attendance.close();

                system("cls");
                emp.showData();
                sal.showData();
            }
            else {
                cout << "\n\n\n\t\t\t\t\t| Verfiying EMPLOYEE |\n\t\t\t\t\t";
                for (int a = 1; a < 8; a++) {
                    cout << "...";
                }
                cout << "\n\nAccess Aborted...\n\n";
                system("PAUSE");
                system("cls");
                goto first_checkpoint;
            }
            file >> name_reg >> pass_reg;
        }
        file.close();
        file1.close();
    }
    else {
        cout << "\nInvalid Input.. Please Try Again..";
       goto first_checkpoint;
    }
    return 0;
}
        
    } else if(first_choice == 2){ // admin reg and login
{
    string pass_reg = "";
    string name_reg = "";
    string pass = "";
    string name = "";
    fstream file;
    char ch;
    admin_checkpoint:
    system("cls");
    cout << "\n\t\t\t -------------------------------------------";
    cout << "\n\t\t\t||  WELCOME TO EMPLOYEE MANAGEMENT SYSTEM  ||";
    cout << "\n\t\t\t -------------------------------------------";
    cout << "\n\n\t\t\t   -| Press: [1] Register & [2] Login  |-";
    int selection;
    cout << "\n\nPlease Enter Value: ";
    cin >> selection;
    // if user press [1], then it would lead them to register.
    if (selection == 1) {
        system("cls");
        cout << "\n\t\t\t\t\t---------------------------";
        cout << "\n\t\t\t\t\t>> REGISTRATION Admin <<";
        cout << "\n\t\t\t\t\t---------------------------";
        cout << "\n\n\t\t\t\t\tEnter Your Name: ";
        cin >> name_reg;
        cout << "\n\t\t\t\t\tEnter Your Password: ";
        ch = _getch();
        while (ch != 13) {
            pass_reg.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        file.open("Ad_data.txt", ios::app);
        file << " " << name_reg << " " << pass_reg << "\n";
        file.close();
        cout << "\nRegistration Succesfully save";
        getch();
        goto admin_checkpoint;
       // password_user();
    }
    // if user press [2], then it would lead them to login.
    else if (selection == 2) {
        system("cls");
        file.open("Ad_data.txt", ios::in);
        cout << "\n\t\t\t\t\t--------------------";
        cout << "\n\t\t\t\t\t>> LOGIN Admin <<";
        cout << "\n\t\t\t\t\t--------------------";
        cout << "\n\n\t\t\t\t\tEnter Your Name: ";
        cin >> name;
        cout << "\n\t\t\t\t\tEnter Your Password: ";
        ch = _getch();
        while (ch != 13) {
            pass.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        file >> name_reg >> pass_reg;
        while (!file.eof()) {
            if (pass == pass_reg && name == name_reg) {
                cout << "\n\n\n\t\t\t\t\t| Verfiying Admin |\n\t\t\t\t\t";
                for (int a = 1; a < 8; a++)
                {
                    cout << "...";
                }
                cout << "\n\nAccess Granted..\n\n";
                system("PAUSE");
                system("cls");
                goto admin;
            }
            else {
                cout << "\n\n\n\t\t\t\t\t| Verfiying Admin  |\n\t\t\t\t\t";
                for (int a = 1; a < 8; a++)
                {
                    cout << "...";
                }
                cout << "\n\nAccess Aborted...\n\n";
                system("PAUSE");
                system("cls");
                goto first_checkpoint;
            }
            file >> name_reg >> pass_reg;
        }
        file.close();
    }
    else {
        cout << "\nInvalid Input.. Please Try Again..";
       
        goto first_checkpoint;
    }
    return 0;
}
    } else {
        cout<<"Wrong Input!"<<endl;
    }
    
    
    admin:
    int user_choice;

    while(1){  
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;  
        cout << "------------------------------------- Employee Management System ------------------------------------------" << endl;
        
        cout<<"\n\n\t Press 1 to Enter Department Data:";
        cout<<"\n\n\t Press 2 to Enter Employee Data:";
        
        cout<<"\n\n\t Press 3 to Display Department Records";
        cout<<"\n\n\t Press 4 to Display Employee Records";
        
        cout<<"\n\n\t Press 5 to Search Employee Record";        
        cout<<"\n\n\t Press 6 to Update Employee Record:";
        
        cout<<"\n\n\t Press 7 to Delete Employee Data:";
        
        cout<<"\n\n\t Press 8 to View Employee logs:";     

        cout<<"\n\n\t Press 9 to Log Out";
        
        cout<<"\n\n\t Press 10 to exit";
        cout<<"\n\n\t Your choice: ";
        cin>>user_choice;   
     
        switch(user_choice){
            case 1:
                dept.getData();                                           
                break;
            case 2:
                emp.getData();
                sal.getData();
                break;                
            case 3:
                dept.showData();             
                break;
            case 4:
                emp.showData();
                cout<<"\n\n";
                sal.showData();
                break;                
            case 5:
                emp.search();
                break;                              
            case 6:
                emp.update();
                break;                
            case 7:                
                emp.del();
                break;                
            case 8:
                system("cls");
                t1 = CreateThread(NULL, 0, ReadFromAFile, &fileReader, 0, &tid);
                Sleep(5000);
                WaitForSingleObject(t1, INFINITE);
                break;                
            case 9:
                goto first_checkpoint;
                break;              
            case 10:
                exit(0);
                break;
            default:
                cout<<"Wrong Input! Please Select from number 1 to 10"<<endl;
                break;
        }          
    }
}