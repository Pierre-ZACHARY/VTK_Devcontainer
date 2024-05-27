find_package(VTK COMPONENTS
        CommonColor
        CommonCore
        FiltersSources
        InteractionStyle
        RenderingContextOpenGL2
        RenderingCore
        RenderingFreeType
        RenderingGL2PSOpenGL2
        RenderingOpenGL2
)

if (NOT VTK_FOUND)
    message(FATAL_ERROR "CylinderExample: Unable to find the VTK build folder.")
endif()

set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")

find_package(MPI REQUIRED)
add_executable(CylinderExample CylinderExample.cpp)
target_link_libraries(CylinderExample PRIVATE ${VTK_LIBRARIES} MPI::MPI_CXX)
vtk_module_autoinit(
        TARGETS CylinderExample
        MODULES ${VTK_LIBRARIES}
)