#include "__preprocessor__.h"
#include "time_stamp.h"

class File_Utils
{
    static vector<string> read(const string &file_path)
    {
        vector<string> ret;

        std::ifstream FILE(file_path);

        if (!plik.is_open())
        {
            std::cerr << "Nie można otworzyć pliku!" << std::endl;
            return 1;
        }

        std::string linia;
        while (std::getline(plik, linia))
        {                                    // Czyta linijka po linijce
            std::cout << linia << std::endl; // Wypisuje linijkę na konsolę
        }

        plik.close(); // Zamknięcie pliku

        return ret;
    }
}

int main(int argc, char *argv[])
{
    time_stamp("It just works");

    ifstream FILE_input();

    if (!plik.is_open())
    { // Sprawdza, czy plik został poprawnie otwarty
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
        return 1;
    }

    std::string linia;
    while (std::getline(plik, linia))
    {                                    // Czyta linijka po linijce
        std::cout << linia << std::endl; // Wypisuje linijkę na konsolę
    }

    plik.close(); // Zamknięcie pliku

    file.close();

    return 0;
}
