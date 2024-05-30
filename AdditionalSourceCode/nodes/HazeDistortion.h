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

namespace HazeDistortion_impl
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
using minmax_t = control::minmax<NV, 
                                 parameter::plain<project::FuzzTone<NV>, 0>>;

template <int NV>
using WET_t = container::chain<parameter::empty, 
                               wrap::fix<2, filters::svf<NV>>, 
                               minmax_t<NV>, 
                               project::FuzzTone<NV>, 
                               filters::ladder<NV>, 
                               core::gain<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, DRY_t<NV>>, 
                                 WET_t<NV>>;

namespace HazeDistortion_t_parameters
{
// Parameter list for HazeDistortion_impl::HazeDistortion_t ----------------------------------------

DECLARE_PARAMETER_RANGE(KnbDryWet_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<HazeDistortion_impl::xfader_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbToneRange, 
                             20., 
                             20000., 
                             0.229905);

template <int NV>
using KnbTone = parameter::from0To1<filters::svf<NV>, 
                                    0, 
                                    KnbToneRange>;

DECLARE_PARAMETER_RANGE(KnbHaze_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbHaze = parameter::chain<KnbHaze_InputRange, 
                                 parameter::plain<HazeDistortion_impl::minmax_t<NV>, 0>>;

template <int NV>
using KnbFilter = parameter::from0To1<filters::ladder<NV>, 
                                      0, 
                                      KnbToneRange>;

template <int NV>
using HazeDistortion_t_plist = parameter::list<KnbDryWet<NV>, 
                                               KnbTone<NV>, 
                                               KnbHaze<NV>, 
                                               KnbFilter<NV>>;
}

template <int NV>
using HazeDistortion_t_ = container::chain<HazeDistortion_t_parameters::HazeDistortion_t_plist<NV>, 
                                           wrap::fix<2, xfader_t<NV>>, 
                                           split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public HazeDistortion_impl::HazeDistortion_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(HazeDistortion);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(70)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x5462, 0x6E6F, 0x0065, 
            0x0000, 0x41A0, 0x4000, 0x469C, 0x0000, 0x447A, 0x6C1A, 0x3E6B, 
            0x0000, 0x0000, 0x025B, 0x0000, 0x4B00, 0x626E, 0x6148, 0x657A, 
            0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x6E4B, 0x4662, 0x6C69, 
            0x6574, 0x0072, 0x0000, 0x41A0, 0x4000, 0x469C, 0x0000, 0x447A, 
            0x6C1A, 0x3E6B, 0x0000, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                  // HazeDistortion_impl::xfader_t<NV>
		auto& split = this->getT(1);                   // HazeDistortion_impl::split_t<NV>
		auto& DRY = this->getT(1).getT(0);             // HazeDistortion_impl::DRY_t<NV>
		auto& DryGain = this->getT(1).getT(0).getT(0); // core::gain<NV>
		auto& WET = this->getT(1).getT(1);             // HazeDistortion_impl::WET_t<NV>
		auto& Tone = this->getT(1).getT(1).getT(0);    // filters::svf<NV>
		auto& minmax = this->getT(1).getT(1).getT(1);  // HazeDistortion_impl::minmax_t<NV>
		auto& Fuzz = this->getT(1).getT(1).getT(2);    // project::FuzzTone<NV>
		auto& ladder = this->getT(1).getT(1).getT(3);  // filters::ladder<NV>
		auto& WetGain = this->getT(1).getT(1).getT(4); // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		this->getParameterT(1).connectT(0, Tone); // KnbTone -> Tone::Frequency
		
		this->getParameterT(2).connectT(0, minmax); // KnbHaze -> minmax::Value
		
		this->getParameterT(3).connectT(0, ladder); // KnbFilter -> ladder::Frequency
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, DryGain);             // xfader -> DryGain::Gain
		xfader_p.getParameterT(1).connectT(0, WetGain);             // xfader -> WetGain::Gain
		minmax.getWrappedObject().getParameter().connectT(0, Fuzz); // minmax -> Fuzz::distortion
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                              // DryGain::Gain is automated
		DryGain.setParameterT(1, 20.); // core::gain::Smoothing
		DryGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // Tone::Frequency is automated
		Tone.setParameterT(1, 0.3);  // filters::svf::Q
		Tone.setParameterT(2, 0.);   // filters::svf::Gain
		Tone.setParameterT(3, 0.01); // filters::svf::Smoothing
		Tone.setParameterT(4, 2.);   // filters::svf::Mode
		Tone.setParameterT(5, 1.);   // filters::svf::Enabled
		
		;                              // minmax::Value is automated
		minmax.setParameterT(1, 0.);   // control::minmax::Minimum
		minmax.setParameterT(2, 100.); // control::minmax::Maximum
		minmax.setParameterT(3, 1.);   // control::minmax::Skew
		minmax.setParameterT(4, 0.);   // control::minmax::Step
		minmax.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                          // Fuzz::distortion is automated
		Fuzz.setParameterT(1, 3.); // core::faust::gain
		
		;                                  // ladder::Frequency is automated
		ladder.setParameterT(1, 0.614836); // filters::ladder::Q
		ladder.setParameterT(2, 0.);       // filters::ladder::Gain
		ladder.setParameterT(3, 0.01);     // filters::ladder::Smoothing
		ladder.setParameterT(4, 0.);       // filters::ladder::Mode
		ladder.setParameterT(5, 1.);       // filters::ladder::Enabled
		
		;                              // WetGain::Gain is automated
		WetGain.setParameterT(1, 20.); // core::gain::Smoothing
		WetGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 1000.);
		this->setParameterT(2, 50.);
		this->setParameterT(3, 1000.);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return true; };
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
using HazeDistortion = wrap::node<HazeDistortion_impl::instance<NV>>;
}


