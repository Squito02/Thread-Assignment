#include <iostream>
#include <thread>
#include <semaphore.h>
#include <mutex>
#include <condition_variable>
#include <ctime>
#include <cstdlib>


using namespace std;

mutex mtx;
condition_variable cv;
bool ready = false;
const int sleepMax = 3; // used for random sleep
const int sleepMin = 1; // used for random sleep
const int pageMax = 10; // used for random webpage
const int pageMin = 1;  // used for random webpage
int rando;              // Used for random
int IDcounter = 0;
// initialize message queue
queue<requestStructure> msg_queue;

string webPages[10] = {"google.com", "yahoo.com", "youtube.com", 
                        "crunchyroll.com", "amazon.com", "funimation.com", 
                        "walmart.com", "facebook.com", "armorgames.com", 
                        "freewebarcade.com"};

struct requestStructure 
{
    int request_id; 

    string ip_address;

   string page_requested;

};

void listen() 
{
    // sleep for random value 1-3 using sleep_for
    srand(time(0));
    rando = (srand() % (sleepMax - sleepMin + 1)) + sleepMin;
    while(true) 
    {
        sleep_for(rando);
        // generate a request with request_id from a counter shared, ip_address as 
        // an empty string and page_request as a random web page name from the array
        // webPages defined above; then save the request in msg_queue.

        requestStructure requestFromClient;
        requestFromClient.request_id = IDcounter;
        IDcounter++;
        requestFromClient.ip_address = "";
        rando = (srand() % (pageMax - pageMin + 1)) + pageMin;
        requestFromClient.page_requested = webPages[rando];
        msg_queue.push(requestFromClient);
        
        // notify one thread to consume it
        cv.notify_one();
    }
}

void do_request(int thread_id) 
{
    while (true)
    {
        // if the msg_queue is empty, wait using conditional variable
        if (msg_queue == null)
        {
            unique_lock<mutex> lck(mtx);
            cv.wait(lck);
        }
        else // get request from message queue
        {
            requestStructure requested = msg_queue.front();
            cout<< "thread " << thread_id << "completed request " << 
                    requested.request_id << "requesting webpage " <<
                    requested.page_requested << endl;
        }
    }
}

int main() 
{
    int n;
    cout << "How many threads should be created?" << endl;
    cin >> n;
    // create producer and consumer threads
    thread listenThread(listen);
    thread requestThread[n];
    for (int i = 0; i < n; i++)
    {
        requestThread[i] = thread(do_request)
    }

    // wait for threads to finish (should never happen)
    listenThread.join();

    for (int i = 0; i < n; i++)
    {
        requestThread[i].join();
    }
    
    return 0;
}