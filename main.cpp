#include <atomic>
#include <cassert>
#include <iostream>
#include <thread>

std::atomic<unsigned long long> sum;
std::atomic<bool> running(true);

void usage(const char* name)
{
    std::cout << "Usage: " << name << " number_of_threads" << std::endl;
}

void worker_thread(int time)
{
    while (running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        sum++;
    }
}

int main(int argc, char** argv)
{
    sum = 0;

    if (argc >= 2)
    {
        int num = 0;
        try
        {
             num = std::stoi(argv[1]);
        }
        catch (std::invalid_argument& e)
        {
            std::cout << "Invalid number of threads " << argv[1] << ", " << e.what() << std::endl;
            usage(argv[0]);
            exit(1);
        }
        catch (std::out_of_range& e)
        {
            std::cout << "Threads number is out of range " << argv[1] << ", " << e.what() << std::endl;
            usage(argv[0]);
            exit(1);
        }

        std::cout << "Creating " << num << " threads." << std::endl;
        std::thread* threads = new std::thread[num];
        for (int i = 0; i < num; i++)
        {
            threads[i] = std::thread(worker_thread, i * 100);
        }

        do
        {
            std::string r;
            std::cout << "The 'sum' is " << sum << ", is it enough? (Y/n) ";
            std::cin >> r;
            if (r == "Y")
            {
                running.exchange(false);
            }
        }
        while (running);

        for (int i = 0; i < num; i++)
        {
            threads[i].join();
        }

        std::cout << "The 'sum' has reached " << sum << std::endl;

        delete[] threads;
    }
    else
    {
        usage(argv[0]);
        exit(1);
    }

    return 0;
}
