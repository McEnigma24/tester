#include "__preprocessor__.h"
#include "time_stamp.h"

struct File_Utils
{
    static vector<string> read_from(const string &file_path)
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

    static void save_to(const vector<string> &input, const string &file_path,
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

std::vector<std::string> splitString(const std::string &input, char delimiter)
{
    std::vector<std::string> result;
    std::string segment;
    std::istringstream stream(input);

    while (std::getline(stream, segment, delimiter))
    {
        result.push_back(segment);
    }

    return result;
}

struct single_question
{
    string question;
    string answer_a;
    string answer_b;
    string answer_c;
    string answer_d;
    string answer_correct;
    string explanation;

    single_question(string _question, string _answer_a, string _answer_b,
                    string _answer_c, string _answer_d, string _answer_correct,
                    string _explanation)
        : question(_question), answer_a(_answer_a), answer_b(_answer_b),
          answer_c(_answer_c), answer_d(_answer_d),
          answer_correct(_answer_correct), explanation(_explanation)
    {
    }
};

// clang-format off
struct Format_Buffer
{
    static tupl input_log_line_output_variables(const string &log_line)
    {
        auto result = splitString(log_line, '; ');

        cout << endl << endl;
        for(auto& r : result)
        {
            r.pop_back();
            std::replace(r.begin(), r.end(), '_', ' ');
        }

        return
        {
            result[0],
            result[1],
            result[2],
            result[3],
            result[4],
            result[5],
            result[6]
        };
    }

    static single_question input_log_line_output_obj(const string &log_line)
    {
        auto result = splitString(log_line, '; ');

        cout << endl << endl;
        for(auto& r : result)
        {
            r.pop_back();
            std::replace(r.begin(), r.end(), '_', ' ');
        }

        return
        {
            result[0],
            result[1],
            result[2],
            result[3],
            result[4],
            result[5],
            result[6]
        };
    }
};
// clang-format on

class Test
{
    vector<single_question> all_questions;

  public:
    Test(const string &input_file)
    {
        auto all_lines = File_Utils::read_from(input_file);

        for (auto &line : all_lines)
        {
            if (line != "\n" && line != "")
            {
                auto question = Format_Buffer::input_log_line_output_obj(line);

                cout << question.question << endl;
                cout << question.answer_a << endl;
                cout << question.answer_b << endl;
                cout << question.answer_c << endl;
                cout << question.answer_d << endl;
                cout << question.answer_correct << endl;
                cout << question.explanation << endl;
                // cin.get();

                all_questions.push_back(question);
            }
        }

        cin.get();

        for (auto &question : all_questions)
        {
            cout << question.question << endl;
            cout << question.answer_a << endl;
            cout << question.answer_b << endl;
            cout << question.answer_c << endl;
            cout << question.answer_d << endl;
            cout << question.answer_correct << endl;
            cout << question.explanation << endl;

            cin.get();
        }
    }
};

int main(int argc, char *argv[])
{
    time_stamp("It just works");

    Test test("input/quiz_1.txt");

    return 0;
}
