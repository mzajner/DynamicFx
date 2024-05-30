//========EFFECTS ARCHIVE========

const knobSettings = {

//----------AUTOPANNER----------
        "AutoPanner": {
        knobs: [
            { id: 0, config: { text: "Dry/Wet", min: 0.0, max: 100.0, mode: "Linear", stepSize: 0.1, middlePosition: 50.0, defaultValue: 50.0, suffix: "%", tooltip: "Controls the dry/wet." }},
            { id: 1, config: { text: "Rate", min: 150.0, max: 5000.0, mode: "Time", stepSize: 1.0, middlePosition: 2500.0, defaultValue: 2500.0, suffix: " ms", tooltip: "Controls the panner rate in milliseconds." }},
            { id: 2, config: { text: "Tempo", min: 0.0, max: 18.0, mode: "TempoSync", stepSize: 1.0, middlePosition: 9.0, defaultValue: 9.0, suffix: "", tooltip: "Sets the rate of the panner synced to the host's tempo." }},
            { id: 3, config: { text: "Waveform", min: 1.0, max: 4.0, mode: "Linear", stepSize: 1.0, middlePosition: 3.0, defaultValue: 1.0, suffix: "", tooltip: "Controls the waveshape of the panner's modulation." }},
            { id: 4, config: { text: "Depth", min: 0.0, max: 100.0, mode: "TempoSync", stepSize: 0.1, middlePosition: 50.0, defaultValue: 50.0, suffix: "%", tooltip: "Sets the depth of the panner amount." }},
            { id: 5, config: { text: "Sync", min: 0.0, max: 1.0, mode: "Linear", stepSize: 1.0, middlePosition: 0.5, defaultValue: 0.0, suffix: "", tooltip: "Syncs the panner rate." }}
        ],
        sync: {
            buttonIndex: 5,
            unsyncedKnobs: [1], // Rate
            syncedKnobs: [2]    // Tempo
        }
    },
    
//----------COMPRESSOR----------
    "Compressor": [
        { id: 0, config: { 
        	text: "Dry/Wet", 
        	min: 0.0, 
        	max: 100.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: 50, 
        	defaultValue: 50, 
        	suffix: "%", 
        	tooltip: "Controls the delay dry/wet." 
        }},
        { id: 1, config: { 
        	text: "Ratio", 
        	min: 1.0, 
        	max: 20.0, 
        	mode: "Linear", 
        	stepSize: 0.01, 
        	middlePosition: 10.0, 
        	defaultValue: 4.0, 
        	suffix: ":1", 
        	tooltip: "Controls the ratio of the compressor." 
        }},
        { id: 2, config: { 
        	text: "Threshold", 
        	min: -100.0, 
        	max: 10.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: -18.0, 
        	defaultValue: -18.0, 
        	suffix: "", 
        	tooltip: "Sets the thrshold of the compressor." 
        }},
        { id: 3, config: { 
        	text: "Attack", 
        	min: 1.0, 
        	max: 1000.0, 
        	mode: "Linear", 
        	stepSize: 0.01, 
        	middlePosition: 20.0, 
        	defaultValue: 1.0, 
        	suffix: " ms", 
        	tooltip: "Controls the attack time." 
        }},
        { id: 4, config: { 
        	text: "Release", 
        	min: 1.0, 
        	max: 3000.0, 
        	mode: "Linear", 
        	stepSize: 1.0, 
        	middlePosition: 500.0, 
        	defaultValue: 3.0, 
        	suffix: " ms", 
        	tooltip: "Controls the release time." 
        }},
        { id: 5, config: { 
        	text: "Makeup Gain", 
        	min: -12.0, 
        	max: 12.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: 0, 
        	defaultValue: 0, 
        	suffix: " dB", 
        	tooltip: "Sets the makeup gain." 
        }}
    ],

//----------DETUNER----------
    "Detuner": [
        { id: 0, config: { 
        	text: "Dry/Wet", 
        	min: 0.0, 
        	max: 100.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: 50, 
        	defaultValue: 50, 
        	suffix: "%", 
        	tooltip: "Controls the dry/wet." 
        }},
        { id: 1, config: { 
        	text: "Center Detune", 
        	min: -100.0, 
        	max: 100.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: 0, 
        	defaultValue: 25.0, 
        	suffix: " st", 
        	tooltip: "Controls the detune of the center of the signal in semitones." 
        }},
        { id: 2, config: { 
        	text: "Sides Detune", 
        	min: -100.0, 
        	max: 100.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: 0, 
        	defaultValue: 0, 
        	suffix: " st", 
        	tooltip: "Controls the detune of the sides of the signal in semitones." 
        }},
        { id: 3, config: { 
        	text: "Mid/Side", 
        	min: 0, 
        	max: 100.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: 50.0, 
        	defaultValue: 50.0, 
        	suffix: "%", 
        	tooltip: "Sets the balance of the mid and sides." 
        }},
        { id: 4, config: { 
        	text: "Sync",
        	min: 0, 
        	max: 1.0, 
        	mode: "Linear", 
        	stepSize: 1.0, 
        	middlePosition: 0.5, 
        	defaultValue: 0, 
        	suffix: "", 
        	tooltip: "Syncs the detune of the mid and sides." 
        }}
    ],

//----------FLANGER----------
    "Flanger": {
        knobs: [
            { id: 0, config: { text: "Dry/Wet", min: 0.0, max: 100.0, mode: "Linear", stepSize: 0.1, middlePosition: 50.0, defaultValue: 50.0, suffix: "%", tooltip: "Controls the dry/wet." }},
            { id: 1, config: { text: "Rate", min: 0.01, max: 10.0, mode: "Linear", stepSize: 0.01, middlePosition: 0.50, defaultValue: 0.50, suffix: " Hz", tooltip: "Controls the flanger rate." }},
            { id: 2, config: { text: "Feedback", min: 0.0, max: 100.0, mode: "Linear", stepSize: 0.1, middlePosition: 50.0, defaultValue: 50.0, suffix: "%", tooltip: "Controls the amount of feedback." }},
            { id: 3, config: { text: "Time", min: 0.1, max: 50.0, mode: "Time", stepSize: 0.1, middlePosition: 25.0, defaultValue: 25.0, suffix: " ms", tooltip: "Sets the delay time in milliseconds." }},
            { id: 4, config: { text: "Tempo", min: 0.0, max: 18.0, mode: "TempoSync", stepSize: 1.0, middlePosition: 9.0, defaultValue: 5.0, suffix: "", tooltip: "Sets the rate of the flanger synced to the host's tempo." }},
            { id: 5, config: { text: "Sync", min: 0.0, max: 1.0, mode: "Linear", stepSize: 1.0, middlePosition: 0.5, defaultValue: 0.0, suffix: "", tooltip: "Syncs the flanger rate." }}
        ],
        sync: {
            buttonIndex: 5,
            unsyncedKnobs: [1, 3], // Rate and Time
            syncedKnobs: [4]       // Tempo
        }
    },
    
//----------GLISTEN REVERB----------
    "GlistenReverb": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Decay",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the decay time."
        }},
        { id: 2, config: {
            text: "Glisten",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the amount of pitch reflections."
        }},
        { id: 3, config: {
            text: "$bipolar Pitch",
            min: -24.0,
            max: 24.0,
            mode: "Linear",
            stepSize: 0.01,
            middlePosition: 0,
            defaultValue: 0,
            suffix: " st",
            tooltip: "Sets the pitch shifting in semitones."
        }},
        { id: 4, config: {
            text: "$bipolar Fine Tune",
            min: -100.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 0,
            defaultValue: 0,
            suffix: " cents",
            tooltip: "Sets the fine tuning in cents."
        }},
        { id: 5, config: {
            text: "Freeze",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Infinitley freezes reverb."
        }}
    ],

    //----------INFINITE REVERB----------
    "InfiniteReverb": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Size",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the size of the reverb."
        }},
        { id: 2, config: {
            text: "Damp",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the amount of damping."
        }},
        { id: 3, config: {
            text: "Diffusion",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.01,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Sets the amount of diffusion."
        }},
        { id: 4, config: {
            text: "Depth",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Sets the depth amount of the reverb."
        }},
        { id: 5, config: {
            text: "Mod. Freq.",
            min: 0.0,
            max: 10.0,
            mode: "Linear",
            stepSize: 0.01,
            middlePosition: 1.00,
            defaultValue: 1.00,
            suffix: " Hz",
            tooltip: "Sets the modulation frequency of the delay line."
        }},
        { id: 6, config: {
            text: "Mod. Depth",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Sets the modulation depth amount of the delay line."
        }},
        { id: 7, config: {
            text: "Time",
            min: 0.0,
            max: 1450.0,
            mode: "Time",
            stepSize: 1.0,
            middlePosition: 145.0,
            defaultValue: 145.0,
            suffix: " ms",
            tooltip: "Sets the delay time."
        }},
    ],
    
//----------GRAINS----------
    "Grains": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Time",
            min: 50.0,
            max: 1000.0,
            mode: "Time",
            stepSize: 1.0,
            middlePosition: 500.0,
            defaultValue: 500.0,
            suffix: " ms",
            tooltip: "Sets the time of the grain reproduction in milliseconds."
        }},
        { id: 2, config: {
            text: "Size",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Sets the size of the grain window."
        }},
        { id: 3, config: {
            text: "Probability",
            min: 20.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 60.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Sets the probability of a grain being produced."
        }},
        { id: 4, config: {
            text: "Tempo",
            min: 0.0,
            max: 18.0,
            mode: "TempoSync",
            stepSize: 1.0,
            middlePosition: 9.0,
            defaultValue: 5.0,
            suffix: "",
            tooltip: "Sets the time of the grain reproduction synced to the host's tempo."
        }},
        { id: 5, config: {
            text: "Sync",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Syncs the grain reproduction."
        }}
    ],
    
//----------HAZE DISTORTION----------
    "HazeDistortion": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50,
            defaultValue: 50,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Tone",
            min: 20.0,
            max: 20000.0,
            mode: "Frequency",
            stepSize: 1.0,
            middlePosition: 1000.0,
            defaultValue: 1000.0,
            suffix: " Hz",
            tooltip: "Sets the tone of the distortion."
        }},
        { id: 2, config: {
            text: "Haze",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Sets the amount of haze distortion."
        }},
        { id: 3, config: {
            text: "Filter",
            min: 20.0,
            max: 20000.0,
            mode: "Frequency",
            stepSize: 1.0,
            middlePosition: 1000.0,
            defaultValue: 1000.0,
            suffix: " Hz",
            tooltip: "Sets the cutoff frequency of the post-low-pass filter."
        }}
    ],
    
//----------LOOPER----------
    "Looper": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50,
            defaultValue: 50,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Record Length",
            min: 0.0,
            max: 10000.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 5000.0,
            defaultValue: 2000.0,
            suffix: " ms",
            tooltip: "Sets the record length in milliseconds."
        }},
        { id: 2, config: {
            text: "Length",
            min: 0.0,
            max: 18.0,
            mode: "TempoSync",
            stepSize: 1.0,
            middlePosition: 9.0,
            defaultValue: 9.0,
            suffix: "",
            tooltip: "Sets the record length synced to the host's tempo."
        }},
        { id: 3, config: {
            text: "Pitch",
            min: -24.0,
            max: 24.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 0,
            defaultValue: 0,
            suffix: " st",
            tooltip: "Sets the pitch shifting in semitones."
        }},
        { id: 4, config: {
            text: "Multiplier",
            min: 0.0,
            max: 3.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 1.0,
            defaultValue: 0,
            suffix: "",
            tooltip: "Doubles the tempo length of the record time when tempo sync is set."
        }},
        { id: 5, config: {
            text: "Tempo Sync",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Syncs the record length to the host tempo."
        }},
        { id: 6, config: {
            text: "Record.Play",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Record inconming signal then play the loop back."
        }},
        { id: 7, config: {
            text: "Auto",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Automatically records the incoming signal."
        }},
        { id: 8, config: {
            text: "Reverse",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Reverse the recorde signal."
        }}
    ],

//----------PHASER----------
    "Phaser": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Rate",
            min: 0.01,
            max: 10.0,
            mode: "Frequency",
            stepSize: 0.01,
            middlePosition: 1.0,
            defaultValue: 1.0,
            suffix: " Hz",
            tooltip: "Controls the phaser rate."
        }},
        { id: 2, config: {
            text: "Feedback",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the amount of feedback."
        }},
        { id: 3, config: {
            text: "Depth",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: " ms",
            tooltip: "Sets the depth of the phaser."
        }},
        { id: 4, config: {
            text: "Tempo",
            min: 0.0,
            max: 18.0,
            mode: "TempoSync",
            stepSize: 1.0,
            middlePosition: 9.0,
            defaultValue: 5.0,
            suffix: "",
            tooltip: "Sets the rate of the phaser synced to the host's tempo."
        }},
        { id: 5, config: {
            text: "Tempo Sync",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Syncs the phaser rate."
        }},
        { id: 6, config: {
            text: "Width",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the width of the notch signal."
        }},
        { id: 7, config: {
            text: "Notch",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Sets the central notch frequency"
        }},
        { id: 8, config: {
            text: "Tempo Sync",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Sync's the modulation signal to the host's tempo."
        }},
        { id: 9, config: {
            text: "Invert",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Invert the modulation signal."
        }},
        { id: 10, config: {
            text: "Vibrato",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Enable vibrato."
        }}
    ],
 
//----------REVERSE DELAY----------
    "ReverseDelay": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Delay Time",
            min: 0.01,
            max: 5000.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 1000.0,
            defaultValue: 1000.0,
            suffix: " ms",
            tooltip: "Sets the delay time in milliseconds."
        }},
        { id: 2, config: {
            text: "Delay Tempo",
            min: 0,
            max: 18.0,
            mode: "TempoSync",
            stepSize: 1.0,
            middlePosition: 9.0,
            defaultValue: 9.0,
            suffix: "",
            tooltip: "Sets the delay time synced to the host's tempo."
        }},
        { id: 3, config: {
            text: "Feedback",
            min: 0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Sets the delay's feedback."
        }},
        { id: 4, config: {
            text: "Crossover",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Sets left signal to right channel, and right channel to left channel."
        }},
        { id: 5, config: {
            text: "Window",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the window width of the reverse buffer."
        }},
        { id: 6, config: {
            text: "Tempo Sync",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Sync's the modulation signal to the host's tempo."
        }}
    ],
    
    //----------SATURATOR MODERN----------
    "SaturatorModern": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Drive",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the amount of distortion."
        }},
        { id: 2, config: {
            text: "Blend",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 0.0,
            suffix: "%",
            tooltip: "Blends between cubic and quadratic distortion."
        }},
        { id: 3, config: {
            text: "Harmonics",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 0.0,
            suffix: "%",
            tooltip: "Blends between even and odd harmonics."
        }},
        { id: 4, config: {
            text: "Tone",
            min: 20.0,
            max: 20000.0,
            mode: "Frequency",
            stepSize: 1.0,
            middlePosition: 1000.0,
            defaultValue: 1000.0,
            suffix: " Hz",
            tooltip: "Controls frequency of the tone added to the signal."
        }}
    ],
    
//----------SATURATOR MODERN----------
    "SaturatorModern": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Drive",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 0.0,
            suffix: "%",
            tooltip: "Controls the amount of distortion."
        }},
        { id: 2, config: {
            text: "Blend",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 0.0,
            suffix: "%",
            tooltip: "Blends between soft clip and hard clip distortion."
        }},
        { id: 3, config: {
            text: "Tone",
            min: 100.0,
            max: 10000.0,
            mode: "Frequency",
            stepSize: 1.0,
            middlePosition: 1000.0,
            defaultValue: 1000.0,
            suffix: " Hz",
            tooltip: "Controls frequency of the tone added to the signal."
        }}
    ],
   
//----------SATURATOR MODERN----------
    "SaturatorVintage": [
        { id: 0, config: {
        text: "Dry/Wet",
        min: 0.0,
        max: 100.0,
        mode: "Linear",
        stepSize: 0.1,
        middlePosition: 50.0,
        defaultValue: 50.0,
        suffix: "%",
        tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
        text: "Drive",
        min: 0.0,
        max: 100.0,
        mode: "Linear",
        stepSize: 0.1,
        middlePosition: 50.0,
        defaultValue: 0.0,
        suffix: "%",
        tooltip: "Controls the amount of distortion."
        }},
        { id: 2, config: {
        text: "Blend",
        min: 0.0,
        max: 100.0,
        mode: "Linear",
        stepSize: 0.1,
        middlePosition: 50.0,
        defaultValue: 0.0,
        suffix: "%",
        tooltip: "Blends between soft clip and hard clip distortion."
        }},
        { id: 3, config: {
        text: "Tone",
        min: 200.0,
        max: 5000.0,
        mode: "Frequency",
        stepSize: 1.0,
        middlePosition: 1000.0,
        defaultValue: 1000.0,
        suffix: " Hz",
        tooltip: "Controls frequency of the tone added to the signal."
        }}
    ],
    
//----------SHREDDISTORTION----------
    "ShredDistortion": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Shred",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the amount of distortion."
        }},
        { id: 2, config: {
            text: "Tone",
            min: 100.0,
            max: 5000.0,
            mode: "Frequency",
            stepSize: 1.0,
            middlePosition: 1000.0,
            defaultValue: 1000.0,
            suffix: " Hz",
            tooltip: "Sets the tone of the distortion."
        }},
        { id: 3, config: {
            text: "Boost",
            min: -15.0,
            max: 0.0,
            mode: "Decibel",
            stepSize: 0.1,
            middlePosition: -6.0,
            defaultValue: -6.0,
            suffix: " dB",
            tooltip: "Controls the amount of tone added to the signal."
        }}
    ],
    
//----------SLAPBAKCDELAY----------
    "SlapbackDelay": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Delay Time",
            min: 1.0,
            max: 2000.0,
            mode: "Time",
            stepSize: 0.1,
            middlePosition: 500.0,
            defaultValue: 250.0,
            suffix: " ms",
            tooltip: "Sets the delay time in milliseconds."
        }},
        { id: 2, config: {
            text: "Feedback",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Sets the delay's feedback."
        }},
        { id: 3, config: {
            text: "Filter",
            min: 20.0,
            max: 20000.0,
            mode: "Frequency",
            stepSize: 1.0,
            middlePosition: 1000.0,
            defaultValue: 1000.0,
            suffix: " Hz",
            tooltip: "Sets the cutoff frequency of the filter."
        }},
        { id: 4, config: {
            text: "Delay Tempo",
            min: 0,
            max: 18.0,
            mode: "TempoSync",
            stepSize: 1.0,
            middlePosition: 9.0,
            defaultValue: 9.0,
            suffix: "",
            tooltip: "Sets the delay time synced to the host's tempo."
        }},
        { id: 5, config: {
            text: "Filter Type",
            min: 0.0,
            max: 2.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 1.0,
            defaultValue: 0,
            suffix: "",
            tooltip: "Sets the filter to LPF, HPF, or BPF."
        }},
        { id: 6, config: {
            text: "Tempo Sync",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Sync's the modulation signal to the host's tempo."
        }}
    ],

//----------TWIST DELAY----------
    "TwistDelay": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Time",
            min: 0.01,
            max: 2000.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 1000.0,
            defaultValue: 1000.0,
            suffix: " ms",
            tooltip: "Sets the delay time in milliseconds."
        }},
        { id: 2, config: {
            text: "Feedback",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Sets the delay's feedback."
        }},
        { id: 3, config: {
            text: "Echo",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Sets the amount of slpaback."
        }},
        { id: 4, config: {
            text: "Tempo",
            min: 0.0,
            max: 18.0,
            mode: "TempoSync",
            stepSize: 1.0,
            middlePosition: 9.0,
            defaultValue: 9.0,
            suffix: "",
            tooltip: "Sets the delay time synced to the host's tempo."
        }},
        { id: 5, config: {
            text: "$bipolar Twist",
            min: -1.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 0.01,
            middlePosition: 0.0,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Sets the direction of the twist."
        }},
        { id: 6, config: {
            text: "Filter",
            min: 0.0,
            max: 1.0,
            mode: "Frequency",
            stepSize: 0.01,
            middlePosition: 0.5,
            defaultValue: 1.0,
            suffix: "",
            tooltip: "Sets the cutoff frequency of the lowpass-filter."
        }},
        { id: 7, config: {
            text: "Sync",
            min: 0.0,
            max: 1.0,
            mode: "Linear",
            stepSize: 1.0,
            middlePosition: 0.5,
            defaultValue: 0.0,
            suffix: "",
            tooltip: "Sync's the modulation signal to the host's tempo."
        }}
    ],
    
//----------Widener----------
    "Widener": [
        { id: 0, config: {
            text: "Dry/Wet",
            min: 0.0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50,
            defaultValue: 50,
            suffix: "%",
            tooltip: "Controls the dry/wet."
        }},
        { id: 1, config: {
            text: "Mid Gain",
            min: -100.0,
            max: 6.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: -12.0,
            defaultValue: 25.0,
            suffix: " dB",
            tooltip: "Sets the amplitude of the mid signal"
        }},
        { id: 2, config: {
            text: "Side Gain",
            min: -100.0,
            max: 6.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: -12.0,
            defaultValue: 25.0,
            suffix: " dB",
            tooltip: "Sets the amplitude of the side signals"
        }},
        { id: 3, config: {
            text: "Mid/Side",
            min: 0,
            max: 100.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 50.0,
            defaultValue: 50.0,
            suffix: "%",
            tooltip: "Sets the balance of the mid and sides."
        }},
        { id: 4, config: {
            text: "Makeup Gain",
            text: "Mid Gain",
            min: -100.0,
            max: 24.0,
            mode: "Linear",
            stepSize: 0.1,
            middlePosition: 0,
            defaultValue: 0,
            suffix: " dB",
            tooltip: "Controls the amplitude makeup gain."
        }}
    ],
    
    
    
    
    
    
    
//----------REVVV----------
    "mp3Reverb_ScriptFx": [
        { id: 0, config: { 
        	text: "Delay time", 
        	min: 1.00, 
        	max: 1450.0, 
        	mode: "Linear", 
        	stepSize: 1.0, 
        	middlePosition: 750.0, 
        	defaultValue: 200.0, 
        	suffix: " s", 
        	tooltip: "Controls the reverb delay time." 
        }},
        { id: 1, config: { 
        	text: "Damping", 
        	min: 0.0, 
        	max: 100.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: 50.0, 
        	defaultValue: 50.0, 
        	suffix: "%", 
        	tooltip: "Controls the damping." 
        }},
        { id: 2, config: { 
        	text: "Size", 
        	min: 0.0, 
        	max: 100.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: 50.0, 
        	defaultValue: 50.0, 
        	suffix: "%", 
        	tooltip: "Controls the reverb size." 
        }},
        { id: 3, config: { 
        	text: "Diffusion", 
        	min: 0.0, 
        	max: 100.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: 50.0, 
        	defaultValue: 50.0, 
        	suffix: "%", 
        	tooltip: "Controls the diffusion." 
        }},
		{ id: 4, config: { 
        	text: "Feedback", 
        	min: 0.0, 
        	max: 100.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: 50.0, 
        	defaultValue: 50.0, 
        	suffix: "%", 
        	tooltip: "Controls the feedback." 
        }},
		{ id: 5, config: { 
        	text: "Modulation Depth", 
        	min: 0.0, 
        	max: 100.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: 50.0, 
        	defaultValue: 50.0, 
        	suffix: "%", 
        	tooltip: "Controls the modulation depth." 
        }},
		{ id: 6, config: { 
        	text: "Modulation Rate", 
        	min: 0.0, 
        	max: 10.0, 
        	mode: "Linear", 
        	stepSize: 0.01, 
        	middlePosition: 5.0, 
        	defaultValue: 2.0, 
        	suffix: " Hz", 
        	tooltip: "Controls the modulation rate." 
        }},        
		{ id: 7, config: { 
        	text: "Dry/Wet", 
        	min: 0.0, 
        	max: 100.0, 
        	mode: "Linear", 
        	stepSize: 0.1, 
        	middlePosition: 50.0, 
        	defaultValue: 50.0, 
        	suffix: "%", 
        	tooltip: "Controls the Dry/Wet." 
        }}                         
    ],
    "Reverb": [
        { id: 0, config: { 
        	text: "Dry/Wet", 
        	min: 0.0, 
        	max: 1.0, 
        	mode: "Linear", 
        	stepSize: 0.01, 
        	middlePosition: 0.5, 
        	defaultValue: 0.5, 
        	suffix: "%", 
        	tooltip: "Controls the reverb dry/wet." 
        }},
        { id: 1, config: { 
        	text: "Damping", 
        	min: 0.0, 
        	max: 1.0, 
        	mode: "Linear", 
        	stepSize: 0.01, 
        	middlePosition: 0.5, 
        	defaultValue: 0.5, 
        	suffix: "%", 
        	tooltip: "Controls the damping." 
        }},
        { id: 2, config: { 
        	text: "Width", 
        	min: 0.0, 
        	max: 1.0, 
        	mode: "Linear", 
        	stepSize: 0.01, 
        	middlePosition: 0.5, 
        	defaultValue: 0.5, 
        	suffix: "%", 
        	tooltip: "Controls the reverb width." 
        }},
        { id: 3, config: { 
        	text: "Size", 
        	min: 0.0, 
        	max: 1.0, 
        	mode: "Linear", 
        	stepSize: 0.01, 
        	middlePosition: 0.5, 
        	defaultValue: 0.5, 
        	suffix: "%", 
        	tooltip: "Controls the feedback amount." 
        }}
    ]
    

};
