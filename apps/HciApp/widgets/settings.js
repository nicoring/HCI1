function createSettings(stage, label, resumebuttons, instrumentbuttons, midibuttons, chordsbtn, chorddisplay, pentbtn, pentscreen) {
    return new Settings({
                            stage: stage,
                            label: label,
                            resumebuttons: resumebuttons,
                            instrumentbuttons: instrumentbuttons,
                            midibuttons: midibuttons,
                            showChords: chordsbtn,
                            chorddisplay: chorddisplay,
                            showPentatonic: pentbtn,
                            pentscreen: pentscreen
                        });
}

function Settings(items) {

    this.items = items;

    // states
    this.startedOnce = false;
    this.floorInstrument = false;
    this.ownInstrument = false;

    // pausing
    this.timeThreshold = 4000;
    this.lastContact = Date.now();
    this.noOneOnStage = true;

    this.setupScreens();
    this.switchScreenTo(this.showStartScreen);
}

/** show/ hide helpers **/

Settings.prototype.showLabel = function() {
    this.items.label.enabled = true;
}

Settings.prototype.hideLabel = function() {
    this.items.label.enabled = false;
}

Settings.prototype.showResumebuttons = function() {
    this.items.resumebuttons.enabled = true;
}

Settings.prototype.hideResumebuttons = function() {
    this.items.resumebuttons.enabled = false;
}

Settings.prototype.showInstrumentbuttons = function() {
    this.items.instrumentbuttons.enabled = true;
}

Settings.prototype.hideInstrumentbuttons = function() {
    this.items.instrumentbuttons.enabled = false;
}

Settings.prototype.showMidibuttons = function() {
    this.items.midibuttons.enabled = true;
}

Settings.prototype.hideMidibuttons = function() {
    this.items.midibuttons.enabled = false;
}

Settings.prototype.showChorddisplay = function() {
    this.items.chorddisplay.enabled = true;
    this.items.showPentatonic.enabled = true;
}

Settings.prototype.hideChorddisplay = function() {
    this.items.chorddisplay.enabled = false;
    this.items.showPentatonic.enabled = false;
}

Settings.prototype.showPentatonicScreen = function() {
    this.items.pentscreen.enabled = true;
    this.items.showChords.enabled = true;
}

Settings.prototype.hidePentatonicScreen = function() {
    this.items.pentscreen.enabled = false;
    this.items.showChords.enabled = false;
}

Settings.prototype.hideAll = function() {
    this.hideLabel();
    this.hideMidibuttons();
    this.hideResumebuttons();
    this.hideInstrumentbuttons();
    this.hideChorddisplay();
    this.hidePentatonicScreen();
}

/** screens **/

/**
 * assign static buttons with functionality
 */
Settings.prototype.setupScreens = function() {
    var _this = this;

    // instrument buttons
    this.items.instrumentbuttons.floorInstrument.onTap = function() {
        _this.switchScreenTo(_this.showFloorInstrumentScreen);
    }
    this.items.instrumentbuttons.ownInstrument.onTap = function() {
        _this.switchScreenTo(_this.showOwnInstrumentScreen);
    }

    // chords button (to switch to the pentatonic display)
    this.items.showPentatonic.onTap = function() {
        _this.switchScreenTo(_this.showPentatonicScreen);
    }
    // pentatonic button (to switch to the chords display)
    this.items.showChords.onTap = function() {
        _this.switchScreenTo(_this.showOwnInstrumentScreen);
    }
}

Settings.prototype.switchScreenTo = function(screenCallback) {
    this.hideAll();

    // noop
    this.items.stage.onContactDown = function() {};

    screenCallback.apply(this);
}

/**
 * Start Screen
 * show label
 *
 * when started first time
 * --> trigger action when contact down on stage
 *
 * when started once
 * --> show resume/ restart buttons
 * --> trigger only on buttons
 */
Settings.prototype.showStartScreen = function() {
    this.showLabel();

    if (this.startedOnce) {
        this.showResumeButtons();
    } else {
        var _this = this;
        this.items.stage.onContactDown = function() {
            _this.switchScreenTo(_this.showInstrumentScreen);
        }
    }

    this.startedOnce = true;
}

/**
 * Instrument Screen
 * show instrument buttons
 */
Settings.prototype.showInstrumentScreen = function() {
    this.showInstrumentbuttons();
}

/**
 * Floor Instrument Screen
 * show 4 midi buttons
 */
Settings.prototype.showFloorInstrumentScreen = function() {
    this.showMidibuttons();
}

/**
 * Own Instrument Screen
 * show chord hints
 */
Settings.prototype.showOwnInstrumentScreen = function() {
    this.showChorddisplay();
}

/** pausing **/

Settings.prototype.updateContact = function() {
    // get time delta
    var now = Date.now();
    var delta = now - this.lastContact;
    this.lastContact = now;

    if (this.noOneOnStage) {
        this.hideAll();
        this.showStartScreen();
    } else {
        // much time elapsed
        // player probably paused the session
        if (delta > this.timeThreshold) {
           this.noOneOnStage = true;
        }
    }

}
