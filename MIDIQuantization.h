// Copyright (c) 2026 JDSherbert. All rights reserved.
 
#pragma once
 
#include <cstdint>
 
// ======================================================================= //
 
namespace Sherbert::MIDI
{
 
    // ------------------------------------------------------------------- //
    // Quantization
    // ------------------------------------------------------------------- //
 
    /**
     * Represents a MIDI time quantization unit. Used to express note lengths,
     * offsets, and grid resolutions in a DAW or sequencer context.
     *
     * Bars and Beats are tempo/time-signature dependent.
     * All other values are fixed subdivisions of a whole note.
     * Dotted values are 1.5x the base duration.
     * Triplet values are 2/3 of the base duration.
     */
    enum class MIDIQuantization : uint8_t
    {
        Milliseconds,           // Absolute time — not tempo-relative
 
        Bars,                   // Tempo + time signature dependent
        Beats,                  // Tempo + time signature dependent
 
        ThirtySecondNotes,      // 1/32
        SixteenthNotes,         // 1/16
        EighthNotes,            // 1/8
        QuarterNotes,           // 1/4
        HalfNotes,              // 1/2
        WholeNotes,             // 1/1
 
        DottedSixteenthNotes,   // 1/16 dotted  (= 3/32)
        DottedEighthNotes,      // 1/8  dotted  (= 3/16)
        DottedQuarterNotes,     // 1/4  dotted  (= 3/8)
        DottedHalfNotes,        // 1/2  dotted  (= 3/4)
        DottedWholeNotes,       // 1/1  dotted  (= 3/2)
 
        SixteenthNoteTriplets,  // 1/16 triplet (= 1/24)
        EighthNoteTriplets,     // 1/8  triplet (= 1/12)
        QuarterNoteTriplets,    // 1/4  triplet (= 1/6)
        HalfNoteTriplets,       // 1/2  triplet (= 1/3)
    };
 
}
 
// ======================================================================= //
