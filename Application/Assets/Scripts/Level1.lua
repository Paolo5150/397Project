--Objects can be added with the formats:
--Create("assetType", posX, posY, posZ)
--Create("assetType", posX, posY, posZ, rotX, rotY, rotZ)
--Create("assetType", posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ);
--Using -9999 in the posX or posZ position will set posX or posZ to the center of the terrain
--Using -9999 in the posY position will set posY to Terrain::GetHeightat(posX, posZ)


--Player must always be created before any objects with AI
Create("Player", 3428, -9999, 3341, 0, 50, 0);

waterScaleX, waterScaleY, waterScaleZ = 10000, 10000, 1;
Create("Water", -9999, 750, -9999, -90, 0, 0, waterScaleX, waterScaleY, waterScaleZ);

--Create all npcs and props
--[[Create("Pumpkin", 7680, -9999, 8263.64)
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

--Farm-ish area
Create("PumpkinBunch", 9000, -9999, 5200)
Create("PumpkinBunch", 8800, -9999, 5200)
Create("PumpkinBunch", 8600, -9999, 5200)
Create("PumpkinBunch", 9000, -9999, 5400)
Create("PumpkinBunch", 8800, -9999, 5400)
Create("PumpkinBunch", 8600, -9999, 5400)
--Create("Pumpkin", 8802.5, -9999, 5209.56)
--Create("Pumpkin", 8948.95, -9999, 5257.05)
--Create("Pumpkin", 9087.69, -9999, 5302.04)
--Create("Pumpkin", 9046.55, -9999, 5428.93)
--Create("Pumpkin", 8938.7, -9999, 5393.95)
--Create("Pumpkin", 8881.66, -9999, 5375.46)

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

Create("Cabin", 4690, -9999, 3600, 0, 180, 0);
Create("Barrel", 4480, -9999, 3782);
Create("Barrel", 4540, -9999, 3782);
Create("Barrel", 4505, -9999, 3831);
Create("PumpkinBunch", 4470, -9999, 3370);
Create("PumpkinBunch", 4730, -9999, 3370);

Create("Cabin", 2771, -9999, 2272, 0, 300, 0);
Create("Cabin", 2895, -9999, 3954, 0, 20, 0);]]--

Create("Hive", 4800, -9999, 7600);
Create("Hive", 8200, -9999, 6500);
Create("Hive", 13510, -9999, 7626);
Create("Hive", 2721, -9999, 13133);
Create("Hive", 6808, -9999, 10868);
Create("Hive", 10344, -9999, 10293);

--[[Create("Tree", 9100, -9999, 8000);
Create("Tree", 10500, -9999, 5500);
Create("Tree", 8760, -9999, 4600);
Create("Tree", 8000, -9999, 4350);
Create("Tree", 8975, -9999, 9100);

--Farm-ish area
Create("Tree", 9334.88, -9999, 5430.89);
Create("Tree", 8631.7, -9999, 5523.17);
Create("Tree", 8482.53, -9999, 4968.06);]]--

--Trees around cabins
--Create("Tree", 4805, -9999, 3032);
--Create("Tree", 4426, -9999, 4362);
--Create("Tree", 3947, -9999, 4795);
--Create("Tree", 3320, -9999, 4782);
--Create("Tree", 2187, -9999, 3924);
--Create("Tree", 2170, -9999, 3340);
--Create("Tree", 2268, -9999, 2652);
