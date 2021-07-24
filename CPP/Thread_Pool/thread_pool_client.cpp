#include <future>
#include <memory>
#include <chrono>
#include "thread_pool.h"

using PkgTask = std::packaged_task<int(int,int)>;
using PkgTaskRef = std::shared_ptr<PkgTask>;
using ThreadPoolRef = std::shared_ptr<ThreadPool<PkgTaskRef>>;

void ProcessTaskRequest (PkgTaskRef task) {
    (*task)(10, 10);
}

int main()
{
    ThreadPoolRef thread_pool = std::make_shared<ThreadPool<PkgTaskRef>>();
    thread_pool->InItThreadPool(4, ProcessTaskRequest);
    for (int i = 0;  i < 10; i++) {
        PkgTaskRef task = std::make_shared<PkgTask>([i](int a, int b) -> int {
            return (i * (a + b));
        });
        auto future = task->get_future();
        thread_pool->EnqueueItem(task);
        std::cout << "Val = " << future.get() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    thread_pool->StopThreadPool();
    return 0;
}
