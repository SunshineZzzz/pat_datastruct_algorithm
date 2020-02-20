add_executable(PrintN_for PrintN_for.cc)
add_test(NAME PrintN_for COMMAND PrintN_for)

add_executable(PrintN_rec PrintN_rec.cc)
add_test(NAME PrintN_rec COMMAND PrintN_rec)

add_executable(Multinomial Multinomial.cc)
add_test(NAME Multinomial COMMAND Multinomial)

add_executable(Maximum_subsequence Maximum_subsequence.cc)
add_test(NAME Maximum_subsequence COMMAND Maximum_subsequence)