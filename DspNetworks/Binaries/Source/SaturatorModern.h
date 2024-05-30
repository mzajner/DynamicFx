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

namespace SaturatorModern_impl
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
using Dry_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>>;

template <int NV> using xfader1_c0 = xfader_c0<NV>;

template <int NV> using xfader1_c1 = xfader_c0<NV>;

template <int NV>
using xfader1_multimod = parameter::list<xfader1_c0<NV>, xfader1_c1<NV>>;

template <int NV>
using xfader1_t = control::xfader<xfader1_multimod<NV>, faders::rms>;

template <int NumVoices> struct snex_softsat
{
	SNEX_NODE(snex_softsat);
	// Implement the Waveshaper here...
	float gain = 0.0f;
	float out = 0.0f;
	float saturate(float input)
	{
		if(input < gain)
		{
			out = input;
		}
		else if(input > gain)
		{
			out = gain + (input-gain) / 				(1.0f+Math.pow(((input-gain)/(1.0f-gain)), 2.0f));
		}
		else if(input > 1.0f)
		{
			out = (gain + 1.0f) / 2.0f;
		}
		return out;
	}
	float getSample(float input)
	{
		if(input>0.0f)
		{
			saturate(input);
		}
		else
		{
			input = input * -1.0f;
			saturate(input);
			out = out * -1.0f;
		}
		return out;
	}
	// These functions are the glue code that call the function above
	template <typename T> void process(T& data)
	{
		for(auto ch: data)
		{
			for(auto& s: data.toChannelData(ch))
			{
				s = getSample(s);
			}
		}
	}
	template <typename T> void processFrame(T& data)
	{
		for(auto& s: data)
			s = getSample(s);
	}
	void reset()
	{
	}
	void prepare(PrepareSpecs ps)
	{
	}
	void setExternalData(const ExternalData& d, int index)
	{
	}
	template <int P> void setParameter(double v)
	{
		if(P==0)
		{
			gain = (float)v;
		}
	}
};

template <int NV>
using snex_shaper3_t = wrap::no_data<core::snex_shaper<snex_softsat<NV>>>;
template <int NV>
using smoothed_parameter_unscaled3_t = wrap::mod<parameter::plain<snex_shaper3_t<NV>, 0>, 
                                                 control::smoothed_parameter_unscaled<NV, smoothers::linear_ramp<NV>>>;
template <int NV>
using minmax1_t = control::minmax<NV, 
                                  parameter::plain<smoothed_parameter_unscaled3_t<NV>, 0>>;

template <int NV>
using oversample16x1_t_ = container::chain<parameter::empty, 
                                           wrap::fix<2, minmax1_t<NV>>, 
                                           smoothed_parameter_unscaled3_t<NV>, 
                                           snex_shaper3_t<NV>>;

template <int NV>
using oversample16x1_t = wrap::oversample<16, oversample16x1_t_<NV>>;

template <int NV>
using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, core::gain<NV>>, 
                                 oversample16x1_t<NV>>;

template <int NumVoices> struct snex_hardsat
{
	SNEX_NODE(snex_hardsat);
	static const int NUM_CHANNELS = 2;
	span<sfloat, NUM_CHANNELS> k;
	// Implement the Waveshaper here...
	float thresh = 0.0f;
	float bias = 0.0f;
	float out = 0.0f;
	float getSample(float input)
	{
		input += bias;
		if(input > thresh)
		{
			out = thresh;
		}
		else if(input < thresh*-1.0f)
		{
			out = thresh * -1.0f;
		}
		else
		{
			out = input;
		}
		return out;
	}
	// These functions are the glue code that call the function above
	template <typename T> void process(T& data)
	{
		for(auto ch: data)
		{
			for(auto& s: data.toChannelData(ch))
			{
				s = getSample(s);
			}
		}
	}
	template <typename T> void processFrame(T& data)
	{
		for(auto& s: data)
			s = getSample(s);
	}
	void reset()
	{
	}
	void prepare(PrepareSpecs ps)
	{
	}
	void setExternalData(const ExternalData& d, int index)
	{
	}
	template <int P> void setParameter(double v)
	{
		if(P==0)
		{
			thresh = (float)v;
		}
		else if (P == 1)
		{
			bias = (float)v;  // Set bias
		}
	}
};

template <int NV>
using snex_shaper1_t = wrap::no_data<core::snex_shaper<snex_hardsat<NV>>>;
DECLARE_PARAMETER_RANGE_SKEW_INV(smoothed_parameter_unscaled_modRange, 
                                 0.1, 
                                 1., 
                                 0.985565);

template <int NV>
using smoothed_parameter_unscaled_mod = parameter::from0To1_inv<snex_shaper1_t<NV>, 
                                                                0, 
                                                                smoothed_parameter_unscaled_modRange>;

template <int NV>
using smoothed_parameter_unscaled_t = wrap::mod<smoothed_parameter_unscaled_mod<NV>, 
                                                control::smoothed_parameter_unscaled<NV, smoothers::linear_ramp<NV>>>;
template <int NV>
using minmax_t = control::minmax<NV, 
                                 parameter::plain<smoothed_parameter_unscaled_t<NV>, 0>>;

template <int NV>
using oversample16x_t_ = container::chain<parameter::empty, 
                                          wrap::fix<2, minmax_t<NV>>, 
                                          smoothed_parameter_unscaled_t<NV>, 
                                          snex_shaper1_t<NV>, 
                                          core::gain<NV>>;

template <int NV>
using oversample16x_t = wrap::oversample<16, oversample16x_t_<NV>>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<2, core::gain<NV>>, 
                                  oversample16x_t<NV>>;

template <int NV>
using split1_t = container::split<parameter::empty, 
                                  wrap::fix<2, chain_t<NV>>, 
                                  chain1_t<NV>>;
using oscilloscope_t = wrap::no_data<wrap::no_process<analyse::oscilloscope>>;

template <int NV>
using Wet_t = container::chain<parameter::empty, 
                               wrap::fix<2, core::gain<NV>>, 
                               filters::svf_eq<NV>, 
                               xfader1_t<NV>, 
                               split1_t<NV>, 
                               oscilloscope_t>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, Dry_t<NV>>, 
                                 Wet_t<NV>>;

namespace SaturatorModern_t_parameters
{
// Parameter list for SaturatorModern_impl::SaturatorModern_t --------------------------------------

DECLARE_PARAMETER_RANGE(KnbDrive_InputRange, 
                        0., 
                        100.);
DECLARE_PARAMETER_RANGE_SKEW(KnbDrive_0Range, 
                             0., 
                             1., 
                             3.);

template <int NV>
using KnbDrive_0 = parameter::from0To1<SaturatorModern_impl::minmax_t<NV>, 
                                       0, 
                                       KnbDrive_0Range>;

template <int NV>
using KnbDrive_1 = parameter::from0To1<SaturatorModern_impl::minmax1_t<NV>, 
                                       0, 
                                       KnbDrive_0Range>;

DECLARE_PARAMETER_RANGE_SKEW(KnbDrive_2Range, 
                             0., 
                             3., 
                             0.339741);

template <int NV>
using KnbDrive_2 = parameter::from0To1<core::gain<NV>, 
                                       0, 
                                       KnbDrive_2Range>;

template <int NV>
using KnbDrive = parameter::chain<KnbDrive_InputRange, 
                                  KnbDrive_0<NV>, 
                                  KnbDrive_1<NV>, 
                                  KnbDrive_2<NV>>;

DECLARE_PARAMETER_RANGE(KnbBlend_InputRange, 
                        0., 
                        100.);

template <int NV>
using KnbBlend = parameter::chain<KnbBlend_InputRange, 
                                  parameter::plain<SaturatorModern_impl::xfader1_t<NV>, 0>>;

using KnbDryWet = parameter::empty;
template <int NV>
using KnbTone = parameter::plain<filters::svf_eq<NV>, 0>;
template <int NV>
using SaturatorModern_t_plist = parameter::list<KnbDryWet, 
                                                KnbDrive<NV>, 
                                                KnbBlend<NV>, 
                                                KnbTone<NV>>;
}

template <int NV>
using SaturatorModern_t_ = container::chain<SaturatorModern_t_parameters::SaturatorModern_t_plist<NV>, 
                                            wrap::fix<2, xfader_t<NV>>, 
                                            split_t<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public SaturatorModern_impl::SaturatorModern_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(SaturatorModern);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(70)
		{
			0x005B, 0x0000, 0x4B00, 0x626E, 0x7244, 0x5779, 0x7465, 0x0000, 
            0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 0x003F, 
            0x0000, 0x5B00, 0x0001, 0x0000, 0x6E4B, 0x4462, 0x6972, 0x6576, 
            0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0002, 0x0000, 0x6E4B, 0x4262, 0x656C, 
            0x646E, 0x0000, 0x0000, 0x0000, 0xC800, 0x0042, 0x4800, 0x0042, 
            0x8000, 0x003F, 0x0000, 0x5B00, 0x0003, 0x0000, 0x6E4B, 0x5462, 
            0x6E6F, 0x0065, 0x0000, 0x42C8, 0x4000, 0x461C, 0x0000, 0x447A, 
            0x004E, 0x3E94, 0x0000, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& xfader = this->getT(0);                                                               // SaturatorModern_impl::xfader_t<NV>
		auto& split = this->getT(1);                                                                // SaturatorModern_impl::split_t<NV>
		auto& Dry = this->getT(1).getT(0);                                                          // SaturatorModern_impl::Dry_t<NV>
		auto& gain2 = this->getT(1).getT(0).getT(0);                                                // core::gain<NV>
		auto& Wet = this->getT(1).getT(1);                                                          // SaturatorModern_impl::Wet_t<NV>
		auto& gain1 = this->getT(1).getT(1).getT(0);                                                // core::gain<NV>
		auto& svf_eq = this->getT(1).getT(1).getT(1);                                               // filters::svf_eq<NV>
		auto& xfader1 = this->getT(1).getT(1).getT(2);                                              // SaturatorModern_impl::xfader1_t<NV>
		auto& split1 = this->getT(1).getT(1).getT(3);                                               // SaturatorModern_impl::split1_t<NV>
		auto& chain = this->getT(1).getT(1).getT(3).getT(0);                                        // SaturatorModern_impl::chain_t<NV>
		auto& gain3 = this->getT(1).getT(1).getT(3).getT(0).getT(0);                                // core::gain<NV>
		auto& oversample16x1 = this->getT(1).getT(1).getT(3).getT(0).getT(1);                       // SaturatorModern_impl::oversample16x1_t<NV>
		auto& minmax1 = this->getT(1).getT(1).getT(3).getT(0).getT(1).getT(0);                      // SaturatorModern_impl::minmax1_t<NV>
		auto& smoothed_parameter_unscaled3 = this->getT(1).getT(1).getT(3).getT(0).getT(1).getT(1); // SaturatorModern_impl::smoothed_parameter_unscaled3_t<NV>
		auto& snex_shaper3 = this->getT(1).getT(1).getT(3).getT(0).getT(1).getT(2);                 // SaturatorModern_impl::snex_shaper3_t<NV>
		auto& chain1 = this->getT(1).getT(1).getT(3).getT(1);                                       // SaturatorModern_impl::chain1_t<NV>
		auto& gain4 = this->getT(1).getT(1).getT(3).getT(1).getT(0);                                // core::gain<NV>
		auto& oversample16x = this->getT(1).getT(1).getT(3).getT(1).getT(1);                        // SaturatorModern_impl::oversample16x_t<NV>
		auto& minmax = this->getT(1).getT(1).getT(3).getT(1).getT(1).getT(0);                       // SaturatorModern_impl::minmax_t<NV>
		auto& smoothed_parameter_unscaled = this->getT(1).getT(1).getT(3).getT(1).getT(1).getT(1);  // SaturatorModern_impl::smoothed_parameter_unscaled_t<NV>
		auto& snex_shaper1 = this->getT(1).getT(1).getT(3).getT(1).getT(1).getT(2);                 // SaturatorModern_impl::snex_shaper1_t<NV>
		auto& gain = this->getT(1).getT(1).getT(3).getT(1).getT(1).getT(3);                         // core::gain<NV>
		auto& oscilloscope = this->getT(1).getT(1).getT(4);                                         // SaturatorModern_impl::oscilloscope_t
		
		// Parameter Connections -------------------------------------------------------------------
		
		auto& KnbDrive_p = this->getParameterT(1);
		KnbDrive_p.connectT(0, minmax);  // KnbDrive -> minmax::Value
		KnbDrive_p.connectT(1, minmax1); // KnbDrive -> minmax1::Value
		KnbDrive_p.connectT(2, gain);    // KnbDrive -> gain::Gain
		
		this->getParameterT(2).connectT(0, xfader1); // KnbBlend -> xfader1::Value
		
		this->getParameterT(3).connectT(0, svf_eq); // KnbTone -> svf_eq::Frequency
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain2); // xfader -> gain2::Gain
		xfader_p.getParameterT(1).connectT(0, gain1); // xfader -> gain1::Gain
		auto& xfader1_p = xfader1.getWrappedObject().getParameter();
		xfader1_p.getParameterT(0).connectT(0, gain3);                                       // xfader1 -> gain3::Gain
		xfader1_p.getParameterT(1).connectT(0, gain4);                                       // xfader1 -> gain4::Gain
		smoothed_parameter_unscaled3.getParameter().connectT(0, snex_shaper3);               // smoothed_parameter_unscaled3 -> snex_shaper3::Drive
		minmax1.getWrappedObject().getParameter().connectT(0, smoothed_parameter_unscaled3); // minmax1 -> smoothed_parameter_unscaled3::Value
		smoothed_parameter_unscaled.getParameter().connectT(0, snex_shaper1);                // smoothed_parameter_unscaled -> snex_shaper1::Thresh
		minmax.getWrappedObject().getParameter().connectT(0, smoothed_parameter_unscaled);   // minmax -> smoothed_parameter_unscaled::Value
		
		// Default Values --------------------------------------------------------------------------
		
		xfader.setParameterT(0, 1.); // control::xfader::Value
		
		;                            // gain2::Gain is automated
		gain2.setParameterT(1, 20.); // core::gain::Smoothing
		gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                              // svf_eq::Frequency is automated
		svf_eq.setParameterT(1, 0.7);  // filters::svf_eq::Q
		svf_eq.setParameterT(2, 6.);   // filters::svf_eq::Gain
		svf_eq.setParameterT(3, 0.01); // filters::svf_eq::Smoothing
		svf_eq.setParameterT(4, 4.);   // filters::svf_eq::Mode
		svf_eq.setParameterT(5, 1.);   // filters::svf_eq::Enabled
		
		; // xfader1::Value is automated
		
		;                            // gain3::Gain is automated
		gain3.setParameterT(1, 20.); // core::gain::Smoothing
		gain3.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                             // minmax1::Value is automated
		minmax1.setParameterT(1, 0.); // control::minmax::Minimum
		minmax1.setParameterT(2, 1.); // control::minmax::Maximum
		minmax1.setParameterT(3, 1.); // control::minmax::Skew
		minmax1.setParameterT(4, 0.); // control::minmax::Step
		minmax1.setParameterT(5, 1.); // control::minmax::Polarity
		
		;                                                    // smoothed_parameter_unscaled3::Value is automated
		smoothed_parameter_unscaled3.setParameterT(1, 100.); // control::smoothed_parameter_unscaled::SmoothingTime
		smoothed_parameter_unscaled3.setParameterT(2, 1.);   // control::smoothed_parameter_unscaled::Enabled
		
		; // snex_shaper3::Drive is automated
		
		;                            // gain4::Gain is automated
		gain4.setParameterT(1, 20.); // core::gain::Smoothing
		gain4.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                             // minmax::Value is automated
		minmax.setParameterT(1, 0.1); // control::minmax::Minimum
		minmax.setParameterT(2, 1.);  // control::minmax::Maximum
		minmax.setParameterT(3, 1.);  // control::minmax::Skew
		minmax.setParameterT(4, 0.);  // control::minmax::Step
		minmax.setParameterT(5, 1.);  // control::minmax::Polarity
		
		;                                                   // smoothed_parameter_unscaled::Value is automated
		smoothed_parameter_unscaled.setParameterT(1, 350.); // control::smoothed_parameter_unscaled::SmoothingTime
		smoothed_parameter_unscaled.setParameterT(2, 1.);   // control::smoothed_parameter_unscaled::Enabled
		
		; // snex_shaper1::Thresh is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 50.);
		this->setParameterT(1, 50.);
		this->setParameterT(2, 50.);
		this->setParameterT(3, 1000.);
		this->setExternalData({}, -1);
	}
	~instance() override
	{
		// Cleanup external data references --------------------------------------------------------
		
		this->setExternalData({}, -1);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(1).getT(1).getT(3).getT(0).getT(1).getT(2).setExternalData(b, index); // SaturatorModern_impl::snex_shaper3_t<NV>
		this->getT(1).getT(1).getT(3).getT(1).getT(1).getT(2).setExternalData(b, index); // SaturatorModern_impl::snex_shaper1_t<NV>
		this->getT(1).getT(1).getT(4).setExternalData(b, index);                         // SaturatorModern_impl::oscilloscope_t
	}
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
using SaturatorModern = wrap::node<SaturatorModern_impl::instance<NV>>;
}


