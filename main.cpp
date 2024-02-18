#include <iostream>
#include <string>
#include <type_traits>

template <typename T> concept ComplexConcept = !std::has_virtual_destructor<T>::value && requires(T obj)
{
    {obj.hash()}->std::convertible_to<long>;
    {obj.toString()}->std::same_as<std::string>;
};

struct Data1
{
    int value_{ 47 };
    ~Data1() = default;
    auto hash()
    {
        return value_;
    }
    auto toString()
    {
        return std::to_string(value_);
    }
};

struct Data2
{
    virtual ~Data2() = default;
};

struct Data3
{
    std::string str_{ "someString" };
    auto hash()
    {
        return str_;
    }
    auto toString()
    {
        return str_.c_str();
    }
};

template <typename T>
void printData(T value)
{
    ComplexConcept auto t = value;
    auto val = t.hash();
    std::cout << "checking type test_1: " << typeid(val).name() << '\n';
    auto str = t.toString();
    std::cout << "checking type test_2: " << typeid(str).name() << '\n';
}

int main()
{
    Data1 d1;
    printData(d1);
    // Data2 d2;
    // printData(d2);
    // Data3 d3;
    // printData(d3);
}
