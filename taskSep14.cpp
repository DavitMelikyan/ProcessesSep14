#include <pthread.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define MAX_THREADS 5

struct ThreadData {
    int thread_id;
    int line_number;
    std::string line_data;
    int word_count;
};

ThreadData maxLine;
pthread_mutex_t mutex;

void* process_line(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    std::stringstream ss(data->line_data);
    std::string word;
    int count = 0;
    while (ss >> word) {
        count++;
    }
    data->word_count = count;
    pthread_mutex_lock(&mutex);
    if (count > maxLine.word_count) {
        maxLine = *data;
    }
    pthread_mutex_unlock(&mutex);

    return nullptr;
}

int main() {
    std::ifstream in("taskSep14.txt");
    if (!in) {
        std::cout << "Error while opening file" << std::endl;
        return 1;
    }

    pthread_mutex_init(&mutex, nullptr);
    std::string line;
    int ln = 1;
    int tid = 1;

    std::vector<pthread_t> ths;
    std::vector<ThreadData*> thdata;

    while (std::getline(in, line)) {
        ThreadData* thd = new ThreadData{tid++, ln++, line, 0};
        pthread_t th;
        pthread_create(&th, nullptr, process_line, thd);
        ths.push_back(th);
        thdata.push_back(thd);
        if (ths.size() >= MAX_THREADS) {
            for (size_t i = 0; i < ths.size(); i++) {
                pthread_join(ths[i], nullptr);
            }
            ths.clear();
        }
    }

    for (size_t i = 0; i < ths.size(); i++) {
        pthread_join(ths[i], nullptr);
    }

    for (auto th : thdata) { 
        delete th;
    }
    pthread_mutex_destroy(&mutex);

    std::cout << "Max word: " << maxLine.word_count << std::endl << "Thread ID: " << maxLine.thread_id << std::endl << "Line: " << maxLine.line_number << std::endl;
}