#pragma once

#include "RnboReverseDelay.h"
// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace ReverseDelay_impl
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
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, core::gain<NV>>>;

template <int NV>
using tempo_sync_mod = parameter::chain<ranges::Identity, 
                                        parameter::plain<project::RnboReverseDelay<NV>, 0>, 
                                        parameter::plain<project::RnboReverseDelay<NV>, 1>>;

template <int NV>
using tempo_sync_t = wrap::mod<tempo_sync_mod<NV>, 
                               control::tempo_sync<NV>>;

template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<project::RnboReverseDelay<NV>, 3>>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<2, core::gain<NV>>, 
                                  tempo_sync_t<NV>, 
                                  minmax_t<NV>, 
                                  project::RnboReverseDelay<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, chain_t<NV>>, 
                                 chain1_t<NV>>;

namespace ReverseDelay_t_parameters
{
// Parameter list for ReverseDelay_impl::ReverseDelay_t --------------------------------------------

DECLARE_PARAMETER_RANGE_STEP(KnbDryWet_InputRange, 
                             0., 
                             100., 
                             0.01);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<ReverseDelay_impl::xfader_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbDelayTimeFree_InputRange, 
                             0., 
                             5000., 
                             0.430677);
DECLARE_PARAMETER_RANGE_SKEW(KnbDelayTimeFree_0Range, 
                             0., 
                             5000., 
                             0.430677);

template <int NV>
using KnbDelayTimeFree_0 = parameter::from0To1<ReverseDelay_impl::tempo_sync_t<NV>, 
                                               3, 
                                               KnbDelayTimeFree_0Range>;

template <int NV>
using KnbDelayTimeFree = parameter::chain<KnbDelayTimeFree_InputRange, 
                                          KnbDelayTimeFree_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(KnbFeedback_InputRange, 
                             0., 
                             100., 
                             0.1);
DECLARE_PARAMETER_RANGE(KnbFeedback_0Range, 
                        0., 
                        100.);

template <int NV>
using KnbFeedback_0 = parameter::from0To1<project::RnboReverseDelay<NV>, 
                                          2, 
                                          KnbFeedback_0Range>;

template <int NV>
using KnbFeedback = parameter::chain<KnbFeedback_InputRange, KnbFeedback_0<NV>>;

DECLARE_PARAMETER_RANGE_STEP(KnbCrossover_InputRange, 
                             0., 
                             100., 
                             0.1);
template <int NV>
using KnbCrossover_0 = parameter::from0To1<project::RnboReverseDelay<NV>, 
                                           4, 
                                           KnbFeedback_0Range>;

template <int NV>
using KnbCrossover = parameter::chain<KnbCrossover_InputRange, 
                                      KnbCrossover_0<NV>>;

DECLARE_PARAMETER_RANGE(KnbWindow_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbWindow = parameter::chain<KnbWindow_InputRange, 
                                   parameter::plain<ReverseDelay_impl::minmax_t<NV>, 0>>;

template <int NV>
using KnbDelayTimeSync = parameter::plain<ReverseDelay_impl::tempo_sync_t<NV>, 
                                          0>;
template <int NV>
using BtnTempoSync = parameter::plain<ReverseDelay_impl::tempo_sync_t<NV>, 
                                      2>;
template <int NV>
using ReverseDelay_t_plist = parameter::list<KnbDryWet<NV>, 
                                             KnbDelayTimeFree<NV>, 
                                             KnbDelayTimeSync<NV>, 
                                             KnbFeedback<NV>, 
                                             KnbCrossover<NV>, 
                                             KnbWindow<NV>, 
                                             BtnTempoSync<NV>>;
}

template <int NV>
using ReverseDelay_t_ = container::chain<ReverseDelay_t_parameters::ReverseDelay_t_plist<NV>, 
                                         wrap::fix<2, xfader_t<NV>>, 
                                         split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public ReverseDelay_impl::ReverseDelay_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(ReverseDelay);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(134)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x0A3F, 
            0x23D7, 0x5B3C, 0x0001, 0x0000, 0x6E4B, 0x4462, 0x6C65, 0x7961, 
            0x6954, 0x656D, 0x7246, 0x6565, 0x0000, 0x0000, 0x0000, 0x9C40, 
            0x0045, 0x7A00, 0xA344, 0xDC81, 0x003E, 0x8000, 0x5B3F, 0x0002, 
            0x0000, 0x6E4B, 0x4462, 0x6C65, 0x7961, 0x6954, 0x656D, 0x7953, 
            0x636E, 0x0000, 0x0000, 0x0000, 0x9000, 0x0041, 0xA000, 0x0040, 
            0x8000, 0x003F, 0x8000, 0x5B3F, 0x0003, 0x0000, 0x6E4B, 0x4662, 
            0x6565, 0x6264, 0x6361, 0x006B, 0x0000, 0x0000, 0x0000, 0x42C8, 
            0x0000, 0x4248, 0x0000, 0x3F80, 0xCCCD, 0x3DCC, 0x045B, 0x0000, 
            0x4B00, 0x626E, 0x7243, 0x736F, 0x6F73, 0x6576, 0x0072, 0x0000, 
            0x0000, 0x0000, 0x42C8, 0x0000, 0x4248, 0x0000, 0x3F80, 0xCCCD, 
            0x3DCC, 0x055B, 0x0000, 0x4B00, 0x626E, 0x6957, 0x646E, 0x776F, 
            0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0006, 0x0000, 0x7442, 0x546E, 0x6D65, 
            0x6F70, 0x7953, 0x636E, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                           // ReverseDelay_impl::xfader_t<NV>
		auto& split = this->getT(1);                            // ReverseDelay_impl::split_t<NV>
		auto& chain = this->getT(1).getT(0);                    // ReverseDelay_impl::chain_t<NV>
		auto& gain = this->getT(1).getT(0).getT(0);             // core::gain<NV>
		auto& chain1 = this->getT(1).getT(1);                   // ReverseDelay_impl::chain1_t<NV>
		auto& gain1 = this->getT(1).getT(1).getT(0);            // core::gain<NV>
		auto& tempo_sync = this->getT(1).getT(1).getT(1);       // ReverseDelay_impl::tempo_sync_t<NV>
		auto& minmax = this->getT(1).getT(1).getT(2);           // ReverseDelay_impl::minmax_t<NV>
		auto& RnboReverseDelay = this->getT(1).getT(1).getT(3); // project::RnboReverseDelay<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		this->getParameterT(1).connectT(0, tempo_sync); // KnbDelayTimeFree -> tempo_sync::UnsyncedTime
		
		this->getParameterT(2).connectT(0, tempo_sync); // KnbDelayTimeSync -> tempo_sync::Tempo
		
		this->getParameterT(3).connectT(0, RnboReverseDelay); // KnbFeedback -> RnboReverseDelay::KnbFeedback
		
		this->getParameterT(4).connectT(0, RnboReverseDelay); // KnbCrossover -> RnboReverseDelay::KnbCrossFeedback
		
		this->getParameterT(5).connectT(0, minmax); // KnbWindow -> minmax::Value
		
		this->getParameterT(6).connectT(0, tempo_sync); // BtnTempoSync -> tempo_sync::Enabled
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain);                            // xfader -> gain::Gain
		xfader_p.getParameterT(1).connectT(0, gain1);                           // xfader -> gain1::Gain
		tempo_sync.getParameter().connectT(0, RnboReverseDelay);                // tempo_sync -> RnboReverseDelay::KnbDelayTimeLeft
		tempo_sync.getParameter().connectT(1, RnboReverseDelay);                // tempo_sync -> RnboReverseDelay::KnbDelayTimeRight
		minmax.getWrappedObject().getParameter().connectT(0, RnboReverseDelay); // minmax -> RnboReverseDelay::KnbWindowCoefficient
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                // tempo_sync::Tempo is automated
		tempo_sync.setParameterT(1, 1.); // control::tempo_sync::Multiplier
		;                                // tempo_sync::Enabled is automated
		;                                // tempo_sync::UnsyncedTime is automated
		
		;                            // minmax::Value is automated
		minmax.setParameterT(1, 0.); // control::minmax::Minimum
		minmax.setParameterT(2, 1.); // control::minmax::Maximum
		minmax.setParameterT(3, 1.); // control::minmax::Skew
		minmax.setParameterT(4, 0.); // control::minmax::Step
		minmax.setParameterT(5, 0.); // control::minmax::Polarity
		
		;                                         // RnboReverseDelay::KnbDelayTimeLeft is automated
		;                                         // RnboReverseDelay::KnbDelayTimeRight is automated
		;                                         // RnboReverseDelay::KnbFeedback is automated
		;                                         // RnboReverseDelay::KnbWindowCoefficient is automated
		;                                         // RnboReverseDelay::KnbCrossFeedback is automated
		RnboReverseDelay.setParameterT(5, 0.);    // project::RnboReverseDelay::KnbWaveshapeMorph
		RnboReverseDelay.setParameterT(6, 0.);    // project::RnboReverseDelay::KnbWaveshapeFixed
		RnboReverseDelay.setParameterT(7, 0.);    // project::RnboReverseDelay::BtnWaveShapeMorph
		RnboReverseDelay.setParameterT(8, 0.);    // project::RnboReverseDelay::KnbDuty
		RnboReverseDelay.setParameterT(9, 1.);    // project::RnboReverseDelay::BtnEnable
		RnboReverseDelay.setParameterT(10, 50.);  // project::RnboReverseDelay::KnbSmooth
		RnboReverseDelay.setParameterT(11, 0.);   // project::RnboReverseDelay::KnbSmoothWindow
		RnboReverseDelay.setParameterT(12, 100.); // project::RnboReverseDelay::KnbMix
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 1000.);
		this->setParameterT(2, 5.);
		this->setParameterT(3, 50.);
		this->setParameterT(4, 50.);
		this->setParameterT(5, 50.);
		this->setParameterT(6, 0.);
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
using ReverseDelay = wrap::node<ReverseDelay_impl::instance<NV>>;
}


