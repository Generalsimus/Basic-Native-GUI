//
// Created by PC on 10/22/2023.
//

#ifndef CUDA_NEU_CHAIN_H
#define CUDA_NEU_CHAIN_H

template <typename... Args> class Chain {
private:
  using ChainCallFunctionType = std::function<Args...>;
  ChainCallFunctionType callBackFunc;
  Chain<Args...> *before = nullptr;
  Chain<Args...> *after = nullptr;

  //  using ChainCallFunctionType = std::function<Args...>;
  //  ChainCallFunctionType callBackFunc;
  //
  //  Chain<Args...> *before = nullptr;
  //  Chain<Args...> *after = nullptr;

public:
  Chain(ChainCallFunctionType &&callBackFunc, bool isAsync = false);
  ~Chain();

  void callAfter(Args &&...args);

  void callBefore(Args &&...args);

  void SetCallBackFunction(ChainCallFunctionType &&afterCallBackFunc,
                           bool isAsync = false);

  void setAfter(Event<Args...> newAfterPoint);

  void CreateNewAfter(ChainCallFunctionType &&afterCallBackFunc,
                      bool isAsync = false);

  void CreateNewAfter(ChainCallFunctionType &&afterCallBackFunc,
                      bool isAsync = false);

  void CreateNewBefore(ChainCallFunctionType &&BeforeCallBackFunc,
                         bool isAsync = false);
  //  explicit Chain(ChainCallFunctionType &&callBackFunc, bool isAsync = false)
  //  {
  //    this->SetCallBackFunction(callBackFunc, isAsync);
  //  }
  //  ~Chain() {
  //    delete before;
  //    delete after;
  //  }
  //  void callAfter(Args &&...args) {
  //    this->callBackFunc(std::forward<Args>(args)...);
  //    if (this->after != nullptr) {
  //      this->before->callAfter(std::forward<Args>(args)...);
  //    }
  //  };
  //  void callBefore(Args &&...args) {
  //    this->callBackFunc(std::forward<Args>(args)...);
  //    if (this->before != nullptr) {
  //      this->before->callBefore(std::forward<Args>(args)...);
  //    }
  //  };
  //  void SetCallBackFunction(ChainCallFunctionType &&afterCallBackFunc,
  //                           bool isAsync = false) {
  //    if (isAsync) {
  //      this->callBackFunc = []<typename... Args>(Args &&...args) {
  //        runAsyncTask(afterCallBackFunc, std::forward<Args>(args)...);
  //      }
  //    } else {
  //      this->callBackFunc = afterCallBackFunc;
  //    }
  //  }
  //  void setAfter(Event<Args...> newAfterPoint) { this->after = newAfterPoint;
  //  } void setBefore(Event<Args...> newBeforePoint) {
  //    this->before = newBeforePoint;
  //  }
  //  void CreateNewAfter(ChainCallFunctionType &&afterCallBackFunc,
  //                      bool isAsync = false) {
  //    this->after = new Chain<Args...>(afterCallBackFunc, isAsync);
  //  }
  //  void CreateNewBefore(ChainCallFunctionType &&BeforeCallBackFunc,
  //                       bool isAsync = false) {
  //    this->before = new Chain<Args...>(BeforeCallBackFunc, isAsync);
  //  }
};

#endif // CUDA_NEU_CHAIN_H
