#include "__preprocessor__.h"

std::chrono::steady_clock::time_point time_stamp_last_time = std::chrono::steady_clock::now();

std::string get_current_local_time()
{
    auto now = std::chrono::system_clock::now();
    std::time_t czas = std::chrono::system_clock::to_time_t(now);
    std::tm* aktualnyCzas = std::localtime(&czas);

    std::ostringstream oss;
    oss << std::put_time(aktualnyCzas, "%H:%M:%S");
    return oss.str();
}

std::string calculate_time_difference()
{
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - time_stamp_last_time);
    time_stamp_last_time = now; // Aktualizuj czas ostatniego pomiaru

    // Konwersja na jednostki czasu
    long long milliseconds = duration.count();
    long long hours = milliseconds / (1000 * 60 * 60);
    milliseconds %= (1000 * 60 * 60);
    long long minutes = milliseconds / (1000 * 60);
    milliseconds %= (1000 * 60);
    long long seconds = milliseconds / 1000;
    milliseconds %= 1000;

    // Formatowanie wyniku
    std::ostringstream oss;
    if (hours > 0) oss << hours << "h ";
    if (minutes > 0 || hours > 0) oss << minutes << "m ";
    if (seconds > 0 || minutes > 0 || hours > 0) oss << seconds << "s ";
    oss << milliseconds << "ms";
    return oss.str();
}

#define time_stamp(x) std::cout << "\nTIME_STAMP: " << x << " " << get_current_local_time() << " (+ " << calculate_time_difference() << ")\n";
#define time_stamp_reset() calculate_time_difference();
// #define time_stamp(x) 