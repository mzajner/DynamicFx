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

namespace GlistenReverb_impl
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
using minmaxDecay_t = control::minmax<NV, 
                                      parameter::plain<project::AllPassLoopReverb<NV>, 0>>;

template <int NV>
using minmaxShimmer_t = control::minmax<NV, 
                                        parameter::plain<project::AllPassLoopReverb<NV>, 4>>;

template <int NV>
using minmaxPitch_t = control::minmax<NV, 
                                      parameter::plain<project::AllPassLoopReverb<NV>, 5>>;

template <int NV>
using WET_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>, 
                               minmaxDecay_t<NV>, 
                               minmaxShimmer_t<NV>, 
                               minmaxPitch_t<NV>, 
                               project::AllPassLoopReverb<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, DRY_t<NV>>, 
                                 WET_t<NV>>;

namespace GlistenReverb_t_parameters
{
// Parameter list for GlistenReverb_impl::GlistenReverb_t ------------------------------------------

DECLARE_PARAMETER_RANGE(KnbDryWet_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<GlistenReverb_impl::xfader_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE(KnbDecay_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDecay = parameter::chain<KnbDecay_InputRange, 
                                  parameter::plain<GlistenReverb_impl::minmaxDecay_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE(KnbShimmer_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbShimmer = parameter::chain<KnbShimmer_InputRange, 
                                    parameter::plain<GlistenReverb_impl::minmaxShimmer_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE(KnbPitch_InputRange, 
                        -24., 
                        24.);

template <int NV>
using KnbPitch = parameter::chain<KnbPitch_InputRange, 
                                  parameter::plain<GlistenReverb_impl::minmaxPitch_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_STEP(KnbFineTune_InputRange, 
                             -100., 
                             100., 
                             0.01);
DECLARE_PARAMETER_RANGE_STEP(KnbFineTune_0Range, 
                             -1., 
                             1., 
                             0.001);

template <int NV>
using KnbFineTune_0 = parameter::from0To1<project::AllPassLoopReverb<NV>, 
                                          6, 
                                          KnbFineTune_0Range>;

template <int NV>
using KnbFineTune = parameter::chain<KnbFineTune_InputRange, KnbFineTune_0<NV>>;

template <int NV>
using BtnFreeze = parameter::plain<project::AllPassLoopReverb<NV>, 
                                   3>;
template <int NV>
using GlistenReverb_t_plist = parameter::list<KnbDryWet<NV>, 
                                              KnbDecay<NV>, 
                                              KnbShimmer<NV>, 
                                              KnbPitch<NV>, 
                                              KnbFineTune<NV>, 
                                              BtnFreeze<NV>>;
}

template <int NV>
using GlistenReverb_t_ = container::chain<GlistenReverb_t_parameters::GlistenReverb_t_plist<NV>, 
                                          wrap::fix<2, xfader_t<NV>>, 
                                          split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public GlistenReverb_impl::GlistenReverb_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(GlistenReverb);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(106)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x4462, 0x6365, 0x7961, 
            0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0002, 0x0000, 0x6E4B, 0x5362, 0x6968, 
            0x6D6D, 0x7265, 0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 
            0x0042, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x6E4B, 
            0x5062, 0x7469, 0x6863, 0x0000, 0xC000, 0x00C1, 0xC000, 0x0041, 
            0x4000, 0x0041, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0004, 0x0000, 
            0x6E4B, 0x4662, 0x6E69, 0x5465, 0x6E75, 0x0065, 0x0000, 0xC2C8, 
            0x0000, 0x42C8, 0x0000, 0x23C0, 0x0000, 0x3F80, 0xD70A, 0x3C23, 
            0x055B, 0x0000, 0x4200, 0x6E74, 0x7246, 0x6565, 0x657A, 0x0000, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 
            0x8000, 0x003F
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                        // GlistenReverb_impl::xfader_t<NV>
		auto& split = this->getT(1);                         // GlistenReverb_impl::split_t<NV>
		auto& DRY = this->getT(1).getT(0);                   // GlistenReverb_impl::DRY_t<NV>
		auto& DryGain = this->getT(1).getT(0).getT(0);       // core::gain<NV>
		auto& WET = this->getT(1).getT(1);                   // GlistenReverb_impl::WET_t<NV>
		auto& WetGain = this->getT(1).getT(1).getT(0);       // core::gain<NV>
		auto& minmaxDecay = this->getT(1).getT(1).getT(1);   // GlistenReverb_impl::minmaxDecay_t<NV>
		auto& minmaxShimmer = this->getT(1).getT(1).getT(2); // GlistenReverb_impl::minmaxShimmer_t<NV>
		auto& minmaxPitch = this->getT(1).getT(1).getT(3);   // GlistenReverb_impl::minmaxPitch_t<NV>
		auto& faust = this->getT(1).getT(1).getT(4);         // project::AllPassLoopReverb<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		this->getParameterT(1).connectT(0, minmaxDecay); // KnbDecay -> minmaxDecay::Value
		
		this->getParameterT(2).connectT(0, minmaxShimmer); // KnbShimmer -> minmaxShimmer::Value
		
		this->getParameterT(3).connectT(0, minmaxPitch); // KnbPitch -> minmaxPitch::Value
		
		this->getParameterT(4).connectT(0, faust); // KnbFineTune -> faust::FineTune
		
		this->getParameterT(5).connectT(0, faust); // BtnFreeze -> faust::Freeze
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, DryGain);                     // xfader -> DryGain::Gain
		xfader_p.getParameterT(1).connectT(0, WetGain);                     // xfader -> WetGain::Gain
		minmaxDecay.getWrappedObject().getParameter().connectT(0, faust);   // minmaxDecay -> faust::KRTDecay
		minmaxShimmer.getWrappedObject().getParameter().connectT(0, faust); // minmaxShimmer -> faust::Shimmer
		minmaxPitch.getWrappedObject().getParameter().connectT(0, faust);   // minmaxPitch -> faust::Frequency
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                              // DryGain::Gain is automated
		DryGain.setParameterT(1, 20.); // core::gain::Smoothing
		DryGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                              // WetGain::Gain is automated
		WetGain.setParameterT(1, 20.); // core::gain::Smoothing
		WetGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                   // minmaxDecay::Value is automated
		minmaxDecay.setParameterT(1, 0.);   // control::minmax::Minimum
		minmaxDecay.setParameterT(2, 0.75); // control::minmax::Maximum
		minmaxDecay.setParameterT(3, 1.);   // control::minmax::Skew
		minmaxDecay.setParameterT(4, 0.);   // control::minmax::Step
		minmaxDecay.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                                     // minmaxShimmer::Value is automated
		minmaxShimmer.setParameterT(1, 0.);   // control::minmax::Minimum
		minmaxShimmer.setParameterT(2, 0.75); // control::minmax::Maximum
		minmaxShimmer.setParameterT(3, 1.);   // control::minmax::Skew
		minmaxShimmer.setParameterT(4, 0.);   // control::minmax::Step
		minmaxShimmer.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                                   // minmaxPitch::Value is automated
		minmaxPitch.setParameterT(1, -24.); // control::minmax::Minimum
		minmaxPitch.setParameterT(2, 24.);  // control::minmax::Maximum
		minmaxPitch.setParameterT(3, 1.);   // control::minmax::Skew
		minmaxPitch.setParameterT(4, 0.);   // control::minmax::Step
		minmaxPitch.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                            // faust::KRTDecay is automated
		faust.setParameterT(1, 0.1); // core::faust::DrySound
		faust.setParameterT(2, 1.);  // core::faust::ReverbIN
		;                            // faust::Freeze is automated
		;                            // faust::Shimmer is automated
		;                            // faust::Frequency is automated
		;                            // faust::FineTune is automated
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 50.);
		this->setParameterT(2, 50.);
		this->setParameterT(3, 12.);
		this->setParameterT(4, 2.08167e-17);
		this->setParameterT(5, 0.);
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
using GlistenReverb = wrap::node<GlistenReverb_impl::instance<NV>>;
}


