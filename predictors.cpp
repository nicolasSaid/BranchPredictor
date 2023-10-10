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

void tournamentPredictor(string output, const vector<string> &input){
    int branchCommands = input.size();
    int correctBranchPredictions = 0;
    unsigned long long addr;
    unsigned long long target;

    //gshare stuff
    unsigned int globalHist = 0;
    unsigned int len = 0;
    for(int i = 0; i < 11; i++){
        len = len<<1;
        len++;
    }
    unsigned int tableSize = 2048;
    int tableG[tableSize];

    //bimodel stuff
    int tableB[tableSize];

    //selector table

    int tableS[tableSize];

    for(int i = 0; i < tableSize; i++){
        tableG[i] = 3;
        tableB[i] = 3;
        tableS[i] = 0;
    }


    string behavior;
    for(int i = 0; i < input.size(); i++){
        // Now we have to parse the line into it's two pieces
        stringstream s(input.at(i));
        s >> std::hex >> addr >> behavior >> std::hex >> target;
        // Now we can output it

        unsigned int indexSB = addr % tableSize;

        unsigned int indexG = addr % tableSize;
        indexG = indexG ^ globalHist;

        unsigned int GCorr, BCorr;

        if(behavior == "NT"){
            //gshare start
            globalHist = globalHist<<1;
            globalHist = globalHist & len;
            if(tableG[indexG] == 0 || tableG[indexG] == 1){
                GCorr = 1;
                if(tableG[indexG] == 1){
                    tableG[indexG]--;
                }
            }else{
                GCorr = 0;
                tableG[indexG]--;
            }
            //gshare end
            if(tableB[indexSB] == 0 || tableB[indexSB] == 1){
                BCorr = 1;
                if(tableB[indexSB] == 1){
                    tableB[indexSB]--;
                }
            }else{
                BCorr = 0;
                tableB[indexSB]--;
            }

        }else{
            //gshare start
            globalHist = globalHist<<1;
            globalHist++;
            globalHist = globalHist & len;
            if(tableG[indexG] == 2 || tableG[indexG] == 3){
                GCorr = 1;
                if(tableG[indexG] == 2){
                    tableG[indexG]++;
                }
            }else{
                GCorr = 0;
                tableG[indexG]++;
            }
            //gshare end
            if(tableB[indexSB] == 2 || tableB[indexSB] == 3){
                BCorr = 1;
                if(tableB[indexSB] == 2){
                    tableB[indexSB]++;
                }
            }else{
                BCorr = 0;
                tableB[indexSB]++;
            }
        }
        if(tableS[indexSB] == 0 || tableS[indexSB] == 1){
            if(GCorr == 1){
                correctBranchPredictions++;
            }

            if(GCorr == 1 && BCorr == 0){
                if(tableS[indexSB] == 1){
                    tableS[indexSB]--;
                }
            } else if(GCorr == 0 && BCorr == 1){
                tableS[indexSB]++;
            }
        } else if(tableS[indexSB] == 2 || tableS[indexSB] == 3){
            if(BCorr == 1){
                correctBranchPredictions++;
            }

            if(GCorr == 1 && BCorr == 0){
                tableS[indexSB]--;
            } else if(GCorr == 0 && BCorr == 1){
                if(tableS[indexSB] == 2){
                    tableS[indexSB]++;
                }
            }
        }

    }

    //change to file output later
    cout<<correctBranchPredictions<<","<<branchCommands<<";"<<endl;;
}


void BTB(string output, const vector<string> &input){
    int branchCommands = 0;
    int correctBranchPredictions = 0;
    unsigned long long addr;
    unsigned long long target;

    unsigned int tableSize = 512;
    int table[tableSize];
    unsigned long long btbTable[tableSize];
    for(int i = 0; i < tableSize; i++){
        table[i] = 1;
        btbTable[i] = 0;
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
                //correctBranchPredictions++;
            }else{
                branchCommands++;
                table[index] = 0;
                if(btbTable[index] == target){
                    correctBranchPredictions++;
                }
            }
        }else{
            if(table[index] == 1){
                branchCommands++;
                if(btbTable[index] == target){
                    correctBranchPredictions++;
                }
            }else{
                table[index] = 1;
            }
            btbTable[index] = target;
        }
    }

    //change to file output later
    cout<<correctBranchPredictions<<","<<branchCommands<<";"<<endl;
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

    tournamentPredictor(argv[2], inputs);

    BTB(argv[2], inputs);

}
