#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <locale.h>
#include <vector>
#include "Haslo.h"
#include "Szyfrowanie.h"
#include <chrono>

using namespace std;
void wczytajHasla(string& fileName);
void zapiszPlik(string& fileName);
void addPassword(string& fileName, Haslo& h);
void usunHaslo(string& witryna);
std::string wybierzKategorie();
std::string generujHaslo(int iloscZnakow, bool zawieraMaleLitery, bool zawieraWielkieLitery, bool zawieraZnakiSpecjalne);
void wyszukajHaslo(string& witryna);
void usunKategorie(string& kat);

bool operator==(const Haslo& haslo1, const Haslo& haslo2) {
    return haslo1.haslo == haslo2.haslo && haslo1.witryna ==haslo2.witryna && haslo1.kategoria == haslo2.kategoria;
}
vector<string> kategorie;
vector<Haslo> wszystkie_hasla;
string PoprawneHaslo = "haslo123";

int main() {
    string fileName;
    int choice;
    string podaneHaslo;
    cout << "Podaj Haslo: " << endl;
    cin >> podaneHaslo;
    if (podaneHaslo == PoprawneHaslo) {
        std::ifstream inputFile("log.txt");
        if (!inputFile) {
            cerr << "Blad podczas otwierania pliku log." << endl;
            return 1;
        }
        string timestamp;
        getline(inputFile, timestamp);
        inputFile.close();
        cout << "Ostatni timestamp: " << timestamp << endl;

           bool czy_istnieje =false;
           do{
               cout << "podaj nazwe pliku: " << endl;
               cin >> fileName;
               ifstream file(fileName);
               if(file){
                   czy_istnieje = true;
               }
               else{
                   cout<<"zly plik ";
               }
           }while(!czy_istnieje);

        wczytajHasla(fileName);
        do {
            cout << "1. Wyszukaj hasla" << endl;
            cout << "2. Dodaj haslo" << endl;
            cout << "3. Usun haslo" << endl;
            cout << "4. dodaj kategorie" << endl;
            cout << "5. usun kategorie" << endl;
            cout << "0. Wyjscie" << endl;
            cout << "Wybierz opcje: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    string n;
                    cout << "podaj nazwe: " << endl;
                    cin >> n;
                    wyszukajHaslo(n);
                    break;
                }
                case 2: {
                    string witryna, haslo, login, www;
                    cout << "Podaj nazwe hasla: ";
                    cin >> witryna;
                    cout<< "Chcesz wpisac haslo czy wolisz by zostalo wygenerowane? (wpisz 1-wygenerowane haslo 0 -wlasne): ";
                    int decyzja_haslo;
                    cin >> decyzja_haslo;

                    if (decyzja_haslo) {
                        int iloscZnakow;
                        bool zawieraMaleLitery, zawieraWielkieLitery, zawieraZnakiSpecjalne;
                        cout << "podaj ilosc znakow: ";
                        cin >> iloscZnakow;

                        cout << "Czy ma zawierac male litery? (1 - tak, 0 - nie): " << endl;
                        cin >> zawieraMaleLitery;

                        cout << "Czy ma zawierac wielkie litery? (1 - tak, 0 - nie): " << endl;
                        cin >> zawieraWielkieLitery;

                        cout << "Czy ma zawierac znaki specjalne? (1 - tak, 0 - nie): " << endl;
                        cin >> zawieraZnakiSpecjalne;

                        string h = generujHaslo(iloscZnakow, zawieraMaleLitery, zawieraWielkieLitery,zawieraZnakiSpecjalne);
                        cout << "wygenerowane haslo: " << h << endl;
                        haslo = h;
                    } else {
                        cout << "Podaj haslo: ";
                        cin >> haslo;
                    }
                    string kategoria = wybierzKategorie();
                    if (kategoria == "") {
                        break;
                    }
                    int decyzja_www;
                    cout << "czy chcesz podac www? (1-tak 0-nie)";
                    cin >> decyzja_www;
                    if (decyzja_www == 1) {
                        cout << "Podaj strone www: ";
                        cin >> www;}
                    else{
                        www="0";
                    }
                    int decyzja_login;
                    cout << "czy chcesz podac login? (1-tak 0-nie)"<<endl;
                    cin >>decyzja_login;
                    if(decyzja_login) {
                        cout << "Podaj login: ";
                        cin >> login;
                    }
                    else{
                        login ="0";
                    }
                        Haslo h(witryna, haslo, kategoria, www, login);
                        addPassword(fileName, h);
                    break;
                }
                case 3: {
                    string website;
                    cout << "Podaj nazwe hasla do usuniecia: ";
                    cin >> website;
                    usunHaslo(website);
                    zapiszPlik(fileName);
                    wczytajHasla(fileName);
                    for (Haslo h: wszystkie_hasla) {
                        cout << h.witryna << " " << h.haslo << endl;
                    }
                    break;
                }
                case 4: {
                    string nazwa;
                    cout << "Podaj nazwe kategori: ";
                    cin >> nazwa;
                    kategorie.push_back(nazwa);
                    break;
                }
                case 5: {
                    string nazwa;
                    cout << "Podaj nazwe kategori: ";
                    cin >> nazwa;
                    usunKategorie(nazwa);
                    zapiszPlik(fileName);
                    wczytajHasla(fileName);
                    break;
                }
                case 0:
                    cout << "Program zakonczony." << endl;
                    break;
                default:
                    cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
                    break;
            }
            cout << endl;
        } while (choice != 0);
    } else {
        cout << "niepoprawne haslo";
        std::ofstream outputFile("log.txt");
        if (!outputFile) {
            std::cerr << "Blad podczas otwierania pliku." << std::endl;
            return 1;
        }
        // Pobranie aktualnego timestampu
        auto currentTimestamp = std::chrono::system_clock::now();
        auto currentTime = std::chrono::system_clock::to_time_t(currentTimestamp);
        std::string currentTimestampStr = std::ctime(&currentTime);
        outputFile << currentTimestampStr;
        outputFile.close();
    }
return 0;
}
/**
 * \brief Wczytuje dane haseł z pliku.
 *
 * Funkcja wczytuje dane haseł z podanego pliku tekstowego. Każda linia w pliku reprezentuje
 * parametry hasła. Paraetry składają się z kilku pól oddzielonych spacjami.
 * Dane pola są deszyfrowane przy użyciu funkcji deszyfrujTekst. Wczytane hasło jest dodawane do wektora.
 *
 * \param fileName Nazwa pliku, z którego wczytywane są dane haseł.
 *
 */
void wczytajHasla(string& fileName) {
    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "Blad podczas otwierania pliku." << endl;
        return;
    }
    string line;
    wszystkie_hasla.clear();
    kategorie.clear();
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string wiersz;
        vector<string> dane;
        while(ss >> wiersz){
            dane.push_back(wiersz);
        }
        for(int i=0;i<dane.size();i++){
            dane[i]=deszyfrujTekst(dane[i]);
        }
            kategorie.push_back(dane[2]);

        if(dane.size()>3){
            Haslo h(dane[0],dane[1],dane[2],dane[3],dane[4]);
            wszystkie_hasla.push_back(h);
        } else{
            Haslo h(dane[0],dane[1],dane[2]);
            wszystkie_hasla.push_back(h);
        }
        cout <<endl;
    }
    inputFile.close();
}

/**
 * \brief Dodaje hasło do pliku i struktur danych.
 *
 * Funkcja dodaje podane hasło i jego parametry do pliku o podanej nazwie oraz do wektora.
 * Hasło jest dodawane na koniec pliku w formacie tekstowym, po zaszyfrowaniu odpowiednich pól.
 *
 * \param fileName Nazwa pliku, do którego ma zostać dodane hasło.
 * \param h hasło do dodania.
 *
 */
void addPassword(string& fileName, Haslo& h) {
    ofstream outputFile(fileName, ios::app);
    if (!outputFile) {
        cerr << "Blad podczas otwierania pliku." << endl;
        return;
    }
    wszystkie_hasla.push_back(h);

    string linia = szyfrujTekst(h.witryna) + " " +szyfrujTekst(h.haslo) + " " + szyfrujTekst(h.kategoria);
    if(h.www!=""){
        linia += " " +szyfrujTekst(h.www);
    }
    if(h.login!=""){
        linia += " " + szyfrujTekst(h.login);
    }
    outputFile << linia<<endl;
    outputFile.close();
    cout << "Haslo zostalo dodane." << endl;
}
/**
 * \brief Usuwa hasło o podanej nazwie.
 *
 * Funkcja usuwa hasło o podanej nazwie z listy wszystkich haseł.
 *
 * \param witryna Nazwa, dla której ma zostać usunięte hasło.
 */
void usunHaslo(string& witryna){
    for(Haslo h : wszystkie_hasla){
        if(h.witryna==witryna){
            erase(wszystkie_hasla,h);
        }
    }
}
/**
 * \brief Zapisuje dane haseł do pliku.
 *
 * Funkcja zapisuje zaszyfrowane dane haseł do pliku o podanej nazwie. Domyślny plik zostaje zastąpiony
 * nowym plikiem, zawierającym zaktualizowane dane haseł. Funkcja tworzy tymczasowy plik,
 * do którego zapisuje dane, a następnie usuwa oryginalny plik i zmienia nazwę tymczasowego
 * pliku na docelową nazwę.
 *
 * \param fileName Nazwa pliku, do którego mają zostać zapisane dane haseł.
 *
 */
void zapiszPlik(string& fileName) {
    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "Blad podczas otwierania pliku." << endl;
        return;
    }
    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cerr << "Blad podczas tworzenia pliku tymczasowego." << endl;
        inputFile.close();
        return;
    }
    //string line;
    for(Haslo h : wszystkie_hasla){
        string linia = szyfrujTekst(h.witryna) + " " + szyfrujTekst(h.haslo) + " " + szyfrujTekst(h.kategoria);
        if(h.www != ""){
            linia += " " + szyfrujTekst(h.login);
        }
        if(h.login != ""){
            linia += " " + szyfrujTekst(h.login);
        }
        istringstream iss(linia);
        tempFile << linia << endl;
    }
    inputFile.close();
    tempFile.close();
    if (remove(fileName.c_str()) != 0) {
        cerr << "Blad podczas usuwania pliku." << endl;
        return;
    }
    if (rename("temp.txt", fileName.c_str()) != 0) {
        cerr << "Blad podczas zmiany nazwy pliku tymczasowego." << endl;
        return;
    }
}
/**
 * \brief Wybiera kategorię z dostępnych kategorii.
 *
 * Funkcja wyświetla listę dostępnych kategorii i prosi użytkownika o podanie numeru kategorii.
 * Jeśli lista kategorii jest pusta, funkcja wyświetla odpowiedni komunikat i zwraca pusty string.
 * Użytkownik ma możliwość wybrania numeru kategorii od 1 do liczby dostępnych kategorii. Po poprawnym
 * wybraniu numeru, funkcja zwraca nazwę wybranej kategorii.
 *
 * \return Nazwa wybranej kategorii lub pusty string, jeśli lista kategorii jest pusta.
 */
string wybierzKategorie() {
    int numer;
    if(kategorie.empty()){
        cout<<"brak kategori"<<endl;
        return "";
    };
    do {
        cout << "Lista kategorii: ";
        for (int i = 0; i < kategorie.size(); ++i) {
            cout << i + 1 << ". " << kategorie[i] << endl;
        }
        cout << "Podaj numer kategorii: ";
        cin >> numer;
    }while (!(numer >= 1 && numer <= kategorie.size()));
        return kategorie[numer - 1];
}
/**
 * \brief Generuje losowe hasło o zadanych parametrach.
 *
 * Funkcja generuje losowe hasło o podanej liczbie znaków oraz uwzględniające
 * zadane opcje, czyli zawierające małe litery, wielkie litery i znaki specjalne.
 * Funkcja zwraca wygenerowane hasło.
 *
 * \param iloscZnakow Liczba znaków w wygenerowanym haśle.
 * \param zawieraMaleLitery Określa, czy hasło ma zawierać małe litery.
 * \param zawieraWielkieLitery Określa, czy hasło ma zawierać wielkie litery.
 * \param zawieraZnakiSpecjalne Określa, czy hasło ma zawierać znaki specjalne.
 *
 * \return Wygenerowane hasło.
 */
string generujHaslo(int iloscZnakow, bool zawieraMaleLitery, bool zawieraWielkieLitery, bool zawieraZnakiSpecjalne) {
    string haslo;
    string maleLitery = "abcdefghijklmnopqrstuvwxyz";
    string wielkieLitery = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string znakiSpecjalne = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    string dostepneZnaki;
    //jesli true, dodaje wskazane znaki
    dostepneZnaki += (zawieraMaleLitery ? maleLitery : "");
    dostepneZnaki += (zawieraWielkieLitery ? wielkieLitery : "");
    dostepneZnaki += (zawieraZnakiSpecjalne ? znakiSpecjalne : "");
    //losowanie
    for (int i = 0; i < iloscZnakow; ++i) {
        int losowyIndeks = rand() % dostepneZnaki.length();
        haslo += dostepneZnaki[losowyIndeks];
    }
    return haslo;
}
/**
 * \brief Wyszukuje hasła dla podanej witryny.
 *
 * Funkcja wyszukuje hasła dla podanej nazwy w liście wszystkich haseł.
 * Jeśli znalezione zostaną pasujące hasła, funkcja wyświetla je na ekranie,
 * wraz z informacjami o haśle. Jeśli nie zostaną znalezione pasujące hasła,
 * funkcja wyświetla odpowiedni komunikat.
 *
 * \param witryna Nazwa, dla której mają zostać wyszukane hasła.
 */
void wyszukajHaslo(string& witryna){
    int counter = 0;
    for(Haslo h : wszystkie_hasla){
        if(h.witryna==witryna){
            counter++;
            cout << "Nazwa hasla: " + h.witryna + " haslo: " + h.haslo + " kategoria: " + h.kategoria;
            if(h.www !="0"){
                cout << " www: " + h.www;
            }
            if(h.login !="0"){
                cout <<  " login: " + h.login;
            }
            cout<<endl;
        }
    }
    if(counter==0){
        cout<<"brak hasel";
    }
}
/**
 * \brief Usuwa kategorię wraz z powiązanymi hasłami.
 *
 * Funkcja usuwa podaną kategorię z listy kategorii oraz usuwa wszystkie hasła,
 * które są przypisane do tej kategorii. Po usunięciu kategorii i powiązanych haseł,
 * struktury danych są aktualizowane.
 *
 * \param kat Kategoria do usunięcia.
 */
void usunKategorie(string& kat){
    for(int i=0;i<kategorie.size(); i++){
        if(kategorie[i]==kat){
            kategorie.erase(kategorie.begin()+i);
            i--;
        }
    }
        for(int i=0;i<wszystkie_hasla.size(); i++){
            if(wszystkie_hasla[i].kategoria==kat){
                wszystkie_hasla.erase(wszystkie_hasla.begin()+i);
                i--;
            }
        }
}

