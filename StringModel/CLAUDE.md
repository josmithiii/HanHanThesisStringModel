# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

StringModel is a JUCE-based audio plugin that synthesizes physical models of vibrating strings and drums in 1D, 2D, and 3D. The project implements mathematical models for modal synthesis using partial differential equations to simulate string/membrane vibrations with controllable physical parameters.

## Build System

### CMake Build (Recommended)

The project includes a `CMakeLists.txt` for modern CMake-based builds:

```bash
# Configure (specify JUCE_DIR if JUCE is not in CMAKE_PREFIX_PATH)
cmake -B build -DJUCE_DIR=/path/to/JUCE

# Build
cmake --build build

# The standalone app will be in build/StringModel_artefacts/
```

**Requirements**: CMake 3.15+, JUCE 6.0+ with CMake support

### Projucer Build (Legacy)

Alternatively, use JUCE's Projucer:

1. **Opening the project**: Open `StringModel.jucer` in Projucer (there's also `StringModel-jos-mv.jucer` - a variant branch)
2. **Generating build files**: In Projucer, save the project to generate/update build files in `Builds/MacOSX/`
3. **Building**: Open the generated Xcode project in `Builds/MacOSX/` and build from there
4. **Plugin format**: Currently configured to build as a standalone application (see `pluginFormats="buildStandalone"` in .jucer file)

**JUCE modules path**: The Projucer build expects JUCE modules at `../Documents/music_tech/JUCE/modules` relative to the project directory.

## Code Architecture

### Audio Processing Pipeline

- **PluginProcessor** (`PluginProcessor.h/cpp`): Main audio processor implementing JUCE's `AudioProcessor` interface
  - Contains a `Synthesiser` instance (`mySynth`) managing voices and sounds
  - Uses `AudioProcessorValueTreeState` (`tree`) for parameter management
  - Parameters: tau (decay time), omega (fundamental frequency), p (inharmonicity), dispersion, alpha1/alpha2 (aspect ratios), dimtype (dimension selector), length, thickness

- **SynthVoice** (`SynthVoice.h`): Implements the modal synthesis engine
  - Supports 3 dimensions: 1D string (dim=0), 2D membrane (dim=1), 3D volume (dim=2)
  - Core synthesis in `finaloutput()` method - sums modal contributions with exponential decay
  - `getcusParam()` method updates physical parameters and recalculates modal coefficients
  - Uses fixed mode counts: MAX_M1=5, MAX_M2=5 modes per dimension
  - Modal parameters stored in arrays: `omega[]` (frequencies), `sigma[]` (decay rates), `k[]` (amplitudes)

- **SynthSound** (`SynthSound.h`): Simple sound class for JUCE synthesiser framework

### GUI Components

- **PluginEditor** (`PluginEditor.h/cpp`): Main editor using tabbed interface (`TabbedComponent`)
  - Tab 1: `Customize` - Parameter controls for string model
  - Tab 2: `Customize2` - Alternative interface (implementation details not examined)

- **Customize** (`Customize.h/cpp`): Primary parameter control interface
  - Contains sliders for all physical parameters (tau, omega, length, p, dispersion, alpha, alpha2, A)
  - Includes `theString` visual component for graphical feedback
  - Play button for triggering notes
  - Sliders linked to processor via `AudioProcessorValueTreeState::SliderAttachment`

- **theString** (`theString.h/cpp`): Visual representation component
  - Displays string/membrane visualization based on current parameters
  - `changeParameter()` method updates visual representation

- **Drumface** (`Drumface.h/cpp`): Interactive 2D drum interface
  - Mouse interaction to trigger notes at specific positions
  - `mouseDown()` handles user clicks, `clicked()` processes MIDI note triggering
  - `changeParameter()` updates visual representation

### Mathematical Model

The synthesis engine implements modal decomposition of the wave equation:
- **1D (string)**: Vibrating string with stiffness and damping
- **2D (membrane)**: Rectangular drum membrane
- **3D (volume)**: 3D resonator/cavity

Key mathematical components in SynthVoice:
- `getsigma*()`: Calculates modal decay rates from physical parameters
- `getw*()`: Calculates modal frequencies including dispersion and inharmonicity
- `getK*()`: Calculates mode amplitudes from excitation function
- `deff()`: Defines Gaussian excitation distribution
- `getf()`: Computes Fourier coefficients of excitation via trapezoidal integration
- `findmax*()`: Normalizes output by finding maximum initial amplitude

## File Organization

- `Source/` - All source code
  - Core: `PluginProcessor.*`, `PluginEditor.*`
  - Synthesis: `SynthVoice.h`, `SynthSound.h`
  - GUI: `Customize.*`, `Customize2.*`, `theString.*`, `Drumface.*`
  - Assets: `.png` images, `.otf` font files
- `JuceLibraryCode/` - Auto-generated JUCE integration code
- `Builds/MacOSX/` - Generated Xcode project (not in git)
- `.jucer` files - JUCE project definitions

## Development Notes

- This is a JUCE 5/6 era project (uses older `ScopedPointer` instead of modern `std::unique_ptr` in some places)
- No test suite currently exists
- Sample rate hardcoded to 44100 Hz in SynthVoice (line 568)
- The project implements research on physical modeling synthesis - mathematical accuracy is critical
- Git status shows many untracked generated files (JuceLibraryCode, Builds, etc.) - these should not be committed
