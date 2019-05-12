--Objects can be added with the formats:
--Create("assetType", posX, posY, posZ)
--Create("assetType", posX, posY, posZ, rotX, rotY, rotZ)
--Create("assetType", posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ);
--Using -9999 in the posX or posZ position will set posX or posZ to the center of the terrain
--Using -9999 in the posY position will set posY to Terrain::GetHeightat(posX, posZ)


--Player must always be created before any objects with AI
Create("Player", -9999, -9999, -9999)--, 30, 180, 0);

waterScaleX, waterScaleY, waterScaleZ = 30000, 30000, 1;
Create("Water", -9999, 600, -9999, -90, 0, 0, waterScaleX, waterScaleY, waterScaleZ);

mountainScaleX, mountainScaleY, mountainScaleZ = 25, 25, 25;
--Create("Mountains", -9999, 300, -9999, 0, 0, 0, mountainScaleX, mountainScaleY, mountainScaleZ);

--Create all npcs and props
Create("Pumpkin", 2234, -9999, 1833);
Create("Pumpkin", 255, -9999, 1007);
Create("Pumpkin", 1043, -9999, 2660);
Create("Pumpkin", 1558, -9999, 2772);
Create("Pumpkin", 1628, -9999, 1189);
Create("Pumpkin", 580, -9999, 2778);
Create("Pumpkin", 277, -9999, 2515);
Create("Pumpkin", 1330, -9999, 2158);
Create("Pumpkin", 276, -9999, 1642);
Create("Pumpkin", 270, -9999, 359);
Create("Pumpkin", 2125, -9999, 1724);
Create("Pumpkin", 2320, -9999, 2302);
Create("Pumpkin", 277, -9999, 1477);
Create("Pumpkin", 118, -9999, 427);
Create("Pumpkin", 1589, -9999, 2115);
Create("Pumpkin", 360, -9999, 2176);
Create("Pumpkin", 2617, -9999, 1129);
Create("Pumpkin", 242, -9999, 2715);
Create("Pumpkin", 209, -9999, 774);
Create("Pumpkin", 219, -9999, 874);

Create("Barrel", 1116, -9999, 1327);
Create("Barrel", 1289, -9999, 1066);
Create("Barrel", 1325, -9999, 1826);
Create("Barrel", 253, -9999, 237);
Create("Barrel", 649, -9999, 1589);
Create("Barrel", 731, -9999, 2747);
Create("Barrel", 1194, -9999, 1025);
Create("Barrel", 43, -9999, 672);
Create("Barrel", 1363, -9999, 1678);
Create("Barrel", 955, -9999, 2148);
Create("Barrel", 608, -9999, 2287);
Create("Barrel", 101, -9999, 803);
Create("Barrel", 110, -9999, 792);
Create("Barrel", 717, -9999, 1703);
Create("Barrel", 231, -9999, 928);
Create("Barrel", 1590, -9999, 1431);
Create("Barrel", 199, -9999, 501);
Create("Barrel", 79, -9999, 919);
Create("Barrel", 1202, -9999, 1652);
Create("Barrel", 1431, -9999, 1566);

Create("Crate", 1633, -9999, 1555);
Create("Crate", 220, -9999, 1613);
Create("Crate", 220, -9999, 2470);
Create("Crate", 2290, -9999, 622);
Create("Crate", 681, -9999, 2505);
Create("Crate", 1626, -9999, 1778);
Create("Crate", 831, -9999, 2193);
Create("Crate", 1240, -9999, 1871);
Create("Crate", 1359, -9999, 962);
Create("Crate", 1085, -9999, 1347);
Create("Crate", 2401, -9999, 217);
Create("Crate", 771, -9999, 1333);
Create("Crate", 1411, -9999, 1539);
Create("Crate", 1818, -9999, 2552);
Create("Crate", 2794, -9999, 524);
Create("Crate", 1706, -9999, 1023);
Create("Crate", 1217, -9999, 2102);
Create("Crate", 804, -9999, 1014);
Create("Crate", 1135, -9999, 275);
Create("Crate", 1708, -9999, 1886);

--Create("Spider", 4000, -9999, 4000);

Create("Gun", 1637, -9999, 1605, 0, 0, 0); --Similar x and z location as crate 1

Create("Ship", 7000, -9999, 4250);

Create("Cabin", 6100, -9999, 6000, -90, 180, 0);

Create("Hive", 4800, -9999, 7600, 0, 0, 0, 100, 100, 100);
Create("Hive", 6600, -9999, 3100, 0, 0, 0, 100, 100, 100);
Create("Hive", 8200, -9999, 6500, 0, 0, 0, 100, 100, 100);