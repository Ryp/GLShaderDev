cmake_minimum_required(VERSION 2.8.2)
project(QtPropertyBrowser CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
include(${QT_USE_FILE})

set(KIT_SRCS
  qtbuttonpropertybrowser.cpp
  qtbuttonpropertybrowser.h
  qteditorfactory.cpp
  qteditorfactory.h
  qtgroupboxpropertybrowser.cpp
  qtgroupboxpropertybrowser.h
  qtpropertybrowser.cpp
  qtpropertybrowser.h
  qtpropertybrowserutils.cpp
  qtpropertybrowserutils_p.h
  qtpropertymanager.cpp
  qtpropertymanager.h
  qttreepropertybrowser.cpp
  qttreepropertybrowser.h
  qtvariantproperty.cpp
  qtvariantproperty.h
  )

set(KIT_MOC_SRCS
  qtpropertybrowserutils_p.h
  )

set(KIT_UI_FORMS
  )

set(KIT_resources
  )

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  )

qt4_wrap_ui(KIT_UI_CPP ${KIT_UI_FORMS})
qt4_wrap_cpp(KIT_MOC_CPP ${KIT_MOC_SRCS})
qt4_add_resources(KIT_QRC_SRCS ${KIT_resources})

set(libname ${PROJECT_NAME})
add_library(${libname} SHARED
  ${KIT_SRCS}
  ${KIT_UI_CPP}
  ${KIT_MOC_CPP}
  ${KIT_QRC_SRCS}
  )

set(${PROJECT_NAME}_LINK_LIBRARIES ${QT_LIBRARIES})
target_link_libraries(
  ${libname}
  ${${PROJECT_NAME}_LINK_LIBRARIES}
  )

# List of header that should go though moc
set(KIT_HEADERS_MOC_SRCS
  qtbuttonpropertybrowser.h
  qteditorfactory.h
  qtgroupboxpropertybrowser.h
  qtpropertybrowser.h
  qtpropertybrowserutils_p.h
  qtpropertymanager.h
  qttreepropertybrowser.h
  qtvariantproperty.h
  )

set(KIT_MOC_CPP)
foreach(file ${KIT_HEADERS_MOC_SRCS})
  get_filename_component(filename_we ${file} NAME_WE)
  set(output_file moc_${filename_we}.cpp)
  qt4_generate_moc(${file} ${output_file})
  list(APPEND KIT_MOC_CPP ${output_file})
endforeach()

# List of cpp files that should go though moc
set(KIT_CPP_MOC_SRCS
  qteditorfactory.cpp
  qtpropertymanager.cpp
  qttreepropertybrowser.cpp
  )

foreach(file ${KIT_CPP_MOC_SRCS})
  get_filename_component(filename_we ${file} NAME_WE)
  set(output_file ${filename_we}.moc)
  qt4_generate_moc(${file} ${output_file})
  list(APPEND KIT_MOC_CPP ${output_file})
endforeach()

add_custom_target(${libname}GenerateMoc
  DEPENDS ${KIT_MOC_CPP}
  )
add_dependencies(${libname} ${libname}GenerateMoc)
