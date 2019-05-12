--Objects can be added with the formats:
--Create("assetType", posX, posY, posZ)
--Create("assetType", posX, posY, posZ, rotX, rotY, rotZ)
--Create("assetType", posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ);
--Using -9999 in the posX or posZ position will set posX or posZ to the center of the terrain
--Using -9999 in the posY position will set posY to Terrain::GetHeightat(posX, posZ)


--Player must always be created before any objects with AI
Create("Player", 3428, -9999, 3341, 0, 50, 0);

waterScaleX, waterScaleY, waterScaleZ = 30000, 30000, 1;
Create("Water", -9999, 600, -9999, -90, 0, 0, waterScaleX, waterScaleY, waterScaleZ);

--Create all npcs and props
Create("Pumpkin", 7680, -9999, 8263.64)
Create("Pumpkin", 9023.74, -9999, 9264.36)
Create("Pumpkin", 9424.54, -9999, 8964.33)
Create("Pumpkin", 10271.8, -9999, 11173.3)
Create("Pumpkin", 10656.3, -9999, 11422)
Create("Pumpkin", 9600.79, -9999, 12123)
Create("Pumpkin", 8003.37, -9999, 11650.9)
Create("Pumpkin", 7840.98, -9999, 11508.5)
Create("Pumpkin", 7724.09, -9999, 11317.3)
Create("Pumpkin", 7665.9, -9999, 11188.6)
Create("Pumpkin", 5095.02, -9999, 11732.3)
Create("Pumpkin", 3654.85, -9999, 11468)
Create("Pumpkin", 3444.22, -9999, 11672.9)
Create("Pumpkin", 3294.96, -9999, 11510.3)
Create("Pumpkin", 3019.77, -9999, 11467.6)
Create("Pumpkin", 2873.84, -9999, 11221)
Create("Pumpkin", 2757.98, -9999, 10940.5)
Create("Pumpkin", 2580.36, -9999, 9354.46)
Create("Pumpkin", 2504.41, -9999, 9045.26)
Create("Pumpkin", 2455.44, -9999, 8902.79)
Create("Pumpkin", 1768.44, -9999, 7917.85)
Create("Pumpkin", 1808.27, -9999, 7694.72)
Create("Pumpkin", 1862.67, -9999, 7471.78)
Create("Pumpkin", 1915.36, -9999, 7284.34)
Create("Pumpkin", 1966.37, -9999, 7045.32)
Create("Pumpkin", 8802.5, -9999, 5209.56)
Create("Pumpkin", 8948.95, -9999, 5257.05)
Create("Pumpkin", 9087.69, -9999, 5302.04)
Create("Pumpkin", 9046.55, -9999, 5428.93)
Create("Pumpkin", 8938.7, -9999, 5393.95)
Create("Pumpkin", 8881.66, -9999, 5375.46)

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

--Crates next to ship
--right row
Create("Crate", 2800, -9999, 6060);
Create("Crate", 2800, -9999, 6000);
Create("Crate", 2800, -9999, 5940);
Create("Crate", 2800, -9999, 5880);
Create("Crate", 2800, -9999, 5820);
Create("Crate", 2800, -9999, 5760);
--left row
Create("Crate", 2860, -9999, 6060);
Create("Crate", 2860, -9999, 6000);
Create("Crate", 2860, -9999, 5940);
Create("Crate", 2860, -9999, 5880);
Create("Crate", 2860, -9999, 5820);
Create("Crate", 2860, -9999, 5760);

Create("Ship", 2470, -9999, 5971);

Create("Cabin", 4690, -9999, 3600, -90, 180, 0);
Create("Barrel", 4480, -9999, 3851);
Create("Barrel", 4540, -9999, 3851);
Create("Barrel", 4505, -9999, 3900);

Create("Cabin", 2771, -9999, 2272, -90, 300, 0);
Create("Cabin", 2895, -9999, 3954, -90, 300, 0); --Rotation issue, should be 264

Create("Hive", 4800, -9999, 7600);
Create("Hive", 8200, -9999, 6500);
Create("Hive", 13510, -9999, 7626);
Create("Hive", 2721, -9999, 13133);
Create("Hive", 6808, -9999, 10868);
Create("Hive", 10344, -9999, 10293);

Create("Tree", 9100, -9999, 8000);
Create("Tree", 10500, -9999, 5500);
Create("Tree", 8760, -9999, 4600);
Create("Tree", 8000, -9999, 4350);
Create("Tree", 8975, -9999, 9100);
Create("Tree", 9334.88, -9999, 5430.89);
Create("Tree", 8631.7, -9999, 5523.17);
Create("Tree", 8482.53, -9999, 4968.06);
