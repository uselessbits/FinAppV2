cmake_minimum_required(VERSION 3.26)
project(FinAppV2 C)

set(CMAKE_C_STANDARD 11)

add_executable(FinAppV2 main.c
        account_actions.c
        users.h
        main.h
        users.c
        accounts.h
        transactions.h
        transactions.c)
