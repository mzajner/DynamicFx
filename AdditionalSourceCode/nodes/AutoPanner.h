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

namespace AutoPanner_impl
{
// ==============================| Node & Parameter type declarations |==============================

DECLARE_PARAMETER_RANGE_SKEW(drywet_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using drywet_c0 = parameter::from0To1<core::gain<NV>, 
                                      0, 
                                      drywet_c0Range>;

template <int NV> using drywet_c1 = drywet_c0<NV>;

template <int NV>
using drywet_multimod = parameter::list<drywet_c0<NV>, drywet_c1<NV>>;

template <int NV>
using drywet_t = control::xfader<drywet_multimod<NV>, faders::rms>;

template <int NV>
using dry_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>>;

template <int NV>
using oscillator1_t = wrap::no_data<core::oscillator<NV>>;
template <int NV>
using converter_t = control::converter<parameter::plain<oscillator1_t<NV>, 1>, 
                                       conversion_logic::ms2freq>;
template <int NV>
using tempo_sync_t = wrap::mod<parameter::plain<converter_t<NV>, 0>, 
                               control::tempo_sync<NV>>;

DECLARE_PARAMETER_RANGE(smoothed_parameter_modRange, 
                        -1., 
                        1.);

template <int NV>
using smoothed_parameter_mod = parameter::from0To1<jdsp::jpanner<NV>, 
                                                   0, 
                                                   smoothed_parameter_modRange>;

template <int NV>
using smoothed_parameter_t = wrap::mod<smoothed_parameter_mod<NV>, 
                                       control::smoothed_parameter<NV, smoothers::linear_ramp<NV>>>;
template <int NV>
using peak1_t = wrap::mod<parameter::plain<smoothed_parameter_t<NV>, 0>, 
                          wrap::no_data<core::peak>>;

template <int NV>
using modchain1_t_ = container::chain<parameter::empty, 
                                      wrap::fix<1, oscillator1_t<NV>>, 
                                      math::sig2mod<NV>, 
                                      peak1_t<NV>>;

template <int NV>
using modchain1_t = wrap::control_rate<modchain1_t_<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, smoothed_parameter_t<NV>>, 
                                 jdsp::jpanner<NV>>;

template <int NV>
using multi_t = container::multi<parameter::empty, 
                                 wrap::fix<2, chain_t<NV>>>;

template <int NV>
using wet_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>, 
                               tempo_sync_t<NV>, 
                               converter_t<NV>, 
                               modchain1_t<NV>, 
                               multi_t<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, dry_t<NV>>, 
                                 wet_t<NV>>;

namespace AutoPanner_t_parameters
{
// Parameter list for AutoPanner_impl::AutoPanner_t ------------------------------------------------

DECLARE_PARAMETER_RANGE_STEP(KnbDryWet_InputRange, 
                             0., 
                             100., 
                             0.1);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<AutoPanner_impl::drywet_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbRateFree_InputRange, 
                             150., 
                             5000., 
                             0.956641);
DECLARE_PARAMETER_RANGE_SKEW(KnbRateFree_0Range, 
                             150., 
                             5000., 
                             0.956641);

template <int NV>
using KnbRateFree_0 = parameter::from0To1<AutoPanner_impl::tempo_sync_t<NV>, 
                                          3, 
                                          KnbRateFree_0Range>;

template <int NV>
using KnbRateFree = parameter::chain<KnbRateFree_InputRange, KnbRateFree_0<NV>>;

DECLARE_PARAMETER_RANGE(KnbDepth_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDepth = parameter::chain<KnbDepth_InputRange, 
                                  parameter::plain<AutoPanner_impl::oscillator1_t<NV>, 5>>;

template <int NV>
using KnbRateSync = parameter::plain<AutoPanner_impl::tempo_sync_t<NV>, 
                                     0>;
using KnbWaveform = parameter::empty;
template <int NV>
using BtnTempoSync = parameter::plain<AutoPanner_impl::tempo_sync_t<NV>, 
                                      2>;
template <int NV>
using AutoPanner_t_plist = parameter::list<KnbDryWet<NV>, 
                                           KnbRateFree<NV>, 
                                           KnbRateSync<NV>, 
                                           KnbWaveform, 
                                           KnbDepth<NV>, 
                                           BtnTempoSync<NV>>;
}

template <int NV>
using AutoPanner_t_ = container::chain<AutoPanner_t_parameters::AutoPanner_t_plist<NV>, 
                                       wrap::fix<2, drywet_t<NV>>, 
                                       split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public AutoPanner_impl::AutoPanner_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(AutoPanner);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(110)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0xCD3F, 
            0xCCCC, 0x5B3D, 0x0001, 0x0000, 0x6E4B, 0x5262, 0x7461, 0x4665, 
            0x6572, 0x0065, 0x0000, 0x4316, 0x4000, 0x459C, 0x4000, 0x451C, 
            0xE670, 0x3F74, 0x0000, 0x3F80, 0x025B, 0x0000, 0x4B00, 0x626E, 
            0x6152, 0x6574, 0x7953, 0x636E, 0x0000, 0x0000, 0x0000, 0x9000, 
            0x0041, 0x1000, 0x0041, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x0003, 
            0x0000, 0x6E4B, 0x5762, 0x7661, 0x6665, 0x726F, 0x006D, 0x0000, 
            0x3F80, 0x0000, 0x4080, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x045B, 0x0000, 0x4B00, 0x626E, 0x6544, 0x7470, 0x0068, 
            0x0000, 0x0000, 0x0000, 0x42C8, 0x0000, 0x4248, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x055B, 0x0000, 0x4200, 0x6E74, 0x6554, 0x706D, 
            0x536F, 0x6E79, 0x0063, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& drywet = this->getT(0);                                             // AutoPanner_impl::drywet_t<NV>
		auto& split = this->getT(1);                                              // AutoPanner_impl::split_t<NV>
		auto& dry = this->getT(1).getT(0);                                        // AutoPanner_impl::dry_t<NV>
		auto& gain = this->getT(1).getT(0).getT(0);                               // core::gain<NV>
		auto& wet = this->getT(1).getT(1);                                        // AutoPanner_impl::wet_t<NV>
		auto& gain1 = this->getT(1).getT(1).getT(0);                              // core::gain<NV>
		auto& tempo_sync = this->getT(1).getT(1).getT(1);                         // AutoPanner_impl::tempo_sync_t<NV>
		auto& converter = this->getT(1).getT(1).getT(2);                          // AutoPanner_impl::converter_t<NV>
		auto& modchain1 = this->getT(1).getT(1).getT(3);                          // AutoPanner_impl::modchain1_t<NV>
		auto& oscillator1 = this->getT(1).getT(1).getT(3).getT(0);                // AutoPanner_impl::oscillator1_t<NV>
		auto& sig2mod1 = this->getT(1).getT(1).getT(3).getT(1);                   // math::sig2mod<NV>
		auto& peak1 = this->getT(1).getT(1).getT(3).getT(2);                      // AutoPanner_impl::peak1_t<NV>
		auto& multi = this->getT(1).getT(1).getT(4);                              // AutoPanner_impl::multi_t<NV>
		auto& chain = this->getT(1).getT(1).getT(4).getT(0);                      // AutoPanner_impl::chain_t<NV>
		auto& smoothed_parameter = this->getT(1).getT(1).getT(4).getT(0).getT(0); // AutoPanner_impl::smoothed_parameter_t<NV>
		auto& jpanner = this->getT(1).getT(1).getT(4).getT(0).getT(1);            // jdsp::jpanner<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, drywet); // KnbDryWet -> drywet::Value
		
		this->getParameterT(1).connectT(0, tempo_sync); // KnbRateFree -> tempo_sync::UnsyncedTime
		
		this->getParameterT(2).connectT(0, tempo_sync); // KnbRateSync -> tempo_sync::Tempo
		
		this->getParameterT(4).connectT(0, oscillator1); // KnbDepth -> oscillator1::Gain
		
		this->getParameterT(5).connectT(0, tempo_sync); // BtnTempoSync -> tempo_sync::Enabled
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& drywet_p = drywet.getWrappedObject().getParameter();
		drywet_p.getParameterT(0).connectT(0, gain);                          // drywet -> gain::Gain
		drywet_p.getParameterT(1).connectT(0, gain1);                         // drywet -> gain1::Gain
		converter.getWrappedObject().getParameter().connectT(0, oscillator1); // converter -> oscillator1::Frequency
		tempo_sync.getParameter().connectT(0, converter);                     // tempo_sync -> converter::Value
		smoothed_parameter.getParameter().connectT(0, jpanner);               // smoothed_parameter -> jpanner::Pan
		peak1.getParameter().connectT(0, smoothed_parameter);                 // peak1 -> smoothed_parameter::Value
		
		// Default Values --------------------------------------------------------------------------
		
		; // drywet::Value is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                // tempo_sync::Tempo is automated
		tempo_sync.setParameterT(1, 2.); // control::tempo_sync::Multiplier
		;                                // tempo_sync::Enabled is automated
		;                                // tempo_sync::UnsyncedTime is automated
		
		; // converter::Value is automated
		
		oscillator1.setParameterT(0, 0.); // core::oscillator::Mode
		;                                 // oscillator1::Frequency is automated
		oscillator1.setParameterT(2, 1.); // core::oscillator::FreqRatio
		oscillator1.setParameterT(3, 1.); // core::oscillator::Gate
		oscillator1.setParameterT(4, 0.); // core::oscillator::Phase
		;                                 // oscillator1::Gain is automated
		
		sig2mod1.setParameterT(0, 0.); // math::sig2mod::Value
		
		;                                          // smoothed_parameter::Value is automated
		smoothed_parameter.setParameterT(1, 100.); // control::smoothed_parameter::SmoothingTime
		smoothed_parameter.setParameterT(2, 1.);   // control::smoothed_parameter::Enabled
		
		;                             // jpanner::Pan is automated
		jpanner.setParameterT(1, 0.); // jdsp::jpanner::Rule
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 2500.);
		this->setParameterT(2, 9.);
		this->setParameterT(3, 1.);
		this->setParameterT(4, 50.);
		this->setParameterT(5, 0.);
		this->setExternalData({}, -1);
	}
	~instance() override
	{
		// Cleanup external data references --------------------------------------------------------
		
		this->setExternalData({}, -1);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool isProcessingHiseEvent() { return true; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(1).getT(1).getT(3).getT(0).setExternalData(b, index); // AutoPanner_impl::oscillator1_t<NV>
		this->getT(1).getT(1).getT(3).getT(2).setExternalData(b, index); // AutoPanner_impl::peak1_t<NV>
	}
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
using AutoPanner = wrap::node<AutoPanner_impl::instance<NV>>;
}


