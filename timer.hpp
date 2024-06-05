#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

struct Timer {
  std::chrono::milliseconds elapsed = std::chrono::milliseconds(0);
  
  Timer(const int duration_ms, std::function<void(const int &)> callback,
        const bool recurring = false)
      : callback(callback), recurring(recurring) {
    this->duration_ms = std::chrono::milliseconds(duration_ms);
    this->cancelled = false;
  }
  
  void start() {
    this->elapsed = std::chrono::milliseconds(0);
    if (thread != nullptr) {
      thread->join();
      delete thread;
    }
    cancelled = false;
    thread = new std::thread(&Timer::m_run, this);
  }
  void stop() {
    if (thread == nullptr) {
      return;
    }
    cancelled = true;
  }
  ~Timer() {
    stop();
    if (thread->joinable()) {
      thread->join();
    }
    delete thread;
  }
  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;
  Timer(Timer&&) = delete;
  Timer& operator=(Timer&&) = delete;
private:
  void m_run() {
    do {
      std::this_thread::sleep_for(duration_ms);
      if (cancelled) {
        break;
      }
      elapsed += duration_ms;
      callback(elapsed.count());
    } while (recurring);
  }

  std::atomic<bool> cancelled = false;
  bool recurring;
  std::function<void(const int &)> callback;
  std::chrono::milliseconds duration_ms;
  std::thread *thread = nullptr;
};