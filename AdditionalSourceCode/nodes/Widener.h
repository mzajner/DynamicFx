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

namespace Widener_impl
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
using mid_chain_t = container::chain<parameter::empty, 
                                     wrap::fix<1, core::gain<NV>>>;

template <int NV> using side_chain_t = mid_chain_t<NV>;

template <int NV>
using ms_splitter_t = container::multi<parameter::empty, 
                                       wrap::fix<1, mid_chain_t<NV>>, 
                                       wrap::fix<1, side_chain_t<NV>>>;

template <int NV>
using mid_side1_t = container::chain<parameter::empty, 
                                     wrap::fix<2, routing::ms_decode>, 
                                     ms_splitter_t<NV>, 
                                     routing::ms_encode>;

template <int NV>
using sb1_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, mid_side1_t<NV>>>;

template <int NV>
using sb1_t = bypass::smoothed<20, sb1_t_<NV>>;
template <int NV>
using switcher_c0 = parameter::bypass<sb1_t<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(xfader1_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using xfader1_c0 = parameter::from0To1<core::gain<NV>, 
                                       0, 
                                       xfader1_c0Range>;

template <int NV> using xfader1_c1 = xfader1_c0<NV>;

template <int NV>
using xfader1_multimod = parameter::list<xfader1_c0<NV>, xfader1_c1<NV>>;

template <int NV>
using xfader1_t = control::xfader<xfader1_multimod<NV>, faders::rms>;

template <int NV> using mid_chain1_t = mid_chain_t<NV>;

template <int NV> using side_chain1_t = mid_chain_t<NV>;

template <int NV>
using ms_splitter1_t = container::multi<parameter::empty, 
                                        wrap::fix<1, mid_chain1_t<NV>>, 
                                        wrap::fix<1, side_chain1_t<NV>>>;

template <int NV>
using mid_side2_t = container::chain<parameter::empty, 
                                     wrap::fix<2, xfader1_t<NV>>, 
                                     routing::ms_decode, 
                                     ms_splitter1_t<NV>, 
                                     routing::ms_encode>;

template <int NV>
using sb2_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, mid_side2_t<NV>>>;

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

using mid_chain2_t = container::chain<parameter::empty, 
                                      wrap::fix<1, core::empty>>;

using side_chain2_t = mid_chain2_t;

using ms_splitter2_t = container::multi<parameter::empty, 
                                        wrap::fix<1, mid_chain2_t>, 
                                        wrap::fix<1, side_chain2_t>>;

using mid_side3_t = container::chain<parameter::empty, 
                                     wrap::fix<2, routing::ms_encode>, 
                                     ms_splitter2_t, 
                                     routing::ms_decode>;

template <int NV>
using WET_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>, 
                               softbypass_switch3_t<NV>, 
                               mid_side3_t, 
                               core::gain<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, DRY_t<NV>>, 
                                 WET_t<NV>>;

namespace Widener_t_parameters
{
// Parameter list for Widener_impl::Widener_t ------------------------------------------------------

DECLARE_PARAMETER_RANGE(KnbDryWet_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<Widener_impl::xfader_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_STEP(KnbMidSideBalance_InputRange, 
                             0., 
                             100., 
                             0.1);

template <int NV>
using KnbMidSideBalance = parameter::chain<KnbMidSideBalance_InputRange, 
                                           parameter::plain<Widener_impl::xfader1_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbMakeUpGain_InputRange, 
                             -100., 
                             24., 
                             3.22227);
DECLARE_PARAMETER_RANGE_SKEW(KnbMakeUpGain_0Range, 
                             -100., 
                             24., 
                             3.22227);

template <int NV>
using KnbMakeUpGain_0 = parameter::from0To1<core::gain<NV>, 
                                            0, 
                                            KnbMakeUpGain_0Range>;

template <int NV>
using KnbMakeUpGain = parameter::chain<KnbMakeUpGain_InputRange, 
                                       KnbMakeUpGain_0<NV>>;

template <int NV>
using KnbMidGain = parameter::plain<core::gain<NV>, 0>;
template <int NV> using KnbSideGain = KnbMidGain<NV>;
using BtnMidSide = parameter::empty;
template <int NV>
using Widener_t_plist = parameter::list<KnbDryWet<NV>, 
                                        KnbMidGain<NV>, 
                                        KnbSideGain<NV>, 
                                        KnbMidSideBalance<NV>, 
                                        KnbMakeUpGain<NV>, 
                                        BtnMidSide>;
}

template <int NV>
using Widener_t_ = container::chain<Widener_t_parameters::Widener_t_plist<NV>, 
                                    wrap::fix<2, xfader_t<NV>>, 
                                    split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Widener_impl::Widener_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Widener);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(114)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x4D62, 0x6469, 0x6147, 
            0x6E69, 0x0000, 0xC800, 0x00C2, 0xC000, 0x0040, 0x4000, 0x05C1, 
            0x6E5F, 0xCD40, 0xCCCC, 0x5B3D, 0x0002, 0x0000, 0x6E4B, 0x5362, 
            0x6469, 0x4765, 0x6961, 0x006E, 0x0000, 0xC2C8, 0x0000, 0x40C0, 
            0x0000, 0x0000, 0x5F05, 0x406E, 0xCCCD, 0x3DCC, 0x035B, 0x0000, 
            0x4B00, 0x626E, 0x694D, 0x5364, 0x6469, 0x4265, 0x6C61, 0x6E61, 
            0x6563, 0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 
            0x8000, 0xCD3F, 0xCCCC, 0x5B3D, 0x0004, 0x0000, 0x6E4B, 0x4D62, 
            0x6B61, 0x5565, 0x4770, 0x6961, 0x006E, 0x0000, 0xC2C8, 0x0000, 
            0x41C0, 0x0000, 0x0000, 0x39B1, 0x404E, 0x0000, 0x0000, 0x055B, 
            0x0000, 0x4200, 0x6E74, 0x694D, 0x5364, 0x6469, 0x0065, 0x0000, 
            0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                                                       // Widener_impl::xfader_t<NV>
		auto& split = this->getT(1);                                                        // Widener_impl::split_t<NV>
		auto& DRY = this->getT(1).getT(0);                                                  // Widener_impl::DRY_t<NV>
		auto& DryGain = this->getT(1).getT(0).getT(0);                                      // core::gain<NV>
		auto& WET = this->getT(1).getT(1);                                                  // Widener_impl::WET_t<NV>
		auto& WetGain = this->getT(1).getT(1).getT(0);                                      // core::gain<NV>
		auto& softbypass_switch3 = this->getT(1).getT(1).getT(1);                           // Widener_impl::softbypass_switch3_t<NV>
		auto& switcher = this->getT(1).getT(1).getT(1).getT(0);                             // Widener_impl::switcher_t<NV>
		auto& sb_container = this->getT(1).getT(1).getT(1).getT(1);                         // Widener_impl::sb_container_t<NV>
		auto& sb1 = this->getT(1).getT(1).getT(1).getT(1).getT(0);                          // Widener_impl::sb1_t<NV>
		auto& mid_side1 = this->getT(1).getT(1).getT(1).getT(1).getT(0).getT(0);            // Widener_impl::mid_side1_t<NV>
		auto& decoder = this->getT(1).getT(1).getT(1).getT(1).getT(0).getT(0).getT(0);      // routing::ms_decode
		auto& ms_splitter = this->getT(1).getT(1).getT(1).getT(1).getT(0).getT(0).getT(1);  // Widener_impl::ms_splitter_t<NV>
		auto& mid_chain = this->getT(1).getT(1).getT(1).getT(1).                            // Widener_impl::mid_chain_t<NV>
                          getT(0).getT(0).getT(1).getT(0);
		auto& gain4 = this->getT(1).getT(1).getT(1).getT(1).                                // core::gain<NV>
                      getT(0).getT(0).getT(1).getT(0).
                      getT(0);
		auto& side_chain = this->getT(1).getT(1).getT(1).getT(1).                           // Widener_impl::side_chain_t<NV>
                           getT(0).getT(0).getT(1).getT(1);
		auto& gain = this->getT(1).getT(1).getT(1).getT(1).                                 // core::gain<NV>
                     getT(0).getT(0).getT(1).getT(1).
                     getT(0);
		auto& encoder = this->getT(1).getT(1).getT(1).getT(1).getT(0).getT(0).getT(2);      // routing::ms_encode
		auto& sb2 = this->getT(1).getT(1).getT(1).getT(1).getT(1);                          // Widener_impl::sb2_t<NV>
		auto& mid_side2 = this->getT(1).getT(1).getT(1).getT(1).getT(1).getT(0);            // Widener_impl::mid_side2_t<NV>
		auto& xfader1 = this->getT(1).getT(1).getT(1).getT(1).getT(1).getT(0).getT(0);      // Widener_impl::xfader1_t<NV>
		auto& decoder1 = this->getT(1).getT(1).getT(1).getT(1).getT(1).getT(0).getT(1);     // routing::ms_decode
		auto& ms_splitter1 = this->getT(1).getT(1).getT(1).getT(1).getT(1).getT(0).getT(2); // Widener_impl::ms_splitter1_t<NV>
		auto& mid_chain1 = this->getT(1).getT(1).getT(1).getT(1).                           // Widener_impl::mid_chain1_t<NV>
                           getT(1).getT(0).getT(2).getT(0);
		auto& gain1 = this->getT(1).getT(1).getT(1).getT(1).                            // core::gain<NV>
                      getT(1).getT(0).getT(2).getT(0).
                      getT(0);
		auto& side_chain1 = this->getT(1).getT(1).getT(1).getT(1).                      // Widener_impl::side_chain1_t<NV>
                            getT(1).getT(0).getT(2).getT(1);
		auto& gain2 = this->getT(1).getT(1).getT(1).getT(1).                            // core::gain<NV>
                      getT(1).getT(0).getT(2).getT(1).
                      getT(0);
		auto& encoder1 = this->getT(1).getT(1).getT(1).getT(1).getT(1).getT(0).getT(3); // routing::ms_encode
		auto& mid_side3 = this->getT(1).getT(1).getT(2);                                // Widener_impl::mid_side3_t
		auto& encoder2 = this->getT(1).getT(1).getT(2).getT(0);                         // routing::ms_encode
		auto& ms_splitter2 = this->getT(1).getT(1).getT(2).getT(1);                     // Widener_impl::ms_splitter2_t
		auto& mid_chain2 = this->getT(1).getT(1).getT(2).getT(1).getT(0);               // Widener_impl::mid_chain2_t
		auto& side_chain2 = this->getT(1).getT(1).getT(2).getT(1).getT(1);              // Widener_impl::side_chain2_t
		auto& decoder2 = this->getT(1).getT(1).getT(2).getT(2);                         // routing::ms_decode
		auto& gain3 = this->getT(1).getT(1).getT(3);                                    // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		this->getParameterT(1).connectT(0, gain4); // KnbMidGain -> gain4::Gain
		
		this->getParameterT(2).connectT(0, gain); // KnbSideGain -> gain::Gain
		
		this->getParameterT(3).connectT(0, xfader1); // KnbMidSideBalance -> xfader1::Value
		
		this->getParameterT(4).connectT(0, gain3); // KnbMakeUpGain -> gain3::Gain
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, DryGain); // xfader -> DryGain::Gain
		xfader_p.getParameterT(1).connectT(0, WetGain); // xfader -> WetGain::Gain
		auto& xfader1_p = xfader1.getWrappedObject().getParameter();
		xfader1_p.getParameterT(0).connectT(0, gain1); // xfader1 -> gain1::Gain
		xfader1_p.getParameterT(1).connectT(0, gain2); // xfader1 -> gain2::Gain
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
		
		switcher.setParameterT(0, 0.); // control::xfader::Value
		
		;                            // gain4::Gain is automated
		gain4.setParameterT(1, 20.); // core::gain::Smoothing
		gain4.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // xfader1::Value is automated
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain2::Gain is automated
		gain2.setParameterT(1, 20.); // core::gain::Smoothing
		gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain3::Gain is automated
		gain3.setParameterT(1, 20.); // core::gain::Smoothing
		gain3.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, -12.);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 50.);
		this->setParameterT(4, 0.);
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
using Widener = wrap::node<Widener_impl::instance<NV>>;
}


