function createController(s1,s2,s3,s4,circle) {
    return new Controller(s1,s2,s3,s4,circle);
}

var MODUS = {
    READY : 0,
    WARM_UP: 1,
    SESSION: 2
}

var timer = Qt.createComponent("Timer.qml")
function createTimer(options) {
    options = options || {};
    return timer.createObject(null, options);
}

function Controller(s1,s2,s3,s4,circle) {
    this.players = {
        player1: {
            stage: s1,
            isActive: false,
            number: 1
        },
        player2: {
            stage: s2,
            isActive: false,
            number: 2
        },
        player3: {
            stage: s3,
            isActive: false,
            number: 3
        },
        player4: {
            stage: s4,
            isActive: false,
            number: 4
        }
    };

    this.activePlayerCount = 0;
    var _this = this;
    this.players.player1.stage.activated.connect(function() {_this.activate("player1")});
    this.players.player1.stage.deactivated.connect(function() {_this.deactivate("player1")});

    this.players.player2.stage.activated.connect(function() {_this.activate("player2")});
    this.players.player2.stage.deactivated.connect(function() {_this.deactivate("player2")});

    this.players.player3.stage.activated.connect(function() {_this.activate("player3")});
    this.players.player3.stage.deactivated.connect(function() {_this.deactivate("player3")});

    this.players.player4.stage.activated.connect(function() {_this.activate("player4")});
    this.players.player4.stage.deactivated.connect(function() {_this.deactivate("player4")});

    this.circle = circle;

    this.state = MODUS.READY;
}

Controller.prototype.changed = function() {
    switch (this.state) {
        case MODUS.READY:
            if (this.activePlayerCount >= 2) {
                this.state = MODUS.WARM_UP;
                this.startWarmUp();
            }
            break;
        case MODUS.WARM_UP:
            break;
        case MODUS.SESSION:
            if (this.activePlayerCount <= 0) {
                this.state = MODUS.READY;
            }
            break;
    }
}

Controller.prototype.startWarmUp = function() {
    var activePlayers, soloPlayer, hasNextPlayer;
    var _this = this;

    function endWarmUp() {
        _this.circle.disableSpinner();
        _this.circle.rotationStopped.disconnect(rotateToNextPlayer);
        _this.wait(1000, _this.startSession);
    }

    function rotateToNextPlayer() {
        var lastPlayer = soloPlayer;
        soloPlayer = getNextPlayer();
        if (hasNextPlayer) {
            circle.rotateFromToPlayer(lastPlayer.number, soloPlayer.number);
        } else {
            endWarmUp();
        }
    }

    function getNextPlayer() {
        if (activePlayers.length <= 0) {
            hasNextPlayer = false;
            return;
        }

        var nextPlayer = activePlayers.shift();
        // maybe someone paused meanwhile
        while (!nextPlayer.isActive) {
            if (activePlayers.length <= 0) {
                hasNextPlayer = false;
                return;
            }
            nextPlayer = activePlayers.shift();
        }
        hasNextPlayer = true;
        return nextPlayer;
    }

    activePlayers = this.getActivePlayers();
    this.circle.enableSpinner();
    soloPlayer = activePlayers.shift();
    this.circle.rotateToPlayer(soloPlayer.number);
    this.circle.rotationStopped.connect(rotateToNextPlayer);
}

Controller.prototype.startSession = function() {
    var _this = this;

    function getRandomPlayerOf(players) {
      var playerCount = players.length;
      var playerNum = Math.floor(Math.random() * playerCount);
      return players[playerNum];
    }

    function getRandomTime() {
      return Math.floor(Math.random() * 5000) + 1000;
    }

    function startSoloAfterRandomTime() {
        _this.circle.disableSpinner();
        _this.wait(getRandomTime(), startSolo);
    }

    function endSession() {
        _this.state = MODUS.READY;
        _this.circle.spinningStopped.disconnect(startSoloAfterRandomTime);
    }

    function startSolo() {
        if (_this.state === MODUS.SESSION) {
            var soloPlayer = getRandomPlayerOf(_this.getActivePlayers());
            _this.circle.enableSpinner();
            _this.circle.spinToPlayer(soloPlayer.number);
            _this.circle.spinningStopped.connect(startSoloAfterRandomTime);
        } else {
            endSession();
        }
    }

    this.state = MODUS.SESSION;
    this.wait(1000, startSolo);
}

Controller.prototype.wait = function(time, cb) {
    var timer = createTimer({interval: time});
    timer.triggered.connect(cb);
    timer.start();
}

Controller.prototype.getActivePlayers = function() {
    var activePlayers = [];
    for (var player in this.players) {
        player = this.players[player];
        if( player.isActive) {
            activePlayers.push(player);
        }
    }
    return activePlayers;
}

Controller.prototype.activate = function(player) {
    this.players[player].isActive = true;
    this.activePlayerCount++;
    this.changed();
}

Controller.prototype.deactivate = function(player) {
    this.players[player].isActive = false;
    this.activePlayerCount--;
    this.changed();
}


