//======FX DRY/WET CONTROL CALLBACK=====

// Function to update component visibility based on ComboBox selection
inline function onFxComboboxDryWetControl(component, value)
{
    // Hide all controls initially
    KnbSamplerDryWet0.set("visible", false);
    KnbSamplerDryWet1.set("visible", false);
    KnbSamplerDryWet2.set("visible", false);
    KnbSamplerDryWet3.set("visible", false);
    KnbMasterDryWet1.set("visible", false);
    KnbMasterDryWet2.set("visible", false);
    KnbMasterDryWet3.set("visible", false);

    // Check the selected item index and show corresponding controls
    switch(value)
    {
        case 1: // Master
            KnbSamplerDryWet0.set("visible", true);
            KnbMasterDryWet.set("visible", true);
            break;
        case 2: // Layer A
            KnbSamplerDryWet1.set("visible", true);
            KnbMasterDryWet1.set("visible", true);
            break;
        case 3: // Layer B
            KnbSamplerDryWet2.set("visible", true);
            KnbMasterDryWet2.set("visible", true);
            break;
        case 4: // Layer C
            KnbSamplerDryWet3.set("visible", true);
            KnbMasterDryWet3.set("visible", true);
            break;
    }
}
// Set the control callback to the ComboBox
FxComboboxDryWet.setControlCallback(onFxComboboxDryWetControl);

// Initially call the function to set the correct visibility state based on the default ComboBox selection
//onFxComboboxDryWet(FxComboboxDryWet, FxComboboxDryWet.getValue());


//Dry/Wet Sampler Knob Handling
const var FxDryWetKnobs1 = [Content.getComponent("KnbParam1"), Content.getComponent("KnbParam9")];
const var FxDryWetKnobs2 = [Content.getComponent("KnbParam17"), Content.getComponent("KnbParam25")];
const var FxDryWetKnobs3 = [Content.getComponent("KnbParam33"), Content.getComponent("KnbParam41")];

// Function to update the specified knobs to reflect the value of the dry/wet control
function updateFxKnobs(knobsArray, value) {
    for (i = 0; i < knobsArray.length; i++) {
        knobsArray[i].setValue(value);
    }
}

// Control callback for the Sampler A Dry/Wets
inline function onSamplerDryWet1Control(component, value) {
    updateFxKnobs(FxDryWetKnobs1, value);
    FxSlot1.setAttribute(0, value);
    FxSlot2.setAttribute(0, value);
}

KnbSamplerDryWet1.setControlCallback(onSamplerDryWet1Control);

// Control callback for the Sampler B Dry/Wets
inline function onSamplerDryWet2Control(component, value) {
    updateFxKnobs(FxDryWetKnobs2, value);
    FxSlot3.setAttribute(0, value);
    FxSlot4.setAttribute(0, value);
}

KnbSamplerDryWet2.setControlCallback(onSamplerDryWet2Control);

// Control callback for the Sampler B Dry/Wets
inline function onSamplerDryWet3Control(component, value) {
    updateFxKnobs(FxDryWetKnobs3, value);
    FxSlot5.setAttribute(0, value);
    FxSlot6.setAttribute(0, value);
}

KnbSamplerDryWet3.setControlCallback(onSamplerDryWet3Control);



// Initialize arrays for SendEffects and PostGains
const SendEffects = [
    Synth.getEffect("Send Effect1"),
    Synth.getEffect("Send Effect2"),
    Synth.getEffect("Send Effect3")
];

const PostGains = [
    Synth.getEffect("PostGain1"),
    Synth.getEffect("PostGain2"),
    Synth.getEffect("PostGain3")
];

// Initialize controls for Dry/Wet knobs
const DryWetKnobs = [
    Content.getComponent("KnbMasterDryWet1"),
    Content.getComponent("KnbMasterDryWet2"),
    Content.getComponent("KnbMasterDryWet3")
];

// Universal Dry/Wet control callback
inline function onMasterDryWetControl(component, value) {
    local index = DryWetKnobs.indexOf(component);
    if (index == -1) return; 

    local normalizedValue = value / 100.0;
    local wetGainDB = Engine.getDecibelsForGainFactor(normalizedValue);
    local dryGainDB = Engine.getDecibelsForGainFactor(1 - normalizedValue);

    if (SendEffects[index] && PostGains[index]) {
        SendEffects[index].setAttribute(SendEffects[index].Gain, wetGainDB);
        PostGains[index].setAttribute(PostGains[index].Gain, dryGainDB);
    }
}

// Attach the control callback to each knob
for (var i = 0; i < DryWetKnobs.length; i++) {
    DryWetKnobs[i].setControlCallback(onMasterDryWetControl);
}


// Master Dry/Wet control callback
inline function onMasterDryWetGlobalControl(component, value) {
    for (i = 0; i < DryWetKnobs.length; i++) {
        DryWetKnobs[i].setValue(value); 
    }

    // Directly update SendEffects and PostGains
    local normalizedValue = value / 100.0;
    local wetGainDB = Engine.getDecibelsForGainFactor(normalizedValue);
    local dryGainDB = Engine.getDecibelsForGainFactor(1 - normalizedValue);

    for (i = 0; i < SendEffects.length; i++) {
        SendEffects[i].setAttribute(SendEffects[i].Gain, wetGainDB);
        PostGains[i].setAttribute(PostGains[i].Gain, dryGainDB);
    }
}
KnbMasterDryWet.setControlCallback(onMasterDryWetGlobalControl);

// Optional: Synchronize the initial state of all controls based on the master knob's value
onMasterDryWetGlobalControl(KnbMasterDryWet, KnbMasterDryWet.getValue());







/*
// Control callback for the Sampler A Master Dry/Wets
inline function onKnbMasterDryWet1Control(component, value)
{
    local normalizedValue = value / 100.0;
    local wetGainDB = Engine.getDecibelsForGainFactor(normalizedValue);
    local dryGainDB = Engine.getDecibelsForGainFactor(1 - normalizedValue);

    SendEffect1.setAttribute(SendEffect1.Gain, wetGainDB);
    PostGain1.setAttribute(PostGain1.Gain, dryGainDB);
};
Content.getComponent("KnbMasterDryWet1").setControlCallback(onKnbMasterDryWet1Control);

// Control callback for the Sampler B Master Dry/Wets
inline function onKnbMasterDryWet2Control(component, value)
{
	local normalizedValue = value / 100.0;
	local wetGainDB = Engine.getDecibelsForGainFactor(normalizedValue);
	local dryGainDB = Engine.getDecibelsForGainFactor(1 - normalizedValue);
	
	SendEffect2.setAttribute(SendEffect2.Gain, wetGainDB);
	PostGain2.setAttribute(PostGain2.Gain, dryGainDB);

};
Content.getComponent("KnbMasterDryWet2").setControlCallback(onKnbMasterDryWet2Control);

// Control callback for the Sampler C Master Dry/Wets
inline function onKnbMasterDryWet3Control(component, value)
{
	local normalizedValue = value / 100.0;
	local wetGainDB = Engine.getDecibelsForGainFactor(normalizedValue);
	local dryGainDB = Engine.getDecibelsForGainFactor(1 - normalizedValue);
	
	SendEffect3.setAttribute(SendEffect3.Gain, wetGainDB);
	PostGain3.setAttribute(PostGain3.Gain, dryGainDB);
};
Content.getComponent("KnbMasterDryWet3").setControlCallback(onKnbMasterDryWet3Control);
*/