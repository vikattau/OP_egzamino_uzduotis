
#include "Lib.h"
#include "Functions.h"

int main()
{ 
    setlocale(LC_ALL, "lt_LT.UTF-8");

    tekstoAnalize("Tekstas.txt");\
    urlSkaitymas("url_tekstas.txt");

    cout << "Suskaiciuoti faile 'Tekstas.txt' esantys zodziai.\n" <<
        "Rezultatas isvestas i 'zodziu_skaicius.txt' faila.\n" <<
        "Sukurta cross-reference lentele - 'cross_reference_lentele.txt' failas. \n" << 
        "I faila 'rasti_url.txt' irasyti visi url is 'url_tekstas.txt' failo" << endl;
    
    system("pause");
    return 0; 
}

