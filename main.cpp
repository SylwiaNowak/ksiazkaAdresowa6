#include <iostream>
#include <windows.h> // funkcja system("cls")
#include <cstdlib> // funkcja exit(0)
#include <fstream> //biblioteka odpowiedzialna za wspolprace z plikami
#include <algorithm>
#include <string>

using namespace std;

struct Adresat
{
    int idAdresata;
    string imie, nazwisko, nrTelefonu, email, adres;
};

int wczytajAdresatowZPliku(Adresat adresaci[], int iloscAdresatow);
int wprowadzDaneNowegoAdresata(Adresat adresaci[], int iloscAdresatow);
void wyszukajAdresataWedlugImie(Adresat adresaci[], int iloscAdresatow);
void wyszukajAdresataWedlugNazwisko(Adresat adresaci[], int iloscAdresatow);
void wyswietlKsiazkeAdresowa (Adresat adresaci[], int iloscAdresatow);

int main()
{
    Adresat adresaci[1000];
    int iloscAdresatow = 0;
    char wybor;

    iloscAdresatow = wczytajAdresatowZPliku(adresaci, iloscAdresatow);

    while(1)
    {
        system("cls");
        cout << "Ksiazka adresowa" << endl << endl;
        cout << "MENU" << endl;
        cout << "1. Wprowadz nowego adresata" << endl;
        cout << "2. Wyszukaj adresata wg imienia" << endl;
        cout << "3. Wyszukaj adresata wg nazwiska" << endl;
        cout << "4. Wyswietl cala ksiazke adresowa" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> wybor;

        if (wybor == '1')
        {
           iloscAdresatow = wprowadzDaneNowegoAdresata(adresaci, iloscAdresatow);
        }
        else if (wybor == '2')
        {
            wyszukajAdresataWedlugImie(adresaci, iloscAdresatow);
        }
        else if (wybor == '3')
        {
            wyszukajAdresataWedlugNazwisko(adresaci, iloscAdresatow);
        }
        else if (wybor == '4')
        {
            wyswietlKsiazkeAdresowa(adresaci, iloscAdresatow);
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }

    return 0;
}

int wczytajAdresatowZPliku(Adresat adresaci[], int iloscAdresatow)
{
    string linia; //zmienna, do ktorej zapisane beda odczytane z pliku linie
    int nr_linii = 1; //licznik linii

    //tworzenie zmiennej plikowej, nazwa pliku w kodzie zrodlowym to 'ksiazka_adresowa'
    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::in); //odczyt z pliku

    if (plik.good() == false)
    {
        cout << "Ksiazka adresowa jest pusta." << endl;
        cout << "Nacisnij dowolny klawisz, aby przejsc do menu glownego." << endl;
        system("pause");
    }

   //kazdy znak bialy w tym spacja jest uznawany w strumieniu za separator, czyli cos co rozdziela dwa napisy
   //jednak czasem zmienna zawiera spacje, np. podwojne imie

    while(getline(plik,linia)) //getline pozwala aby spacja mogla byc elementem stringu
        //czyli pobiera cala linie tekstu, pobiera ja z pliku tekstowego 'plik' i zapisuje do zmiennej 'linia'
        //petla while zwraca wartosc 'true' do momentu, gdy funkcja 'getline' zwraca linie i zakonczy sie
        //czyli zwroci wartosc 'false' kiedy funkcja getline przestanie zwracac linie
    {
        switch (nr_linii)
        {
        case 1:
            adresaci[iloscAdresatow].idAdresata = atoi(linia.c_str());
            break;
        //konwersja zmiennej typu string na int czyli z napisu zrobic liczbe
        //wszystko co przychodzi z pliku komputer traktuje jako napis
        case 2:
            adresaci[iloscAdresatow].imie = linia;
            break;
        case 3:
            adresaci[iloscAdresatow].nazwisko = linia;
            break;
        case 4:
            adresaci[iloscAdresatow].nrTelefonu = linia;
            break;
        case 5:
            adresaci[iloscAdresatow].email = linia;
            break;
        case 6:
            adresaci[iloscAdresatow].adres = linia;
            break;

        }
        if (nr_linii >= 6) //instrukcja pozwala wydrukowac wszystkich adresatow, bez tego drukuje sie tylko jeden adresat
        {
            nr_linii = 0;
            iloscAdresatow++;
        }
        else
        {
            nr_linii++;// w kazdym kroku petli licznik linii zwieksza sie o jeden
        }

    } //koniec petli 'while'

   plik.close();
   plik.clear();

   return iloscAdresatow;
}

int wprowadzDaneNowegoAdresata(Adresat adresaci[], int iloscAdresatow)
{
    string imie, nazwisko, nrTelefonu, email, adres;
    //DODANIE OSOBY DO PLIKU
    system("cls");
    cout << "Podaj imie nowego adresata: ";                     cin.sync();                      getline(cin, imie);
    cout << "Podaj nazwisko nowego adresata: ";                 cin >> nazwisko;
    cout << "Podaj numer telefonu nowego adresata: ";           cin.sync();                      getline(cin, nrTelefonu);
    cout << "Podaj adres email nowego adresata: ";              cin >> email;
    cout << "Podaj adres do korespondencji nowego adresata: ";  cin.sync(); /*oproznia bufor*/   getline(cin, adres); //wczytuje razem ze spacja

    //WCZYTANIE DANYCH ADRESATA DO TABLICY:
    adresaci[iloscAdresatow].idAdresata = iloscAdresatow + 1;
    adresaci[iloscAdresatow].imie = imie;
    adresaci[iloscAdresatow].nazwisko = nazwisko;
    adresaci[iloscAdresatow].nrTelefonu = nrTelefonu;
    adresaci[iloscAdresatow].email = email;
    adresaci[iloscAdresatow].adres = adres;

    //DODANIE OSOBY DO PLIKU TEKSTOWEGO
    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::app); //input output stream out - wyprowadz
    //czyli pokieruj strumien danych z programu do pliku

    if (plik.good() == true)
    {
        //wyrzucenie danej strumieniem do pliku na dysk:
        plik << adresaci[iloscAdresatow].idAdresata << endl;
        plik << adresaci[iloscAdresatow].imie << endl;
        plik << adresaci[iloscAdresatow].nazwisko << endl;
        plik << adresaci[iloscAdresatow].nrTelefonu << endl;
        plik << adresaci[iloscAdresatow].email << endl;
        plik << adresaci[iloscAdresatow].adres << endl;

        plik.close();
        plik.clear();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku \"ksiazka_adresowa.txt\"" << endl;
    }

    cout << "Adresat dodany";
    Sleep(2000);
    return iloscAdresatow + 1;
}

void wyszukajAdresataWedlugImie(Adresat adresaci[], int iloscAdresatow)
{
    string szukaneImie;
    system("cls");
    cout << "Podaj imie, ktore wyszukac: ";
    cin.sync();
    getline (cin, szukaneImie);
    cout << endl;

    for (int i = 0; i < iloscAdresatow; i++)
   {
       if (adresaci[i].imie == szukaneImie)
       {
           cout << adresaci[i].idAdresata << endl;
           cout << adresaci[i].imie << endl;
           cout << adresaci[i].nazwisko << endl;
           cout << adresaci[i].nrTelefonu << endl;
           cout << adresaci[i].email << endl;
           cout << adresaci[i].adres << endl;

        } // koniec instrukcji 'if'

    } //koniec petli 'for'

    system("pause");
}

void wyszukajAdresataWedlugNazwisko(Adresat adresaci[], int iloscAdresatow)
{
    string szukaneNazwisko;
    system("cls");
    cout << "Podaj nazwisko, ktore wyszukac: ";
    cin >> szukaneNazwisko;
    cout << endl;

   for (int i = 0; i < iloscAdresatow; i++)
   {
       if (adresaci[i].nazwisko == szukaneNazwisko)
       {
           cout << adresaci[i].idAdresata << endl;
           cout << adresaci[i].imie << endl;
           cout << adresaci[i].nazwisko << endl;
           cout << adresaci[i].nrTelefonu << endl;
           cout << adresaci[i].email << endl;
           cout << adresaci[i].adres << endl << endl;

        } // koniec instrukcji 'if'

    } //koniec petli 'for'

    system("pause");
}

void wyswietlKsiazkeAdresowa (Adresat adresaci[], int iloscAdresatow)
{
    system("cls");
    for (int i = 0; i < iloscAdresatow; i++)
   {
       cout << adresaci[i].idAdresata << endl;
       cout << adresaci[i].imie << endl;
       cout << adresaci[i].nazwisko << endl;
       cout << adresaci[i].nrTelefonu << endl;
       cout << adresaci[i].email << endl;
       cout << adresaci[i].adres << endl << endl;
   }
   system ("pause");
}
