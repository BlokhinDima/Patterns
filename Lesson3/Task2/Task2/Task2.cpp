#include <iostream>
#include <vector>
#include <memory>
#include <fstream>


class Observer {
public:
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};


class WarningObserver : public Observer
{
public:
    virtual void onWarning(const std::string& message) { std::cout << message << std::endl; }
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};


class ErrorObserver : public Observer
{
public:
    ErrorObserver(const std::string& file_path) : file_path(file_path) {}
    virtual void onWarning(const std::string& message) {}

    virtual void onError(const std::string& message) 
    {
        std::ofstream f{ file_path };
        if (f.is_open())
            f << message;
            f.close();
    }

    virtual void onFatalError(const std::string& message) {}

private:
    std::string file_path;
};


class FatalErrorObserver : public Observer
{
public:
    FatalErrorObserver(const std::string& file_path) : file_path(file_path) {}
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}

    virtual void onFatalError(const std::string& message)
    {
        std::cout << message << std::endl;

        std::ofstream f{ file_path };
        if (f.is_open())
        { 
            f << message;
            f.close();
        }
    }

private:
    std::string file_path;
};


class Observed
{
public:
    void warning(const std::string& message) const
    {
        for (auto observer : observers)
        {
            if (auto str_ptr = observer.lock())
                str_ptr->onWarning(message);
        }
    }

    void error(const std::string& message) const
    {
        for (auto observer : observers)
        {
            if (auto str_ptr = observer.lock())
                str_ptr->onError(message);
        }
    }

    void fatalError(const std::string& message) const
    {
        for (auto observer : observers)
        {
            if (auto str_ptr = observer.lock())
                str_ptr->onFatalError(message);
        }
    }

    void addObserver(std::weak_ptr<Observer> observer)
    {
        observers.push_back(observer);
    }

private:
    std::vector<std::weak_ptr<Observer>> observers;
};


int main()
{
    std::string file_path{ "err_log.txt" };
    std::string file_path2{ "fatal_err_log.txt" };

    std::shared_ptr<WarningObserver> warn_observer_sp = std::make_shared<WarningObserver>();
    std::weak_ptr<WarningObserver> warn_observer_wp = warn_observer_sp;

    std::shared_ptr<ErrorObserver> err_observer_sp = std::make_shared<ErrorObserver>(file_path);
    std::weak_ptr<ErrorObserver> err_observer_wp = err_observer_sp;

    std::shared_ptr<FatalErrorObserver> fatal_err_observer_sp = std::make_shared<FatalErrorObserver>(file_path2);
    std::weak_ptr<FatalErrorObserver> fatal_err_observer_wp = fatal_err_observer_sp;

    Observed observed;
    observed.addObserver(warn_observer_wp);
    observed.addObserver(err_observer_wp);
    observed.addObserver(fatal_err_observer_wp);

    observed.warning("Warning!");
    observed.error("Error!");
    observed.fatalError("Fatal Error!");
}
