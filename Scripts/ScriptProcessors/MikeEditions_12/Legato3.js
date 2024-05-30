 /**
   * Title: Synth Legato/Portamento v1.0.0.js
   * Author: David Healey
   * Date: 02/07/2017
   * Modified: 02/07/2017
   * License: Public Domain
  */
  
  Content.setHeight(50);
  
  const heldNotes = [];
  const playedNotes = [];
  const releaseBuffer = [];
  const releaseGlideTimers = [];
  const releaseNotes = [];
  const releaseTriggerEventIds = Engine.createMidiList();
  const releaseTriggerVelocities = Engine.createMidiList();
  
  reg lastNote = -1;
  //reg previousFineDetune = 0;
  reg eventId;
  reg tuning;
  reg lastTime = 0;
  reg timeLimit = 0.025;
  reg lastTimeOff = 0;
  
  inline function newReleaseGlideTimerObject()
  {
  	local localTimer = Engine.createTimerObject();
  
  	localTimer.setTimerCallback(releaseGlideTimerCallback);
  
  	return { timer: localTimer, buffer: [] };
  }
  
  inline function releaseGlideTimerCallback()
  {
  	local parent = getParent(releaseGlideTimers, this);
  
  	glide(parent.buffer[0], parent.buffer[1], parent.buffer[2]);
  
  	//Console.print("Portamento: Release glide");
  
  	this.stopTimer();
  }
  
  //GUI
  const time = Content.addKnob("Time", 0, 0);
  time.setRange(0, 2000, 0.01);
  
  const releaseTrigger = Content.addButton("releaseTrigger", 150, 10);
  releaseTrigger.set("saveInPreset", false);
  
  inline function getFirstFreeReleaseGlideTimer()
  {
  	for (x in releaseGlideTimers)
  	{
  		if (!x.timer.isTimerRunning())
  			return x;
  	}
  
  	releaseGlideTimers.push(newReleaseGlideTimerObject());
  	//Console.print("Portamento: Had to create a new timer. Please consider increasing the pool size at initialization. The pool size has been increased to " + releaseGlideTimers.length);
  	return releaseGlideTimers[releaseGlideTimers.length - 1];
  }
  
  inline function getParent(array, value)
  {
  	for (obj in array)
  		if (obj.timer == value)
  			return obj;
  
  	Console.print("Portamento: Could not identify the timer object. Aborting current spatialization. This issue MUST be debugged.");
  	value.stopTimer();
  }
  
  inline function removeFromHeldNotes(noteNumber)
  {
  	local i;
  
  	for (i = 0; i < heldNotes.length; i++)
  	{
  		if (heldNotes[i][0] == noteNumber)
  		{
  			heldNotes.removeElement(i);
  			break;
  		}
  	}
  }
  
  inline function fixPlayedNote(index)
  {
  	if (!isDefined(playedNotes[index][2]) || playedNotes[index][2] == null)
  	{
  		if (index > 0 && !(!isDefined(playedNotes[index - 1][2]) || playedNotes[index - 1][2] == null))
  			playedNotes[index][2] = playedNotes[index - 1][2];
  		else
  			playedNotes[index][2] = 0;
  	}
  }
  
  inline function glide(index, targetCoarseTune, targetFineTune)
  {
  	fixPlayedNote(index);
  
  	local coarseTune = !isDefined(targetCoarseTune) || targetCoarseTune == null ? 0 : targetCoarseTune;
  	local fineTune = !isDefined(targetFineTune) || targetFineTune == null ? 0 : targetFineTune;
  	Synth.addPitchFade(playedNotes[index][1], time.getValue(), coarseTune - playedNotes[index][0], fineTune);
  }
  
  inline function findIndexes(noteNumber) // returns an array of length 1. Review this to allow sending larger sizes.
  {
  	local result = [];
  	local previousInterval = 100000;
  	local interval;
  	local i;
  
  	for (i = 0; i < playedNotes.length; i++)
  	{
  		interval = playedNotes[i][2] - noteNumber; // from destination to current note
  
  		if (interval > 0)
  		{
  			if (Math.abs(interval) > Math.abs(previousInterval))
  			{
  				if (i < playedNotes.length - 1 && previousInterval < 0 && playedNotes[i][2] == playedNotes[i + 1][2] && !(i > 1 && playedNotes[i - 1][2] == playedNotes[i - 2][2]))
  				{
  					result.push(i);
  					break;
  				}
  
  				if (i > 2 && previousInterval > 0 && playedNotes[i - 2][2] == playedNotes[i - 3][2])
  				{
  					result.push(i - 2);
  					break;
  				}
  
  				result.push(i - 1);
  				break;
  			}
  			else if (previousInterval == interval)
  			{
  				result.push(i - 1);
  				break;
  			}
  			else if (Math.abs(interval) == Math.abs(previousInterval))
  			{
  				if (i < playedNotes.length - 1 && playedNotes[i][2] == playedNotes[i + 1][2])
  				{
  					result.push(i);
  					break;
  				}
  
  				result.push(i - 1);
  				break;
  			}
  			else
  			{
  				if (i == playedNotes.length - 1 && i > 1 && playedNotes[i - 1][2] == playedNotes[i - 2][2])
  				{
  					result.push(i - 1);
  					break;
  				}
  
  				//Console.print("Portamento: Possible unimplemented exception");
  			}
  		}
  
  		if (i == playedNotes.length - 1) // Catch the last iteration
  		{
  			result.push(i);
  			break;
          }
  
  		previousInterval = interval;
  	}
  
  	return result;
  }
  
  inline function findIndexesOnRelease(noteNumber)
  {
  	local result = [];
  	local i;
  
  	for (i = 0; i < playedNotes.length; i++)
  		if (playedNotes[i][2] == noteNumber)
  			result.push(i);
  
  	return result;
  }
  
  inline function getTargetNotesOnPressed(indexes) // Must be updated to send multiple values
  {
  	local result = [];
  	local i;
  
  	result.push([Message.getNoteNumber(), Message.getCoarseDetune(), Message.getFineDetune()]);
  
  	//for (i = 0; i < indexes.length - 1; i++)
  	//{
  	//	result.push(chooseNote(indexes[i]));
  	//}
  
  	//Engine.sortWithFunction(result, function(a, b)
  	//{
  	//	if (a[0] < b[0]) return -1;
  	//	if (a[0] > b[0]) return 1;
  	//});
  
  	return result;
  }
  
  
  inline function chooseNoteOnRelease(indexes)
  {
  	local notes = heldNotes.clone();
  	local result = [];
  	local i;
  	local j;
  	local previousInterval = 100000;
  	local interval;
  	local played = [];
  
  	Engine.sortWithFunction(notes, function(a, b)
  	{
  		if (a[0] < b[0]) return -1;
  		if (a[0] > b[0]) return 1;
  	});
  
  	for (x in playedNotes)
  		played.push(x[2]);
  
  	for (i = notes.length - 1; i >= 0; i--)
  	{
  		if ((indexes[0] > 0 && notes[i][0] < played[indexes[0] - 1]) || (indexes[indexes.length - 1] < played.length - 1 && notes[i][0] > played[indexes[indexes.length - 1] + 1]))
  			notes.removeElement(i);
  	}
  
  	//Console.print(trace(notes));
  
  	for (j = 0; j < notes.length; j++) // Closest note
  	{
  		interval = Math.abs(playedNotes[indexes[0]][2] - notes[j][0]);
  
  		if (interval >= previousInterval || (j > 0 && j == notes.length - 1 && indexes[indexes.length - 1] != played.length - 1))
  		{
  			if (!played.contains(notes[j - 1][0]))
  			{
  				result = notes[j - 1];
  				break;
  			}
  			else if (!played.contains(notes[j][0]))
  			{
  				result = notes[j];
  				break;
  			}
  			else if (j > 1 && !played.contains(notes[j - 2][0]))
  			{
  				if (indexes[0] > 0)
  				{
  					if (notes[j - 2][0] > played[indexes[0] - 1])
  					{
  						result = notes[j - 2];
  						break;
  					}
  					else
  					{
  						result = notes[j - 1];
  						break;
  					}
  				}
  				else
  				{
  					result = notes[j - 2];
  					break;
  				}
  			}
  			else // No "free" notes...
  			{
  				if (interval < previousInterval)
  				{
  					result = notes[j];
  					break;
  				}
  				else
  				{
  					result = notes[j - 1];
  					break;
  				}
  			}
  		}
  
  		if (j == notes.length - 1)
  		{
  			result = notes[j];
  			break;
  		}
  
  		previousInterval = interval;
  	}
  	//return notes[i - 1];
  	return result;
  }function onNoteOn()
{
	if (time.getValue() > 0)
	{
		local timeDiff = Engine.getUptime() - lastTime;	

		if (playedNotes.length == 0 || timeDiff < timeLimit)
		{
			//timer.stopTimer();
			//lastNote = Message.getNoteNumber();
			//eventId = Message.getEventId();

			local id = Message.makeArtificial();

			playedNotes.push([Message.getNoteNumber(), id, Message.getNoteNumber(), Message.getVelocity()]);

			Engine.sortWithFunction(playedNotes, function(a, b)
			{
				if (a[0] < b[0]) return -1;
				if (a[0] > b[0]) return 1;
			});

			if (releaseTrigger.getValue())
				Message.ignoreEvent(true);
		}
		else
		{
			local indexes = findIndexes(Message.getNoteNumber());
			local targetNotes = getTargetNotesOnPressed(indexes);
			local i;

			Message.ignoreEvent(true);

			for (i = 0; i < indexes.length; i++)
			{
				glide(indexes[i], targetNotes[i][0] + targetNotes[i][1], targetNotes[i][2]);
				playedNotes[indexes[i]][2] = targetNotes[i][0];
			}

			timeLimit = -1;

			//Console.print(trace(playedNotes));
		}

		heldNotes.push([Message.getNoteNumber(), Message.getCoarseDetune(), Message.getFineDetune(), Message.getVelocity()]);
		lastTime = Engine.getUptime();
	}
	else if (releaseTrigger.getValue())
	{
		Message.ignoreEvent(true);
		releaseTriggerVelocities.setValue(Message.getNoteNumber(), Message.getVelocity());
	}
}function onNoteOff()
{
	if (time.getValue() > 0)
	{
		removeFromHeldNotes(Message.getNoteNumber());
		Message.ignoreEvent(true);

		if (!Synth.getNumPressedKeys() && heldNotes.length == 0)// && eventId != -1)
		{
			if (releaseTrigger.getValue())
				if (releaseBuffer.length > 0)
					for (x in releaseBuffer[0][3])
						Synth.noteOffDelayedByEventId(Synth.playNote(x[2], x[3]), Engine.getSamplesForMilliSeconds(100));
				else
					for (x in playedNotes)
						Synth.noteOffDelayedByEventId(Synth.playNote(x[2], x[3]), Engine.getSamplesForMilliSeconds(100));
			else
				for (x in playedNotes)
					Synth.noteOffByEventId(x[1]);

			//Engine.allNotesOff();
			//heldNotes.clear();
			playedNotes.clear();
			timeLimit = 0.025;
			//lastNote = -1;
			//eventId = -1; // Causes an issue on glitch

			//for (x in releaseGlideTimers)
			//	x.timer.stopTimer();

			Synth.stopTimer();
			releaseBuffer.clear();

			//Console.print("All Notes Off");
		}
		else
		{
			local indexes = findIndexesOnRelease(Message.getNoteNumber());

			if (indexes.length > 0)
			{
				local i;

				for (i = 0; i < indexes.length; i++)
				{
					local heldNote = chooseNoteOnRelease(indexes);
					//local localTimer = getFirstFreeReleaseGlideTimer();

					//localTimer.buffer = [indexes[i], heldNote[0] + heldNote[1], heldNote[2]];
					releaseBuffer.push([indexes[i], heldNote[0] + heldNote[1], heldNote[2], playedNotes.clone()]);
					//localTimer.timer.startTimer(30);
					if (!Synth.isTimerRunning())
						Synth.startTimer(30 / 1000);

					playedNotes[indexes[i]][2] = heldNote[0];
					playedNotes[indexes[i]][3] = heldNote[3];
				}

				Engine.sortWithFunction(playedNotes, function(a, b)
				{
					if (a[0] < b[0]) return -1;
					if (a[0] > b[0]) return 1;
				});
			}
		}
	}
	else if (releaseTrigger.getValue())
	{
		//local id = Synth.playNote(Message.getNoteNumber(), Message.getVelocity());
		local n = Message.getNoteNumber();

		releaseTriggerEventIds.setValue(n, Synth.playNote(n, releaseTriggerVelocities.getValue(n)));
		Synth.noteOffDelayedByEventId(releaseTriggerEventIds.getValue(n), Engine.getSamplesForMilliSeconds(100));
	}
}function onController()
{
	
}
 function onTimer()
{
	for (x in releaseBuffer)
	{
		if (!Synth.isTimerRunning())
			break;

		glide(x[0], x[1], x[2]);
		//Console.print("Portamento: Release glide");
	}

	releaseBuffer.clear();
	Synth.stopTimer();
}function onControl(number, value)
{
	
}
 