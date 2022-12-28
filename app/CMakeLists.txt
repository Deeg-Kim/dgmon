add_executable(DGMon main.cpp)
target_link_libraries(DGMon PRIVATE DGMonLibrary sfml-graphics)
target_compile_features(DGMon PRIVATE cxx_std_17)

install(TARGETS DGMon)
