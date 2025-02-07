#include <vector>
#include <functional>
#include <iostream>
#include "candle.h"

using TestFunc = std::function<bool()>;

static std::vector<TestFunc> tests;

// для зеленой и красной (open < close) + нулевая

// Тест 1: Зеленая свеча – значение внутри тела, и вне тела
bool test_body_contains_case1() {
    Candle c{1.0, 5.0, 0.0, 3.0}; // (open 1.0 < close 3.0)
    return c.body_contains(2.0) && !c.body_contains(0.5);
}

// Тест 2: Красная свеча
bool test_body_contains_case2() {
    Candle c{3.0, 6.0, 1.0, 1.0}; // (open = 3.0, close = 1.0)
    return c.body_contains(2.0) && !c.body_contains(3.5);
}

// Тест 3: Нулевая (open == close)
bool test_body_contains_case3() {
    Candle c{2.0, 4.0, 1.5, 2.0}; // (open 2.0 == close 2.0)
    return c.body_contains(2.0) && !c.body_contains(2.1);
}


// Тест 4: Значение внутри диапазона
bool test_contains_inside() {
    Candle c{1.0, 5.0, 0.0, 3.0}; // диапазон: 0.0 - 5.0
    return c.contains(3.0);
}

// Тест 5: Значение на нижней границе диапазона
bool test_contains_lower_edge() {
    Candle c{1.0, 5.0, 0.0, 3.0};
    return c.contains(0.0);
}

// Тест 6: Значение вне диапазона (сверху)
bool test_contains_outside() {
    Candle c{1.0, 5.0, 0.0, 3.0};
    return !c.contains(5.1);
}

// Тест 7: Нормальный диапазон
bool test_full_size_normal() {
    Candle c{1.0, 5.0, 0.0, 3.0}; // full_size = 5.0 - 0.0 = 5.0
    return c.full_size() == 5.0;
}

// Тест 8: Нулевой диапазон (low == high)
bool test_full_size_zero() {
    Candle c{2.0, 2.0, 2.0, 2.0};
    return c.full_size() == 0.0;
}

// Тест 9: Диапазон с отрицательными значениями
bool test_full_size_negative_low() {
    Candle c{-2.0, 3.0, -4.0, 1.0}; // full_size = 3.0 - (-4.0) = 7.0
    return c.full_size() == 7.0;
}

// Тест 10: Зеленая свеча
bool test_body_size_green() {
    Candle c{1.0, 5.0, 0.0, 4.0}; // body_size = 4.0 - 1.0 = 3.0
    return c.body_size() == 3.0;
}

// Тест 11: Красная свеча
bool test_body_size_red() {
    Candle c{4.0, 5.0, 0.0, 1.0}; // body_size = 4.0 - 1.0 = 3.0
    return c.body_size() == 3.0;
}

// Тест 12: Нулевое тело (open == close)
bool test_body_size_zero() {
    Candle c{2.0, 3.0, 1.0, 2.0}; // body_size = 0.0
    return c.body_size() == 0.0;
}

// Тест 13: Красная свеча (open > close)
bool test_is_red_true() {
    Candle c{3.0, 5.0, 1.0, 1.0}; // красная (3.0 > 1.0)
    return c.is_red();
}

// Тест 14: Зеленая свеча – return false
bool test_is_red_false_green() {
    Candle c{1.0, 5.0, 0.0, 3.0}; // зеленая (1.0 < 3.0)
    return !c.is_red();
}

// Тест 15: Свеча с нулевым телом но не красная
bool test_is_red_false_equal() {
    Candle c{2.0, 4.0, 1.0, 2.0}; // open == close
    return !c.is_red();
}

// Тест 16: Зеленая свеча (open < close)
bool test_is_green_true() {
    Candle c{1.0, 5.0, 0.0, 3.0}; // зеленая (1.0 < 3.0)
    return c.is_green();
}

// Тест 17: Красная свеча – return false
bool test_is_green_false_red() {
    Candle c{3.0, 5.0, 1.0, 1.0}; // красная (3.0 > 1.0)
    return !c.is_green();
}

// Тест 18: Свеча с нулевым телом – но не зеленая
bool test_is_green_false_equal() {
    Candle c{2.0, 4.0, 1.0, 2.0}; // open == close
    return !c.is_green();
}

void initTests()
{
    // body_contains
    tests.push_back(test_body_contains_case1);
    tests.push_back(test_body_contains_case2);
    tests.push_back(test_body_contains_case3);

    // contains
    tests.push_back(test_contains_inside);
    tests.push_back(test_contains_lower_edge);
    tests.push_back(test_contains_outside);

    // full_size
    tests.push_back(test_full_size_normal);
    tests.push_back(test_full_size_zero);
    tests.push_back(test_full_size_negative_low);

    // body_size
    tests.push_back(test_body_size_green);
    tests.push_back(test_body_size_red);
    tests.push_back(test_body_size_zero);

    // is_red
    tests.push_back(test_is_red_true);
    tests.push_back(test_is_red_false_green);
    tests.push_back(test_is_red_false_equal);

    // is_green
    tests.push_back(test_is_green_true);
    tests.push_back(test_is_green_false_red);
    tests.push_back(test_is_green_false_equal);
}

int launchTests()
{
    int total = 0;
    int passed = 0;

    for (const auto& test : tests)
    {
        total++;
        std::cout << "Test #" << total << ": ";
        if (test())
        {
            passed++;
            std::cout << "passed\n";
        }
        else
        {
            std::cout << "failed\n";
        }
    }

    std::cout << "\nPassed " << passed << " out of " << total << " tests." << std::endl;
    // passed == total => прошли все тесты
    return total - passed;
}

int main()
{
    initTests();
    return launchTests();
}
