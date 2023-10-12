#include<iostream>
#include<vector>
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

void alwaysTakenPredictor(ofstream &file, const vector<string> &input){
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
    file<<correctBranchPredictions<<","<<branchCommands<<";"<<endl;
}

void alwaysNotTakenPredictor(ofstream &file, const vector<string> &input){
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
    file<<correctBranchPredictions<<","<<branchCommands<<";"<<endl;
}

void bimodalOneBitPredictor(ofstream &file, const vector<string> &input){
    int branchCommands = input.size();
    int correctBranchPredictions1 = 0;
    int correctBranchPredictions2 = 0;
    int correctBranchPredictions3 = 0;
    int correctBranchPredictions4 = 0;
    int correctBranchPredictions5 = 0;
    int correctBranchPredictions6 = 0;
    int correctBranchPredictions7 = 0;
    unsigned long long addr;
    unsigned long long target;

    int table1[16];
    int table2[32];
    int table3[128];
    int table4[256];
    int table5[512];
    int table6[1024];
    int table7[2048];
    for(int i = 0; i < 2048; i++){
        if(i < 16){
            table1[i] = 1;
            table2[i] = 1;
            table3[i] = 1;
            table4[i] = 1;
            table5[i] = 1;
            table6[i] = 1;
            table7[i] = 1;
        }else if(i < 32){
            table2[i] = 1;
            table3[i] = 1;
            table4[i] = 1;
            table5[i] = 1;
            table6[i] = 1;
            table7[i] = 1;
            
        }else if(i < 128){
            table3[i] = 1;
            table4[i] = 1;
            table5[i] = 1;
            table6[i] = 1;
            table7[i] = 1;
        }else if(i < 256){
            table4[i] = 1;
            table5[i] = 1;
            table6[i] = 1;
            table7[i] = 1;
        }else if(i < 512){
            table5[i] = 1;
            table6[i] = 1;
            table7[i] = 1;
        }else if(i < 1024){
            table6[i] = 1;
            table7[i] = 1;
        }else{
            table7[i] = 1;
        }
    }

    string behavior;
    for(int i = 0; i < input.size(); i++){
        // Now we have to parse the line into it's two pieces
        stringstream s(input.at(i));
        s >> std::hex >> addr >> behavior >> std::hex >> target;
        // Now we can output it
        unsigned int index1 = addr % 16;
        unsigned int index2 = addr % 32;
        unsigned int index3 = addr % 128;
        unsigned int index4 = addr % 256;
        unsigned int index5 = addr % 512;
        unsigned int index6 = addr % 1024;
        unsigned int index7 = addr % 2048;
        if(behavior == "NT"){
            if(table1[index1] == 0){
                correctBranchPredictions1++;
            }else{
                table1[index1] = 0;
            }
            if(table2[index2] == 0){
                correctBranchPredictions2++;
            }else{
                table2[index2] = 0;
            }
            if(table3[index3] == 0){
                correctBranchPredictions3++;
            }else{
                table3[index3] = 0;
            }
            if(table4[index4] == 0){
                correctBranchPredictions4++;
            }else{
                table4[index4] = 0;
            }
            if(table5[index5] == 0){
                correctBranchPredictions5++;
            }else{
                table5[index5] = 0;
            }
            if(table6[index6] == 0){
                correctBranchPredictions6++;
            }else{
                table6[index6] = 0;
            }
            if(table7[index7] == 0){
                correctBranchPredictions7++;
            }else{
                table7[index7] = 0;
            }
        }else{
            if(table1[index1] == 1){
                correctBranchPredictions1++;
            }else{
                table1[index1] = 1;
            }
            if(table2[index2] == 1){
                correctBranchPredictions2++;
            }else{
                table2[index2] = 1;
            }
            if(table3[index3] == 1){
                correctBranchPredictions3++;
            }else{
                table3[index3] = 1;
            }
            if(table4[index4] == 1){
                correctBranchPredictions4++;
            }else{
                table4[index4] = 1;
            }
            if(table5[index5] == 1){
                correctBranchPredictions5++;
            }else{
                table5[index5] = 1;
            }
            if(table6[index6] == 1){
                correctBranchPredictions6++;
            }else{
                table6[index6] = 1;
            }
            if(table7[index7] == 1){
                correctBranchPredictions7++;
            }else{
                table7[index7] = 1;
            }
        }
    }

    //change to file output later
    file<<correctBranchPredictions1<<","<<branchCommands<<"; "<<correctBranchPredictions2<<","<<branchCommands<<"; "<<correctBranchPredictions3<<","<<branchCommands<<"; "<<correctBranchPredictions4<<","<<branchCommands<<"; "<<correctBranchPredictions5<<","<<branchCommands<<"; "<<correctBranchPredictions6<<","<<branchCommands<<"; "<<correctBranchPredictions7<<","<<branchCommands<<";";
}

void bimodalTwoBitPredictor(ofstream &file, const vector<string> &input){
    int branchCommands = input.size();
    int correctBranchPredictions1 = 0;
    int correctBranchPredictions2 = 0;
    int correctBranchPredictions3 = 0;
    int correctBranchPredictions4 = 0;
    int correctBranchPredictions5 = 0;
    int correctBranchPredictions6 = 0;
    int correctBranchPredictions7 = 0;
    unsigned long long addr;
    unsigned long long target;

    int table1[16];
    int table2[32];
    int table3[128];
    int table4[256];
    int table5[512];
    int table6[1024];
    int table7[2048];
    for(int i = 0; i < 2048; i++){
        if(i < 16){
            table1[i] = 3;
            table2[i] = 3;
            table3[i] = 3;
            table4[i] = 3;
            table5[i] = 3;
            table6[i] = 3;
            table7[i] = 3;
        }else if(i < 32){
            table2[i] = 3;
            table3[i] = 3;
            table4[i] = 3;
            table5[i] = 3;
            table6[i] = 3;
            table7[i] = 3;
            
        }else if(i < 128){
            table3[i] = 3;
            table4[i] = 3;
            table5[i] = 3;
            table6[i] = 3;
            table7[i] = 3;
        }else if(i < 256){
            table4[i] = 3;
            table5[i] = 3;
            table6[i] = 3;
            table7[i] = 3;
        }else if(i < 512){
            table5[i] = 3;
            table6[i] = 3;
            table7[i] = 3;
        }else if(i < 1024){
            table6[i] = 3;
            table7[i] = 3;
        }else{
            table7[i] = 3;
        }
    }

    string behavior;
    for(int i = 0; i < input.size(); i++){
        // Now we have to parse the line into it's two pieces
        stringstream s(input.at(i));
        s >> std::hex >> addr >> behavior >> std::hex >> target;
        // Now we can output it
        unsigned int index1 = addr % 16;
        unsigned int index2 = addr % 32;
        unsigned int index3 = addr % 128;
        unsigned int index4 = addr % 256;
        unsigned int index5 = addr % 512;
        unsigned int index6 = addr % 1024;
        unsigned int index7 = addr % 2048;
        if(behavior == "NT"){
            if(table1[index1] == 0 || table1[index1] == 1){
                correctBranchPredictions1++;
                if(table1[index1] == 1){
                    table1[index1]--;
                }
            }else{
                table1[index1]--;
            }
            if(table2[index2] == 0 || table2[index2] == 1){
                correctBranchPredictions2++;
                if(table2[index2] == 1){
                    table2[index2]--;
                }
            }else{
                table2[index2]--;
            }
            if(table3[index3] == 0 || table3[index3] == 1){
                correctBranchPredictions3++;
                if(table3[index3] == 1){
                    table3[index3]--;
                }
            }else{
                table3[index3]--;
            }
            if(table4[index4] == 0 || table4[index4] == 1){
                correctBranchPredictions4++;
                if(table4[index4] == 1){
                    table4[index4]--;
                }
            }else{
                table4[index4]--;
            }
            if(table5[index5] == 0 || table5[index5] == 1){
                correctBranchPredictions5++;
                if(table5[index5] == 1){
                    table5[index5]--;
                }
            }else{
                table5[index5]--;
            }
            if(table6[index6] == 0 || table6[index6] == 1){
                correctBranchPredictions6++;
                if(table6[index6] == 1){
                    table6[index6]--;
                }
            }else{
                table6[index6]--;
            }
            if(table7[index7] == 0 || table7[index7] == 1){
                correctBranchPredictions7++;
                if(table7[index7] == 1){
                    table7[index7]--;
                }
            }else{
                table7[index7]--;
            }
        }else{
            if(table1[index1] == 2 || table1[index1] == 3){
                correctBranchPredictions1++;
                if(table1[index1] == 2){
                    table1[index1]++;
                }
            }else{
                table1[index1]++;
            }
            if(table2[index2] == 2 || table2[index2] == 3){
                correctBranchPredictions2++;
                if(table2[index2] == 2){
                    table2[index2]++;
                }
            }else{
                table2[index2]++;
            }
            if(table3[index3] == 2 || table3[index3] == 3){
                correctBranchPredictions3++;
                if(table3[index3] == 2){
                    table3[index3]++;
                }
            }else{
                table3[index3]++;
            }
            if(table4[index4] == 2 || table4[index4] == 3){
                correctBranchPredictions4++;
                if(table4[index4] == 2){
                    table4[index4]++;
                }
            }else{
                table4[index4]++;
            }
            if(table5[index5] == 2 || table5[index5] == 3){
                correctBranchPredictions5++;
                if(table5[index5] == 2){
                    table5[index5]++;
                }
            }else{
                table5[index5]++;
            }
            if(table6[index6] == 2 || table6[index6] == 3){
                correctBranchPredictions6++;
                if(table6[index6] == 2){
                    table6[index6]++;
                }
            }else{
                table6[index6]++;
            }
            if(table7[index7] == 2 || table7[index7] == 3){
                correctBranchPredictions7++;
                if(table7[index7] == 2){
                    table7[index7]++;
                }
            }else{
                table7[index7]++;
            }
        }
    }

    //change to file output later
    file<<correctBranchPredictions1<<","<<branchCommands<<"; "<<correctBranchPredictions2<<","<<branchCommands<<"; "<<correctBranchPredictions3<<","<<branchCommands<<"; "<<correctBranchPredictions4<<","<<branchCommands<<"; "<<correctBranchPredictions5<<","<<branchCommands<<"; "<<correctBranchPredictions6<<","<<branchCommands<<"; "<<correctBranchPredictions7<<","<<branchCommands<<";";
}

void gsharePredictor(ofstream &file, const vector<string> &input, unsigned int globalBits){
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
    file<<correctBranchPredictions<<","<<branchCommands<<"; ";
}

void tournamentPredictor(ofstream &file, const vector<string> &input){
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
    file<<correctBranchPredictions<<","<<branchCommands<<";"<<endl;;
}


void BTB(ofstream &file, const vector<string> &input){
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
    file<<correctBranchPredictions<<","<<branchCommands<<";"<<endl;
}

int main(int argc, char *argv[]) {
    if(argc != 3){
        cout<<"Incorrect number of arguments"<<endl;
    }

    ofstream file;
    file.open(argv[2]);
    vector<string> inputs;
    parse(argv[1], inputs);
    alwaysTakenPredictor(file, inputs);
    alwaysNotTakenPredictor(file, inputs);

    bimodalOneBitPredictor(file, inputs);
    file<<endl;
    bimodalTwoBitPredictor(file, inputs);
    file<<endl;

    for(int i = 3; i <= 11; i++){
        gsharePredictor(file, inputs, i);
    }
    file<<endl;

    tournamentPredictor(file, inputs);

    BTB(file, inputs);
    cout<<"Execution Complete"<<endl;
    file.close();

}
