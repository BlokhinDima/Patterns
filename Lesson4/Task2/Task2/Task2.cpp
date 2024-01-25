#include <fstream>
#include <iostream>

class Printable
{
public:
    virtual ~Printable() = default;
    virtual std::string print() const = 0;
};


class Data : public Printable
{
public:
    Data(std::string data) : data_(std::move(data)) {}

protected:
    std::string data_;
};


class TextData : public Data
{
public:

    TextData(std::string data) : Data(data) {}
    std::string print() const override { return data_; }
};

class HTMLData : public Data
{
public:
    HTMLData(std::string data) : Data(data) {}
    std::string print() const override { return "<html>" + data_ + "<html/>"; }
};


class JSONData : public Data
{
public:
    JSONData(std::string data) : Data(data) {}
    std::string print() const override { return "{ \"data\": \"" + data_ + "\"}"; }
};


void saveTo(std::ofstream& file, const Printable& printable)
{
    file << printable.print();
}


void printDataToConsole(const Printable& printable)
{
    std::cout << printable.print() << std::endl;
}


int main()
{
    TextData text_data{ "Hello" };
    JSONData json_data{ "Hello" };
    HTMLData html_data{ "Hello" };
    printDataToConsole(text_data);
    printDataToConsole(json_data);
    printDataToConsole(html_data);
}
