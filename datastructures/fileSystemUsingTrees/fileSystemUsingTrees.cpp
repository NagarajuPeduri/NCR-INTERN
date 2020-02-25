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


pair<Directory*, bool> changeDir(Directory* presentDir, string name) {
    Directory* temp = NULL;
    //unable to find name in set.. as set contains pair<str, pair<Directory*, bool>> 
    /*
    if (presentDir->list.find(name) != presentDir->list.end()) {

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


/*---------------------Helper functions---------------------*/

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
    cout << "Command prompt\n\n";

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
        vector<pair<Directory*, string>>::iterator dirIt;       //iterator for directory vector
        set<pair<string, pair<Directory*, bool>>> setIt;        //iterator for set
        vector<string>::iterator fileIt;                        //iterator for file vector
        Directory* thead;                                       //for storing presentDir
        char copy[100];
        vector<string> afterSplit;                              //to store the strings after splitting with seperator '\'
        int ind;

        switch (m[vec[0]]) {
        case 1:     //mkdir
            if (containsForwardSlash(vec[1])) {
                cout << "The syntax of the command is incorrect\n";
                continue;
            }
            thead = presentDir;
            for (int i = 1; i < vec.size(); i++) {
                strcpy(copy, vec[i].c_str());
                afterSplit = splitStringsBySlash(copy);

                if (afterSplit.size() < 2) {
                    createDir(vec[i], presentDir);
                }

                if (afterSplit.size() > 1) {
                    for (int j = 0; j < afterSplit.size(); j++) {
                        presentDir = createDir(afterSplit[j], presentDir);
                        presentDir = presentDir->dir[presentDir->dir.size() - 1].first;
                    }
                }                   
            }
            presentDir = thead;
            break;

        case 2:     //mkf            
            for (int i = 1; i < vec.size(); i++) {
                presentDir->file.push_back(vec[1]);
                presentDir->list.insert(make_pair(vec[i], make_pair(temp, false)));
            }
            break;

        case 3:     //rmdir
            dirIt = presentDir->dir.begin();
            ind = getIndexOfDir(presentDir, vec[1]);
            if (ind == -1) {
                cout << "Directory named '" << vec[1] << "' is not present\n";
            }
            else {
                auto pos = presentDir->list.find(make_pair(vec[1], make_pair(presentDir->dir[ind].first, true)));
                presentDir->list.erase(pos);
                presentDir->dir.erase(dirIt + ind);
            }
            break;

        case 4: //rmf (remove file)
            ind = getIndexOfFile(presentDir, vec[1]);
            if (ind == -1) {
                cout << "File named '" << vec[1] << "' does not exist.\n";
            }
            else {
                auto pos = presentDir->list.find(make_pair(vec[1], make_pair(temp, false)));
                fileIt = presentDir->file.begin();
                presentDir->list.erase(pos);
                presentDir->file.erase(fileIt + ind);
            }
            break;

        case 5:
            display(presentDir);
            break;

        case 6:     //cd (change directory)
            val = changeDir(presentDir, vec[1]);
            if (val.second) {
                path.push_back(vec[1]);     //push into path vector.
                currPath = join(path);      //after changing the directory, update the currPath.
                presentDir = val.first;     //move the currDir.
            }
            else {
                cout << "The directory named '" << vec[1] << "' is not present in the current directory.\n";
            }
            break;

        case 7:     //pwd
            cout << "PWD: " << currPath<<"\n";
            break;

        case 8:     //cd ..
            if (presentDir->prevPointer == NULL) {      //If reaches the root directory
                cout << "Path does not exists.\n";
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
            cout << "command '" << vec[0] << "' is not valid.\n";
            break;
        }
    }
}

