add_test([=[HelloTest.BasicAssertions]=]  /Users/sooyokim/42seoul/ft_webserv/tdd/build/aa [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY /Users/sooyokim/42seoul/ft_webserv/tdd/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  aa_TESTS HelloTest.BasicAssertions)
