math.randomseed(os.time());

--Local variables
local movementSpeed;
local rotationSpeed;
local fleeDistance;
local agroDistance;
local maxFollowDistance;
local attackDistance;
local fowardMovement;
local rightMovement;
local rotation;
local animation;

--C++ variables
local _state;
local _targetDistance;
local _targetRotation;
local _wanderDirection;
local _timerDeltaS;
local _lastStateChange;
local _randomTimer;

function PopulateVariables(state, targetDistance, targetRotation, timerCurrentTime, timerDeltaS, lastStateChange, randomTimer)
    _state = state;
    _targetDistance = targetDistance;
    _targetRotation = targetRotation;
    _timerDeltaS = timerDeltaS;
    _lastStateChange = lastStateChange;
    _randomTimer = randomTimer;
end

--Entry function
--Returns: state, animation, fowardMovement, rightMovement, rotation(left/right), wanderDirection
function Think(state, targetDistance, targetRotation, timerCurrentTime, timerDeltaS, lastStateChange, randomTimer)
    PopulateVariables(state, targetDistance, targetRotation, timerCurrentTime, timerDeltaS, lastStateChange, randomTimer);
    
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
    end

    return _state, animation, fowardMovement, rightMovement, rotation, _wanderDirection;
end

function Idle()
    animation = 14;

    if(timerCurrentTime - _randomTimer > 0.5 and timerCurrentTime - _lastStateChange > 5.0) then
        _randomTimer = timerCurrentTime;

        if(math.random(1, 100) < 10) then
            _state = "Wander";
        end
    end

    if(targetDistance <= _agroDistance) then
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

    rotation = _wanderDirection * rotationSpeed * _timerDeltaS;
    fowardMovement = movementSpeed * _timerDeltaS;
    _wanderDirection = _wanderDirection - _wanderDirection * rotationSpeed * _timerDeltaS;

    if(timerCurrentTime - _randomTimer > 0.5 and timerCurrentTime - _lastStateChange > 5.0) then
        _randomTimer = timerCurrentTime;

        if(math.random(1, 100) < 10) then
            _state = "Idle";
        end
    end

    if(targetDistance <= _agroDistance) then
        _state = "Seek"
    end
end

function Seek()
    animation = 7;
end

function Fight()
    animation = 0;
end

function Flee()
    animation = 7;
end