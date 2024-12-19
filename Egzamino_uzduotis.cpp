
#include "Lib.h"
#include "Functions.h"

int main()
{ 
    setlocale(LC_ALL, "lt_LT.UTF-8");
    tekstoAnalize("Tekstas.txt");
    cout << "Suskaiciuoti faile 'Tekstas.txt' esantys zodziai. Rezultatas isvestas i 'zodziu_skaicius.txt' faila" << endl;

    system("pause");
    return 0; 
}

