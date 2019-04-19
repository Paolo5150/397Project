allColliders = false; --lua colliders currently (possibly) broken, don't set to true

CreateAsset("MainCamera");
camX, camY, camZ = 0, 35, 0;
camRotX, camRotY, camRotZ = 0, 0, 0;
camCollider = allColliders;
camColliderX, camColliderY, camColliderZ = 0, 0, 0;
camColliderScale = 20;

CreateAsset("Water");
waterX, waterY, waterZ = 0, 100, 0;
waterScaleX, waterScaleY, waterScaleZ = 2000, 2000, 1;


--Create all npcs and props

npc_nanosuits = 2;
npc_pumpkins = 10;
prop_barrels = 10;
prop_crates = 10;

totalAssets = (2 + npc_nanosuits + npc_pumpkins + prop_barrels + prop_crates + 3); -- 2 extra objects before the for loops, 3 after

for i = 0, npc_nanosuits-1, 1
do
    CreateAsset("Model", "Nanosuit");
end
    nanosuitScale = 2;
    nanosuitCollider = allColliders;
    nanosuitColliderScale = 1;

for i = 0, npc_pumpkins-1, 1
do
    CreateAsset("Model", "Pumpkin");
end
    pumpkinScale = 20;
    pumpkinCollider = allColliders;
    pumpkinColliderScale = 1;

for i = 0, prop_barrels-1, 1
do
    CreateAsset("Model", "Barrel");
end
    barrelScale = 20;
    barrelCollider = allColliders;
    barrelColliderScale = 1;

for i = 0, prop_crates-1, 1
do
    CreateAsset("Model", "Crate");
end
    crateScale = 1;
    crateCollider = allColliders;
    crateColliderScale = 20;

CreateAsset("Model", "Gun");
gunX, gunY, gunZ = 1637, 16, 1555; --Same x and z location as crate 1, y = 16 is to lay the gun on a crate
gunScale = 0.8;
gunCollider = allColliders;
gunColliderX, gunColliderY, gunColliderZ = 0, 0, 0;
gunColliderScale = 1;

CreateAsset("Model", "Ship");
shipX, shipY, shipZ = 1545, 0, 1414;
shipScale = 20;
shipCollider = allColliders;
shipColliderX, shipColliderY, shipColliderZ = 0, 5, 0;
shipColliderScale = 20;

CreateAsset("Model", "Cabin");
cabinX, cabinY, cabinZ = 300, 50, 1200;
cabinScale = 100;
cabinCollider = allColliders;
cabinColliderX, cabinColliderY, cabinColliderZ = 0, 0, 0;
cabinColliderScale = 1;

   nanosuitColliderX, nanosuitColliderY, nanosuitColliderZ = 0, 0, 0;
   nanosuit1X, nanosuit1Y, nanosuit1Z = 1900, 0, 1900;
   nanosuit2X, nanosuit2Y, nanosuit2Z = 1700, 0, 2300;

   pumpkinColliderX, pumpkinColliderY, pumpkinColliderZ = 0, 0, 0;
   pumpkin1X, pumpkin1Y, pumpkin1Z = 2234, 0, 1833;
   pumpkin2X, pumpkin2Y, pumpkin2Z = 255, 0, 1007;
   pumpkin3X, pumpkin3Y, pumpkin3Z = 1043, 0, 2660;
   pumpkin4X, pumpkin4Y, pumpkin4Z = 1558, 0, 2772;
   pumpkin5X, pumpkin5Y, pumpkin5Z = 1628, 0, 1189;
   pumpkin6X, pumpkin6Y, pumpkin6Z = 580, 0, 2778;
   pumpkin7X, pumpkin7Y, pumpkin7Z = 277, 0, 2515;
   pumpkin8X, pumpkin8Y, pumpkin8Z = 1330, 0, 2158;
   pumpkin9X, pumpkin9Y, pumpkin9Z = 276, 0, 1642;
pumpkin10X, pumpkin10Y, pumpkin10Z = 270, 0, 359;
pumpkin11X, pumpkin11Y, pumpkin11Z = 2125, 0, 1724;
pumpkin12X, pumpkin12Y, pumpkin12Z = 2320, 0, 2302;
pumpkin13X, pumpkin13Y, pumpkin13Z = 277, 0, 1477;
pumpkin14X, pumpkin14Y, pumpkin14Z = 118, 0, 427;
pumpkin15X, pumpkin15Y, pumpkin15Z = 1589, 0, 2115;
pumpkin16X, pumpkin16Y, pumpkin16Z = 360, 0, 2176;
pumpkin17X, pumpkin17Y, pumpkin17Z = 2617, 0, 1129;
pumpkin18X, pumpkin18Y, pumpkin18Z = 242, 0, 2715;
pumpkin19X, pumpkin19Y, pumpkin19Z = 209, 0, 774;
pumpkin20X, pumpkin20Y, pumpkin20Z = 219, 0, 874;

   barrelColliderX, barrelColliderY, barrelColliderZ = 0, 1, 0;
   barrel1X, barrel1Y, barrel1Z = 1116, 0, 1327;
   barrel2X, barrel2Y, barrel2Z = 1289, 0, 1066;
   barrel3X, barrel3Y, barrel3Z = 1325, 0, 1826;
   barrel4X, barrel4Y, barrel4Z = 253, 0, 237;
   barrel5X, barrel5Y, barrel5Z = 649, 0, 1589;
   barrel6X, barrel6Y, barrel6Z = 731, 0, 2747;
   barrel7X, barrel7Y, barrel7Z = 1194, 0, 1025;
   barrel8X, barrel8Y, barrel8Z = 43, 0, 672;
   barrel9X, barrel9Y, barrel9Z = 1363, 0, 1678;
barrel10X, barrel10Y, barrel10Z = 955, 0, 2148;
barrel11X, barrel11Y, barrel11Z = 608, 0, 2287;
barrel12X, barrel12Y, barrel12Z = 101, 0, 803;
barrel13X, barrel13Y, barrel13Z = 110, 0, 792;
barrel14X, barrel14Y, barrel14Z = 717, 0, 1703;
barrel15X, barrel15Y, barrel15Z = 231, 0, 928;
barrel16X, barrel16Y, barrel16Z = 1590, 0, 1331;
barrel17X, barrel17Y, barrel17Z = 199, 0, 501;
barrel18X, barrel18Y, barrel18Z = 79, 0, 919;
barrel19X, barrel19Y, barrel19Z = 1202, 0, 1652;
barrel20X, barrel20Y, barrel20Z = 1431, 0, 1566;

   crateColliderX, crateColliderY, crateColliderZ = 0, 1, 0;
   crate1X, crate1Y, crate1Z = 1633, 0, 1555;
   crate2X, crate2Y, crate2Z = 220, 0, 1613;
   crate3X, crate3Y, crate3Z = 220, 0, 2470;
   crate4X, crate4Y, crate4Z = 2290, 0, 622;
   crate5X, crate5Y, crate5Z = 681, 0, 2505;
   crate6X, crate6Y, crate6Z = 1626, 0, 1778;
   crate7X, crate7Y, crate7Z = 831, 0, 2193;
   crate8X, crate8Y, crate8Z = 1240, 0, 1871;
   crate9X, crate9Y, crate9Z = 1359, 0, 962;
crate10X, crate10Y, crate10Z = 1085, 0, 1347;
crate11X, crate11Y, crate11Z = 2401, 0, 217;
crate12X, crate12Y, crate12Z = 771, 0, 1333;
crate13X, crate13Y, crate13Z = 1411, 0, 1539;
crate14X, crate14Y, crate14Z = 1818, 0, 2552;
crate15X, crate15Y, crate15Z = 2794, 0, 524;
crate16X, crate16Y, crate16Z = 1706, 0, 1023;
crate17X, crate17Y, crate17Z = 1217, 0, 2102;
crate18X, crate18Y, crate18Z = 804, 0, 1014;
crate19X, crate19Y, crate19Z = 1135, 0, 275;
crate20X, crate20Y, crate20Z = 1708, 0, 1886;