#include "Functions.h"

string pasalintiSkyrybosZenklus(const string& zodis) {
    string rezultatas;

    for (char simbolis : zodis) {
        if (!ispunct(static_cast<unsigned char>(simbolis))) {  
            rezultatas += simbolis;  
        }
    }

    return rezultatas;
}

string sutvarkytiZodzius(const string& zodis) {
    string sutvarkytasZodis = zodis;

    for (char& raide : sutvarkytasZodis) {
        raide = tolower(static_cast<unsigned char>(raide));
    }

    sutvarkytasZodis = pasalintiSkyrybosZenklus(sutvarkytasZodis);

    bool raides = any_of(sutvarkytasZodis.begin(), sutvarkytasZodis.end(),
        [](char c) { return isalpha(static_cast<unsigned char>(c)); });

    return raides ? sutvarkytasZodis : "";

}
void tekstoAnalize(const string& failoPav) {
    ifstream inputFile(failoPav);
    if (!inputFile.is_open()) {
        cerr << "Nepavyko atidaryti failo." << endl;
    }

    map<string, int> zodziu_skaiciavimas;
    string zodis;

    while (inputFile >> zodis) {
        string sutvarkytasZodis = sutvarkytiZodzius(zodis);
        if (!sutvarkytasZodis.empty()) {
            zodziu_skaiciavimas[sutvarkytasZodis]++;
        }
    }

    inputFile.close();

    ofstream outputFile("zodziu_skaicius.txt");
    if (!outputFile.is_open()) {
        cerr << "Nepavyko atidaryti failo." << endl;
    }
    outputFile << setw(15) << left << "Zodis"<< setw(15) << left << "Pasikartojimu skaicius" << endl;
    outputFile << string(37, '-') << endl;
    for (map<string, int>::iterator it = zodziu_skaiciavimas.begin(); it != zodziu_skaiciavimas.end(); ++it) {
        const string& zodis = it->first;
        int count = it->second;
        if (count > 1) {
            outputFile << setw(15) << left << zodis << setw(15) << right << count << endl;
        }
    }
    
    
    outputFile.close();
}

