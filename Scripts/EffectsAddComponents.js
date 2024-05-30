//============CREATE PANLS=============

/*
//Create the buttons
const var buttonWidth = 60; 
const var buttonHeight = 20; 
const var buttonMargin = 10;

for (var i = 0; i < FxPanels.length; i++) {
    var panel = FxPanels[i];

    // Create a button for each panel
    var button = Content.addButton("BtnEnableFx" + (i + 1), buttonMargin, buttonMargin);
    button.set("width", buttonWidth);
    button.set("height", buttonHeight);
    button.set("parentComponent", panel.getId());
    button.set("text", "ON.OFF");
}

//CCreate FX Panels
const var panelsPerRow = 3;
const var numRows = 2;
const var margin = 20;  // Margin around each panel and between panels

// Assuming FXPanelSamplers has dimensions already defined:
const var parentWidth = 920;
const var parentHeight = 500;

const var topBottomOffset = 30; // 30 pixels offset from top and bottom

// Adjust panelHeight to deduct the additional top and bottom offsets
const var panelHeight = (parentHeight - (margin * (numRows + 1)) - (topBottomOffset * 2)) / numRows;
const var panelWidth = (parentWidth - margin * (panelsPerRow + 1)) / panelsPerRow;

const var FxPanels = [];

for (var row = 0; row < numRows; row++) {
    for (var col = 0; col < panelsPerRow; col++) {
        var panelIndex = row * panelsPerRow + col; // Calculate the index for naming
        var panelX = margin + col * (panelWidth + margin);

        // Include topBottomOffset in the Y position calculation
        var panelY = topBottomOffset + margin + row * (panelHeight + margin);

        var newPanel = Content.addPanel("FxPanel" + (panelIndex + 1), panelX, panelY);
        newPanel.set("width", panelWidth);
        newPanel.set("height", panelHeight);
        newPanel.set("parentComponent", FXPanelSamplers.getId());
        newPanel.set("allowCallbacks", true);
        newPanel.set("enabled", true);
        FxPanels.push(newPanel);
    }
}
*/


/*
const var knobWidth = 70;
const var knobHeight = 80;

// Define X and Y positions for each set of knobs
const var x1 = 0.0, y1 = 30.0;
const var x2 = 70.0, y2 = 30.0;
const var x3 = 0.0, y3 = 110.0;
const var x4 = 70.0, y4 = 110.0;
const var x5 = 140.0, y5 = 30.0;
const var x6 = 210.0, y6 = 30.0;
const var x7 = 140.0, y7 = 110.0;
const var x8 = 210.0, y8 = 110.0;

// Define knob arrays and positions using the defined coordinates
const var knobs = [
    { array: [Content.getComponent("KnbParam1"), Content.getComponent("KnbParam9")], x: x1, y: y1 },
    { array: [Content.getComponent("KnbParam2"), Content.getComponent("KnbParam10")], x: x2, y: y2 },
    { array: [Content.getComponent("KnbParam3"), Content.getComponent("KnbParam11")], x: x3, y: y3 },
    { array: [Content.getComponent("KnbParam4")], x: x4, y: y4 },
    { array: [Content.getComponent("KnbParam5")], x: x5, y: y5 },
    { array: [Content.getComponent("KnbParam6")], x: x6, y: y6 },
    { array: [Content.getComponent("KnbParam7")], x: x7, y: y7 },
    { array: [Content.getComponent("KnbParam8")], x: x8, y: y8 }
];

// Function to set knob properties
function setKnobProperties(knobArray, x, y) {
    for (var i = 0; i < knobArray.length; i++) {
        if (knobArray[i]) {
            knobArray[i].set("x", x);
            knobArray[i].set("y", y);
            knobArray[i].set("width", knobWidth);
            knobArray[i].set("height", knobHeight);
        }
    }
}

// Apply settings to each knob in the arrays
for (var i = 0; i < knobs.length; i++) {
    setKnobProperties(knobs[i].array, knobs[i].x, knobs[i].y);
}
*/




/*
//Knob Height and Width
const var knobWidth = 70;
const var knobHeight = 80;

//Knob Positions:;
const var KnobSlot1 = [];
for (var i = 0; i < 12; i++) {
    var knobId = 1 + i * 8; // Starts at 1 and jumps by 8 each time
    KnobSlot1.push(Content.getComponent("KnbParam" + knobId));
}


// Position and size settings
const var knobX1 = 0.0;
const var knobY1 = 30.0;

// Apply settings to each knob in the array
for(var i = 0; i < KnobSlot1.length; i++) {
    if (KnobSlot1[i]) {
        KnobSlot1[i].set("x", knobX1);
        KnobSlot1[i].set("y", knobY1);
        KnobSlot1[i].set("width", knobWidth);
        KnobSlot1[i].set("height", knobHeight);
    }
}

//Knob Positions:;
const var KnobSlot2 = [];
for (var i = 0; i < 12; i++) {
    var knobId = 2 + i * 8; // 
    KnobSlot2.push(Content.getComponent("KnbParam" + knobId));
}

// Position and size settings
const var knobX2 = 70.0;
const var knobY2 = 30.0;

// Apply settings to each knob in the array
for(var i = 0; i < KnobSlot2.length; i++) {
    if (KnobSlot2[i]) {
        KnobSlot2[i].set("x", knobX2);
        KnobSlot2[i].set("y", knobY2);
        KnobSlot2[i].set("width", knobWidth);
        KnobSlot2[i].set("height", knobHeight);
    }
}


//Knob Positions:;
const var KnobSlot3 = [];
for (var i = 0; i < 12; i++) {
    var knobId = 3 + i * 8; // 
    KnobSlot3.push(Content.getComponent("KnbParam" + knobId));
}

// Position and size settings
const var knobX3 = 0.0;
const var knobY3 = 110.0;

// Apply settings to each knob in the array
for(var i = 0; i < KnobSlot3.length; i++) {
    if (KnobSlot3[i]) {
        KnobSlot3[i].set("x", knobX3);
        KnobSlot3[i].set("y", knobY3);
        KnobSlot3[i].set("width", knobWidth);
        KnobSlot3[i].set("height", knobHeight);
    }
}

const var KnobSlot4 = [];
for (var i = 0; i < 12; i++) {
    var knobId = 4 + i * 8; // 
    KnobSlot4.push(Content.getComponent("KnbParam" + knobId));
}

// Position and size settings
const var knobX4 = 70.0;
const var knobY4 = 110.0;


// Apply settings to each knob in the array
for(var i = 0; i < KnobSlot4.length; i++) {
    if (KnobSlot4[i]) {
        KnobSlot4[i].set("x", knobX4);
        KnobSlot4[i].set("y", knobY4);
        KnobSlot4[i].set("width", knobWidth);
        KnobSlot4[i].set("height", knobHeight);
    }
}

const var KnobSlot5 = [];
for (var i = 0; i < 12; i++) {
    var knobId = 5 + i * 8; // 
    KnobSlot5.push(Content.getComponent("KnbParam" + knobId));
}

// Position and size settings
const var knobX5 = 140.0;
const var knobY5 = 30.0;


// Apply settings to each knob in the array
for(var i = 0; i < KnobSlot5.length; i++) {
    if (KnobSlot5[i]) {
        KnobSlot5[i].set("x", knobX5);
        KnobSlot5[i].set("y", knobY5);
        KnobSlot5[i].set("width", knobWidth);
        KnobSlot5[i].set("height", knobHeight);
    }
}

const var KnobSlot6 = [];
for (var i = 0; i < 12; i++) {
    var knobId = 6 + i * 8; // 
    KnobSlot6.push(Content.getComponent("KnbParam" + knobId));
}

// Position and size settings
const var knobX6 = 210.0;
const var knobY6 = 30.0;


// Apply settings to each knob in the array
for(var i = 0; i < KnobSlot6.length; i++) {
    if (KnobSlot5[i]) {
        KnobSlot6[i].set("x", knobX6);
        KnobSlot6[i].set("y", knobY6);
        KnobSlot6[i].set("width", knobWidth);
        KnobSlot6[i].set("height", knobHeight);
    }
}

const var KnobSlot7 = [];
for (var i = 0; i < 12; i++) {
    var knobId = 7 + i * 8; // 
    KnobSlot7.push(Content.getComponent("KnbParam" + knobId));
}

// Position and size settings
const var knobX7 = 140.0;
const var knobY7 = 110.0;


// Apply settings to each knob in the array
for(var i = 0; i < KnobSlot7.length; i++) {
    if (KnobSlot5[i]) {
        KnobSlot7[i].set("x", knobX7);
        KnobSlot7[i].set("y", knobY7);
        KnobSlot7[i].set("width", knobWidth);
        KnobSlot7[i].set("height", knobHeight);
    }
}

const var KnobSlot8 = [];
for (var i = 0; i < 12; i++) {
    var knobId = 8 + i * 8; // 
    KnobSlot8.push(Content.getComponent("KnbParam" + knobId));
}

// Position and size settings
const var knobX8 = 210.0;
const var knobY8 = 110.0;


// Apply settings to each knob in the array
for(var i = 0; i < KnobSlot8.length; i++) {
    if (KnobSlot8[i]) {
        KnobSlot8[i].set("x", knobX8);
        KnobSlot8[i].set("y", knobY8);
        KnobSlot8[i].set("width", knobWidth);
        KnobSlot8[i].set("height", knobHeight);
    }
}

function setKnobPositionAndSize(knob, x, y, width, height) {
    if (knob) {
        knob.set("x", x);
        knob.set("y", y);
        knob.set("width", width);
        knob.set("height", height);
    }
}

// Usage for each knob slot
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
    {x: 210.0, y: 110.0}
];

for (var slotIndex = 0; slotIndex < 12; slotIndex++) {
    for (var knobIndex = 0; knobIndex < knobPositions.length; knobIndex++) {
        var knobId = 1 + slotIndex * 8 + knobIndex;
        var knob = Content.getComponent("KnbParam" + knobId);
        var pos = knobPositions[knobIndex];
        setKnobPositionAndSize(knob, pos.x, pos.y, knobWidth, knobHeight);
    }
}
*/