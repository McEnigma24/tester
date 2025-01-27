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

    int change_letter_to_index(const string &letter)
    {
        char l = UTILS::str::to_lower_case(letter)[0];
        return l - 97;
    }

    template <typename T> void swap_indexes(T *tab, int idx_1, int idx_2)
    {
        T tmp = tab[idx_1];

        tab[idx_1] = tab[idx_2];
        tab[idx_2] = tmp;
    }

    template <typename T1, typename T2>
    void mixing_two_tabs(T1 *tab_1, T2 *tab_2, size_t size)
    {
        const int number_of_swaps = 15;

        int r1, r2;
        for (int i = 0; i < number_of_swaps; i++)
        {
            r1 = rand() % size;
            r2 = rand() % size;

            if (r1 == r2)
            {
                i--;
                continue;
            }

            swap_indexes(tab_1, r1, r2);
            swap_indexes(tab_2, r1, r2);
        }
    }

    void show_question_evaluate_answer(single_question &q)
    {
        UTILS::clear_terminal();

        cout << q.question << endl << endl;

        bool correct_answer_is[4];
        memset(correct_answer_is, 0, 4 * sizeof(bool));
        correct_answer_is[change_letter_to_index(q.answer_correct)] = 1;

        string answers[4] = {q.answer_a, q.answer_b, q.answer_c, q.answer_d};

        mixing_two_tabs(correct_answer_is, answers, 4);

        cout << "a: " << answers[0] << endl;
        cout << "b: " << answers[1] << endl;
        cout << "c: " << answers[2] << endl;
        cout << "d: " << answers[3] << endl;
        cout << endl;

        string user_answer;
        cin >> user_answer;

        if (correct_answer_is[change_letter_to_index(user_answer)])
        {
            cout << "                                                GOOD"
                    "\n\n";
            good++;
        }
        else
        {
            cout << "                                                WRONG\n"
                    "                                                          "
                    "answer is <"
                 << q.answer_correct << ">\n\n";
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

        cout << "\n\n\n";
    }

    void start()
    {
        // najpierw mieszamy ich pozycje i potem iterujemy od początku ->
        // zapisujemy ostatnio wykonany index

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

    Test test("input/quiz_2.txt");

    // Test test("input/1.txt");

    return 0;
}
