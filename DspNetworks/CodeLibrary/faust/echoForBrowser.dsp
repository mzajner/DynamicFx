// imported by echo.dsp and echomt.dsp

import("stdfaust.lib");

echo_group(x) = x; // Let layout2.dsp lay us out
   knobs_group(x) = ekg(x);
   switches_group(x)  = esg(x);

dmax = 32768; // one and done 
dmaxs = float(dmax)/48000.0;

Nnines = 1.8; // Increase until you get the desired maximum amount of smoothing when fbs==1
//fastpow2 = ffunction(float fastpow2(float), "fast_pow2.h", "");
fbspr(fbs) = 1.0 - pow(2.0, (-3.33219*Nnines*fbs)); // pole radius of feedback smoother
inputSelect(gi) = _,0 : select2(gi);
echo_mono(dmax,curdel,tapdel,fb,fbspr,gi) = inputSelect(gi) : (+:si.smooth(fbspr)
				   <: de.fdelay(dmax,curdel),
				      de.fdelay(dmax,tapdel))
				      ~(*(fb),!) : !,_;

tau2pole(tau) = ba.if(tau>0, exp(-1.0/(tau*ma.SR)), 0.0);
t60smoother(dEchoT60) = si.smooth(tau2pole(dEchoT60/6.91));

dEchoT60 = knobs_group(vslider("[1] DelayT60 [midi:ctrl 60] [style:knob]", 0.5, 0, 100, 0.001)):si.smoo;
dEchoSamplesRaw = knobs_group(vslider("[0] Delay [midi:ctrl 4] [style:knob]", 0.5, 0.001, (dmaxs-0.001), 0.001)) * ma.SR:si.smoo;
dEchoSamples = dEchoSamplesRaw : t60smoother(dEchoT60);
warpRaw = knobs_group(vslider("[0] Warp [midi:ctrl 62] [style:knob]", 0, -1.0, 1.0, 0.001)):si.smoo;

scrubAmpRaw = 0;

scrubPhaseRaw = 0;
fb = knobs_group(vslider("[2] Feedback [midi:ctrl 3] [style:knob]", .85, 0.0, 0.95, 0.0001)):si.smoo;
amp = knobs_group(vslider("[3] Amp [midi:ctrl 2] [style:knob]", 1, 0, 1, 0.001)) : si.smooth(ba.tau2pole(ampT60/6.91));

ampT60 = 0.15661;
fbs = knobs_group(vslider("[5] [midi:ctrl 76] FeedbackSm [style:knob]", 0.6, 0, 0.6, 0.00001)):si.smoo;
gi = switches_group(1-vslider("[7] [midi:ctrl 105] EnableEcho[style:knob]",1,0,1,1)); // "ground input" switches input to zeros

// Warp and Scrubber stuff:
enableEcho = (scrubAmpRaw > 0.00001);
triggerScrubOn = (enableEcho - enableEcho') > 0;  // enableEcho went 0 to 1
triggerScrubOff = (enableEcho - enableEcho') < 0; // enableEcho went 1 to 0
// Ramps up only during scrub "hold" time and is otherwise zero:
counter = (enableEcho * (triggerScrubOn : + ~ +(1) * enableEcho : -(2))) & (dmax-1);
// implementation that continues scrubbing where it left off:

scrubPhase = scrubPhaseRaw : t60smoother(dEchoT60*(1-triggerScrubOff));
scrubAmp = scrubAmpRaw : t60smoother(dEchoT60*(1-triggerScrubOff));
warp = warpRaw : t60smoother(dEchoT60);
dTapSamplesRaw = dEchoSamplesRaw * (1.0 + warp + scrubPhase * scrubAmp) + float(counter);
dTapSamples = dTapSamplesRaw : t60smoother(dEchoT60*(1-triggerScrubOff));

process = amp * echo_mono(dmax,dEchoSamples,dTapSamples,fb,fbspr(fbs),gi),  amp * echo_mono(dmax,dEchoSamples,dTapSamples,fb,fbspr(fbs),gi);
// This layout loosely follows the MiniMoog-V
// Arturia-only features are labeled
// Original versions also added where different

// Need vrocker and hrocker toggle switches in Faust!
// Need orange and blue color choices
//   Orange => Connect modulation sources to their destinations
//    Blue  => Turn audio sources On and Off
// - and later -
//   White  => Turn performance features On and Off
//   Black  => Select between modulation sources
//   Julius Smith for Analog Devices 3/1/2017

vrocker(x) = checkbox("%%x [style:vrocker]");
hrocker(x) = checkbox("%%x [style:hrocker]");
vrockerblue(x) = checkbox("%x  [style:vrocker] [color:blue]");
vrockerblue(x) = checkbox("%x [style:vrocker] [color:blue]");
 // USAGE: vrockerorange("[0] ModulationEnable");

hrockerblue(x) = checkbox("%%x [style:hrocker] [color:blue]");
vrockerred(x) = checkbox("%%x [style:vrocker] [color:red]");
hrockerred(x) = checkbox("%%x [style:hrocker] [color:red]");

declare designer "Robert A. Moog";

mmg(x) = hgroup("",x); // Minimoog + Effects
  synthg(x) = mmg(vgroup("[0] Minimoog",x));
  fxg(x) = mmg(hgroup("[1] Effects",x));
  mg(x) = synthg(hgroup("[0]",x));
    cg(x) = mg(vgroup("[0] Controllers",x)); // Formerly named "Modules" but "Minimoog" group-title is enough
      vg(x) = cg(hgroup("[0] Master Volume", x));
      dg(x) = cg(hgroup("[1] Oscillator Tuning & Switching", x));
        // Tune knob = master tune
        dsg(x) = dg(vgroup("[1] Switches", x));
	  // Oscillator Modulation HrockerRed => apply Modulation Mix output to osc1&2 pitches
	  // [MOVED here from osc3 group] Osc 3 Control VrockerRed => use osc3 as LFO instead of osc3
      gmmg(x) = cg(hgroup("[2] Glide and ModMix", x));
        // Glide knob [0:10] = portamento speed
        // Modulation Mix knob [0:10] (between Osc3 and Noise) = mix of noise and osc3 modulating osc1&2 pitch and/or VCF freq
    og(x) = mg(vgroup("[1] Oscillator Bank", x));
      osc1(x) = og(hgroup("[1] Oscillator 1", x));
        // UNUSED Control switch (for alignment) - Could put Oscillator Modulation switch there
        // Range rotary switch: LO (slow pulses or rhythm), 32', 16', 8', 4', 2'
        // Frequency <something> switch: LED to right
        // Waveform rotary switch: tri, impulse/bent-triangle, saw, pulseWide, pulseMed, pulseNarrow
      osc2(x) = og(hgroup("[2] Oscillator 2", x));
        // UNUSED (originall) or Osc 2 Control VrockerRed
        // Range rotary switch: LO, 32', 16', 8', 4', 2'
        // Detuning knob: -7 to 7 [NO SWITCH]
        // Waveform rotary switch: tri, impulse(?), saw, pulseWide, pulseMed, pulseNarrow
      osc3(x) = og(hgroup("[3] Oscillator 3", x));
        // Osc 3 Control VrockerRed => use osc3 as LFO instead of osc3
        // Range rotary switch: LO, 32', 16', 8', 4', 2'
        // Detuning knob: -7 to 7 [NO SWITCH]
        // Waveform rotary switch: tri, impulse(?), saw, pulseWide, pulseMed, pulseNarrow
    mixg(x) = mg(vgroup("[2] Mixer", x));
      // Each row 5 slots to maintain alignment and include red rockers joining VCF area:
      mr1(x) = mixg(hgroup("[0] Osc1", x)); // mixer row 1 =
      // Osc1 Volume and Osc1 HrockerBlue & _ & _ & Filter Modulation HrockerRed
      // Filter Modulation => Modulation Mix output to VCF freq
      mr2(x) = mixg(hgroup("[1] Ext In, KeyCtl", x)); // row 2 = Ext In HrockerBlue and Vol and Overload LED and Keyboard Ctl HrockerRed 1
      mr3(x) = mixg(hgroup("[2] Osc2", x)); // = Osc2 Volume and Osc2 HrockerBlue and Keyboard Ctl HrockerRed 2
      // Keyboard Control Modulation 1&2 => 0, 1/3, 2/3, all of Keyboard Control Signal ("gate?") applied to VCF freq
      mr4(x) = mixg(hgroup("[3] Noise", x)); // = Noise HrockerBlue and Volume and Noise Type VrockerBlue
        mr4cbg(x) = mr4(vgroup("[1]", x)); // = Noise Off and White/Pink selection
	// two rockers
      mr5(x) = mixg(hgroup("[4] Osc3", x)); //  Osc3 Volume and Osc3 HrockerBlue
    modg(x) = mg(vgroup("[3] Modifiers", x));
      vcfg(x) = modg(vgroup("[0] Filter", x));
        vcf1(x) = vcfg(hgroup("[0] [tooltip:freq, Q, ContourScale]", x));
	  vcf1cbg(x) = vcf1(vgroup("[0] [tooltip:two checkboxes]", x));
          // Filter Modulation switch
          // VCF Off switch
        // Corner Frequency knob
        // Filter Emphasis knob
        // Amount of Contour knob
        vcf2(x) = vcfg(hgroup("[1] Filter Contour [tooltip:AttFilt, DecFilt, Sustain Level for Filter Contour]", x));
        // Attack Time knob
        // Decay Time knob
        // Sustain Level knob
      ng(x) = modg(hgroup("[1] Loudness Contour", x));
        // Attack Time knob
        // Decay Time knob
        // Sustain Level knob
    echog(x) = fxg(hgroup("[4] Echo",x));
      ekg(x) = echog(vgroup("[0] Knobs",x));
      esg(x) = echog(vgroup("[1] Switches",x));
    flg(x) = fxg(hgroup("[5] Flanger",x));
      flkg(x) = flg(vgroup("[0] Knobs",x));
      flsg(x) = flg(vgroup("[1] Switches",x));
    chg(x) = fxg(hgroup("[6] Chorus",x));
      ckg(x) = chg(vgroup("[0] Knobs",x));
      csg(x) = chg(vgroup("[1] Switches",x));
    rg(x) = fxg(hgroup("[7] Reverb",x));
      rkg(x) = rg(vgroup("[0] Knobs",x));
      rsg(x) = rg(vgroup("[1] Switches",x));
    outg(x) = fxg(vgroup("[8] Output", x));
      volg(x) = outg(hgroup("[0] Volume Main Output", x));
        // Volume knob [0-10]
	// Unison switch (Arturia) or Output connect/disconnect switch (original)
	//   When set, all voices are stacked and instrument is in mono mode
      tunerg(x) = outg(hgroup("[1] A-440 Switch", x));
      vdtpolyg(x) = outg(hgroup("[2] Voice Detune / Poly", x));
        // Voice Detune knob [0-10] (Arturia) or
	// Polyphonic switch [red LED below] (Arturia)
	//   When set, instrument is in polyphonic mode with one oscillator per key
    clipg(x) = fxg(vgroup("[9] Soft Clip", x));
	// Soft Clipping switch [red LED above]
  kg(x) = synthg(hgroup("[1] Keyboard Group", x)); // Keyboard was 3 1/2 octaves
    ws(x) = kg(vgroup("[0] Wheels and Switches", x));
      s1g(x) = ws(hgroup("[0] Jacks and Rockers", x));
        jg(x) = s1g(vgroup("[0] MiniJacks",x));
        gdlg(x) = s1g(vgroup("[1] Glide/Decay/Legato Enables",x)); // Arturia
	// Glide Hrocker (see original Button version below)
	// Decay Hrocker (see original Button version below) => Sets Release (R) of ADSR to either 0 or Decay (R)
	// Legato Hrocker (not in original)
      s2g(x) = ws(hgroup("[1] [tooltip:Wheels+]", x));
        bg(x) = s2g(vgroup("[0] [tooltip:Bend Enable and Range]", x));
        wg(x) = s2g(hgroup("[1] [tooltip:Bend and Mod Wheels]", x));
	// Using Glide/Decay/Legato enables above following Arturia:
	//   dg(x) = s2g(hgroup("[2] Glide and Decay momentary pushbuttons", x));
	//   Glide Button injects portamento as set by Glide knob
	//   Decay Button uses decay of Loudness Contour (else 0)
    keys(x) = kg(hgroup("[1] [tooltip:Keys]", x));
      gg(x) = keys(hgroup("[0] [tooltip: Gates]",x));
      // leave slot 1 open for sustain (below)