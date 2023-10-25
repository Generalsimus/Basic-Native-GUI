////
//// Created by PC on 10/22/2023.
////
//
#include "Chain.h"
#include "./invokeFunction.cpp"

//
//template<typename... Args>
//Chain<Args...>::Chain() {}
//
//////////////////////
//template<typename... Args>
//Chain<Args...>::Chain(ChainCallFunctionType &&callBackFunc, bool isAsync) {
//    this->SetCallBackFunction(callBackFunc, isAsync);
//}
//
//////////////////////
//template<typename... Args>
//Chain<Args...>::~Chain() {
//    delete before;
//    delete after;
//}
//
//////////////////////
//
//template<typename... Args>
//void Chain<Args...>::callBefore(Args &&... args) {
//    // Use std::forward to forward the arguments
//    // If you need to maintain the reference type, you can use decltype(auto)
////    processArgs(std::forward<ChainArgs>(args)...);
//
////    this->callBackFunc(std::forward<Args>(args)...);
////    if (this->after != nullptr) {
////        this->before->callAfter(std::forward<Args>(args)...);
////    }
//}
//
//////////////////////
//template<typename... Args>
//void Chain<Args...>::callAfter(Args &&... args) {
////    this->callBackFunc(std::forward<Args>(args)...);
////    if (this->before != nullptr) {
////        this->before->callBefore(std::forward<Args>(args)...);
////    }
//};
//////////////////////
//
//template<typename... Args>
//Chain<Args...> *Chain<Args...>::SetCallBackFunction(ChainCallFunctionType &&afterCallBackFunc,
//                                                    bool isAsync) {
//
//    this->SetCallBackFunction(afterCallBackFunc, isAsync);
//    return this;
//}
//////////////////////
//template<typename... Args>
//void Chain<Args...>::remove() {
//
//}
//////////////////////
//template<typename... Args>
//Chain<Args...> *Chain<Args...>::CreateNewAfter(ChainCallFunctionType &&afterCallBackFunc, bool isAsync) {
////    return nullptr;
//    return this;
//}
//////////////////////
//
////template<typename... Args>
////Chain<Args...> *Chain<Args...>::SetCallBackFunction(ChainCallFunctionType &afterCallBackFunc,
////                                                    bool isAsync) {
////    if (isAsync) {
////        this->callBackFunc = []<typename... Args>(Args &&...args) {
////            runAsyncTask(afterCallBackFunc, std::forward<Args>(args)...);
////        };
////    } else {
////        this->callBackFunc = afterCallBackFunc;
////    }
////
////    return this;
////}
//////////////////////
//
//
////template<typename... Args>
////Chain<Args...>* Chain<Args...>::CreateNewBefore(ChainCallFunctionType &&BeforeCallBackFunc,
////                                     bool isAsync) {
////    this->before = new Chain<Args...>(BeforeCallBackFunc, isAsync);
////    return this->before;
////}
////////////////////////
////template<typename... Args>
////Chain<Args...> *Chain<Args...>::setAfter(Chain<Args...> newAfterPoint) {
////    this->after = newAfterPoint;
////    return newAfterPoint;
////}
//
////////////////////////
////template<typename... Args>
////Chain<Args...> *Chain<Args...>::setBefore(Chain<Args...> newBeforePoint) {
////    this->before = newBeforePoint;
////    return newBeforePoint;
////}
//////////////////////
template<typename... Args>
void Chain<Args...>::remove() {
    if (this->before != nullptr && this->after != nullptr) {
        this->before->after = this->after;
        this->after->before = this->before;
    };
    this->before = nullptr;
    this->after = nullptr;
    this->callChainFunction = [](Args &&... args) {};
}

//////////////////////
template<typename... Args>
template<class RemoveFunction>
void Chain<Args...>::invokeRemoveFunction(RemoveFunction &&removeCallBackFunc) {

    auto self = this;
    invokeFunction(removeCallBackFunc, [self]() {
        self->remove();
    });
}
//////////////////////
