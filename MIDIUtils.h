// Copyright (c) 2026 JDSherbert. All rights reserved.
 
#pragma once
 
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <string>
 
#include "MIDIConfig.h"
#include "MIDIKey.h"
 
// ======================================================================= //
 
namespace Sherbert::MIDI
{
 
    // ------------------------------------------------------------------- //
    // Utils
    // ------------------------------------------------------------------- //
 
    /**
     * Static utility functions for working with MIDI data.
     * All functions are stateless and constexpr or inline where possible.
     *
     * Frequency conversion uses A5 = 440 Hz (concert pitch) as the reference.
     */
    struct MIDIUtils
    {
        MIDIUtils() = delete;
 
        // ------------------------------------------------------------------- //
        // Note <-> Frequency
        // ------------------------------------------------------------------- //
 
        /**
         * Returns the frequency in Hz for a raw MIDI note number (0-127)
         * using a table lookup. Returns 0.0f for out-of-range values.
         */
        [[nodiscard]] static constexpr float midiToHz(const uint8_t midiNote)
        {
            if (midiNote > Config::maxNote)
                return 0.0f;
 
            return MIDIKeyFrequencyTable[midiNote];
        }
 
        /**
         * Returns the frequency in Hz for a Key.
         * Returns 0.0f for Key::NUL.
         */
        [[nodiscard]] static constexpr float keyToHz(const MIDIKey key)
        {
            if (key == MIDIKey::NUL)
                return 0.0f;
 
            return MIDIKeyFrequencyTable[static_cast<uint8_t>(key)];
        }
 
        /**
         * Calculates frequency in Hz from a raw MIDI note number using the
         * equal temperament formula: 440 * 2^((note - 69) / 12).
         * Use this if you need tuning other than A5 = 440 Hz.
         *
         * @param midiNote  MIDI note number (0-127)
         * @param rootFreq  Reference frequency for A5 in Hz (default 440.0f)
         */
        [[nodiscard]] static inline float midiToHzCalculated(const uint8_t midiNote,
                                                              const float rootFreq = 440.0f)
        {
            return rootFreq * std::pow(2.0f, (midiNote - 69) / 12.0f);
        }
 
        /**
         * Returns the nearest MIDI note number for a given frequency in Hz.
         * Returns MIDIKey::NUL if the frequency is <= 0.
         */
        [[nodiscard]] static constexpr MIDIKey hzToKey(const float hz)
        {
            if (hz <= 0.0f)
                return MIDIKey::NUL;
 
            uint8_t closest = 0;
            float closestDistance = std::abs(MIDIKeyFrequencyTable[0] - hz);
 
            for (uint8_t i = 1; i < Config::maxNumNotes; ++i)
            {
                const float distance = std::abs(MIDIKeyFrequencyTable[i] - hz);
                if (distance < closestDistance)
                {
                    closestDistance = distance;
                    closest = i;
                }
            }
 
            return static_cast<MIDIKey>(closest);
        }
 
        /**
         * Returns the nearest raw MIDI note number for a given frequency in Hz.
         * Returns 255 as a sentinel if the frequency is <= 0.
         */
        [[nodiscard]] static constexpr uint8_t hzToMidi(const float hz)
        {
            const MIDIKey key = hzToKey(hz);
            return (key == MIDIKey::NUL) ? 255 : static_cast<uint8_t>(key);
        }
 
        // ------------------------------------------------------------------- //
        // Transposition
        // ------------------------------------------------------------------- //
 
        /**
         * Transposes a frequency by N semitones.
         * Positive values transpose up, negative values transpose down.
         */
        [[nodiscard]] static inline float transpose(const float hz, const int32_t semitones)
        {
            return hz * std::pow(2.0f, semitones / 12.0f);
        }
 
        /**
         * Transposes a MIDI note number by N semitones.
         * Returns Key::NUL if the result is out of range.
         */
        [[nodiscard]] static constexpr Key transposeKey(const MIDIKey key, const int32_t semitones)
        {
            if (key == MIDIKey::NUL)
                return MIDIKey::NUL;
 
            const int32_t result = static_cast<int32_t>(key) + semitones;
            if (result < Config::minNote || result > Config::maxNote)
                return MIDIKey::NUL;
 
            return static_cast<MIDIKey>(result);
        }
 
        // ------------------------------------------------------------------- //
        // Key <-> Note Number
        // ------------------------------------------------------------------- //
 
        /**
         * Returns the raw MIDI note number (0-127) for a Key.
         * Returns 255 as a sentinel for Key::NUL.
         */
        [[nodiscard]] static constexpr uint8_t keyToNoteNumber(const MIDIKey key)
        {
            return static_cast<uint8_t>(key);
        }
 
        /**
         * Returns the Key for a raw MIDI note number (0-127).
         * Returns MIDIKey::NUL for values > 127.
         */
        [[nodiscard]] static constexpr MIDIKey noteNumberToKey(const uint8_t midiNote)
        {
            return (midiNote <= Config::maxNote)
                ? static_cast<MIDIKey>(midiNote)
                : MIDIKey::NUL;
        }
 
        /**
         * Returns the octave number (-1 to 9) for a Key.
         * Returns -2 for MIDIKey::NUL.
         */
        [[nodiscard]] static constexpr int8_t keyToOctave(const MIDIKey key)
        {
            if (key == MIDIKey::NUL)
                return -2;
 
            return static_cast<int8_t>(static_cast<uint8_t>(key) / 12) - 1;
        }
 
        // ------------------------------------------------------------------- //
        // String Parsing
        // ------------------------------------------------------------------- //
 
        /**
         * Parses a string into a Key. Returns MIDIKey::NUL if parsing fails.
         *
         * Accepts two formats:
         *
         * Musical notation  : "C4", "Db4", "A#4", "C-1", "Gb0"
         * Enum identifier   : "C4", "Dbn1", "Ab0", "Cn1", "Gb0"
         *
         * Rules:
         *  - Case insensitive
         *  - Sharps (#) and flats (b/B) are both accepted
         *  - Negative octaves can be written as "-1" or "n1" (n = negative)
         *  - Optional underscore separator is ignored (e.g. "Db_4" = "Db4")
         */
        [[nodiscard]] static MIDIKey nameToKey(const std::string& input)
        {
            if (input.empty())
                return MIDIKey::NUL;
 
            // Uppercase copy for case-insensitive parsing
            std::string s = input;
            std::transform(s.begin(), s.end(), s.begin(),
                           [](unsigned char c) { return std::toupper(c); });
 
            size_t i = 0;
 
            // --- Note letter ---
            if (i >= s.size() || s[i] < 'A' || s[i] > 'G')
                return MIDIKey::NUL;
 
            int32_t semitone = 0;
            switch (s[i++])
            {
                case 'C': semitone = 0;  break;
                case 'D': semitone = 2;  break;
                case 'E': semitone = 4;  break;
                case 'F': semitone = 5;  break;
                case 'G': semitone = 7;  break;
                case 'A': semitone = 9;  break;
                case 'B': semitone = 11; break;
                default:  return MIDIKey::NUL;
            }
 
            // --- Accidental (#, b, or none) ---
            if (i < s.size())
            {
                if (s[i] == '#')        { semitone += 1; ++i; }
                else if (s[i] == 'B')   { semitone -= 1; ++i; }
            }
 
            // --- Optional underscore separator ---
            if (i < s.size() && s[i] == '_')
                ++i;
 
            // --- Octave (handles "-1", "n1", "0".."9") ---
            if (i >= s.size())
                return MIDIKey::NUL;
 
            int32_t octave = 0;
            bool negative = false;
 
            if (s[i] == '-') { negative = true; ++i; }    // musical notation  C-1
            else if (s[i] == 'N') { negative = true; ++i; } // enum notation   Cn1
 
            if (i >= s.size() || !std::isdigit(static_cast<unsigned char>(s[i])))
                return MIDIKey::NUL;
 
            while (i < s.size() && std::isdigit(static_cast<unsigned char>(s[i])))
                octave = octave * 10 + (s[i++] - '0');
 
            if (negative)
                octave = -octave;
 
            // --- Bounds check and compute MIDI note number ---
            const int32_t midiNote = (octave + 1) * 12 + semitone;
            if (midiNote < Config::minNote || midiNote > Config::maxNote)
                return MIDIKey::NUL;
 
            return static_cast<MIDIKey>(midiNote);
        }
    };
}
 
// ======================================================================= //
