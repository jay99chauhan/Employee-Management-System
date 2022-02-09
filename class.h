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

using namespace std;

void waitForEnter()
{
    cout << "\n\nPress enter to go back: ";
    cin.get();
}

// department class
class department {    
    
    public: 
        
        char dept_id[5];
        char dept_name[10];  
        char dept_head[15];

    public:
    //department get data
    void getData(){
        system("cls");
        fstream file;
        file.open("department_info.txt", ios::app);
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Department Info -------------------------------------------" << endl;        
        cout<<"Enter Department ID: "<<endl;
        cin>>dept_id;
        cout<<"Enter Department Name: "<<endl;
        //cin>>dept_name;
        fflush(stdin);
        cin.getline(dept_name,5);
        cout<<"Enter Department Head: "<<endl;
        cin.getline(dept_head,15);
        //cin>>dept_head;        
        file<< " " <<dept_id<< " " <<dept_name<< " " <<dept_head<<"\n";    
        file.close();
    }

    //department show data
    void showData(void){
    system("cls");
    int total = 1;
    fstream file;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Department Record Data -------------------------------------------" << endl;
    file.open("department_info.txt", ios::in);
    if (!file){
        cout << "\n\t\t\tNo Data is Present... ";
        file.close();
    }
    else{
        file >> dept_id >> dept_name >> dept_head;
        cout << "\n -------------------------------------------------------------------------------------------------";
        cout << "\n||      ID    ||    Department Name    ||    Head    ||";
        cout << "\n -------------------------------------------------------------------------------------------------";
        while (!file.eof())
        {
            cout << "\n";
            cout << total++ <<"\t "<< dept_id << "\t\t " << dept_name << "\t\t  " << dept_head << "\t\t   ";
            file >> dept_id >> dept_name >> dept_head;
        }
    }
    file.close();
    waitForEnter();
    }
};

//employee class
class employee: public department {
    public:
    char emp_id[5];
    char emp_name[15];
    char emp_gender;
    char emp_dept[10];
    
    public:
    //employee get data
void getData(){
    system("cls");
        p:
        char checkId[5];
        fstream file;
        file.open("employee_info.txt", ios::out | ios::app);
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Employee Info -------------------------------------------" << endl;        
        cout<<"Enter Employee ID: "<<endl;
        cin>>emp_id;

        bool flag1=search_employee(emp_id);
        if(flag1){ 
            cout<<"ID already exists. Please enter a unique ID."<<endl;
            goto p;
        } 
 
        cout<<"Enter Employee Name: "<<endl;
        cin>>emp_name;
        cout<<"Enter Employee Gender: "<<endl;
        cin>>emp_gender;
        start:
        cout<<"Enter Employee Department: "<<endl;
        cin>>emp_dept;
        bool flag = search_department(emp_dept);            
        if(flag){
                
        file << " " << emp_id << " " << emp_name << " " << emp_gender << " " << emp_dept << "\n";
        } else {
            cout<<"No such Department"<<endl;
            goto start;
        }   
        file.close();        
    }


    //employee show data
void showData(void){
    system("cls");
    
    cout<<" emp id "<< emp_id << " emp name " << emp_name << " gender "<< emp_gender << " dept "<<  emp_dept <<endl;
    fstream show_file;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Employee Record Data -------------------------------------------" << endl;
    show_file.open("employee_info.txt", ios::in);
    if (!show_file) {
        cout << "\n\t\t\tNo Data is Present... ";
        show_file.close();
    } else {
     show_file >> emp_id >> emp_name >> emp_gender >> emp_dept;
        cout << "\n -------------------------------------------------------------------------------------------------";
        cout << "\n||    Employee ID   ||    Employee Name   ||    Gender  ||   Department  ||";
        cout << "\n -------------------------------------------------------------------------------------------------";
        while (!show_file.eof()) {
            cout << "\n";
            cout <<"\t"<< emp_id << "\t\t  " << emp_name << "\t\t\t  " << emp_gender << "\t\t   "<< emp_dept;
            show_file >> emp_id >> emp_name >> emp_gender >> emp_dept;
        }
    }
    show_file.close();
    }

    void search(); //search function declaration
    void update(); //update function declaration
    void del(); //delete function declaration
    int search_department(char* t); //check department function declaration
    int search_employee(char* t);  //check employee function declaration
};

// salary class
class salary:public employee{
    int sal;
    public:
    //salary get data
    void getData(){
        fstream file;
        file.open("salary.txt", ios::in | ios::out | ios::app);
        cout<<"Enter Salary: "<<endl;
        cin>>sal;
        file << " " << sal <<"\n";
        file.close();
    }

    //salary show data
    void showData(){
        fstream file;
        file.open("salary.txt", ios::in | ios::out);
         if (!file) {
        cout << "\n\t\t\tNo Data is Present... ";
            file.close();
        } else {
        file >> sal;
        cout << "\n ------------------";
        cout << "\n||    Salary   ||";
        cout << "\n ------------------";
        while (!file.eof()) {
            cout << "\n";
            cout << sal;
            file >> sal;
        }
    }
    file.close();

    }
};


