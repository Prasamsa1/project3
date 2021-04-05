#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#include<string.h>
#include<stdio.h>
using namespace std;
const char* filename="poo.txt";
class person
{
private:
    int id;
    char name[20],address[40],phone[10],mobile[10],email[30];
public:
    void read();
    int getid();
    void display();
    char* getmobile();
    char* getname();
};
void person::read(){
cout<<endl<<"id: ";
cin>>id;
cout<<endl<<"name: ";
cin>>name;
cout<<endl<<"address";
cin>>address;
cout<<endl<<"phone";
cin>>phone;
cout<<endl<<"mobile";
cin>>mobile;
cout<<endl<<"email";
cin>>email;
}
void person:: display()
{
    cout<<endl<<"...................................";
    cout<<endl<<setw(4)<<id<<setw(10)<<name<<setw(10)<<address<<setw(10)<<phone<<setw(10)<<mobile<<setw(15)<<email;
}
int person::getid()
{
    return id;
}
char* person::getmobile()
{
    return mobile;
}
char* person::getname()
{
    return name;
}
int main()
{
    person p ,p1 ,temp ,a[100];
    char option,ch,mobile[10],name[10];
    int id,isfound,i,counter,loca,recno;
   // clrscr();
    fstream file;
    file.open(filename,ios::out|ios::in|ios::ate|ios::binary);
    do{
        cout<<"*******Welcome to Telephone Diary System*******"<<endl;
        cout<<"*******************Menu*****************";
        cout<<endl<<"enter your option";
        cout<<endl<<"1: add a new contact";
      cout<<endl<<"2: search a name contact";
      cout<<endl<<"3: search a mobile contact";
      cout<<endl<<"4: display all contact";
      cout<<endl<<"5: update contact on the basis of id";
      cout<<endl<<"7: exit from a program";
      cout<<".............................................................";
      cin>>option;
      switch(option)
      {
      case '1':
        p.read();
        file.seekg(0,ios::beg);
        isfound=0;
        file.read((char*)&p1,sizeof(p1));
        while(!file.eof())
        {
            if(strcmp(p1.getmobile(),p.getmobile())==0)
            {
                cout<<"the contact with this mobile number already exist";
                isfound=1;
                 break;
            }
            file.read((char*)&p1,sizeof(p1));
        }
        if(isfound==1)
            break;
        file.clear();
        file.seekp(0,ios::end);
        file.write((char*)&p,sizeof(p));
        cout<<endl<<"new contact has been added";
        break;
      case '2':
        isfound=0;
        cout<<endl<<"enter name to be searched:";
        cin>>name;
        file.seekg(0,ios::beg);
        file.read((char*)&p1,sizeof(p1));
        while(!file.eof())
        {
            if(strcmp(p1.getname(),name)==0)
            {
                cout<<setw(4)<<"id"<<setw(10)<<"name"<<setw(10)<<"address"<<setw(10)<<"phone"<<setw(10)<<"mobile"<<setw(15)<<"email";
                p1.display();
                isfound=1;
                break;
            }
            file.read((char*)&p1,sizeof(p1));
        }
        file.clear();
        if(isfound==0)
            cout<<endl<<"data not found for this name"<<name;
        break;
      case '3':
        isfound=0;
        cout<<endl<<"enter mobile number to be searched:";
        cin>>mobile;
        file.seekg(0,ios::beg);
        file.read((char*)&p1,sizeof(p1));
        while(!file.eof())
        {
            if(strcmp(p1.getmobile(),mobile)==0)
            {
                cout<<setw(4)<<"id"<<setw(10)<<"name"<<setw(10)<<"address"<<setw(10)<<"phone"<<setw(10)<<"mobile"<<setw(15)<<"email";
                p1.display();
                isfound=1;
                break;
            }
            file.read((char*)&p1,sizeof(p1));
        }
        file.clear();
        if(isfound==0)
            cout<<endl<<"data not found for this mobile number"<<mobile;
        break;
      case '4':
        cout<<endl<<"****************All Contacts**********************";
        file.clear();
        file.seekg(0,ios::beg);
         counter=0;
                    file.read((char*)&p1,sizeof(p1));
 while(!file.eof())
    {
    a[counter]=p1;
 counter++;
 if(counter==1)
 {
     cout<<endl<<setw(4)<<"id"<<setw(10)<<"name"<<setw(10)<<"address"<<setw(10)<<"phone"<<setw(10)<<"mobile"<<setw(15)<<"email";
 }
  file.read((char*)&p1,sizeof(p1));
 }
 for( i=0;i<counter;i++)
 {
     for(int j=i+1;j<counter;j++)
     {
         if(strcmp(a[i].getname(),a[j].getname())>0)
         {
             temp=a[i];
             a[i]=a[j];
             a[j]=temp;
         }
     }
 }
 for ( i=0;i<counter;i++)
    a[i].display();
 cout<<endl<<counter<<"records found.......";
 file.clear();
 break;

      case '5':
         recno=0;
        cout<<endl<<"enter id of person to be updated:";
        cin>>id;
        isfound=0;
         file.seekg(0,ios::beg);
          file.read((char*)&p1,sizeof(p1));
           while(!file.eof())
           {
               recno++;
               if(p1.getid()==id)
               {
                   cout<<endl<<"the old record is";
                   p1.display();
                   isfound=1;
                   break;
               }
                file.read((char*)&p1,sizeof(p1));
           }
           if(isfound==0)
           {
              cout<<endl<<"contact not found";
              break;
           }
           file.clear();
            loca=(recno-1)*sizeof(p1);
           file.seekp(loca,ios::beg);
           cout<<endl<<"enter new record for person having id:"<<id;
           p1.read();
           file.write((char*)&p1,sizeof(p1));
           file.close();
           break;
      case '7':
        exit(0);
        break;
      default:
        cout<<"invalid options";
      }
      cout<<"do you want to continue...?y/n";
      cin>>ch;
    }
    while(ch!='n');
    getch();
}
