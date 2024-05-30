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

namespace SlapbackDelay_impl
{
// ==============================| Node & Parameter type declarations |==============================

DECLARE_PARAMETER_RANGE_SKEW(dryWetXfade_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using dryWetXfade_c0 = parameter::from0To1<core::gain<NV>, 
                                           0, 
                                           dryWetXfade_c0Range>;

template <int NV> using dryWetXfade_c1 = dryWetXfade_c0<NV>;

template <int NV>
using dryWetXfade_multimod = parameter::list<dryWetXfade_c0<NV>, dryWetXfade_c1<NV>>;

template <int NV>
using dryWetXfade_t = control::xfader<dryWetXfade_multimod<NV>, 
                                      faders::rms>;

template <int NV>
using DRYChain_t = container::chain<parameter::empty, 
                                    wrap::fix<2, core::gain<NV>>>;

template <int NV>
using tempo_sync1_t = wrap::mod<parameter::plain<project::EchoplexDelay<NV>, 0>, 
                                control::tempo_sync<NV>>;

template <int NV>
using minmax1_t = control::minmax<NV, 
                                  parameter::plain<project::EchoplexDelay<NV>, 1>>;

template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<filters::svf<NV>, 4>>;

template <int NV>
using WET_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>, 
                               tempo_sync1_t<NV>, 
                               minmax1_t<NV>, 
                               project::EchoplexDelay<NV>, 
                               minmax_t<NV>, 
                               filters::svf<NV>>;

template <int NV>
using dryWetSplit_t = container::split<parameter::empty, 
                                       wrap::fix<2, DRYChain_t<NV>>, 
                                       WET_t<NV>>;

namespace SlapbackDelay_t_parameters
{
// Parameter list for SlapbackDelay_impl::SlapbackDelay_t ------------------------------------------

DECLARE_PARAMETER_RANGE(KnbDryWet_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<SlapbackDelay_impl::dryWetXfade_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbTimeFree_InputRange, 
                             1., 
                             2000., 
                             0.499459);
DECLARE_PARAMETER_RANGE_SKEW(KnbTimeFree_0Range, 
                             0., 
                             2000., 
                             0.5);

template <int NV>
using KnbTimeFree_0 = parameter::from0To1<SlapbackDelay_impl::tempo_sync1_t<NV>, 
                                          3, 
                                          KnbTimeFree_0Range>;

template <int NV>
using KnbTimeFree = parameter::chain<KnbTimeFree_InputRange, KnbTimeFree_0<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbFeedback_InputRange, 
                             0., 
                             200., 
                             0.5);
DECLARE_PARAMETER_RANGE_SKEW(KnbFeedback_0Range, 
                             0., 
                             1., 
                             0.5);

template <int NV>
using KnbFeedback_0 = parameter::from0To1<SlapbackDelay_impl::minmax1_t<NV>, 
                                          0, 
                                          KnbFeedback_0Range>;

template <int NV>
using KnbFeedback = parameter::chain<KnbFeedback_InputRange, KnbFeedback_0<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbFilterRange, 
                             20., 
                             20000., 
                             0.229905);

template <int NV>
using KnbFilter = parameter::from0To1<filters::svf<NV>, 
                                      0, 
                                      KnbFilterRange>;

DECLARE_PARAMETER_RANGE_STEP(KnbFilterType_InputRange, 
                             0., 
                             2., 
                             1.);

template <int NV>
using KnbFilterType = parameter::chain<KnbFilterType_InputRange, 
                                       parameter::plain<SlapbackDelay_impl::minmax_t<NV>, 0>>;

template <int NV>
using KnbTimeSync = parameter::plain<SlapbackDelay_impl::tempo_sync1_t<NV>, 
                                     0>;
template <int NV>
using BtnTempoSync = parameter::plain<SlapbackDelay_impl::tempo_sync1_t<NV>, 
                                      2>;
template <int NV>
using SlapbackDelay_t_plist = parameter::list<KnbDryWet<NV>, 
                                              KnbTimeFree<NV>, 
                                              KnbFeedback<NV>, 
                                              KnbFilter<NV>, 
                                              KnbTimeSync<NV>, 
                                              KnbFilterType<NV>, 
                                              BtnTempoSync<NV>>;
}

template <int NV>
using SlapbackDelay_t_ = container::chain<SlapbackDelay_t_parameters::SlapbackDelay_t_plist<NV>, 
                                          wrap::fix<2, dryWetXfade_t<NV>>, 
                                          dryWetSplit_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public SlapbackDelay_impl::SlapbackDelay_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(SlapbackDelay);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(130)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x5462, 0x6D69, 0x4665, 
            0x6572, 0x0065, 0x0000, 0x3F80, 0x0000, 0x44FA, 0x0000, 0x437A, 
            0xB914, 0x3EFF, 0x0000, 0x0000, 0x025B, 0x0000, 0x4B00, 0x626E, 
            0x6546, 0x6465, 0x6162, 0x6B63, 0x0000, 0x0000, 0x0000, 0x4800, 
            0x0043, 0x4800, 0x0042, 0x0000, 0x003F, 0x0000, 0x5B00, 0x0003, 
            0x0000, 0x6E4B, 0x4662, 0x6C69, 0x6574, 0x0072, 0x0000, 0x41A0, 
            0x4000, 0x469C, 0x0000, 0x447A, 0x6C1A, 0x3E6B, 0x0000, 0x0000, 
            0x045B, 0x0000, 0x4B00, 0x626E, 0x6954, 0x656D, 0x7953, 0x636E, 
            0x0000, 0x0000, 0x0000, 0x9000, 0x0041, 0xA000, 0x0040, 0x8000, 
            0x003F, 0x8000, 0x5B3F, 0x0005, 0x0000, 0x6E4B, 0x4662, 0x6C69, 
            0x6574, 0x5472, 0x7079, 0x0065, 0x0000, 0x0000, 0x0000, 0x4000, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x065B, 0x0000, 
            0x4200, 0x6E74, 0x6554, 0x706D, 0x536F, 0x6E79, 0x0063, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& dryWetXfade = this->getT(0);                 // SlapbackDelay_impl::dryWetXfade_t<NV>
		auto& dryWetSplit = this->getT(1);                 // SlapbackDelay_impl::dryWetSplit_t<NV>
		auto& DRYChain = this->getT(1).getT(0);            // SlapbackDelay_impl::DRYChain_t<NV>
		auto& gain2 = this->getT(1).getT(0).getT(0);       // core::gain<NV>
		auto& WET = this->getT(1).getT(1);                 // SlapbackDelay_impl::WET_t<NV>
		auto& gain = this->getT(1).getT(1).getT(0);        // core::gain<NV>
		auto& tempo_sync1 = this->getT(1).getT(1).getT(1); // SlapbackDelay_impl::tempo_sync1_t<NV>
		auto& minmax1 = this->getT(1).getT(1).getT(2);     // SlapbackDelay_impl::minmax1_t<NV>
		auto& faust = this->getT(1).getT(1).getT(3);       // project::EchoplexDelay<NV>
		auto& minmax = this->getT(1).getT(1).getT(4);      // SlapbackDelay_impl::minmax_t<NV>
		auto& svf = this->getT(1).getT(1).getT(5);         // filters::svf<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, dryWetXfade); // KnbDryWet -> dryWetXfade::Value
		
		this->getParameterT(1).connectT(0, tempo_sync1); // KnbTimeFree -> tempo_sync1::UnsyncedTime
		
		this->getParameterT(2).connectT(0, minmax1); // KnbFeedback -> minmax1::Value
		
		this->getParameterT(3).connectT(0, svf); // KnbFilter -> svf::Frequency
		
		this->getParameterT(4).connectT(0, tempo_sync1); // KnbTimeSync -> tempo_sync1::Tempo
		
		this->getParameterT(5).connectT(0, minmax); // KnbFilterType -> minmax::Value
		
		this->getParameterT(6).connectT(0, tempo_sync1); // BtnTempoSync -> tempo_sync1::Enabled
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& dryWetXfade_p = dryWetXfade.getWrappedObject().getParameter();
		dryWetXfade_p.getParameterT(0).connectT(0, gain2);            // dryWetXfade -> gain2::Gain
		dryWetXfade_p.getParameterT(1).connectT(0, gain);             // dryWetXfade -> gain::Gain
		tempo_sync1.getParameter().connectT(0, faust);                // tempo_sync1 -> faust::delayms
		minmax1.getWrappedObject().getParameter().connectT(0, faust); // minmax1 -> faust::feedback
		minmax.getWrappedObject().getParameter().connectT(0, svf);    // minmax -> svf::Mode
		
		// Default Values --------------------------------------------------------------------------
		
		; // dryWetXfade::Value is automated
		
		;                            // gain2::Gain is automated
		gain2.setParameterT(1, 20.); // core::gain::Smoothing
		gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                 // tempo_sync1::Tempo is automated
		tempo_sync1.setParameterT(1, 1.); // control::tempo_sync::Multiplier
		;                                 // tempo_sync1::Enabled is automated
		;                                 // tempo_sync1::UnsyncedTime is automated
		
		;                               // minmax1::Value is automated
		minmax1.setParameterT(1, 0.);   // control::minmax::Minimum
		minmax1.setParameterT(2, 1.95); // control::minmax::Maximum
		minmax1.setParameterT(3, 1.);   // control::minmax::Skew
		minmax1.setParameterT(4, 0.);   // control::minmax::Step
		minmax1.setParameterT(5, 0.);   // control::minmax::Polarity
		
		; // faust::delayms is automated
		; // faust::feedback is automated
		
		;                            // minmax::Value is automated
		minmax.setParameterT(1, 0.); // control::minmax::Minimum
		minmax.setParameterT(2, 2.); // control::minmax::Maximum
		minmax.setParameterT(3, 1.); // control::minmax::Skew
		minmax.setParameterT(4, 1.); // control::minmax::Step
		minmax.setParameterT(5, 0.); // control::minmax::Polarity
		
		;                           // svf::Frequency is automated
		svf.setParameterT(1, 1.);   // filters::svf::Q
		svf.setParameterT(2, 0.);   // filters::svf::Gain
		svf.setParameterT(3, 0.01); // filters::svf::Smoothing
		;                           // svf::Mode is automated
		svf.setParameterT(5, 1.);   // filters::svf::Enabled
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 250.);
		this->setParameterT(2, 50.);
		this->setParameterT(3, 1000.);
		this->setParameterT(4, 5.);
		this->setParameterT(5, 0.);
		this->setParameterT(6, 0.);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool isProcessingHiseEvent() { return true; };
	
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
using SlapbackDelay = wrap::node<SlapbackDelay_impl::instance<NV>>;
}


