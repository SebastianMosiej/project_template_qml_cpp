if (WIN32)
  
   find_package(Qt6Core REQUIRED)
  
  # get absolute path to qmake, then use it to find windeployqt executable
  get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
  get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
endif()

function(windeployqt target)

    if (WIN32)
        # POST_BUILD step
        # - after build, we have a bin/lib for analyzing qt dependencies
        # - we run windeployqt on target and deploy Qt libs

        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND "${_qt_bin_dir}/windeployqt.exe"
                    --verbose 1
                    --\"$<IF:$<CONFIG:Debug>,debug,release>\"
                    --no-svg
                    --no-compiler-runtime
                    --no-system-d3d-compiler
                    --qmldir ${CMAKE_SOURCE_DIR}
                    \"$<TARGET_FILE:${target}>\"
            COMMENT "Deploying Qt libraries using windeployqt for compilation target '${target}' ..."
        )

        if (MINGW)
            cmake_path(GET CMAKE_CXX_COMPILER PARENT_PATH QT_MINGW)
            cmake_path(GET QT_MINGW PARENT_PATH QT_MINGW)

            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_MINGW}/bin/libgcc_s_seh-1.dll \"$<TARGET_FILE_DIR:${target}>\"
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_MINGW}/bin/libstdc++-6.dll \"$<TARGET_FILE_DIR:${target}>\"
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QT_MINGW}/bin/libwinpthread-1.dll \"$<TARGET_FILE_DIR:${target}>\"
                    COMMENT "Deploy mingw runtime libraries from ${QT_MINGW}/bin"
                    )
        endif()
    endif()
endfunction()
