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

        this->SetCallBackFunction(std::forward<ChainCallFunctionType>(callBackFunc), std::forward<bool>(isAsync));
    };

    ~Chain() {

    };

    void callAfter(Args &&... args) {
        this->callChainFunction(std::forward<Args>(args)...);
        if (this->after != nullptr) {
            this->after->callAfter(std::forward<Args>(args)...);
        }
    };

    void callBefore(Args &&... args) {
//        printf("CAL BEFORE\n");
        this->callChainFunction(std::forward<Args>(args)...);

        if (this->before != nullptr) {
            this->before->callBefore(std::forward<Args>(args)...);
        }
    };


    Chain<Args...> *addNewAfter(ChainCallFunctionType &&afterCallBackFunc, bool isAsync = false) {
        auto *newAfterChain = new Chain<Args...>(std::forward<ChainCallFunctionType>(afterCallBackFunc),
                                                std::forward<bool>(isAsync));

        newAfterChain->after = this->after;
        newAfterChain->before = this;
        this->after = newAfterChain;
        return newAfterChain;
    };

    Chain<Args...> *addNewBefore(ChainCallFunctionType &&afterCallBackFunc, bool isAsync = false) {
        auto *newBeforeChain = new Chain<Args...>(std::forward<ChainCallFunctionType>(afterCallBackFunc),
                                                 std::forward<bool>(isAsync));

        newBeforeChain->before = this->before;
        newBeforeChain->addNewAfter = this;
        this->before = newBeforeChain;

        return newBeforeChain;
    };

    Chain<Args...> *SetCallBackFunction(ChainCallFunctionType &&callBackFunc, bool isAsync = false) {
        if (isAsync) {
            this->callChainFunction = [callBackFunc]<typename... AllArgs>(AllArgs &&... args) {
                runAsyncTask(callBackFunc, std::forward<AllArgs>(args)...);
            };
        } else {
            this->callChainFunction = callBackFunc;
        }
        return this;
    };

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
    template<class RemoveFunction>
    void invokeRemoveFunction(RemoveFunction &&removeCallBackFunc);

    void remove();

private:
    ChainCallFunctionType callChainFunction = [](Args &&... args) {};
    Chain<Args...> *before = nullptr;
    Chain<Args...> *after = nullptr;
};


#endif // CUDA_NEU_CHAIN_H
