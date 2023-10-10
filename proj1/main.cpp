#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;

void fifo(string fileName) {
    fstream readFile(fileName);
    string output;

    vector<char> jobs;
    queue<int> arrival;
    queue<int> length;

    int currentTime = 0;
    int currentJob = 0;

    char name;
    int arrivalTime;
    int lengthTime;
    
    while (readFile >> name >> arrivalTime >> lengthTime) {
        jobs.push_back(name);
        arrival.push(arrivalTime);
        length.push(lengthTime);
    }
    readFile.close();

    vector<char> jobsCopy = jobs;
    vector<int> TT;
    vector<int> RT;

    while(!length.empty()) {
        RT.push_back(currentTime - arrival.front());
        for (int i = 0; i < length.front(); i++) {
            cout << jobs[currentJob] << " ";
            currentTime++;
        }
        currentJob++;
        length.pop();
        TT.push_back(currentTime - arrival.front());
        arrival.pop();
    }
    double sumTT = 0;
    double sumRT = 0;
    cout << endl << "Job     TT      RT" << endl;
    cout << "~~~~~~~~~~~~~~~~~" << endl;
    for (int i = 0; i < jobsCopy.size(); i++) {
        cout << " " << jobsCopy[i] << "\t" << TT[i] << "\t" << RT[i] << endl;
        sumTT += TT[i];
        sumRT += RT[i];
    }
    cout << "avg:    " << sumTT/TT.size() << "\t" << sumRT/RT.size() << endl;
}

void sjf(string fileName) {
    string output;
    fstream readFile(fileName);

    vector<char> jobs;
    vector<int> arrival;
    vector<int> length;
    
    char name;
    int arrivalTime;
    int lengthTime;
    
    while (readFile >> name >> arrivalTime >> lengthTime) {
        jobs.push_back(name);
        arrival.push_back(arrivalTime);
        length.push_back(lengthTime);
    }
    readFile.close();

    vector<char> jobsCopy = jobs;
    vector<int> RT(jobs.size(), 0);
    vector<int> TT(jobs.size(), 0);

    int shortJobPos = 0;
    int jobTime = length[0];
    int currentTime = 0;

    while(!length.empty()) {
        for (int i = 0; i < jobsCopy.size(); i++) {
            if (jobs[shortJobPos] == jobsCopy[i]) {
                RT[i] = currentTime - arrival[shortJobPos];
            }
        }
        for (int i = 0; i < length[shortJobPos]; i++) {
            cout << jobs[shortJobPos] << " ";
            currentTime++;
        }
        for (int i = 0; i < jobsCopy.size(); i++) {
            if (jobs[shortJobPos] == jobsCopy[i]) {
                TT[i] = currentTime - arrival[shortJobPos];
            }
        }
        jobs.erase(jobs.begin() + shortJobPos);
        arrival.erase(arrival.begin() + shortJobPos);
        length.erase(length.begin() + shortJobPos);

        int tempShortest = length[0];
        for (int i = 0; i < length.size(); i++) {
            if ((length[i] < tempShortest) && (length[i] != 0)) {
                tempShortest = length[i];
            }
        }
        if (!length.empty()) {
            for (int i = 0; i < arrival.size(); i++) {
                if ((arrival[i] <= jobTime) && (length[i] <= tempShortest)) { 
                    shortJobPos = i;
                    jobTime = jobTime + length[i];
                }
            }
        }
    }
    double sumTT = 0;
    double sumRT = 0;
    cout << endl << "Job     TT      RT" << endl;
    cout << "~~~~~~~~~~~~~~~~~" << endl;
    for (int i = 0; i < jobsCopy.size(); i++) {
        cout << " " << jobsCopy[i] << "\t" << TT[i] << "\t" << RT[i] << endl;
        sumTT += TT[i];
        sumRT += RT[i];
    }
    cout << "avg:    " << sumTT/TT.size() << "\t" << sumRT/RT.size() << endl;
}

void stcf(string fileName) {
    string output;
    fstream readFile(fileName);

    vector<char> jobs;
    vector<int> arrival;
    vector<int> length;

    int currentJobPos = 0;
    int currentTime = 0;

    char name;
    int arrivalTime;
    int lengthTime;
    
    while (readFile >> name >> arrivalTime >> lengthTime) {
        jobs.push_back(name);
        arrival.push_back(arrivalTime);
        length.push_back(lengthTime);
    }
    readFile.close();
    
    vector<char> jobsCopy = jobs;
    vector<int> lengthCopy = length;
    vector<int> RT(jobs.size(), 0);
    vector<int> TT(jobs.size(), 0);

    int timePos = 0;
    while (!jobs.empty()) {
            for (int i = 0; i < RT.size(); i++) {
                if ((jobs[currentJobPos] == jobsCopy[i]) && (length[currentJobPos] == lengthCopy[i])) {
                    RT[i] = currentTime - arrival[currentJobPos];
                }
            }
        cout << jobs[currentJobPos] << " ";
        currentTime++;
        length[currentJobPos] = length[currentJobPos] - 1;
        
        for (int i = 0; i < jobsCopy.size(); i++) {
            if (jobs[currentJobPos] == jobsCopy[i]) {
                TT[i] = currentTime - arrival[currentJobPos];
            }
        }

        int tempJobPos = currentJobPos;
        if (length[currentJobPos] <= 0) {
            jobs.erase(jobs.begin() + (currentJobPos));
            arrival.erase(arrival.begin() + (currentJobPos));
            length.erase(length.begin() + (currentJobPos));
            currentJobPos--;
        }
        for (int i = 0; i < length.size(); i++) {
            if ((arrival[i] <= currentTime) && (length[i] <= length[currentJobPos])) {
                currentJobPos = i;
            }
        }
    }
    double sumTT = 0;
    double sumRT = 0;
    cout << endl << "Job     TT      RT" << endl;
    cout << "~~~~~~~~~~~~~~~~~~" << endl;
    for (int i = 0; i < jobsCopy.size(); i++) {
        cout << " " << jobsCopy[i] << "\t" << TT[i] << "\t" << RT[i] << endl;
        sumTT += TT[i];
        sumRT += RT[i];
    }
    cout << "avg:    " << sumTT/TT.size() << "\t" << sumRT/RT.size() << endl;
}

int main() {
    fstream file;
    string fileName;
    int num;

    cout << "Welcome, what file would you like to run?" << endl;
    cin >> fileName;
    file.open(fileName);
    file.close();
    if (file.fail()) {
        cout << "This file does not exist" << endl;
    } else {
        cout << "What algorithm would you like to use?" << endl;
        cout << "1. First in First Out" << endl;
        cout << "2. Shortest Job to Finish" << endl;
        cout << "3. Shortest to Completion First" << endl;
        cin >> num;
        if (num == 1) {
            fifo(fileName);
        } else if (num == 2) {
            sjf(fileName);
        } else if (num == 3) {
            stcf(fileName);
        } else {
            cout << "That algorithm does not exist, choose between 1 and 3";
        }
    }
}