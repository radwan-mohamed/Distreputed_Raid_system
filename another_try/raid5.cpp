#include <iostream>
#include <algorithm>
#include <string.h>
#include <fstream>

using namespace std;
void cleanString(string& data){
    data.erase(remove_if(data.begin(),data.end(),[](unsigned char c) {return !isprint(c);}),data.end());
}

string recov_Data(const string& wordB,const string& parityWord){
    size_t size = max(wordB.size(),parityWord.size());
    string recovered;
    string paddedWordB = wordB + string(size - wordB.size(),0);
    string padded_parityWord = parityWord + string(size - parityWord.size(),0);
    for(size_t i=0;i<size;i++){
        recovered += (paddedWordB[i] ^ padded_parityWord[i]);
    }
    return recovered;
}


int main(int argc, char** argv){
    ifstream fileB("./data/testB.txt", ios::binary);
    ifstream fileC("./data/testC.txt", ios::binary);

    if(!fileB.is_open() || !fileC.is_open()){
        cerr<<"Error openeing the file"<<endl;
        return 1;
    }
    string lineB, parityLine;

    ofstream reco_A("./data/reco_A.txt", ios::binary);
    if(!reco_A.is_open()){
        cerr<<"Error openeing the file"<<endl;
        return 1;
    }

    while(true){
        bool hasLineParity = static_cast<bool>(getline(fileC, parityLine)); // Read from fileA
        bool hasLineB = static_cast<bool>(getline(fileB, lineB)); // Read from fileB

        if(!hasLineParity && !hasLineB)
            break;
        string recoverA = recov_Data(lineB,parityLine);
        cleanString(recoverA);
        reco_A << recoverA << '\n';
    }
    fileB.close();
    fileC.close();
    reco_A.close();

    return 0;
}
