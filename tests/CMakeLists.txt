add_executable(test_hash_table test_hash_table.c)

target_link_libraries(test_hash_table
    PRIVATE kutiles
)

add_test(NAME hash_table_tests COMMAND test_hash_table)
