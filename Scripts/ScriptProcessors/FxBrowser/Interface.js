Content.makeFrontInterface(939, 706);

//Effects Files
include("Effects/EffectsDeclarations.js");
include("Effects/EffectsArchive.js");
include("Effects/EffectsHandling.js");
include("Effects/EffectsKnobLaf.js");
include("Effects/EffectsBrowser.js");

// Fx Slot IDs for storing state in presets
const var fxSlotIDs = ["FxSlot1", "FxSlot2", "FxSlot3", "FxSlot4", "FxSlot5", "FxSlot6", "FxSlot7", "FxSlot8", "FxSlot9", "FxSlot10", "FxSlot11", "FxSlot12"];

// Create the fxSlotConfigurations array dynamically
const var fxSlotConfigurations = [];

for (var i = 0; i < fxSlotIDs.length; i++) {
    fxSlotConfigurations.push({
        "ID": fxSlotIDs[i],
        "RemovedProperties": ["bypass"],
        "RemovedChildElements": ["Modulator"]
    });
}

// Function to add an effect slot to the user preset system
function addFxSlotToPreset(slotConfig) {
    Engine.addModuleStateToUserPreset(slotConfig);
}

// Add each FX slot configuration to the user preset system
for (var i = 0; i < fxSlotConfigurations.length; i++) {
    addFxSlotToPreset(fxSlotConfigurations[i]);
}


// Initialize Knobs
for (var i = 0; i < KnobNames.length; i++) {
    for (var j = 0; j < KnobNames[i].length; j++) {
        var knob = Content.getComponent(KnobNames[i][j]);
        var pos = knobPositions[j % knobPositions.length];
        knob.set("x", pos.x);
        knob.set("y", pos.y);
        knob.set("width", knobWidth);
        knob.set("height", knobHeight);
        knob.set("min", 0.0); 
        knob.set("max", 100.0); 
        knob.set("middlePosition", 50.0); 
        Knobs.push(knob);
    }
}



// Set an Empty effect, otherwise update knobs to selected effect
function updateFxSlotUI(effectId, slotIndex) {
    if (effectId === "") {
        FxLabels[slotIndex].set("visible", false);
        PlusLabels[slotIndex].set("visible", true);
        PlusLabels[slotIndex].set("text", "+");
        for (var i = 0; i < 8; i++) {
            var knob = Content.getComponent(KnobNames[slotIndex][i]);
            knob.showControl(false);
        }
    } else {
        //FxLabels[slotIndex].set("text", displayName);
        PlusLabels[slotIndex].set("visible", false);
        FxLabels[slotIndex].set("visible", true);
        updateKnobsForEffect(effectId, slotIndex); // Use the centralized function
    }
}

// Function to check for changes in effect IDs and update UI accordingly
function checkEffectChanges() {
    for (var i = 0; i < FxSlots.length; i++) {
        var effectId = FxSlots[i].getCurrentEffectId();
        updateFxSlotUI(effectId, i);
    }
}


// Set up a timer to periodically check for changes
const var updateTimer = Engine.createTimerObject();
updateTimer.setTimerCallback(function() {
    checkEffectChanges();
});

// Start the timer to check every second (1000 milliseconds)
updateTimer.startTimer(200);

// Call the function initially to set the initial state
checkEffectChanges();




/*
// Create a Broadcaster object
const var bc = Engine.createBroadcaster({
    "id": "NetworkBroadcaster",
    "args": ["component", "value"]
});

// Define the callback function that will be called when a message is received
function onNetworkChange(component, value)
{
    Console.print("The effect slot network has changed!");
    Console.print("Component: " + component + ", New Value: " + value);
    // Add any other logic you want to execute when the network changes
}

// Add a listener for the broadcaster to call the onNetworkChange function
bc.addListener({
    "id": "NetworkChangeListener"
}, "Effect Slot Network Change Listener", onNetworkChange);
*/


/*
var effectId = FxSlot1.getCurrentEffectId();
//Console.print("FxSlot1 current effect ID: " + effectId);
   
const var KnbParam1 = Content.getComponent("KnbParam1");
const var FxLabel1 = Content.getComponent("FxLabel1");
const var LabelPlusFx1 = Content.getComponent("LabelPlusFx1");




var lastEffectId = "";

// Function to update the knobs and labels for FxSlot1
function updateFxSlot1UI(effectId) {
    if (effectId === "Flanger") {
        FxLabel1.set("text", effectId);
        PlusLabels[0].set("visible", true);
        KnbParam1.showControl(false); // Hide knob if effect is "Flanger"
    } else {
        FxLabel1.set("text", "");
        PlusLabels[0].set("visible", false);
        KnbParam1.showControl(true); // Show knob otherwise
    }
}


*/





/*
// Function to update knobs for the selected effect
function updateKnobsForEffect(effectName, panelIndex) {
    var knobIds = getKnobIdsForPanel(panelIndex);
    var effectKnobs = knobSettings[effectName];

    if (effectKnobs) {
        for (var i = 0; i < effectKnobs.length; i++) {
            var knobConfig = effectKnobs[i].config;
            var knobId = knobIds[effectKnobs[i].id];
            var knob = Content.getComponent(knobId);
            if (knob) {
                setKnobProperties(knobId, knobConfig);
                knob.setValue(Slots[panelIndex].getAttribute(effectKnobs[i].id)); // Get value from slot
            } else {
                Console.print("Invalid knobId: " + knobId);
            }
        }
    }
}

// Function to clear knobs for a panel
function clearKnobsForPanel(panelIndex) {
    var knobIds = getKnobIdsForPanel(panelIndex);
    for (var i = 0; i < knobIds.length; i++) {
        var knob = Content.getComponent(knobIds[i]);
        if (knob) {
            knob.showControl(false);
        }
    }
}

// Helper function to get knob IDs for a panel
function getKnobIdsForPanel(panelIndex) {
    var baseId = 1 + panelIndex * 8;
    var knobIds = [];
    for (var i = 0; i < 8; i++) {
        knobIds.push("KnbParam" + (baseId + i));
    }
    return knobIds;
}

// Helper function to set knob properties
function setKnobProperties(knobId, properties) {
    var knob = Content.getComponent(knobId);
    if (knob) {
        knob.set("text", properties.text);
        knob.setRange(properties.min, properties.max, properties.stepSize);
        knob.set("middlePosition", properties.middlePosition);
        knob.set("defaultValue", properties.defaultValue);
        knob.set("suffix", properties.suffix);
        knob.showControl(true);
    }
}
*/



/*
//FX PAGE
FXPage.set("allowCallbacks", true); 
FXPage.set("enabled", true); 

const var FXPanelSamplers = Content.getComponent("FXPanelSamplers");
FXPanelSamplers.set("allowCallbacks", true); 

const var FXPanelMaster = Content.getComponent("FXPanelMaster");
FXPanelMaster.set("allowCallbacks", true); 

//Show/Hide Sampler or Master FX Page
inline function onFxPageButtonControl(component, value)
{
	FXPanelSamplers.set("enabled", !value); 
	FXPanelSamplers.set("visible", !value); 
	FXPanelMaster.set("enabled", value);
    FXPanelMaster.set("visible", value); 
};

Content.getComponent("FxPageButton").setControlCallback(onFxPageButtonControl);
*/


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
    /*  This callback just calls the page handling function with the respective page.
    *   The other custom callbacks are implemented in the onInit script.
    */
	switch(number)
    {
        case APageButton: handlePages(APage); break;
        case BPageButton: handlePages(BPage); break;
        case CPageButton: handlePages(CPage); break;
        case FXPageButton: handlePages(FXPage); break;
case SeqPageButton: handlePages(SeqPage); break;
case SettingsPageButton: handlePages(StgPage); break;
case MainPageButton: handlePages(MainPage); break;


    }
}