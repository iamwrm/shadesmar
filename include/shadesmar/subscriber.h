//
// Created by squadrick on 8/3/19.
//

#ifndef SHADERMAR_SUBSCRIBER_H
#define SHADERMAR_SUBSCRIBER_H

#include <stdint.h>

#include <cstring>
#include <functional>
#include <memory>
#include <string>

#include <iostream>

#include <shadesmar/memory.h>

namespace shm {
template<typename T>
class Subscriber {
 public:
  Subscriber(std::string topic_name, std::function<void(std::shared_ptr<T>)> callback):
      topic_name_(topic_name), spinning_(false),
      msg_(reinterpret_cast<T*>(malloc(sizeof(T)))){
    callback_ = std::move(callback);
    mem_ = std::make_shared<Memory>(topic_name_, sizeof(T), false);
  }

  void spin(float rate=0.0f) {
    // if rate is 0.0, spin continuously
    spinning_ = true;

    // create a thread
  }

  void spinOnce() {
    // no threading
    mem_->read(msg_.get(), true);
    callback_(msg_);
  }

  void shutdown() {
    // stop spinning
    if (!spinning_)
      return;

    spinning_ = false;
  }


 private:
  std::string topic_name_;

  std::shared_ptr<Memory> mem_;
  std::function<void(std::shared_ptr<T>)> callback_;

  bool spinning_;

  std::shared_ptr<T> msg_;


};
}
#endif //SHADERMAR_SUBSCRIBER_H