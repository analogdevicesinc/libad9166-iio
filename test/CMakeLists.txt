add_executable(CalibrateTest ad9166_calibrate.c)
set_target_properties(CalibrateTest PROPERTIES
	C_STANDARD 11
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
)
target_link_libraries(CalibrateTest LINK_PRIVATE ${LIBIIO_LIBRARIES} ad9166)
add_test(NAME CalibrateTest
         COMMAND CalibrateTest
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
