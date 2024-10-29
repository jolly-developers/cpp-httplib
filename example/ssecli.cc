//
//  ssecli.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <httplib.h>
#include <iostream>

using namespace std;

int main(void) {
  vector<thread> threads;
  map<string, size_t> counts;

  size_t thread_count = 20;

  for (size_t i = 0; i < thread_count; i++) {
    threads.push_back(thread{[&] {
      httplib::Client("http://localhost:1234")
          .Get("/event1", [&](const char *data, size_t data_length) {
            auto d = string(data, data_length - 2);
            counts[d]++;
            if (counts[d] == thread_count) {
              cout << d << endl;
            }
            return true;
          });
    }});
  }

  for (auto &t : threads) {
    t.join();
  }

  return 0;
}
