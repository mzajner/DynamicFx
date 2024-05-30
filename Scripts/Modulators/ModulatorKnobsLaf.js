const var KnobLaf = Content.createLocalLookAndFeel();


KnobLaf.registerFunction("drawRotarySlider", function(g, obj) {
    var Area = obj.area;
    var KnobHeight = Area[HEIGHT];
    var KnobWidth = Area[HEIGHT];

    var underDrag = Content.getComponentUnderDrag() == obj.id;
    var LabelOffset = 10;
    var textArea = Rect.removeFromRight(obj.area, obj.area[2] - obj.area[3]);
    textArea[0] += LabelOffset;

	g.setColour(0xFFFFFFFF);
	g.setFont("Oxygen Bold", 12);
	g.drawAlignedText(obj.text, textArea, "left");

	g.setColour(0XFF838387); 
	g.setFont("Oxygen Regular", 10);
	g.drawAlignedText(obj.valueAsText, [textArea[0], textArea[1] + 15, textArea[2], textArea[3]], "left");
	
	var isBipolar = obj.min < 0 && obj.id != "Knob1";
	var start = isBipolar ? 0 : -2.7;
	var modStart = isBipolar ? (-2.7 + obj.valueNormalized * 2 * 2.7) : -2.7;

	g.setColour(0x10000000);

	var radius = 35 - obj.clicked;

	g.fillEllipse(Rect.translated(Rect.withSizeKeepingCentre(obj.area, radius + 2, radius +2), 0, 2));
	g.fillEllipse(Rect.translated(Rect.withSizeKeepingCentre(obj.area, radius + 2, radius +2), 0, 3));
	g.fillEllipse(Rect.translated(Rect.withSizeKeepingCentre(obj.area, radius + 2, radius +2), 0, 4));
	
	//Arc
	var p = Content.createPath();
	
	p.startNewSubPath(0, 0);
	p.startNewSubPath(1,1);
	p.addArc([0.0, 0.0, 1.0, 1.0], -2.7, 2.7);
	
	g.setColour( 0xBE3F3F3F); //Unfilled portion of arc
	g.drawPath(p, Rect.reduced(obj.area, 5), 4);
	g.setColour(underDrag ? 0x88555555 : 0x88181818);
	g.drawPath(p, Rect.reduced(obj.area, 1), 2);

	p = Content.createPath();
		
	p.startNewSubPath(0, 0);
	p.startNewSubPath(1,1);
	p.addArc([0.0, 0.0, 1.0, 1.0], start, -2.66 + Math.max(0.01, obj.valueNormalized) * 2 * 2.66);
	
	g.setColour(Colours.withAlpha(obj.itemColour1, obj.clicked ? 1.0 : 0.8));
	g.drawPath(p, Rect.reduced(obj.area, 5), 4);
	
	p = Content.createPath();
			
	p.startNewSubPath(0, 0);
	p.startNewSubPath(1,1);
	var modValue = matrix.getModValue(obj.id);
	
	var numMods = matrix.getConnectionData(obj.id).length;
	
	if(numMods > 0)
	{
		g.setColour(Colours.white);
		g.drawAlignedText(numMods, obj.area.clone(), "topRight");
	}
	
	
	//Arc
	p.addArc([0.0, 0.0, 1.0, 1.0], modStart, -2.66 + Math.max(0.01, modValue) * 2 * 2.66);
	g.setColour(Colours.withAlpha(obj.itemColour2, obj.clicked ? 0.8 : 0.5));
	g.drawPath(p, Rect.reduced(obj.area, 1), 2);
	g.addDropShadowFromAlpha(0x44000000, 5);

	//Hover & Drag functions
	g.setGradientFill([0xFF818081, 0.0, 0.0,
					   0xAA5F5F5F, 0.0, obj.area[3], false]);
	g.fillEllipse(Rect.withSizeKeepingCentre(obj.area, radius, radius));
	
	if(obj.hover)
	{
		g.setColour(0xAA5F5F5F);
		g.fillEllipse(Rect.withSizeKeepingCentre(obj.area, radius, radius));
	}
	
	g.setGradientFill([0xB32F2F2F, 0.0, 0.0,
					   0xFF818081, 0.0, obj.area[3], true]);
	g.drawEllipse(Rect.withSizeKeepingCentre(obj.area, radius-3, radius-3), 3.5);
	
	if(underDrag)
	{
		g.setColour(0x22FFFFFF);
		g.fillEllipse(Rect.reduced(obj.area, 6));
	}
	
	//Small Value Indicator in the center of the knob indicating value
	g.setColour(Colours.white); // Rectangle Color
	g.rotate(-2.66 + obj.valueNormalized * 2.66 * 2, Rect.getCentre(obj.area));
	g.fillRect(Rect.translated(Rect.withSizeKeepingCentre(obj.area, 1.5, 7), 0, -8)); // Rectangle size

});


// ----- MASTER ASSIGN ----- 
GainC.setLocalLookAndFeel(KnobLaf);
PanC.setLocalLookAndFeel(KnobLaf);
GainB.setLocalLookAndFeel(KnobLaf);
PanB.setLocalLookAndFeel(KnobLaf);
GainA.setLocalLookAndFeel(KnobLaf);
PanA.setLocalLookAndFeel(KnobLaf);

FilterFreqKnob1.setLocalLookAndFeel(KnobLaf);
FilterQKnob1.setLocalLookAndFeel(KnobLaf);