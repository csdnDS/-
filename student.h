#pragma once

class student{
private:
    char Student_Name[50];
    int Roll_no;
    int SocialStudies_Marks,Statistics_Marks,Math_Marks,English_Marks,Computer_Marks;
    double Student_Percentage;
    char Student_Grade;
    bool flag;   // To avoid the same Roll_no
    void CalculateGrade();
public:
    student();
    void getdata();
    void CheckForDuplicationInFile();
    void showdata();
    void TabularDisplay();
    int GetStudentRollNo();
    void ShowStudentRecord(int);
    void Write_Student_Record_In_File();
    void Update_Student_Record(int);
    void Delete_From_Duplicate_File(int);
    void Delete_Student_Record(int);
    void Show_Result_Menu();
    void Display_Class_Result();

};
