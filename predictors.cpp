#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<array>

using namespace std;

void parse(string in, vector<unsigned long long> &x, vector<string> &y, vector<unsigned long long> &z){
    // Temporary variables
    unsigned long long addr;
    string behavior, line;
    unsigned long long target;

    // Open file for reading
    ifstream infile(in);

    // The following loop will read a line at a time
    while(getline(infile, line)) {
        // Now we have to parse the line into it's two pieces
        stringstream s(line);
        s >> std::hex >> addr >> behavior >> std::hex >> target;
        // Now we can output it
        x.push_back(addr);
        y.push_back(behavior);
        z.push_back(target);
    }
}

void alwaysTakenPredictor(ofstream &file, const vector<unsigned long long> &addr, const vector<string> &behavior, const vector<unsigned long long> &target){
    int branchCommands = addr.size();
    int correctBranchPredictions = 0;
    for(int i = 0; i < addr.size(); i++){
        // Now we have to parse the line into it's two pieces
        // Now we can output it
        if(behavior[i] == "T"){
            correctBranchPredictions++;
        }
    }

    //change to file output later
    file<<correctBranchPredictions<<","<<branchCommands<<";"<<endl;
}

void alwaysNotTakenPredictor(ofstream &file, const vector<unsigned long long> &addr, const vector<string> &behavior, const vector<unsigned long long> &target){
    int branchCommands = addr.size();
    int correctBranchPredictions = 0;
    for(int i = 0; i < addr.size(); i++){
        // Now we have to parse the line into it's two pieces
        if(behavior[i] == "NT"){
            correctBranchPredictions++;
        }
    }

    //change to file output later
    file<<correctBranchPredictions<<","<<branchCommands<<";"<<endl;
}

void bimodalOneBitPredictor(ofstream &file, const vector<unsigned long long> &addr, const vector<string> &behavior, const vector<unsigned long long> &target){
    int branchCommands = addr.size();
    int correctBranchPredictions[] = {0,0,0,0,0,0,0};

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

    int index[7] = {0,0,0,0,0,0,0};
    for(int i = 0; i < addr.size(); i++){
        // Now we have to parse the line into it's two pieces
        index[0] = addr[i] % 16;
        index[1] = addr[i] % 32;
        index[2] = addr[i] % 128;
        index[3] = addr[i] % 256;
        index[4] = addr[i] % 512;
        index[5] = addr[i] % 1024;
        index[6] = addr[i] % 2048;
        if(behavior[i] == "NT"){
            if(table1[index[0]] == 0){
                correctBranchPredictions[0]++;
            }else{
                table1[index[0]] = 0;
            }
            if(table2[index[1]] == 0){
                correctBranchPredictions[1]++;
            }else{
                table2[index[1]] = 0;
            }
            if(table3[index[2]] == 0){
                correctBranchPredictions[2]++;
            }else{
                table3[index[2]] = 0;
            }
            if(table4[index[3]] == 0){
                correctBranchPredictions[3]++;
            }else{
                table4[index[3]] = 0;
            }
            if(table5[index[4]] == 0){
                correctBranchPredictions[4]++;
            }else{
                table5[index[4]] = 0;
            }
            if(table6[index[5]] == 0){
                correctBranchPredictions[5]++;
            }else{
                table6[index[5]] = 0;
            }
            if(table7[index[6]] == 0){
                correctBranchPredictions[6]++;
            }else{
                table7[index[6]] = 0;
            }
        }else{
            if(table1[index[0]] == 1){
                correctBranchPredictions[0]++;
            }else{
                table1[index[0]] = 1;
            }
            if(table2[index[1]] == 1){
                correctBranchPredictions[1]++;
            }else{
                table2[index[1]] = 1;
            }
            if(table3[index[2]] == 1){
                correctBranchPredictions[2]++;
            }else{
                table3[index[2]] = 1;
            }
            if(table4[index[3]] == 1){
                correctBranchPredictions[3]++;
            }else{
                table4[index[3]] = 1;
            }
            if(table5[index[4]] == 1){
                correctBranchPredictions[4]++;
            }else{
                table5[index[4]] = 1;
            }
            if(table6[index[5]] == 1){
                correctBranchPredictions[5]++;
            }else{
                table6[index[5]] = 1;
            }
            if(table7[index[6]] == 1){
                correctBranchPredictions[6]++;
            }else{
                table7[index[6]] = 1;
            }
        }
    }

    //change to file output later
    file<<correctBranchPredictions[0]<<","<<branchCommands<<"; "<<correctBranchPredictions[1]<<","<<branchCommands<<"; "<<correctBranchPredictions[2]<<","<<branchCommands<<"; "<<correctBranchPredictions[3]<<","<<branchCommands<<"; "<<correctBranchPredictions[4]<<","<<branchCommands<<"; "<<correctBranchPredictions[5]<<","<<branchCommands<<"; "<<correctBranchPredictions[6]<<","<<branchCommands<<";";
}

void bimodalTwoBitPredictor(ofstream &file, const vector<unsigned long long> &addr, const vector<string> &behavior, const vector<unsigned long long> &target){
    int branchCommands = addr.size();
    int correctBranchPredictions[7] = {0,0,0,0,0,0,0};

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

    unsigned int index[7];
    for(int i = 0; i < addr.size(); i++){
        // Now we have to parse the line into it's two pieces
        // Now we can output it
        index[0] = addr[i] % 16;
        index[1] = addr[i] % 32;
        index[2] = addr[i] % 128;
        index[3] = addr[i] % 256;
        index[4] = addr[i] % 512;
        index[5] = addr[i] % 1024;
        index[6] = addr[i] % 2048;
        if(behavior[i] == "NT"){
            if(table1[index[0]] == 0 || table1[index[0]] == 1){
                correctBranchPredictions[0]++;
                if(table1[index[0]] == 1){
                    table1[index[0]]--;
                }
            }else{
                table1[index[0]]--;
            }
            if(table2[index[1]] == 0 || table2[index[1]] == 1){
                correctBranchPredictions[1]++;
                if(table2[index[1]] == 1){
                    table2[index[1]]--;
                }
            }else{
                table2[index[1]]--;
            }
            if(table3[index[2]] == 0 || table3[index[2]] == 1){
                correctBranchPredictions[2]++;
                if(table3[index[2]] == 1){
                    table3[index[2]]--;
                }
            }else{
                table3[index[2]]--;
            }
            if(table4[index[3]] == 0 || table4[index[3]] == 1){
                correctBranchPredictions[3]++;
                if(table4[index[3]] == 1){
                    table4[index[3]]--;
                }
            }else{
                table4[index[3]]--;
            }
            if(table5[index[4]] == 0 || table5[index[4]] == 1){
                correctBranchPredictions[4]++;
                if(table5[index[4]] == 1){
                    table5[index[4]]--;
                }
            }else{
                table5[index[4]]--;
            }
            if(table6[index[5]] == 0 || table6[index[5]] == 1){
                correctBranchPredictions[5]++;
                if(table6[index[5]] == 1){
                    table6[index[5]]--;
                }
            }else{
                table6[index[5]]--;
            }
            if(table7[index[6]] == 0 || table7[index[6]] == 1){
                correctBranchPredictions[6]++;
                if(table7[index[6]] == 1){
                    table7[index[6]]--;
                }
            }else{
                table7[index[6]]--;
            }
        }else{
            if(table1[index[0]] == 2 || table1[index[0]] == 3){
                correctBranchPredictions[0]++;
                if(table1[index[0]] == 2){
                    table1[index[0]]++;
                }
            }else{
                table1[index[0]]++;
            }
            if(table2[index[1]] == 2 || table2[index[1]] == 3){
                correctBranchPredictions[1]++;
                if(table2[index[1]] == 2){
                    table2[index[1]]++;
                }
            }else{
                table2[index[1]]++;
            }
            if(table3[index[2]] == 2 || table3[index[2]] == 3){
                correctBranchPredictions[2]++;
                if(table3[index[2]] == 2){
                    table3[index[2]]++;
                }
            }else{
                table3[index[2]]++;
            }
            if(table4[index[3]] == 2 || table4[index[3]] == 3){
                correctBranchPredictions[3]++;
                if(table4[index[3]] == 2){
                    table4[index[3]]++;
                }
            }else{
                table4[index[3]]++;
            }
            if(table5[index[4]] == 2 || table5[index[4]] == 3){
                correctBranchPredictions[4]++;
                if(table5[index[4]] == 2){
                    table5[index[4]]++;
                }
            }else{
                table5[index[4]]++;
            }
            if(table6[index[5]] == 2 || table6[index[5]] == 3){
                correctBranchPredictions[5]++;
                if(table6[index[5]] == 2){
                    table6[index[5]]++;
                }
            }else{
                table6[index[5]]++;
            }
            if(table7[index[6]] == 2 || table7[index[6]] == 3){
                correctBranchPredictions[6]++;
                if(table7[index[6]] == 2){
                    table7[index[6]]++;
                }
            }else{
                table7[index[6]]++;
            }
        }
    }

    //change to file output later
    file<<correctBranchPredictions[0]<<","<<branchCommands<<"; "<<correctBranchPredictions[1]<<","<<branchCommands<<"; "<<correctBranchPredictions[2]<<","<<branchCommands<<"; "<<correctBranchPredictions[3]<<","<<branchCommands<<"; "<<correctBranchPredictions[4]<<","<<branchCommands<<"; "<<correctBranchPredictions[5]<<","<<branchCommands<<"; "<<correctBranchPredictions[6]<<","<<branchCommands<<";";
}

void gsharePredictor(ofstream &file, const vector<unsigned long long> &addr, const vector<string> &behavior, const vector<unsigned long long> &target){
    int branchCommands = addr.size();
    int correctBranchPredictions[9] = {0,0,0,0,0,0,0,0};

    unsigned int globalHist[9] = {0,0,0,0,0,0,0,0,0};
    unsigned int len[9] = {0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < 11; i++){
        if(i<3){
            for(int i = 0; i < 9; i++){
                len[i] = len[i] << 1;
                len[i]++;
            }
        }else if (i<4){
            for(int i = 1; i < 9; i++){
                len[i] = len[i] << 1;
                len[i]++;
            }
        }else if (i<5){
            for(int i = 2; i < 9; i++){
                len[i] = len[i] << 1;
                len[i]++;
            }
        }else if (i<6){
            for(int i = 3; i < 9; i++){
                len[i] = len[i] << 1;
                len[i]++;
            }
        }else if (i<7){
            for(int i = 4; i < 9; i++){
                len[i] = len[i] << 1;
                len[i]++;
            }
        }else if (i<8){
            for(int i = 5; i < 9; i++){
                len[i] = len[i] << 1;
                len[i]++;
            }
        }else if (i<9){
            for(int i = 6; i < 9; i++){
                len[i] = len[i] << 1;
                len[i]++;
            }
        }else if (i<10){
            for(int i = 7; i < 9; i++){
                len[i] = len[i] << 1;
                len[i]++;
            }
        }else{
            for(int i = 8; i < 9; i++){
                len[i] = len[i] << 1;
                len[i]++;
            }
        }
    }

    unsigned int tableSize = 2048;
    int table[9][tableSize];

    for(int i = 0; i < tableSize; i++){
        for(int j = 0; j < 9; j++){
            table[j][i] = 3;
        }
    }

    unsigned int index[9];
    for(int i = 0; i < addr.size(); i++){
        // Now we have to parse the line into it's two pieces
        // Now we can output it
        for(int j = 0; j < 9; j++){
            index[j] = addr[i] % tableSize;
            index[j] = index[j] ^ globalHist[j];
        }

        if(behavior[i] == "NT"){
            for(int j = 0; j < 9; j++){
                globalHist[j] = globalHist[j]<<1;
                globalHist[j] = globalHist[j] & len[j];
            }

            for(int j = 0; j < 9; j++){
                if(table[j][index[j]] == 0 || table[j][index[j]] == 1){
                    correctBranchPredictions[j]++;
                    if(table[j][index[j]] == 1){
                        table[j][index[j]]--;
                    }
                }else{
                    table[j][index[j]]--;
                }
            }

        }else{
            for(int j = 0; j < 9; j++){
                globalHist[j] = globalHist[j]<<1;
                globalHist[j]++;
                globalHist[j] = globalHist[j] & len[j];
            }

            for(int j = 0; j < 9; j++){
                if(table[j][index[j]] == 2 || table[j][index[j]] == 3){
                    correctBranchPredictions[j]++;
                    if(table[j][index[j]] == 2){
                        table[j][index[j]]++;
                    }
                }else{
                    table[j][index[j]]++;
                }
            }
        }
    }

    //change to file output later
    file<<correctBranchPredictions[0]<<","<<branchCommands<<"; "<<correctBranchPredictions[1]<<","<<branchCommands<<"; "<<correctBranchPredictions[2]<<","<<branchCommands<<"; "<<correctBranchPredictions[3]<<","<<branchCommands<<"; "<<correctBranchPredictions[4]<<","<<branchCommands<<"; "<<correctBranchPredictions[5]<<","<<branchCommands<<"; "<<correctBranchPredictions[6]<<","<<branchCommands<<"; "<<correctBranchPredictions[7]<<","<<branchCommands<<"; "<<correctBranchPredictions[8]<<","<<branchCommands<<";";
}

void tournamentPredictor(ofstream &file, const vector<unsigned long long> &addr, const vector<string> &behavior, const vector<unsigned long long> &target){
    int branchCommands = addr.size();
    int correctBranchPredictions = 0;

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


    for(int i = 0; i < addr.size(); i++){
        // Now we have to parse the line into it's two pieces
        // Now we can output it

        unsigned int indexSB = addr[i] % tableSize;

        unsigned int indexG = addr[i] % tableSize;
        indexG = indexG ^ globalHist;

        unsigned int GCorr, BCorr;

        if(behavior[i] == "NT"){
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


void BTB(ofstream &file, const vector<unsigned long long> &addr, const vector<string> &behavior, const vector<unsigned long long> &target){
    int branchCommands = 0;
    int correctBranchPredictions = 0;

    unsigned int tableSize = 512;
    int table[tableSize];
    unsigned long long btbTable[tableSize];
    for(int i = 0; i < tableSize; i++){
        table[i] = 1;
        btbTable[i] = 0;
    }

    for(int i = 0; i < addr.size(); i++){
        // Now we have to parse the line into it's two pieces
        // Now we can output it
        unsigned int index = addr[i] % tableSize;
        if(behavior[i] == "NT"){
            if(table[index] == 0){
                //correctBranchPredictions++;
            }else{
                branchCommands++;
                table[index] = 0;
                if(btbTable[index] == target[i]){
                    correctBranchPredictions++;
                }
            }
        }else{
            if(table[index] == 1){
                branchCommands++;
                if(btbTable[index] == target[i]){
                    correctBranchPredictions++;
                }
            }else{
                table[index] = 1;
            }
            btbTable[index] = target[i];
        }
    }

    //change to file output later
    file<<correctBranchPredictions<<","<<branchCommands<<";"<<endl;
}

int main(int argc, char *argv[]) {
    if(argc != 3){
        std::cout<<"Incorrect number of arguments"<<endl;
    }

    ofstream file;
    file.open(argv[2]);
    vector<unsigned long long> addr;
    vector<string> behavior;
    vector<unsigned long long> target;

    parse(argv[1], addr, behavior, target);
    alwaysTakenPredictor(file, addr, behavior, target);
    alwaysNotTakenPredictor(file, addr, behavior, target);

    bimodalOneBitPredictor(file, addr, behavior, target);
    file<<endl;
    bimodalTwoBitPredictor(file, addr, behavior, target);
    file<<endl;

    gsharePredictor(file, addr, behavior, target);
    file<<endl;

    tournamentPredictor(file, addr, behavior, target);

    BTB(file, addr, behavior, target);
    std::cout<<"Execution Complete"<<endl;
    file.close();

}
