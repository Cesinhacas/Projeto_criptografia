project(criptografia C CXX)

add_executable(m_bench m_bench.cpp)
target_link_libraries(m_bench benchmark gmp)

add_executable(mep_bench mep_bench.cpp)
target_link_libraries(mep_bench benchmark gmp)

add_executable(mnp_bench mnp_bench.cpp)
target_link_libraries(mnp_bench benchmark gmp)

add_executable(main main.c)
target_link_libraries(main benchmark gmp)

add_executable(main_exp_pow main.c)
target_link_libraries(main_exp_pow benchmark gmp)