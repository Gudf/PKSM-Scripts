#include <pksm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

union FeebasSeed {
    unsigned long seed;
    unsigned char part[4];
};

int main(int argc, char **argv) {
    unsigned char *saveData = (unsigned char *)atoi(argv[0]);
    unsigned char version = *argv[2];
    union FeebasSeed feebasSeed;
    unsigned int sday = *(unsigned char*)(saveData + 0x1C), 
        smon = *(unsigned char*)(saveData + 0x18),
        syear = (*(unsigned char*)(saveData + 0x14)) + 2000;
    int xpos[4], ypos[4];
    int spot[] = {
        585, 586, 587, 588, 589, 590, 591, 592, 593, 594,
        595, 596, 597, 598, 599, 600, 601, 602, 617, 618, 619, 620, 621, 622,
        623, 624, 625, 626, 627, 628, 629, 630, 631, 632, 633, 634, 649, 650,
        651, 652, 653, 654, 655, 656, 657, 658, 659, 660, 661, 662, 663, 665,
        666, 681, 682, 683, 685, 686, 687, 688, 689, 690, 691, 692, 693, 694,
        695, 696, 697, 698, 713, 714, 715, 716, 717, 718, 719, 720, 721, 722,
        723, 724, 725, 726, 727, 728, 729, 730, 745, 746, 747, 748, 749, 750,
        751, 752, 753, 754, 755, 756, 757, 758, 759, 760, 761, 762, 777, 778,
        779, 780, 781, 782, 783, 784, 785, 786, 787, 788, 789, 790, 791, 792,
        793, 794, 809, 810, 811, 812, 813, 814, 815, 816, 817, 818, 819, 820,
        821, 822, 823, 824, 825, 826, 841, 842, 843, 844, 845, 846, 847, 848,
        849, 850, 851, 852, 853, 854, 855, 856, 857, 858, 873, 874, 875, 876,
        877, 878, 880, 881, 882, 883, 884, 885, 886, 887, 888, 889, 890, 905,
        906, 907, 908, 909, 910, 911, 912, 913, 914, 915, 916, 917, 918, 919,
        920, 921, 922, 937, 938, 939, 940, 941, 942, 943, 944, 952, 953, 954,
        969, 970, 971, 972, 973, 974, 975, 976, 984, 985, 986, 1001, 1002, 1003,
        1004, 1005, 1006, 1007, 1008, 1016, 1017, 1018, 1033, 1034, 1037, 1038,
        1039, 1040, 1048, 1049, 1050, 1065, 1066, 1069, 1070, 1071, 1072, 1080,
        1081, 1082, 1097, 1098, 1099, 1100, 1101, 1102, 1103, 1104, 1112, 1113,
        1114, 1129, 1130, 1131, 1132, 1133, 1134, 1135, 1136, 1144, 1145, 1146,
        1161, 1162, 1163, 1164, 1165, 1166, 1167, 1168, 1169, 1170, 1171, 1172,
        1175, 1176, 1177, 1178, 1193, 1194, 1195, 1196, 1197, 1198, 1199, 1200,
        1201, 1202, 1203, 1204, 1207, 1208, 1209, 1210, 1225, 1226, 1227, 1228,
        1229, 1230, 1231, 1232, 1233, 1234, 1235, 1236, 1237, 1238, 1239, 1240,
        1241, 1242, 1257, 1258, 1259, 1260, 1261, 1262, 1263, 1264, 1265, 1266,
        1267, 1268, 1269, 1270, 1271, 1272, 1273, 1274, 1289, 1290, 1291, 1292,
        1293, 1294, 1295, 1296, 1297, 1298, 1299, 1300, 1301, 1305, 1306, 1321,
        1322, 1323, 1324, 1325, 1326, 1327, 1328, 1329, 1330, 1331, 1332, 1333,
        1337, 1338, 1353, 1354, 1355, 1356, 1357, 1358, 1359, 1360, 1361, 1362,
        1363, 1364, 1365, 1369, 1370, 1385, 1386, 1387, 1388, 1389, 1390, 1391,
        1392, 1393, 1394, 1395, 1396, 1397, 1398, 1399, 1400, 1401, 1402, 1417,
        1418, 1419, 1420, 1421, 1422, 1423, 1424, 1425, 1426, 1428, 1429, 1430,
        1431, 1432, 1433, 1434, 1449, 1450, 1451, 1455, 1456, 1457, 1458, 1459,
        1460, 1461, 1462, 1463, 1464, 1465, 1466, 1481, 1482, 1483, 1487, 1488,
        1489, 1490, 1491, 1492, 1493, 1494, 1495, 1496, 1497, 1498, 1513, 1514,
        1515, 1519, 1520, 1521, 1522, 1523, 1524, 1527, 1528, 1529, 1530, 1545,
        1546, 1547, 1548, 1549, 1550, 1551, 1552, 1553, 1554, 1555, 1556, 1559,
        1560, 1561, 1562, 1577, 1578, 1580, 1581, 1582, 1583, 1584, 1585, 1586,
        1587, 1588, 1589, 1590, 1591, 1592, 1593, 1594, 1609, 1610, 1611, 1612,
        1613, 1614, 1615, 1616, 1617, 1618, 1619, 1620, 1621, 1622, 1623, 1624,
        1625, 1626, 1641, 1642, 1643, 1644, 1645, 1646, 1647, 1648, 1649, 1650,
        1651, 1652, 1653, 1654, 1655, 1656, 1657, 1658
    };
		
    switch (version)
    {
        case 10:
        case 11:
            feebasSeed.seed = *(unsigned long*)(saveData + 0x53C8);
            break;
        case 12:
            feebasSeed.seed = *(unsigned long*)(saveData + 0x5664);
            break;
        default:
            gui_warn("This script is only meant for", "the Sinnoh games (DPPt)");
            return 1;
    }

    for (int i = 0; i < 4; i++)
    {
        xpos[i] = (spot[(feebasSeed.part[3 - i] % 132) + (132 * i)] & 31) - 8;
        ypos[i] = (((spot[(feebasSeed.part[3 - i] % 132) + (132 * i)] & (~31)) - 576) / 32) + 1;
    }
    
    char msg[50] = {'\0'};
    sprintf(&msg, "Your Feebas Tiles for %u/%u/%u (DD/MM/YYYY)", sday, smon, syear);
    gui_warn(msg, "(the day you last saved) are, as follows...");
    char first[60] = {'\0'};
    char second[60] = {'\0'};
    sprintf(&first, "Row #%i from the top, Column #%i from the left", ypos[0], xpos[0]);
    sprintf(&second, "Row #%i from the top, Column #%i from the left", ypos[1], xpos[1]);
    gui_warn(first, second);
    sprintf(&first, "Row #%i from the top, Column #%i from the left", ypos[2], xpos[2]);
    sprintf(&second, "Row #%i from the top, Column #%i from the left", ypos[3], xpos[3]);
    gui_warn(first, second);
    return 0;
}