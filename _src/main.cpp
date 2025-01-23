#include "__preprocessor__.h"
#include "time_stamp.h"
#include <fstream>

class File_Utils
{
    static vector<string> read(const string &file_path)
    {
        vector<string> ret;

        std::ifstream FILE(file_path);
        if (!FILE.is_open())
        {
            FATAL_ERROR("unable to read file " + file_path);
        }

        string tmp_line;
        while (std::getline(FILE, tmp_line))
        {
            ret.push_back(tmp_line);
        }

        FILE.close();

        return ret;
    }
};

int main(int argc, char *argv[])
{
    time_stamp("It just works");

    return 0;
}
