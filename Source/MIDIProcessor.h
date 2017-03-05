#pragma once
/*
  ==============================================================================

	MIDIProcessor.h

This file is part of MIDI2LR. Copyright 2015-2017 by Rory Jaffe.

MIDI2LR is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

MIDI2LR is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
MIDI2LR.  If not, see <http://www.gnu.org/licenses/>.
  ==============================================================================
*/
#ifndef MIDIPROCESSOR_H_INCLUDED
#define MIDIPROCESSOR_H_INCLUDED
#include <memory>
#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiUtilities.h"
#include "NrpnMessage.h"

class MIDIProcessor final : private juce::MidiInputCallback {
public:
	MIDIProcessor() noexcept;
	virtual ~MIDIProcessor();
	void Init(void);

	// re-enumerates MIDI IN devices
	void RescanDevices();

	template <class T> void addCallback(T* object, void (T::*mf)(RSJ::Message)) {
		callbacks_.emplace_back(std::bind(mf, object, std::placeholders::_1));
	}

private:
	// overridden from MidiInputCallback
	void handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage&) override;

	void InitDevices_();

	NRPN_Filter nrpn_filter_;
	std::vector <std::function <void(RSJ::Message)>> callbacks_;
	std::vector <std::unique_ptr<juce::MidiInput>> devices_;
};

#endif  // MIDIPROCESSOR_H_INCLUDED
