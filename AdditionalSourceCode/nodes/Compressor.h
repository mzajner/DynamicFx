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

namespace Compressor_impl
{
// =============================| Node & Parameter type declarations |=============================

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
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, core::gain<NV>>>;

using faust_multimod = parameter::list<parameter::empty, parameter::empty>;

template <int NV>
using faust_t = project::mp3Compressor<NV, faust_multimod>;
template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<faust_t<NV>, 5>>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<2, core::gain<NV>>, 
                                  minmax_t<NV>, 
                                  faust_t<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, chain_t<NV>>, 
                                 chain1_t<NV>>;

namespace Compressor_t_parameters
{
// Parameter list for Compressor_impl::Compressor_t -----------------------------------------------

DECLARE_PARAMETER_RANGE_STEP(KnbDryWet_InputRange, 
                             0., 
                             100., 
                             0.1);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<Compressor_impl::xfader_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbRatio_InputRange, 
                             1., 
                             20., 
                             0.927642);
DECLARE_PARAMETER_RANGE_SKEW(KnbRatio_0Range, 
                             1, 
                             20., 
                             0.927642);

template <int NV>
using KnbRatio_0 = parameter::from0To1<Compressor_impl::faust_t<NV>, 
                                       1, 
                                       KnbRatio_0Range>;

template <int NV>
using KnbRatio = parameter::chain<KnbRatio_InputRange, KnbRatio_0<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbThresholdRange, 
                             -100., 
                             10., 
                             2.35956);

template <int NV>
using KnbThreshold = parameter::from0To1<Compressor_impl::faust_t<NV>, 
                                         2, 
                                         KnbThresholdRange>;

DECLARE_PARAMETER_RANGE_SKEW(KnbAttack_InputRange, 
                             1., 
                             1000., 
                             0.174935);
DECLARE_PARAMETER_RANGE_SKEW(KnbAttack_0Range, 
                             1., 
                             1000., 
                             0.174935);

template <int NV>
using KnbAttack_0 = parameter::from0To1<Compressor_impl::faust_t<NV>, 
                                        3, 
                                        KnbAttack_0Range>;

template <int NV>
using KnbAttack = parameter::chain<KnbAttack_InputRange, KnbAttack_0<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbRelease_InputRange, 
                             1., 
                             3000., 
                             0.386493);
DECLARE_PARAMETER_RANGE_SKEW(KnbRelease_0Range, 
                             1., 
                             3000., 
                             0.386493);

template <int NV>
using KnbRelease_0 = parameter::from0To1<Compressor_impl::faust_t<NV>, 
                                         4, 
                                         KnbRelease_0Range>;

template <int NV>
using KnbRelease = parameter::chain<KnbRelease_InputRange, KnbRelease_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(KnbMakeUpGain_InputRange, 
                             -12., 
                             12., 
                             0.1);

template <int NV>
using KnbMakeUpGain = parameter::chain<KnbMakeUpGain_InputRange, 
                                       parameter::plain<Compressor_impl::minmax_t<NV>, 0>>;

template <int NV>
using Compressor_t_plist = parameter::list<KnbDryWet<NV>, 
                                           KnbRatio<NV>, 
                                           KnbThreshold<NV>, 
                                           KnbAttack<NV>, 
                                           KnbRelease<NV>, 
                                           KnbMakeUpGain<NV>>;
}

template <int NV>
using Compressor_t_ = container::chain<Compressor_t_parameters::Compressor_t_plist<NV>, 
                                       wrap::fix<2, xfader_t<NV>>, 
                                       split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Compressor_impl::Compressor_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Compressor);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(110)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0xCD3F, 
            0xCCCC, 0x5B3D, 0x0001, 0x0000, 0x6E4B, 0x5262, 0x7461, 0x6F69, 
            0x0000, 0x8000, 0x003F, 0xA000, 0x0041, 0x8000, 0xEC40, 0x6D79, 
            0x0A3F, 0x23D7, 0x5B3C, 0x0002, 0x0000, 0x6E4B, 0x5462, 0x7268, 
            0x7365, 0x6F68, 0x646C, 0x0000, 0xC800, 0x00C2, 0x2000, 0x0041, 
            0x9000, 0x0BC1, 0x1703, 0xCD40, 0xCCCC, 0x5B3D, 0x0003, 0x0000, 
            0x6E4B, 0x4162, 0x7474, 0x6361, 0x006B, 0x0000, 0x3F80, 0x0000, 
            0x447A, 0x0000, 0x3F80, 0x2220, 0x3E33, 0xD70A, 0x3C23, 0x045B, 
            0x0000, 0x4B00, 0x626E, 0x6552, 0x656C, 0x7361, 0x0065, 0x0000, 
            0x3F80, 0x8000, 0x453B, 0x0000, 0x41F0, 0xE265, 0x3EC5, 0x0000, 
            0x3F80, 0x055B, 0x0000, 0x4B00, 0x626E, 0x614D, 0x656B, 0x7055, 
            0x6147, 0x6E69, 0x0000, 0x4000, 0x00C1, 0x4000, 0x0041, 0x4000, 
            0x0026, 0x8000, 0xCD3F, 0xCCCC, 0x003D, 0x0000
		};
	};
	
	instance()
	{
		// Node References ------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                 // Compressor_impl::xfader_t<NV>
		auto& split = this->getT(1);                  // Compressor_impl::split_t<NV>
		auto& chain = this->getT(1).getT(0);          // Compressor_impl::chain_t<NV>
		auto& gain = this->getT(1).getT(0).getT(0);   // core::gain<NV>
		auto& chain1 = this->getT(1).getT(1);         // Compressor_impl::chain1_t<NV>
		auto& gain1 = this->getT(1).getT(1).getT(0);  // core::gain<NV>
		auto& minmax = this->getT(1).getT(1).getT(1); // Compressor_impl::minmax_t<NV>
		auto& faust = this->getT(1).getT(1).getT(2);  // Compressor_impl::faust_t<NV>
		
		// Parameter Connections ------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		this->getParameterT(1).connectT(0, faust); // KnbRatio -> faust::Ratio
		
		this->getParameterT(2).connectT(0, faust); // KnbThreshold -> faust::Threshold
		
		this->getParameterT(3).connectT(0, faust); // KnbAttack -> faust::Attack
		
		this->getParameterT(4).connectT(0, faust); // KnbRelease -> faust::Release
		
		this->getParameterT(5).connectT(0, minmax); // KnbMakeUpGain -> minmax::Value
		
		// Modulation Connections -----------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain);  // xfader -> gain::Gain
		xfader_p.getParameterT(1).connectT(0, gain1); // xfader -> gain1::Gain
		auto& faust_p = faust.getWrappedObject().getParameter();
		minmax.getWrappedObject().getParameter().connectT(0, faust); // minmax -> faust::MakeUpGain
		
		// Default Values -------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                              // minmax::Value is automated
		minmax.setParameterT(1, -12.); // control::minmax::Minimum
		minmax.setParameterT(2, 12.);  // control::minmax::Maximum
		minmax.setParameterT(3, 1.);   // control::minmax::Skew
		minmax.setParameterT(4, 0.);   // control::minmax::Step
		minmax.setParameterT(5, 0.);   // control::minmax::Polarity
		
		faust.setParameterT(0, 0.); // core::faust::Bypass
		;                           // faust::Ratio is automated
		;                           // faust::Threshold is automated
		;                           // faust::Attack is automated
		;                           // faust::Release is automated
		;                           // faust::MakeUpGain is automated
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 4.);
		this->setParameterT(2, -18.);
		this->setParameterT(3, 1.);
		this->setParameterT(4, 30.);
		this->setParameterT(5, 6.66134e-16);
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
using Compressor = wrap::node<Compressor_impl::instance<NV>>;
}


