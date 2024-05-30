//Modulator Script

//=====MODULE TREE======
const var GlobalModulatorContainer1 = Synth.getChildSynth("Global Modulator Container1");
const var LFOModulator1 = Synth.getModulator("LFO Modulator1");
const var LFOModulator2 = Synth.getModulator("LFO Modulator2");
const var LFOModulator3 = Synth.getModulator("LFO Modulator3");
const var Velocity = Synth.getModulator("Velocity");

//=====USER INTERFACE=====
//LFO Panel
const var LfoEditButton = Content.getComponent("LfoEditButton");
const var LfoCloseButton = Content.getComponent("LfoCloseButton");
const var ModMatrixPanel = Content.getComponent("ModMatrixPanel");

//Panels
const var LfoEditPanel = Content.getComponent("LfoEditPanel");
const var LfoPanels = [Content.getComponent("LfoPanel1"),
                       Content.getComponent("LfoPanel2"),
                       Content.getComponent("LfoPanel3")];
//Knobs
const var LfoTimeFreeKnob1 = Content.getComponent("LfoTimeFreeKnob1");
const var LfoTimeFreeKnob2 = Content.getComponent("LfoTimeFreeKnob2");
const var LfoTimeFreeKnob3 = Content.getComponent("LfoTimeFreeKnob3");
const var LfoTimeSyncKnob1 = Content.getComponent("LfoTimeSyncKnob1");
const var LfoTimeSyncKnob2 = Content.getComponent("LfoTimeSyncKnob2");
const var LfoTimeSyncKnob3 = Content.getComponent("LfoTimeSyncKnob3");
const var LfoIntensityKnob1 = Content.getComponent("LfoIntensityKnob1");
const var LfoIntensityKnob2 = Content.getComponent("LfoIntensityKnob2");
const var LfoIntensityKnob3 = Content.getComponent("LfoIntensityKnob3");
const var LfoPhaseKnob1 = Content.getComponent("LfoPhaseKnob1");
const var LfoPhaseKnob2 = Content.getComponent("LfoPhaseKnob2");
const var LfoPhaseKnob3 = Content.getComponent("LfoPhaseKnob3");
const var LfoNumSteps1 = Content.getComponent("LfoNumStepsKnob1");
const var LfoNumSteps2 = Content.getComponent("LfoNumStepsKnob2");
const var LfoNumSteps3 = Content.getComponent("LfoNumStepsKnob3");

//Buttons
const var LfoSyncButton1 = Content.getComponent("LfoSyncButton1");
const var LfoSyncButton2 = Content.getComponent("LfoSyncButton2");
const var LfoSyncButton3 = Content.getComponent("LfoSyncButton3");

//Waveforms
const var LfoVisualizer1 = Content.getComponent("LfoVisualizer1");
const var LfoVisualizer2 = Content.getComponent("LfoVisualizer2");
const var LfoVisualizer3 = Content.getComponent("LfoVisualizer3");

//Comboboxes
const var LfoWaveformCombobox1 = Content.getComponent("LfoWaveformCombobox1");
const var LfoWaveformCombobox2 = Content.getComponent("LfoWaveformCombobox2");
const var LfoWaveformCombobox3 = Content.getComponent("LfoWaveformCombobox3");

//Tables
const var LfoTable1 = Content.getComponent("LfoTable1");
const var LfoTable2 = Content.getComponent("LfoTable2");
const var LfoTable3 = Content.getComponent("LfoTable3");

//SliderPacks
const var LfoSliderPack1 = Content.getComponent("LfoSliderPack1");
const var LfoSliderPack2 = Content.getComponent("LfoSliderPack2");
const var LfoSliderPack3 = Content.getComponent("LfoSliderPack3");


//======LFO CONTROL CALLBACK=====
//-----LFO Tempo Sync-----
//LFO 1 Tempo Sync
inline function onLfoSyncButton1Control(component, value)
{
	if (value == 1) {
		LfoTimeFreeKnob1.showControl(false);
		LfoTimeSyncKnob1.showControl(true); 
	} else {
		LfoTimeFreeKnob1.showControl(true);
		LfoTimeSyncKnob1.showControl(false); 
	}
	LFOModulator1.setAttribute(LFOModulator1.TempoSync, value);
};

Content.getComponent("LfoSyncButton1").setControlCallback(onLfoSyncButton1Control);

//LFO 2 Tempo Sync
inline function onLfoSyncButton2Control(component, value)
{
	if (value == 1) {
		LfoTimeFreeKnob2.showControl(false);
		LfoTimeSyncKnob2.showControl(true); 
	} else {
		LfoTimeFreeKnob2.showControl(true);
		LfoTimeSyncKnob2.showControl(false); 
	}
	LFOModulator2.setAttribute(LFOModulator2.TempoSync, value);
};

Content.getComponent("LfoSyncButton2").setControlCallback(onLfoSyncButton2Control);

//LFO 3 Tempo Sync
inline function onLfoSyncButton3Control(component, value)
{
	if (value == 1) {
		LfoTimeFreeKnob3.showControl(false);
		LfoTimeSyncKnob3.showControl(true); 
	} else {
		LfoTimeFreeKnob3.showControl(true);
		LfoTimeSyncKnob3.showControl(false); 
	}
	LFOModulator3.setAttribute(LFOModulator3.TempoSync, value);
};

Content.getComponent("LfoSyncButton3").setControlCallback(onLfoSyncButton3Control);

//Lfo Button/Panel Control
inline function onLfoButtonControl(component, value)
{
    if(value)  // Only act on button press, not release
    {
        for( i = 0; i < LfoButtons.length; i++)
        {
            // Show the panel associated with the pressed button
            LfoPanels[i].set("visible", LfoButtons[i] == component);
        }
    }
}

for( i = 0; i < LfoButtons.length; i++)
{
    LfoButtons[i].setControlCallback(onLfoButtonControl);
}


for( i = 0; i < LfoPanels.length; i++)
{
    LfoPanels[i].set("visible", i == 0);  // Only the first panel visible initially
}


//Combobox Visualizer, table control

inline function onLfoWaveformCombobox1Control(component, value)
{
	LFOModulator1.setAttribute(LFOModulator1.WaveFormType, value);
	LfoTable1.set("visible", value == 6);  
	LfoSliderPack1.set("visible", value == 7); 
	LfoNumSteps1.set("visible", value == 7); 
	LfoPhaseKnob1.set("visible", value != 7); 
}
LfoWaveformCombobox1.setControlCallback(onLfoWaveformCombobox1Control);

inline function onLfoWaveformCombobox2Control(component, value)
{
	LFOModulator2.setAttribute(LFOModulator2.WaveFormType, value);
	LfoTable2.set("visible", value == 6);  
	LfoSliderPack2.set("visible", value == 7); 
	LfoNumSteps2.set("visible", value == 7); 
	LfoPhaseKnob2.set("visible", value != 7); 
}
LfoWaveformCombobox2.setControlCallback(onLfoWaveformCombobox2Control);

inline function onLfoWaveformCombobox3Control(component, value)
{
	LFOModulator3.setAttribute(LFOModulator3.WaveFormType, value);
	LfoTable3.set("visible", value == 6); 
	LfoSliderPack3.set("visible", value == 7); 
	LfoNumSteps3.set("visible", value == 7); 
	LfoPhaseKnob3.set("visible", value != 7);  
}
LfoWaveformCombobox3.setControlCallback(onLfoWaveformCombobox3Control);
