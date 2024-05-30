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

namespace Moog_ScriptFx_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using minmaxCutoff_mod = parameter::chain<ranges::Identity, 
                                          parameter::plain<project::MoogLpf2Poles<NV>, 0>, 
                                          parameter::plain<project::OberheimHpf4Poles<NV>, 0>>;

template <int NV>
using minmaxCutoff_t = control::minmax<NV, minmaxCutoff_mod<NV>>;

template <int NV>
using minmaxQ_mod = parameter::chain<ranges::Identity, 
                                     parameter::plain<project::MoogLpf2Poles<NV>, 1>, 
                                     parameter::plain<project::MoogLpf2Poles<NV>, 1>>;

template <int NV>
using minmaxQ_t = control::minmax<NV, minmaxQ_mod<NV>>;

template <int NV>
using minmax_mod = parameter::chain<ranges::Identity, 
                                    parameter::plain<project::OberheimHpf4Poles<NV>, 1>, 
                                    parameter::plain<project::OberheimHpf4Poles<NV>, 1>>;

template <int NV>
using minmax_t = control::minmax<NV, minmax_mod<NV>>;

template <int NV>
using sb4_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, project::MoogLpf2Poles<NV>>>;

template <int NV>
using sb4_t = bypass::smoothed<20, sb4_t_<NV>>;
template <int NV>
using switcher4_c0 = parameter::bypass<sb4_t<NV>>;

template <int NV>
using sb11_t_ = container::chain<parameter::empty, 
                                 wrap::fix<2, project::OberheimHpf4Poles<NV>>>;

template <int NV>
using sb11_t = bypass::smoothed<20, sb11_t_<NV>>;
template <int NV>
using switcher4_c1 = parameter::bypass<sb11_t<NV>>;

template <int NV>
using sb12_t_ = container::chain<parameter::empty, 
                                 wrap::fix<2, project::MoogLpf2Poles<NV>>, 
                                 project::OberheimHpf4Poles<NV>>;

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

namespace softbypass_switch7_t_parameters
{
DECLARE_PARAMETER_RANGE_STEP(Switch_InputRange, 
                             0., 
                             2., 
                             1.);

template <int NV>
using Switch = parameter::chain<Switch_InputRange, 
                                parameter::plain<Moog_ScriptFx_impl::switcher4_t<NV>, 0>>;

}

template <int NV>
using softbypass_switch7_t = container::chain<softbypass_switch7_t_parameters::Switch<NV>, 
                                              wrap::fix<2, switcher4_t<NV>>, 
                                              sb_container4_t<NV>>;

namespace Moog_ScriptFx_t_parameters
{
// Parameter list for Moog_ScriptFx_impl::Moog_ScriptFx_t ------------------------------------------

DECLARE_PARAMETER_RANGE_SKEW(Cutoff_InputRange, 
                             20., 
                             20000., 
                             0.229905);
DECLARE_PARAMETER_RANGE_SKEW(Cutoff_1Range, 
                             20., 
                             20000., 
                             0.498918);

template <int NV>
using Cutoff_1 = parameter::from0To1<project::MoogLpf2Poles<NV>, 
                                     0, 
                                     Cutoff_1Range>;

DECLARE_PARAMETER_RANGE_SKEW(Cutoff_2Range, 
                             20., 
                             20000., 
                             0.185895);

template <int NV>
using Cutoff_2 = parameter::from0To1<project::OberheimHpf4Poles<NV>, 
                                     0, 
                                     Cutoff_2Range>;

template <int NV>
using Cutoff = parameter::chain<Cutoff_InputRange, 
                                parameter::plain<Moog_ScriptFx_impl::minmaxCutoff_t<NV>, 0>, 
                                Cutoff_1<NV>, 
                                Cutoff_2<NV>>;

DECLARE_PARAMETER_RANGE_SKEW(Q_InputRange, 
                             0.7, 
                             10., 
                             0.201849);

template <int NV>
using Q = parameter::chain<Q_InputRange, 
                           parameter::plain<Moog_ScriptFx_impl::minmaxQ_t<NV>, 0>>;

template <int NV>
using Type = parameter::plain<Moog_ScriptFx_impl::softbypass_switch7_t<NV>, 
                              0>;
using Poles = parameter::empty;
template <int NV>
using Moog_ScriptFx_t_plist = parameter::list<Cutoff<NV>, 
                                              Q<NV>, 
                                              Type<NV>, 
                                              Poles>;
}

template <int NV>
using Moog_ScriptFx_t_ = container::chain<Moog_ScriptFx_t_parameters::Moog_ScriptFx_t_plist<NV>, 
                                          wrap::fix<2, minmaxCutoff_t<NV>>, 
                                          minmaxQ_t<NV>, 
                                          minmax_t<NV>, 
                                          softbypass_switch7_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Moog_ScriptFx_impl::Moog_ScriptFx_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Moog_ScriptFx);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(62)
		{
			0x005B, 0x0000, 0x4300, 0x7475, 0x666F, 0x0066, 0x0000, 0x41A0, 
            0x4000, 0x469C, 0x0000, 0x447A, 0x6C1A, 0x3E6B, 0x0000, 0x0000, 
            0x015B, 0x0000, 0x5100, 0x3300, 0x3333, 0x003F, 0x2000, 0x0041, 
            0x8000, 0x873F, 0x4EB1, 0x003E, 0x0000, 0x5B00, 0x0002, 0x0000, 
            0x7954, 0x6570, 0x0000, 0x0000, 0x0000, 0x0000, 0x0040, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x0003, 0x0000, 0x6F50, 
            0x656C, 0x0073, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& minmaxCutoff = this->getT(0);                   // Moog_ScriptFx_impl::minmaxCutoff_t<NV>
		auto& minmaxQ = this->getT(1);                        // Moog_ScriptFx_impl::minmaxQ_t<NV>
		auto& minmax = this->getT(2);                         // Moog_ScriptFx_impl::minmax_t<NV>
		auto& softbypass_switch7 = this->getT(3);             // Moog_ScriptFx_impl::softbypass_switch7_t<NV>
		auto& switcher4 = this->getT(3).getT(0);              // Moog_ScriptFx_impl::switcher4_t<NV>
		auto& sb_container4 = this->getT(3).getT(1);          // Moog_ScriptFx_impl::sb_container4_t<NV>
		auto& sb4 = this->getT(3).getT(1).getT(0);            // Moog_ScriptFx_impl::sb4_t<NV>
		auto& faust4 = this->getT(3).getT(1).getT(0).getT(0); // project::MoogLpf2Poles<NV>
		auto& sb11 = this->getT(3).getT(1).getT(1);           // Moog_ScriptFx_impl::sb11_t<NV>
		auto& faust = this->getT(3).getT(1).getT(1).getT(0);  // project::OberheimHpf4Poles<NV>
		auto& sb12 = this->getT(3).getT(1).getT(2);           // Moog_ScriptFx_impl::sb12_t<NV>
		auto& faust3 = this->getT(3).getT(1).getT(2).getT(0); // project::MoogLpf2Poles<NV>
		auto& faust1 = this->getT(3).getT(1).getT(2).getT(1); // project::OberheimHpf4Poles<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		softbypass_switch7.getParameterT(0).connectT(0, switcher4); // Switch -> switcher4::Value
		auto& Cutoff_p = this->getParameterT(0);
		Cutoff_p.connectT(0, minmaxCutoff); // Cutoff -> minmaxCutoff::Value
		Cutoff_p.connectT(1, faust3);       // Cutoff -> faust3::Cutofffrequency
		Cutoff_p.connectT(2, faust1);       // Cutoff -> faust1::Cutofffrequency
		
		this->getParameterT(1).connectT(0, minmaxQ); // Q -> minmaxQ::Value
		
		this->getParameterT(2).connectT(0, softbypass_switch7); // Type -> softbypass_switch7::Switch
		
		// Modulation Connections ------------------------------------------------------------------
		
		minmaxCutoff.getWrappedObject().getParameter().connectT(0, faust4); // minmaxCutoff -> faust4::Cutofffrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(1, faust);  // minmaxCutoff -> faust::Cutofffrequency
		minmaxQ.getWrappedObject().getParameter().connectT(0, faust3);      // minmaxQ -> faust3::Q
		minmaxQ.getWrappedObject().getParameter().connectT(1, faust4);      // minmaxQ -> faust4::Q
		minmax.getWrappedObject().getParameter().connectT(0, faust);        // minmax -> faust::Q
		minmax.getWrappedObject().getParameter().connectT(1, faust1);       // minmax -> faust1::Q
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
		minmaxQ.setParameterT(1, 0.5);      // control::minmax::Minimum
		minmaxQ.setParameterT(2, 24.0363);  // control::minmax::Maximum
		minmaxQ.setParameterT(3, 0.235409); // control::minmax::Skew
		minmaxQ.setParameterT(4, 0.);       // control::minmax::Step
		minmaxQ.setParameterT(5, 0.);       // control::minmax::Polarity
		
		minmax.setParameterT(0, 0.);  // control::minmax::Value
		minmax.setParameterT(1, 0.3); // control::minmax::Minimum
		minmax.setParameterT(2, 9.9); // control::minmax::Maximum
		minmax.setParameterT(3, 1.);  // control::minmax::Skew
		minmax.setParameterT(4, 0.);  // control::minmax::Step
		minmax.setParameterT(5, 0.);  // control::minmax::Polarity
		
		; // softbypass_switch7::Switch is automated
		
		; // switcher4::Value is automated
		
		; // faust4::Cutofffrequency is automated
		; // faust4::Q is automated
		
		; // faust::Cutofffrequency is automated
		; // faust::Q is automated
		
		; // faust3::Cutofffrequency is automated
		; // faust3::Q is automated
		
		; // faust1::Cutofffrequency is automated
		; // faust1::Q is automated
		
		this->setParameterT(0, 1000.);
		this->setParameterT(1, 1.);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 0.);
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
using Moog_ScriptFx = wrap::node<Moog_ScriptFx_impl::instance<NV>>;
}


