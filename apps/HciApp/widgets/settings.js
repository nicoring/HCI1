function ButtonsetSettings(buttonset) {

    this.buttonset = buttonset;

    this.startedOnce = false;

    this.floorInstrument = false;
    this.ownInstrument = false;

    this.timeThreshold = 4000;
    this.lastContact = Date.now();
    this.noOneOnStage = true;

    // this.checkContacts();
}

ButtonsetSettings.prototype.showStartScreen = function() {
    this.buttonset.startLabel.enabled = true;

    if (this.startedOnce) {
        this.showResumeButtons();
    }

    this.startedOnce = true;

}

ButtonsetSettings.prototype.showInstrumentScreen = function() {
    this.buttonset.instrumentButtons.enabled = true
}

ButtonsetSettings.prototype.showResumeButtons = function() {
    this.buttonset.resumeButtons.enabled = true;
}

ButtonsetSettings.prototype.hideResumeButtons = function() {
    this.buttonset.resumeButtons.enabled = false;
}

ButtonsetSettings.prototype.hideAll = function() {
    this.hideMidiButtons();
    this.hideResumeButtons();
    this.hideInstrumentButtons();
}

ButtonsetSettings.prototype.updateContact = function() {
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

//ButtonsetSettings.prototype.checkContacts = function() {

//}
