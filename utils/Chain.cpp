//
// Created by PC on 10/22/2023.
//

#include "Chain.h"

template <typename... Args>
Chain<Args...>::Chain(Chain<Args...>::ChainCallFunctionType &&callBackFunc,
                      bool isAsync) {
  this->SetCallBackFunction(callBackFunc, isAsync);
}
template <typename... Args> Chain<Args...>::~Chain() {
  delete before;
  delete after;
}
template <typename... Args> void Chain<Args...>::callBefore(Args &&...args) {
  this->callBackFunc(std::forward<Args>(args)...);
  if (this->after != nullptr) {
    this->before->callAfter(std::forward<Args>(args)...);
  }
};
template <typename... Args> void Chain<Args...>::callAfter(Args &&...args) {
  this->callBackFunc(std::forward<Args>(args)...);
  if (this->before != nullptr) {
    this->before->callBefore(std::forward<Args>(args)...);
  }
};

template <typename... Args>
void Chain<Args...>::CreateNewBefore(
    Chain<Args...>::ChainCallFunctionType &&BeforeCallBackFunc, bool isAsync) {
  this->before = new Chain<Args...>(BeforeCallBackFunc, isAsync);
}

template <typename... Args>
void Chain<Args...>::CreateNewAfter(
    Chain<Args...>::ChainCallFunctionType &&afterCallBackFunc, bool isAsync) {
  this->after = new Chain<Args...>(afterCallBackFunc, isAsync);
}

template <typename... Args>
void Chain<Args...>::SetCallBackFunction(
    Chain<Args...>::ChainCallFunctionType &&afterCallBackFunc, bool isAsync) {
  if (isAsync) {
    this->callBackFunc = []<typename... Args>(Args &&...args) {
      runAsyncTask(afterCallBackFunc, std::forward<Args>(args)...);
    }
  } else {
    this->callBackFunc = afterCallBackFunc;
  }
}