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
    WriterThread(ProducerThread* producer, ImageManager* img);
    virtual ~WriterThread();
    void WaitForThread();
    std::atomic_bool ready;

private:
    void WriteLoop();

    int id_;
    std::thread thd_;
    unsigned char* buf_;
    int bufSize_;
    ImageManager* img_;
    ProducerThread* producer_;
};

