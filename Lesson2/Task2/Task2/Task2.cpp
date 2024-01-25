#include <string>
#include <iostream>


class VeryHeavyDatabase 
{
public:
    std::string GetData(const std::string& key) const noexcept 
    {
        return "Very Big Data String: " + key;
    }
};


class OneShotDB : VeryHeavyDatabase 
{
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1) : real_db_(real_object), shots(shots) {}
    std::string GetData(const std::string& key) noexcept 
    {
        if (shots != 0)
        {
            auto data = real_db_->GetData(key);
            shots--;
            return data;
        }
        else
        {
            return "Error!";
        }
    }

private:
    int shots{};
    VeryHeavyDatabase* real_db_;
};


int main() 
{
    auto real_db = VeryHeavyDatabase();
    auto limit_db = OneShotDB(std::addressof(real_db), 2);
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    return 0;
}
