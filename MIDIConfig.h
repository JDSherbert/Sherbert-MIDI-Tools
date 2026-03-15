// Copyright (c) 2026 JDSherbert. All rights reserved.
 
#pragma once
 
#include <cstdint>
 
// ======================================================================= //
 
namespace Sherbert::MIDI::Config
{
 
    // ------------------------------------------------------------------- //
    // MIDI 1.0 Standard
    //
    // Useful references:
    //   http://www.midi.org/about-midi/table1.shtml
    //   http://www.borg.com/~jglatt/tech/midispec.htm
    // ------------------------------------------------------------------- //
 
    // ---------------------------
    // Channels
    // ---------------------------
 
    inline constexpr uint8_t numChannels        = 16;    // MIDI 1.0 supports 16 channels
 
    // ---------------------------
    // Notes
    // ---------------------------
 
    inline constexpr uint8_t notesPerOctave     = 12;    // Chromatic scale
    inline constexpr uint8_t minNote            = 0;     // C-1
    inline constexpr uint8_t maxNote            = 127;   // G9
    inline constexpr uint8_t maxNumNotes        = 128;   // 0-127 inclusive
 
    // ---------------------------
    // Velocity
    // ---------------------------
 
    inline constexpr uint8_t minVelocity        = 0;     // Silent / NoteOff
    inline constexpr uint8_t maxVelocity        = 127;   // Maximum intensity
    inline constexpr uint8_t defaultVelocity    = 127;
 
    // ---------------------------
    // Timing
    // ---------------------------
 
    inline constexpr int32_t ticksPerQuarterNote    = 960;                          // Standard PPQ resolution
    inline constexpr float   quarterNotesPerTick    = 1.0f / ticksPerQuarterNote;   // ~0.001042f
 
    // ---------------------------
    // Tempo
    // ---------------------------
 
    inline constexpr float   minFileTempo       = 10.0f;     // BPM
    inline constexpr float   maxFileTempo       = 960.0f;    // BPM
    inline constexpr float   defaultTempo       = 120.0f;    // BPM
 
    // ---------------------------
    // Pitch Bend
    // ---------------------------
 
    inline constexpr int16_t pitchBendCenter    = 0;        // No bend
    inline constexpr int16_t pitchBendMin       = -8192;    // Full down
    inline constexpr int16_t pitchBendMax       = 8191;     // Full up
 
    // ---------------------------
    // Control Change
    // ---------------------------
 
    inline constexpr uint8_t ccMin             = 0;
    inline constexpr uint8_t ccMax             = 127;
    inline constexpr uint8_t ccModWheel        = 1;
    inline constexpr uint8_t ccVolume          = 7;
    inline constexpr uint8_t ccPan             = 10;
    inline constexpr uint8_t ccExpression      = 11;
    inline constexpr uint8_t ccSustainPedal    = 64;
    inline constexpr uint8_t ccAllSoundOff     = 120;
    inline constexpr uint8_t ccAllNotesOff     = 123;
 
}
 
// ======================================================================= //
 
