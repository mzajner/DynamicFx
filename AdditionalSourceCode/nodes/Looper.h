#pragma once

#include "RnboLooper2.h"
// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace Looper_impl
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
using tempo_sync_t = wrap::mod<parameter::plain<project::RnboLooper2<NV>, 1>, 
                               control::tempo_sync<NV>>;

template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<project::RnboLooper2<NV>, 0>>;

template <int NV>
using minmax1_t = control::minmax<NV, 
                                  parameter::plain<project::RnboLooper2<NV>, 5>>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<2, core::gain<NV>>, 
                                  tempo_sync_t<NV>, 
                                  minmax_t<NV>, 
                                  minmax1_t<NV>, 
                                  project::RnboLooper2<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, chain_t<NV>>, 
                                 chain1_t<NV>>;

namespace Looper_t_parameters
{
// Parameter list for Looper_impl::Looper_t --------------------------------------------------------

DECLARE_PARAMETER_RANGE(KnbDryWet_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<Looper_impl::xfader_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_STEP(KnbRecordLengthFree_InputRange, 
                             0., 
                             10000., 
                             1.);
DECLARE_PARAMETER_RANGE_STEP(KnbRecordLengthFree_0Range, 
                             0., 
                             10000., 
                             0.1);

template <int NV>
using KnbRecordLengthFree_0 = parameter::from0To1<Looper_impl::tempo_sync_t<NV>, 
                                                  3, 
                                                  KnbRecordLengthFree_0Range>;

template <int NV>
using KnbRecordLengthFree = parameter::chain<KnbRecordLengthFree_InputRange, 
                                             KnbRecordLengthFree_0<NV>>;

template <int NV>
using KnbRecordLengthSync = parameter::plain<Looper_impl::tempo_sync_t<NV>, 
                                             0>;
template <int NV>
using KnbTranspose = parameter::plain<project::RnboLooper2<NV>, 
                                      3>;
template <int NV>
using KnbMultiplier = parameter::plain<Looper_impl::tempo_sync_t<NV>, 
                                       1>;
template <int NV>
using BtnTempoSync = parameter::plain<Looper_impl::tempo_sync_t<NV>, 
                                      2>;
template <int NV>
using BtnRecord = parameter::plain<Looper_impl::minmax1_t<NV>, 
                                   0>;
template <int NV>
using BtnAuto = parameter::plain<Looper_impl::minmax_t<NV>, 
                                 0>;
template <int NV>
using BtnReverse = parameter::plain<project::RnboLooper2<NV>, 
                                    4>;
template <int NV>
using Looper_t_plist = parameter::list<KnbDryWet<NV>, 
                                       KnbRecordLengthFree<NV>, 
                                       KnbRecordLengthSync<NV>, 
                                       KnbTranspose<NV>, 
                                       KnbMultiplier<NV>, 
                                       BtnTempoSync<NV>, 
                                       BtnRecord<NV>, 
                                       BtnAuto<NV>, 
                                       BtnReverse<NV>>;
}

template <int NV>
using Looper_t_ = container::chain<Looper_t_parameters::Looper_t_plist<NV>, 
                                   wrap::fix<2, xfader_t<NV>>, 
                                   split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public Looper_impl::Looper_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Looper);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(174)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x5262, 0x6365, 0x726F, 
            0x4C64, 0x6E65, 0x7467, 0x4668, 0x6572, 0x0065, 0x0000, 0x0000, 
            0x4000, 0x461C, 0x0000, 0x44FA, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x025B, 0x0000, 0x4B00, 0x626E, 0x6552, 0x6F63, 0x6472, 0x654C, 
            0x676E, 0x6874, 0x7953, 0x636E, 0x0000, 0x0000, 0x0000, 0x9000, 
            0x0041, 0x1000, 0x0041, 0x8000, 0x003F, 0x8000, 0x5B3F, 0x0003, 
            0x0000, 0x6E4B, 0x5462, 0x6172, 0x736E, 0x6F70, 0x6573, 0x0000, 
            0xC000, 0x00C1, 0xC000, 0x0041, 0x0000, 0x0000, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0004, 0x0000, 0x6E4B, 0x4D62, 0x6C75, 0x6974, 
            0x6C70, 0x6569, 0x0072, 0x0000, 0x3F80, 0x0000, 0x4080, 0x0000, 
            0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x055B, 0x0000, 0x4200, 
            0x6E74, 0x6554, 0x706D, 0x536F, 0x6E79, 0x0063, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x065B, 0x0000, 0x4200, 0x6E74, 0x6552, 0x6F63, 0x6472, 0x0000, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x0000, 0x8000, 0x003F, 
            0x8000, 0x5B3F, 0x0007, 0x0000, 0x7442, 0x416E, 0x7475, 0x006F, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x3F80, 0x085B, 0x0000, 0x4200, 0x6E74, 0x6552, 0x6576, 
            0x7372, 0x0065, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                      // Looper_impl::xfader_t<NV>
		auto& split = this->getT(1);                       // Looper_impl::split_t<NV>
		auto& chain = this->getT(1).getT(0);               // Looper_impl::chain_t<NV>
		auto& gain1 = this->getT(1).getT(0).getT(0);       // core::gain<NV>
		auto& chain1 = this->getT(1).getT(1);              // Looper_impl::chain1_t<NV>
		auto& gain = this->getT(1).getT(1).getT(0);        // core::gain<NV>
		auto& tempo_sync = this->getT(1).getT(1).getT(1);  // Looper_impl::tempo_sync_t<NV>
		auto& minmax = this->getT(1).getT(1).getT(2);      // Looper_impl::minmax_t<NV>
		auto& minmax1 = this->getT(1).getT(1).getT(3);     // Looper_impl::minmax1_t<NV>
		auto& RnboLooper2 = this->getT(1).getT(1).getT(4); // project::RnboLooper2<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		this->getParameterT(1).connectT(0, tempo_sync); // KnbRecordLengthFree -> tempo_sync::UnsyncedTime
		
		this->getParameterT(2).connectT(0, tempo_sync); // KnbRecordLengthSync -> tempo_sync::Tempo
		
		this->getParameterT(3).connectT(0, RnboLooper2); // KnbTranspose -> RnboLooper2::KnbTranspose
		
		this->getParameterT(4).connectT(0, tempo_sync); // KnbMultiplier -> tempo_sync::Multiplier
		
		this->getParameterT(5).connectT(0, tempo_sync); // BtnTempoSync -> tempo_sync::Enabled
		
		this->getParameterT(6).connectT(0, minmax1); // BtnRecord -> minmax1::Value
		
		this->getParameterT(7).connectT(0, minmax); // BtnAuto -> minmax::Value
		
		this->getParameterT(8).connectT(0, RnboLooper2); // BtnReverse -> RnboLooper2::BtnReverse
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain1);                       // xfader -> gain1::Gain
		xfader_p.getParameterT(1).connectT(0, gain);                        // xfader -> gain::Gain
		tempo_sync.getParameter().connectT(0, RnboLooper2);                 // tempo_sync -> RnboLooper2::KnbRecordLength
		minmax.getWrappedObject().getParameter().connectT(0, RnboLooper2);  // minmax -> RnboLooper2::BtnAutoRecord
		minmax1.getWrappedObject().getParameter().connectT(0, RnboLooper2); // minmax1 -> RnboLooper2::KnbMode
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // tempo_sync::Tempo is automated
		; // tempo_sync::Multiplier is automated
		; // tempo_sync::Enabled is automated
		; // tempo_sync::UnsyncedTime is automated
		
		;                            // minmax::Value is automated
		minmax.setParameterT(1, 0.); // control::minmax::Minimum
		minmax.setParameterT(2, 1.); // control::minmax::Maximum
		minmax.setParameterT(3, 1.); // control::minmax::Skew
		minmax.setParameterT(4, 1.); // control::minmax::Step
		minmax.setParameterT(5, 1.); // control::minmax::Polarity
		
		;                             // minmax1::Value is automated
		minmax1.setParameterT(1, 0.); // control::minmax::Minimum
		minmax1.setParameterT(2, 1.); // control::minmax::Maximum
		minmax1.setParameterT(3, 1.); // control::minmax::Skew
		minmax1.setParameterT(4, 1.); // control::minmax::Step
		minmax1.setParameterT(5, 0.); // control::minmax::Polarity
		
		;                                 // RnboLooper2::BtnAutoRecord is automated
		;                                 // RnboLooper2::KnbRecordLength is automated
		RnboLooper2.setParameterT(2, 0.); // project::RnboLooper2::KnbVolume
		;                                 // RnboLooper2::KnbTranspose is automated
		;                                 // RnboLooper2::BtnReverse is automated
		;                                 // RnboLooper2::KnbMode is automated
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 2000.);
		this->setParameterT(2, 9.);
		this->setParameterT(3, 0.);
		this->setParameterT(4, 1.);
		this->setParameterT(5, 0.);
		this->setParameterT(6, 0.);
		this->setParameterT(7, 0.);
		this->setParameterT(8, 0.);
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
using Looper = wrap::node<Looper_impl::instance<NV>>;
}


