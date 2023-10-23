//
// Created by PC on 10/22/2023.
//

#ifndef CUDA_NEU_CHAIN_H
#define CUDA_NEU_CHAIN_H

template<typename... Args>
class Chain {
public:
    using ChainCallFunctionType = std::function<void(Args &&...)>;

    Chain() {};

    explicit Chain(ChainCallFunctionType &&callBackFunc, bool isAsync = false) {

    };

    ~Chain() {

    };

    void callAfter(Args &&... args) {

    };

    void callBefore(Args &&... args) {

    };


    Chain<Args...> *addNewAfter(ChainCallFunctionType &&afterCallBackFunc, bool isAsync = false) {
        auto newAfterChain = new Chain<Args...>(std::forward<ChainCallFunctionType>(afterCallBackFunc),
                                                std::forward<bool>(isAsync));

        return newAfterChain;
    };

    Chain<Args...> *addNewBefore(ChainCallFunctionType &&afterCallBackFunc, bool isAsync = false) {
        auto newBeforeChain = new Chain<Args...>(std::forward<ChainCallFunctionType>(afterCallBackFunc),
                                                 std::forward<bool>(isAsync));

        return newBeforeChain;
    };

//    Chain<Args...> *SetCallBackFunction(ChainCallFunctionType &&afterCallBackFunc,
//                                        bool isAsync = false);
//
//
//
//
//    Chain<Args...> *setAfter(Chain<Args...> &&newAfterPoint);
//
//    Chain<Args...> *setBefore(Chain<Args...> &&newBeforePoint);
//
//
//    Chain<Args...> *SetCallBackFunction(ChainCallFunctionType &&afterCallBackFunc,
//                                        bool isAsync = false);
//
//
//    Chain<Args...> *CreateNewAfter(ChainCallFunctionType &&afterCallBackFunc,
//                                   bool isAsync = false);
//
////    Chain<Args...> *CreateNewAfter(ChainCallFunctionType &afterCallBackFunc,
////                                   bool isAsync = false);
//
////    Chain<Args...> *CreateNewBefore(ChainCallFunctionType &&&BeforeCallBackFunc,
////                                    bool isAsync = false);
//
//    Chain<Args...> *CreateNewBefore(ChainCallFunctionType &&BeforeCallBackFunc,
//                                    bool isAsync = false);
//
////    template<class RemoveFunction>
////    void invokeRemoveFunction(RemoveFunction &&removeCallBackFunc);

//    void remove();

private:
    ChainCallFunctionType callBackFunc = nullptr;
    Chain<Args...> *before = nullptr;
    Chain<Args...> *after = nullptr;

    Chain<Args...> *first = this;
    Chain<Args...> *last = this;
};


#endif // CUDA_NEU_CHAIN_H
