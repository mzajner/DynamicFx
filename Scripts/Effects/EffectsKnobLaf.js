// Custom LAF;

namespace KnobStyles {
	
	// Use $bipolar in Slider text to set knob to bipolar. Text will be replaced
	// Drag lower edge of knob to control label position
	
	 // SMALL KNOB
	 const CONFIG_SMALL = {
	      SOCKEL_PADDING: 6,
	      BORDER: -1,
	      SHADOW_RADIUS: 10,
	      SHADOW_OFFSET: [0, 7],
	      SHADOW_PADDING: 3,
	      SHADOW_OPACITY: 0.7,
	      MASTER_PADDING: 7,
	      PADDING: 10,
	      LABEL_X_PADDING: 3,
	      ARC_COLOUR: 0xFF31765C,
	      ARC_COLOUR_VAR: Colours.withAlpha(Colours.white, 0.1),
	      INDICATOR_COLOUR: Colours.whitesmoke,
	      SOCKEL_UPPER: 0xB3171717,
	      SOCKEL_MID: 0x66919191,
	      SOCKEL_LOWER: 0x66333333,
	      BODY_UPPER: 0xFF858585,
	      BODY_LOWER: Colours.black,
	      INNER_BODY_UPPER: '0x66919191',
	      INNER_BODY_LOWER: '0x66333333',
	      TEXT_COLOUR: '0xFFFFFFFF',
	      ARC_STOPPERS: '0x66919191',
	      SHADOW_COLOUR: Colours.withAlpha('0xFB000000', 0.8),
	      STOPPER_THICKNESS: 0,
	      STOPPER_LENGTH: 0,
	      STOPPER_GAP: -7,
	      STOPPER_BORDER_RADIUS: 0,
	      ARC_THICKNESS: 5,
	      INDICATOR_THICKNESS: 1.3,
	      INDICATOR_LENGTH: 11,
	      INDICATOR_GAP: 17,
	      INDICATOR_BORDER_RADIUS: 1,
	      KNOB_ROTARY_START: 2.5,
	      FONT_NAME: 'Arial',
	      FONT_SIZE: 12,
	      LABEL_X_PADDING: 0.1,
	      LABEL_LOWER_PADDING: 0.1
	  };
	  
	const var LAF_FxKnobs = Content.createLocalLookAndFeel();
	
	LAF_FxKnobs.registerFunction("drawRotarySlider", smallKnob);
	
	inline function smallKnob(g, obj) {
			
		local a = obj.area;
		
		a = addPadding(a, CONFIG_SMALL.MASTER_PADDING);
		
		local disabled = !obj.enabled;
		local isBipolar = false;
		local start = CONFIG_SMALL.KNOB_ROTARY_START;
		local end = start * 2 * obj.valueNormalized - start;
		local full_end = start * 2 * 1 - start;
		
		if (obj.text.contains('$bipolar')) { 
			isBipolar = true;
			obj.text = obj.text.replace('$bipolar');	
		}
		
		if (isBipolar) start = 0;
		
		local text = obj.text;
		
		local sockelA = addPadding([a[0], a[1], a[2], a[2]], CONFIG_SMALL.SOCKEL_PADDING);
		local knobAreaBorder = addPadding([a[0], a[1], a[2], a[2]], CONFIG_SMALL.PADDING);
		local knobArea = addPadding(knobAreaBorder, CONFIG_SMALL.BORDER);
		local sa = addPadding([a[0], a[1], a[2], a[2]],  CONFIG_SMALL.SHADOW_PADDING);
		
		
		// special padded area
		local labelArea = [
			CONFIG_SMALL.PADDING,
			CONFIG_SMALL.PADDING,
			a[2] - CONFIG_SMALL.PADDING * 2,
			a[2] - CONFIG_SMALL.PADDING * 2
		];
		
		// Inline drawShadow
		local shadowPath = Content.createPath();
		shadowPath.addArc([0.0, 0.0, 1.0, 1.0], 0, Math.PI * 2);
		if (!disabled) {
			g.drawDropShadowFromPath(
				shadowPath,
				sa,
				CONFIG_SMALL.SHADOW_COLOUR,
				CONFIG_SMALL.SHADOW_RADIUS, CONFIG_SMALL.SHADOW_OFFSET
			);
		}
		
		// STOPPERS
		g.setColour(CONFIG_SMALL.ARC_STOPPERS);
		// Inline drawStoppers
		local widthStoppers = a[2] + a[0] * 2;
		local end_1 = CONFIG_SMALL.KNOB_ROTARY_START * 2 * 0 - CONFIG_SMALL.KNOB_ROTARY_START;
		local end_2 = CONFIG_SMALL.KNOB_ROTARY_START * 2 * 1 - CONFIG_SMALL.KNOB_ROTARY_START;
	
		g.fillRoundedRectangle([
			widthStoppers / 2 - (CONFIG_SMALL.STOPPER_THICKNESS / 2),
			a[0] + CONFIG_SMALL.STOPPER_GAP,
			CONFIG_SMALL.STOPPER_THICKNESS,
			(widthStoppers / 100 ) * CONFIG_SMALL.STOPPER_LENGTH],
			CONFIG_SMALL.STOPPER_BORDER_RADIUS
		);
	
		g.rotate(end_1, [widthStoppers / 2 , widthStoppers / 2 ]);
		g.fillRoundedRectangle([
			widthStoppers / 2 - (CONFIG_SMALL.STOPPER_THICKNESS / 2),
			a[0] + CONFIG_SMALL.STOPPER_GAP,
			CONFIG_SMALL.STOPPER_THICKNESS,
			(widthStoppers / 100 ) * CONFIG_SMALL.STOPPER_LENGTH],
			CONFIG_SMALL.STOPPER_BORDER_RADIUS
		);
		g.rotate(end_1 * -1, [widthStoppers / 2 , widthStoppers / 2 ]);
	
		g.rotate(end_2, [widthStoppers / 2 , widthStoppers / 2 ]);
		g.fillRoundedRectangle([
			widthStoppers / 2 - (CONFIG_SMALL.STOPPER_THICKNESS / 2),
			a[0] + CONFIG_SMALL.STOPPER_GAP,
			CONFIG_SMALL.STOPPER_THICKNESS,
			(widthStoppers / 100 ) * CONFIG_SMALL.STOPPER_LENGTH],
			CONFIG_SMALL.STOPPER_BORDER_RADIUS
		);
		g.rotate(end_2 * -1, [widthStoppers / 2 , widthStoppers / 2 ]);
		
		g.setGradientFill([
			CONFIG_SMALL.BODY_UPPER, 0.0, 0.0,
			CONFIG_SMALL.BODY_LOWER, 0.0, 50.0,
			]
		);
		g.fillEllipse(sockelA);
	
		g.setColour(CONFIG_SMALL.ARC_COLOUR_VAR);
		
		// Inline drawArc for CONFIG_SMALL.ARC_COLOUR
		local stableSizeArc1 = a[2];
		local arcThicknessArc1 = CONFIG_SMALL.ARC_THICKNESS / 100;
		local arcWidthArc1 = (1.0 - 2.0 * arcThicknessArc1) + arcThicknessArc1;
		local arcPathArc1 = Content.createPath();
		arcPathArc1.addArc(
			[arcThicknessArc1 / 2, arcThicknessArc1 / 2, arcWidthArc1, arcWidthArc1],
			-start,
			end
		);
		local pathAreaArc1 = arcPathArc1.getBounds(stableSizeArc1);
		pathAreaArc1 = [
			pathAreaArc1[0] + CONFIG_SMALL.MASTER_PADDING,
			pathAreaArc1[1] + CONFIG_SMALL.MASTER_PADDING,
			pathAreaArc1[2],
			pathAreaArc1[3]
		];
		g.setColour(CONFIG_SMALL.ARC_COLOUR);
		g.drawPath(arcPathArc1, pathAreaArc1, stableSizeArc1 * arcThicknessArc1);
	
		// Inline drawArc for CONFIG_SMALL.ARC_COLOUR_VAR
		local stableSizeArc2 = a[2];
		local arcThicknessArc2 = CONFIG_SMALL.ARC_THICKNESS / 100;
		local arcWidthArc2 = (1.0 - 2.0 * arcThicknessArc2) + arcThicknessArc2;
		local arcPathArc2 = Content.createPath();
		arcPathArc2.addArc(
			[arcThicknessArc2 / 2, arcThicknessArc2 / 2, arcWidthArc2, arcWidthArc2],
			-2.5,
			full_end
		);
		local pathAreaArc2 = arcPathArc2.getBounds(stableSizeArc2);
		pathAreaArc2 = [
			pathAreaArc2[0] + CONFIG_SMALL.MASTER_PADDING,
			pathAreaArc2[1] + CONFIG_SMALL.MASTER_PADDING,
			pathAreaArc2[2],
			pathAreaArc2[3]
		];
		
		g.setColour(CONFIG_SMALL.ARC_COLOUR_VAR);
		g.drawPath(arcPathArc2, pathAreaArc2, stableSizeArc2 * arcThicknessArc2);
	
		g.setColour(CONFIG_SMALL.TEXT_COLOUR);
		
		local labelText = text;
		
		if (obj.hover || obj.clicked) {
			labelText = obj.valueAsText;
		}
		
		g.setFont(CONFIG_SMALL.FONT_NAME, CONFIG_SMALL.FONT_SIZE);            
		g.drawAlignedText(labelText, [a[0], a[3] - CONFIG_SMALL.LABEL_X_PADDING, a[2], CONFIG_SMALL.LABEL_LOWER_PADDING], 'centred');
		
		g.setGradientFill([
			CONFIG_SMALL.SOCKEL_UPPER, 0.0, 0.0,
			CONFIG_SMALL.SOCKEL_LOWER, 0.0, 80.0,
			false,
			CONFIG_SMALL.SOCKEL_MID, 0.2,
			]
		);
		g.fillEllipse(knobArea);
		
	// INDICATOR
	g.setColour(CONFIG_SMALL.INDICATOR_COLOUR);
	local indicatorThickness = CONFIG_SMALL.INDICATOR_THICKNESS;
	local indicatorLength = CONFIG_SMALL.INDICATOR_LENGTH;
	local indicatorGap = CONFIG_SMALL.INDICATOR_GAP;
	local indicatorBorderRadius = CONFIG_SMALL.INDICATOR_BORDER_RADIUS;
	local widthIndicator = knobAreaBorder[2] + knobAreaBorder[0] * 2;
		
	local endIndicator = CONFIG_SMALL.KNOB_ROTARY_START * 2 * obj.valueNormalized - CONFIG_SMALL.KNOB_ROTARY_START;
		
	g.rotate(endIndicator, [widthIndicator / 2 , widthIndicator / 2 ]);
	g.fillRoundedRectangle([
		widthIndicator / 2 - (indicatorThickness / 2),
		indicatorArea[0] + indicatorGap,
		indicatorThickness,
		(widthIndicator / 100 ) * indicatorLength],
		indicatorBorderRadius
	);
	}
	
	inline function addPadding(area, p)
	{
		if (typeof p == 'number') {
			return [area[0] + p, area[1] + p, area[2] - 2 * p, area[3] - 2 * p];			
		}
		if (typeof p == 'object') {
			return [area[0] + p.left, area[1] + p.top, area[2] - 2 * p.right, area[3] - 2 * bottom];	
		}
	}
}


const var SmallKnobs = [];
for(var i = 1; i <= 96; i++) {
    SmallKnobs.push(Content.getComponent("KnbParam" + i));
}


for (knb in SmallKnobs) {
    knb.setLocalLookAndFeel(KnobStyles.LAF_FxKnobs);
}

