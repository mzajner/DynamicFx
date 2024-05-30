//========================================  EFFECTS HANDLING ======================================== 


// ---------- INITIATE PANELS AND SLOTS ---------- 
var currentFxPanel = FxPanels[0];
var currentFxSlot = FxSlots[0];


// ====================  DUMP BUTTONS ==================== 

// ---------- Dump Button Callback ---------- 
inline function onDumpButtonControl(component, value) {
    if (value) {
        local panelIndex = parseInt(component.get("id").replace("BtnRemoveEffect", "")) - 1;
        local fxSlot = FxSlots[panelIndex];
        fxSlot.clear(); // Clear the effect slot
        
        //Labels
        FxLabels[panelIndex].set("text", "");
        PlusLabels[panelIndex].set("visible", true);

        local knobIds = getKnobIdsForPanel(panelIndex);
        for(i = 0; i < knobIds.length; i++) {
            local knob = Content.getComponent(knobIds[i]);
            knob.showControl(false); // Hide each knob related to this panel
        }
	}
}

for (j = 0; j < FxPanels.length; j++) {
    Content.getComponent("BtnRemoveEffect" + (j + 1)).setControlCallback(onDumpButtonControl);
} // Assign callback to all dump buttons


// ====================  FX MENU MOUSE DISPLAY CALLBACK ====================  

// ---------- Fx Menu Visibility ---------- 
function showCustomEffectBrowser(panelId) {
    FxMenu1.set("visible", true); // Show the FX browser panel
    FxMenuBlurPanel.set("visible", true); // Show the background blur panel

    currentFxPanel = Content.getComponent(panelId);
    currentFxSlot = FxSlots[FxPanels.indexOf(currentFxPanel)];
    //Console.print(currentFxSlot);

    // Update the FX browser label
    var effectName = currentFxSlot.getCurrentEffectId();
    if (effectName) {
        FxDisplayLabel.set("text", effectName);
    } else {
        FxDisplayLabel.set("text", "Select Effect");
    }
}

// ---------- Panel Mouse Callback ---------- 
for (i = 0; i < FxPanels.length; i++) {
    FxPanels[i].setMouseCallback(function(event) {
        if (event.clicked) {
            //Console.print(this.data.id + " clicked");
            currentFxPanel = this; 
            currentFxSlot = FxSlots[FxPanels.indexOf(this)];
            //Console.print(currentFxSlot);
            //Console.print(this.data.id + " clicked");
            showCustomEffectBrowser(this.data.id);
        }
    });
    FxPanels[i].data.id = FxPanels[i].getId();
}


// ====================  FX KNOBS CALLBACK ====================  

// ---------- Knob IDs Per Panel ---------- 
function getKnobIdsForPanel(panelIndex) {
    var baseId = 1 + panelIndex * 8;
    var knobIds = [];
    for (var i = 0; i < 8; i++) {
        knobIds.push("KnbParam" + (baseId + i));
    }
    return knobIds;
}

// ---------- Knob Properties ---------- 
function setKnobProperties(knobId, properties) {
    var knob = Content.getComponent(knobId);
    if (knob) {
        knob.set("text", properties.text);
        knob.setRange(properties.min, properties.max, properties.stepSize);
        knob.set("mode", knobConfig.mode);
        knob.set("middlePosition", properties.middlePosition);
        knob.set("defaultValue", properties.defaultValue);
        knob.set("suffix", properties.suffix);
    }
}

// ---------- Initialize Knob Components from Names ---------- 
const var Knobs = [];
for (var i = 0; i < KnobNames.length; i++) {
    Knobs[i] = [];
    for (var j = 0; j < KnobNames[i].length; j++) {
        Knobs[i][j] = Content.getComponent(KnobNames[i][j]);
        Knobs[i][j].showControl(false);
    }
}

// ---------- Set Knob Controls based on Slot/Panel Index ---------- 
inline function onKnobControl(component, value) {
    for ( i = 0; i < Knobs.length; i++) {
        local index = Knobs[i].indexOf(component);
        if (index != -1) {
            Slots[i].setAttribute(index, value);
            //Console.print("Knob " + (index + 1 + i * 4) + " controls " + Slots[i].getId() + " Attribute " + index + ": " + value);
            break;
        }
    }
}

// ---------- Set control callbacks for each knob in each slot ---------- 
for ( i = 0; i < Knobs.length; i++) {
    for ( j = 0; j < Knobs[i].length; j++) {
        Knobs[i][j].setControlCallback(onKnobControl);
    }
}

/*
//Set SlotFx Effects to default values
// Define a function to apply an effect and set parameters to default values
function applyEffectToSlotWithDefaults(effectName, slot) {
    if (slot && 'setEffect' in slot) {
        var effect = slot.setEffect(effectName);
        if (effect) {
            var paramProperties = slot.getParameterProperties();
            for(var i = 0; i < paramProperties.length; i++) {
                var param = paramProperties[i];
                effect.setAttribute(i, param.defaultValue);
            }
            //Console.print("Effect " + effectName + " loaded with default parameters.");
        }
    } else {
        Console.print("Invalid slot or missing function 'setEffect'.");
    }
}

// Initialize all slots with a default effect on startup
function initializeSlots() {
    var defaultEffectName = "Empty"; // Change this to your actual default effect
    for(var i = 0; i < FxSlots.length; i++) {
        applyEffectToSlotWithDefaults(defaultEffectName, FxSlots[i]);
    }
}

// Call the initialization function when the script loads
initializeSlots();


// Clear everything by default and hide knobs
function clearEffectsAndResetKnobs() {
    for (var i = 0; i < FxSlots.length; i++) {
        FxSlots[i].clear();  // Clears each slot
    }
    
    var allKnobIds = [];
    for (var j = 0; j < FxPanels.length; j++) {
        var knobIds = getKnobIdsForPanel(j);

        for (var k = 0; k < knobIds.length; k++) {
            allKnobIds.push(knobIds[k]);
        }
    }
    
    // Reset and hide all knobs
    for (var k = 0; k < allKnobIds.length; k++) {
        var knob = Content.getComponent(allKnobIds[k]);
        if (knob) {
            //knob.setValue(0.0); // Reset to middle value or other neutral value
            //knob.set("text", text);
        	//knob.setRange(properties.min, properties.max, properties.stepSize);
        	//knob.set("middlePosition", properties.middlePosition);
        	//knob.set("defaultValue", properties.defaultValue);
        	//knob.setValue(properties.defaultValue);
        	//knob.showControl(0);
            knob.showControl(0);           
        }
    }

    Console.print("All effects cleared and knobs reset and hidden.");
}

// Call the clearing function on script load
clearEffectsAndResetKnobs();
//FxBrowserComboBox.setValue(0); 
*/


// ====================  FX MENU CALLBACKS ====================  

// ---------- Fx Menu Mouse Callback for selecting Individual Fx ---------- 
// This will log which Panel is clicked, associate it with the correct Slot index, and display the browser
for (i = 0; i < FxPanels.length; i++) {
    FxPanels[i].setMouseCallback(function(event) {
        if (event.clicked) {
            //Console.print(this.data.id + " clicked");
            currentFxPanel = this;
            currentFxSlot = FxSlots[FxPanels.indexOf(this)];
            showCustomEffectBrowser(this.data.id); // Trigger the custom browser for effect selection
        }
    });
    FxPanels[i].data.id = FxPanels[i].getId();
}
    
    
// ---------- Update FxPanel Components ---------- 
// Function to handle item selection
function itemSelected(displayName) {
    var mappedName = processFxMapping(displayName);
    
    FxDisplayLabel.set("text", displayName);
    FxMenu1.set("visible", false); // Hide the FX browser
    FxMenuBlurPanel.set("visible", false); // Hide the background blur
	
    if (currentFxSlot && 'setEffect' in currentFxSlot) {
        currentFxSlot.setEffect(mappedName);
        
        var panelIndex = FxPanels.indexOf(currentFxPanel);
        if (panelIndex != -1) {
            FxLabels[panelIndex].set("text", displayName);
            PlusLabels[panelIndex].set("visible", false);
            updateKnobsForEffect(mappedName, panelIndex);
            updateFxSlotUI(mappedName, panelIndex);
        }
       // bc.sendSyncMessage(["FxSlots", mappedName]);
    } else {
        Console.print("Error: No slot is currently selected or does not support setting an effect.");
    }
}

// ---------- Update Knob Properties ---------- 
// Function to update knobs for the selected effect
function updateKnobsForEffect(effectName, panelIndex) {
    var knobIds = getKnobIdsForPanel(panelIndex);
    var effectKnobs = knobSettings[effectName];

    if (effectKnobs) {
        for (var i = 0; i < knobIds.length; i++) {
            var knob = Content.getComponent(knobIds[i]);
            if (i < effectKnobs.length) {
                var knobConfig = effectKnobs[i].config;
                setKnobProperties(knobIds[i], knobConfig);
                knob.setRange(knobConfig.min, knobConfig.max, knobConfig.stepSize); // Set range first
                knob.set("mode", knobConfig.mode);
                knob.set("middlePosition", knobConfig.middlePosition); // Set midpoint within range
                knob.setValue(Slots[panelIndex].getAttribute(effectKnobs[i].id)); // Get value from slot
                knob.showControl(true); // Show the knob if it's being used
            } else {
                knob.showControl(false); // Hide the knob if it's not being used
            }
        }
    } else {
        // If no specific knob settings are found, hide all knobs
        for (var i = 0; i < knobIds.length; i++) {
            var knob = Content.getComponent(knobIds[i]);
            knob.showControl(false);
        }
    }
    
}


// Clear everything by default and hide knobs
function clearEffectsAndResetKnobs() {
    for (var i = 0; i < FxSlots.length; i++) {
        FxSlots[i].clear();  // Clears each slot
    }

    var allKnobIds = [];
    for (var j = 0; j < FxPanels.length; j++) {
        var knobIds = getKnobIdsForPanel(j);
        for (var k = 0; k < knobIds.length; k++) {
            allKnobIds.push(knobIds[k]);
        }
    }

    // Reset and hide all knobs
    for (var k = 0; k < allKnobIds.length; k++) {
        var knob = Content.getComponent(allKnobIds[k]);
        if (knob) {
            knob.showControl(false);           
        }
    }

    //Console.print("All effects cleared and knobs reset and hidden.");
}

// Call the clearing function on script load
clearEffectsAndResetKnobs();

// Initialize all slots with a default effect on startup
function initializeSlots() {
    var defaultEffectName = ""; // Change this to your actual default effect
    for (var i = 0; i < FxSlots.length; i++) {
       // Fxslots.setEffect(defaultEffectName, FxSlots[i]);
    }
}

// Call the initialization function when the script loads
initializeSlots();
