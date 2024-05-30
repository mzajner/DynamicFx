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

namespace InfiniteReverb_impl
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
using Dry_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>>;

template <int NV>
using smoothed_parameter_unscaled_t = wrap::mod<parameter::plain<project::mp3Reverb<NV>, 3>, 
                                                control::smoothed_parameter_unscaled<NV, smoothers::linear_ramp<NV>>>;
template <int NV>
using minmax1_t = control::minmax<NV, 
                                  parameter::plain<smoothed_parameter_unscaled_t<NV>, 0>>;

template <int NV>
using smoothed_parameter_unscaled1_t = wrap::mod<parameter::plain<project::mp3Reverb<NV>, 4>, 
                                                 control::smoothed_parameter_unscaled<NV, smoothers::linear_ramp<NV>>>;
template <int NV>
using minmax2_t = control::minmax<NV, 
                                  parameter::plain<smoothed_parameter_unscaled1_t<NV>, 0>>;

template <int NV>
using smoothed_parameter_unscaled2_t = wrap::mod<parameter::plain<project::mp3Reverb<NV>, 5>, 
                                                 control::smoothed_parameter_unscaled<NV, smoothers::linear_ramp<NV>>>;
template <int NV>
using minmax3_t = control::minmax<NV, 
                                  parameter::plain<smoothed_parameter_unscaled2_t<NV>, 0>>;

template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<project::mp3Reverb<NV>, 6>>;

template <int NV>
using Wet_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>, 
                               minmax1_t<NV>, 
                               smoothed_parameter_unscaled_t<NV>, 
                               minmax2_t<NV>, 
                               smoothed_parameter_unscaled1_t<NV>, 
                               minmax3_t<NV>, 
                               smoothed_parameter_unscaled2_t<NV>, 
                               minmax_t<NV>, 
                               project::mp3Reverb<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, Dry_t<NV>>, 
                                 Wet_t<NV>>;

namespace InfiniteReverb_t_parameters
{
// Parameter list for InfiniteReverb_impl::InfiniteReverb_t ----------------------------------------

DECLARE_PARAMETER_RANGE_STEP(KnbDryWet_InputRange, 
                             0., 
                             100., 
                             0.1);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<InfiniteReverb_impl::xfader_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_STEP(KnbSize_InputRange, 
                             0., 
                             100., 
                             0.1);
DECLARE_PARAMETER_RANGE(KnbSize_0Range, 
                        0.5, 
                        3.);

template <int NV>
using KnbSize_0 = parameter::from0To1<project::mp3Reverb<NV>, 
                                      2, 
                                      KnbSize_0Range>;

template <int NV>
using KnbSize = parameter::chain<KnbSize_InputRange, KnbSize_0<NV>>;

DECLARE_PARAMETER_RANGE(KnbDamp_InputRange, 
                        0., 
                        100.);
DECLARE_PARAMETER_RANGE_STEP(KnbDamp_0Range, 
                             0., 
                             0.99, 
                             0.001);

template <int NV>
using KnbDamp_0 = parameter::from0To1<project::mp3Reverb<NV>, 
                                      1, 
                                      KnbDamp_0Range>;

template <int NV>
using KnbDamp = parameter::chain<KnbDamp_InputRange, KnbDamp_0<NV>>;

DECLARE_PARAMETER_RANGE(KnabDiffusion_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnabDiffusion = parameter::chain<KnabDiffusion_InputRange, 
                                       parameter::plain<InfiniteReverb_impl::minmax1_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_STEP(KnbDepth_InputRange, 
                             0., 
                             100., 
                             0.01);

template <int NV>
using KnbDepth = parameter::chain<KnbDepth_InputRange, 
                                  parameter::plain<InfiniteReverb_impl::minmax2_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbModFreq_InputRange, 
                             0., 
                             10., 
                             0.30103);
DECLARE_PARAMETER_RANGE_SKEW(KnbModFreq_0Range, 
                             0., 
                             1., 
                             0.30103);

template <int NV>
using KnbModFreq_0 = parameter::from0To1<InfiniteReverb_impl::minmax_t<NV>, 
                                         0, 
                                         KnbModFreq_0Range>;

template <int NV>
using KnbModFreq = parameter::chain<KnbModFreq_InputRange, KnbModFreq_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(KnbModDepth_InputRange, 
                             0., 
                             100., 
                             0.01);

template <int NV>
using KnbModDepth = parameter::chain<KnbModDepth_InputRange, 
                                     parameter::plain<InfiniteReverb_impl::minmax3_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(dKnbDelayTime_InputRange, 
                             0., 
                             1450., 
                             0.30103);
DECLARE_PARAMETER_RANGE(dKnbDelayTime_0Range, 
                        0.001, 
                        1.45);

template <int NV>
using dKnbDelayTime_0 = parameter::from0To1<project::mp3Reverb<NV>, 
                                            0, 
                                            dKnbDelayTime_0Range>;

template <int NV>
using dKnbDelayTime = parameter::chain<dKnbDelayTime_InputRange, 
                                       dKnbDelayTime_0<NV>>;

template <int NV>
using InfiniteReverb_t_plist = parameter::list<KnbDryWet<NV>, 
                                               KnbSize<NV>, 
                                               KnbDamp<NV>, 
                                               KnabDiffusion<NV>, 
                                               KnbDepth<NV>, 
                                               KnbModFreq<NV>, 
                                               KnbModDepth<NV>, 
                                               dKnbDelayTime<NV>>;
}

template <int NV>
using InfiniteReverb_t_ = container::chain<InfiniteReverb_t_parameters::InfiniteReverb_t_plist<NV>, 
                                           wrap::fix<2, xfader_t<NV>>, 
                                           split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public InfiniteReverb_impl::InfiniteReverb_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(InfiniteReverb);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(144)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0xCD3F, 
            0xCCCC, 0x5B3D, 0x0001, 0x0000, 0x6E4B, 0x5362, 0x7A69, 0x0065, 
            0x0000, 0x0000, 0x0000, 0x42C8, 0x0000, 0x4248, 0x0000, 0x3F80, 
            0xCCCD, 0x3DCC, 0x025B, 0x0000, 0x4B00, 0x626E, 0x6144, 0x706D, 
            0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x6E4B, 0x6261, 0x6944, 
            0x6666, 0x7375, 0x6F69, 0x006E, 0x0000, 0x0000, 0x0000, 0x42C8, 
            0x0000, 0x4248, 0x0000, 0x3F80, 0x0000, 0x0000, 0x045B, 0x0000, 
            0x4B00, 0x626E, 0x6544, 0x7470, 0x0068, 0x0000, 0x0000, 0x0000, 
            0x42C8, 0x0000, 0x4248, 0x0000, 0x3F80, 0xD70A, 0x3C23, 0x055B, 
            0x0000, 0x4B00, 0x626E, 0x6F4D, 0x4664, 0x6572, 0x0071, 0x0000, 
            0x0000, 0x0000, 0x4120, 0x0000, 0x3F80, 0x209B, 0x3E9A, 0xD70A, 
            0x3C23, 0x065B, 0x0000, 0x4B00, 0x626E, 0x6F4D, 0x4464, 0x7065, 
            0x6874, 0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 
            0x8000, 0x0A3F, 0x23D7, 0x5B3C, 0x0007, 0x0000, 0x4B64, 0x626E, 
            0x6544, 0x616C, 0x5479, 0x6D69, 0x0065, 0x0000, 0x0000, 0x4000, 
            0x44B5, 0x0000, 0x4311, 0x209B, 0x3E9A, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                                       // InfiniteReverb_impl::xfader_t<NV>
		auto& split = this->getT(1);                                        // InfiniteReverb_impl::split_t<NV>
		auto& Dry = this->getT(1).getT(0);                                  // InfiniteReverb_impl::Dry_t<NV>
		auto& gain = this->getT(1).getT(0).getT(0);                         // core::gain<NV>
		auto& Wet = this->getT(1).getT(1);                                  // InfiniteReverb_impl::Wet_t<NV>
		auto& gain1 = this->getT(1).getT(1).getT(0);                        // core::gain<NV>
		auto& minmax1 = this->getT(1).getT(1).getT(1);                      // InfiniteReverb_impl::minmax1_t<NV>
		auto& smoothed_parameter_unscaled = this->getT(1).getT(1).getT(2);  // InfiniteReverb_impl::smoothed_parameter_unscaled_t<NV>
		auto& minmax2 = this->getT(1).getT(1).getT(3);                      // InfiniteReverb_impl::minmax2_t<NV>
		auto& smoothed_parameter_unscaled1 = this->getT(1).getT(1).getT(4); // InfiniteReverb_impl::smoothed_parameter_unscaled1_t<NV>
		auto& minmax3 = this->getT(1).getT(1).getT(5);                      // InfiniteReverb_impl::minmax3_t<NV>
		auto& smoothed_parameter_unscaled2 = this->getT(1).getT(1).getT(6); // InfiniteReverb_impl::smoothed_parameter_unscaled2_t<NV>
		auto& minmax = this->getT(1).getT(1).getT(7);                       // InfiniteReverb_impl::minmax_t<NV>
		auto& faust = this->getT(1).getT(1).getT(8);                        // project::mp3Reverb<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		this->getParameterT(1).connectT(0, faust); // KnbSize -> faust::size
		
		this->getParameterT(2).connectT(0, faust); // KnbDamp -> faust::damping
		
		this->getParameterT(3).connectT(0, minmax1); // KnabDiffusion -> minmax1::Value
		
		this->getParameterT(4).connectT(0, minmax2); // KnbDepth -> minmax2::Value
		
		this->getParameterT(5).connectT(0, minmax); // KnbModFreq -> minmax::Value
		
		this->getParameterT(6).connectT(0, minmax3); // KnbModDepth -> minmax3::Value
		
		this->getParameterT(7).connectT(0, faust); // dKnbDelayTime -> faust::delayTime
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain);                                         // xfader -> gain::Gain
		xfader_p.getParameterT(1).connectT(0, gain1);                                        // xfader -> gain1::Gain
		smoothed_parameter_unscaled.getParameter().connectT(0, faust);                       // smoothed_parameter_unscaled -> faust::diffusion
		minmax1.getWrappedObject().getParameter().connectT(0, smoothed_parameter_unscaled);  // minmax1 -> smoothed_parameter_unscaled::Value
		smoothed_parameter_unscaled1.getParameter().connectT(0, faust);                      // smoothed_parameter_unscaled1 -> faust::feedback
		minmax2.getWrappedObject().getParameter().connectT(0, smoothed_parameter_unscaled1); // minmax2 -> smoothed_parameter_unscaled1::Value
		smoothed_parameter_unscaled2.getParameter().connectT(0, faust);                      // smoothed_parameter_unscaled2 -> faust::modDepth
		minmax3.getWrappedObject().getParameter().connectT(0, smoothed_parameter_unscaled2); // minmax3 -> smoothed_parameter_unscaled2::Value
		minmax.getWrappedObject().getParameter().connectT(0, faust);                         // minmax -> faust::modFreq
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                             // minmax1::Value is automated
		minmax1.setParameterT(1, 0.); // control::minmax::Minimum
		minmax1.setParameterT(2, 1.); // control::minmax::Maximum
		minmax1.setParameterT(3, 1.); // control::minmax::Skew
		minmax1.setParameterT(4, 0.); // control::minmax::Step
		minmax1.setParameterT(5, 0.); // control::minmax::Polarity
		
		;                                                   // smoothed_parameter_unscaled::Value is automated
		smoothed_parameter_unscaled.setParameterT(1, 100.); // control::smoothed_parameter_unscaled::SmoothingTime
		smoothed_parameter_unscaled.setParameterT(2, 1.);   // control::smoothed_parameter_unscaled::Enabled
		
		;                               // minmax2::Value is automated
		minmax2.setParameterT(1, 0.);   // control::minmax::Minimum
		minmax2.setParameterT(2, 0.99); // control::minmax::Maximum
		minmax2.setParameterT(3, 1.);   // control::minmax::Skew
		minmax2.setParameterT(4, 0.);   // control::minmax::Step
		minmax2.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                                                    // smoothed_parameter_unscaled1::Value is automated
		smoothed_parameter_unscaled1.setParameterT(1, 100.); // control::smoothed_parameter_unscaled::SmoothingTime
		smoothed_parameter_unscaled1.setParameterT(2, 1.);   // control::smoothed_parameter_unscaled::Enabled
		
		;                               // minmax3::Value is automated
		minmax3.setParameterT(1, 0.);   // control::minmax::Minimum
		minmax3.setParameterT(2, 0.99); // control::minmax::Maximum
		minmax3.setParameterT(3, 1.);   // control::minmax::Skew
		minmax3.setParameterT(4, 0.);   // control::minmax::Step
		minmax3.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                                                    // smoothed_parameter_unscaled2::Value is automated
		smoothed_parameter_unscaled2.setParameterT(1, 100.); // control::smoothed_parameter_unscaled::SmoothingTime
		smoothed_parameter_unscaled2.setParameterT(2, 1.);   // control::smoothed_parameter_unscaled::Enabled
		
		;                             // minmax::Value is automated
		minmax.setParameterT(1, 0.);  // control::minmax::Minimum
		minmax.setParameterT(2, 10.); // control::minmax::Maximum
		minmax.setParameterT(3, 1.);  // control::minmax::Skew
		minmax.setParameterT(4, 0.);  // control::minmax::Step
		minmax.setParameterT(5, 0.);  // control::minmax::Polarity
		
		; // faust::delayTime is automated
		; // faust::damping is automated
		; // faust::size is automated
		; // faust::diffusion is automated
		; // faust::feedback is automated
		; // faust::modDepth is automated
		; // faust::modFreq is automated
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 50.);
		this->setParameterT(2, 50.);
		this->setParameterT(3, 50.);
		this->setParameterT(4, 50.);
		this->setParameterT(5, 1.);
		this->setParameterT(6, 50.);
		this->setParameterT(7, 145.);
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
using InfiniteReverb = wrap::node<InfiniteReverb_impl::instance<NV>>;
}


