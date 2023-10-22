

template <typename Func>
void invokeFunction(Func &&mainFunction, Func &&addFunction) {
  Func currentMainFunction = std::move(mainFunction);
  mainFunction = [currentMainFunction,
                  addFunction]<typename... Args>(Args &&...args) {
    currentMainFunction(std::forward<Args>(args)...);
    addFunction(std::forward<Args>(args)...);
  };
}

template <typename Func>
void invokeFunctionArgAndSameReturnValue(Func &&mainFunction, Func &&addFunction) {
  Func currentMainFunction = std::move(mainFunction);
  mainFunction = [currentMainFunction, addFunction]<typename Arg>(Arg &&arg) {
    addFunction(currentMainFunction(std::forward<Arg>(arg)));
  };
}