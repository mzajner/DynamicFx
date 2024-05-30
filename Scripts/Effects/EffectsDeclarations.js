//==================== EFFECTS DECLARATIONS AND POSITIONS ====================

// ---------- MENU CATEGORIES & CHILDREN FX ----------
//The list of categories and items displayed in the Fx Menu 
const var FxMenuList = {
    "Delay": ["Reverse Delay", "Slapback Delay", "Twist Delay"],
    "Distortion": ["Digital Saturation","Haze Distortion", "Modern Saturation", "Shred Distortion", "Vintage Saturation"],
    "Filter": ["Filters"],
    "Modulation": ["Auto-Panner", "Flanger", "Grains", "Phaser"],
    "Reverb": ["Infinite Reverb", "Glisten Reverb"],
    "Utility": ["Compressor", "Detuner", "Looper", "Mid/Side", "TransientShaper", "Widener"]
};

// ---------- FX List ---------- 
//The list of Fx Networks that are loaded into the Slot Fx
const var FxNetworksList = ["Empty", 
"AutoPanner",
"Compressor",
"Detuner",
"Flanger",
"GlistenReverb",
"Grains",
"HazeDistortion",
"Looper",
"Phaser_Script",
"ReverseDelay",
"SaturatorDigital",
"SaturatorModern",
"SaturatorVintage",
"ShredDistortion",
"SlapbackDelay",
"TransientShaper",
"TwistDelay",
"Widener"]; 

// ---------- FX MAPPING ---------- 
//Map the Items (names displayed in the Fx Menu) to the FxList (names of the Fx networks)

function processFxMapping(displayName) {
    var mappedName;
    
    if (displayName == "Reverse Delay") {
        mappedName = "ReverseDelay";
    } else if (displayName == "Slapback Delay") {
        mappedName = "SlapbackDelay";
    } else if (displayName == "Twist Delay") {
        mappedName = "TwistDelay";
    } else if (displayName == "Shred Distortion") {
        mappedName = "ShredDistortion";
    } else if (displayName == "Haze Distortion") {
        mappedName = "HazeDistortion";
    } else if (displayName == "Infinite Reverb") {
        mappedName = "InfiniteReverb";
    } else if (displayName == "Glisten Reverb") {
        mappedName = "GlistenReverb";
    } else if (displayName == "Auto-Panner") {
        mappedName = "AutoPanner";
    } else if (displayName == "Mid/Side") {
        mappedName = "Mid/Side";
    } else if (displayName == "Phaser") {
        mappedName = "Phaser_Script";
    } else if (displayName == "Auto-Panner") {
        mappedName = "AutoPanner";
    } else if (displayName == "Digital Saturator") {
            mappedName = "SaturatorDigital";
    } else if (displayName == "Modern Saturator") {
            mappedName = "SaturatorModern";
    } else if (displayName == "Vintage Saturator") {
            mappedName = "SaturatorVintage";
    } else if (displayName == "TransientShaper") {
            mappedName = "Transient Shaper";
        
    } else {
        mappedName = displayName; // Fallback to the display name if no match is found
    }
    
      return mappedName;
}

// Test the mapping function
processFxMapping("Reverse Delay");
processFxMapping("Slapback Delay");
processFxMapping("Twist Delay");
processFxMapping("Unknown Name"); // Test with a name that is not mapped


// ---------- SLOTS ---------- 
const var Slots = [
    Synth.getEffect("FxSlot1"),
    Synth.getEffect("FxSlot2"),
    Synth.getEffect("FxSlot3"),
    Synth.getEffect("FxSlot4"),
    Synth.getEffect("FxSlot5"),
    Synth.getEffect("FxSlot6"),
    Synth.getEffect("FxSlot7"),
    Synth.getEffect("FxSlot8"),
    Synth.getEffect("FxSlot9"),
    Synth.getEffect("FxSlot10"),
    Synth.getEffect("FxSlot11"),
    Synth.getEffect("FxSlot12")];
    

// ---------- FX SLOTS ---------- 
// Initialize FxSlots array
const var FxSlots = [
    Synth.getSlotFX("FxSlot1"),
    Synth.getSlotFX("FxSlot2"),
    Synth.getSlotFX("FxSlot3"),
    Synth.getSlotFX("FxSlot4"),
    Synth.getSlotFX("FxSlot5"),
    Synth.getSlotFX("FxSlot6"),
    Synth.getSlotFX("FxSlot7"),
    Synth.getSlotFX("FxSlot8"),
    Synth.getSlotFX("FxSlot9"),
    Synth.getSlotFX("FxSlot10"),
    Synth.getSlotFX("FxSlot11"),
    Synth.getSlotFX("FxSlot12")
];

// ---------- FX SLOTS INDIVIDUAL---------- 
const var FxSlot1 = Synth.getSlotFX("FxSlot1");
const var FxSlot2 = Synth.getSlotFX("FxSlot2");
const var FxSlot3 = Synth.getSlotFX("FxSlot3");
const var FxSlot4 = Synth.getSlotFX("FxSlot4");
const var FxSlot5 = Synth.getSlotFX("FxSlot5");
const var FxSlot6 = Synth.getSlotFX("FxSlot6");
const var FxSlot7 = Synth.getSlotFX("FxSlot7");
const var FxSlot8 = Synth.getSlotFX("FxSlot8");
const var FxSlot9 = Synth.getSlotFX("FxSlot9");
const var FxSlot10 = Synth.getSlotFX("FxSlot10");
const var FxSlot11 = Synth.getSlotFX("FxSlot11");
const var FxSlot12 = Synth.getSlotFX("FxSlot12");








// ---------- FX PANELS ---------- 
const var FxPanels = [];
for (var i = 1; i <= 12; i++) {
    FxPanels.push(Content.getComponent("FxPanel" + i));
}

// ---------- FX LABELS ---------- 
const var FxLabels = [];

// ---------- PLUS LABELS ---------- 
const var PlusLabels = [];

// ---------- FX KNOBS ---------- 
const var KnobNames = [
    ["KnbParam1", "KnbParam2", "KnbParam3", "KnbParam4", "KnbParam5", "KnbParam6", "KnbParam7", "KnbParam8"],
    ["KnbParam9", "KnbParam10", "KnbParam11", "KnbParam12", "KnbParam13", "KnbParam14", "KnbParam15", "KnbParam16"],
    ["KnbParam17", "KnbParam18", "KnbParam19", "KnbParam20", "KnbParam21", "KnbParam22", "KnbParam23", "KnbParam24"],
    ["KnbParam25", "KnbParam26", "KnbParam27", "KnbParam28", "KnbParam29", "KnbParam30", "KnbParam31", "KnbParam32"],
    ["KnbParam33", "KnbParam34", "KnbParam35", "KnbParam36", "KnbParam37", "KnbParam38", "KnbParam39", "KnbParam40"],
    ["KnbParam41", "KnbParam42", "KnbParam43", "KnbParam44", "KnbParam45", "KnbParam46", "KnbParam47", "KnbParam48"],
    ["KnbParam49", "KnbParam50", "KnbParam51", "KnbParam52", "KnbParam53", "KnbParam54", "KnbParam55", "KnbParam56"],
    ["KnbParam57", "KnbParam58", "KnbParam59", "KnbParam60", "KnbParam61", "KnbParam62", "KnbParam63", "KnbParam64"],
    ["KnbParam65", "KnbParam66", "KnbParam67", "KnbParam68", "KnbParam69", "KnbParam70", "KnbParam71", "KnbParam72"],
    ["KnbParam73", "KnbParam74", "KnbParam75", "KnbParam76", "KnbParam77", "KnbParam78", "KnbParam79", "KnbParam80"],
    ["KnbParam81", "KnbParam82", "KnbParam83", "KnbParam84", "KnbParam85", "KnbParam86", "KnbParam87", "KnbParam88"],
    ["KnbParam89", "KnbParam90", "KnbParam91", "KnbParam92", "KnbParam93", "KnbParam94", "KnbParam95", "KnbParam96"]];

// ---------- KNOB POSITIONS ---------- 
const var knobWidth = 70;
const var knobHeight = 80;
const var knobPositions = [
    {x: 0.0, y: 30.0},
    {x: 70.0, y: 30.0},
    {x: 0.0, y: 110.0},
    {x: 70.0, y: 110.0},
    {x: 140.0, y: 30.0},
    {x: 210.0, y: 30.0},
    {x: 140.0, y: 110.0},
    {x: 210.0, y: 110.0}];

// ---------- FX KNOBS POSITION AND SIZE ---------- 
function setKnobPositionAndSize(knob, x, y, width, height) {
    if (knob) {
        knob.set("x", x);
        knob.set("y", y);
        knob.set("width", width);
        knob.set("height", height);
    }
}

// ---------- FX KNOBS PER PANEL ---------- 
for (var slotIndex = 0; slotIndex < 12; slotIndex++) {
    for (var knobIndex = 0; knobIndex < knobPositions.length; knobIndex++) {
        var knobId = 1 + slotIndex * 8 + knobIndex;
        var knob = Content.getComponent("KnbParam" + knobId);
        var pos = knobPositions[knobIndex];
        setKnobPositionAndSize(knob, pos.x, pos.y, knobWidth, knobHeight);
    }
}

// ---------- FX LABELS POSITION AND SIZE ---------- 
for (var i = 0; i < FxPanels.length; i++) {
    var label = Content.addLabel("FxLabel" + (i + 1), 70, 10); 
    label.set("text", "");
    label.set("width", 140);
    label.set("height", 20);
    //label.set("fontStyle", Arial);
    label.set("fontSize", 16);
    label.set("parentComponent", FxPanels[i].getId());
    //label.set("alignment", centredTop, [FxPanels[i].getWidth() / 2, 20]); // Adjust positioning based on panel size
    FxLabels.push(label);
}

// ---------- PLUS LABELS ---------- 
for (var i = 0; i < FxPanels.length; i++) {
    var plusLabel = Content.addLabel("FxPlusLabel" + (i + 1), 95, 50); 
    plusLabel.set("text", "+");  
    plusLabel.set("parentComponent", FxPanels[i].getId());
    plusLabel.set("enabled", 0);
    plusLabel.set("width", 90);
    plusLabel.set("height", 90);
    plusLabel.set("fontSize", 150);  
    plusLabel.set("alignment", "centred"); 
    //plusLabel.set("textColour", 0x57FFFFFF);
    PlusLabels.push(plusLabel);
}


// ---------- DUMP BUTTONS ---------- 
for (var i = 0; i < FxPanels.length; i++) {
    var dumpButton = Content.addButton("BtnRemoveEffect" + (i + 1), 250, 10);
    dumpButton.set("text", "Dump Effect");
    dumpButton.set("parentComponent", FxPanels[i].getId()); 
}