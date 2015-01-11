function Settings(buttonset) {

    this.buttonset = buttonset;

    this.startedOnce = false;

    this.floorInstrument = false;
    this.ownInstrument = false;

    this.timeThreshold = 4000;
    this.lastContact = Date.now();
    this.noOneOnStage = true;

    // this.checkContacts();
}

Settings.prototype.showStartScreen = function() {
    this.buttonset.startLabel.enabled = true;

    if (this.startedOnce) {
        this.showResumeButtons();
    }

    this.startedOnce = true;

}

Settings.prototype.showInstrumentScreen = function() {
    this.buttonset.instrumentButtons.enabled = true
}

Settings.prototype.showResumeButtons = function() {
    this.buttonset.resumeButtons.enabled = true;
}

Settings.prototype.hideResumeButtons = function() {
    this.buttonset.resumeButtons.enabled = false;
}

Settings.prototype.hideAll = function() {
    this.hideMidiButtons();
    this.hideResumeButtons();
    this.hideInstrumentButtons();
}

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

//Settings.prototype.checkContacts = function() {

//}
