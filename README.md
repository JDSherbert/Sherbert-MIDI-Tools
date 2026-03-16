# Sherbert MIDI Tools
<!-- Header Start -->
<a href="https://learn.microsoft.com/en-us/cpp/cpp-language"><img height="40" img width="40" src="https://cdn.simpleicons.org/cplusplus"></a>
<img align="right" alt="Stars Badge" src="https://img.shields.io/github/stars/jdsherbert/Sherbert-MIDI-Tools?label=%E2%AD%90"/>
<img align="right" alt="Forks Badge" src="https://img.shields.io/github/forks/jdsherbert/Sherbert-MIDI-Tools?label=%F0%9F%8D%B4"/>
<img align="right" alt="Watchers Badge" src="https://img.shields.io/github/watchers/jdsherbert/Sherbert-MIDI-Tools?label=%F0%9F%91%81%EF%B8%8F"/>
<img align="right" alt="Issues Badge" src="https://img.shields.io/github/issues/jdsherbert/Sherbert-MIDI-Tools?label=%E2%9A%A0%EF%B8%8F"/>
<!-- Header End -->
-----------------------------------------------------------------------
<a href="https://midi.org/midi-1-0">
  <img align="left" alt="MIDI 1.0" src="https://img.shields.io/badge/MIDI%201.0-black?style=for-the-badge&logo=midi&logoColor=white&color=black&labelColor=black"></a>
 
<a href="https://en.cppreference.com/w/cpp/20">
  <img align="left" alt="C++20" src="https://img.shields.io/badge/C%2B%2B20-black?style=for-the-badge&logo=cplusplus&logoColor=white&color=black&labelColor=black"></a>
 
<a href="https://choosealicense.com/licenses/mit/">
  <img align="right" alt="License" src="https://img.shields.io/badge/License%20:%20MIT-black?style=for-the-badge&logo=mit&logoColor=white&color=black&labelColor=black"></a>
 
<br></br>
 
-----------------------------------------------------------------------
## Overview
A lightweight, header-only C++20 library providing MIDI 1.0 data types, constants, and utility functions. Designed to be framework-agnostic; works with JUCE, Unreal Engine, or any standard C++ project. No dependencies beyond the C++ standard library.
 
All types live in the `Sherbert::MIDI` namespace to avoid global collisions.
 
-----------------------------------------------------------------------
## Contents
 
| File | Description |
|---|---|
| `MIDI.h` | Umbrella header; include this for everything |
| `MIDIConfig.h` | Tunable MIDI 1.0 constants (channels, velocity, tempo, etc.) |
| `MIDIKey.h` | `MIDIKey` enum (0–127 + NUL) and `MIDIKeyFrequencyTable` |
| `MIDIQuantization.h` | `Quantization` enum for note lengths and grid resolutions |
| `MIDINoteData.h` | `NoteData` struct representing a single MIDI note event |
| `MIDIUtils.h` | Static utility functions for frequency conversion, transposition, and string parsing |
 
-----------------------------------------------------------------------
## Getting Started
 
### Option 1: Copy Headers
Copy the `include/` folder into your project and include the umbrella header:
```cpp
#include "MIDI.h"
```
 
### Option 2: FetchContent (CMake)
```cmake
include(FetchContent)
FetchContent_Declare(
    Sherbert_MIDI
    GIT_REPOSITORY https://github.com/JDSherbert/Sherbert-MIDI-Tools.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(Sherbert_MIDI)
target_link_libraries(YourTarget PRIVATE Sherbert::Sherbert_MIDI)
```
 
### Option 3: CPM (CMake)
```cmake
CPMAddPackage("gh:JDSherbert/Sherbert-MIDI-Tools#main")
target_link_libraries(YourTarget PRIVATE Sherbert::Sherbert_MIDI)
```
 
-----------------------------------------------------------------------
## Usage
 
### Frequency Lookup
```cpp
#include "MIDI.h"
 
// Table lookup (fast, constexpr)
float freq = Sherbert::MIDI::MIDIUtils::keyToHz(Sherbert::MIDI::MIDIKey::A5); // 440.0f
 
// Raw note number
float freq = Sherbert::MIDI::MIDIUtils::midiToHz(69); // 440.0f
 
// Formula-based (use for non-standard tuning)
float freq = Sherbert::MIDI::MIDIUtils::midiToHzCalculated(69, 432.0f); // A432 tuning
```
 
### Note Events
```cpp
// Default: C4, velocity 127, NoteOn
Sherbert::MIDI::NoteData note;
 
// Explicit construction
Sherbert::MIDI::NoteData note(Sherbert::MIDI::MIDIKey::A5, 100, true);
 
// From raw MIDI note number
Sherbert::MIDI::NoteData note(69, 100, true);
 
float freq   = note.getFrequency(); // 440.0f
int8_t oct   = note.getOctave();    // 5
uint8_t num  = note.getNoteNumber(); // 69
bool valid   = note.isValid();       // true
```
 
### Transposition
```cpp
// Transpose a frequency up 12 semitones (one octave)
float up = Sherbert::MIDI::MIDIUtils::transpose(440.0f, 12); // 880.0f
 
// Transpose a Key by semitones
auto key = Sherbert::MIDI::MIDIUtils::transposeKey(Sherbert::MIDI::MIDIKey::A5, -12); // A4
```
 
### String Parsing
```cpp
// Musical notation
auto key = Sherbert::MIDI::MIDIUtils::nameToKey("A5");    // MIDIKey::A5
auto key = Sherbert::MIDI::MIDIUtils::nameToKey("Db4");   // MIDIKey::Db4
auto key = Sherbert::MIDI::MIDIUtils::nameToKey("C-1");   // MIDIKey::Cn1
auto key = Sherbert::MIDI::MIDIUtils::nameToKey("A#4");   // MIDIKey::Bb4 (nearest flat)
 
// Enum identifier style
auto key = Sherbert::MIDI::MIDIUtils::nameToKey("Cn1");   // MIDIKey::Cn1
auto key = Sherbert::MIDI::MIDIUtils::nameToKey("Dbn1");  // MIDIKey::Dbn1
```
 
### Quantization
```cpp
Sherbert::MIDI::MIDIQuantization grid = Sherbert::MIDI::MIDIQuantization::SixteenthNotes;
```
 
### Constants
```cpp
uint8_t maxVel  = Sherbert::MIDI::Config::maxVelocity;    // 127
float   defBpm  = Sherbert::MIDI::Config::defaultTempo;   // 120.0f
int32_t ppq     = Sherbert::MIDI::Config::ticksPerQuarterNote; // 960
```
 
-----------------------------------------------------------------------
## Requirements
- C++20 or later
- No external dependencies
 
-----------------------------------------------------------------------
## Notes
- All enharmonic naming uses **flats** (`Ab`, `Bb`, `Db`, `Eb`, `Gb`) throughout for consistency and identifier safety
- `MIDIKey::NUL` (value 128) is a sentinel for "no note" or invalid; always check `isValid()` or compare against `MIDIKey::NUL` before use
- Frequency values are tuned to **A5 - 440 Hz** (concert pitch). Use `midiToHzCalculated()` for alternative tuning systems
- Designed as a standalone C++ learning resource and drop-in utility library
 
-----------------------------------------------------------------------
