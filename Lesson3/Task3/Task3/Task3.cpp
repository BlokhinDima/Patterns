#include <iostream>
#include <memory>
#include <fstream>
#include <exception>


namespace log_messages
{
    enum class Type
    {
        WARNING,
        ERROR,
        FATAL_ERROR,
        UNKNOWN_MESSAGE
    };

    class LogMessage {
    public:

        LogMessage(Type type) : type_(type) {}
        Type type() const { return type_; };

        const std::string message() const
        {
            switch (type_)
            {
            case Type::WARNING:
                return "Warning!";
                break;
            case Type::ERROR:
                return "Error!";
                break;
            case Type::FATAL_ERROR:
                return "Fatal Error!";
                break;
            case Type::UNKNOWN_MESSAGE:
                return "Unknown Message!";
                break;
            default:
                return "";
                break;
            }
        };

    private:
        Type type_;
    };
}


class Handler
{
public:
    virtual void handleMessage(log_messages::LogMessage& log_message) {}
    void setNext(std::weak_ptr<Handler> next_handler) { next_handler_ = next_handler; }

protected:
    std::weak_ptr<Handler> next_handler_;
};


class WarningHandler : public Handler
{
public:

    void handleMessage(log_messages::LogMessage& log_message) override
    {
        if (log_message.type() == log_messages::Type::WARNING)
        {
            std::cout << "Warning handler is working ..." << std::endl;
            std::cout << log_message.message() << std::endl;
        }
        else
        {
            if (auto str_ptr = next_handler_.lock())
                str_ptr->handleMessage(log_message);
        }
    }
};


class ErrorHandler : public Handler
{
public:
    ErrorHandler(const std::string& file_path) : file_path(file_path) {}

    void handleMessage(log_messages::LogMessage& log_message) override
    {
        if (log_message.type() == log_messages::Type::ERROR)
        {
            std::cout << "Error handler is working ..." << std::endl;
            std::ofstream f{ file_path };
            if (f.is_open())
            {
                f << log_message.message();
                f.close();
            }
        }
        else
        {
            if (auto str_ptr = next_handler_.lock())
                str_ptr->handleMessage(log_message);
        }
    }

private:
    std::string file_path;
};


class FatalErrorHandler : public Handler
{
public:

    void handleMessage(log_messages::LogMessage& log_message) override
    {
        if (log_message.type() == log_messages::Type::FATAL_ERROR)
        {
            std::cout << "Fatal error handler is working ..." << std::endl;
            throw std::logic_error(log_message.message());
        }
        else
        {
            if (auto str_ptr = next_handler_.lock())
                str_ptr->handleMessage(log_message);
        }
    }
};


class UnknownMessageHandler : public Handler
{
public:
   
    void handleMessage(log_messages::LogMessage& log_message) override
    {
        if (log_message.type() == log_messages::Type::UNKNOWN_MESSAGE)
        {
            std::cout << "Unknown message handler is working ..." << std::endl;
            throw std::logic_error(log_message.message());
        }
        else
        {
            if (auto str_ptr = next_handler_.lock())
                str_ptr->handleMessage(log_message);
        }
    }
};


int main()
{
    try
    {
        using namespace log_messages;

        std::string file_path{ "err_log.txt" };

        LogMessage warn_message(Type::WARNING);
        LogMessage err_message(Type::ERROR);
        LogMessage fatal_err_message(Type::FATAL_ERROR);
        LogMessage unknown_message(Type::UNKNOWN_MESSAGE);

        auto warn_handler_sp = std::make_shared<WarningHandler>();
        std::weak_ptr<WarningHandler> warn_handler_wp = warn_handler_sp;

        auto err_handler_sp = std::make_shared<ErrorHandler>(file_path);
        std::weak_ptr<ErrorHandler> err_handler_wp = err_handler_sp;
        err_handler_sp->setNext(warn_handler_wp);

        auto fatal_err_handler_sp = std::make_shared<FatalErrorHandler>();
        std::weak_ptr<FatalErrorHandler> fatal_err_handler_wp = fatal_err_handler_sp;
        fatal_err_handler_sp->setNext(err_handler_wp);

        auto unknown_msg_handler_sp = std::make_shared<UnknownMessageHandler>();
        unknown_msg_handler_sp->setNext(fatal_err_handler_wp);

        //unknown_msg_handler_sp->handleMessage(warn_message);
        unknown_msg_handler_sp->handleMessage(err_message);
        //unknown_msg_handler_sp->handleMessage(fatal_err_message);
        //unknown_msg_handler_sp->handleMessage(unknown_message);
    }
    catch (const std::logic_error& e)
    {
        std::cout << "Caught exception: " << e.what() << "\n";
        throw e;
    }
}
