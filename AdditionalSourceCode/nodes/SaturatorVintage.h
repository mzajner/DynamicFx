#pragma once

#include "RnboTubeTapeSaturation.h"
// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace SaturatorVintage_impl
{
// ==============================| Node & Parameter type declarations |==============================

template <int NV>
using smoothed_parameter_unscaled2_t = wrap::mod<parameter::plain<project::RnboTubeTapeSaturation<NV>, 0>, 
                                                 control::smoothed_parameter_unscaled<NV, smoothers::linear_ramp<NV>>>;

template <int NV>
using smoothed_parameter_unscaled1_t = wrap::mod<parameter::plain<project::RnboTubeTapeSaturation<NV>, 2>, 
                                                 control::smoothed_parameter_unscaled<NV, smoothers::linear_ramp<NV>>>;

template <int NV>
using smoothed_parameter_unscaled_t = wrap::mod<parameter::plain<project::RnboTubeTapeSaturation<NV>, 3>, 
                                                control::smoothed_parameter_unscaled<NV, smoothers::linear_ramp<NV>>>;

namespace SaturatorVintage_t_parameters
{
// Parameter list for SaturatorVintage_impl::SaturatorVintage_t ------------------------------------

template <int NV>
using KnbDryWet = parameter::plain<SaturatorVintage_impl::smoothed_parameter_unscaled2_t<NV>, 
                                   0>;
template <int NV>
using KnbDrive = parameter::plain<SaturatorVintage_impl::smoothed_parameter_unscaled1_t<NV>, 
                                  0>;
template <int NV>
using KnbBlend = parameter::plain<SaturatorVintage_impl::smoothed_parameter_unscaled_t<NV>, 
                                  0>;
template <int NV>
using KnbTone = parameter::plain<filters::svf_eq<NV>, 0>;
template <int NV>
using SaturatorVintage_t_plist = parameter::list<KnbDryWet<NV>, 
                                                 KnbDrive<NV>, 
                                                 KnbBlend<NV>, 
                                                 KnbTone<NV>>;
}

template <int NV>
using SaturatorVintage_t_ = container::chain<SaturatorVintage_t_parameters::SaturatorVintage_t_plist<NV>, 
                                             wrap::fix<2, filters::svf_eq<NV>>, 
                                             smoothed_parameter_unscaled2_t<NV>, 
                                             smoothed_parameter_unscaled1_t<NV>, 
                                             smoothed_parameter_unscaled_t<NV>, 
                                             project::RnboTubeTapeSaturation<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public SaturatorVintage_impl::SaturatorVintage_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(SaturatorVintage);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(70)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0xC800, 0x0042, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x4462, 0x6972, 0x6576, 
            0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0002, 0x0000, 0x6E4B, 0x4262, 0x656C, 
            0x646E, 0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 
            0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x6E4B, 0x5462, 
            0x6E6F, 0x0065, 0x0000, 0x4348, 0x4000, 0x459C, 0x0000, 0x447A, 
            0x1192, 0x3EC6, 0x0000, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& svf_eq = this->getT(0);                       // filters::svf_eq<NV>
		auto& smoothed_parameter_unscaled2 = this->getT(1); // SaturatorVintage_impl::smoothed_parameter_unscaled2_t<NV>
		auto& smoothed_parameter_unscaled1 = this->getT(2); // SaturatorVintage_impl::smoothed_parameter_unscaled1_t<NV>
		auto& smoothed_parameter_unscaled = this->getT(3);  // SaturatorVintage_impl::smoothed_parameter_unscaled_t<NV>
		auto& RnboTubeTapeSaturation = this->getT(4);       // project::RnboTubeTapeSaturation<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, smoothed_parameter_unscaled2); // KnbDryWet -> smoothed_parameter_unscaled2::Value
		
		this->getParameterT(1).connectT(0, smoothed_parameter_unscaled1); // KnbDrive -> smoothed_parameter_unscaled1::Value
		
		this->getParameterT(2).connectT(0, smoothed_parameter_unscaled); // KnbBlend -> smoothed_parameter_unscaled::Value
		
		this->getParameterT(3).connectT(0, svf_eq); // KnbTone -> svf_eq::Frequency
		
		// Modulation Connections ------------------------------------------------------------------
		
		smoothed_parameter_unscaled2.getParameter().connectT(0, RnboTubeTapeSaturation); // smoothed_parameter_unscaled2 -> RnboTubeTapeSaturation::KnbDryWet
		smoothed_parameter_unscaled1.getParameter().connectT(0, RnboTubeTapeSaturation); // smoothed_parameter_unscaled1 -> RnboTubeTapeSaturation::KnbDrive
		smoothed_parameter_unscaled.getParameter().connectT(0, RnboTubeTapeSaturation);  // smoothed_parameter_unscaled -> RnboTubeTapeSaturation::KnbBlend
		
		// Default Values --------------------------------------------------------------------------
		
		;                              // svf_eq::Frequency is automated
		svf_eq.setParameterT(1, 1.);   // filters::svf_eq::Q
		svf_eq.setParameterT(2, 6.);   // filters::svf_eq::Gain
		svf_eq.setParameterT(3, 0.01); // filters::svf_eq::Smoothing
		svf_eq.setParameterT(4, 4.);   // filters::svf_eq::Mode
		svf_eq.setParameterT(5, 1.);   // filters::svf_eq::Enabled
		
		;                                                    // smoothed_parameter_unscaled2::Value is automated
		smoothed_parameter_unscaled2.setParameterT(1, 100.); // control::smoothed_parameter_unscaled::SmoothingTime
		smoothed_parameter_unscaled2.setParameterT(2, 1.);   // control::smoothed_parameter_unscaled::Enabled
		
		;                                                    // smoothed_parameter_unscaled1::Value is automated
		smoothed_parameter_unscaled1.setParameterT(1, 100.); // control::smoothed_parameter_unscaled::SmoothingTime
		smoothed_parameter_unscaled1.setParameterT(2, 1.);   // control::smoothed_parameter_unscaled::Enabled
		
		;                                                   // smoothed_parameter_unscaled::Value is automated
		smoothed_parameter_unscaled.setParameterT(1, 100.); // control::smoothed_parameter_unscaled::SmoothingTime
		smoothed_parameter_unscaled.setParameterT(2, 1.);   // control::smoothed_parameter_unscaled::Enabled
		
		;                                            // RnboTubeTapeSaturation::KnbDryWet is automated
		RnboTubeTapeSaturation.setParameterT(1, 0.); // project::RnboTubeTapeSaturation::KnbInput
		;                                            // RnboTubeTapeSaturation::KnbDrive is automated
		;                                            // RnboTubeTapeSaturation::KnbBlend is automated
		RnboTubeTapeSaturation.setParameterT(4, 0.); // project::RnboTubeTapeSaturation::KnbOutput
		
		this->setParameterT(0, 100.);
		this->setParameterT(1, 50.);
		this->setParameterT(2, 50.);
		this->setParameterT(3, 1000.);
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
using SaturatorVintage = wrap::node<SaturatorVintage_impl::instance<NV>>;
}


