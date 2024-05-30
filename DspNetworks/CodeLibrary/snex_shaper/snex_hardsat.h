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
