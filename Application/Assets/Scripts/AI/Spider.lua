--Local variables
local wanderDirection;
local movementSpeed;
local rotationSpeed;
local fleeDistance;
local agroDistance;
local maxFollowDistance;
local attackDistance;
local fowardMovement;
local rightMovement;
local rotation;

--C++ variables
local _state;
local _targetDistance;
local _targetRotation;
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
--Returns: state, fowardMovement, rightMovement, rotation(left/right), wanderDirection
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

    return _state, fowardMovement, rightMovement, rotation, _wanderDirection, _movementSpeed, _rotationSpeed, _fleeDistance, _agroDistance, _maxFollowDistance, _attackDistance;
end

function Idle()
    
end

function Wander()
    
end

function Seek()
    
end

function Fight()
    
end

function Flee()
    
end