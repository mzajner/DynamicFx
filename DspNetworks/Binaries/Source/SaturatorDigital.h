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

namespace SaturatorDigital_impl
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
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<2, core::gain<NV>>>;

template <int NV> using xfader1_c0 = xfader_c0<NV>;

template <int NV> using xfader1_c1 = xfader_c0<NV>;

template <int NV>
using xfader1_multimod = parameter::list<xfader1_c0<NV>, xfader1_c1<NV>>;

template <int NV>
using xfader1_t = control::xfader<xfader1_multimod<NV>, faders::rms>;

template <int NV>
using minmax_mod = parameter::chain<ranges::Identity, 
                                    parameter::plain<project::SaturatorWavefolding<NV>, 1>, 
                                    parameter::plain<project::SaturatorWavefolding<NV>, 1>>;

template <int NV>
using minmax_t = control::minmax<NV, minmax_mod<NV>>;

template <int NV>
using multi_t = container::multi<parameter::empty, 
                                 wrap::fix<1, project::SaturatorWavefolding<NV>>, 
                                 wrap::fix<1, project::SaturatorWavefolding<NV>>>;

template <int NV>
using oversample8x_t_ = container::chain<parameter::empty, 
                                         wrap::fix<2, multi_t<NV>>>;

template <int NV>
using oversample8x_t = wrap::oversample<8, oversample8x_t_<NV>>;

template <int NV>
using chain5_t = container::chain<parameter::empty, 
                                  wrap::fix<2, core::gain<NV>>, 
                                  minmax_t<NV>, 
                                  oversample8x_t<NV>, 
                                  core::gain<NV>>;

template <int NV>
using oversample8x1_t_ = container::chain<parameter::empty, 
                                          wrap::fix<2, project::QuadraticDistortion<NV>>>;

template <int NV>
using oversample8x1_t = wrap::oversample<8, oversample8x1_t_<NV>>;

template <int NV>
using chain4_t = container::chain<parameter::empty, 
                                  wrap::fix<2, core::gain<NV>>, 
                                  oversample8x1_t<NV>, 
                                  core::gain<NV>>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<2, chain5_t<NV>>, 
                                  chain4_t<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, filters::svf_eq<NV>>, 
                                 core::gain<NV>, 
                                 xfader1_t<NV>, 
                                 split1_t<NV>, 
                                 core::gain<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, chain1_t<NV>>, 
                                 chain_t<NV>>;

namespace SaturatorDigital_t_parameters
{
// Parameter list for SaturatorDigital_impl::SaturatorDigital_t ------------------------------------

DECLARE_PARAMETER_RANGE(KnbDryWet_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbDryWet = parameter::chain<KnbDryWet_InputRange, 
                                   parameter::plain<SaturatorDigital_impl::xfader_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE(KnbDrive_InputRange, 
                        0., 
                        100.);
DECLARE_PARAMETER_RANGE_SKEW_INV(KnbDrive_3Range, 
                                 -12., 
                                 0., 
                                 0.5);

template <int NV>
using KnbDrive_3 = parameter::from0To1_inv<core::gain<NV>, 
                                           0, 
                                           KnbDrive_3Range>;

template <int NV>
using KnbDrive = parameter::chain<KnbDrive_InputRange, 
                                  parameter::plain<project::QuadraticDistortion<NV>, 1>, 
                                  parameter::plain<project::SaturatorWavefolding<NV>, 0>, 
                                  parameter::plain<project::SaturatorWavefolding<NV>, 0>, 
                                  KnbDrive_3<NV>>;

DECLARE_PARAMETER_RANGE(KnbBlend_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbBlend = parameter::chain<KnbBlend_InputRange, 
                                  parameter::plain<SaturatorDigital_impl::xfader1_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE(KnbHarmonics_InputRange, 
                        0., 
                        100.);
DECLARE_PARAMETER_RANGE_STEP(KnbHarmonics_0Range, 
                             20., 
                             200., 
                             1.);

template <int NV>
using KnbHarmonics_0 = parameter::from0To1<project::QuadraticDistortion<NV>, 
                                           0, 
                                           KnbHarmonics_0Range>;

DECLARE_PARAMETER_RANGE_SKEW(KnbHarmonics_1Range, 
                             -3, 
                             0., 
                             5.42227);

template <int NV>
using KnbHarmonics_1 = parameter::from0To1<core::gain<NV>, 
                                           0, 
                                           KnbHarmonics_1Range>;

template <int NV>
using KnbHarmonics = parameter::chain<KnbHarmonics_InputRange, 
                                      KnbHarmonics_0<NV>, 
                                      KnbHarmonics_1<NV>, 
                                      parameter::plain<SaturatorDigital_impl::minmax_t<NV>, 0>>;

DECLARE_PARAMETER_RANGE_SKEW(KnbTone_InputRange, 
                             20., 
                             20000., 
                             0.229905);
DECLARE_PARAMETER_RANGE_SKEW(KnbTone_0Range, 
                             20., 
                             20000., 
                             0.229905);

template <int NV>
using KnbTone_0 = parameter::from0To1<filters::svf_eq<NV>, 
                                      0, 
                                      KnbTone_0Range>;

template <int NV>
using KnbTone = parameter::chain<KnbTone_InputRange, KnbTone_0<NV>>;

template <int NV>
using SaturatorDigital_t_plist = parameter::list<KnbDryWet<NV>, 
                                                 KnbDrive<NV>, 
                                                 KnbBlend<NV>, 
                                                 KnbHarmonics<NV>, 
                                                 KnbTone<NV>>;
}

template <int NV>
using SaturatorDigital_t_ = container::chain<SaturatorDigital_t_parameters::SaturatorDigital_t_plist<NV>, 
                                             wrap::fix<2, xfader_t<NV>>, 
                                             split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public SaturatorDigital_impl::SaturatorDigital_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(SaturatorDigital);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(88)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x4462, 0x6972, 0x6576, 
            0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0002, 0x0000, 0x6E4B, 0x4262, 0x656C, 
            0x646E, 0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x6E4B, 0x4862, 
            0x7261, 0x6F6D, 0x696E, 0x7363, 0x0000, 0x0000, 0x0000, 0xC800, 
            0x0042, 0x0000, 0x0000, 0x8000, 0x003F, 0x0000, 0x5B00, 0x0004, 
            0x0000, 0x6E4B, 0x5462, 0x6E6F, 0x0065, 0x0000, 0x41A0, 0x4000, 
            0x469C, 0x4000, 0x4499, 0x6C1A, 0x3E6B, 0x0000, 0x3F80, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                                                 // SaturatorDigital_impl::xfader_t<NV>
		auto& split = this->getT(1);                                                  // SaturatorDigital_impl::split_t<NV>
		auto& chain1 = this->getT(1).getT(0);                                         // SaturatorDigital_impl::chain1_t<NV>
		auto& gain = this->getT(1).getT(0).getT(0);                                   // core::gain<NV>
		auto& chain = this->getT(1).getT(1);                                          // SaturatorDigital_impl::chain_t<NV>
		auto& svf_eq = this->getT(1).getT(1).getT(0);                                 // filters::svf_eq<NV>
		auto& gain1 = this->getT(1).getT(1).getT(1);                                  // core::gain<NV>
		auto& xfader1 = this->getT(1).getT(1).getT(2);                                // SaturatorDigital_impl::xfader1_t<NV>
		auto& split1 = this->getT(1).getT(1).getT(3);                                 // SaturatorDigital_impl::split1_t<NV>
		auto& chain5 = this->getT(1).getT(1).getT(3).getT(0);                         // SaturatorDigital_impl::chain5_t<NV>
		auto& gain6 = this->getT(1).getT(1).getT(3).getT(0).getT(0);                  // core::gain<NV>
		auto& minmax = this->getT(1).getT(1).getT(3).getT(0).getT(1);                 // SaturatorDigital_impl::minmax_t<NV>
		auto& oversample8x = this->getT(1).getT(1).getT(3).getT(0).getT(2);           // SaturatorDigital_impl::oversample8x_t<NV>
		auto& multi = this->getT(1).getT(1).getT(3).getT(0).getT(2).getT(0);          // SaturatorDigital_impl::multi_t<NV>
		auto& faust1 = this->getT(1).getT(1).getT(3).getT(0).getT(2).getT(0).getT(0); // project::SaturatorWavefolding<NV>
		auto& faust2 = this->getT(1).getT(1).getT(3).getT(0).getT(2).getT(0).getT(1); // project::SaturatorWavefolding<NV>
		auto& gain3 = this->getT(1).getT(1).getT(3).getT(0).getT(3);                  // core::gain<NV>
		auto& chain4 = this->getT(1).getT(1).getT(3).getT(1);                         // SaturatorDigital_impl::chain4_t<NV>
		auto& gain5 = this->getT(1).getT(1).getT(3).getT(1).getT(0);                  // core::gain<NV>
		auto& oversample8x1 = this->getT(1).getT(1).getT(3).getT(1).getT(1);          // SaturatorDigital_impl::oversample8x1_t<NV>
		auto& faust = this->getT(1).getT(1).getT(3).getT(1).getT(1).getT(0);          // project::QuadraticDistortion<NV>
		auto& gain4 = this->getT(1).getT(1).getT(3).getT(1).getT(2);                  // core::gain<NV>
		auto& gain2 = this->getT(1).getT(1).getT(4);                                  // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // KnbDryWet -> xfader::Value
		
		auto& KnbDrive_p = this->getParameterT(1);
		KnbDrive_p.connectT(0, faust);  // KnbDrive -> faust::Drive
		KnbDrive_p.connectT(1, faust1); // KnbDrive -> faust1::Drive
		KnbDrive_p.connectT(2, faust2); // KnbDrive -> faust2::Drive
		KnbDrive_p.connectT(3, gain2);  // KnbDrive -> gain2::Gain
		
		this->getParameterT(2).connectT(0, xfader1); // KnbBlend -> xfader1::Value
		
		auto& KnbHarmonics_p = this->getParameterT(3);
		KnbHarmonics_p.connectT(0, faust);  // KnbHarmonics -> faust::BreakFrequency
		KnbHarmonics_p.connectT(1, gain4);  // KnbHarmonics -> gain4::Gain
		KnbHarmonics_p.connectT(2, minmax); // KnbHarmonics -> minmax::Value
		
		this->getParameterT(4).connectT(0, svf_eq); // KnbTone -> svf_eq::Frequency
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain);  // xfader -> gain::Gain
		xfader_p.getParameterT(1).connectT(0, gain1); // xfader -> gain1::Gain
		auto& xfader1_p = xfader1.getWrappedObject().getParameter();
		xfader1_p.getParameterT(0).connectT(0, gain6);                // xfader1 -> gain6::Gain
		xfader1_p.getParameterT(1).connectT(0, gain5);                // xfader1 -> gain5::Gain
		minmax.getWrappedObject().getParameter().connectT(0, faust1); // minmax -> faust1::Width
		minmax.getWrappedObject().getParameter().connectT(1, faust2); // minmax -> faust2::Width
		
		// Default Values --------------------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                  // svf_eq::Frequency is automated
		svf_eq.setParameterT(1, 0.536713); // filters::svf_eq::Q
		svf_eq.setParameterT(2, 6.);       // filters::svf_eq::Gain
		svf_eq.setParameterT(3, 0.01);     // filters::svf_eq::Smoothing
		svf_eq.setParameterT(4, 4.);       // filters::svf_eq::Mode
		svf_eq.setParameterT(5, 1.);       // filters::svf_eq::Enabled
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // xfader1::Value is automated
		
		;                            // gain6::Gain is automated
		gain6.setParameterT(1, 20.); // core::gain::Smoothing
		gain6.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                              // minmax::Value is automated
		minmax.setParameterT(1, 0.01); // control::minmax::Minimum
		minmax.setParameterT(2, 0.99); // control::minmax::Maximum
		minmax.setParameterT(3, 1.);   // control::minmax::Skew
		minmax.setParameterT(4, 0.);   // control::minmax::Step
		minmax.setParameterT(5, 0.);   // control::minmax::Polarity
		
		; // faust1::Drive is automated
		; // faust1::Width is automated
		
		; // faust2::Drive is automated
		; // faust2::Width is automated
		
		gain3.setParameterT(0, -9);  // core::gain::Gain
		gain3.setParameterT(1, 20.); // core::gain::Smoothing
		gain3.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain5::Gain is automated
		gain5.setParameterT(1, 20.); // core::gain::Smoothing
		gain5.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // faust::BreakFrequency is automated
		; // faust::Drive is automated
		
		;                            // gain4::Gain is automated
		gain4.setParameterT(1, 20.); // core::gain::Smoothing
		gain4.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain2::Gain is automated
		gain2.setParameterT(1, 20.); // core::gain::Smoothing
		gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 50.);
		this->setParameterT(2, 0.);
		this->setParameterT(3, 0.);
		this->setParameterT(4, 1226.);
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
using SaturatorDigital = wrap::node<SaturatorDigital_impl::instance<NV>>;
}


