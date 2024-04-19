//GROUP MEMBER:

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

time_t now = time(NULL);
char* date = ctime(&now);

class nodeQ
{
    public:
        string name;
        string matricno;
        string course;
        string FYPField;
        string FYPTitle;
        string FYPStatus;
        string FYPDate;
        double FYPMark;
        nodeQ *next;
};

class StudentQ
{
    public:
        nodeQ *backPtr, *frontPtr, *markbackPtr, *markfrontPtr;
        nodeQ *create_node(string name, string matricno, string course, string FYPField, string FYPTitle, string FYPStatus, string FYPDate, double FYPMark)
        {
            nodeQ *newNode = new nodeQ;
            if(!newNode)
            {
                cout << "Memory Error" << endl;
                return NULL;
            }
            else
            {
            newNode->name = name;
            newNode->matricno = matricno;
            newNode->course = course;
            newNode->FYPField = FYPField;
            newNode->FYPTitle = FYPTitle;
            newNode->FYPStatus = FYPStatus;
            newNode->FYPDate = FYPDate;
            newNode->FYPMark = FYPMark;
            newNode->next = NULL;
            return newNode;
            }
        }
        StudentQ()
        {
            backPtr = NULL;
            frontPtr = NULL;
            markbackPtr=NULL;
            markfrontPtr=NULL;
        }
        bool isEmpty()
        {
            return (frontPtr == NULL && backPtr == NULL);
        }
        ~StudentQ()
        {
            nodeQ *temp = frontPtr;
            while (temp)
            {
                frontPtr = frontPtr->next;
                delete temp;
                temp = frontPtr;

            }
        }
        void ReadStudent()
        {
            fstream fin;
            fin.open("StudentFYP.txt", ios::in);
            string name, matricno, course, FYPField, FYPTitle, FYPStatus, FYPDate;
            double FYPMark;
            while (!fin.eof())
            {if(!fin){
                    break;}
                getline(fin, name);
                if(name == "") break;
                getline(fin, matricno);
                getline(fin, course);
                getline(fin, FYPField);
                getline(fin, FYPTitle);
                getline(fin, FYPStatus);
                getline(fin, FYPDate);
                fin >> FYPMark;
                fin.ignore();
                nodeQ *newNode = create_node(name, matricno, course, FYPField, FYPTitle, FYPStatus, FYPDate, FYPMark);
                if (frontPtr == NULL)
                {
                    frontPtr = newNode;
                    backPtr = newNode;
                    frontPtr->next = NULL;
                }
                else
                {
                    backPtr->next = newNode;
                    backPtr = newNode;
                    backPtr->next = NULL;
                }
            }
            fin.close();
        }

        void ReadMarkingOrder(){
            fstream fin;
            fin.open("MarkingOrder.txt",ios::in);
            string  matricno;
            while(!fin.eof()){
                getline(fin,matricno);
                if(matricno=="") break;
                nodeQ* temp= new nodeQ;
                temp->matricno=matricno;
                //temp= frontPtr;
                /*while(temp->matricno!=matricno){
                    temp=temp->next;
                }*/
            //nodeQ *newNode= new nodeQ;
            /*newNode->name = temp->name;
            newNode->matricno = temp->matricno;
            newNode->course = temp->course;
            newNode->FYPField = temp->FYPField;
            newNode->FYPTitle = temp->FYPTitle;
            newNode->FYPStatus = temp->FYPStatus;
            newNode->FYPDate = temp->FYPDate;
            newNode->FYPMark = temp->FYPMark;
            newNode->next = NULL;*/
            
            if (markfrontPtr == NULL){
                markfrontPtr = temp;
                markbackPtr = temp;
                markfrontPtr->next = NULL;        
            }
            else{
                markbackPtr->next=temp;
                markbackPtr=temp;
                markbackPtr->next=NULL;
            }   
            
        }
            fin.close();
        }
        string isEmpty(string &input, string type)
        {
            getline(cin, input);
            while (input == "")
            {
                cout << "Invalid input. Please try again." << endl;
                cout << "Enter your " << type << ": ";
                getline(cin, input);
            }
            return input;
        }
        void enqueue()
        {
            string name, matricno, course, FYPField, FYPTitle, FYPStatus, FYPDate;
            double FYPMark;

            cout << "******************************************" << endl;
            cout << "***        STUDENT INFORMATION         ***" << endl;
            cout << "******************************************" << endl;
            cin.ignore();
            cout << "Enter your name: ";
            isEmpty(name, "name");
            cout << "Enter your MatricNo: ";
            isEmpty(matricno, "MatricNo");
            nodeQ *checknode= frontPtr;
            while(checknode !=NULL){
                if(checknode->matricno==matricno){
                    cout<<"You have record in the system already. Don't need to register a new FYP"<<endl;
                    cout<<"Press any key to continue";
                    cin.get();
                    
                    return;
                }
                    checknode=checknode->next;
                
            }
            cout << "Enter your course: ";
            isEmpty(course, "course");

            cout << "\n**************************************" << endl;
            cout << "*           FYP INFORMATION          *" << endl;
            cout << "**************************************" << endl;

            cout << "Enter your FYP Field: ";
            isEmpty(FYPField, "FYP Field");
            cout << "Enter your FYP Title: ";
            isEmpty(FYPTitle, "FYP Title");
            FYPStatus = "TitleSubmitted";
            FYPDate = date;
            FYPMark = -1.0;
            nodeQ *newNode = create_node(name, matricno, course, FYPField, FYPTitle, FYPStatus, FYPDate, FYPMark);

            if (frontPtr == NULL)
            {
                frontPtr = newNode;
                backPtr = newNode;
                frontPtr->next = NULL;
            }
            else
            {
                backPtr->next = newNode;
                backPtr = newNode;
                backPtr->next = NULL;
            }
            fstream fout;
            fout.open("StudentFYP.txt", ios::app);
            nodeQ *temp = backPtr;
            while (temp)
            {
                fout << temp->name << endl
                << temp->matricno << endl
                << temp->course << endl
                << temp->FYPField << endl
                << temp->FYPTitle << endl 
                << temp->FYPStatus << endl
                << temp->FYPDate
                << temp->FYPMark << endl;
                temp = temp->next;
            }
            fout.close();
            cout << "\nYour FYP Information had been saved" << endl;
            cout << "Press any key to continue...";
            cin.get();
        }
    
        void alterqueue()
        {
            nodeQ *temp = frontPtr;
            if (frontPtr == NULL)
            {
                cout << "SYSTEM EMPTY" << endl;
                cout << "Press any key to continue...";
                cin.get();
                return;
            }
            string matricno, FYPField, FYPTitle, FYPStatus, FYPDate;
            cin.ignore();
            cout << "Enter your Matric No: ";
            getline(cin, matricno);
            if(temp->FYPStatus=="Marked")
            {
                cout<<"Your FYP had been marked. You can't change the FYP Information."<<endl;
                cin.get();
                return;
            }
            while(temp)
            {
                
                if(temp->matricno == matricno)
                {
                    cout << "\n******************************************" << endl;
                    cout << "***           FYP INFORMATION          ***" << endl;
                    cout << "******************************************" << endl;

                    cout << "Enter your updated FYP Field: ";
                    isEmpty(FYPField, "updated FYP Field");

                    cout << "Enter your updated FYP Title: ";
                    isEmpty(FYPTitle, "updated FYP Title");

                    temp->FYPField = FYPField;
                    temp->FYPTitle = FYPTitle;
                    temp = frontPtr;
                    fstream fout;
                    fout.open("StudentFYP.txt", ios::out);
                    while (temp)
                    {
                        fout << temp->name << endl
                        << temp->matricno << endl
                        << temp->course << endl
                        << temp->FYPField << endl
                        << temp->FYPTitle << endl 
                        << temp->FYPStatus << endl
                        << temp->FYPDate << endl
                        << temp->FYPMark << endl;
                        temp = temp->next;
                    }
                    fout.close();
                    cout<<"\nYour FYP Information had been updated" << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                    break;
                }
                temp = temp->next;
                if(temp == NULL)
                {
                    cout << "Student Not Found" << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                    break;
                }
                
            }
            
        }
        void display()
        {
            nodeQ *temp = frontPtr;
            int counter = 1;
            if(temp == NULL)
            {
                cout << "EMPTY SYSTEM";
                cout << "Press any key to continue...";
                cin.get();
                return;
            }
            while (temp != NULL)
            {  
                cout << "STUDENT " << counter++ << "--------------------------------" << endl;
                cout << "**************************************************" << endl;
                cout << "***            STUDENT INFORMATION             ***" << endl;
                cout << "**************************************************" << endl;
                cout << "Student Name: " << temp->name << endl
                << "Student MatricNo: " << temp->matricno << endl 
                << "Student Course: " << temp->course << endl;
                cout << "\n**************************************************" << endl;
                cout << "***               FYP INFORMATION              ***" << endl;
                cout << "**************************************************" << endl;
                cout << "FYP Field: " << temp->FYPField << endl
                << "FYP Title: " << temp->FYPTitle << endl
                << "FYP Title Submission Date: " << temp->FYPDate << endl
                << "FYP Status: " << temp->FYPStatus << endl
                << "FYP Mark: ";
                if(temp->FYPMark == -1) {cout << "TBA" << endl;} 
                else {cout << temp->FYPMark << endl;}
                cout << "-------------------------------------------" << endl << endl;
                temp = temp->next;
            }

            cout<<"Press any key to continue...";
            cin.ignore();
            cin.get();

        }
        void updatestatus() 
        {
            
            int statuschoice;
            nodeQ *temp = frontPtr;
            string matricno;
            cin.ignore();
             if(temp == NULL)
            {
                cout << "EMPTY SYSTEM";
                cout << "Press any key to continue...";
                cin.get();
                return;
            }
            cout << "Enter your Matric No: ";
            getline(cin, matricno);
            while(temp)
            {
                
                if(temp->matricno == matricno)
                {if(temp->FYPStatus=="Marked")
                {
                    cout<<"Your FYP had been marked. You can't change the status."<<endl;
                    cin.get();
                    return;
                }
                    cout << "******************************************" << endl;
                    cout << "***           UPDATE STATUS            ***" << endl;
                    cout << "******************************************" << endl;
                    cout << "Select your current FYP Status: " << endl;
                    cout << "1. Title Submitted" << endl;
                    cout << "2. Proposal Submitted" << endl;
                    cout << "3. Final Report Submitted" << endl;
                    cout << "4. Presentation Done" << endl;
                    cout << "5. Back" << endl;
                    string previousstat=temp->FYPStatus;
                    do
                    {
                        cout << "Enter your choice:";
                        int choice; 
                        cin >> statuschoice;
                        
                        switch(statuschoice)
                        {
                            case 1:
                                temp->FYPStatus = "TitleSubmitted";
                                break;
                            case 2:
                                temp->FYPStatus = "ProposalSubmitted";
                                break;
                            case 3:
                                temp->FYPStatus = "FinalReportSubmitted";
                                break;
                            case 4:
                                temp->FYPStatus = "PresentationDone";
                                break;
                            case 5:
                                return;
                            default:
                                cout << "Invalid Choice." << endl;
                                cout << "Please enter a valid choice" << endl;
                        }
                    }
                    while(statuschoice < 1 || statuschoice > 5);
                    cout << "\nYour FYP Status have been updated to - " << temp->FYPStatus << endl;
                    cout << "Press any key to continue...";
                    cin.ignore();
                    cin.get();
                    nodeQ *newnode=new nodeQ;
                    newnode->matricno=temp->matricno;
                    if(previousstat!=temp->FYPStatus)
                    {
                        if(previousstat!="PresentationDone"&&temp->FYPStatus=="PresentationDone")
                        {
                            if (markfrontPtr == NULL)
                            {
                                markfrontPtr = newnode;
                                markbackPtr = newnode;
                                markfrontPtr->next = NULL;     
                            }
                            else
                            {
                                markbackPtr->next=newnode;
                                markbackPtr=newnode;
                                markbackPtr->next=NULL;
                            } 
                        }
                        if(previousstat=="PresentationDone"&&temp->FYPStatus!="PresentationDone")
                        {
                            
                            string cycleendindex=markfrontPtr->matricno;
                            if(markfrontPtr->matricno==matricno)
                            {
                                markfrontPtr=markfrontPtr->next;
                            }
                            else
                            {
                                do 
                                {
                                   if(markfrontPtr->matricno!=matricno)
                                   {
                                        markbackPtr->next=markfrontPtr;
                                        markbackPtr=markfrontPtr;
                                        markfrontPtr=markfrontPtr->next;
                                        markbackPtr->next=NULL;
                                   } 
                                   else
                                   {
                                        markfrontPtr=markfrontPtr->next;
                                   }
                                }while(markfrontPtr->matricno!=cycleendindex&&markfrontPtr!=NULL);
                            }
                        }
                    }
                    temp = frontPtr;
                    fstream fout;
                    fout.open("StudentFYP.txt", ios::out);
                    while (temp!=NULL)
                    {   cout<<temp->name<<endl;
                        fout << temp->name << endl
                        << temp->matricno << endl
                        << temp->course << endl
                        << temp->FYPField << endl
                        << temp->FYPTitle << endl 
                        << temp->FYPStatus << endl
                        << temp->FYPDate << endl
                        << temp->FYPMark << endl;
                        temp = temp->next;
                    }
                    fout.close();
                    temp=markfrontPtr;
                    fout.open("MarkingOrder.txt", ios::out);
                    while (temp!=NULL)
                    {
                        fout << temp->matricno << endl;
                        temp=temp->next;
                    }
                    fout.close();
                    return;
                    
                }
                temp = temp->next;
            }
            if(temp == NULL)
            {
                cout << "Student Not Found" << endl;
                cout << "Press any key to continue...";
                cin.get();
            }
        }
        
        void CheckResult()
        {
            nodeQ *temp = frontPtr;
            string matricno;
            cin.ignore();
            if(frontPtr == NULL){
                cout << "EMPTY SYSTEM";
                cout << "Press any key to continue...";
                cin.get();
                return;
                }
            cout << "Enter your Matric No: ";
            getline(cin, matricno);
            while(temp)
            {
                if(temp->matricno == matricno)
                {
                    cout << "*************************************" << endl;
                    cout << "*           CHECK RESULT            *" << endl;
                    cout << "*************************************" << endl;
                    cout << "Your FYP Status: " << temp->FYPStatus << endl;
                    cout << "Your FYP Mark: ";
                    if(temp->FYPMark == -1)
                    {
                        cout << "TBA" << endl;
                    } 
                    else
                    {
                        cout << temp->FYPMark << endl;
                    }
                    cout << "Press any key to continue...";
                    cin.get();                    
                    break;
                
                }
                temp = temp->next;
            }
            if(temp == NULL)
            {
                cout << "Student Not Found" << endl;
                cout << "Press any key to continue...";
                cin.get();
            }
        }

        void displaycertain()
        {
            nodeQ *temp = frontPtr;
            if(temp == NULL)
            {
                cout << "EMPTY SYSTEM";
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
                return;
            }
            string matricno;
            cin.ignore();
            cout << "Enter your Matric No: ";
            getline(cin, matricno);

            while(temp)
            {
                if(temp->matricno == matricno)
                {
                    system("CLS");
                    cout << "**************************************************" << endl;
                    cout << "***            STUDENT INFORMATION             ***" << endl;
                    cout << "**************************************************" << endl;
                    cout << "Student Name: " << temp->name << endl
                    << "Student MatricNo: " << temp->matricno << endl 
                    << "Student Course: " << temp->course << endl;
                    cout << "\n**************************************************" << endl;
                    cout << "***               FYP INFORMATION              ***" << endl;
                    cout << "**************************************************" << endl;
                    cout << "FYP Field: " << temp->FYPField << endl
                    << "FYP Title: " << temp->FYPTitle << endl
                    << "FYP Title Submission Date: " << temp->FYPDate << endl;
                    cout << "Press any key to continue...";
                    cin.get();
                    break;
                }
                temp = temp->next;
            }
            if(temp == NULL)
            {
                cout << "Student Not Found" << endl;
                cout << "Press any key to continue...";
                cin.get();
            }
        }

        void displayFYP()
        {
            nodeQ *temp = frontPtr;
            int FYPcounter = 1;
            cout << "****************************************************************************************************" << endl;
            cout << "***                                STUDENT FINAL YEAR PROJECT LIST                               ***" << endl;  
            cout << "****************************************************************************************************" << endl;

            cout << setw(4) << left << "No." << setw(20) << "NAME" << setw(12) << "MATRIC_NO" << setw(30) << "FYP_TITLE" << setw(26) << "FYP_STATUS" << setw(10) << "FYP_MARK" << endl;
            
            while(temp)
            {
                cout << setw(4) << left << FYPcounter++ << setw(20) << temp->name 
                << setw(12) << temp->matricno << setw(30) << temp->FYPTitle 
                << setw(26) << temp->FYPStatus << setw(5);
                if(temp->FYPMark == -1)
                {
                    cout << "TBA" << endl;
                } 
                else
                {
                    cout << temp->FYPMark << endl;
                }
                temp = temp->next;
            }
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
        }

        void UpdateResult()
        {
            nodeQ *temp = frontPtr;
            if(temp == NULL)
            {
                cout << "EMPTY SYSTEM";
                cout << "\nPress any key to continue...";
                cin.get();
                return;
            }
            string matricno;
            cin.ignore();
            cout << "Enter Student Matric No: ";
            getline(cin, matricno);
            while(temp)
            {
                if(temp == backPtr&& temp->matricno!=matricno)
                {
                    cout << "Student Not Found" << endl;
                    break;
                }
                if(temp->matricno == matricno)
                {string previousstat= temp->FYPStatus;
                    cout << "******************************************" << endl;
                    cout << "***           UPDATE RESULT            ***" << endl;
                    cout << "******************************************" << endl;
                    cout << "Enter Student FYP Mark: ";
                    cin >> temp->FYPMark;
                    cout << temp->name << " FYP Mark have been updated" << endl;
                    temp->FYPStatus = "Marked";
                    if(previousstat=="PresentationDone")
                    {
                       string cycleindex= markfrontPtr->matricno;
                       if(markfrontPtr->matricno==matricno)
                       {
                        markfrontPtr=markfrontPtr->next;
                       }
                       else{
                            do
                            {
                                if(markfrontPtr->matricno!=matricno){
                                    markbackPtr->next=markfrontPtr;
                                    markbackPtr=markfrontPtr;
                                    markfrontPtr=markfrontPtr->next;
                                    markbackPtr->next=NULL;
                                } 
                                else{
                                    markfrontPtr=markfrontPtr->next;
                                }
                            }while(markfrontPtr->matricno!=cycleindex&&markfrontPtr!=NULL);
                       }
                    }

                    temp = frontPtr;
                    fstream fout;
                    fout.open("StudentFYP.txt", ios::out);
                    while (temp)
                    {
                        fout << temp->name << endl
                        << temp->matricno << endl
                        << temp->course << endl
                        << temp->FYPField << endl
                        << temp->FYPTitle << endl 
                        << temp->FYPStatus << endl
                        << temp->FYPDate << endl
                        << temp->FYPMark << endl;
                        temp = temp->next;
                    }
                    fout.close();
                    temp=markfrontPtr;
                    fout.open("MarkingOrder.txt",ios::out);
                    while (temp)
                    {
                        fout<<temp->matricno<<endl;
                        temp=temp->next;
                    }
                    fout.close();
                    
                    cin.ignore();
                    break;
                }
                temp = temp->next;
            }
        }

        void markpeek()
        {
            if(markfrontPtr==NULL){
                cout<< "There is no student to be marked yet"<<endl;
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
            }
            else
            {
                nodeQ *newnode=frontPtr;
                nodeQ *temp;
                while(newnode!=NULL)
                {    
                    if(newnode->matricno==markfrontPtr->matricno)
                    {
                        cout << "**************************************************" << endl;
                        cout << "***            STUDENT INFORMATION             ***" << endl;
                        cout << "**************************************************" << endl;
                        cout << "Student Name: " << newnode->name << endl
                        << "Student MatricNo: " << newnode->matricno << endl 
                        << "Student Course: " << newnode->course << endl;
                        cout << "\n**************************************************" << endl;
                        cout << "***               FYP INFORMATION              ***" << endl;
                        cout << "**************************************************" << endl;
                        cout << "FYP Field: " <<newnode->FYPField << endl
                        << "FYP Title: " << newnode->FYPTitle << endl
                        << "FYP Title Submission Date: " << newnode->FYPDate << endl
                        << "FYP Status: " << newnode->FYPStatus << endl
                        << "FYP Mark: ";
                        if(newnode->FYPMark == -1)
                        {
                        cout << "TBA" << endl;
                        } 
                        else
                        {
                        cout << newnode->FYPMark << endl;
                        }
                        cout << "******************************************" << endl;
                        cout << "***           UPDATE RESULT            ***" << endl;
                        cout << "******************************************" << endl;
                        cout << "Enter Student FYP Mark: ";
                        cin >> newnode->FYPMark;
                        cout << newnode->name << " FYP Mark have been up5dated" << endl;
                        
                        
                        newnode->FYPStatus = "Marked";
                        break;
                    }
                    else
                    {
                        newnode=newnode->next;
                    }
                }
                markfrontPtr=markfrontPtr->next;
                
                if(!frontPtr)
                    backPtr=NULL;
            
                fstream fout;
                fout.open("StudentFYP.txt",ios::out);
                newnode=frontPtr;
                while (newnode)
                {
                    fout << newnode->name << endl
                    << newnode->matricno << endl
                    << newnode->course << endl
                    << newnode->FYPField << endl
                    << newnode->FYPTitle << endl 
                    << newnode->FYPStatus << endl
                    << newnode->FYPDate << endl
                    << newnode->FYPMark << endl;
                    newnode = newnode->next;
                }
                fout.close();

                temp=markfrontPtr;
                fout.open("MarkingOrder.txt", ios::out);
                while (temp)
                {
                    fout << temp->matricno << endl;
                    temp=temp->next;
                }
                
                fout.close();
                }       
        }

};

class Lecturer
{
    private:
        string LectName;
        string password;
        StudentQ *studentQ;
    public:
        Lecturer()
        {
            LectName = "";
            password = "";
            studentQ = new StudentQ;
        }
        Lecturer(string name, string pass)
        {
            LectName = name;
            password = pass;
        }
        void setLectName(string name)
        {
            LectName = name;
        }
        void setPassword(string pass)
        {
            password = pass;
        }
        string getLectName()
        {
            return LectName;
        }
        string getPassword()
        {
            return password;
        }
        void displayFYP(StudentQ *studentQ)
        {
            cout << "Access By  :" << this->getLectName() << endl;
            cout << "Access Time:" << date << endl;
            studentQ->displayFYP();
        }
        void UpdateResult(StudentQ *studentQ)
        {
            cout << "Access By  :" << this->getLectName() << endl;
            cout << "Access Time:" << date << endl;
            studentQ->UpdateResult();
            cout << "\nPress any key to continue...";
           
            cin.get();
        }
        void Peek(StudentQ *studentQ)
        {   int option=-1;

            cout << "Access By  :" << this->getLectName() << endl;
            cout << "Access Time:" << date << endl;
            cout<<"Are you going to mark the student"<<endl
                <<"1.Yes\n2.No\n";
            cout << "Enter your choice: ";
            cin>>option;
            if(option==1){
                system("CLS");
                studentQ->markpeek();
            }
            if (option<1||option>2)
            {
                cout<<"please enter right option\n";
                cout << "\nPress any key to continue...";
                cin.ignore();
                cin.get();
                system("CLS");
            }
            if(option==2){ return; }
        }
        void display(StudentQ *studentQ)
        {
            cout << "Access By  :" << this->getLectName() << endl;
            cout << "Access Time:" << date << endl << endl;
            studentQ->display();
        }
};

class Menu
{
    private:
        StudentQ studentQ;
        Lecturer lecturer;
        int choice;
        int lecturerchoice;
    public:
        Menu()
        {
            studentQ.ReadStudent();
            studentQ.ReadMarkingOrder();
            choice = 0;
            lecturerchoice = 0;
        }
        void StudentAccessZone()
        {
            
            do
            {
                system("CLS");
                cout << "******************************************" << endl;
                cout << "    * FINAL YEAR PROJECT MANAGEMENT *" << endl;
                cout << "    *          STUDENT MENU         *" << endl;
                cout << "******************************************" << endl << endl;
                cout << "1. Check Suggested FYP Field\n";
                cout << "2. Key In FYP and Student Information\n";
                cout << "3. Update FYP Information\n";
                cout << "4. Update FYP Status\n";
                cout << "5. Display Your Information\n";
                cout << "6. Check Result\n";
                cout << "7. Back\n";
                cout << "------------------------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch(choice)
                {
                    case 1: system("CLS"); CheckFYPField(); break;
                    case 2: system("CLS"); studentQ.enqueue(); break;
                    case 3: system("CLS"); studentQ.alterqueue(); break;
                    case 4: system("CLS"); studentQ.updatestatus(); break;
                    case 5: system("CLS"); studentQ.displaycertain(); break;
                    case 6: system("CLS"); studentQ.CheckResult(); break;
                    case 7: system("CLS"); break;
                    default:
                    {
                        cout << "Invalid Input" << endl;
                        cout << "Please enter a valid choice" << endl;
                        cout << "Press any key to continue...";
                        cin.ignore();
                        cin.get();
                        system("CLS");
                    }
                }

            }while(choice != 7);
            
        }
        void CheckFYPField()
        {
            int FieldChoice;
            cout << "******************************************" << endl;
            cout << "    * FINAL YEAR PROJECT MANAGEMENT *" << endl;
            cout << "    *      SUGGESTED FYP FIELD      *" << endl;
            cout << "******************************************" << endl << endl;
            cout << "1. Artificial Intelligence\n";
            cout << "2. Web Technology\n";
            cout << "3. Data Science\n";
            cout << "4. Machine Learning\n";
            cout << "5. Internet of Things\n";
            cout << "6. Blockchain\n";
            cout << "7. Game Development\n";
            cout << "8. Back\n";

            do
            {
                cout << "------------------------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> FieldChoice;
                cin.ignore();
                cout << endl;
                switch(FieldChoice)
                {
                    case 1: cout << "Artificial Intelligence (AI): AI is the branch of computer science that deals with creating machines and systems that can perform tasks that typically require human intelligence, such as understanding natural language, recognizing speech, making decisions, and so on. There are many different areas of AI research, such as natural language processing, computer vision, robotics, and so on.\n"; break;
                    case 2: cout << "Web Technology: Web Technology is the branch of computer science that deals with the development and design of websites and web applications. It involves the use of various technologies such as HTML, CSS, JavaScript, and others to create dynamic and interactive websites.\n"; break;
                    case 3: cout << "Data Science: Data Science is the branch of computer science that deals with the extraction of insights and knowledge from data. It involves the use of various techniques such as statistical analysis, machine learning, and data visualization to analyze and make predictions from data.\n"; break;
                    case 4: cout << "Machine Learning: Machine Learning is a subfield of AI that deals with the development of algorithms and models that can learn from data and improve their performance over time. It involves the use of techniques such as supervised and unsupervised learning, deep learning, and reinforcement learning to develop models that can make predictions and decisions.\n"; break;
                    case 5: cout << "Internet of Things (IoT): IoT is the branch of computer science that deals with the development of interconnected devices and systems that can communicate with each other over the internet. It involves the use of various technologies such as sensors, microcontrollers, and wireless communications to connect devices and enable them to collect and share data.\n"; break;
                    case 6: cout << "Blockchain: Blockchain is a distributed ledger technology that enables secure and transparent transactions without the need for intermediaries. It uses cryptography to secure transactions and provide a tamper-proof record of all transactions on the network.\n"; break;
                    case 7: cout << "Game Development: Game Development is the branch of computer science that deals with the development of video games. It involves the use of various technologies such as game engines, programming languages, and graphics tools to create interactive and engaging game experiences.\n"; break;
                    case 8: { system("CLS"); StudentAccessZone(); break;}
                    default: cout << "Invalid Input\n";
                }
            }while(FieldChoice != 8);
        }
        void LecturerManagement()
        {
            do
            {
                system("CLS");
                cout << "******************************************" << endl;
                cout << "    * FINAL YEAR PROJECT MANAGEMENT *" << endl;
                cout << "       *      LECTURER MENU      *" << endl;
                cout << "******************************************" << endl << endl;
                cout << "1. Student List\n";
                cout << "2. FYP List\n";
                cout << "3. Update Result\n";
                cout << "4. Mark Student\n";
                cout << "5. Back\n";
                cout << "------------------------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                system("CLS");

                switch(choice)
                {
                    case 1: lecturer.display(&studentQ); break;
                    case 2: lecturer.displayFYP(&studentQ); break;
                    case 3: lecturer.UpdateResult(&studentQ); break;
                    case 4: lecturer.Peek(&studentQ); break;
                    case 5: break;
                    default: cout << "Invalid Input\n";
                }

            }while(choice != 5);
        }
        void LecturerSignUp()
        {
            char answer = 'N';
            fstream fout;
            string name, pass;
            fout.open("LecturerAccount.txt", ios::app);
            cin.ignore();
            do
            {
                system("CLS");
                cout << "******************************************" << endl;
                cout << "    * FINAL YEAR PROJECT MANAGEMENT *" << endl;
                cout << "    *       LECTURER SIGN UP        *" << endl;
                cout << "******************************************" << endl << endl;
                cout << "Enter your name: ";
                getline(cin, name);
                cout << "Enter your password: ";
                getline(cin, pass);
                if(name != "" && pass != "")
                {
                    fout << name << endl;
                    fout << pass << endl;
                    cout << "Sign Up Successful\n";
                }
                else
                {
                    cout << "Sign Up Unsucessful\n";
                }
                cout << "Add another lecturer? (Y/N): ";
                cin >> answer;
                cin.ignore();
                if(answer == 'Y' || answer == 'y') system("CLS");
                else
                {
                    system("CLS");
                    break;
                }
             }while(answer == 'Y' || answer == 'y');
            fout.close();
        }
        void LecturerLogIn()
        {
            string name, pass;
            string name1, pass1;
            int count = 0;
            fstream fin;
            fin.open("LecturerAccount.txt", ios::in);
            cin.ignore();

            system("CLS");
            cout << "*************************************" << endl;
            cout << "    * FINAL YEAR PROJECT MANAGEMENT *" << endl;
            cout << "     *      LECTURER LOG IN      *" << endl;
            cout << "*************************************" << endl << endl;
            cout << "Enter your name: ";
            getline(cin, name);
            cout << "Enter your password: ";
            getline(cin, pass);

            lecturer.setLectName(name);
            lecturer.setPassword(pass);

            while(!fin.eof())
            {
                getline(fin, name1);
                if(name1 == ""){ break;}
                getline(fin, pass1);
                if(name == name1 && pass == pass1)
                {
                    count++;
                    break;
                }
            }
            if(count == 1)
            {
                cout << "Log In Successful\n";
                system("PAUSE");
                system("CLS");
                LecturerManagement();
            }
            else
            {
                cout << "Log In Failed\n";
                system("PAUSE");
                system("CLS");
                return;
            }
            fin.close();
        }
        void LecturerAccessZone()
        {
            cin.ignore();
            do
            {
                cout << "******************************************" << endl;
                cout << "*      FINAL YEAR PROJECT MANAGEMENT     *" << endl;
                cout << "*          LECTURER ACCESS ZONE          *" << endl;
                cout << "******************************************" << endl << endl;
                cout << "1. First-time Lecturer\n";
                cout << "2. Lecturer Log in\n";
                cout << "3. Back\n";
                cout << "------------------------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> lecturerchoice;
                switch(lecturerchoice)
                {
                    case 1: {system("CLS"); LecturerSignUp(); break;}
                    case 2: {system("CLS"); LecturerLogIn(); break;}
                    case 3: {system("CLS"); break;}
                    default: 
                    {
                        cout << "Invalid Input\n";
                        cout << "Please enter a valid choice" << endl;
                        cout << "Press enter to continue...";
                        cin.ignore();
                        cin.get();
                        system("CLS");
                    }
                }
                

            }while(lecturerchoice != 3);
        }
};

int main()
{
    Lecturer lecturer;
    Menu menu;
    StudentQ studentQ;
    studentQ.ReadStudent();
    studentQ.ReadMarkingOrder();
    int choice;
    do
    {
        cout << "******************************************" << endl;
        cout << "    * FINAL YEAR PROJECT MANAGEMENT *" << endl;
        cout << "    *      FYP MANAGEMENT MENU      *" << endl;
        cout << "******************************************" << endl << endl;
        cout << "         " << date << endl;
        cout << "------------------------------------------" << endl;
        cout << "User Type:\n";
        cout << "------------------------------------------" << endl;
        cout << "1. Student\n";
        cout << "2. Lecturer\n";
        cout << "3. Exit\n";
        cout << "------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == 1)
        {
            system("CLS");

            menu.StudentAccessZone();
        }
        else if(choice == 2)
        {
            system("CLS");
            menu.LecturerAccessZone();
        }
        else if(choice == 3)
        {
            system("CLS");
            break;
        }
        else
        {
            cout << "Invalid choice" << endl;
            cout << "Please enter a valid choice" << endl;
            cout << "Press enter to continue...";
            cin.ignore();
            cin.get();
            system("CLS");
        }
    }while(choice != 1 || choice != 2 || choice != 3);

    cout << "\n******************************************" << endl;
    cout << "Thank you for using FYP Management System" << endl;
    cout << "             Have a nice day             " << endl;
    cout << "******************************************" << endl;
    system("pause");
    return 0;
}