#include <iostream>
#include<fstream>
#include<iomanip>
#include "student.h"

using namespace std;


void entry_menu();
void display_all();

int main() {
    system("cls");
    system("color cf");
    char ch;
    student std_obj;
    cout.setf(ios::fixed|ios::showpoint);
    cout<<setprecision(2);
    do{
        system("cls");
        cout<<"\n\n\n\t\t****  WELCOME TO STUDENT DATABASE MANAGEMENT AND RESULT CALCULATION SYSTEM  ****";
        cout<<"\n\n\n\t\t\t\t\t\tHOME SCREEN";
        cout<<"\n\n\t\t\t\t\t1. Result Calculation System";
        cout<<"\n\n\t\t\t\t\t2. Student Database Management System";
        cout<<"\n\n\t\t\t\t\t3. Exit";
        cout<<"\n\n\t\t\t\tPlease Select Your Option (1-3) : ";
        cin>>ch;
        switch(ch){
            case '1':
                std_obj.Show_Result_Menu();
                break;
            case '2':
                entry_menu();  //switch to the student record management menu
                break;
            case '3':
                break;
            default:
                cout<<"\a";
        }
    }while(ch!='3');
    system("pause");
    return 0;
}

void entry_menu(){
    char ch;
    int num;
    student std;
    system("cls");
    cout<<"\n\n\n\t\t\t\t****  STUDENT RECORD MANAGEMENT MENU  ****"<<endl;
    cout<<"\n\n\t\t\t\t\t1. CREATE STUDENT RECORD";
    cout<<"\n\n\t\t\t\t\t2. SHOW RECORDS OF ALL STUDENTS";
    cout<<"\n\n\t\t\t\t\t3. SEARCH STUDENT RECORD";
    cout<<"\n\n\t\t\t\t\t4. UPDATE STUDENT RECORD";
    cout<<"\n\n\t\t\t\t\t5. DELETE STUDENT RECORD";
    cout<<"\n\n\t\t\t\t\t6. BACK TO HOME SCREEN";
    cout<<"\n\n\n\t\t\t\tPlease Enter Your Choice (1-6) : ";
    cin>>ch;
    system("cls");
    switch(ch){
        case '1':
            std.Write_Student_Record_In_File();
            break;
        case '2':
            display_all();
            break;
        case '3':
            cout<<"\n\n\t Please Enter The Roll No : ";
            cin>>num;
            std.ShowStudentRecord(num);
            break;
        case '4':
            cout<<"\n\n\t Please Enter The Roll No : ";
            cin>>num;
            std.Update_Student_Record(num);
            break;
        case '5':
            cout<<"\n\n\t Please Enter The Roll No : ";
            cin>>num;
            std.Delete_Student_Record(num);
            break;
        case '6':
            break;
        default:
            cout<<"\a";     // Alert errors by ringing a bell.
            entry_menu();
    }
}

void display_all(){
    student std;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile){
        cout<<"File could not opened! Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\n\t\t\t\t****  Here Are The Students\' Record  ****"<<endl;
    while(inFile.read(reinterpret_cast<char *>(&std),sizeof(student))){
        std.showdata();
        cout<<"\n\n\t\t\t\t=========================================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}
