if(EXISTS "C:/Users/7777m/OneDrive/Рабочий стол/labwork2/labwork2-olyamironova/cmake-build-debug/tests/number_tests[1]_tests.cmake")
  include("C:/Users/7777m/OneDrive/Рабочий стол/labwork2/labwork2-olyamironova/cmake-build-debug/tests/number_tests[1]_tests.cmake")
else()
  add_test(number_tests_NOT_BUILT number_tests_NOT_BUILT)
endif()
