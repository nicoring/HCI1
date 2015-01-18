// --- Musical control --------------------------------------------------------

// Each subarray contains the stages I(0), II(1), IV(2), V(3), VI(4) (I equals the key)
// Implemented key options: Es, B, F, C, G, D, A (chords are in german notation)
// @disable-check M112
var chords = new Array();
chords["Es"] = ["Es", "Fm", "As", "B", "Cm"];
chords["B"] = ["B", "Cm", "Es", "F", "Gm"];
chords["F"] = ["F", "Gm", "B", "C", "Dm"];
chords["C"] = ["C", "Dm", "F", "G", "Am"];
chords["G"] = ["G", "Am", "C", "D", "Em"];
chords["D"] = ["D", "Em", "G", "A", "Hm"];
chords["A"] = ["A", "Hm", "D", "E", "Fism"]; // "Fism" -> "Fis-Moll" / "F sharp minor"

// Global variables to control the music support
var key = undefined;
var cardence = undefined;
var curIndex = 0;

/** Throw an error if the key is not allowed -> Otherwise return it*/
function checkForAllowedKey(key) {
    switch(key) {
    case "Es":
    case "B":
    case "F":
    case "C":
    case "G":
    case "D":
    case "A":
        break;
    default:
        throw "MIDI interface sent a not accepted key!";
    }
    return key;
}

function doOneSlidingStep() {
    var preloadChord = cardence[getChordIndex(curIndex + 3)];
    // Slides the chord from left to right and preloads the following 'next chord'
    chorddis_player1.doOneSlidingStep(preloadChord);
    chorddis_player2.doOneSlidingStep(preloadChord);
    chorddis_player3.doOneSlidingStep(preloadChord);
    chorddis_player4.doOneSlidingStep(preloadChord);
    curIndex++;
}

/** Returns a valid cardence array index */
function getChordIndex(i){
    if (cardence !== undefined) {
        return i % cardence.length;
    } else {
        throw "The cardence is not initialized";
    }
}

/** MIDI interface should use this method to say which key to use.
 It generates a suitable cardence (sequence of chords) which will
 be shown on the chord display and loads the pentatonic image.*/
function useKey(k) {
    // Take a cadence -> I, VI, IV, V (TODO: implement more choices)
    var keyChords = chords[checkForAllowedKey(k)];
    cardence = [keyChords[0], keyChords[4], keyChords[2], keyChords[3]];
    key = k;

    // Load chord images
    var c1, c2, c3; // The three next chords
    c1 = cardence[curIndex];
    c2 = cardence[getChordIndex(curIndex + 1)];
    c3 = cardence[getChordIndex(curIndex + 2)];
    chorddis_player1.loadChords(c1, c2, c3);
    chorddis_player2.loadChords(c1, c2, c3);
    chorddis_player3.loadChords(c1, c2, c3);
    chorddis_player4.loadChords(c1, c2, c3);

    // Load pentatonic image
    pentscreen_player1.loadImage(chords[k][4]); // Change from Major to Minor (e.G. C Major -> A Minor)

}

/** Updates the timer interval fitting to the beat and activates it*/
function useBeat(bpm) {
    var barInterval = bpm / 60; // Beats per second
    barInterval *= 4; // Only call at every beginning of a bar containing four steps
    barInterval *= 1000; // In ms
    slidingTimer.interval = barInterval;
    slidingTimer.running = true;
}
