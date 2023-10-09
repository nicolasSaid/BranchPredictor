#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<array>

using namespace std;

void parse(string in, vector<string> &x){
    // Temporary variables
    unsigned long long addr;
    string behavior, line;
    unsigned long long target;

    // Open file for reading
    ifstream infile(in);

    // The following loop will read a line at a time
    while(getline(infile, line)) {
        // // Now we have to parse the line into it's two pieces
        // stringstream s(line);
        // s >> std::hex >> addr >> behavior >> std::hex >> target;
        // // Now we can output it
        // cout << addr;
        // if(behavior == "T") {
        //     cout << " -> taken, ";
        // }else {
        //     cout << " -> not taken, ";
        // }
        // cout << "target=" << target << endl;
        x.push_back(line);
    }
}

void alwaysTakenPredictor(string output, const vector<string> &input){
    int branchCommands = input.size();
    int correctBranchPredictions = 0;
    unsigned long long addr;
    unsigned long long target;
    string behavior;
    for(int i = 0; i < input.size(); i++){
        // Now we have to parse the line into it's two pieces
        stringstream s(input.at(i));
        s >> std::hex >> addr >> behavior >> std::hex >> target;
        // Now we can output it
        if(behavior == "T"){
            correctBranchPredictions++;
        }
    }

    //change to file output later
    cout<<correctBranchPredictions<<","<<branchCommands<<";"<<endl;
}

void alwaysNotTakenPredictor(string output, const vector<string> &input){
    int branchCommands = input.size();
    int correctBranchPredictions = 0;
    unsigned long long addr;
    unsigned long long target;
    string behavior;
    for(int i = 0; i < input.size(); i++){
        // Now we have to parse the line into it's two pieces
        stringstream s(input.at(i));
        s >> std::hex >> addr >> behavior >> std::hex >> target;
        // Now we can output it
        if(behavior == "NT"){
            correctBranchPredictions++;
        }
    }

    //change to file output later
    cout<<correctBranchPredictions<<","<<branchCommands<<";"<<endl;
}

void bimodalOneBitPredictor(string output, const vector<string> &input, unsigned int tableSize){
    int branchCommands = input.size();
    int correctBranchPredictions = 0;
    unsigned long long addr;
    unsigned long long target;

    int table[tableSize];
    for(int i = 0; i < tableSize; i++){
        table[i] = 1;
    }

    string behavior;
    for(int i = 0; i < input.size(); i++){
        // Now we have to parse the line into it's two pieces
        stringstream s(input.at(i));
        s >> std::hex >> addr >> behavior >> std::hex >> target;
        // Now we can output it
        unsigned int index = addr % tableSize;
        if(behavior == "NT"){
            if(table[index] == 0){
                correctBranchPredictions++;
            }else{
                table[index] = 0;
            }
        }else{
            if(table[index] == 1){
                correctBranchPredictions++;
            }else{
                table[index] = 1;
            }
        }
    }

    //change to file output later
    cout<<correctBranchPredictions<<","<<branchCommands<<"; ";
}

void bimodalTwoBitPredictor(string output, const vector<string> &input, unsigned int tableSize){
    int branchCommands = input.size();
    int correctBranchPredictions = 0;
    unsigned long long addr;
    unsigned long long target;

    int table[tableSize];
    for(int i = 0; i < tableSize; i++){
        table[i] = 3;
    }

    string behavior;
    for(int i = 0; i < input.size(); i++){
        // Now we have to parse the line into it's two pieces
        stringstream s(input.at(i));
        s >> std::hex >> addr >> behavior >> std::hex >> target;
        // Now we can output it
        unsigned int index = addr % tableSize;
        if(behavior == "NT"){
            if(table[index] == 0 || table[index] == 1){
                correctBranchPredictions++;
                if(table[index] == 1){
                    table[index]--;
                }
            }else{
                table[index]--;
            }
        }else{
            if(table[index] == 2 || table[index] == 3){
                correctBranchPredictions++;
                if(table[index] == 2){
                    table[index]++;
                }
            }else{
                table[index]++;
            }
        }
    }

    //change to file output later
    cout<<correctBranchPredictions<<","<<branchCommands<<"; ";
}

void gsharePredictor(string output, const vector<string> &input, unsigned int globalBits){
    int branchCommands = input.size();
    int correctBranchPredictions = 0;
    unsigned long long addr;
    unsigned long long target;

    unsigned int globalHist = 0;
    unsigned int len = 0;
    for(int i = 0; i < globalBits; i++){
        len = len<<1;
        len++;
    }

    unsigned int tableSize = 2048;
    int table[tableSize];

    for(int i = 0; i < tableSize; i++){
        table[i] = 3;
    }

    string behavior;
    for(int i = 0; i < input.size(); i++){
        // Now we have to parse the line into it's two pieces
        stringstream s(input.at(i));
        s >> std::hex >> addr >> behavior >> std::hex >> target;
        // Now we can output it
        unsigned int index = addr % tableSize;
        index = index ^ globalHist;

        if(behavior == "NT"){
            globalHist = globalHist<<1;
            globalHist = globalHist & len;
            if(table[index] == 0 || table[index] == 1){
                correctBranchPredictions++;
                if(table[index] == 1){
                    table[index]--;
                }
            }else{
                table[index]--;
            }
        }else{
            globalHist = globalHist<<1;
            globalHist++;
            globalHist = globalHist & len;
            if(table[index] == 2 || table[index] == 3){
                correctBranchPredictions++;
                if(table[index] == 2){
                    table[index]++;
                }
            }else{
                table[index]++;
            }
        }
    }

    //change to file output later
    cout<<correctBranchPredictions<<","<<branchCommands<<"; ";
}

int main(int argc, char *argv[]) {
    if(argc != 3){
        cout<<"Incorrect number of arguments"<<endl;
    }

    vector<string> inputs;
    parse(argv[1], inputs);
    alwaysTakenPredictor(argv[2], inputs);
    alwaysNotTakenPredictor(argv[2], inputs);
    int sizes[] = {16,32,128,256,512,1024,2048};

    for(int i = 0; i < sizeof(sizes)/sizeof(int); i++){
        bimodalOneBitPredictor(argv[2], inputs, sizes[i]);
    }
    cout<<endl;
    for(int i = 0; i < sizeof(sizes)/sizeof(int); i++){
        bimodalTwoBitPredictor(argv[2], inputs, sizes[i]);
    }
    cout<<endl;

    for(int i = 3; i <= 11; i++){
        gsharePredictor(argv[2], inputs, i);
    }
    cout<<endl;

}
