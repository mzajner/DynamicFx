//========================================  EFFECTS CUSTOM BROWSER/MENU ======================================== 


// ====================  MENU PROPERTIES ==================== 
// The list of categories and items is inside EffectsDeclarations

// ---------- MENU COLOURS & PROPERTIES ---------- 
// Colour Variables
var PanelBackground = 0x300C0F2D;
var PanelColour = 0x0021319A; // Dark grey
var HoverColour = 0x7094A2FF; // Slightly darker grey for hover effect
var ClickColour = 0xBB94A2FF; // Darker grey for click effect
var ItemColour = 0x566D75A4;
var CategoryTextColour = Colours.whitesmoke;
var ItemTextColour = Colours.whitesmoke;
var ArrowColour = Colours.whitesmoke;

// Other Properties
const var lineHeight = 30; //Height of categories and items
const var list = []; // This will store panel references and their visibility state


// ====================  VARIABLES ==================== 

// ---------- MAIN MENU ---------- 
const var FxMenu1 = Content.getComponent("FxMenu1");
FxMenu1.set("visible", false); 

// ---------- BLUR PANEL ---------- 
const var FxMenuBlurPanel = Content.getComponent("FxMenuBlurPanel");
//FxMenuBlurPanel.loadImage("{PROJECT_FOLDER}NewBlur.png", "Blur");
FxMenuBlurPanel.set("visible", false); 
/*
FxMenuBlurPanel.setPaintRoutine(function(g)
{
	var a = this.getLocalBounds(0);
	
	g.drawImage("Blur", a, 0, 0);
});
*/

// ---------- MENU DISPLAY PANEL ---------- 
const var FxMenuDisplayPanel = Content.addPanel("FxMenuDisplayPanel");
var FxMenuDisplayPanelX = FxMenuDisplayPanel.set("x", 320);
var FxMenuDisplayPanelY = FxMenuDisplayPanel.set("y", 20);
FxMenuDisplayPanel.set("width", 280);
FxMenuDisplayPanel.set("height", 30); 
FxMenuDisplayPanel.set("allowCallbacks", "Clicks & Hover");

// ---------- MENU DISPLAY LABEL ---------- 
const var FxDisplayLabel = Content.addLabel("FxDisplayLabel", FxMenuDisplayPanelX + 50, FxMenuDisplayPanelY +0 );
FxDisplayLabel.set("text", "Select Effect");
FxDisplayLabel.set("fontName", "Arial");
FxDisplayLabel.set("fontSize", 20);
FxDisplayLabel.set("textColour", CategoryTextColour);
FxDisplayLabel.set("alignment", "centred");
FxDisplayLabel.set("editable", false);



// ====================  LIST (CATEGORIES + ITEM) CONTROLS ==================== 

// ---------- CLEAR CHILD PANELS ---------- 
// Clear existing panels before recreating them
function clearPanels() {
    var children = FxMenu1.getChildPanelList();
    for (i = children.length - 1; i >= 0; i--) {
        children[i].removeFromParent();
    }
}
clearPanels();

// Paint Panel Background Colour
FxMenu1.setPaintRoutine(function(g) {
    g.fillAll(PanelBackground); 
});

// ---------- UPDATE LIST ---------- 
//Paint the list
inline function updateList() {
    local y = 0;
    for (c in list) {
        if (c.panel.get("visible")) {
            c.panel.set("y", y);
            y += lineHeight;
        }
    }
    FxMenu1.set("height", y); // Adjust panel height dynamically
    FxMenu1.repaint(); // Force a repaint immediately after updating
}

// ---------- ITEM VISIBILITY ---------- 
// Toggles the visibility of child panels (items)
inline function toggleChildren(parentText) {
    // Collapse all categories first
    for (c in list) {
        if (c.parentText != "" && c.parentText != parentText) {
            c.panel.set("visible", true);
            c.panel.set("visible", false);
        }
    }

    // Explicitly manage visibility of current category's items
    local categoryIsActive = false;  // Track if the category is active
    for (c in list) {
        if (c.parentText == parentText) {
            // If the category is active, decide the new visibility state
            if (!categoryIsActive) {  // Determine if we need to show or hide items
                categoryIsActive = c.panel.get("visible");
            }
            c.panel.set("visible", !categoryIsActive);
        }
    }

    // Update the UI list after managing visibility
    updateList();
}

/*
// I think this is for debugging, so it could be removed
// When clicking on an item, make sure it doesn't trigger category toggle
inline function onItemClick(text) {
    Console.print("Item clicked: " + text);
    itemSelected(text);
    resetClickStates(null); // Reset states, but ignore the null because all should be reset
}
*/

// ---------- RESET CLICKS ---------- 
function resetClickStates(exceptPanel) {
    for (c in list) {
        if (c.panel != exceptPanel) { // Check all panels, not just non-category ones
            c.panel.data.clicked = false;
            c.panel.repaint();
        }
    }
}


// ====================   FX MENU LAF ==================== 

// ---------- CREATE ROWS ---------- 
// Function to create each panel for effects or categories
inline function createRow(text, isCategory, parentText) {
    local p = FxMenu1.addChildPanel();
    p.data.text = text;
    p.data.isCategory = isCategory;
    p.data.clicked = false;
    p.set("width", FxMenu1.getWidth());
    p.set("height", lineHeight);
    p.set("allowCallbacks", "Clicks & Hover");
    
    // Set different width and height for categories and items
        if (isCategory) {
            p.set("width", FxMenu1.getWidth());
            p.set("height", lineHeight);
        } else {
            // Items are indented by 10 pixels and are slightly smaller in height
            p.set("width", FxMenu1.getWidth() - 10);
            p.set("height", lineHeight - 1); // Optionally adjust the height to be smaller
            p.set("x", 10); // Shift the item rightwards to create an indentation
            p.set("y", 1);
        } 

// ---------- PAINT ROUTINE ---------- 
    p.setPaintRoutine(function(g) {
        var backgroundColor = this.data.isCategory ? PanelColour : ItemColour;
        if (this.data.hover) backgroundColor = HoverColour;
        if (this.data.clicked) backgroundColor = ClickColour;
        
        
// ---------- ROUNDED RECTANGLE ---------- 
    	var rectWidth = this.getWidth() - 2 - 5;  
    	var rectHeight = this.getHeight() - 3; 
    	var xPos = 0;  
    	var yPos = 0;  
    	var cornerRadius = 3; 
    	g.setColour(backgroundColor);
    	g.fillRoundedRectangle([xPos, yPos, rectWidth, rectHeight], cornerRadius);
    	
// ---------- TEXT COLOUR & ALIGNMENT---------- 
        var textColour = this.data.isCategory ? CategoryTextColour : ItemTextColour;
        g.setFont("Arial", this.data.isCategory ? 20 : 14);
        g.setColour(textColour);
        g.drawAlignedText(this.data.text, [15, 0, this.getWidth() - 20, this.getHeight()], "left");

// ---------- ARROWS ---------- 		
        if (this.data.isCategory) {
            var arrowPath = Content.createPath();
            var arrowSize = 7;
            var arrowX = this.getWidth() - 20;
            var arrowY = this.getHeight() / 2 + arrowSize / 2;
            arrowPath.startNewSubPath(arrowX, arrowY);
            arrowPath.lineTo(arrowX + arrowSize, arrowY - arrowSize);
            arrowPath.lineTo(arrowX - arrowSize, arrowY - arrowSize);
            arrowPath.closeSubPath();
            g.setColour(ArrowColour);
            g.fillPath(arrowPath, arrowX);
        }
    });
	
// ---------- VISIBILITY ---------- 		
	    if (isCategory) {
	        p.set("visible", true); // Categories are visible
	    } else {
	        p.set("visible", false); // Items are not visible by default
	    }
	    

// --------------------   MOUSE CALLBACKS --------------------
    // Mouse callback to handle clicks and hover
    p.setMouseCallback(function(event) {
        this.data.hover = event.hover;
        if (event.clicked) {
            resetClickStates(this); // Reset all other panels' clicked state
            
            if (this.data.isCategory) {
                toggleChildren(this.data.text);
            } else {
                Console.print("Item clicked: " + this.data.text);
                itemSelected(this.data.text); 
            }
        	this.data.clicked = !this.data.clicked; // Toggle the clicked state of this panel 
        }
        this.repaint();
    });

    list.push({panel: p, parentText: parentText});
}

// ---------- CRREATE CATEGORIES AND ITEMS IN ROWS ---------- 		
for (category in FxMenuList) {
    createRow(category, true, ""); // Create category row
    for (fx in FxMenuList[category]) {
        createRow(fx, false, category); // Create effect row under each category
    }
}
updateList(); // Make sure the UI is updated after initialization

FxMenu1.repaint();





// ====================   FX DISPLAY MENU PANEL ==================== 

// ---------- DISPLAY MENU CONTROL + VISIBILITY ---------- 
/*		    
function itemSelected(effectName) {
    FxDisplayLabel.set("text", effectName);
    FxMenu1.set("visible", false); // Hide the FX browser
    FxMenuBlurPanel.set("visible", false); // Hide the background blur

    if (currentFxSlot && 'setEffect' in currentFxSlot) {
        currentFxSlot.setEffect(effectName);

        var panelIndex = FxPanels.indexOf(currentFxPanel);
        if (panelIndex != -1) {
            FxLabels[panelIndex].set("text", effectName);
            PlusLabels[panelIndex].set("visible", false);
            updateKnobsForEffect(effectName, panelIndex);
        }
    } else {
        Console.print("Error: No slot is currently selected or does not support setting an effect.");
    }
}
*/

// ---------- DISPLAY MENU PAINT ROUTINE ---------- 			    
FxMenuDisplayPanel.setPaintRoutine(function(g) {
	var backgroundColor = this.data.isCategory ? PanelColour : ItemColour;
    if (this.data.hover) backgroundColor = HoverColour;
    if (this.data.clicked) backgroundColor = ClickColour;
	g.setColour(backgroundColor);  
	//g.fillRoundedRectangle([xPos, yPos, rectWidth, rectHeight], cornerRadius);
	    
	// Rounded Rectangle Setup
	var rectWidth = this.getWidth() - 2; 
	var rectHeight = this.getHeight() - 2; 
	var xPos = 0;  
	var yPos = 1;  
	var cornerRadius = 3; 
	g.setColour(backgroundColor);
	g.fillRoundedRectangle([xPos, yPos, rectWidth, rectHeight], cornerRadius);
	

     // Arrow setup
    var arrowPath = Content.createPath();
    var arrowSize = 7;
    var arrowX = this.getWidth() - 20;
    var arrowY = this.getHeight() / 2 + arrowSize / 2;
    arrowPath.startNewSubPath(arrowX, arrowY);
    arrowPath.lineTo(arrowX + arrowSize, arrowY - arrowSize);
    arrowPath.lineTo(arrowX - arrowSize, arrowY - arrowSize);
    arrowPath.closeSubPath();

    g.setColour(ArrowColour);
    g.fillPath(arrowPath, arrowX);
});

// --------------------   MOUSE CALLBACKS --------------------
//FxMenuDisplayPanel Mouse Callback
FxMenuDisplayPanel.setMouseCallback(function(event) {
    this.data.hover = event.hover;
    if (event.clicked) {
        FxMenu1.set("visible", !FxMenu1.get("visible")); 
        FxMenuBlurPanel.set("visible", !FxMenuBlurPanel.get("visible"));// Toggle visibility 
    }
    this.repaint();
});

// Ensure repaint is properly triggered
FxMenuDisplayPanel.repaint();






