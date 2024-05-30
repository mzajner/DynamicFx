#pragma once

// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace ShredDistortion_impl
{
// ==============================| Node & Parameter type declarations |==============================

DECLARE_PARAMETER_RANGE_SKEW(xfader_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using xfader_c0 = parameter::from0To1<core::gain<NV>, 
                                      0, 
                                      xfader_c0Range>;

template <int NV> using xfader_c1 = xfader_c0<NV>;

template <int NV>
using xfader_multimod = parameter::list<xfader_c0<NV>, xfader_c1<NV>>;

template <int NV>
using xfader_t = control::xfader<xfader_multimod<NV>, faders::rms>;

template <int NV>
using DRY_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>>;

template <int NV>
using minmaxGain_mod = parameter::chain<ranges::Identity, 
                                        parameter::plain<project::GritAmp<NV>, 2>, 
                                        parameter::plain<project::GritAmp<NV>, 2>>;

template <int NV>
using minmaxGain_t = control::minmax<NV, minmaxGain_mod<NV>>;

template <int NV>
using minmaxFrequency_mod = parameter::chain<ranges::Identity, 
                                             parameter::plain<project::GritAmp<NV>, 3>, 
                                             parameter::plain<project::GritAmp<NV>, 3>>;

template <int NV>
using minmaxFrequency_t = control::minmax<NV, 
                                          minmaxFrequency_mod<NV>>;

DECLARE_PARAMETER_RANGE_STEP_INV(minmaxDepth_mod_0Range, 
                                 0., 
                                 1., 
                                 0.001);

template <int NV>
using minmaxDepth_mod_0 = parameter::from0To1_inv<project::GritAmp<NV>, 
                                                  0, 
                                                  minmaxDepth_mod_0Range>;

template <int NV>
using minmaxDepth_mod = parameter::chain<ranges::Identity, 
                                         minmaxDepth_mod_0<NV>, 
                                         parameter::plain<project::GritAmp<NV>, 0>>;

template <int NV>
using minmaxDepth_t = control::minmax<NV, minmaxDepth_mod<NV>>;

template <int NV>
using minmaxGritz_mod = parameter::chain<ranges::Identity, 
                                         parameter::plain<project::GritAmp<NV>, 1>, 
                                         parameter::plain<project::GritAmp<NV>, 1>>;

template <int NV>
using minmaxGritz_t = control::minmax<NV, minmaxGritz_mod<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<1, project::GritAmp<NV>>>;

template <int NV> using chain1_t = chain_t<NV>;

template <int NV>
using multi_t = container::multi<parameter::empty, 
                                 wrap::fix<1, chain_t<NV>>, 
                                 wrap::fix<1, chain1_t<NV>>>;

template <int NV>
using WET_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>, 
                               minmaxGain_t<NV>, 
                               minmaxFrequency_t<NV>, 
                               minmaxDepth_t<NV>, 
                               minmaxGritz_t<NV>, 
                               multi_t<NV>, 
                               core::gain<NV>, 
                               core::gain<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, DRY_t<NV>>, 
                                 WET_t<NV>>;

namespace ShredDistortion_t_parameters
{
// Parameter list for ShredDistortion_impl::ShredDistortion_t --------------------------------------

DECLARE_PARAMETER_RANGE(KnbDryWet_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<ShredDistortion_impl::xfader_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE(KnbDrive_InputRange, 
                        0., 
                        100.);
DECLARE_PARAMETER_RANGE_STEP(KnbDrive_2Range, 
                             -6., 
                             0., 
                             0.1);

template <int NV>
using KnbDrive_2 = parameter::from0To1<core::gain<NV>, 
                                       0, 
                                       KnbDrive_2Range>;

template <int NV>
using KnbDrive = parameter::chain<KnbDrive_InputRange, 
                                  parameter::plain<ShredDistortion_impl::minmaxDepth_t<NV>, 0>, 
                                  parameter::plain<ShredDistortion_impl::minmaxGritz_t<NV>, 0>, 
                                  KnbDrive_2<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbToneFrequency_InputRange, 
                             100., 
                             5000., 
                             0.409034);
DECLARE_PARAMETER_RANGE_SKEW(KnbToneFrequency_0Range, 
                             0., 
                             1., 
                             0.409034);

template <int NV>
using KnbToneFrequency_0 = parameter::from0To1<ShredDistortion_impl::minmaxFrequency_t<NV>, 
                                               0, 
                                               KnbToneFrequency_0Range>;

template <int NV>
using KnbToneFrequency = parameter::chain<KnbToneFrequency_InputRange, 
                                          KnbToneFrequency_0<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbToneGain_InputRange, 
                             -15., 
                             0., 
                             1.35692);
DECLARE_PARAMETER_RANGE_STEP_INV(KnbToneGain_1Range, 
                                 0., 
                                 3., 
                                 0.1);

template <int NV>
using KnbToneGain_1 = parameter::from0To1_inv<core::gain<NV>, 
                                              0, 
                                              KnbToneGain_1Range>;

template <int NV>
using KnbToneGain = parameter::chain<KnbToneGain_InputRange, 
                                     parameter::plain<ShredDistortion_impl::minmaxGain_t<NV>, 0>, 
                                     KnbToneGain_1<NV>>;

template <int NV>
using ShredDistortion_t_plist = parameter::list<KnbDryWet<NV>, 
                                                KnbDrive<NV>, 
                                                KnbToneFrequency<NV>, 
                                                KnbToneGain<NV>>;
}

template <int NV>
using ShredDistortion_t_ = container::chain<ShredDistortion_t_parameters::ShredDistortion_t_plist<NV>, 
                                            wrap::fix<2, xfader_t<NV>>, 
                                            split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public ShredDistortion_impl::ShredDistortion_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(ShredDistortion);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(76)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x8000, 0x003F, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x4462, 0x6972, 0x6576, 
            0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0002, 0x0000, 0x6E4B, 0x5462, 0x6E6F, 
            0x4665, 0x6572, 0x7571, 0x6E65, 0x7963, 0x0000, 0xC800, 0x0042, 
            0x9C40, 0x0045, 0x7A00, 0xE644, 0xD16C, 0x003E, 0x0000, 0x5B00, 
            0x0003, 0x0000, 0x6E4B, 0x5462, 0x6E6F, 0x4765, 0x6961, 0x006E, 
            0x0000, 0xC170, 0x0000, 0x0000, 0x0000, 0xC0C0, 0xAF68, 0x3FAD, 
            0x0000, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                                 // ShredDistortion_impl::xfader_t<NV>
		auto& split = this->getT(1);                                  // ShredDistortion_impl::split_t<NV>
		auto& DRY = this->getT(1).getT(0);                            // ShredDistortion_impl::DRY_t<NV>
		auto& DryGain = this->getT(1).getT(0).getT(0);                // core::gain<NV>
		auto& WET = this->getT(1).getT(1);                            // ShredDistortion_impl::WET_t<NV>
		auto& WetGain = this->getT(1).getT(1).getT(0);                // core::gain<NV>
		auto& minmaxGain = this->getT(1).getT(1).getT(1);             // ShredDistortion_impl::minmaxGain_t<NV>
		auto& minmaxFrequency = this->getT(1).getT(1).getT(2);        // ShredDistortion_impl::minmaxFrequency_t<NV>
		auto& minmaxDepth = this->getT(1).getT(1).getT(3);            // ShredDistortion_impl::minmaxDepth_t<NV>
		auto& minmaxGritz = this->getT(1).getT(1).getT(4);            // ShredDistortion_impl::minmaxGritz_t<NV>
		auto& multi = this->getT(1).getT(1).getT(5);                  // ShredDistortion_impl::multi_t<NV>
		auto& chain = this->getT(1).getT(1).getT(5).getT(0);          // ShredDistortion_impl::chain_t<NV>
		auto& faust = this->getT(1).getT(1).getT(5).getT(0).getT(0);  // project::GritAmp<NV>
		auto& chain1 = this->getT(1).getT(1).getT(5).getT(1);         // ShredDistortion_impl::chain1_t<NV>
		auto& faust1 = this->getT(1).getT(1).getT(5).getT(1).getT(0); // project::GritAmp<NV>
		auto& gain1 = this->getT(1).getT(1).getT(6);                  // core::gain<NV>
		auto& gain = this->getT(1).getT(1).getT(7);                   // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		auto& KnbDrive_p = this->getParameterT(1);
		KnbDrive_p.connectT(0, minmaxDepth); // KnbDrive -> minmaxDepth::Value
		KnbDrive_p.connectT(1, minmaxGritz); // KnbDrive -> minmaxGritz::Value
		KnbDrive_p.connectT(2, gain);        // KnbDrive -> gain::Gain
		
		this->getParameterT(2).connectT(0, minmaxFrequency); // KnbToneFrequency -> minmaxFrequency::Value
		
		auto& KnbToneGain_p = this->getParameterT(3);
		KnbToneGain_p.connectT(0, minmaxGain); // KnbToneGain -> minmaxGain::Value
		KnbToneGain_p.connectT(1, gain1);      // KnbToneGain -> gain1::Gain
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, DryGain);                        // xfader -> DryGain::Gain
		xfader_p.getParameterT(1).connectT(0, WetGain);                        // xfader -> WetGain::Gain
		minmaxGain.getWrappedObject().getParameter().connectT(0, faust);       // minmaxGain -> faust::Tone
		minmaxGain.getWrappedObject().getParameter().connectT(1, faust1);      // minmaxGain -> faust1::Tone
		minmaxFrequency.getWrappedObject().getParameter().connectT(0, faust);  // minmaxFrequency -> faust::ToneFrequency
		minmaxFrequency.getWrappedObject().getParameter().connectT(1, faust1); // minmaxFrequency -> faust1::ToneFrequency
		minmaxDepth.getWrappedObject().getParameter().connectT(0, faust);      // minmaxDepth -> faust::Depth
		minmaxDepth.getWrappedObject().getParameter().connectT(1, faust1);     // minmaxDepth -> faust1::Depth
		minmaxGritz.getWrappedObject().getParameter().connectT(0, faust);      // minmaxGritz -> faust::Gritz
		minmaxGritz.getWrappedObject().getParameter().connectT(1, faust1);     // minmaxGritz -> faust1::Gritz
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                              // DryGain::Gain is automated
		DryGain.setParameterT(1, 20.); // core::gain::Smoothing
		DryGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                              // WetGain::Gain is automated
		WetGain.setParameterT(1, 20.); // core::gain::Smoothing
		WetGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                  // minmaxGain::Value is automated
		minmaxGain.setParameterT(1, -15.); // control::minmax::Minimum
		minmaxGain.setParameterT(2, 0.);   // control::minmax::Maximum
		minmaxGain.setParameterT(3, 1.);   // control::minmax::Skew
		minmaxGain.setParameterT(4, 0.);   // control::minmax::Step
		minmaxGain.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                                        // minmaxFrequency::Value is automated
		minmaxFrequency.setParameterT(1, 100.);  // control::minmax::Minimum
		minmaxFrequency.setParameterT(2, 5000.); // control::minmax::Maximum
		minmaxFrequency.setParameterT(3, 1.);    // control::minmax::Skew
		minmaxFrequency.setParameterT(4, 0.);    // control::minmax::Step
		minmaxFrequency.setParameterT(5, 0.);    // control::minmax::Polarity
		
		;                                 // minmaxDepth::Value is automated
		minmaxDepth.setParameterT(1, 0.); // control::minmax::Minimum
		minmaxDepth.setParameterT(2, 1.); // control::minmax::Maximum
		minmaxDepth.setParameterT(3, 1.); // control::minmax::Skew
		minmaxDepth.setParameterT(4, 0.); // control::minmax::Step
		minmaxDepth.setParameterT(5, 1.); // control::minmax::Polarity
		
		;                                   // minmaxGritz::Value is automated
		minmaxGritz.setParameterT(1, 0.);   // control::minmax::Minimum
		minmaxGritz.setParameterT(2, 100.); // control::minmax::Maximum
		minmaxGritz.setParameterT(3, 1.);   // control::minmax::Skew
		minmaxGritz.setParameterT(4, 0.);   // control::minmax::Step
		minmaxGritz.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                           // faust::Depth is automated
		;                           // faust::Gritz is automated
		;                           // faust::Tone is automated
		;                           // faust::ToneFrequency is automated
		faust.setParameterT(4, 1.); // core::faust::Volume
		
		;                            // faust1::Depth is automated
		;                            // faust1::Gritz is automated
		;                            // faust1::Tone is automated
		;                            // faust1::ToneFrequency is automated
		faust1.setParameterT(4, 1.); // core::faust::Volume
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 1.);
		this->setParameterT(1, 50.);
		this->setParameterT(2, 1000.);
		this->setParameterT(3, -6.);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
};
}

#undef getT
#undef connectT
#undef setParameterT
#undef setParameterWT
#undef getParameterT
// ======================================| Public Definition |======================================

namespace project
{
// polyphonic template declaration

template <int NV>
using ShredDistortion = wrap::node<ShredDistortion_impl::instance<NV>>;
}


