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

namespace Detuner_impl
{
// ==============================| Node & Parameter type declarations |==============================

DECLARE_PARAMETER_RANGE_SKEW(xfader_c0_0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using xfader_c0_0 = parameter::from0To1<core::gain<NV>, 
                                        0, 
                                        xfader_c0_0Range>;

template <int NV>
using xfader_c0_1 = parameter::from0To1<core::gain<NV>, 
                                        2, 
                                        xfader_c0_0Range>;

template <int NV>
using xfader_c0 = parameter::chain<ranges::Identity, 
                                   xfader_c0_0<NV>, 
                                   xfader_c0_1<NV>>;

template <int NV> using xfader_c1 = xfader_c0_0<NV>;

template <int NV>
using xfader_multimod = parameter::list<xfader_c0<NV>, xfader_c1<NV>>;

template <int NV>
using xfader_t = control::xfader<xfader_multimod<NV>, faders::rms>;

template <int NV>
using DRY_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>>;

template <int NV> using MidSide_c0 = xfader_c0_0<NV>;

DECLARE_PARAMETER_RANGE_SKEW(MidSide_c1Range, 
                             -100., 
                             -3., 
                             10.8556);

template <int NV>
using MidSide_c1 = parameter::from0To1<core::gain<NV>, 
                                       0, 
                                       MidSide_c1Range>;

template <int NV>
using MidSide_multimod = parameter::list<MidSide_c0<NV>, MidSide_c1<NV>>;

template <int NV>
using MidSide_t = control::xfader<MidSide_multimod<NV>, faders::rms>;

template <int NV>
using chainMid_t = container::chain<parameter::empty, 
                                    wrap::fix<2, core::gain<NV>>, 
                                    project::MicroShifter<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, project::MicroShifter<NV>>, 
                                 jdsp::jpanner<NV>>;

template <int NV> using chain1_t = chain_t<NV>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<2, chain_t<NV>>, 
                                  chain1_t<NV>>;

template <int NV>
using sb1_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, split1_t<NV>>>;

template <int NV>
using sb1_t = bypass::smoothed<20, sb1_t_<NV>>;
template <int NV>
using switcher_c0 = parameter::bypass<sb1_t<NV>>;

template <int NV> using chain3_t = chain_t<NV>;

template <int NV> using chain4_t = chain_t<NV>;

template <int NV>
using split2_t = container::split<parameter::empty, 
                                  wrap::fix<2, chain3_t<NV>>, 
                                  chain4_t<NV>>;

template <int NV>
using sb2_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, split2_t<NV>>>;

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
using chainSides_t = container::chain<parameter::empty, 
                                      wrap::fix<2, core::gain<NV>>, 
                                      softbypass_switch3_t<NV>>;

template <int NV>
using splitMidSide_t = container::split<parameter::empty, 
                                        wrap::fix<2, chainMid_t<NV>>, 
                                        chainSides_t<NV>>;

template <int NV>
using WET_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>, 
                               MidSide_t<NV>, 
                               splitMidSide_t<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, DRY_t<NV>>, 
                                 WET_t<NV>>;

namespace Detuner_t_parameters
{
// Parameter list for Detuner_impl::Detuner_t ------------------------------------------------------

DECLARE_PARAMETER_RANGE(KnbDryWet_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<Detuner_impl::xfader_t<NV>, 0>>;

template <int NV>
using KnbCenterDetune = parameter::chain<ranges::Identity, 
                                         parameter::plain<project::MicroShifter<NV>, 4>, 
                                         parameter::plain<project::MicroShifter<NV>, 4>, 
                                         parameter::plain<project::MicroShifter<NV>, 4>>;

template <int NV>
using KnbSideDetune = parameter::chain<ranges::Identity, 
                                       parameter::plain<project::MicroShifter<NV>, 4>, 
                                       parameter::plain<project::MicroShifter<NV>, 4>>;

DECLARE_PARAMETER_RANGE(KnbMidSideBalance_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbMidSideBalance = parameter::chain<KnbMidSideBalance_InputRange, 
                                           parameter::plain<Detuner_impl::MidSide_t<NV>, 0>>;

template <int NV>
using BtnDetuneSync = parameter::plain<Detuner_impl::switcher_t<NV>, 
                                       0>;
template <int NV>
using Detuner_t_plist = parameter::list<KnbDryWet<NV>, 
                                        KnbCenterDetune<NV>, 
                                        KnbSideDetune<NV>, 
                                        KnbMidSideBalance<NV>, 
                                        BtnDetuneSync<NV>>;
}

template <int NV>
using Detuner_t_ = container::chain<Detuner_t_parameters::Detuner_t_plist<NV>, 
                                    wrap::fix<2, xfader_t<NV>>, 
                                    split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Detuner_impl::Detuner_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Detuner);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(100)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x4362, 0x6E65, 0x6574, 
            0x4472, 0x7465, 0x6E75, 0x0065, 0x0000, 0xC2C8, 0x0000, 0x42C8, 
            0x0001, 0x41C8, 0x0000, 0x3F80, 0xCCCD, 0x3DCC, 0x025B, 0x0000, 
            0x4B00, 0x626E, 0x6953, 0x6564, 0x6544, 0x7574, 0x656E, 0x0000, 
            0xC800, 0x00C2, 0xC800, 0x6842, 0x9999, 0x00BE, 0x8000, 0xCD3F, 
            0xCCCC, 0x5B3D, 0x0003, 0x0000, 0x6E4B, 0x4D62, 0x6469, 0x6953, 
            0x6564, 0x6142, 0x616C, 0x636E, 0x0065, 0x0000, 0x0000, 0x0000, 
            0x42C8, 0x0000, 0x4248, 0x0000, 0x3F80, 0x0000, 0x0000, 0x045B, 
            0x0000, 0x4200, 0x6E74, 0x6544, 0x7574, 0x656E, 0x7953, 0x636E, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x8000, 0x003F, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                                               // Detuner_impl::xfader_t<NV>
		auto& split = this->getT(1);                                                // Detuner_impl::split_t<NV>
		auto& DRY = this->getT(1).getT(0);                                          // Detuner_impl::DRY_t<NV>
		auto& DryGain = this->getT(1).getT(0).getT(0);                              // core::gain<NV>
		auto& WET = this->getT(1).getT(1);                                          // Detuner_impl::WET_t<NV>
		auto& WetGain = this->getT(1).getT(1).getT(0);                              // core::gain<NV>
		auto& MidSide = this->getT(1).getT(1).getT(1);                              // Detuner_impl::MidSide_t<NV>
		auto& splitMidSide = this->getT(1).getT(1).getT(2);                         // Detuner_impl::splitMidSide_t<NV>
		auto& chainMid = this->getT(1).getT(1).getT(2).getT(0);                     // Detuner_impl::chainMid_t<NV>
		auto& gain = this->getT(1).getT(1).getT(2).getT(0).getT(0);                 // core::gain<NV>
		auto& faust = this->getT(1).getT(1).getT(2).getT(0).getT(1);                // project::MicroShifter<NV>
		auto& chainSides = this->getT(1).getT(1).getT(2).getT(1);                   // Detuner_impl::chainSides_t<NV>
		auto& gain1 = this->getT(1).getT(1).getT(2).getT(1).getT(0);                // core::gain<NV>
		auto& softbypass_switch3 = this->getT(1).getT(1).getT(2).getT(1).getT(1);   // Detuner_impl::softbypass_switch3_t<NV>
		auto& switcher = this->getT(1).getT(1).getT(2).getT(1).getT(1).getT(0);     // Detuner_impl::switcher_t<NV>
		auto& sb_container = this->getT(1).getT(1).getT(2).getT(1).getT(1).getT(1); // Detuner_impl::sb_container_t<NV>
		auto& sb1 = this->getT(1).getT(1).getT(2).getT(1).getT(1).getT(1).getT(0);  // Detuner_impl::sb1_t<NV>
		auto& split1 = this->getT(1).getT(1).getT(2).getT(1).                       // Detuner_impl::split1_t<NV>
                       getT(1).getT(1).getT(0).getT(0);
		auto& chain = this->getT(1).getT(1).getT(2).getT(1).                       // Detuner_impl::chain_t<NV>
                      getT(1).getT(1).getT(0).getT(0).
                      getT(0);
		auto& faust1 = this->getT(1).getT(1).getT(2).getT(1).getT(1).              // project::MicroShifter<NV>
                       getT(1).getT(0).getT(0).getT(0).getT(0);
		auto& jpanner = this->getT(1).getT(1).getT(2).getT(1).getT(1).             // jdsp::jpanner<NV>
                        getT(1).getT(0).getT(0).getT(0).getT(1);
		auto& chain1 = this->getT(1).getT(1).getT(2).getT(1).                      // Detuner_impl::chain1_t<NV>
                       getT(1).getT(1).getT(0).getT(0).
                       getT(1);
		auto& faust2 = this->getT(1).getT(1).getT(2).getT(1).getT(1).              // project::MicroShifter<NV>
                       getT(1).getT(0).getT(0).getT(1).getT(0);
		auto& jpanner1 = this->getT(1).getT(1).getT(2).getT(1).getT(1).            // jdsp::jpanner<NV>
                         getT(1).getT(0).getT(0).getT(1).getT(1);
		auto& sb2 = this->getT(1).getT(1).getT(2).getT(1).getT(1).getT(1).getT(1); // Detuner_impl::sb2_t<NV>
		auto& split2 = this->getT(1).getT(1).getT(2).getT(1).                      // Detuner_impl::split2_t<NV>
                       getT(1).getT(1).getT(1).getT(0);
		auto& chain3 = this->getT(1).getT(1).getT(2).getT(1).            // Detuner_impl::chain3_t<NV>
                       getT(1).getT(1).getT(1).getT(0).
                       getT(0);
		auto& faust3 = this->getT(1).getT(1).getT(2).getT(1).getT(1).    // project::MicroShifter<NV>
                       getT(1).getT(1).getT(0).getT(0).getT(0);
		auto& jpanner4 = this->getT(1).getT(1).getT(2).getT(1).getT(1).  // jdsp::jpanner<NV>
                         getT(1).getT(1).getT(0).getT(0).getT(1);
		auto& chain4 = this->getT(1).getT(1).getT(2).getT(1).            // Detuner_impl::chain4_t<NV>
                       getT(1).getT(1).getT(1).getT(0).
                       getT(1);
		auto& faust4 = this->getT(1).getT(1).getT(2).getT(1).getT(1).    // project::MicroShifter<NV>
                       getT(1).getT(1).getT(0).getT(1).getT(0);
		auto& jpanner5 = this->getT(1).getT(1).getT(2).getT(1).getT(1).  // jdsp::jpanner<NV>
                         getT(1).getT(1).getT(0).getT(1).getT(1);
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		auto& KnbCenterDetune_p = this->getParameterT(1);
		KnbCenterDetune_p.connectT(0, faust);  // KnbCenterDetune -> faust::shift
		KnbCenterDetune_p.connectT(1, faust3); // KnbCenterDetune -> faust3::shift
		KnbCenterDetune_p.connectT(2, faust4); // KnbCenterDetune -> faust4::shift
		
		auto& KnbSideDetune_p = this->getParameterT(2);
		KnbSideDetune_p.connectT(0, faust1); // KnbSideDetune -> faust1::shift
		KnbSideDetune_p.connectT(1, faust2); // KnbSideDetune -> faust2::shift
		
		this->getParameterT(3).connectT(0, MidSide); // KnbMidSideBalance -> MidSide::Value
		
		this->getParameterT(4).connectT(0, switcher); // BtnDetuneSync -> switcher::Value
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, DryGain); // xfader -> DryGain::Gain
		xfader_p.getParameterT(0).connectT(1, DryGain); // xfader -> DryGain::ResetValue
		xfader_p.getParameterT(1).connectT(0, WetGain); // xfader -> WetGain::Gain
		auto& MidSide_p = MidSide.getWrappedObject().getParameter();
		MidSide_p.getParameterT(0).connectT(0, gain);  // MidSide -> gain::Gain
		MidSide_p.getParameterT(1).connectT(0, gain1); // MidSide -> gain1::Gain
		auto& switcher_p = switcher.getWrappedObject().getParameter();
		switcher_p.getParameterT(0).connectT(0, sb1); // switcher -> sb1::Bypassed
		switcher_p.getParameterT(1).connectT(0, sb2); // switcher -> sb2::Bypassed
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                              // DryGain::Gain is automated
		DryGain.setParameterT(1, 20.); // core::gain::Smoothing
		;                              // DryGain::ResetValue is automated
		
		;                              // WetGain::Gain is automated
		WetGain.setParameterT(1, 20.); // core::gain::Smoothing
		WetGain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // MidSide::Value is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		faust.setParameterT(0, 1.);   // core::faust::ONOFF
		faust.setParameterT(1, 1.);   // core::faust::Volume
		faust.setParameterT(2, 100.); // core::faust::dry_wet
		faust.setParameterT(3, 1.);   // core::faust::gain
		;                             // faust::shift is automated
		faust.setParameterT(5, 0.);   // core::faust::window
		
		;                             // gain1::Gain is automated
		gain1.setParameterT(1, 20.);  // core::gain::Smoothing
		gain1.setParameterT(2, -1.3); // core::gain::ResetValue
		
		; // switcher::Value is automated
		
		faust1.setParameterT(0, 1.);   // core::faust::ONOFF
		faust1.setParameterT(1, 1.);   // core::faust::Volume
		faust1.setParameterT(2, 100.); // core::faust::dry_wet
		faust1.setParameterT(3, 1.);   // core::faust::gain
		;                              // faust1::shift is automated
		faust1.setParameterT(5, 75.);  // core::faust::window
		
		jpanner.setParameterT(0, -1.); // jdsp::jpanner::Pan
		jpanner.setParameterT(1, 1.);  // jdsp::jpanner::Rule
		
		faust2.setParameterT(0, 1.);   // core::faust::ONOFF
		faust2.setParameterT(1, 1.);   // core::faust::Volume
		faust2.setParameterT(2, 100.); // core::faust::dry_wet
		faust2.setParameterT(3, 1.);   // core::faust::gain
		;                              // faust2::shift is automated
		faust2.setParameterT(5, 75.);  // core::faust::window
		
		jpanner1.setParameterT(0, 1.); // jdsp::jpanner::Pan
		jpanner1.setParameterT(1, 1.); // jdsp::jpanner::Rule
		
		faust3.setParameterT(0, 1.);  // core::faust::ONOFF
		faust3.setParameterT(1, 1.);  // core::faust::Volume
		faust3.setParameterT(2, 1);   // core::faust::dry_wet
		faust3.setParameterT(3, 1.);  // core::faust::gain
		;                             // faust3::shift is automated
		faust3.setParameterT(5, 75.); // core::faust::window
		
		jpanner4.setParameterT(0, -1.); // jdsp::jpanner::Pan
		jpanner4.setParameterT(1, 1.);  // jdsp::jpanner::Rule
		
		faust4.setParameterT(0, 1.);  // core::faust::ONOFF
		faust4.setParameterT(1, 1.);  // core::faust::Volume
		faust4.setParameterT(2, 1);   // core::faust::dry_wet
		faust4.setParameterT(3, 1.);  // core::faust::gain
		;                             // faust4::shift is automated
		faust4.setParameterT(5, 75.); // core::faust::window
		
		jpanner5.setParameterT(0, 1.); // jdsp::jpanner::Pan
		jpanner5.setParameterT(1, 1.); // jdsp::jpanner::Rule
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 25.);
		this->setParameterT(2, -0.299999);
		this->setParameterT(3, 50.);
		this->setParameterT(4, 1.);
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
using Detuner = wrap::node<Detuner_impl::instance<NV>>;
}


