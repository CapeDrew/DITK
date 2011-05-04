# Create source code, compile and link a test driver
# Two variables must be defined before including this file.
#   KIT should define a unique name for the test driver.
#   KitTests should contain a list of test file names without a .cxx suffix.
# Arguments - Input
#   KIT - the name of the test directory
#   KIT_LIBS - a list of libraries needed to link the test driver
#   KitTests - a list of tests to be included in the test driver

macro(CreateTestDriver KIT KIT_LIBS KitTests)
  set(CMAKE_TESTDRIVER_BEFORE_TESTMAIN "#include \"itkTestDriverBeforeTest.inc\"")
  set(CMAKE_TESTDRIVER_AFTER_TESTMAIN "#include \"itkTestDriverAfterTest.inc\"")
  create_test_sourcelist(Tests ${KIT}TestDriver.cxx
    ${KitTests}
    EXTRA_INCLUDE itkTestDriverIncludeRequiredIOFactories.h
    FUNCTION  ProcessArgumentsAndRegisterRequiredFactories
    )
  add_executable(${KIT}TestDriver ${KIT}TestDriver.cxx ${Tests})
  target_link_libraries(${KIT}TestDriver ${KIT_LIBS} ${ITK-TestKernel_LIBRARIES})
  itk_module_target_label(${KIT}TestDriver)
endmacro(CreateTestDriver)


macro(CreateTestDriver_SupportBuildInIOFactories KIT KIT_LIBS KitTests)
   set(CMAKE_TESTDRIVER_BEFORE_TESTMAIN  "#include \"itkTestDriverBeforeTest.inc\"")
   set(CMAKE_TESTDRIVER_AFTER_TESTMAIN "#include \"itkTestDriverAfterTest.inc\"")
   create_test_sourcelist(Tests ${KIT}TestDriver.cxx
     ${KitTests}
     EXTRA_INCLUDE  itkTestDriverIncludeBuiltInIOFactories.h
     FUNCTION  ProcessArgumentsAndRegisterBuiltInFactories
     )
   add_executable(${KIT}TestDriver ${KIT}TestDriver.cxx ${Tests})
   target_link_libraries(${KIT}TestDriver ${KIT_LIBS} ${ITK-TestKernel_LIBRARIES})
   itk_module_target_label(${KIT}TestDriver)
endmacro(CreateTestDriver_SupportBuildInIOFactories)
