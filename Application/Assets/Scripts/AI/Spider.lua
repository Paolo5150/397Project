--Script variables
movementSpeed = 100;
rotationSpeed = 1;
fleeDistance = 1000; --Distance the ai will try and get to before stopping fleeing
agroDistance = 500; --Distance the ai will notice and start following the target
maxFollowDistance = 1000; --Distance the ai will stop following the target
attackDistance = 150; --Distance the ai will switch to fighting
fowardMovement = 0;
rightMovement = 0;
rotation = 0;
animation = 0;

--C++ variables
_state = "";
_targetDistance = 0;
_targetRotation = 0;
_targetRotationReverse = 0;
_wanderDirection = 0;
_timerCurrentTime = 0;
_timerDeltaS = 0;
_lastStateChange = 0;
_randomTimer = 0;

function PopulateVariables(state, targetDistance, targetRotation, targetRotationReverse, timerCurrentTime, timerDeltaS, lastStateChange, randomTimer)
    _state = state;
    _targetDistance = targetDistance;
    _targetRotation = targetRotation;
    _targetRotationReverse = targetRotationReverse;
    _timerCurrentTime = timerCurrentTime;
    _timerDeltaS = timerDeltaS;
    _lastStateChange = lastStateChange;
    _randomTimer = randomTimer;
end

--Entry function
--Returns: state, animation, fowardMovement, rightMovement, rotation(left/right), wanderDirection
function Think(state, targetDistance, targetRotation, targetRotationReverse, timerCurrentTime, timerDeltaS, lastStateChange, randomTimer)
    PopulateVariables(state, targetDistance, targetRotation, targetRotationReverse, timerCurrentTime, timerDeltaS, lastStateChange, randomTimer);
    
    if(_state == "Idle") then
        Idle();
    elseif(_state == "Wander") then
        Wander();
    elseif(_state == "Seek") then
        Seek();
    elseif(_state == "Fight") then
        Fight();
    elseif(_state == "Flee") then
        Flee();
    elseif(_state == "") then
        _state = "Idle";
        Idle();
    end

    return _state, animation, fowardMovement, rightMovement, rotation, _wanderDirection;
end

function Idle()
    animation = 14;

    rotation = 0;
    fowardMovement = 0;
    rightMovement = 0;

    if(_timerCurrentTime - _randomTimer > 0.5 and _timerCurrentTime - _lastStateChange > 5.0) then
        _randomTimer = _timerCurrentTime;

        print(math.random(1, 100))

        if(math.random(1, 100) < 10) then
            _state = "Wander";
        end
    end

    if(_targetDistance <= agroDistance) then
        _state = "Seek";
    end
end

function Wander()
    animation = 7;

    if(_wanderDirection > -2 and _wanderDirection < 2) then
        if(math.random(1,100) <= 10) then
            _wanderDirection = _wanderDirection + math.random() + math.random(-90, 0);
        elseif(math.random(1,100) >= 90) then
            _wanderDirection = _wanderDirection + math.random() + math.random(0, 90);
        end
    end

    rotation = -(_wanderDirection * rotationSpeed * _timerDeltaS);
    fowardMovement = -(movementSpeed * _timerDeltaS);
    rightMovement = 0;
    _wanderDirection = _wanderDirection - _wanderDirection * rotationSpeed * _timerDeltaS;

    if(_timerCurrentTime - _randomTimer > 0.5 and _timerCurrentTime - _lastStateChange > 5.0) then
        _randomTimer = _timerCurrentTime;

        if(math.random(1, 100) < 10) then
            _state = "Idle";
        end
    end

    if(_targetDistance <= agroDistance) then
        _state = "Seek";
    end
end

function Seek()
    animation = 7;

    rotation = _targetRotationReverse * rotationSpeed * _timerDeltaS;
    _wanderDirection = rotation;
    fowardMovement = -(movementSpeed * _timerDeltaS);
    rightMovement = 0;

    if(_targetDistance >= maxFollowDistance) then
        _state = "Wander";
    end

    if(_targetDistance <= attackDistance) then
        _state = "Fight";
    end
end

function Fight()
    animation = 0;

    rotation = _targetRotationReverse * rotationSpeed * _timerDeltaS;
    fowardMovement = 0;
    rightMovement = 0;

    if(_targetDistance > attackDistance) then
        _state = "Seek";
    end
end

function Flee()
    animation = 7;
end