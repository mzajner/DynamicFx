/* ------------------------------------------------------------
author: "Bram de Jong (from musicdsp.org)"
name: "fuzz -- a simple distortion effect"
version: "1.0"
Code generated with Faust 2.70.3 (https://faust.grame.fr)
Compilation options: -lang cpp -rui -nvi -ct 1 -cn _FuzzTone -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  ___FuzzTone_H__
#define  ___FuzzTone_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>

#ifndef FAUSTCLASS 
#define FAUSTCLASS _FuzzTone
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float _FuzzTone_faustpower2_f(float value) {
	return value * value;
}

class _FuzzTone final : public ::faust::dsp {
	
 public:
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	
 public:
	_FuzzTone() {}

	void metadata(Meta* m) { 
		m->declare("author", "Bram de Jong (from musicdsp.org)");
		m->declare("compile_options", "-lang cpp -rui -nvi -ct 1 -cn _FuzzTone -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0");
		m->declare("filename", "FuzzTone.dsp");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "fuzz -- a simple distortion effect");
		m->declare("version", "1.0");
	}

	static constexpr int getStaticNumInputs() {
		return 2;
	}
	static constexpr int getStaticNumOutputs() {
		return 2;
	}
	int getNumInputs() {
		return 2;
	}
	int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
	}
	
	void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(3.0f);
		fHslider1 = FAUSTFLOAT(12.0f);
	}
	
	void instanceClear() {
	}
	
	void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	_FuzzTone* clone() {
		return new _FuzzTone();
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("dist");
		ui_interface->addHorizontalSlider("distortion", &fHslider1, FAUSTFLOAT(12.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("gain", &fHslider0, FAUSTFLOAT(3.0f), FAUSTFLOAT(-96.0f), FAUSTFLOAT(96.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = std::max<float>(0.0f, std::min<float>(1e+02f, float(fHslider1)));
		float fSlow1 = std::pow(1e+01f, 0.05f * std::max<float>(-96.0f, std::min<float>(96.0f, float(fHslider0)))) / std::sqrt(fSlow0 + 1.0f);
		float fSlow2 = std::pow(1e+01f, 0.05f * fSlow0);
		float fSlow3 = fSlow2 + -1.0f;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]);
			float fTemp1 = std::fabs(fTemp0);
			output0[i0] = FAUSTFLOAT(fSlow1 * (fTemp0 * (fSlow2 + fTemp1) / (_FuzzTone_faustpower2_f(fTemp0) + fSlow3 * fTemp1 + 1.0f)));
			float fTemp2 = float(input1[i0]);
			float fTemp3 = std::fabs(fTemp2);
			output1[i0] = FAUSTFLOAT(fSlow1 * (fTemp2 * (fSlow2 + fTemp3) / (_FuzzTone_faustpower2_f(fTemp2) + fSlow3 * fTemp3 + 1.0f)));
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "FuzzTone.dsp"
	#define FAUST_CLASS_NAME "_FuzzTone"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -rui -nvi -ct 1 -cn _FuzzTone -scn ::faust::dsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -uim -single -ftz 0"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 2
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("dist/distortion", fHslider1, 12.0f, 0.0f, 1e+02f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("dist/gain", fHslider0, 3.0f, -96.0f, 96.0f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, distortion, "dist/distortion", fHslider1, 12.0f, 0.0f, 1e+02f, 0.1f) \
		p(HORIZONTALSLIDER, gain, "dist/gain", fHslider0, 3.0f, -96.0f, 96.0f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#endif
