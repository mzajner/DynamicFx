Content.makeFrontInterface(300, 200);


//! ============ Look And Feel ============
const var laf = Engine.createGlobalScriptLookAndFeel();

// Function to draw arc knobs
laf.registerFunction("drawArcKnob", function(g, obj)
{
    var K = Content.createPath();
    var p1 = Content.createPath();
    var range = obj.max - obj.min;
    
    // start radian
    var startOffset = 2.5;
    var arcThickness = 0.1;
    var stableSize = 50;
    var arcWidth = 1.0 - 2.0 * arcThickness;

    p1.clear();

    // calculate the end radian from the current value
    var endOffset = -startOffset + 2.0 * startOffset * (obj.value - obj.min) / range; 
    
    var val = "";
    var a = obj.area;
    
    g.setColour(obj.bgColour);
    p1.addArc([arcThickness / 2, arcThickness / 2, arcWidth + arcThickness, arcWidth + arcThickness], - startOffset, 2.5);

    var pathArea = p1.getBounds(stableSize);
    g.setColour(obj.bgColour);
    g.drawPath(p1, pathArea, stableSize * arcThickness);

    K.addArc([arcThickness / 2, arcThickness / 2, arcWidth + arcThickness, arcWidth + arcThickness], -startOffset - 0.08, endOffset);   
    var pathArea = K.getBounds(stableSize);

    g.setColour(obj.textColour);
    g.drawPath(K, pathArea, stableSize * arcThickness );

    if (obj.hover || obj.clicked) {
        g.setColour(Colours.withAlpha(0xFFE5FF00, 1.00 ));
        g.drawPath(K, pathArea, stableSize * arcThickness );
    }

    // Text
    val = obj.value;
    g.setColour(Colours.withAlpha(obj.textColour, 0.86 ));
    g.setFont("Arial", 12);  
    g.drawAlignedText(Engine.doubleToString(val, 1) + " " + obj.suffix, [60, 7, a[2], 48], "left");
    g.setColour(obj.textColour);
    g.drawAlignedText(obj.text, [60, -5, a[2], 48], "left");

    // Point
    g.beginLayer(true);
    g.rotate(endOffset, [stableSize / 2, stableSize / 2]);
    g.setColour(0xBB000000);
    g.fillRoundedRectangle([stableSize / 2 - stableSize * 0.05, stableSize / 2 - stableSize * 0.5, stableSize  * 0.05, stableSize * 0.1], 0);
    g.endLayer();
});

const var Knob1 = Content.getComponent("Knob1");




// Assigning the custom LAF to specific knobs
Knob1.setLookAndFeel(laf);






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
 