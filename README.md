## Timer:

A super basic header-only cpp library that has a single Timer class, a background-thread timer that can repeat or run as a one-shot.



## Usage:
  
- include the header
  
`#include "timer.hpp"`
  
- use the timer

```cpp
#include "timer.hpp"
#include <iostream>

int main() {
  // arg0 : (int) -> milliseconds duration before calling-back
  // arg1 : (function<void(const int&)>) -> the callback that is invoked on timer finish. the integer passed back is the elapsed ms since start time.
  // arg2 : (bool = false) -> default false, this boolean indicates whether the timer should repeat or fire once. true for recurring/repeating, false for once.
  Timer timer(1000, [](elapsed){
    std::cout << "elasped: " << elapsed << std::endl;
  }, true);
  
  // begin the timer
  timer.start();
  
  // for demonstration, loop until the user enters a char.
  // the timer should print the elapsed duration at the specified interval until this exits.
  char c;
  std::cin >> c;
  
  // in this case, this is unneccesary, but this will stop the timer.
  timer.stop();
  
  // this would reset the timer, and begin again.
  timer.start();
  
  std::cin >> c;
}

```
  
  
  