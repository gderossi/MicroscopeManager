#pragma once
#include "MMThread.h"
#include <windows.h>
#include "ImageManager.h"
#include <condition_variable>
#include <mutex>
#include "ProducerThread.h"

class WriterThread :
    public MMThread
{
public:
    WriterThread(std::string filename, unsigned int bufsize, int id, ProducerThread* producer, ImageManager* img);
    virtual ~WriterThread();
    void WaitForThread();
    std::atomic_bool ready;

private:
    void WriteLoop();

    int id_;
    std::string filename_;
    std::thread thd_;
    unsigned char* buf_;
    int bufsize_;
    ImageManager* img_;
    ProducerThread* producer_;
};

