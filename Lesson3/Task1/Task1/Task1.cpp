#include <iostream>
#include <string>
#include <fstream>


class LogCommand 
{
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};


class LogConsole : public LogCommand
{
public:
    void print(const std::string& message) override { std::cout << message; }
};


class LogFile : public LogCommand
{
public:
    LogFile(const std::string& file_path) : file_path(file_path) {}
    void print(const std::string& message) override
    {
        std::ofstream f{ file_path };
        f << message;
        f.close();
    };

private:
    std::string file_path{};
};


void print(LogCommand& command)
{
    command.print("Message!");
}


int main()
{
    LogConsole log_console;
    print(log_console);

    std::string file_path{ "file.txt" };
    LogFile log_file{file_path};
    print(log_file);
}