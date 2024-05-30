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

namespace TwistDelay_impl
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

namespace custom
{

struct cable_expr
{
	static double op(double input)
	{
		return input*0.00001;
	}
};
}

template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<project::echoForBrowser<NV>, 0>>;
template <int NV>
using cable_expr_t = control::cable_expr<custom::cable_expr, 
                                         parameter::plain<minmax_t<NV>, 0>>;
template <int NV>
using converter_t = control::converter<parameter::plain<cable_expr_t<NV>, 0>, 
                                       conversion_logic::freq2samples>;
template <int NV>
using converter1_t = control::converter<parameter::plain<converter_t<NV>, 0>, 
                                        conversion_logic::ms2freq>;
template <int NV>
using tempo_sync_t = wrap::mod<parameter::plain<converter1_t<NV>, 0>, 
                               control::tempo_sync<NV>>;

template <int NV>
using minmaxFeedback_t = control::minmax<NV, 
                                         parameter::plain<project::echoForBrowser<NV>, 3>>;

template <int NV>
using minmaxEcho_t = control::minmax<NV, 
                                     parameter::plain<project::echoForBrowser<NV>, 2>>;

template <int NV>
using minmax1_t = control::minmax<NV, 
                                  parameter::plain<project::echoForBrowser<NV>, 1>>;

template <int NV>
using minmax2_t = control::minmax<NV, 
                                  parameter::plain<project::echoForBrowser<NV>, 5>>;

template <int NV>
using WET_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>, 
                               tempo_sync_t<NV>, 
                               converter1_t<NV>, 
                               converter_t<NV>, 
                               cable_expr_t<NV>, 
                               minmax_t<NV>, 
                               minmaxFeedback_t<NV>, 
                               minmaxEcho_t<NV>, 
                               minmax1_t<NV>, 
                               minmax2_t<NV>, 
                               project::echoForBrowser<NV>, 
                               control::smoothed_parameter_unscaled<NV, smoothers::linear_ramp<NV>>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, DRY_t<NV>>, 
                                 WET_t<NV>>;

namespace TwistDelay_t_parameters
{
// Parameter list for TwistDelay_impl::TwistDelay_t ------------------------------------------------

DECLARE_PARAMETER_RANGE(KnbDryWet_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<TwistDelay_impl::xfader_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE(KnbTimeFree_InputRange, 
                        0., 
                        2000.);
DECLARE_PARAMETER_RANGE_SKEW(KnbTimeFree_0Range, 
                             1, 
                             2000., 
                             0.999279);

template <int NV>
using KnbTimeFree_0 = parameter::from0To1<TwistDelay_impl::tempo_sync_t<NV>, 
                                          3, 
                                          KnbTimeFree_0Range>;

template <int NV>
using KnbTimeFree = parameter::chain<KnbTimeFree_InputRange, KnbTimeFree_0<NV>>;

DECLARE_PARAMETER_RANGE(KnbFeedback_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbFeedback = parameter::chain<KnbFeedback_InputRange, 
                                     parameter::plain<TwistDelay_impl::minmaxFeedback_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE(KnbEcho_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbEcho = parameter::chain<KnbEcho_InputRange, 
                                 parameter::plain<TwistDelay_impl::minmaxEcho_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE(KnbTwistDirection_InputRange, 
                        -1., 
                        1.);

template <int NV>
using KnbTwistDirection = parameter::chain<KnbTwistDirection_InputRange, 
                                           parameter::plain<TwistDelay_impl::minmax1_t<NV>, 0>>;

template <int NV>
using KnbTimeSync = parameter::plain<TwistDelay_impl::tempo_sync_t<NV>, 
                                     0>;
template <int NV>
using KnbFilter = parameter::plain<TwistDelay_impl::minmax2_t<NV>, 
                                   0>;
template <int NV>
using BtnTempoSync = parameter::plain<TwistDelay_impl::tempo_sync_t<NV>, 
                                      2>;
template <int NV>
using TwistDelay_t_plist = parameter::list<KnbDryWet<NV>, 
                                           KnbTimeFree<NV>, 
                                           KnbFeedback<NV>, 
                                           KnbEcho<NV>, 
                                           KnbTimeSync<NV>, 
                                           KnbTwistDirection<NV>, 
                                           KnbFilter<NV>, 
                                           BtnTempoSync<NV>>;
}

template <int NV>
using TwistDelay_t_ = container::chain<TwistDelay_t_parameters::TwistDelay_t_plist<NV>, 
                                       wrap::fix<2, xfader_t<NV>>, 
                                       split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public TwistDelay_impl::TwistDelay_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(TwistDelay);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(148)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x5462, 0x6D69, 0x4665, 
            0x6572, 0x0065, 0x0000, 0x0000, 0x0000, 0x44FA, 0x0000, 0x447A, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x025B, 0x0000, 0x4B00, 0x626E, 
            0x6546, 0x6465, 0x6162, 0x6B63, 0x0000, 0x0000, 0x0000, 0xC800, 
            0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 
            0x0000, 0x6E4B, 0x4562, 0x6863, 0x006F, 0x0000, 0x0000, 0x0000, 
            0x42C8, 0x0000, 0x4248, 0x0000, 0x3F80, 0x0000, 0x0000, 0x045B, 
            0x0000, 0x4B00, 0x626E, 0x6954, 0x656D, 0x7953, 0x636E, 0x0000, 
            0x0000, 0x0000, 0x9000, 0x0041, 0xA000, 0x0040, 0x8000, 0x003F, 
            0x8000, 0x5B3F, 0x0005, 0x0000, 0x6E4B, 0x5462, 0x6977, 0x7473, 
            0x6944, 0x6572, 0x7463, 0x6F69, 0x006E, 0x0000, 0xBF80, 0x0000, 
            0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x065B, 
            0x0000, 0x4B00, 0x626E, 0x6946, 0x746C, 0x7265, 0x0000, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 0x0000, 
            0x5B00, 0x0007, 0x0000, 0x7442, 0x546E, 0x6D65, 0x6F70, 0x7953, 
            0x636E, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x8000, 0x003F
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                                       // TwistDelay_impl::xfader_t<NV>
		auto& split = this->getT(1);                                        // TwistDelay_impl::split_t<NV>
		auto& DRY = this->getT(1).getT(0);                                  // TwistDelay_impl::DRY_t<NV>
		auto& DryGain = this->getT(1).getT(0).getT(0);                      // core::gain<NV>
		auto& WET = this->getT(1).getT(1);                                  // TwistDelay_impl::WET_t<NV>
		auto& WetGain = this->getT(1).getT(1).getT(0);                      // core::gain<NV>
		auto& tempo_sync = this->getT(1).getT(1).getT(1);                   // TwistDelay_impl::tempo_sync_t<NV>
		auto& converter1 = this->getT(1).getT(1).getT(2);                   // TwistDelay_impl::converter1_t<NV>
		auto& converter = this->getT(1).getT(1).getT(3);                    // TwistDelay_impl::converter_t<NV>
		auto& cable_expr = this->getT(1).getT(1).getT(4);                   // TwistDelay_impl::cable_expr_t<NV>
		auto& minmax = this->getT(1).getT(1).getT(5);                       // TwistDelay_impl::minmax_t<NV>
		auto& minmaxFeedback = this->getT(1).getT(1).getT(6);               // TwistDelay_impl::minmaxFeedback_t<NV>
		auto& minmaxEcho = this->getT(1).getT(1).getT(7);                   // TwistDelay_impl::minmaxEcho_t<NV>
		auto& minmax1 = this->getT(1).getT(1).getT(8);                      // TwistDelay_impl::minmax1_t<NV>
		auto& minmax2 = this->getT(1).getT(1).getT(9);                      // TwistDelay_impl::minmax2_t<NV>
		auto& faust2 = this->getT(1).getT(1).getT(10);                      // project::echoForBrowser<NV>
		auto& smoothed_parameter_unscaled = this->getT(1).getT(1).getT(11); // control::smoothed_parameter_unscaled<NV, smoothers::linear_ramp<NV>>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		this->getParameterT(1).connectT(0, tempo_sync); // KnbTimeFree -> tempo_sync::UnsyncedTime
		
		this->getParameterT(2).connectT(0, minmaxFeedback); // KnbFeedback -> minmaxFeedback::Value
		
		this->getParameterT(3).connectT(0, minmaxEcho); // KnbEcho -> minmaxEcho::Value
		
		this->getParameterT(4).connectT(0, tempo_sync); // KnbTimeSync -> tempo_sync::Tempo
		
		this->getParameterT(5).connectT(0, minmax1); // KnbTwistDirection -> minmax1::Value
		
		this->getParameterT(6).connectT(0, minmax2); // KnbFilter -> minmax2::Value
		
		this->getParameterT(7).connectT(0, tempo_sync); // BtnTempoSync -> tempo_sync::Enabled
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, DryGain);                       // xfader -> DryGain::Gain
		xfader_p.getParameterT(1).connectT(0, WetGain);                       // xfader -> WetGain::Gain
		minmax.getWrappedObject().getParameter().connectT(0, faust2);         // minmax -> faust2::Delay
		cable_expr.getWrappedObject().getParameter().connectT(0, minmax);     // cable_expr -> minmax::Value
		converter.getWrappedObject().getParameter().connectT(0, cable_expr);  // converter -> cable_expr::Value
		converter1.getWrappedObject().getParameter().connectT(0, converter);  // converter1 -> converter::Value
		tempo_sync.getParameter().connectT(0, converter1);                    // tempo_sync -> converter1::Value
		minmaxFeedback.getWrappedObject().getParameter().connectT(0, faust2); // minmaxFeedback -> faust2::Feedback
		minmaxEcho.getWrappedObject().getParameter().connectT(0, faust2);     // minmaxEcho -> faust2::DelayT60
		minmax1.getWrappedObject().getParameter().connectT(0, faust2);        // minmax1 -> faust2::Warp
		minmax2.getWrappedObject().getParameter().connectT(0, faust2);        // minmax2 -> faust2::FeedbackSm
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                              // DryGain::Gain is automated
		DryGain.setParameterT(1, 20.); // core::gain::Smoothing
		DryGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                              // WetGain::Gain is automated
		WetGain.setParameterT(1, 20.); // core::gain::Smoothing
		WetGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                // tempo_sync::Tempo is automated
		tempo_sync.setParameterT(1, 1.); // control::tempo_sync::Multiplier
		;                                // tempo_sync::Enabled is automated
		;                                // tempo_sync::UnsyncedTime is automated
		
		; // converter1::Value is automated
		
		; // converter::Value is automated
		
		; // cable_expr::Value is automated
		
		;                               // minmax::Value is automated
		minmax.setParameterT(1, 0.001); // control::minmax::Minimum
		minmax.setParameterT(2, 1.);    // control::minmax::Maximum
		minmax.setParameterT(3, 1.);    // control::minmax::Skew
		minmax.setParameterT(4, 0.);    // control::minmax::Step
		minmax.setParameterT(5, 0.);    // control::minmax::Polarity
		
		;                                     // minmaxFeedback::Value is automated
		minmaxFeedback.setParameterT(1, 0.);  // control::minmax::Minimum
		minmaxFeedback.setParameterT(2, 0.9); // control::minmax::Maximum
		minmaxFeedback.setParameterT(3, 1.);  // control::minmax::Skew
		minmaxFeedback.setParameterT(4, 0.);  // control::minmax::Step
		minmaxFeedback.setParameterT(5, 0.);  // control::minmax::Polarity
		
		;                                  // minmaxEcho::Value is automated
		minmaxEcho.setParameterT(1, 0.);   // control::minmax::Minimum
		minmaxEcho.setParameterT(2, 100.); // control::minmax::Maximum
		minmaxEcho.setParameterT(3, 1.);   // control::minmax::Skew
		minmaxEcho.setParameterT(4, 0.);   // control::minmax::Step
		minmaxEcho.setParameterT(5, 0.);   // control::minmax::Polarity
		
		;                              // minmax1::Value is automated
		minmax1.setParameterT(1, -1.); // control::minmax::Minimum
		minmax1.setParameterT(2, 1.);  // control::minmax::Maximum
		minmax1.setParameterT(3, 1.);  // control::minmax::Skew
		minmax1.setParameterT(4, 0.);  // control::minmax::Step
		minmax1.setParameterT(5, 1.);  // control::minmax::Polarity
		
		;                              // minmax2::Value is automated
		minmax2.setParameterT(1, 0.);  // control::minmax::Minimum
		minmax2.setParameterT(2, 0.6); // control::minmax::Maximum
		minmax2.setParameterT(3, 1.);  // control::minmax::Skew
		minmax2.setParameterT(4, 0.);  // control::minmax::Step
		minmax2.setParameterT(5, 1.);  // control::minmax::Polarity
		
		;                            // faust2::Delay is automated
		;                            // faust2::Warp is automated
		;                            // faust2::DelayT60 is automated
		;                            // faust2::Feedback is automated
		faust2.setParameterT(4, 1.); // core::faust::Amp
		;                            // faust2::FeedbackSm is automated
		faust2.setParameterT(6, 1.); // core::faust::EnableEcho
		
		smoothed_parameter_unscaled.setParameterT(0, 0.);   // control::smoothed_parameter_unscaled::Value
		smoothed_parameter_unscaled.setParameterT(1, 500.); // control::smoothed_parameter_unscaled::SmoothingTime
		smoothed_parameter_unscaled.setParameterT(2, 1.);   // control::smoothed_parameter_unscaled::Enabled
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 1000.);
		this->setParameterT(2, 50.);
		this->setParameterT(3, 50.);
		this->setParameterT(4, 5.);
		this->setParameterT(5, 0.);
		this->setParameterT(6, 1.);
		this->setParameterT(7, 0.);
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
using TwistDelay = wrap::node<TwistDelay_impl::instance<NV>>;
}


