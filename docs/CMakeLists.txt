cmake_minimum_required(VERSION 3.11)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR})
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR})

    configure_file(${DOXYGEN_IN}/Doxyfile.in ${DOXYGEN_OUT}/Doxyfile @ONLY)
    message("Doxygen build added")

    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )

    add_custom_command(TARGET doc_doxygen POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${DOXYGEN_OUT}/html" "${DOXYGEN_IN}"
        COMMENT "copying Doxygen output to source tree"
        VERBATIM
    )

else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
