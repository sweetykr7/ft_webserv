if(EXISTS "/Users/sooyokim/42seoul/ft_webserv/tdd/build/iteratorTest[1]_tests.cmake")
  include("/Users/sooyokim/42seoul/ft_webserv/tdd/build/iteratorTest[1]_tests.cmake")
else()
  add_test(iteratorTest_NOT_BUILT iteratorTest_NOT_BUILT)
endif()
