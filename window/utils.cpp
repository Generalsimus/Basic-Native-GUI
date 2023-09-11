#include <iostream>
#include <iostream>
#include <vector>
#include <functional>
#include <string>


template<typename CallBeckFunction>
void CreateFunctionChain(CallBeckFunction *chainMemoryAddr, CallBeckFunction addChainCallBack) {
    printf("CreateFunctionChain()\n");

    printf("CreateFunctionChain 1\n");
    CallBeckFunction currentChainFunc = *chainMemoryAddr;
    printf("CreateFunctionChain 2\n");

    auto newCHainCallBack = [&currentChainFunc, &addChainCallBack]<typename... ARGS>(ARGS &&... args) {
        currentChainFunc(std::forward<ARGS>(args)...);
        addChainCallBack(std::forward<ARGS>(args)...);
    };
    printf("CreateFunctionChain 3\n");

    *chainMemoryAddr = newCHainCallBack;

    printf("CreateFunctionChain 4\n");
};
