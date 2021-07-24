#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

template <typename WorkItem, int max_queue_size=0>
class ThreadPool {

using ProcessWorkerItemCallback = std::function<void(WorkItem item)>;

public :
    void InItThreadPool(int num, ProcessWorkerItemCallback call_back) {
        process_work_item_callback_ = call_back;
        for(int i = 0; i < num; i++) {
            std::shared_ptr<std::thread> worker = nullptr;
            worker = std::make_shared<std::thread>(std::bind(&ThreadPool::ProcessRequest, this));
            worker_list.push_back(worker);
        }
    }

    void ProcessRequest() {
        std::stringstream ss;
        ss << std::this_thread::get_id();
        std::cout << "Thread Started " << ss.str().c_str() << std::endl;
        while(!interrupted()) {
            WorkItem work_item;
            {
                std::unique_lock<std::mutex> lock(mtx_);
                while(!interrupted() && work_item_queue_.empty()) {
                cond_var_.wait(lock, [this]() { return (interrupted() || !work_item_queue_.empty());});
                }
                if(interrupted())
                    break;
                work_item = work_item_queue_.front();
                work_item_queue_.pop();
            }
            std::cout << "Thread Running " << ss.str().c_str() << std::endl;
            process_work_item_callback_(work_item);
        }
        std::cout << "Thread Exited " << ss.str().c_str() << std::endl;
    }

    bool EnqueueItem(WorkItem work_item) {
        if((max_queue_size != 0) && (work_item_queue_.size() < max_queue_size)) {
            return false;
        }
        {
            std::unique_lock<std::mutex> lock(mtx_);
            work_item_queue_.push(work_item);
        }
        cond_var_.notify_one();
        return true;
    }

    bool interrupted() {
        return interrupted_;
    }

    void StopThreadPool() {
        if (!interrupted_.exchange(true)) {
            std::lock_guard<std::mutex> lock(mtx_);
            cond_var_.notify_all();
        }
        std::cout << "interrupted_ = " << interrupted_ << std::endl;
        for (auto & worker : worker_list) {
            if (worker->joinable()) {
                worker->join();
            }
        }
        std::queue<WorkItem> empty_queue;
        std::lock_guard<std::mutex> lock(mtx_);
        work_item_queue_.swap(empty_queue);
    }

private :
    std::queue<WorkItem> work_item_queue_;
    std::mutex mtx_;
    std::condition_variable cond_var_;
    std::vector<std::shared_ptr<std::thread>> worker_list;
    ProcessWorkerItemCallback process_work_item_callback_;
    std::atomic<bool> interrupted_{false};
};
