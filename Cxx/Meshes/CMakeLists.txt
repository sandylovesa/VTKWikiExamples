PROJECT (${WIKI}Meshes)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkRendering vtkHybrid)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()

#
# Build all .cxx files in the directory
FILE(GLOB ALL_FILES *.cxx)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresVersion.cmake)
set(VERSION_MIN "6.0")
Requires_Version(DeformPointSet ${VERSION_MIN} ALL_FILES)

foreach(SOURCE_FILE ${ALL_FILES})
  STRING(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  STRING(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  ADD_EXECUTABLE(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  TARGET_LINK_LIBRARIES(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach(SOURCE_FILE)

if (BUILD_TESTING)
# Testing
SET(KIT Meshes)
SET(NEEDS_ARGS
  ClipDataSetWithPolyData
  FillHoles
  MatrixMathFilter
  OBBDicer
  TableBasedClipDataSetWithPolyData
)
SET(DATA ${WikiExamples_SOURCE_DIR}/Testing/Data)

ADD_TEST(${KIT}-ClipDataSetWithPolyData ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestClipDataSetWithPolyData -E 25)

ADD_TEST(${KIT}-FillHoles ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestFillHoles ${DATA}/Torso.vtp)

ADD_TEST(${KIT}-OBBDicer ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestOBBDicer ${DATA}/Bunny.vtp)

ADD_TEST(${KIT}-MatrixMathFilter ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestMatrixMathFilter ${DATA}/tensors.vtk)

ADD_TEST(${KIT}-TableBasedClipDataSetWithPolyData ${EXECUTABLE_OUTPUT_PATH}/${KIT}CxxTests
  TestTableBasedClipDataSetWithPolyData -E 25)

INCLUDE(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
