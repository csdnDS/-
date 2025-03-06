#include "student.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>

using namespace std;

int RollNoToBeUpdate = 0;

student::student(){       // construction function
    ofstream outFile("student.dat",ios::binary|ios::app);
    outFile.close();
    ofstream outDFile("DuplicateCheckingFile.txt",ios::app);
    outDFile.close();
}

void student::getdata(){     //// get the student's data
    flag=false;
    cout<<"Enter the Roll No of the Student : ";
    cin>>Roll_no;
    if(RollNoToBeUpdate!=Roll_no)
        CheckForDuplicationInFile();
    if(flag==true){
        cout<<"Error duplicate record"<<endl;
        return;
    }
    cout<<"\n\nEnter the name of student : ";
    cin.ignore();
    cin.getline(Student_Name,50);
    cout<<"\nEnter The Marks in SocialStudies out of 100 : ";
    cin>>SocialStudies_Marks;
    cout<<"\nEnter The Marks in Statistics out of 100 : ";
    cin>>Statistics_Marks;
    cout<<"\nEnter The Marks in Math out of 100 : ";
    cin>>Math_Marks;
    cout<<"\nEnter The Marks in English out of 100 : ";
    cin>>English_Marks;
    cout<<"\nEnter The Marks in Computer out of 100 : ";
    cin>>Computer_Marks;
    CalculateGrade();   //then calculate the grade
}


void student::CheckForDuplicationInFile(){    // Determine if there are duplicate roll no
    int Current_Rollno=0;
    flag=false;
    ifstream infile("DuplicateCheckingFile.txt");
    while(infile>>Current_Rollno){
        if(Current_Rollno==Roll_no)
            flag=true;
    }
    infile.close();
    if(flag==false){
        ofstream outfile("DuplicateCheckingFile.txt",ios::app);
        outfile<<Roll_no<<endl;
        outfile.close();
    }
}

void student::showdata(){     //show student's data
    cout<<"\n\t\t\t\tRoll Number of student = "<<Roll_no;
    cout<<"\n\t\t\t\tName of student = "<<Student_Name;
    cout<<"\n\t\t\t\tMarks in SocialStudies = "<<SocialStudies_Marks;
    cout<<"\n\t\t\t\tMarks in Statistics = "<<Statistics_Marks;
    cout<<"\n\t\t\t\tMarks in Math = "<<Math_Marks;
    cout<<"\n\t\t\t\tMarks in English = "<<English_Marks;
    cout<<"\n\t\t\t\tMarks in Computer = "<<Computer_Marks;
    cout<<"\n\t\t\t\tPercentage of student = "<<Student_Percentage;
    cout<<"\n\t\t\t\tGrade of student = "<<Student_Grade;
}

void student::Write_Student_Record_In_File(){
    ofstream outFile;
    outFile.open("student.dat",ios::binary|ios::app);
    getdata();
    if(flag==false){
        outFile.write(reinterpret_cast<char *>(this),sizeof(student));
        outFile.close();
        cout<<"\n\n student record has been created";
    }
    if(flag==true){
        cout<<"record not created due to duplication\n";
        outFile.close();
    }
}

void student::Update_Student_Record(int n){
    RollNoToBeUpdate=n;
    bool found = false;
    fstream File;
    File.open("student.dat",ios::binary|ios::in|ios::out);
    if(!File){
        cout<<"File could not opened! Press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    while(!File.eof()&&found==false){
        File.read(reinterpret_cast<char *>(this),sizeof(student));
        if(GetStudentRollNo()==n){
            showdata();
            cout<<"\n\n Please Enter The New Details Of Student"<<endl;
            getdata();
            if(flag==false){
                int pos=(-1)*static_cast<int>(sizeof(*this));
                File.seekp(pos,ios::cur);
                File.write(reinterpret_cast<char *>(this),sizeof(student));
            }
            found = true;
        }
    }
    File.close();
    if(flag==true){
        cout<<"could not update because this RollNo already exists";
    }
    if(found==false){
        cout<<"\n\n Record Not Found";
    }
    cin.ignore();
    cin.get();
    if(flag== false&&found== true&&RollNoToBeUpdate!=Roll_no){
        Delete_From_Duplicate_File(n);
        RollNoToBeUpdate=0;
    }
}

// calculate student's grade
void student::CalculateGrade(){
    Student_Percentage=(SocialStudies_Marks+Statistics_Marks+Math_Marks+English_Marks+Computer_Marks)/5.0;
    if(Student_Percentage>=80)
        Student_Grade='A';
    if(Student_Percentage>=70&&Student_Percentage<80)
        Student_Grade='B';
    if(Student_Percentage>=60&&Student_Percentage<70)
        Student_Grade='C';
    if(Student_Percentage<60)
        Student_Grade='F';
}

void student::TabularDisplay(){
    cout<<"\t\t\t"<<setw(3)<<Roll_no<<setw(15)<<Student_Name<<setw(11)<<SocialStudies_Marks<<setw(9)
        <<Statistics_Marks<<setw(9)<<Math_Marks<<setw(9)<<English_Marks<<setw(8)<<Computer_Marks<<endl;
}

int student::GetStudentRollNo(){
    return Roll_no;
}

void student::ShowStudentRecord(int n){
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be opened! "<<endl;
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while(inFile.read(reinterpret_cast<char*>(this),sizeof(student))){
        if(GetStudentRollNo()==n){
            showdata();
            flag = true;
        }
    }   //end of while loop
    inFile.close();
    if(flag==false)
        cout<<"\n\n record does not exist";
    cin.ignore();
    cin.get();
}

void student::Delete_Student_Record(int n) {
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile){
        cout<<"\nFile could not open!";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream  outFile;
    outFile.open("Temp.dat",ios::out);
    inFile.seekg(0,ios::beg);
    bool found = false;
    while(inFile.read(reinterpret_cast<char *>(this),sizeof(student))){
        if(GetStudentRollNo()==n) {
        	found = true;
        }else{
        	outFile.write(reinterpret_cast<char *>(this),sizeof(student));
		}
    }
    if(found){
    	outFile.close();
    	inFile.close();
    	remove("student.dat");
    	rename("Temp.dat","student.dat");
    	cout<<"Record deleted";
    	cin.ignore();
    	cin.get();
    	Delete_From_Duplicate_File(n);
	}else{
		remove("Temp.dat");
		cout << "Record with Roll No " << n << " does not exist." << endl;
		cin.ignore();
		cin.get();
	}
}


void student::Delete_From_Duplicate_File(int n) {
    int Current_RollNo;
    ifstream inFile("DuplicateCheckingFile.txt");
    ofstream outFile("TempFile.txt");
    inFile.seekg(0,ios::beg);
    while(!inFile.eof()){
        inFile>>Current_RollNo;
        if(Current_RollNo!=n){
            outFile<<"\n"<<Current_RollNo;
        }
    }
    inFile.close();
    outFile.close();
    remove("DuplicateCheckingFile.txt");
    rename("TempFile.txt","DuplicateCheckingFile.txt");
    cin.ignore();
    cin.get();
}

void student::Show_Result_Menu() {
      char ch;
      int rno;
      system("cls");
      cout<<"\n\n\n\t\t\t\t\t****  RESULT MENU  ****";
      cout<<"\n\n\n\t\t\t\t\t1. Class Result";
      cout<<"\n\n\n\t\t\t\t\t2. Student Report Card";
      cout<<"\n\n\n\t\t\t\t\t3. Back To Main Menu";
      cout<<"\n\n\n\t\t\t\t\tEnter Choice (1/2/3)? :";
      cin>>ch;
    system("cls");
    switch (ch) {
        case'1':
            Display_Class_Result();
            break;
        case'2':
            cout<<"Enter the Roll No of the Student : ";
            cin>>rno;
            ShowStudentRecord(rno);
            break;
        case'3':
            break;
        default:
            cout<<"\a";
    }
}

void student::Display_Class_Result() {
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile){
        cout<<"\nFile could not open!";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\n\t\t\t\t\t\tALL CLASS RESULT "<<endl;
    cout<<"\t\t\t=================================================================="<<endl;
    cout<<"\t\t\tR.No           Name        Soc     Stats     Math     Eng     CS  "<<endl;
    cout<<"\t\t\t=================================================================="<<endl;
    while (inFile.read(reinterpret_cast<char *>(this),sizeof(student))){
        TabularDisplay();
    }
    inFile.close();
    cin.ignore();
    cin.get();
}



