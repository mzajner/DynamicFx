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

namespace Korg_ScriptFx_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using pma_unscaled_mod = parameter::chain<ranges::Identity, 
                                          parameter::plain<project::KorgHpf2Poles<NV>, 0>, 
                                          parameter::plain<project::KorgHpf2Poles<NV>, 0>, 
                                          parameter::plain<project::KorgHpf2Poles<NV>, 0>>;

template <int NV>
using pma_unscaled_t = control::pma_unscaled<NV, pma_unscaled_mod<NV>>;

template <int NV>
using pma_unscaled1_mod = parameter::chain<ranges::Identity, 
                                           parameter::plain<project::KorgLpf2Poles<NV>, 0>, 
                                           parameter::plain<project::KorgLpf2Poles<NV>, 0>, 
                                           parameter::plain<project::KorgLpf2Poles<NV>, 0>>;

template <int NV>
using pma_unscaled1_t = control::pma_unscaled<NV, pma_unscaled1_mod<NV>>;

template <int NV>
using minmaxCutoff_mod = parameter::chain<ranges::Identity, 
                                          parameter::plain<project::KorgLpf2Poles<NV>, 0>, 
                                          parameter::plain<project::KorgLpf2Poles<NV>, 0>, 
                                          parameter::plain<project::KorgLpf2Poles<NV>, 0>, 
                                          parameter::plain<project::KorgHpf2Poles<NV>, 0>, 
                                          parameter::plain<project::KorgHpf2Poles<NV>, 0>, 
                                          parameter::plain<project::KorgHpf2Poles<NV>, 0>, 
                                          parameter::plain<pma_unscaled_t<NV>, 0>, 
                                          parameter::plain<pma_unscaled1_t<NV>, 0>>;

template <int NV>
using minmaxCutoff_t = control::minmax<NV, minmaxCutoff_mod<NV>>;

template <int NV>
using minmaxQ_mod = parameter::chain<ranges::Identity, 
                                     parameter::plain<project::KorgLpf2Poles<NV>, 1>, 
                                     parameter::plain<project::KorgLpf2Poles<NV>, 1>, 
                                     parameter::plain<project::KorgLpf2Poles<NV>, 1>, 
                                     parameter::plain<project::KorgHpf2Poles<NV>, 1>, 
                                     parameter::plain<project::KorgHpf2Poles<NV>, 1>, 
                                     parameter::plain<project::KorgHpf2Poles<NV>, 1>, 
                                     parameter::plain<project::KorgHpf2Poles<NV>, 1>, 
                                     parameter::plain<project::KorgLpf2Poles<NV>, 1>, 
                                     parameter::plain<project::KorgHpf2Poles<NV>, 1>, 
                                     parameter::plain<project::KorgLpf2Poles<NV>, 1>, 
                                     parameter::plain<project::KorgHpf2Poles<NV>, 1>, 
                                     parameter::plain<project::KorgLpf2Poles<NV>, 1>>;

template <int NV>
using minmaxQ_t = control::minmax<NV, minmaxQ_mod<NV>>;

using switcher1_multimod = parameter::list<parameter::empty, parameter::empty>;

using switcher1_t = control::xfader<switcher1_multimod, faders::switcher>;

template <int NV>
using sb5_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, project::KorgLpf2Poles<NV>>>;

template <int NV>
using sb5_t = bypass::smoothed<20, sb5_t_<NV>>;

template <int NV>
using sb6_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, project::KorgLpf2Poles<NV>>, 
                                project::KorgLpf2Poles<NV>>;

template <int NV>
using sb6_t = bypass::smoothed<20, sb6_t_<NV>>;

template <int NV>
using sb_container1_t = container::chain<parameter::empty, 
                                         wrap::fix<2, sb5_t<NV>>, 
                                         sb6_t<NV>>;

template <int NV>
using softbypass_switch3_t = container::chain<parameter::empty, 
                                              wrap::fix<2, switcher1_t>, 
                                              sb_container1_t<NV>>;

template <int NV>
using sb1_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, softbypass_switch3_t<NV>>>;

template <int NV>
using sb1_t = bypass::smoothed<20, sb1_t_<NV>>;
template <int NV>
using switcher_c0_0 = parameter::bypass<sb1_t<NV>>;

template <int NV>
using switcher_c0 = parameter::chain<ranges::Identity, 
                                     switcher_c0_0<NV>, 
                                     switcher_c0_0<NV>>;

using switcher2_multimod = switcher1_multimod;

using switcher2_t = control::xfader<switcher2_multimod, faders::switcher>;

template <int NV>
using sb7_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, project::KorgHpf2Poles<NV>>>;

template <int NV>
using sb7_t = bypass::smoothed<20, sb7_t_<NV>>;

template <int NV>
using sb8_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, project::KorgHpf2Poles<NV>>, 
                                project::KorgHpf2Poles<NV>>;

template <int NV>
using sb8_t = bypass::smoothed<20, sb8_t_<NV>>;

template <int NV>
using sb_container2_t = container::chain<parameter::empty, 
                                         wrap::fix<2, sb7_t<NV>>, 
                                         sb8_t<NV>>;

template <int NV>
using softbypass_switch4_t = container::chain<parameter::empty, 
                                              wrap::fix<2, switcher2_t>, 
                                              sb_container2_t<NV>>;

template <int NV>
using sb2_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, softbypass_switch4_t<NV>>>;

template <int NV>
using sb2_t = bypass::smoothed<20, sb2_t_<NV>>;
template <int NV>
using switcher_c1 = parameter::bypass<sb2_t<NV>>;

using switcher3_multimod = switcher1_multimod;

using switcher3_t = control::xfader<switcher3_multimod, faders::switcher>;

template <int NV>
using sb9_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, project::KorgHpf2Poles<NV>>, 
                                project::KorgLpf2Poles<NV>>;

template <int NV>
using sb9_t = bypass::smoothed<20, sb9_t_<NV>>;

template <int NV>
using sb10_t_ = container::chain<parameter::empty, 
                                 wrap::fix<2, project::KorgHpf2Poles<NV>>, 
                                 project::KorgLpf2Poles<NV>, 
                                 project::KorgHpf2Poles<NV>, 
                                 project::KorgLpf2Poles<NV>>;

template <int NV>
using sb10_t = bypass::smoothed<20, sb10_t_<NV>>;

template <int NV>
using sb_container3_t = container::chain<parameter::empty, 
                                         wrap::fix<2, sb9_t<NV>>, 
                                         sb10_t<NV>>;

namespace softbypass_switch5_t_parameters
{
DECLARE_PARAMETER_RANGE_INV(BpSpread_0Range, 
                            0.5, 
                            0.9);

template <int NV>
using BpSpread_0 = parameter::from0To1_inv<Korg_ScriptFx_impl::pma_unscaled_t<NV>, 
                                           1, 
                                           BpSpread_0Range>;

DECLARE_PARAMETER_RANGE(BpSpread_1Range, 
                        1.1, 
                        1.5);

template <int NV>
using BpSpread_1 = parameter::from0To1<Korg_ScriptFx_impl::pma_unscaled1_t<NV>, 
                                       1, 
                                       BpSpread_1Range>;

template <int NV>
using BpSpread = parameter::chain<ranges::Identity, 
                                  BpSpread_0<NV>, 
                                  BpSpread_1<NV>>;

}

template <int NV>
using softbypass_switch5_t = container::chain<softbypass_switch5_t_parameters::BpSpread<NV>, 
                                              wrap::fix<2, switcher3_t>, 
                                              pma_unscaled_t<NV>, 
                                              pma_unscaled1_t<NV>, 
                                              sb_container3_t<NV>>;

template <int NV>
using sb3_t_ = container::chain<parameter::empty, 
                                wrap::fix<2, softbypass_switch5_t<NV>>>;

template <int NV>
using sb3_t = bypass::smoothed<20, sb3_t_<NV>>;
template <int NV>
using switcher_c2 = parameter::bypass<sb3_t<NV>>;

template <int NV>
using switcher_multimod = parameter::list<switcher_c0<NV>, 
                                          switcher_c1<NV>, 
                                          switcher_c2<NV>>;

template <int NV>
using switcher_t = control::xfader<switcher_multimod<NV>, faders::switcher>;

template <int NV>
using sb_container_t = container::chain<parameter::empty, 
                                        wrap::fix<2, sb1_t<NV>>, 
                                        sb2_t<NV>, 
                                        sb3_t<NV>>;

namespace softbypass_FilterType_t_parameters
{
// Parameter list for Korg_ScriptFx_impl::softbypass_FilterType_t ----------------------------------

DECLARE_PARAMETER_RANGE_STEP(Switch_InputRange, 
                             0., 
                             3., 
                             1.);

template <int NV>
using Switch = parameter::chain<Switch_InputRange, 
                                parameter::plain<Korg_ScriptFx_impl::switcher_t<NV>, 0>>;

using _2Poles4 = parameter::chain<ranges::Identity, 
                                  parameter::plain<Korg_ScriptFx_impl::switcher1_t, 0>, 
                                  parameter::plain<Korg_ScriptFx_impl::switcher2_t, 0>, 
                                  parameter::plain<Korg_ScriptFx_impl::switcher3_t, 0>>;

template <int NV>
using softbypass_FilterType_t_plist = parameter::list<Switch<NV>, _2Poles4>;
}

template <int NV>
using softbypass_FilterType_t = container::chain<softbypass_FilterType_t_parameters::softbypass_FilterType_t_plist<NV>, 
                                                 wrap::fix<2, switcher_t<NV>>, 
                                                 sb_container_t<NV>>;

namespace Korg_ScriptFx_t_parameters
{
// Parameter list for Korg_ScriptFx_impl::Korg_ScriptFx_t ------------------------------------------

DECLARE_PARAMETER_RANGE_SKEW(Cutoff_InputRange, 
                             20., 
                             20000., 
                             0.229905);

template <int NV>
using Cutoff = parameter::chain<Cutoff_InputRange, 
                                parameter::plain<Korg_ScriptFx_impl::minmaxCutoff_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(Q_InputRange, 
                             0.7, 
                             10., 
                             0.201849);

template <int NV>
using Q = parameter::chain<Q_InputRange, 
                           parameter::plain<Korg_ScriptFx_impl::minmaxQ_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_STEP(Type_InputRange, 
                             0., 
                             2., 
                             1.);
DECLARE_PARAMETER_RANGE_STEP(Type_0Range, 
                             0., 
                             3., 
                             1.);

template <int NV>
using Type_0 = parameter::from0To1<Korg_ScriptFx_impl::softbypass_FilterType_t<NV>, 
                                   0, 
                                   Type_0Range>;

template <int NV>
using Type = parameter::chain<Type_InputRange, Type_0<NV>>;

DECLARE_PARAMETER_RANGE(BpSpread_InputRange, 
                        0., 
                        100.);

template <int NV>
using BpSpread = parameter::chain<BpSpread_InputRange, 
                                  parameter::plain<Korg_ScriptFx_impl::softbypass_switch5_t<NV>, 0>>;

template <int NV>
using Poles = parameter::plain<Korg_ScriptFx_impl::softbypass_FilterType_t<NV>, 
                               1>;
template <int NV>
using Korg_ScriptFx_t_plist = parameter::list<Cutoff<NV>, 
                                              Q<NV>, 
                                              Type<NV>, 
                                              Poles<NV>, 
                                              BpSpread<NV>>;
}

template <int NV>
using Korg_ScriptFx_t_ = container::chain<Korg_ScriptFx_t_parameters::Korg_ScriptFx_t_plist<NV>, 
                                          wrap::fix<2, minmaxCutoff_t<NV>>, 
                                          minmaxQ_t<NV>, 
                                          softbypass_FilterType_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Korg_ScriptFx_impl::Korg_ScriptFx_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Korg_ScriptFx);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(78)
		{
			0x005B, 0x0000, 0x4300, 0x7475, 0x666F, 0x0066, 0x0000, 0x41A0, 
            0x4000, 0x469C, 0x0000, 0x447A, 0x6C1A, 0x3E6B, 0x0000, 0x0000, 
            0x015B, 0x0000, 0x5100, 0x3300, 0x3333, 0x003F, 0x2000, 0x0041, 
            0x8000, 0x873F, 0x4EB1, 0x003E, 0x0000, 0x5B00, 0x0002, 0x0000, 
            0x7954, 0x6570, 0x0000, 0x0000, 0x0000, 0x0000, 0x0040, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x0003, 0x0000, 0x6F50, 
            0x656C, 0x0073, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x045B, 0x0000, 0x4200, 0x5370, 
            0x7270, 0x6165, 0x0064, 0x0000, 0x0000, 0x0000, 0x42C8, 0x0000, 
            0x42C8, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& minmaxCutoff = this->getT(0);                                            // Korg_ScriptFx_impl::minmaxCutoff_t<NV>
		auto& minmaxQ = this->getT(1);                                                 // Korg_ScriptFx_impl::minmaxQ_t<NV>
		auto& softbypass_FilterType = this->getT(2);                                   // Korg_ScriptFx_impl::softbypass_FilterType_t<NV>
		auto& switcher = this->getT(2).getT(0);                                        // Korg_ScriptFx_impl::switcher_t<NV>
		auto& sb_container = this->getT(2).getT(1);                                    // Korg_ScriptFx_impl::sb_container_t<NV>
		auto& sb1 = this->getT(2).getT(1).getT(0);                                     // Korg_ScriptFx_impl::sb1_t<NV>
		auto& softbypass_switch3 = this->getT(2).getT(1).getT(0).getT(0);              // Korg_ScriptFx_impl::softbypass_switch3_t<NV>
		auto& switcher1 = this->getT(2).getT(1).getT(0).getT(0).getT(0);               // Korg_ScriptFx_impl::switcher1_t
		auto& sb_container1 = this->getT(2).getT(1).getT(0).getT(0).getT(1);           // Korg_ScriptFx_impl::sb_container1_t<NV>
		auto& sb5 = this->getT(2).getT(1).getT(0).getT(0).getT(1).getT(0);             // Korg_ScriptFx_impl::sb5_t<NV>
		auto& faust = this->getT(2).getT(1).getT(0).getT(0).getT(1).getT(0).getT(0);   // project::KorgLpf2Poles<NV>
		auto& sb6 = this->getT(2).getT(1).getT(0).getT(0).getT(1).getT(1);             // Korg_ScriptFx_impl::sb6_t<NV>
		auto& faust1 = this->getT(2).getT(1).getT(0).getT(0).getT(1).getT(1).getT(0);  // project::KorgLpf2Poles<NV>
		auto& faust6 = this->getT(2).getT(1).getT(0).getT(0).getT(1).getT(1).getT(1);  // project::KorgLpf2Poles<NV>
		auto& sb2 = this->getT(2).getT(1).getT(1);                                     // Korg_ScriptFx_impl::sb2_t<NV>
		auto& softbypass_switch4 = this->getT(2).getT(1).getT(1).getT(0);              // Korg_ScriptFx_impl::softbypass_switch4_t<NV>
		auto& switcher2 = this->getT(2).getT(1).getT(1).getT(0).getT(0);               // Korg_ScriptFx_impl::switcher2_t
		auto& sb_container2 = this->getT(2).getT(1).getT(1).getT(0).getT(1);           // Korg_ScriptFx_impl::sb_container2_t<NV>
		auto& sb7 = this->getT(2).getT(1).getT(1).getT(0).getT(1).getT(0);             // Korg_ScriptFx_impl::sb7_t<NV>
		auto& faust2 = this->getT(2).getT(1).getT(1).getT(0).getT(1).getT(0).getT(0);  // project::KorgHpf2Poles<NV>
		auto& sb8 = this->getT(2).getT(1).getT(1).getT(0).getT(1).getT(1);             // Korg_ScriptFx_impl::sb8_t<NV>
		auto& faust3 = this->getT(2).getT(1).getT(1).getT(0).getT(1).getT(1).getT(0);  // project::KorgHpf2Poles<NV>
		auto& faust7 = this->getT(2).getT(1).getT(1).getT(0).getT(1).getT(1).getT(1);  // project::KorgHpf2Poles<NV>
		auto& sb3 = this->getT(2).getT(1).getT(2);                                     // Korg_ScriptFx_impl::sb3_t<NV>
		auto& softbypass_switch5 = this->getT(2).getT(1).getT(2).getT(0);              // Korg_ScriptFx_impl::softbypass_switch5_t<NV>
		auto& switcher3 = this->getT(2).getT(1).getT(2).getT(0).getT(0);               // Korg_ScriptFx_impl::switcher3_t
		auto& pma_unscaled = this->getT(2).getT(1).getT(2).getT(0).getT(1);            // Korg_ScriptFx_impl::pma_unscaled_t<NV>
		auto& pma_unscaled1 = this->getT(2).getT(1).getT(2).getT(0).getT(2);           // Korg_ScriptFx_impl::pma_unscaled1_t<NV>
		auto& sb_container3 = this->getT(2).getT(1).getT(2).getT(0).getT(3);           // Korg_ScriptFx_impl::sb_container3_t<NV>
		auto& sb9 = this->getT(2).getT(1).getT(2).getT(0).getT(3).getT(0);             // Korg_ScriptFx_impl::sb9_t<NV>
		auto& faust4 = this->getT(2).getT(1).getT(2).getT(0).getT(3).getT(0).getT(0);  // project::KorgHpf2Poles<NV>
		auto& faust5 = this->getT(2).getT(1).getT(2).getT(0).getT(3).getT(0).getT(1);  // project::KorgLpf2Poles<NV>
		auto& sb10 = this->getT(2).getT(1).getT(2).getT(0).getT(3).getT(1);            // Korg_ScriptFx_impl::sb10_t<NV>
		auto& faust8 = this->getT(2).getT(1).getT(2).getT(0).getT(3).getT(1).getT(0);  // project::KorgHpf2Poles<NV>
		auto& faust9 = this->getT(2).getT(1).getT(2).getT(0).getT(3).getT(1).getT(1);  // project::KorgLpf2Poles<NV>
		auto& faust10 = this->getT(2).getT(1).getT(2).getT(0).getT(3).getT(1).getT(2); // project::KorgHpf2Poles<NV>
		auto& faust11 = this->getT(2).getT(1).getT(2).getT(0).getT(3).getT(1).getT(3); // project::KorgLpf2Poles<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		auto& BpSpread_p = softbypass_switch5.getParameterT(0);
		BpSpread_p.connectT(0, pma_unscaled);                         // BpSpread -> pma_unscaled::Multiply
		BpSpread_p.connectT(1, pma_unscaled1);                        // BpSpread -> pma_unscaled1::Multiply
		softbypass_FilterType.getParameterT(0).connectT(0, switcher); // Switch -> switcher::Value
		
		auto& _2Poles4_p = softbypass_FilterType.getParameterT(1);
		_2Poles4_p.connectT(0, switcher1);                // _2Poles4 -> switcher1::Value
		_2Poles4_p.connectT(1, switcher2);                // _2Poles4 -> switcher2::Value
		_2Poles4_p.connectT(2, switcher3);                // _2Poles4 -> switcher3::Value
		this->getParameterT(0).connectT(0, minmaxCutoff); // Cutoff -> minmaxCutoff::Value
		
		this->getParameterT(1).connectT(0, minmaxQ); // Q -> minmaxQ::Value
		
		this->getParameterT(2).connectT(0, softbypass_FilterType); // Type -> softbypass_FilterType::Switch
		
		this->getParameterT(3).connectT(0, softbypass_FilterType); // Poles -> softbypass_FilterType::_2Poles4
		
		this->getParameterT(4).connectT(0, softbypass_switch5); // BpSpread -> softbypass_switch5::BpSpread
		
		// Modulation Connections ------------------------------------------------------------------
		
		pma_unscaled.getWrappedObject().getParameter().connectT(0, faust4);        // pma_unscaled -> faust4::Cutofffrequency
		pma_unscaled.getWrappedObject().getParameter().connectT(1, faust8);        // pma_unscaled -> faust8::Cutofffrequency
		pma_unscaled.getWrappedObject().getParameter().connectT(2, faust10);       // pma_unscaled -> faust10::Cutofffrequency
		pma_unscaled1.getWrappedObject().getParameter().connectT(0, faust5);       // pma_unscaled1 -> faust5::Cutofffrequency
		pma_unscaled1.getWrappedObject().getParameter().connectT(1, faust9);       // pma_unscaled1 -> faust9::Cutofffrequency
		pma_unscaled1.getWrappedObject().getParameter().connectT(2, faust11);      // pma_unscaled1 -> faust11::Cutofffrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(0, faust);         // minmaxCutoff -> faust::Cutofffrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(1, faust1);        // minmaxCutoff -> faust1::Cutofffrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(2, faust6);        // minmaxCutoff -> faust6::Cutofffrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(3, faust2);        // minmaxCutoff -> faust2::Cutofffrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(4, faust3);        // minmaxCutoff -> faust3::Cutofffrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(5, faust7);        // minmaxCutoff -> faust7::Cutofffrequency
		minmaxCutoff.getWrappedObject().getParameter().connectT(6, pma_unscaled);  // minmaxCutoff -> pma_unscaled::Value
		minmaxCutoff.getWrappedObject().getParameter().connectT(7, pma_unscaled1); // minmaxCutoff -> pma_unscaled1::Value
		minmaxQ.getWrappedObject().getParameter().connectT(0, faust);              // minmaxQ -> faust::Q
		minmaxQ.getWrappedObject().getParameter().connectT(1, faust1);             // minmaxQ -> faust1::Q
		minmaxQ.getWrappedObject().getParameter().connectT(2, faust6);             // minmaxQ -> faust6::Q
		minmaxQ.getWrappedObject().getParameter().connectT(3, faust2);             // minmaxQ -> faust2::Q
		minmaxQ.getWrappedObject().getParameter().connectT(4, faust3);             // minmaxQ -> faust3::Q
		minmaxQ.getWrappedObject().getParameter().connectT(5, faust7);             // minmaxQ -> faust7::Q
		minmaxQ.getWrappedObject().getParameter().connectT(6, faust4);             // minmaxQ -> faust4::Q
		minmaxQ.getWrappedObject().getParameter().connectT(7, faust5);             // minmaxQ -> faust5::Q
		minmaxQ.getWrappedObject().getParameter().connectT(8, faust8);             // minmaxQ -> faust8::Q
		minmaxQ.getWrappedObject().getParameter().connectT(9, faust9);             // minmaxQ -> faust9::Q
		minmaxQ.getWrappedObject().getParameter().connectT(10, faust10);           // minmaxQ -> faust10::Q
		minmaxQ.getWrappedObject().getParameter().connectT(11, faust11);           // minmaxQ -> faust11::Q
		auto& switcher1_p = switcher1.getWrappedObject().getParameter();
		auto& switcher2_p = switcher2.getWrappedObject().getParameter();
		auto& switcher3_p = switcher3.getWrappedObject().getParameter();
		auto& switcher_p = switcher.getWrappedObject().getParameter();
		switcher_p.getParameterT(0).connectT(0, sb1); // switcher -> sb1::Bypassed
		switcher_p.getParameterT(0).connectT(1, sb1); // switcher -> sb1::Bypassed
		switcher_p.getParameterT(1).connectT(0, sb2); // switcher -> sb2::Bypassed
		switcher_p.getParameterT(2).connectT(0, sb3); // switcher -> sb3::Bypassed
		
		// Default Values --------------------------------------------------------------------------
		
		;                                        // minmaxCutoff::Value is automated
		minmaxCutoff.setParameterT(1, 20.);      // control::minmax::Minimum
		minmaxCutoff.setParameterT(2, 20000.);   // control::minmax::Maximum
		minmaxCutoff.setParameterT(3, 0.229905); // control::minmax::Skew
		minmaxCutoff.setParameterT(4, 0.);       // control::minmax::Step
		minmaxCutoff.setParameterT(5, 0.);       // control::minmax::Polarity
		
		;                              // minmaxQ::Value is automated
		minmaxQ.setParameterT(1, 0.5); // control::minmax::Minimum
		minmaxQ.setParameterT(2, 7.5); // control::minmax::Maximum
		minmaxQ.setParameterT(3, 1.);  // control::minmax::Skew
		minmaxQ.setParameterT(4, 0.);  // control::minmax::Step
		minmaxQ.setParameterT(5, 0.);  // control::minmax::Polarity
		
		; // softbypass_FilterType::Switch is automated
		; // softbypass_FilterType::_2Poles4 is automated
		
		; // switcher::Value is automated
		
		; // switcher1::Value is automated
		
		; // faust::Cutofffrequency is automated
		; // faust::Q is automated
		
		; // faust1::Cutofffrequency is automated
		; // faust1::Q is automated
		
		; // faust6::Cutofffrequency is automated
		; // faust6::Q is automated
		
		; // switcher2::Value is automated
		
		; // faust2::Cutofffrequency is automated
		; // faust2::Q is automated
		
		; // faust3::Cutofffrequency is automated
		; // faust3::Q is automated
		
		; // faust7::Cutofffrequency is automated
		; // faust7::Q is automated
		
		; // softbypass_switch5::BpSpread is automated
		
		; // switcher3::Value is automated
		
		;                                  // pma_unscaled::Value is automated
		;                                  // pma_unscaled::Multiply is automated
		pma_unscaled.setParameterT(2, 0.); // control::pma_unscaled::Add
		
		;                                   // pma_unscaled1::Value is automated
		;                                   // pma_unscaled1::Multiply is automated
		pma_unscaled1.setParameterT(2, 0.); // control::pma_unscaled::Add
		
		; // faust4::Cutofffrequency is automated
		; // faust4::Q is automated
		
		; // faust5::Cutofffrequency is automated
		; // faust5::Q is automated
		
		; // faust8::Cutofffrequency is automated
		; // faust8::Q is automated
		
		; // faust9::Cutofffrequency is automated
		; // faust9::Q is automated
		
		; // faust10::Cutofffrequency is automated
		; // faust10::Q is automated
		
		; // faust11::Cutofffrequency is automated
		; // faust11::Q is automated
		
		this->setParameterT(0, 1000.);
		this->setParameterT(1, 1.);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 0.);
		this->setParameterT(4, 100.);
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
using Korg_ScriptFx = wrap::node<Korg_ScriptFx_impl::instance<NV>>;
}


