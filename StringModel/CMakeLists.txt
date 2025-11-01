cmake_minimum_required(VERSION 3.15)

project(StringModel VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find JUCE
# You can set JUCE_DIR to point to your JUCE installation, e.g.:
# cmake -DJUCE_DIR=/path/to/JUCE ..
# Or uncomment and set the path below:
# set(JUCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Documents/music_tech/JUCE")

if(DEFINED JUCE_DIR)
    add_subdirectory(${JUCE_DIR} JUCE)
else()
    # Try to find JUCE via CMAKE_PREFIX_PATH
    find_package(JUCE CONFIG REQUIRED)
endif()

# Add binary resources
juce_add_binary_data(StringModelAssets
    SOURCES
        Source/question2.png
        Source/ButtonOn.png
        Source/ButtonOff.png
        Source/drumface.png
        Source/Existence-Light.otf
        Source/boxOff.png
        Source/boxOn.png
        Source/drumOff.png
        Source/drumOn.png
        Source/stringOff.png
        Source/stringOn.png
        Source/buttonOn.png
        Source/buttonOff.png
)

# Create the plugin
juce_add_plugin(StringModel
    PLUGIN_NAME "Stringmodel"
    COMPANY_NAME "THESIS"
    PLUGIN_MANUFACTURER_CODE Thes
    PLUGIN_CODE Stmo
    FORMATS Standalone
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT TRUE
    PRODUCT_NAME "StringModel"
)

# Add source files
target_sources(StringModel
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
        Source/PluginEditor.cpp
        Source/PluginEditor.h
        Source/Customize.cpp
        Source/Customize.h
        Source/Customize2.cpp
        Source/Customize2.h
        Source/theString.cpp
        Source/theString.h
        Source/Drumface.cpp
        Source/Drumface.h
        Source/SynthSound.h
        Source/SynthVoice.h
)

# Preprocessor definitions matching the .jucer settings
target_compile_definitions(StringModel
    PUBLIC
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_STRICT_REFCOUNTEDPOINTER=1
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
)

# Link JUCE modules
target_link_libraries(StringModel
    PRIVATE
        StringModelAssets
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_cryptography
        juce::juce_data_structures
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_opengl
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
