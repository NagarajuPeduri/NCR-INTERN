// fileSystemUsingTrees.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <set>
#include <string>
using namespace std;

class Directory {
public:
    Directory* prevPointer = NULL;
    vector<pair<Directory*, string>> dir;
    vector<string> file;
    set<pair<string, pair<Directory*, bool>>> list;       //for storing the files or folders in sorted order.
};


Directory* createDir(string name, Directory* presentDir) {
    Directory* newDir = new Directory;

    if (presentDir == NULL) {
        Directory* temp = NULL;
        newDir->prevPointer = temp;
        newDir->dir.push_back(make_pair(temp, name));
        return newDir;
    }

    newDir->prevPointer = presentDir;
    presentDir->dir.push_back(make_pair(newDir, name));
    presentDir->list.insert(make_pair(name, make_pair(newDir, true)));
    return presentDir;
}


bool containsFile(Directory* presentDir, string name) {
    for (auto s : presentDir->file) {
        if (s == name)
            return true;
    }
    return false;
}


pair<Directory*, bool> containsDir(Directory* presentDir, string name) {
    Directory* temp = NULL;
    //unable to find name in set.. as set contains pair<str, pair<Directory*, bool>> 
    
    /*if (presentDir->list.find(make_pair(name, make_pair(presentDir, true))) != presentDir->list.end()) {

    }*/

    for (auto s : presentDir->dir) {
        if (s.second == name) {
            return make_pair(s.first, true);
        }   
    }
    return make_pair(temp, false);
}


void display(Directory* presentDir) {
    
    for (auto s: presentDir->list) {
        if (s.second.second) {
            cout << "<DIR>\t" << s.first<<"\n";
        }
        else {
            cout << "    \t" << s.first << "\n";
        }
    }
    cout << "\n";
}


/*--------------------- Helper functions ---------------------*/

bool isValidName(string name){
    string invalid = "*+,/:;<=>?\\[]|";

    int count = 0;
    for (char c : name) {
        int val = invalid.find_first_of(c);
        if (val != -1)
            return false;
    }
    return true;
}


pair<bool, int> containsAllDots(string name) {
    int count = 0;
    for (char c : name) {
        if (c == '.')
            count++;
    }
    if (count == name.size())
        return make_pair(true, count);
    return make_pair(false, count);
}


vector<string> splitStringsBySlash(char str[])
{
    char* token = strtok(str, "\\");
    vector<string> vec;

    while (token != NULL)
    {
        vec.push_back(token);
        token = strtok(NULL, "\\");
    }
    return vec;
}


vector<string> splitStrings(char str[])
{
    char* token = strtok(str, " ");
    vector<string> vec;

    while (token != NULL)
    {
        vec.push_back(token);
        token = strtok(NULL, " ");
    }
    return vec;
}


string join(vector<string> path) {
    string currPath = "";
    for (auto s : path) {
        currPath += s;
        currPath += "\\";
    }
    return currPath;
}


int getIndexOfDir(Directory* presentDir, string name) {
    for (int i = 0; i < presentDir->dir.size(); i++) {
        if (presentDir->dir[i].second == name)
            return i;
    }
    return -1;
}


int getIndexOfFile(Directory* presentDir, string name) {
    for (int i = 0; i < presentDir->file.size(); i++) {
        if (presentDir->file[i] == name)
            return i;
    }
    return -1;
}


bool containsForwardSlash(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '/')
            return true;
    }
    return false;
}

/*-------------------------------------------------------------*/


int main()
{
    char ch[100];
    vector<string> path;
    path.push_back("C:");
    
    map<string, int> m{ {"mkdir",1},  {"mkf", 2} , {"rmdir", 3}, {"rmf", 4}, {"dir", 5 }, {"cd", 6 }, {"pwd", 7}, {"cd..", 8}, {"exit", 9} };

    Directory* presentDir = NULL, * temp = NULL;
    presentDir = createDir("C:", presentDir);
    cout << "Microsoft Windows [Version 10.0.17763.973]\n(c) 2020 Microsoft Corporation. All rights reserved.\n\n";

    string currPath = join(path);
     
    while (true) {
        cout << currPath;
        cin.getline(ch, 100);
        
        vector<string> vec;
        vec = splitStrings(ch);

        if (vec.size() == 0 || vec[0].size() == 0) {
            continue;
        }

        if (vec.size() == 2) {
            if (vec[0] == "cd") {
                if (vec[1] == "..")
                    vec[0] = "cd..";
            }
        }

        pair<Directory*, bool> val;
        pair<bool, int> checkDots;
        vector<pair<Directory*, string>>::iterator dirIt;       //iterator for directory vector
        set<pair<string, pair<Directory*, bool>>> setIt;        //iterator for set
        vector<string>::iterator fileIt;                        //iterator for file vector
        Directory* thead;                                       //for storing presentDir
        char copy[100];
        vector<string> afterSplit;                              //to store the strings after splitting with seperator '\'
        int ind;

        switch (m[vec[0]]) {
        case 1:     //mkdir

            if (vec.size() == 1) {
                cout << "The syntax of the command is incorrect.\n\n";
                continue;
            }

            if (containsForwardSlash(vec[1])) {
                cout << "The syntax of the command is incorrect\n\n";
                continue;
            }
            thead = presentDir;                                 //store the presentDir 
            for (int i = 1; i < vec.size(); i++) {              //iterate over strings seperated by spaces which are entered after mkdir
                strcpy(copy, vec[i].c_str());
                afterSplit = splitStringsBySlash(copy);         //split the string with '\'

                presentDir = thead;     

                val = containsDir(presentDir, afterSplit[0]);

                if (afterSplit.size()<2 && val.second) {        //Check if the folder already exists.
                    cout << "Directory named '" << afterSplit[0] << "' already exists.\n\n";
                    continue;
                }

                if (afterSplit.size() < 2) {                    //if the string has no subfolders to add, then add the folder directly to the current directory.
                    if (containsAllDots(afterSplit[0]).first){  //check for strings containing dots. 
                        cout << "A subdirectory or file " << afterSplit[0] << " already exists\n\n";
                        continue; 
                    }

                    if (!isValidName(vec[i])) {                 //check if the string name is valid. 
                        cout << "The filename, directory name, or volume label syntax is incorrect.\n\n";
                    }
                    else {
                        createDir(vec[i], presentDir);          //if the string name is valid and if name is not full of dots, then add the folder to current directory. 
                    }
                }

                if (afterSplit.size() > 1) {                    //if contains subfolders to add.
                    for (int j = 0; j < afterSplit.size(); j++) {

                        if (val.second) {                       //if the directory already exists, move to it.     
                            val.second = false;
                            presentDir = val.first;
                        }
                        else {
                            if (containsAllDots(afterSplit[j]).first) {
                                cout << "A subdirectory or file " << afterSplit[0] << " already exists\n\n";
                                break;
                            }
                            if (!isValidName(afterSplit[j])) {
                                cout << "The filename, directory name, or volume label syntax is incorrect.\n\n";
                                break;
                            }
                            presentDir = createDir(afterSplit[j], presentDir);
                            presentDir = presentDir->dir[presentDir->dir.size() - 1].first;
                        }
                    }
                }                   
            }
            presentDir = thead;
            break;

        case 2:     //mkf   

            if (vec.size() == 1) {
                cout << "The syntax of the command is incorrect.\n\n";
                continue;
            }

            for (int i = 1; i < vec.size(); i++) {
                if (containsFile(presentDir, vec[i])) {
                    cout << "File named '" << vec[i] << "' already exists.\n\n";
                }
                else {
                    if (!isValidName(vec[i])) {
                        cout << "The filename, directory name, or volume label syntax is incorrect.\n\n";
                    }
                    else {
                        presentDir->file.push_back(vec[1]);
                        presentDir->list.insert(make_pair(vec[i], make_pair(temp, false)));
                    }
                }
            }
            break;

        case 3:     //rmdir

            if (vec.size() == 1) {
                cout << "The syntax of the command is incorrect.\n\n";
                continue;
            }

            dirIt = presentDir->dir.begin();
            ind = getIndexOfDir(presentDir, vec[1]);
            if (ind == -1) {
                cout << "Directory named '" << vec[1] << "' is not present\n\n";
            }
            else {
                auto pos = presentDir->list.find(make_pair(vec[1], make_pair(presentDir->dir[ind].first, true)));
                presentDir->list.erase(pos);
                presentDir->dir.erase(dirIt + ind);
            }
            break;

        case 4: //rmf (remove file)

            if (vec.size() == 1) {
                cout << "The syntax of the command is incorrect.\n\n";
                continue;
            }

            ind = getIndexOfFile(presentDir, vec[1]);
            if (ind == -1) {
                cout << "File named '" << vec[1] << "' does not exist.\n\n";
            }
            else {
                auto pos = presentDir->list.find(make_pair(vec[1], make_pair(temp, false)));        //get the position of file_name in file vector. 
                fileIt = presentDir->file.begin();                                                  //iterator.
                presentDir->list.erase(pos);                                                        //remove from set.
                presentDir->file.erase(fileIt + ind);                                               //remove from file vector.    
            }
            break;

        case 5:
            display(presentDir);
            break;

        case 6:     //cd (change directory)

            if (vec.size() == 1) {
                cout << "The syntax of the command is incorrect.\n\n";
                continue;
            }

            checkDots = containsAllDots(vec[1]);
            if (checkDots.second != 2 && checkDots.first) {
                cout << "\n";
                continue;
            }

            val = containsDir(presentDir, vec[1]);
            if (val.second) {
                path.push_back(vec[1]);     //push into path vector.
                currPath = join(path);      //after changing the directory, update the currPath.
                presentDir = val.first;     //move the currDir.
            }
            else {
                cout << "The directory named '" << vec[1] << "' is not present in the current directory.\n\n";
            }
            break;

        case 7:     //pwd
            cout << "PWD: " << currPath<<"\n\n";
            break;

        case 8:     //cd ..

            /*if (vec.size() == 1) {
                cout << "The syntax of the command is incorrect.\n\n";
                continue;
            }*/

            if (presentDir->prevPointer == NULL) {      //If reaches the root directory
                cout << "\n";
            }
            else {
                path.pop_back();
                currPath = join(path);
                presentDir = presentDir->prevPointer;
            }
            break;

        case 9:
            return 0;

        default:
            cout << "command '" << vec[0] << "' is not valid.\n\n";
            break;
        }
    }
}

