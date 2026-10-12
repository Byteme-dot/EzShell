#include<iostream>
#include <windows.h>
#include <cstring>
#include <string>
#include <fstream>
#include <limits>
#include <filesystem>

using namespace std;

WCHAR username[256];
int asadmin=0;

void helpf(){
    cout<<endl<<"- - - - - - - - Commands - - - - - - - -"<<endl;
    cout<<"Delete - rm <filedirectory> [REQUIRES ADMIN PRIVILEGES]"<<endl;
    cout<<"Copy and Paste - cp <filedirectory> <pastingdirectory> [REQUIRES ADMIN PRIVILEGES]"<<endl;
    cout<<"Create File - cf <filename.extension> [REQUIRES ADMIN PRIVILEGES]"<<endl;
    cout<<"Open File - op <filedirectory>"<<endl;
    cout<<"Display all files in the directory - list"<<endl;
    cout<<"Go to a directory - goto <directory>"<<endl;
    cout<<"Go to Desktop directory - DESKTOP"<<endl;
    cout<<"Go to Download directory - DOWNLOAD"<<endl;
    cout<<"Go to Document directory - DOCUMENT"<<endl;
    cout<<"Go to Picture directory - PICTURE"<<endl;
    cout<<"Go to Video directory - VIDEO"<<endl;
    if(asadmin==0){
        cout<<"Switch to Admin - ADMIN"<<endl;
    }
    cout<<"To exit program - EXIT"<<endl;
    cout<<endl<<"- - - - - - - - - - - - - - - - - - - - -"<<endl;
}

int verifyadmin() {
    string password, ipassword,repassword;
    ifstream file("pas.dat", ios::binary);

    if (file.is_open()) {
        getline(file, password);
        file.close();
        cout << "Enter Password: ";
        getline(cin, ipassword);
        if (ipassword==password){
            cout<<"Welcome Admin !"<<endl;
            return 1;
        }else{
            cerr<<"Incorrect Password!"<<endl;
            return 0;
        }
    }else{
        cerr<<"You need to create a new password"<<endl;
        ofstream file("pas.dat", ios::binary);
        if (file.is_open()){
            cout<< "Enter New Password: ";
            getline(cin, repassword);
            file<<repassword; 
            file.close();
            cout<<"Password Saved Successfully!"<<endl;
            return 1;
        }else{
            cerr<<"Error: Could not create file!"<<endl;
            return 0;
        }
    }
}


void runasadmin(){
    string adinput;
    cout<<"Type !help for commands"<<endl;
    while(true){
        cout<<"BAT C:/Users/admin>> ";
        getline(cin,adinput);
        if(adinput=="!help"){
            helpf();
        }else if (adinput=="EXIT"){
            break;
            exit(1);
        }else if(adinput=="rm"){
            //DELETE function
        }else if(adinput=="cp"){
            //Copy & Paste Function, ask if u dont understand
        }else if(adinput=="op"){
            //Open function
        }else if(adinput=="cf"){
            //Create file function
        }else if(adinput=="list"){
            // display all files in directory
        }else if(adinput=="goto"){
            //go to a directory function (goto <directory>)
        }else if(adinput=="DESKTOP"){
            //go to Desktop 
        }else if(adinput=="DOWNLOAD"){
            //go to download
        }else if(adinput=="DOCUMENT"){
            //go to document
        }else if(adinput=="PICTURE"){
            //go to picture
        }else if(adinput=="VIDEO"){
            //go to video
        }else{
            cout<<"'"<<adinput<<"' is not recognized as an internal or external command"<<endl;
        }

        
    }
}

void runasuser(){
    int checkad=0;
    string usinput;
    cout<<"Type !help for commands"<<endl;
    while(true){
        wcout<<L"BAT C:/Users/"<<username<<L">> ";
        getline(cin,usinput);
        if(usinput=="!help"){
            helpf();
        }else if(usinput=="EXIT"){
            break;
            exit(1);
        }else if(usinput=="ADMIN"){
            checkad=verifyadmin();
            if(checkad==1){
                asadmin=1;
                runasadmin();
                return;
            }else{
                cout<<"Access denied. Staying in user mode."<<endl;
            }
        }else if(usinput=="rm"){
            cout<<"Access denied. Requires Admin Privileges!"<<endl;
        }else if(usinput=="cp"){
            cout<<"Access denied. Requires Admin Privileges!"<<endl;
        }else if(usinput=="op"){
            //Open function
        }else if(usinput=="cf"){
            cout<<"Access denied. Requires Admin Privileges!"<<endl;
        }else if(usinput=="list"){
            // display all files in directory
        }else if(usinput=="goto"){
            //go to a directory function (goto <directory>)
        }else if(usinput=="DESKTOP"){
            //go to Desktop 
        }else if(usinput=="DOWNLOAD"){
            //go to download
        }else if(usinput=="DOCUMENT"){
            //go to document
        }else if(usinput=="PICTURE"){
            //go to picture
        }else if(usinput=="VIDEO"){
            //go to video
        }else{
            cout<<"'"<<usinput<<"' is not recognized as an internal or external command."<<endl;
        }
    }
}

void startingterminal() {
    DWORD username_len = 256;

    if (GetUserNameW(username, &username_len)){
    }else{
        wcscpy(username, L"user"); // Assign default username
    }

    cout<<"Loading File Explorer CLI";
    for (int i = 0; i < 3; i++) {
        Sleep(1000);
        cout<<".";
    }
    cout<<endl<<"Copyright (C) ByteArch Terminal (BAT). All rights reserved."<<endl;
    cout<<endl<<"A File Explorer CLI Project by ByteArch!"<<endl;
    wcout<<endl << L"Welcome " << username << L" !" <<endl;
    
}


int main(){
    int a;
    startingterminal();
    while(true){
        cout<<"Run As Admin?(1-true,0-false)>>";
        cin>>asadmin;
        if(asadmin!=1 && asadmin!=0){
            cout<<"Enter a valid input!!"<<endl;
        }else{
            break;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ← ✅ Only here
    if(asadmin==1){
        a=verifyadmin();
        if(a==1){
            runasadmin();
        }else{
            runasuser();
        }
    }
    if(asadmin==0){
        runasuser();
    }
    
    
    exit(0);
    return 0;
}