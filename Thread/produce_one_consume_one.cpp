#include <iostream>
#include <thread>
#include <deque>
#include <mutex>
#include <chrono>
#include <condition_variable>

using std::deque;
std::mutex mutex_for_pipe;




std::mutex full;
std::mutex empty;

class Network
{
public:
    void post_price(int num) {
            pipe_.push_back(num);
            return;
    }
    int read_price(){
            int back = pipe_.back();
            pipe_.pop_back();
            return back;
    }
    Network() {}
private:
    deque<int> pipe_;
};

class TickerPlant
{
public:
    TickerPlant(Network* buffer)
    {
        this->pipe_ = buffer;
    }
    void run(){
        
        for (int counter = 0; counter < 100 ; counter++){
            empty.lock();
            
            pipe_->post_price(counter);
            
            std::cout << "Send Price: " << counter << std::endl;
            if (counter == 99) std::cout << "END TICKER PLANT" << std::endl;
            
            full.unlock();
        }
        // std::cout << "END TICKER PLANT" << std::endl;
    }
private:
    Network *pipe_;
};

class TradingSystem
{
public:
    TradingSystem(Network* buffer)
    {
        this->pipe_ = buffer;
        full.lock();
    }
    void run(){
        for (int counter = 0; counter < 100 ; counter++)
        {
            full.lock();
            
            int num = pipe_->read_price();

            std::cout << "Receive Price: " << num << std::endl;
            
            empty.unlock();
        }
        std::cout << "END TRADING SYSTEM" << std::endl;
    }
private:
    Network *pipe_;
};

int main() {
    Network b;
    TickerPlant p(&b);
    TradingSystem c(&b);

    std::thread tickerplant_thread(&TickerPlant::run, &p);
    std::thread tradingsystem_thread(&TradingSystem::run, &c);

    tickerplant_thread.join();
    tradingsystem_thread.join();

    return 0;
}