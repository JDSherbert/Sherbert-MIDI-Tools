target_compile_features(Sherbert_MIDI INTERFACE cxx_std_20)
 
target_include_directories(Sherbert_MIDI
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
 
# ======================================================================= #
# Optional: Install Rules
# Allows `cmake --install` to copy headers to a system or prefix location
# ======================================================================= #
 
include(GNUInstallDirs)
 
install(TARGETS Sherbert_MIDI
    EXPORT Sherbert_MIDITargets
)
 
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
 
install(EXPORT Sherbert_MIDITargets
    FILE Sherbert_MIDITargets.cmake
    NAMESPACE Sherbert::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Sherbert_MIDIs
)
 
# ======================================================================= #
# Optional: FetchContent / CPM usage example (comment only)
#
# Other projects can consume this library via FetchContent:
#
#   include(FetchContent)
#   FetchContent_Declare(
#       Sherbert_MIDI
#       GIT_REPOSITORY https://github.com/JDSherbert/Sherbert-MIDI-Tools.git
#       GIT_TAG        main
#   )
#   FetchContent_MakeAvailable(Sherbert_MIDI)
#   target_link_libraries(YourTarget PRIVATE Sherbert::Sherbert_MIDI)
#
# Or via CPM:
#
#   CPMAddPackage("gh:JDSherbert/Sherbert-MIDI-Tools#main")
#   target_link_libraries(YourTarget PRIVATE Sherbert::Sherbert_MIDI)
#
# ======================================================================= #
