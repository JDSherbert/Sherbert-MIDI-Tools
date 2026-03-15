// Copyright (c) 2026 JDSherbert. All rights reserved.
 
#pragma once
 
#include <array>
#include <cstdint>
 
// ======================================================================= //
 
namespace Sherbert::MIDI
{
 
    // ------------------------------------------------------------------- //
    // MIDIKey
    // ------------------------------------------------------------------- //
 
    /**
     * Represents a MIDI note as a strongly-typed enum serializable to an
     * integer in the range 0-127. NUL (128) is provided as a sentinel value
     * for "no note" or "unrecognized key".
     * Always check for NUL before use.
     *
     * Enharmonic naming convention: flats (Ab, Bb, Db, Eb, Gb) are used
     * throughout to avoid # characters which are not valid in C++ identifiers.
     * Ab/Gb straddle octave boundaries following standard MIDI numbering.
     *
     * MIDI note 0  = C-1 (sub-bass, below audible range on most systems)
     * MIDI note 69 = A5  (concert pitch, 440 Hz)
     * MIDI note 127 = G9
     */
    enum class MIDIKey : uint8_t
    {
        Cn1  = 0,
        Dbn1 = 1,
        Dn1  = 2,
        Ebn1 = 3,
        En1  = 4,
        Fn1  = 5,
        Gbn1 = 6,
        Gn1  = 7,
        Ab0  = 8,
        A0   = 9,
        Bb0  = 10,
        B0   = 11,
        C0   = 12,
        Db0  = 13,
        D0   = 14,
        Eb0  = 15,
        E0   = 16,
        F0   = 17,
        Gb0  = 18,
        G0   = 19,
        Ab1  = 20,
        A1   = 21,
        Bb1  = 22,
        B1   = 23,
        C1   = 24,
        Db1  = 25,
        D1   = 26,
        Eb1  = 27,
        E1   = 28,
        F1   = 29,
        Gb1  = 30,
        G1   = 31,
        Ab2  = 32,
        A2   = 33,
        Bb2  = 34,
        B2   = 35,
        C2   = 36,
        Db2  = 37,
        D2   = 38,
        Eb2  = 39,
        E2   = 40,
        F2   = 41,
        Gb2  = 42,
        G2   = 43,
        Ab3  = 44,
        A3   = 45,
        Bb3  = 46,
        B3   = 47,
        C3   = 48,
        Db3  = 49,
        D3   = 50,
        Eb3  = 51,
        E3   = 52,
        F3   = 53,
        Gb3  = 54,
        G3   = 55,
        Ab4  = 56,
        A4   = 57,
        Bb4  = 58,
        B4   = 59,
        C4   = 60,
        Db4  = 61,
        D4   = 62,
        Eb4  = 63,
        E4   = 64,
        F4   = 65,
        Gb4  = 66,
        G4   = 67,
        Ab5  = 68,
        A5   = 69,   // Concert pitch — 440 Hz
        Bb5  = 70,
        B5   = 71,
        C5   = 72,
        Db5  = 73,
        D5   = 74,
        Eb5  = 75,
        E5   = 76,
        F5   = 77,
        Gb5  = 78,
        G5   = 79,
        Ab6  = 80,
        A6   = 81,
        Bb6  = 82,
        B6   = 83,
        C6   = 84,
        Db6  = 85,
        D6   = 86,
        Eb6  = 87,
        E6   = 88,
        F6   = 89,
        Gb6  = 90,
        G6   = 91,
        Ab7  = 92,
        A7   = 93,
        Bb7  = 94,
        B7   = 95,
        C7   = 96,
        Db7  = 97,
        D7   = 98,
        Eb7  = 99,
        E7   = 100,
        F7   = 101,
        Gb7  = 102,
        G7   = 103,
        Ab8  = 104,
        A8   = 105,
        Bb8  = 106,
        B8   = 107,
        C8   = 108,
        Db8  = 109,
        D8   = 110,
        Eb8  = 111,
        E8   = 112,
        F8   = 113,
        Gb8  = 114,
        G8   = 115,
        Ab9  = 116,
        A9   = 117,
        Bb9  = 118,
        B9   = 119,
        C9   = 120,
        Db9  = 121,
        D9   = 122,
        Eb9  = 123,
        E9   = 124,
        F9   = 125,
        Gb9  = 126,
        G9   = 127,
 
        NUL  = 128   // Sentinel — outside MIDI range, always check for this
    };
 
    // ------------------------------------------------------------------- //
    // Frequency Table
    // ------------------------------------------------------------------- //
 
    /**
     * Maps each MIDI note number (0-127) to its frequency in Hz.
     * Tuned to A5 = 440 Hz (concert pitch).
     * Index directly with a Key cast to uint8_t, or with a raw integer.
     *
     * Source: https://nickfever.com/music/note-frequencies
     */
    inline constexpr std::array<float, 128> MIDIKeyFrequencyTable =
    {
        //  C        Db       D        Eb       E        F        Gb       G        Ab       A        Bb       B
            8.18f,   8.66f,   9.18f,   9.72f,   10.30f,  10.91f,  11.56f,  12.25f,  12.98f,  13.75f,  14.57f,  15.43f,  // -1
            16.35f,  17.32f,  18.35f,  19.45f,  20.60f,  21.83f,  23.12f,  24.50f,  25.96f,  27.50f,  29.14f,  30.87f,  //  0
            32.70f,  34.65f,  36.71f,  38.89f,  41.20f,  43.65f,  46.25f,  49.00f,  51.91f,  55.00f,  58.27f,  61.74f,  //  1
            65.41f,  69.30f,  73.42f,  77.78f,  82.41f,  87.31f,  92.50f,  98.00f,  103.83f, 110.00f, 116.54f, 123.47f, //  2
            130.81f, 138.59f, 146.83f, 155.56f, 164.81f, 174.61f, 185.00f, 196.00f, 207.65f, 220.00f, 233.08f, 246.94f, //  3
            261.63f, 277.18f, 293.66f, 311.13f, 329.63f, 349.23f, 369.99f, 392.00f, 415.30f, 440.00f, 466.16f, 493.88f, //  4
            523.25f, 554.37f, 587.33f, 622.25f, 659.26f, 698.46f, 739.99f, 783.99f, 830.61f, 880.00f, 932.33f, 987.77f, //  5
            1046.50f,1108.73f,1174.66f,1244.51f,1318.51f,1396.91f,1479.98f,1567.98f,1661.22f,1760.00f,1864.66f,1975.53f,//  6
            2093.00f,2217.46f,2349.32f,2489.02f,2637.02f,2793.83f,2959.96f,3135.96f,3322.44f,3520.00f,3729.31f,3951.07f,//  7
            4186.01f,4434.92f,4698.64f,4978.03f,5274.04f,5587.65f,5919.87f,6271.93f,6644.88f,7040.00f,7458.62f,7902.13f,//  8
            8372.02f,8869.84f,9397.27f,9956.06f,10548.08f,11175.30f,11839.82f,12543.85f                                 //  9
    };
 
}
 
// ======================================================================= //
