

template<typename MainFunc, typename InvokeFunc>
void invokeFunction(MainFunc &mainFunction, InvokeFunc &&addFunction) {
    MainFunc currentMainFunction = std::move(mainFunction);
    mainFunction = [currentMainFunction, addFunction]<typename... Args>(Args &&...args) {

        addFunction(std::forward<Args>(args)...);
        return currentMainFunction(std::forward<Args>(args)...);
    };
}

template<typename Func>
void invokeFunctionArgAndSameReturnValue(Func &&mainFunction, Func &&addFunction) {
    Func currentMainFunction = std::move(mainFunction);
    mainFunction = [currentMainFunction, addFunction]<typename Arg>(Arg &&arg) {
        addFunction(currentMainFunction(std::forward<Arg>(arg)));
    };
}