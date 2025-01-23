#include "__preprocessor__.h"
#include "time_stamp.h"

struct File_Utils
{
    static vector<string> read(const string &file_path)
    {
        vector<string> ret;

        ifstream FILE(file_path);
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

    static void save(const vector<string> &input, const string &file_path,
                     bool add_endl = false)
    {
        ofstream FILE(file_path);
        if (!FILE.is_open())
        {
            FATAL_ERROR("unable to write to file " + file_path);
        }

        for (auto &line : input)
        {
            FILE << line;
            if (add_endl)
                FILE << "\n";
        }

        FILE.close();
    }
};

#define BUFFER_SIZE 100000

#define GET(t, index) get<index>(t)
enum category_index
{
    QUESTION,
    ANSWER_A,
    ANSWER_B,
    ANSWER_C,
    ANSWER_D,
    ANSWER_CORRECT,
    EXPLANATION
};
#define LINE_FORMAT "%s; %s; %s; %s; %s; %s; %s;",

#define tupl tuple<string, string, string, string, string, string, string>

struct Format_Buffer
{
    static tupl input_log_line_output_variables(const string &log_line)
    {
        char question[BUFFER_SIZE];
        char answer_a[BUFFER_SIZE];
        char answer_b[BUFFER_SIZE];
        char answer_c[BUFFER_SIZE];
        char answer_d[BUFFER_SIZE];
        char answer_correct[BUFFER_SIZE];
        char explanation[BUFFER_SIZE];

        sscanf(log_line.c_str(),
               LINE_FORMAT

                   & question,
               &answer_a, &answer_b, &answer_c, &answer_d, &answer_correct,
               &explanation);

        return {question, answer_a,       answer_b,   answer_c,
                answer_d, answer_correct, explanation};
    }

    // static tupl input_log_line_output_variables(const string& log_line)
    // {
    //     string question;
    //     string answer_a;
    //     string answer_b;
    //     string answer_c;
    //     string answer_d;
    //     string answer_correct;
    //     string explanation;

    //     sscanf
    //     (
    //         log_line.c_str(), LINE_FORMAT

    //         &question,
    //         &answer_a,
    //         &answer_b,
    //         &answer_c,
    //         &answer_d,
    //         &answer_correct,
    //         &explanation
    //     );

    //     return
    //     {
    //         question,
    //         answer_a,
    //         answer_b,
    //         answer_c,
    //         answer_d,
    //         answer_correct,
    //         explanation
    //     };
    // }
};

int main(int argc, char *argv[])
{
    time_stamp("It just works");

    // vector<string> tmp;

    // tmp.push_back("test 1");
    // tmp.push_back("test 2");
    // tmp.push_back("test 3");

    // File_Utils::save(tmp, "output/test.txt", true);

    // auto reading = File_Utils::read("output/test.txt");

    // for(auto& line : reading)
    // {
    //     cout << line << endl;
    // }

    auto reading = File_Utils::read("input/quiz_1.txt");

    for (auto &line : reading)
    {
        cout << line << endl;
        auto variables = Format_Buffer::input_log_line_output_variables(line);

        cout << endl;
        cout << GET(variables, 0) << endl;
        cout << GET(variables, 1) << endl;
        cout << GET(variables, 2) << endl;
        cout << GET(variables, 3) << endl;
        cout << GET(variables, 4) << endl;
        cout << GET(variables, 5) << endl;
        cout << GET(variables, 6) << endl;

        cin.get();
    }

    return 0;
}
