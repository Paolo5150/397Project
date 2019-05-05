--Objects can be added with the formats:
--CreateObject("assetType", posX, posY, posZ, scaleX, scaleY, scaleZ)
--CreateObject("assetType", posX, posY, posZ, scaleX, scaleY, scaleZ, rotX, rotY, rotZ);


prop_crates = 20; --These will be removed once all prefabs are in, they are currently still needed
prop_barrels = 20;
npc_pumpkins = 20;

camScale = 1;
CreateObject("MainCamera", 0, 35, 0, camScale, camScale, camScale, 30, 180, 0);
camRotX, camRotY, camRotZ = 30, 180, 0;

waterScaleX, waterScaleY, waterScaleZ = 2000, 2000, 1;
CreateAsset("Water", "Water", 0, 100, 0, waterScaleX, waterScaleY, waterScaleZ);

--Create all npcs and props
pumpkinScale = 20;
CreateObject("Pumpkin", 2234, 0, 1833, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 255, 0, 1007, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 1043, 0, 2660, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 1558, 0, 2772, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 1628, 0, 1189, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 580, 0, 2778, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 277, 0, 2515, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 1330, 0, 2158, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 276, 0, 1642, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 270, 0, 359, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 2125, 0, 1724, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 2320, 0, 2302, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 277, 0, 1477, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 118, 0, 427, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 1589, 0, 2115, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 360, 0, 2176, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 2617, 0, 1129, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 242, 0, 2715, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 209, 0, 774, pumpkinScale, pumpkinScale, pumpkinScale);
CreateObject("Pumpkin", 219, 0, 874, pumpkinScale, pumpkinScale, pumpkinScale);

barrelScale = 20;
CreateObject("Barrel", 1116, 0, 1327, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 1289, 0, 1066, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 1325, 0, 1826, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 253, 0, 237, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 649, 0, 1589, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 731, 0, 2747, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 1194, 0, 1025, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 43, 0, 672, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 1363, 0, 1678, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 955, 0, 2148, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 608, 0, 2287, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 101, 0, 803, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 110, 0, 792, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 717, 0, 1703, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 231, 0, 928, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 1590, 0, 1331, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 199, 0, 501, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 79, 0, 919, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 1202, 0, 1652, barrelScale, barrelScale, barrelScale);
CreateObject("Barrel", 1431, 0, 1566, barrelScale, barrelScale, barrelScale);

crateScale = 1;
CreateObject("Crate", 1633, 0, 1555, crateScale, crateScale, crateScale);
CreateObject("Crate", 220, 0, 1613, crateScale, crateScale, crateScale);
CreateObject("Crate", 220, 0, 2470, crateScale, crateScale, crateScale);
CreateObject("Crate", 2290, 0, 622, crateScale, crateScale, crateScale);
CreateObject("Crate", 681, 0, 2505, crateScale, crateScale, crateScale);
CreateObject("Crate", 1626, 0, 1778, crateScale, crateScale, crateScale);
CreateObject("Crate", 831, 0, 2193, crateScale, crateScale, crateScale);
CreateObject("Crate", 1240, 0, 1871, crateScale, crateScale, crateScale);
CreateObject("Crate", 1359, 0, 962, crateScale, crateScale, crateScale);
CreateObject("Crate", 1085, 0, 1347, crateScale, crateScale, crateScale);
CreateObject("Crate", 2401, 0, 217, crateScale, crateScale, crateScale);
CreateObject("Crate", 771, 0, 1333, crateScale, crateScale, crateScale);
CreateObject("Crate", 1411, 0, 1539, crateScale, crateScale, crateScale);
CreateObject("Crate", 1818, 0, 2552, crateScale, crateScale, crateScale);
CreateObject("Crate", 2794, 0, 524, crateScale, crateScale, crateScale);
CreateObject("Crate", 1706, 0, 1023, crateScale, crateScale, crateScale);
CreateObject("Crate", 1217, 0, 2102, crateScale, crateScale, crateScale);
CreateObject("Crate", 804, 0, 1014, crateScale, crateScale, crateScale);
CreateObject("Crate", 1135, 0, 275, crateScale, crateScale, crateScale);
CreateObject("Crate", 1708, 0, 1886, crateScale, crateScale, crateScale);

spiderScale = 1;
CreateObject("Spider", 4000, 0, 4000, spiderScale, spiderScale, spiderScale);

gunScale = 0.8;
CreateAsset("Model", "Gun", 1637, 16, 1555, gunScale, gunScale, gunScale, 0, 90, 0); --Same x and z location as crate 1, y = 16 is to lay the gun on a crate

shipScale = 20;
CreateAsset("Model", "Ship", 1545, 0, 1414, shipScale, shipScale, shipScale);

cabinScale = 100;
CreateObject("Cabin", 300, 50, 1200, cabinScale, cabinScale, cabinScale, -90, 0, 0);