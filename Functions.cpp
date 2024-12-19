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

    transform(sutvarkytasZodis.begin(), sutvarkytasZodis.end(), sutvarkytasZodis.begin(), ::tolower);
    
    sutvarkytasZodis.erase(remove_if(sutvarkytasZodis.begin(), sutvarkytasZodis.end(), ::ispunct), sutvarkytasZodis.end());
    
    bool raides = any_of(sutvarkytasZodis.begin(), sutvarkytasZodis.end(),
        [](char c) { return isalpha(static_cast<unsigned char>(c)); });

    if (!raides) {
        return "";
    }

    return sutvarkytasZodis;

}
void tekstoAnalize(const string& failoPav) {
    ifstream inputFile(failoPav);
    if (!inputFile.is_open()) {
        cerr << "Nepavyko atidaryti failo." << endl;
    }

    map<string, int> zodziu_skaiciavimas;
    map<string, pair<int, set<int>>> zodziuCrossReference;
    
    string eilute;
    int eilutesNumeris = 0;

    while (getline(inputFile, eilute)) {
        eilutesNumeris++;

        stringstream ss(eilute);
        string zodis;

        while (ss >> zodis) {  
            string sutvarkytasZodis = sutvarkytiZodzius(zodis);

            if (!sutvarkytasZodis.empty()) {
                zodziu_skaiciavimas[sutvarkytasZodis]++;

                zodziuCrossReference[sutvarkytasZodis].first = zodziu_skaiciavimas[sutvarkytasZodis];
                zodziuCrossReference[sutvarkytasZodis].second.insert(eilutesNumeris);
            }
        }
    }

    inputFile.close();

    ofstream outputFile("zodziu_skaicius.txt");
    if (!outputFile.is_open()) {
        cerr << "Nepavyko atidaryti failo." << endl;
    }

    ofstream crossRefFile("cross_reference_lentele.txt");
    if (!crossRefFile.is_open()) {
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

    crossRefFile << setw(15) << left << "Zodis" << setw(15) << left << "Eiluciu numeriai" << endl;
    crossRefFile << string(37, '-') << endl;
    for (const auto& it : zodziuCrossReference) {
        const string& zodis = it.first;
        int count = it.second.first;
        const set<int>& eilutes = it.second.second;
        if (count > 1) {  
            crossRefFile << setw(15) << left << it.first << setw(15) << left;
            for (const int line : eilutes) {
                crossRefFile << setw(2) << left << line << " ";
            }
            crossRefFile << endl;
        }
    }
    
    crossRefFile.close();
    outputFile.close();
}

