#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source;
    source.open(filename);
    string text;

    while(getline(source, text))
    {
        char s[100] = "";
        for(unsigned i = 0 ; i < text.size(); i++){
            s[i] = text[i];
        }

        char format[] = "%[^:]: %d %d %d";
        char n[100];
        int a, b, c;
        int sum = 0;

        sscanf(s, format, n, &a, &b, &c);
        sum = a + b + c;
        char g = score2grade(sum);
        
        string t ="";
        for(int i = 0; n[i] != '\0'; i++){
            t = t + n[i];
        }

        names.push_back(t);
        scores.push_back(sum);
        grades.push_back(g);

    }
    
}

void getCommand(string &command, string &key){
    cout << "Please input your command: " << endl;
    string text;
    getline(cin, text); 
    
    int index = text.find_first_of(" ");
    command = text.substr(0, index);
    key = text.substr(index + 1, text.size());

}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    for(unsigned i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << "---------------------------------" << endl;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------" << endl;
            return;
        }
    }
    cout << "---------------------------------" << endl;
    cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
    return;
}


void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------" << endl;
    bool check = false;
    for(unsigned i = 0; i < scores.size(); i++){
        if(grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            check = true;
        }
    }
    if(check == false){
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
    return;
}   


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);

    return 0;
}
