#include "dlist.h"
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

// basic struct
struct Call {
  int timestamp;
  string name;
  string status;
  int duration;
};

void print_call(const Call &call) {
  cout << "Call from " << call.name << " a " << call.status << " member"
       << endl;
}

void print_answer_call(const int current_time) {
  cout << "Starting tick #" << current_time << endl;
}

void add_call(const Call &call, Dlist<Call> &platinumQueue,
              Dlist<Call> &goldQueue, Dlist<Call> &silverQueue,
              Dlist<Call> &regularQueue) {
  if (call.status == "platinum") {
    platinumQueue.insertBack(new Call(call));
  } else if (call.status == "gold") {
    goldQueue.insertBack(new Call(call));
  } else if (call.status == "silver") {
    silverQueue.insertBack(new Call(call));
  } else if (call.status == "regular") {
    regularQueue.insertBack(new Call(call));
  }
}

Call *process_call(Dlist<Call> &platinumQueue, Dlist<Call> &goldQueue,
                   Dlist<Call> &silverQueue, Dlist<Call> &regularQueue) {
  if (!platinumQueue.isEmpty()) {
    return platinumQueue.removeFront();
  }
  if (!goldQueue.isEmpty()) {
    return goldQueue.removeFront();
  }
  if (!silverQueue.isEmpty()) {
    return silverQueue.removeFront();
  }
  if (!regularQueue.isEmpty()) {
    return regularQueue.removeFront();
  }
  return nullptr;
}

int main() {
  // record how many calls should be simulated
  int numCalls;
  cin >> numCalls;

  // four queues for different status
  Dlist<Call> platinum_queue, gold_queue, silver_queue, regular_queue;

  // record all calls
  vector<Call> callList;

  // read call information from cin
  for (int i = 0; i < numCalls; ++i) {
    int timestamp, duration;
    string name, status;
    cin >> timestamp >> name >> status >> duration;
    callList.push_back({timestamp, name, status, duration});
  }

  // init agent
  int current_time = 0;
  int busyUntil = 0;
  Call *current_call = nullptr;
  size_t eventIndex = 0;

  // **打印初始 tick 0**
  print_answer_call(current_time);

  while (eventIndex < callList.size() || !platinum_queue.isEmpty() ||
         !gold_queue.isEmpty() || !silver_queue.isEmpty() ||
         !regular_queue.isEmpty() || current_call) {
    // finish previous call
    while (eventIndex < callList.size() &&
           callList[eventIndex].timestamp == current_time) {
      // process new call
      const Call &newCall = callList[eventIndex];
      print_call(newCall);
      add_call(newCall, platinum_queue, gold_queue, silver_queue,
               regular_queue);
      ++eventIndex;
    }

    // when agent is free
    if (current_call != nullptr && current_time >= busyUntil) {
      delete current_call;
      current_call = nullptr;
    }

    // when agent need to work
    if (current_call == nullptr) {
      current_call =
          process_call(platinum_queue, gold_queue, silver_queue, regular_queue);
      if (current_call != nullptr) {
        cout << "Answering call from " << current_call->name << endl;
        busyUntil = current_time + current_call->duration;
      }
    }

    // print new tick
    ++current_time;
    if (eventIndex < callList.size() || !platinum_queue.isEmpty() ||
        !gold_queue.isEmpty() || !silver_queue.isEmpty() ||
        !regular_queue.isEmpty() || current_call) {
      print_answer_call(current_time);
    }
  }

  return 0;
}
