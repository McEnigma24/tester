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

struct single_question
{
    u16 status; // 0 - not answered // 1 - answered

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
        : status(0), question(_question), answer_a(_answer_a),
          answer_b(_answer_b), answer_c(_answer_c), answer_d(_answer_d),
          answer_correct(_answer_correct), explanation(_explanation)
    {
    }
};

struct Format_Buffer
{
    static single_question input_log_line_output_obj(const string &log_line)
    {
        auto result = UTILS::str::split_string(log_line, '; ');
        cout << endl << endl;
        for (auto &r : result)
        {
            r.pop_back();
            std::replace(r.begin(), r.end(), '_', ' ');
        }

        return {result[0], result[1], result[2], result[3],
                result[4], result[5], result[6]};
    }
};

class Test
{
    vector<single_question> all_questions;
    float good;
    float bad;

    void show_question_evaluate_answer(single_question &q)
    {
        UTILS::clear_terminal();

        cout << q.question << endl << endl;
        // pozamieniać miejscami kilkanaście razy losowe indexy, ta tablica i
        // tablica z zapisanym poprawnym wynikiem, te same zmiany na jednej i na
        // drugiej -> nie gubimy poprawnej odpowiedzi
        cout << "a: " << q.answer_a << endl;
        cout << "b: " << q.answer_b << endl;
        cout << "c: " << q.answer_c << endl;
        cout << "d: " << q.answer_d << endl;
        cout << endl;

        string user_answer;
        cin >> user_answer;

        if (UTILS::str::to_lower_case(user_answer) ==
            UTILS::str::to_lower_case(q.answer_correct))
        {
            cout << "                                                GOOD - "
                    "Gread job\n\n";
            good++;
        }
        else
        {
            cout << "                                                WRONG - "
                    "answer is "
                 << q.answer_correct << "\n\n";
            bad++;
        }

        cout << q.explanation << endl;
        cin.get();
        cin.get();

        q.status = 1;
    }

    single_question &random_question()
    {
        u64 random_index{};
        do
        {
            random_index = rand() % all_questions.size();
        }
        while (all_questions[random_index].status != 0);

        return all_questions[random_index];
    }

    void show_score()
    {
        UTILS::clear_terminal();

        u64 g = (good / all_questions.size()) * 100;
        u64 b = (bad / all_questions.size()) * 100;

        cout << "correct: " << g << "%" << endl;
        cout << "bad:     " << b << "%" << endl;
    }

    void start()
    {
        for (auto &q : all_questions)
        {
            show_question_evaluate_answer(random_question());
        }

        show_score();
    }

  public:
    Test(const string &input_file) : good(0), bad(0)
    {
        auto all_lines = File_Utils::read_from(input_file);

        for (auto &line : all_lines)
        {
            if (line != "\n" && line != "")
            {
                auto question = Format_Buffer::input_log_line_output_obj(line);

                // cout << question.question << endl;
                // cout << question.answer_a << endl;
                // cout << question.answer_b << endl;
                // cout << question.answer_c << endl;
                // cout << question.answer_d << endl;
                // cout << question.answer_correct << endl;
                // cout << question.explanation << endl;

                all_questions.push_back(question);
            }
        }

        start();
    }
};

int main(int argc, char *argv[])
{
    srand(time(null));
    time_stamp("It just works");

    Test test("input/quiz_1.txt");

    return 0;
}
