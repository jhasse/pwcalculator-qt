cmake_minimum_required(VERSION 3.8)

set(CMAKE_AUTOMOC ON)

project(pwcalculator LANGUAGES CXX)

if(NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fdiagnostics-color")
endif()

if(ANDROID)
	set(CMAKE_FIND_ROOT_PATH ${CMAKE_PREFIX_PATH})
endif()
find_package(Qt5 COMPONENTS QuickControls2 REQUIRED)
qt5_add_resources(RESOURCES resources/qml.qrc)

file(GLOB SRC src/*.cpp)

if(ANDROID)
	set(CMAKE_ANDROID_STL_TYPE c++_shared)
	set(ANDROID_BUILD_TOOLS_REVISION "28.0.3")
	find_package(Qt5 COMPONENTS AndroidExtras REQUIRED)

	add_library(pwcalculator SHARED ${SRC} ${RESOURCES})
	target_link_libraries(pwcalculator PRIVATE Qt5::AndroidExtras)

	set(QT_HOST_PREFIX ${_qt5Core_install_prefix})

	set(ANDROID_DEST libs/${CMAKE_ANDROID_ARCH_ABI})
	set(ANDROID_APP_BINARY "${CMAKE_INSTALL_PREFIX}/${ANDROID_DEST}/libpwcalculator.so")
	set(ANDROID_PACKAGE_SRC_DIR "${CMAKE_SOURCE_DIR}/android/package-src-dir")
	install(TARGETS pwcalculator DESTINATION ${ANDROID_DEST})

	configure_file(
		android/android-libbuild-android.so-deployment-settings.in.json
		${PROJECT_BINARY_DIR}/android-libbuild-android.so-deployment-settings.json)
else()
	add_executable(pwcalculator ${SRC} ${RESOURCES})
endif()

target_link_libraries(pwcalculator PRIVATE Qt5::QuickControls2)

if(CMAKE_BUILD_TYPE STREQUAL "Release" OR MSVC)
	set_target_properties(pwcalculator PROPERTIES WIN32_EXECUTABLE 1)
endif()
