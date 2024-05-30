Content.makeFrontInterface(600, 600);

include("Effects/EffectsArchive.js");

const var Panel1 = Content.getComponent("Panel1");

const var FxSlot1 = Synth.getSlotFX("FxSlot1");
const var Slot1 = Synth.getEffect("FxSlot1");
const var ComboBox1 = Content.getComponent("ComboBox1");
         
const var Label1 = Content.getComponent("Label1");

const var Knobs = 		[Content.getComponent("Knob1"),
                       Content.getComponent("Knob2"),
                       Content.getComponent("Knob3"),
                       Content.getComponent("Knob4")];
              
const var Panel2 = Content.getComponent("Panel2");
const var Label2 = Content.getComponent("Label2");
const var ComboBox2 = Content.getComponent("ComboBox2");

const var Knobs2 = [Content.getComponent("Knob8"),
                    Content.getComponent("Knob5"),
                    Content.getComponent("Knob6"),
                    Content.getComponent("Knob7")];


var effectName = FxSlot1.getCurrentEffectId();

// Initialize Broadcaster with metadata
const var fxSlotBroadcaster = Engine.createBroadcaster({
    "id": "FxSlot1Broadcaster",
    "colour": -1, // Use random color
    "tags": ["audio", "value-handling"],
    "args": ["effectName"] // Define the argument
});



// Add FxSlot1 to the user preset system
Engine.addModuleStateToUserPreset({
    "ID": "FxSlot1",
    "RemovedProperties": ["bypass"],
    "RemovedChildElements": ["Modulator"]
});


// Function to update the knobs based on the effect loaded into FxSlot1
function updateKnobsForEffect(effectName) {
    if (knobSettings[effectName]) {
        for (var i = 0; i < Knobs.length; i++) {
            var knobConfig = knobSettings[effectName][i].config;
            var knob = Knobs[i];
            knob.set("text", knobConfig.text);
            knob.setRange(knobConfig.min, knobConfig.max, knobConfig.stepSize);
            var value = Slot1.getAttribute(i);
            knob.setValue(value);
            knob.showControl(true);
        }
    } else {
        for (var i = 0; i < Knobs.length; i++) {
            Knobs[i].showControl(false);
        }
    }
}

// Inline function for knob control callbacks
inline function onKnobControl(component, value) {
    for (i = 0; i < Knobs.length; i++) {
        if (Knobs[i] == component) {
            Slot1.setAttribute(i, value);
            break;
        }
    }
}

// Set control callbacks for each knob
for (var i = 0; i < Knobs.length; i++) {
    Knobs[i].setControlCallback(onKnobControl);
}



// Function to load an effect into FxSlot1 and update UI elements
function loadEffect(effectName) {
    if (FxSlot1.setEffect(effectName)) {
        Label1.set("text", effectName);
        updateKnobsForEffect(effectName);
    } else {
        Label1.set("text", "Empty");
        for (i = 0; i < Knobs.length; i++) {
            Knobs[i].showControl(false);
        }
    }
}

// Initial load (example with "Reverb" effect)
loadEffect("Reverb");



inline function onComboBox1Control(component, value) {
    local effectName = ComboBox1.getItemText();
    loadEffect(effectName);
    fxSlotBroadcaster.addListener("FxSlot1", "CurrentEffectId", "onComboBox1Control");
}

ComboBox1.setControlCallback(onComboBox1Control);





function onNoteOn()
{
	
}
 function onNoteOff()
{
	
}
 function onController()
{
	
}
 function onTimer()
{
	
}
 function onControl(number, value)
{
	
}
 