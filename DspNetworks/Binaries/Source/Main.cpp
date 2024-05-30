/** Autogenerated Main.cpp. */

// =================================| Include only the DSP files  |=================================

#include <AppConfig.h>
#include <hi_dsp_library/hi_dsp_library.h>
#include <hi_faust/hi_faust.h>
#include "includes.h"
// ===========================| Now we can add the rest of the codebase |===========================

#include <JuceHeader.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"

// =======================================| Project Factory |=======================================

namespace project
{

struct Factory: public scriptnode::dll::StaticLibraryHostFactory
{
	Factory()
	{
		TempoSyncer::initTempoData();
		// Node registrations ----------------------------------------------------------------------
		
		registerPolyNode<project::TransientShaper<1>, project::TransientShaper<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::SoftClip<1>, project::SoftClip<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::SaturatorWavefolding<1>, project::SaturatorWavefolding<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::SallenKeyLpf<1>, project::SallenKeyLpf<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::SallenKeyHpf<1>, project::SallenKeyHpf<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::SallenKeyBpf<1>, project::SallenKeyBpf<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::RnboTubeTapeSaturation<1>, project::RnboTubeTapeSaturation<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::RnboReverseDelay<1>, project::RnboReverseDelay<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::RnboLooper2<1>, project::RnboLooper2<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::QuadraticDistortion<1>, project::QuadraticDistortion<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::Phaser<1>, project::Phaser<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::OberheimLpf4Poles<1>, project::OberheimLpf4Poles<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::OberheimLpf2Poles<1>, project::OberheimLpf2Poles<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::OberheimHpf4Poles<1>, project::OberheimHpf4Poles<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::OberheimHpf2Poles<1>, project::OberheimHpf2Poles<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::OberheimBpf4Poles<1>, project::OberheimBpf4Poles<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::OberheimBpf2Poles<1>, project::OberheimBpf2Poles<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::mp3Reverb<1>, project::mp3Reverb<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::mp3Compressor<1>, project::mp3Compressor<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::MoogLpf2Poles<1>, project::MoogLpf2Poles<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::MicroShifter<1>, project::MicroShifter<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::KorgLpf2Poles<1>, project::KorgLpf2Poles<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::KorgHpf2Poles<1>, project::KorgHpf2Poles<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::GritAmp<1>, project::GritAmp<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::granulator<1>, project::granulator<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::FuzzTone<1>, project::FuzzTone<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::FlangerFeedback<1>, project::FlangerFeedback<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::EchoplexDelay<1>, project::EchoplexDelay<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::echoForBrowser<1>, project::echoForBrowser<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::AllPassLoopReverb<1>, project::AllPassLoopReverb<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::AutoPanner<1>, wrap::illegal_poly<project::AutoPanner<1>>>();
		registerPolyNode<project::Compressor<1>, wrap::illegal_poly<project::Compressor<1>>>();
		registerPolyNode<project::Detuner<1>, wrap::illegal_poly<project::Detuner<1>>>();
		registerPolyNode<project::Flanger<1>, wrap::illegal_poly<project::Flanger<1>>>();
		registerPolyNode<project::GlistenReverb<1>, wrap::illegal_poly<project::GlistenReverb<1>>>();
		registerPolyNode<project::Grains<1>, wrap::illegal_poly<project::Grains<1>>>();
		registerPolyNode<project::HazeDistortion<1>, wrap::illegal_poly<project::HazeDistortion<1>>>();
		registerPolyNode<project::InfiniteReverb<1>, wrap::illegal_poly<project::InfiniteReverb<1>>>();
		registerPolyNode<project::Korg_ScriptFx<1>, wrap::illegal_poly<project::Korg_ScriptFx<1>>>();
		registerPolyNode<project::Looper<1>, wrap::illegal_poly<project::Looper<1>>>();
		registerPolyNode<project::Moog_ScriptFx<1>, wrap::illegal_poly<project::Moog_ScriptFx<1>>>();
		registerPolyNode<project::Oberheim_ScriptFx<1>, wrap::illegal_poly<project::Oberheim_ScriptFx<1>>>();
		registerPolyNode<project::ReverseDelay<1>, wrap::illegal_poly<project::ReverseDelay<1>>>();
		registerPolyNode<project::SallenKey_ScriptFx<1>, wrap::illegal_poly<project::SallenKey_ScriptFx<1>>>();
		registerPolyNode<project::SaturatorDigital<1>, wrap::illegal_poly<project::SaturatorDigital<1>>>();
		registerPolyNode<project::SaturatorModern<1>, wrap::illegal_poly<project::SaturatorModern<1>>>();
		registerPolyNode<project::SaturatorVintage<1>, wrap::illegal_poly<project::SaturatorVintage<1>>>();
		registerPolyNode<project::ShredDistortion<1>, wrap::illegal_poly<project::ShredDistortion<1>>>();
		registerPolyNode<project::SlapbackDelay<1>, wrap::illegal_poly<project::SlapbackDelay<1>>>();
		registerPolyNode<project::TwistDelay<1>, wrap::illegal_poly<project::TwistDelay<1>>>();
		registerPolyNode<project::Widener<1>, wrap::illegal_poly<project::Widener<1>>>();
	}
};
}

project::Factory f;

// ====================================| Exported DLL functions |====================================

DLL_EXPORT int getNumNodes()
{
	return f.getNumNodes();
}

DLL_EXPORT size_t getNodeId(int index, char* t)
{
	return HelperFunctions::writeString(t, f.getId(index).getCharPointer());
}

DLL_EXPORT bool isThirdPartyNode(int index)
{
	return index < 30;
}

DLL_EXPORT int getNumDataObjects(int nodeIndex, int dataTypeAsInt)
{
	return f.getNumDataObjects(nodeIndex, dataTypeAsInt);
}

DLL_EXPORT void deInitOpaqueNode(scriptnode::OpaqueNode* n)
{
	n->callDestructor();
}

DLL_EXPORT void initOpaqueNode(scriptnode::OpaqueNode* n, int index, bool polyIfPossible)
{
	f.initOpaqueNode(n, index, polyIfPossible);
}
DLL_EXPORT int getHash(int index)
{
	static const int thirdPartyOffset = 30;
	static const int hashIndexes[21] =
	{
		-1094459401,
		-789337875,
		-70322838,
		-1953245196,
		-2047610723,
		-170891172,
		-1310194645,
		2063744351,
		-1003779723,
		-2086181983,
		-1949552390,
		-1387729830,
		-159213425,
		-953085547,
		131560352,
		871921948,
		-358488535,
		1966763881,
		-2118896870,
		2027186362,
		-1404337227
	};
	return (index >= thirdPartyOffset) ? hashIndexes[index - thirdPartyOffset] : 0;
}
DLL_EXPORT int getWrapperType(int index)
{
	return f.getWrapperType(index);
}
DLL_EXPORT ErrorC getError()
{
	return f.getError();
}
DLL_EXPORT void clearError()
{
	f.clearError();
}
DLL_EXPORT int getDllVersionCounter()
{
	return scriptnode::dll::ProjectDll::DllUpdateCounter;
}

#pragma clang diagnostic pop


