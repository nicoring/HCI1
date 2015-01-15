/** Move all three chords one step from left to right*/
function startSliding() {
    goToNextChordAnimation.running = true;
}

/** Return an array containing the three chords structered*/
function getCurrentChordState(){
    // Determine which chord is on which position
    var cur, next, hidden;
    if (moveCurrentAnimation.target.rid === 2) {
        cur = chord2;
        next = chord1;
        hidden = chord0;
    } else if (moveCurrentAnimation.target.rid === 1) {
        cur = chord1;
        next = chord0;
        hidden = chord2;
    } else if (moveCurrentAnimation.target.rid === 0) {
        cur = chord0;
        next = chord2;
        hidden = chord1;
    }

    return {
        current: cur,
        next: next,
        hidden: hidden
    };
}

/** Update the target properties of the animations */
function rearrangeAnimationTargets(state) {

    // "Next" becomes the current chord
    moveCurrentAnimation.target = state.next;
    scaleCurrentAnimation.target = state.next;
    moveToStartAnimation.target = state.next;

    // "Hidden" becomes the next chord
    moveNextAnimation.target = state.hidden;
    scaleNextAnimation.target = state.hidden;

    // "Current" is hidden
    moveForNextAnimation.target = state.current;
    scaleForNextAnimation.target = state.current;
}

/** Get all available chords and take one of them randomly */
function generateRandomChord() {
    // @disable-check M112
    var chords = new Array("A-Dur", "A-Moll", "As-Dur", "B-Dur",
                           "C-Dur", "C-Moll", "D-Dur", "D-Moll",
                           "E-Dur", "E-Moll", "Es-Dur" ,"F-Dur",
                           "Fis-Moll", "F-Moll", "G-Dur", "G-Moll",
                           "H-Moll");
    var randomIndex = Math.floor((Math.random() * 17));
    return chords[randomIndex];
}

/** Load the new chord image for the hidden chord object*/
function loadChordImage(state, nextChord) {
    state.hidden.effect.texture = "../guitar chords/" + nextChord + ".jpg";
}
