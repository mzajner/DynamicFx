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

namespace Grains_impl
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
using minmax_Probability_t = control::minmax<NV, 
                                             parameter::plain<project::granulator<NV>, 2>>;

template <int NV>
using minmax_GrainSize_t = control::minmax<NV, 
                                           parameter::plain<project::granulator<NV>, 0>>;

template <int NV>
using converter_t = control::converter<parameter::plain<project::granulator<NV>, 1>, 
                                       conversion_logic::ms2freq>;
template <int NV>
using tempo_sync1_t = wrap::mod<parameter::plain<converter_t<NV>, 0>, 
                                control::tempo_sync<NV>>;
template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<tempo_sync1_t<NV>, 3>>;

template <int NV>
using WET_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>, 
                               minmax_Probability_t<NV>, 
                               minmax_GrainSize_t<NV>, 
                               minmax_t<NV>, 
                               tempo_sync1_t<NV>, 
                               converter_t<NV>, 
                               project::granulator<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, DRY_t<NV>>, 
                                 WET_t<NV>>;

namespace Grains_t_parameters
{
// Parameter list for Grains_impl::Grains_t --------------------------------------------------------

DECLARE_PARAMETER_RANGE(KnbDryWet_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<Grains_impl::xfader_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbTimeFree_InputRange, 
                             50., 
                             1000., 
                             0.927642);

template <int NV>
using KnbTimeFree = parameter::chain<KnbTimeFree_InputRange, 
                                     parameter::plain<Grains_impl::minmax_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE(KnbSize_InputRange, 
                        1., 
                        100.);

template <int NV>
using KnbSize = parameter::chain<KnbSize_InputRange, 
                                 parameter::plain<Grains_impl::minmax_GrainSize_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_STEP(KnbProbability_InputRange, 
                             20., 
                             100., 
                             1.);

template <int NV>
using KnbProbability = parameter::chain<KnbProbability_InputRange, 
                                        parameter::plain<Grains_impl::minmax_Probability_t<NV>, 0>>;

template <int NV>
using KnbTimeSync = parameter::plain<Grains_impl::tempo_sync1_t<NV>, 
                                     0>;
template <int NV>
using BtnTempoSync = parameter::plain<Grains_impl::tempo_sync1_t<NV>, 
                                      2>;
template <int NV>
using Grains_t_plist = parameter::list<KnbDryWet<NV>, 
                                       KnbTimeFree<NV>, 
                                       KnbSize<NV>, 
                                       KnbProbability<NV>, 
                                       KnbTimeSync<NV>, 
                                       BtnTempoSync<NV>>;
}

template <int NV>
using Grains_t_ = container::chain<Grains_t_parameters::Grains_t_plist<NV>, 
                                   wrap::fix<2, xfader_t<NV>>, 
                                   split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Grains_impl::Grains_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Grains);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(112)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x5462, 0x6D69, 0x4665, 
            0x6572, 0x0065, 0x0000, 0x4248, 0x0000, 0x447A, 0x0000, 0x43FA, 
            0x79EC, 0x3F6D, 0x0000, 0x3F80, 0x025B, 0x0000, 0x4B00, 0x626E, 
            0x6953, 0x657A, 0x0000, 0x8000, 0x003F, 0xC800, 0x0042, 0x4800, 
            0x0042, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x6E4B, 
            0x5062, 0x6F72, 0x6162, 0x6962, 0x696C, 0x7974, 0x0000, 0xA000, 
            0x0041, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 0x8000, 
            0x5B3F, 0x0004, 0x0000, 0x6E4B, 0x5462, 0x6D69, 0x5365, 0x6E79, 
            0x0063, 0x0000, 0x0000, 0x0000, 0x4190, 0x0000, 0x40A0, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x055B, 0x0000, 0x4200, 0x6E74, 0x6554, 
            0x706D, 0x536F, 0x6E79, 0x0063, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                             // Grains_impl::xfader_t<NV>
		auto& split = this->getT(1);                              // Grains_impl::split_t<NV>
		auto& DRY = this->getT(1).getT(0);                        // Grains_impl::DRY_t<NV>
		auto& DryGain = this->getT(1).getT(0).getT(0);            // core::gain<NV>
		auto& WET = this->getT(1).getT(1);                        // Grains_impl::WET_t<NV>
		auto& WetGain = this->getT(1).getT(1).getT(0);            // core::gain<NV>
		auto& minmax_Probability = this->getT(1).getT(1).getT(1); // Grains_impl::minmax_Probability_t<NV>
		auto& minmax_GrainSize = this->getT(1).getT(1).getT(2);   // Grains_impl::minmax_GrainSize_t<NV>
		auto& minmax = this->getT(1).getT(1).getT(3);             // Grains_impl::minmax_t<NV>
		auto& tempo_sync1 = this->getT(1).getT(1).getT(4);        // Grains_impl::tempo_sync1_t<NV>
		auto& converter = this->getT(1).getT(1).getT(5);          // Grains_impl::converter_t<NV>
		auto& faust = this->getT(1).getT(1).getT(6);              // project::granulator<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		this->getParameterT(1).connectT(0, minmax); // KnbTimeFree -> minmax::Value
		
		this->getParameterT(2).connectT(0, minmax_GrainSize); // KnbSize -> minmax_GrainSize::Value
		
		this->getParameterT(3).connectT(0, minmax_Probability); // KnbProbability -> minmax_Probability::Value
		
		this->getParameterT(4).connectT(0, tempo_sync1); // KnbTimeSync -> tempo_sync1::Tempo
		
		this->getParameterT(5).connectT(0, tempo_sync1); // BtnTempoSync -> tempo_sync1::Enabled
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, DryGain);                          // xfader -> DryGain::Gain
		xfader_p.getParameterT(1).connectT(0, WetGain);                          // xfader -> WetGain::Gain
		minmax_Probability.getWrappedObject().getParameter().connectT(0, faust); // minmax_Probability -> faust::Probability
		minmax_GrainSize.getWrappedObject().getParameter().connectT(0, faust);   // minmax_GrainSize -> faust::GrainSize
		converter.getWrappedObject().getParameter().connectT(0, faust);          // converter -> faust::Speed
		tempo_sync1.getParameter().connectT(0, converter);                       // tempo_sync1 -> converter::Value
		minmax.getWrappedObject().getParameter().connectT(0, tempo_sync1);       // minmax -> tempo_sync1::UnsyncedTime
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                              // DryGain::Gain is automated
		DryGain.setParameterT(1, 20.); // core::gain::Smoothing
		DryGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                              // WetGain::Gain is automated
		WetGain.setParameterT(1, 20.); // core::gain::Smoothing
		WetGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                          // minmax_Probability::Value is automated
		minmax_Probability.setParameterT(1, 0.);   // control::minmax::Minimum
		minmax_Probability.setParameterT(2, 100.); // control::minmax::Maximum
		minmax_Probability.setParameterT(3, 1.);   // control::minmax::Skew
		minmax_Probability.setParameterT(4, 0.);   // control::minmax::Step
		minmax_Probability.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                                         // minmax_GrainSize::Value is automated
		minmax_GrainSize.setParameterT(1, 0.);    // control::minmax::Minimum
		minmax_GrainSize.setParameterT(2, 2200.); // control::minmax::Maximum
		minmax_GrainSize.setParameterT(3, 1.);    // control::minmax::Skew
		minmax_GrainSize.setParameterT(4, 0.);    // control::minmax::Step
		minmax_GrainSize.setParameterT(5, 0.);    // control::minmax::Polarity
		
		;                               // minmax::Value is automated
		minmax.setParameterT(1, 0.);    // control::minmax::Minimum
		minmax.setParameterT(2, 1000.); // control::minmax::Maximum
		minmax.setParameterT(3, 1.);    // control::minmax::Skew
		minmax.setParameterT(4, 0.);    // control::minmax::Step
		minmax.setParameterT(5, 0.);    // control::minmax::Polarity
		
		;                                 // tempo_sync1::Tempo is automated
		tempo_sync1.setParameterT(1, 1.); // control::tempo_sync::Multiplier
		;                                 // tempo_sync1::Enabled is automated
		;                                 // tempo_sync1::UnsyncedTime is automated
		
		; // converter::Value is automated
		
		; // faust::GrainSize is automated
		; // faust::Speed is automated
		; // faust::Probability is automated
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 500.);
		this->setParameterT(2, 50.);
		this->setParameterT(3, 50.);
		this->setParameterT(4, 5.);
		this->setParameterT(5, 0.);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool isProcessingHiseEvent() { return true; };
	
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
using Grains = wrap::node<Grains_impl::instance<NV>>;
}


