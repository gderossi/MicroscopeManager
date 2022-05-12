#pragma once
#include "MMThread.h"
#include <mutex>
#include <condition_variable>
#include <vector>
#include "MicroscopeManager.h"

class WriterThread;

class ProducerThread :
    public MMThread
{
public:
    ProducerThread(int bufsize, MicroscopeManager* mm);
    virtual ~ProducerThread();
    void StartThread();
    void WaitForThread();
    void AddWriterThread(WriterThread* writer);

    std::mutex pMutex;
    std::condition_variable pCV;
    int producerIndex;
    std::vector<unsigned char*> imgBuffers;
    std::vector<bool> bufReadys;
    MicroscopeManager* mm_;
    std::atomic_bool masked;
    int bufSize;
    int lastWriterID;

private:
    virtual void ProducerLoop();

    std::thread thd_;
    std::vector<WriterThread*> writerThreads_;
};

