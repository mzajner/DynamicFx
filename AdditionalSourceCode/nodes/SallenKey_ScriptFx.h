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

namespace SallenKey_ScriptFx_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using minmaxCutoff_mod = parameter::chain<ranges::Identity, 
                                          parameter::plain<project::SallenKeyLpf<NV>, 1>, 
                                          parameter::plain<project::SallenKeyLpf<NV>, 1>, 
                                          parameter::plain<project::SallenKeyLpf<NV>, 1>, 
                                          parameter::plain<project::SallenKeyHpf<NV>, 0>, 
                                          parameter::plain<project::SallenKeyHpf<NV>, 0>, 
                                          parameter::plain<project::SallenKeyHpf<NV>, 0>, 
                                          parameter::plain<project::SallenKeyBpf<NV>, 0>, 
                                          parameter::plain<project::SallenKeyBpf<NV>, 0>, 
                                          parameter::plain<project::SallenKeyBpf<NV>, 0>>;

template <int NV>
using minmaxCutoff_t = control::minmax<NV, minmaxCutoff_mod<NV>>;

template <int NV>
using minmaxQ_mod = parameter::chain<ranges::Identity, 
                                     parameter::plain<project::SallenKeyLpf<NV>, 0>, 
                                     parameter::plain<project::SallenKeyHpf<NV>, 1>, 
                                     parameter::plain<project::SallenKeyBpf<NV>, 1>, 
                                     parameter::plain<project::SallenKeyLpf<NV>, 0>, 
                                     parameter::plain<project::SallenKeyLpf<NV>, 0>, 
                                     parameter::plain<project::SallenKeyHpf<NV>, 1>, 
                                     parameter::plain<project::SallenKeyHpf<NV>, 1>, 
                                     parameter::plain<project::SallenKeyBpf<NV>, 1>, 
                                     parameter::plain<project::SallenKeyBpf<NV>, 1>>;

template <int NV>
using minmaxQ_t = control::minmax<NV, minmaxQ_mod<NV>>;

template <int NV>
using sb13_t_ = container::chain<parameter::empty, 
                                 wrap::fix<2, project::SallenKeyLpf<NV>>>;

template <int NV>
using sb13_t = bypass::smoothed<20, sb13_t_<NV>>;
template <int NV>
using switcher5_c0 = parameter::bypass<sb13_t<NV>>;

template <int NV>
using sb14_t_ = container::chain<parameter::empty, 
                                 wrap::fix<2, project::SallenKeyLpf<NV>>, 
                                 project::SallenKeyLpf<NV>>;

template <int NV>
using sb14_t = bypass::smoothed<20, sb14_t_<NV>>;
template <int NV>
using switcher5_c1 = parameter::bypass<sb14_t<NV>>;

template <int NV>
using switcher5_multimod = parameter::list<switcher5_c0<NV>, switcher5_c1<NV>>;

template <int NV>
using switcher5_t = control::xfader<switcher5_multimod<NV>, faders::switcher>;

template <int NV>
using sb_container5_t = container::chain<parameter::empty, 
                                         wrap::fix<2, sb13_t<NV>>, 
                                         sb14_t<NV>>;

template <int NV>
using softbypass_switch6_t = container::chain<parameter::empty, 
                                              wrap::fix<2, switcher5_t<NV>>, 
                                              sb_container5_t<NV>>;

template <int NV>
using sb4_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, softbypass_switch6_t<NV>>>;

template <int NV>
using sb4_t = bypass::smoothed<20, sb4_t_<NV>>;
template <int NV>
using switcher4_c0 = parameter::bypass<sb4_t<NV>>;

template <int NV>
using sb17_t_ = container::chain<parameter::empty, 
                                 wrap::fix<2, project::SallenKeyHpf<NV>>>;

template <int NV>
using sb17_t = bypass::smoothed<20, sb17_t_<NV>>;
template <int NV>
using switcher7_c0 = parameter::bypass<sb17_t<NV>>;

template <int NV>
using sb18_t_ = container::chain<parameter::empty, 
                                 wrap::fix<2, project::SallenKeyHpf<NV>>, 
                                 project::SallenKeyHpf<NV>>;

template <int NV>
using sb18_t = bypass::smoothed<20, sb18_t_<NV>>;
template <int NV>
using switcher7_c1 = parameter::bypass<sb18_t<NV>>;

template <int NV>
using switcher7_multimod = parameter::list<switcher7_c0<NV>, switcher7_c1<NV>>;

template <int NV>
using switcher7_t = control::xfader<switcher7_multimod<NV>, faders::switcher>;

template <int NV>
using sb_container7_t = container::chain<parameter::empty, 
                                         wrap::fix<2, sb17_t<NV>>, 
                                         sb18_t<NV>>;

template <int NV>
using softbypass_switch8_t = container::chain<parameter::empty, 
                                              wrap::fix<2, switcher7_t<NV>>, 
                                              sb_container7_t<NV>>;

template <int NV>
using sb11_t_ = container::chain<parameter::empty, 
                                 wrap::fix<2, softbypass_switch8_t<NV>>>;

template <int NV>
using sb11_t = bypass::smoothed<20, sb11_t_<NV>>;
template <int NV>
using switcher4_c1 = parameter::bypass<sb11_t<NV>>;

template <int NV>
using sb19_t_ = container::chain<parameter::empty, 
                                 wrap::fix<2, project::SallenKeyBpf<NV>>>;

template <int NV>
using sb19_t = bypass::smoothed<20, sb19_t_<NV>>;
template <int NV>
using switcher8_c0 = parameter::bypass<sb19_t<NV>>;

template <int NV>
using sb20_t_ = container::chain<parameter::empty, 
                                 wrap::fix<2, project::SallenKeyBpf<NV>>, 
                                 project::SallenKeyBpf<NV>>;

template <int NV>
using sb20_t = bypass::smoothed<20, sb20_t_<NV>>;
template <int NV>
using switcher8_c1 = parameter::bypass<sb20_t<NV>>;

template <int NV>
using switcher8_multimod = parameter::list<switcher8_c0<NV>, switcher8_c1<NV>>;

template <int NV>
using switcher8_t = control::xfader<switcher8_multimod<NV>, faders::switcher>;

template <int NV>
using sb_container8_t = container::chain<parameter::empty, 
                                         wrap::fix<2, sb19_t<NV>>, 
                                         sb20_t<NV>>;

template <int NV>
using softbypass_switch9_t = container::chain<parameter::empty, 
                                              wrap::fix<2, switcher8_t<NV>>, 
                                              sb_container8_t<NV>>;

template <int NV>
using sb12_t_ = container::chain<parameter::empty, 
                                 wrap::fix<2, softbypass_switch9_t<NV>>>;

template <int NV>
using sb12_t = bypass::smoothed<20, sb12_t_<NV>>;
template <int NV>
using switcher4_c2 = parameter::bypass<sb12_t<NV>>;

template <int NV>
using switcher4_multimod = parameter::list<switcher4_c0<NV>, 
                                           switcher4_c1<NV>, 
                                           switcher4_c2<NV>>;

template <int NV>
using switcher4_t = control::xfader<switcher4_multimod<NV>, faders::switcher>;

template <int NV>
using sb_container4_t = container::chain<parameter::empty, 
                                         wrap::fix<2, sb4_t<NV>>, 
                                         sb11_t<NV>, 
                                         sb12_t<NV>>;

template <int NV>
using softbypass_switch7_t = container::chain<parameter::empty, 
                                              wrap::fix<2, switcher4_t<NV>>, 
                                              sb_container4_t<NV>>;

namespace SallenKey_ScriptFx_t_parameters
{
// Parameter list for SallenKey_ScriptFx_impl::SallenKey_ScriptFx_t --------------------------------

DECLARE_PARAMETER_RANGE_SKEW(Cutoff_InputRange, 
                             20., 
                             20000., 
                             0.229905);

template <int NV>
using Cutoff = parameter::chain<Cutoff_InputRange, 
                                parameter::plain<SallenKey_ScriptFx_impl::minmaxCutoff_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(Q_InputRange, 
                             0.3, 
                             8., 
                             0.289065);

template <int NV>
using Q = parameter::chain<Q_InputRange, 
                           parameter::plain<SallenKey_ScriptFx_impl::minmaxQ_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_STEP(Type_InputRange, 
                             0., 
                             2., 
                             1.);

template <int NV>
using Type = parameter::chain<Type_InputRange, 
                              parameter::plain<SallenKey_ScriptFx_impl::switcher4_t<NV>, 0>>;

template <int NV>
using Poles = parameter::chain<ranges::Identity, 
                               parameter::plain<SallenKey_ScriptFx_impl::switcher5_t<NV>, 0>, 
                               parameter::plain<SallenKey_ScriptFx_impl::switcher7_t<NV>, 0>, 
                               parameter::plain<SallenKey_ScriptFx_impl::switcher8_t<NV>, 0>>;

using BpSpread = parameter::empty;
template <int NV>
using SallenKey_ScriptFx_t_plist = parameter::list<Cutoff<NV>, 
                                                   Q<NV>, 
                                                   Type<NV>, 
                                                   Poles<NV>, 
                                                   BpSpread>;
}

template <int NV>
using SallenKey_ScriptFx_t_ = container::chain<SallenKey_ScriptFx_t_parameters::SallenKey_ScriptFx_t_plist<NV>, 
                                               wrap::fix<2, minmaxCutoff_t<NV>>, 
                                               minmaxQ_t<NV>, 
                                               softbypass_switch7_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public SallenKey_ScriptFx_impl::SallenKey_ScriptFx_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(SallenKey_ScriptFx);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(78)
		{
			0x005B, 0x0000, 0x4300, 0x7475, 0x666F, 0x0066, 0x0000, 0x41A0, 
            0x4000, 0x469C, 0x0000, 0x447A, 0x6C1A, 0x3E6B, 0x0000, 0x0000, 
            0x015B, 0x0000, 0x5100, 0x9A00, 0x9999, 0x003E, 0x0000, 0x0041, 
            0x8000, 0x4E3F, 0x9400, 0x003E, 0x0000, 0x5B00, 0x0002, 0x0000, 
            0x7954, 0x6570, 0x0000, 0x0000, 0x0000, 0x0000, 0x0040, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x0003, 0x0000, 0x6F50, 
            0x656C, 0x0073, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x045B, 0x0000, 0x4200, 0x5370, 
            0x7270, 0x6165, 0x0064, 0x0000, 0x0000, 0x0000, 0x42C8, 0x0000, 
            0x4248, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& minmaxCutoff = this->getT(0);                                           // SallenKey_ScriptFx_impl::minmaxCutoff_t<NV>
		auto& minmaxQ = this->getT(1);                                                // SallenKey_ScriptFx_impl::minmaxQ_t<NV>
		auto& softbypass_switch7 = this->getT(2);                                     // SallenKey_ScriptFx_impl::softbypass_switch7_t<NV>
		auto& switcher4 = this->getT(2).getT(0);                                      // SallenKey_ScriptFx_impl::switcher4_t<NV>
		auto& sb_container4 = this->getT(2).getT(1);                                  // SallenKey_ScriptFx_impl::sb_container4_t<NV>
		auto& sb4 = this->getT(2).getT(1).getT(0);                                    // SallenKey_ScriptFx_impl::sb4_t<NV>
		auto& softbypass_switch6 = this->getT(2).getT(1).getT(0).getT(0);             // SallenKey_ScriptFx_impl::softbypass_switch6_t<NV>
		auto& switcher5 = this->getT(2).getT(1).getT(0).getT(0).getT(0);              // SallenKey_ScriptFx_impl::switcher5_t<NV>
		auto& sb_container5 = this->getT(2).getT(1).getT(0).getT(0).getT(1);          // SallenKey_ScriptFx_impl::sb_container5_t<NV>
		auto& sb13 = this->getT(2).getT(1).getT(0).getT(0).getT(1).getT(0);           // SallenKey_ScriptFx_impl::sb13_t<NV>
		auto& faust = this->getT(2).getT(1).getT(0).getT(0).getT(1).getT(0).getT(0);  // project::SallenKeyLpf<NV>
		auto& sb14 = this->getT(2).getT(1).getT(0).getT(0).getT(1).getT(1);           // SallenKey_ScriptFx_impl::sb14_t<NV>
		auto& faust1 = this->getT(2).getT(1).getT(0).getT(0).getT(1).getT(1).getT(0); // project::SallenKeyLpf<NV>
		auto& faust2 = this->getT(2).getT(1).getT(0).getT(0).getT(1).getT(1).getT(1); // project::SallenKeyLpf<NV>
		auto& sb11 = this->getT(2).getT(1).getT(1);                                   // SallenKey_ScriptFx_impl::sb11_t<NV>
		auto& softbypass_switch8 = this->getT(2).getT(1).getT(1).getT(0);             // SallenKey_ScriptFx_impl::softbypass_switch8_t<NV>
		auto& switcher7 = this->getT(2).getT(1).getT(1).getT(0).getT(0);              // SallenKey_ScriptFx_impl::switcher7_t<NV>
		auto& sb_container7 = this->getT(2).getT(1).getT(1).getT(0).getT(1);          // SallenKey_ScriptFx_impl::sb_container7_t<NV>
		auto& sb17 = this->getT(2).getT(1).getT(1).getT(0).getT(1).getT(0);           // SallenKey_ScriptFx_impl::sb17_t<NV>
		auto& faust3 = this->getT(2).getT(1).getT(1).getT(0).getT(1).getT(0).getT(0); // project::SallenKeyHpf<NV>
		auto& sb18 = this->getT(2).getT(1).getT(1).getT(0).getT(1).getT(1);           // SallenKey_ScriptFx_impl::sb18_t<NV>
		auto& faust4 = this->getT(2).getT(1).getT(1).getT(0).getT(1).getT(1).getT(0); // project::SallenKeyHpf<NV>
		auto& faust5 = this->getT(2).getT(1).getT(1).getT(0).getT(1).getT(1).getT(1); // project::SallenKeyHpf<NV>
		auto& sb12 = this->getT(2).getT(1).getT(2);                                   // SallenKey_ScriptFx_impl::sb12_t<NV>
		auto& softbypass_switch9 = this->getT(2).getT(1).getT(2).getT(0);             // SallenKey_ScriptFx_impl::softbypass_switch9_t<NV>
		auto& switcher8 = this->getT(2).getT(1).getT(2).getT(0).getT(0);              // SallenKey_ScriptFx_impl::switcher8_t<NV>
		auto& sb_container8 = this->getT(2).getT(1).getT(2).getT(0).getT(1);          // SallenKey_ScriptFx_impl::sb_container8_t<NV>
		auto& sb19 = this->getT(2).getT(1).getT(2).getT(0).getT(1).getT(0);           // SallenKey_ScriptFx_impl::sb19_t<NV>
		auto& faust6 = this->getT(2).getT(1).getT(2).getT(0).getT(1).getT(0).getT(0); // project::SallenKeyBpf<NV>
		auto& sb20 = this->getT(2).getT(1).getT(2).getT(0).getT(1).getT(1);           // SallenKey_ScriptFx_impl::sb20_t<NV>
		auto& faust7 = this->getT(2).getT(1).getT(2).getT(0).getT(1).getT(1).getT(0); // project::SallenKeyBpf<NV>
		auto& faust8 = this->getT(2).getT(1).getT(2).getT(0).getT(1).getT(1).getT(1); // project::SallenKeyBpf<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, minmaxCutoff); // Cutoff -> minmaxCutoff::Value
		
		this->getParameterT(1).connectT(0, minmaxQ); // Q -> minmaxQ::Value
		
		this->getParameterT(2).connectT(0, switcher4); // Type -> switcher4::Value
		
		auto& Poles_p = this->getParameterT(3);
		Poles_p.connectT(0, switcher5); // Poles -> switcher5::Value
		Poles_p.connectT(1, switcher7); // Poles -> switcher7::Value
		Poles_p.connectT(2, switcher8); // Poles -> switcher8::Value
		
		// Modulation Connections ------------------------------------------------------------------
		
		minmaxCutoff.getWrappedObject().getParameter().connectT(0, faust);  // minmaxCutoff -> faust::CutoffFrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(1, faust1); // minmaxCutoff -> faust1::CutoffFrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(2, faust2); // minmaxCutoff -> faust2::CutoffFrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(3, faust3); // minmaxCutoff -> faust3::CutoffFrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(4, faust4); // minmaxCutoff -> faust4::CutoffFrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(5, faust5); // minmaxCutoff -> faust5::CutoffFrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(6, faust6); // minmaxCutoff -> faust6::CutoffFrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(7, faust7); // minmaxCutoff -> faust7::CutoffFrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(8, faust8); // minmaxCutoff -> faust8::CutoffFrequency
		minmaxQ.getWrappedObject().getParameter().connectT(0, faust);       // minmaxQ -> faust::Q
		minmaxQ.getWrappedObject().getParameter().connectT(1, faust3);      // minmaxQ -> faust3::Q
		minmaxQ.getWrappedObject().getParameter().connectT(2, faust6);      // minmaxQ -> faust6::Q
		minmaxQ.getWrappedObject().getParameter().connectT(3, faust1);      // minmaxQ -> faust1::Q
		minmaxQ.getWrappedObject().getParameter().connectT(4, faust2);      // minmaxQ -> faust2::Q
		minmaxQ.getWrappedObject().getParameter().connectT(5, faust4);      // minmaxQ -> faust4::Q
		minmaxQ.getWrappedObject().getParameter().connectT(6, faust5);      // minmaxQ -> faust5::Q
		minmaxQ.getWrappedObject().getParameter().connectT(7, faust7);      // minmaxQ -> faust7::Q
		minmaxQ.getWrappedObject().getParameter().connectT(8, faust8);      // minmaxQ -> faust8::Q
		auto& switcher5_p = switcher5.getWrappedObject().getParameter();
		switcher5_p.getParameterT(0).connectT(0, sb13); // switcher5 -> sb13::Bypassed
		switcher5_p.getParameterT(1).connectT(0, sb14); // switcher5 -> sb14::Bypassed
		auto& switcher7_p = switcher7.getWrappedObject().getParameter();
		switcher7_p.getParameterT(0).connectT(0, sb17); // switcher7 -> sb17::Bypassed
		switcher7_p.getParameterT(1).connectT(0, sb18); // switcher7 -> sb18::Bypassed
		auto& switcher8_p = switcher8.getWrappedObject().getParameter();
		switcher8_p.getParameterT(0).connectT(0, sb19); // switcher8 -> sb19::Bypassed
		switcher8_p.getParameterT(1).connectT(0, sb20); // switcher8 -> sb20::Bypassed
		auto& switcher4_p = switcher4.getWrappedObject().getParameter();
		switcher4_p.getParameterT(0).connectT(0, sb4);  // switcher4 -> sb4::Bypassed
		switcher4_p.getParameterT(1).connectT(0, sb11); // switcher4 -> sb11::Bypassed
		switcher4_p.getParameterT(2).connectT(0, sb12); // switcher4 -> sb12::Bypassed
		
		// Default Values --------------------------------------------------------------------------
		
		;                                        // minmaxCutoff::Value is automated
		minmaxCutoff.setParameterT(1, 20.);      // control::minmax::Minimum
		minmaxCutoff.setParameterT(2, 20000.);   // control::minmax::Maximum
		minmaxCutoff.setParameterT(3, 0.229905); // control::minmax::Skew
		minmaxCutoff.setParameterT(4, 0.);       // control::minmax::Step
		minmaxCutoff.setParameterT(5, 0.);       // control::minmax::Polarity
		
		;                                   // minmaxQ::Value is automated
		minmaxQ.setParameterT(1, 0.3);      // control::minmax::Minimum
		minmaxQ.setParameterT(2, 8.);       // control::minmax::Maximum
		minmaxQ.setParameterT(3, 0.289065); // control::minmax::Skew
		minmaxQ.setParameterT(4, 0.);       // control::minmax::Step
		minmaxQ.setParameterT(5, 0.);       // control::minmax::Polarity
		
		; // switcher4::Value is automated
		
		; // switcher5::Value is automated
		
		; // faust::Q is automated
		; // faust::CutoffFrequency is automated
		
		; // faust1::Q is automated
		; // faust1::CutoffFrequency is automated
		
		; // faust2::Q is automated
		; // faust2::CutoffFrequency is automated
		
		; // switcher7::Value is automated
		
		; // faust3::CutoffFrequency is automated
		; // faust3::Q is automated
		
		; // faust4::CutoffFrequency is automated
		; // faust4::Q is automated
		
		; // faust5::CutoffFrequency is automated
		; // faust5::Q is automated
		
		; // switcher8::Value is automated
		
		; // faust6::CutoffFrequency is automated
		; // faust6::Q is automated
		
		; // faust7::CutoffFrequency is automated
		; // faust7::Q is automated
		
		; // faust8::CutoffFrequency is automated
		; // faust8::Q is automated
		
		this->setParameterT(0, 1000.);
		this->setParameterT(1, 1.);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 0.);
		this->setParameterT(4, 50.);
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
using SallenKey_ScriptFx = wrap::node<SallenKey_ScriptFx_impl::instance<NV>>;
}


