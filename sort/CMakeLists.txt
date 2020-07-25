add_executable(BubbleSort BubbleSort.cc)
add_test(NAME BubbleSort COMMAND BubbleSort)

add_executable(InsertSort InsertSort.cc)
add_test(NAME InsertSort COMMAND InsertSort)

add_executable(ShellSort ShellSort.cc)
add_test(NAME ShellSort COMMAND ShellSort)

add_executable(SelectSort SelectSort.cc)
add_test(NAME SelectSort COMMAND SelectSort)