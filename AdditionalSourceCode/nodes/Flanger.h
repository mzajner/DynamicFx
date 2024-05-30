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

namespace Flanger_impl
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
using converter_t = control::converter<parameter::plain<project::FlangerFeedback<NV>, 3>, 
                                       conversion_logic::ms2freq>;
template <int NV>
using tempo_sync1_t = wrap::mod<parameter::plain<converter_t<NV>, 0>, 
                                control::tempo_sync<NV>>;
template <int NV>
using converter1_t = control::converter<parameter::plain<tempo_sync1_t<NV>, 3>, 
                                        conversion_logic::freq2ms>;

template <int NV>
using smoothedFlangeDelay1_t = wrap::mod<parameter::plain<project::FlangerFeedback<NV>, 0>, 
                                         control::smoothed_parameter_unscaled<NV, smoothers::linear_ramp<NV>>>;
template <int NV>
using minmaxFlangeDelay_t = control::minmax<NV, 
                                            parameter::plain<smoothedFlangeDelay1_t<NV>, 0>>;

template <int NV>
using minmaxFeedback_t = control::minmax<NV, 
                                         parameter::plain<project::FlangerFeedback<NV>, 2>>;

template <int NV>
using minmaxDepth_t = control::minmax<NV, 
                                      parameter::plain<project::FlangerFeedback<NV>, 1>>;

template <int NV>
using sb1_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, converter1_t<NV>>, 
                                tempo_sync1_t<NV>, 
                                converter_t<NV>, 
                                minmaxFlangeDelay_t<NV>, 
                                smoothedFlangeDelay1_t<NV>, 
                                minmaxFeedback_t<NV>, 
                                minmaxDepth_t<NV>, 
                                project::FlangerFeedback<NV>>;

template <int NV>
using sb1_t = bypass::smoothed<20, sb1_t_<NV>>;
template <int NV>
using switcher_c0 = parameter::bypass<sb1_t<NV>>;

template <int NV> using converter2_t = converter_t<NV>;
template <int NV>
using tempo_sync2_t = wrap::mod<parameter::plain<converter2_t<NV>, 0>, 
                                control::tempo_sync<NV>>;

template <int NV> using smoothedFlangeDelay2_t = smoothedFlangeDelay1_t<NV>;
template <int NV>
using minmaxFlangeDelay1_t = control::minmax<NV, 
                                             parameter::plain<smoothedFlangeDelay2_t<NV>, 0>>;

template <int NV> using minmaxFeedback1_t = minmaxFeedback_t<NV>;

template <int NV> using minmaxDepth1_t = minmaxDepth_t<NV>;

template <int NV>
using sb2_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, tempo_sync2_t<NV>>, 
                                converter2_t<NV>, 
                                minmaxFlangeDelay1_t<NV>, 
                                smoothedFlangeDelay2_t<NV>, 
                                minmaxFeedback1_t<NV>, 
                                minmaxDepth1_t<NV>, 
                                project::FlangerFeedback<NV>>;

template <int NV>
using sb2_t = bypass::smoothed<20, sb2_t_<NV>>;
template <int NV>
using switcher_c1 = parameter::bypass<sb2_t<NV>>;

template <int NV>
using switcher_multimod = parameter::list<switcher_c0<NV>, switcher_c1<NV>>;

template <int NV>
using switcher_t = control::xfader<switcher_multimod<NV>, faders::switcher>;

template <int NV>
using sb_container_t = container::chain<parameter::empty, 
                                        wrap::fix<2, sb1_t<NV>>, 
                                        sb2_t<NV>>;

template <int NV>
using softbypass_switch3_t = container::chain<parameter::empty, 
                                              wrap::fix<2, switcher_t<NV>>, 
                                              sb_container_t<NV>>;

template <int NV>
using WET_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>, 
                               softbypass_switch3_t<NV>, 
                               core::gain<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, DRY_t<NV>>, 
                                 WET_t<NV>>;

namespace Flanger_t_parameters
{
// Parameter list for Flanger_impl::Flanger_t ------------------------------------------------------

DECLARE_PARAMETER_RANGE(KnbDryWet_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<Flanger_impl::xfader_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE(KnbFeedback_InputRange, 
                        0., 
                        100.);
DECLARE_PARAMETER_RANGE_STEP_INV(KnbFeedback_4Range, 
                                 -6., 
                                 0., 
                                 0.1);

template <int NV>
using KnbFeedback_4 = parameter::from0To1_inv<core::gain<NV>, 
                                              0, 
                                              KnbFeedback_4Range>;

template <int NV>
using KnbFeedback = parameter::chain<KnbFeedback_InputRange, 
                                     parameter::plain<Flanger_impl::minmaxFeedback_t<NV>, 0>, 
                                     parameter::plain<Flanger_impl::minmaxFeedback1_t<NV>, 0>, 
                                     parameter::plain<Flanger_impl::minmaxDepth_t<NV>, 0>, 
                                     parameter::plain<Flanger_impl::minmaxDepth1_t<NV>, 0>, 
                                     KnbFeedback_4<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbDelayTime_InputRange, 
                             0.1, 
                             50., 
                             0.997114);

template <int NV>
using KnbDelayTime = parameter::chain<KnbDelayTime_InputRange, 
                                      parameter::plain<Flanger_impl::minmaxFlangeDelay_t<NV>, 0>, 
                                      parameter::plain<Flanger_impl::minmaxFlangeDelay1_t<NV>, 0>>;

template <int NV>
using KnbRateFree = parameter::plain<Flanger_impl::converter1_t<NV>, 
                                     0>;
template <int NV>
using KnbRateSync = parameter::plain<Flanger_impl::tempo_sync2_t<NV>, 
                                     0>;
template <int NV>
using BtnTempoSync = parameter::plain<Flanger_impl::switcher_t<NV>, 
                                      0>;
template <int NV>
using Flanger_t_plist = parameter::list<KnbDryWet<NV>, 
                                        KnbRateFree<NV>, 
                                        KnbFeedback<NV>, 
                                        KnbDelayTime<NV>, 
                                        KnbRateSync<NV>, 
                                        BtnTempoSync<NV>>;
}

template <int NV>
using Flanger_t_ = container::chain<Flanger_t_parameters::Flanger_t_plist<NV>, 
                                    wrap::fix<2, xfader_t<NV>>, 
                                    split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Flanger_impl::Flanger_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Flanger);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(112)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x5262, 0x7461, 0x4665, 
            0x6572, 0x0065, 0xD70A, 0x3C23, 0x0000, 0x4120, 0x8EF3, 0x3F03, 
            0x6C1A, 0x3E6B, 0xB717, 0x38D1, 0x025B, 0x0000, 0x4B00, 0x626E, 
            0x6546, 0x6465, 0x6162, 0x6B63, 0x0000, 0x0000, 0x0000, 0xC800, 
            0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 
            0x0000, 0x6E4B, 0x4462, 0x6C65, 0x7961, 0x6954, 0x656D, 0xCD00, 
            0xCCCC, 0x003D, 0x4800, 0x0042, 0xC800, 0xE241, 0x7F42, 0x0A3F, 
            0x23D7, 0x5B3C, 0x0004, 0x0000, 0x6E4B, 0x5262, 0x7461, 0x5365, 
            0x6E79, 0x0063, 0x0000, 0x0000, 0x0000, 0x4190, 0x0000, 0x40A0, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x055B, 0x0000, 0x4200, 0x6E74, 
            0x6554, 0x706D, 0x536F, 0x6E79, 0x0063, 0x0000, 0x0000, 0x0000, 
            0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                                                       // Flanger_impl::xfader_t<NV>
		auto& split = this->getT(1);                                                        // Flanger_impl::split_t<NV>
		auto& DRY = this->getT(1).getT(0);                                                  // Flanger_impl::DRY_t<NV>
		auto& DryGain = this->getT(1).getT(0).getT(0);                                      // core::gain<NV>
		auto& WET = this->getT(1).getT(1);                                                  // Flanger_impl::WET_t<NV>
		auto& WetGain = this->getT(1).getT(1).getT(0);                                      // core::gain<NV>
		auto& softbypass_switch3 = this->getT(1).getT(1).getT(1);                           // Flanger_impl::softbypass_switch3_t<NV>
		auto& switcher = this->getT(1).getT(1).getT(1).getT(0);                             // Flanger_impl::switcher_t<NV>
		auto& sb_container = this->getT(1).getT(1).getT(1).getT(1);                         // Flanger_impl::sb_container_t<NV>
		auto& sb1 = this->getT(1).getT(1).getT(1).getT(1).getT(0);                          // Flanger_impl::sb1_t<NV>
		auto& converter1 = this->getT(1).getT(1).getT(1).getT(1).getT(0).getT(0);           // Flanger_impl::converter1_t<NV>
		auto& tempo_sync1 = this->getT(1).getT(1).getT(1).getT(1).getT(0).getT(1);          // Flanger_impl::tempo_sync1_t<NV>
		auto& converter = this->getT(1).getT(1).getT(1).getT(1).getT(0).getT(2);            // Flanger_impl::converter_t<NV>
		auto& minmaxFlangeDelay = this->getT(1).getT(1).getT(1).getT(1).getT(0).getT(3);    // Flanger_impl::minmaxFlangeDelay_t<NV>
		auto& smoothedFlangeDelay1 = this->getT(1).getT(1).getT(1).getT(1).getT(0).getT(4); // Flanger_impl::smoothedFlangeDelay1_t<NV>
		auto& minmaxFeedback = this->getT(1).getT(1).getT(1).getT(1).getT(0).getT(5);       // Flanger_impl::minmaxFeedback_t<NV>
		auto& minmaxDepth = this->getT(1).getT(1).getT(1).getT(1).getT(0).getT(6);          // Flanger_impl::minmaxDepth_t<NV>
		auto& faust = this->getT(1).getT(1).getT(1).getT(1).getT(0).getT(7);                // project::FlangerFeedback<NV>
		auto& sb2 = this->getT(1).getT(1).getT(1).getT(1).getT(1);                          // Flanger_impl::sb2_t<NV>
		auto& tempo_sync2 = this->getT(1).getT(1).getT(1).getT(1).getT(1).getT(0);          // Flanger_impl::tempo_sync2_t<NV>
		auto& converter2 = this->getT(1).getT(1).getT(1).getT(1).getT(1).getT(1);           // Flanger_impl::converter2_t<NV>
		auto& minmaxFlangeDelay1 = this->getT(1).getT(1).getT(1).getT(1).getT(1).getT(2);   // Flanger_impl::minmaxFlangeDelay1_t<NV>
		auto& smoothedFlangeDelay2 = this->getT(1).getT(1).getT(1).getT(1).getT(1).getT(3); // Flanger_impl::smoothedFlangeDelay2_t<NV>
		auto& minmaxFeedback1 = this->getT(1).getT(1).getT(1).getT(1).getT(1).getT(4);      // Flanger_impl::minmaxFeedback1_t<NV>
		auto& minmaxDepth1 = this->getT(1).getT(1).getT(1).getT(1).getT(1).getT(5);         // Flanger_impl::minmaxDepth1_t<NV>
		auto& faust3 = this->getT(1).getT(1).getT(1).getT(1).getT(1).getT(6);               // project::FlangerFeedback<NV>
		auto& gain = this->getT(1).getT(1).getT(2);                                         // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		this->getParameterT(1).connectT(0, converter1); // KnbRateFree -> converter1::Value
		
		auto& KnbFeedback_p = this->getParameterT(2);
		KnbFeedback_p.connectT(0, minmaxFeedback);  // KnbFeedback -> minmaxFeedback::Value
		KnbFeedback_p.connectT(1, minmaxFeedback1); // KnbFeedback -> minmaxFeedback1::Value
		KnbFeedback_p.connectT(2, minmaxDepth);     // KnbFeedback -> minmaxDepth::Value
		KnbFeedback_p.connectT(3, minmaxDepth1);    // KnbFeedback -> minmaxDepth1::Value
		KnbFeedback_p.connectT(4, gain);            // KnbFeedback -> gain::Gain
		
		auto& KnbDelayTime_p = this->getParameterT(3);
		KnbDelayTime_p.connectT(0, minmaxFlangeDelay);  // KnbDelayTime -> minmaxFlangeDelay::Value
		KnbDelayTime_p.connectT(1, minmaxFlangeDelay1); // KnbDelayTime -> minmaxFlangeDelay1::Value
		
		this->getParameterT(4).connectT(0, tempo_sync2); // KnbRateSync -> tempo_sync2::Tempo
		
		this->getParameterT(5).connectT(0, switcher); // BtnTempoSync -> switcher::Value
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, DryGain);                                         // xfader -> DryGain::Gain
		xfader_p.getParameterT(1).connectT(0, WetGain);                                         // xfader -> WetGain::Gain
		converter.getWrappedObject().getParameter().connectT(0, faust);                         // converter -> faust::freq
		tempo_sync1.getParameter().connectT(0, converter);                                      // tempo_sync1 -> converter::Value
		converter1.getWrappedObject().getParameter().connectT(0, tempo_sync1);                  // converter1 -> tempo_sync1::UnsyncedTime
		smoothedFlangeDelay1.getParameter().connectT(0, faust);                                 // smoothedFlangeDelay1 -> faust::delay
		minmaxFlangeDelay.getWrappedObject().getParameter().connectT(0, smoothedFlangeDelay1);  // minmaxFlangeDelay -> smoothedFlangeDelay1::Value
		minmaxFeedback.getWrappedObject().getParameter().connectT(0, faust);                    // minmaxFeedback -> faust::feedback
		minmaxDepth.getWrappedObject().getParameter().connectT(0, faust);                       // minmaxDepth -> faust::depth
		converter2.getWrappedObject().getParameter().connectT(0, faust3);                       // converter2 -> faust3::freq
		tempo_sync2.getParameter().connectT(0, converter2);                                     // tempo_sync2 -> converter2::Value
		smoothedFlangeDelay2.getParameter().connectT(0, faust3);                                // smoothedFlangeDelay2 -> faust3::delay
		minmaxFlangeDelay1.getWrappedObject().getParameter().connectT(0, smoothedFlangeDelay2); // minmaxFlangeDelay1 -> smoothedFlangeDelay2::Value
		minmaxFeedback1.getWrappedObject().getParameter().connectT(0, faust3);                  // minmaxFeedback1 -> faust3::feedback
		minmaxDepth1.getWrappedObject().getParameter().connectT(0, faust3);                     // minmaxDepth1 -> faust3::depth
		auto& switcher_p = switcher.getWrappedObject().getParameter();
		switcher_p.getParameterT(0).connectT(0, sb1); // switcher -> sb1::Bypassed
		switcher_p.getParameterT(1).connectT(0, sb2); // switcher -> sb2::Bypassed
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                              // DryGain::Gain is automated
		DryGain.setParameterT(1, 20.); // core::gain::Smoothing
		DryGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                              // WetGain::Gain is automated
		WetGain.setParameterT(1, 20.); // core::gain::Smoothing
		WetGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // switcher::Value is automated
		
		; // converter1::Value is automated
		
		tempo_sync1.setParameterT(0, 0.); // control::tempo_sync::Tempo
		tempo_sync1.setParameterT(1, 1.); // control::tempo_sync::Multiplier
		tempo_sync1.setParameterT(2, 0.); // control::tempo_sync::Enabled
		;                                 // tempo_sync1::UnsyncedTime is automated
		
		; // converter::Value is automated
		
		;                                          // minmaxFlangeDelay::Value is automated
		minmaxFlangeDelay.setParameterT(1, 0.001); // control::minmax::Minimum
		minmaxFlangeDelay.setParameterT(2, 0.05);  // control::minmax::Maximum
		minmaxFlangeDelay.setParameterT(3, 1.);    // control::minmax::Skew
		minmaxFlangeDelay.setParameterT(4, 0.);    // control::minmax::Step
		minmaxFlangeDelay.setParameterT(5, 0.);    // control::minmax::Polarity
		
		;                                            // smoothedFlangeDelay1::Value is automated
		smoothedFlangeDelay1.setParameterT(1, 150.); // control::smoothed_parameter_unscaled::SmoothingTime
		smoothedFlangeDelay1.setParameterT(2, 1.);   // control::smoothed_parameter_unscaled::Enabled
		
		;                                      // minmaxFeedback::Value is automated
		minmaxFeedback.setParameterT(1, 0.);   // control::minmax::Minimum
		minmaxFeedback.setParameterT(2, 0.95); // control::minmax::Maximum
		minmaxFeedback.setParameterT(3, 1.);   // control::minmax::Skew
		minmaxFeedback.setParameterT(4, 0.);   // control::minmax::Step
		minmaxFeedback.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                                  // minmaxDepth::Value is automated
		minmaxDepth.setParameterT(1, 0.);  // control::minmax::Minimum
		minmaxDepth.setParameterT(2, 0.1); // control::minmax::Maximum
		minmaxDepth.setParameterT(3, 1.);  // control::minmax::Skew
		minmaxDepth.setParameterT(4, 0.);  // control::minmax::Step
		minmaxDepth.setParameterT(5, 0.);  // control::minmax::Polarity
		
		;                           // faust::delay is automated
		;                           // faust::depth is automated
		;                           // faust::feedback is automated
		;                           // faust::freq is automated
		faust.setParameterT(4, 1);  // core::faust::level
		faust.setParameterT(5, 1.); // core::faust::stereo
		
		;                                    // tempo_sync2::Tempo is automated
		tempo_sync2.setParameterT(1, 4.);    // control::tempo_sync::Multiplier
		tempo_sync2.setParameterT(2, 1.);    // control::tempo_sync::Enabled
		tempo_sync2.setParameterT(3, 2000.); // control::tempo_sync::UnsyncedTime
		
		; // converter2::Value is automated
		
		;                                           // minmaxFlangeDelay1::Value is automated
		minmaxFlangeDelay1.setParameterT(1, 0.001); // control::minmax::Minimum
		minmaxFlangeDelay1.setParameterT(2, 0.05);  // control::minmax::Maximum
		minmaxFlangeDelay1.setParameterT(3, 1.);    // control::minmax::Skew
		minmaxFlangeDelay1.setParameterT(4, 0.);    // control::minmax::Step
		minmaxFlangeDelay1.setParameterT(5, 0.);    // control::minmax::Polarity
		
		;                                            // smoothedFlangeDelay2::Value is automated
		smoothedFlangeDelay2.setParameterT(1, 150.); // control::smoothed_parameter_unscaled::SmoothingTime
		smoothedFlangeDelay2.setParameterT(2, 1.);   // control::smoothed_parameter_unscaled::Enabled
		
		;                                       // minmaxFeedback1::Value is automated
		minmaxFeedback1.setParameterT(1, 0.);   // control::minmax::Minimum
		minmaxFeedback1.setParameterT(2, 0.95); // control::minmax::Maximum
		minmaxFeedback1.setParameterT(3, 1.);   // control::minmax::Skew
		minmaxFeedback1.setParameterT(4, 0.);   // control::minmax::Step
		minmaxFeedback1.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                                   // minmaxDepth1::Value is automated
		minmaxDepth1.setParameterT(1, 0.);  // control::minmax::Minimum
		minmaxDepth1.setParameterT(2, 0.1); // control::minmax::Maximum
		minmaxDepth1.setParameterT(3, 1.);  // control::minmax::Skew
		minmaxDepth1.setParameterT(4, 0.);  // control::minmax::Step
		minmaxDepth1.setParameterT(5, 0.);  // control::minmax::Polarity
		
		;                            // faust3::delay is automated
		;                            // faust3::depth is automated
		;                            // faust3::feedback is automated
		;                            // faust3::freq is automated
		faust3.setParameterT(4, 1);  // core::faust::level
		faust3.setParameterT(5, 1.); // core::faust::stereo
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 0.5139);
		this->setParameterT(2, 50.);
		this->setParameterT(3, 25.);
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
using Flanger = wrap::node<Flanger_impl::instance<NV>>;
}


