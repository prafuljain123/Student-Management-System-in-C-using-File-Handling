#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <string_view>
#include <regex>
using namespace std;
bool Emailcheck(string email)
{
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}
class Student
{
private:
    string name, roll_no, email_id,contact_no, course,address;

public:
    void menu();
    void insert();
    void display();
    void modify();
    void search();
    void deleted();
};

void Student ::menu()
{
menustart:
    int choice;
    char x;
    system("cls");

    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t|----------- Student Management System  ----------|" << endl;
    cout << "\t\t---------------------------------------------------" << endl;

    cout << "\t\t 1. Enter New Record " << endl;
    cout << "\t\t 2. Display Record " << endl;
    cout << "\t\t 3. Modify Record " << endl;
    cout << "\t\t 4. Search Record " << endl;
    cout << "\t\t 5. Delete Record " << endl;
    cout << "\t\t 6. Exit " << endl;

    cout << "\tEnter your Choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        do
        {
            insert();
            cout << "\n\t\tAdd Another Student Record(Y, N) : ";
            cin >> x;
            if(x=='n'||x=='N')break;
        } while (x == 'Y' || x == 'y');
        break;

    case 2:
        display();
        break;

        case 3:
            modify();
            break;

        case 4:
            search();
            break;

        case 5:
            deleted();
            break;

    case 6:
        exit(0);

    default:
        cout << "\tInvalid Choice! Please Try Again..";
        break;
    }
    getch();
    goto menustart;
}

void Student ::display()
{
    system("cls");
    fstream file;
    int total = 0;

    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t|---------     Student Record Table     ----------|" << endl;
    cout << "\t\t---------------------------------------------------" << endl;

    file.open("student.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\tNo Data is Present....";
        file.close();
    }
    else
    {
        file >> name >> roll_no >> email_id >> course >> contact_no >> address;
        while (!file.eof())
        {
            cout << "\n\n\t\t Student No.: " << ++total << endl;
            cout << "\t\t Student Name: " << name << endl;
            cout << "\t\t Student Roll No.: " << roll_no << endl;
            cout << "\t\t Student Email Id: " << email_id << endl;
            cout << "\t\t Student Course: " << course << endl;
            cout << "\t\t Student Contact No.: " << contact_no << endl;
            cout << "\t\t Student Address: " << address << endl;
            file >> name >> roll_no >> email_id >> course >> contact_no >> address;
        }
        if (total == 0)
        {
            cout << "\n\t\tNo Data is Present...."<<endl;;
        }
        cout<<"\nPress Enter key to Continue....";
    }
    file.close();
}
void Student ::insert()
{
    system("cls");
    fstream file;

    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t|---------      Add Student Details     ----------|" << endl;
    cout << "\t\t---------------------------------------------------" << endl;

    cout << "\t\tEnter Name: ";
    cin >> name;

    cout << "\t\tEnter Roll No.: ";
    cin >> roll_no;
    email:
    cout << "\t\tEnter Email Id(abc@gmail.com): ";
    cin >> email_id;
    if(!Emailcheck(email_id)){
        cout << "\t\t Your Email-Id is InValid" << endl;
        goto email;
    }
    cout << "\t\tEnter Course: ";
    cin >> course;
    contact:
    cout << "\t\tEnter Contact No.: ";
    cin >> contact_no;
    if(contact_no.size()!=10){
        cout << "\t\t Please Enter Only 10 Digits..." << endl;
        goto contact;
    }
    cout << "\t\tEnter Address: ";
    cin >> address;

    file.open("student.txt", ios::app | ios::out);
    file << " " << name << " " << roll_no << " " << email_id << " " << course << " " << contact_no << " " << address << "\n";
    file.close();
}

void Student ::modify()
{
    system("cls");
    fstream file, file1;
    int found = 0;
    string rollno;

    cout << "\t\t---------------------------------------------------" << endl;
    cout << "\t\t|---------     Student Modify Details    ----------|" << endl;
    cout << "\t\t---------------------------------------------------" << endl;

    file.open("student.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\tNo Data is Present....";
        file.close();
    }
    else
    {
        cout << "\nEnter Roll No. of Student which you want to Modify: ";
        cin >> rollno;
        file1.open("record.txt", ios::app | ios::out);
        file >> name >> roll_no >> email_id >> course >> contact_no >> address;
        while (!file.eof())
        {
            if (rollno != roll_no)
            {
                file1 << " " << name << " " << roll_no << " " << email_id << " " << course << " " << contact_no << " " << address << "\n";
            }
            else
            {
                cout << "\t\tEnter Name: ";
                cin >> name;

                cout << "\t\tEnter Roll No.: ";
                cin >> roll_no;
                email:
                cout << "\t\tEnter Email Id: ";
                cin >> email_id;
                if(!Emailcheck(email_id)){
                    cout << "\t\t Your Email-Id is InValid" << endl;
                    goto email;
                }
                cout << "\t\tEnter Course: ";
                cin >> course;
                contact:
                cout << "\t\tEnter Contact No.: ";
                cin >> contact_no;
                if(contact_no.size()!=10){
                    cout << "\t\tPlease Enter Only 10 Digits..." << endl;
                    goto contact;
                }
                cout << "\t\tEnter Address: ";
                cin >> address;
                file1 << " " << name << " " << roll_no << " " << email_id << " " << course << " " << contact_no << " " << address << "\n";
                found++;
            }
            file >> name >> roll_no >> email_id >> course >> contact_no >> address;
            
        }
        
        if(found == 0){
            cout<<"\n\t\tStudent Roll No. Not Found...";
        }else{
            remove("student.txt");
            rename("record.txt" , "student.txt");
        }
        file.close();
        file1.close();
    }
}

void Student :: search(){
    system("cls");
    fstream file;
    int found = 0;
    file.open("student.txt", ios::in);
    if (!file)
    {
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Student Search Data --------------------------------------------" << endl;
        cout << "\n\t\tNo Data is Present... " << endl;
    }
    else
    {
        string rollno;
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Student Search Table --------------------------------------------" << endl;
        cout << "\nEnter Roll No. of Student which you want to search: ";
        cin >> rollno;
        file >> name >> roll_no >> email_id >> course >> contact_no >> address;
        while (!file.eof())
        {
            if (rollno == roll_no)
            {
                cout << "\n\n\t\tName: " << name << "\n";
                cout << "\t\tRoll No.: " << roll_no << "\n";
                cout << "\t\tEmail Id: " << email_id << "\n";
                cout << "\t\tCourse: " << course << "\n";
                cout << "\t\tContact No.: " << contact_no << "\n";
                cout << "\t\tAddress: " << address << "\n";
                found++;
            }
            file >> name >> roll_no >> email_id >> course >> contact_no >> address;
        }
        if (found == 0)
        {
            cout << "\nStudent Roll NO. Not Found....";
        }
        file.close();
    }
}

void Student ::deleted(){
    system("cls");
    fstream file, file1;
    int found = 0;
    string roll;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Delete Student Details ------------------------------------------" << endl;
    file.open("student.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\tNo Data is Present..";
        file.close();
    }
    else
    {
        cout << "\nEnter Roll No. of Student which you want Delete Data: ";
        cin >> roll;
        file1.open("record.txt", ios::app | ios::out);
        file >> name >> roll_no >> email_id >> course >> contact_no >> address;
        while (!file.eof())
        {
            if (roll != roll_no)
            {
                file1 << " " << name << " " << roll_no << " " << email_id << " " << course << " " << contact_no << " " << address << "\n";
            }
            else
            {
                found++;
                cout << "\n\t\t\tSuccessfully Delete Data";
            }
            file >> name >> roll_no >> email_id >> course >> contact_no >> address;
        }
        if (found == 0)
        {
            cout << "\n\t\t\t Student Roll NO. Not Found....";
        }
        file1.close();
        file.close();
        remove("student.txt");
        rename("record.txt", "student.txt");
    }
}
int main()
{
    Student stu;
    stu.menu();
    return 0;
}
