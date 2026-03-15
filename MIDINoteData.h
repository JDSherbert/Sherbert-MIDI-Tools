// Copyright (c) 2026 JDSherbert. All rights reserved.
 
#pragma once
 
#include <cstdint>
 
#include "MIDIKey.h"
 
// ======================================================================= //
 
namespace Sherbert::MIDI
{
 
    // ------------------------------------------------------------------- //
    // MIDINoteData
    // ------------------------------------------------------------------- //
 
    /**
     * Represents a single MIDI note event; the minimal packet of data
     * needed to describe a note being played or released.
     *
     * Key      : The MIDI note (0-127), defaults to C4 (middle C)
     * Velocity : How hard the note was struck (0-127), defaults to 127
     * isNoteOn : True if the note is being pressed, false if released
     *
     * Note: a NoteOn event with velocity 0 is conventionally equivalent
     * to a NoteOff in the MIDI spec, but this struct uses an explicit
     * isNoteOn flag for clarity.
     */
    struct MIDINoteData
    {
        static constexpr uint8_t maxVelocity = 127;
        static constexpr uint8_t minVelocity = 0;
 
        // ------------------------------------------------------------------- //
 
        Key      key      = Key::C4;
        uint8_t  velocity = maxVelocity;
        bool     isNoteOn = true;
 
        // ------------------------------------------------------------------- //
 
        constexpr MIDINoteData() = default;
 
        constexpr MIDINoteData(const Key newKey, const uint8_t newVelocity, const bool noteOn = true)
            : key(newKey)
            , velocity(newVelocity)
            , isNoteOn(noteOn)
        {}
 
        /**
         * Construct from a raw MIDI note number (0-127).
         * If the note number is out of range, key is set to Key::NUL.
         */
        constexpr MIDINoteData(const uint8_t noteNumber, const uint8_t newVelocity, const bool noteOn = true)
            : key(noteNumber <= 127 ? static_cast<Key>(noteNumber) : MIDIKey::NUL)
            , velocity(newVelocity)
            , isNoteOn(noteOn)
        {}
 
        // ------------------------------------------------------------------- //
 
        /** Returns the raw MIDI note number (0-127), or 128 for NUL. */
        [[nodiscard]] constexpr uint8_t getNoteNumber() const
        {
            return static_cast<uint8_t>(key);
        }
 
        /**
         * Returns the octave number (-1 to 9).
         * Returns -1 for notes in octave -1 (MIDI notes 0-11).
         * Returns -2 if key is NUL (invalid).
         */
        [[nodiscard]] constexpr int8_t getOctave() const
        {
            if (key == MIDIKey::NUL)
                return -2;
 
            return static_cast<int8_t>(getNoteNumber() / 12) - 1;
        }
 
        /**
         * Returns the frequency in Hz for this note.
         * Returns 0.0f if key is NUL.
         */
        [[nodiscard]] constexpr float getFrequency() const
        {
            if (key == MIDIKey::NUL)
                return 0.0f;
 
            return FrequencyTable[getNoteNumber()];
        }
 
        /** Returns true if this note event is valid (key is not NUL). */
        [[nodiscard]] constexpr bool isValid() const
        {
            return key != MIDIKey::NUL;
        }
 
    };
 
}
 
// ======================================================================= //
