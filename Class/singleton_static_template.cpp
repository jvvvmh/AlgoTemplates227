#include <iostream>

template<typename T>
class Singleton{
public:
    void display_log(){
        std::cout << "I am a singleton" << std::endl;
    }
    void display_log(std::string logtext){
        std::cout << logtext << std::endl;
    }
    static T& getInstance(){
        static T* a = new T();
        return *a;
    }
};


class Logger:public Singleton<Logger>
{
    friend class Singleton<Logger>;
private:
    Logger(){}; 
    ~Logger(){};
public:
    void display_log(std::string logtext){
        std::cout << logtext << std::endl;
        static_cast<Singleton<Logger> *>(this)->display_log();
    }
};

Logger * f1()
{
    Logger::getInstance().display_log("display log from f1");
    return &Logger::getInstance();
}

Logger * f2()
{
    Logger::getInstance().display_log("display log from f2");
    return &Logger::getInstance();
}

int main(void)
{
    Logger::getInstance().display_log("Try to make it work");      // use Logger
    std::cout << (f1()==f2()) << std::endl;
    return 0;
}
