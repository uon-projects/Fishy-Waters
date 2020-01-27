#include "Map.h"

Map::Map(void)
{
}

int Map::getObjectType(int type, int x, int y)
{
	//type 1 - 2x2
	//type 2 - 1x1
	//type 3 - bridge
	if(type == 1 && x == 0) {
		return 11;
	} else if(type == 1 && x == 1) {
		return 12;
	} else if(type == 1 && x == 2) {
		return 13;
	} else if(type == 1 && x == 3) {
		return 14;
	} else if(type == 1 && x == 4) {
		return 15;
	} else if(type == 1 && x == 5) {
		return 16;
	} else if(type == 1 && x == 6) {
		return 17;
	} else if(type == 1 && x == 7) {
		return 18;
	} else if(type == 1 && x == 8) {
		return 19;
	} else if(type == 2 && x == 0 && y == 1) {
		return 70;
	} else if(type == 2 && x == 0 && y == 2) {
		return 71;
	} else if(type == 2 && x == 0 && y == 3) {
		return 72;
	} else if(type == 2 && x == 0 && y == 4) {
		return 73;
	} else if(type == 2 && x == 1 && y == 4) {
		return 74;
	} else if(type == 2 && x == 2 && y == 4) {
		return 75;
	} else if(type == 2 && x == 0 && y == 5) {
		return 76;
	} else if(type == 2 && x == 0 && y == 6) {
		return 77;
	} else if(type == 2 && x == 0 && y == 7) {
		return 78;
	} else if(type == 2 && x == 1 && y == 5) {
		return 79;
	} else if(type == 2 && x == 1 && y == 6) {
		return 80;
	} else if(type == 2 && x == 1 && y == 7) {
		return 81;
	} else if(type == 2 && x == 2 && y == 5) {
		return 82;
	} else if(type == 2 && x == 2 && y == 6) {
		return 83;
	} else if(type == 2 && x == 2 && y == 7) {
		return 84;
	} else if(type == 2 && x == 0 && y == 0) {
		return 85;
	} else if(type == 2 && x == 6 && y == 1) {
		return 86;
	} else if(type == 2 && x == 6 && y == 2) {
		return 87;
	} else if(type == 2 && x == 6 && y == 3) {
		return 88;
	} else if(type == 2 && x == 6 && y == 4) {
		return 89;
	} else if(type == 2 && x == 7 && y == 4) {
		return 90;
	} else if(type == 2 && x == 8 && y == 4) {
		return 91;
	} else if(type == 2 && x == 6 && y == 5) {
		return 92;
	} else if(type == 2 && x == 6 && y == 6) {
		return 93;
	} else if(type == 2 && x == 6 && y == 7) {
		return 94;
	} else if(type == 2 && x == 7 && y == 5) {
		return 95;
	} else if(type == 2 && x == 7 && y == 6) {
		return 96;
	} else if(type == 2 && x == 7 && y == 7) {
		return 97;
	} else if(type == 2 && x == 8 && y == 5) {
		return 98;
	} else if(type == 2 && x == 8 && y == 6) {
		return 99;
	} else if(type == 2 && x == 8 && y == 7) {
		return 100;
	} else if(type == 2 && x == 6 && y == 0) {
		return 101;
	} else if(type == 2 && x == 3 && y == 4) {
		return 102;
	} else if(type == 2 && x == 3 && y == 5) {
		return 103;
	} else if(type == 2 && x == 4 && y == 4) {
		return 104;
	} else if(type == 2 && x == 4 && y == 5) {
		return 105;
	} else if(type == 3 && x == 0 && y == 0) {
		return 150;
	} else if(type == 3 && x == 0 && y == 1) {
		return 151;
	} else if(type == 3 && x == 0 && y == 2) {
		return 152;
	} else if(type == 3 && x == 1 && y == 0) {
		return 153;
	} else if(type == 3 && x == 1 && y == 1) {
		return 154;
	} else if(type == 3 && x == 1 && y == 2) {
		return 155;
	}
}

void Map::getObjectByType(int type, int &x, int &y)
{
	if(type == 11) {
		x = 0;
	} else if(type == 12) {
		x = 1;
	} else if(type == 13) {
		x = 2;
	} else if(type == 14) {
		x = 3;
	} else if(type == 15) {
		x = 4;
	} else if(type == 16) {
		x = 5;
	} else if(type == 17) {
		x = 6;
	} else if(type == 18) {
		x = 7;
	} else if(type == 19) {
		x = 8;
	} else if(type == 70) {
		x = 0;
		y = 1;
	} else if(type == 71) {
		x = 0;
		y = 2;
	} else if(type == 72) {
		x = 0;
		y = 3;
	} else if(type == 73) {
		x = 0;
		y = 4;
	} else if(type == 74) {
		x = 1;
		y = 4;
	} else if(type == 75) {
		x = 2;
		y = 4;
	} else if(type == 76) {
		x = 0;
		y = 5;
	} else if(type == 77) {
		x = 0;
		y = 6;
	} else if(type == 78) {
		x = 0;
		y = 7;
	} else if(type == 79) {
		x = 1;
		y = 5;
	} else if(type == 80) {
		x = 1;
		y = 6;
	} else if(type == 81) {
		x = 1;
		y = 7;
	} else if(type == 82) {
		x = 2;
		y = 5;
	} else if(type == 83) {
		x = 2;
		y = 6;
	} else if(type == 84) {
		x = 2;
		y = 7;
	} else if(type == 85) {
		x = 0;
		y = 0;
	} else if(type == 86) {
		x = 6;
		y = 1;
	} else if(type == 87) {
		x = 6;
		y = 2;
	} else if(type == 88) {
		x = 6;
		y = 3;
	} else if(type == 89) {
		x = 6;
		y = 4;
	} else if(type == 90) {
		x = 7;
		y = 4;
	} else if(type == 91) {
		x = 8;
		y = 4;
	} else if(type == 92) {
		x = 6;
		y = 5;
	} else if(type == 93) {
		x = 6;
		y = 6;
	} else if(type == 94) {
		x = 6;
		y = 7;
	} else if(type == 95) {
		x = 7;
		y = 5;
	} else if(type == 96) {
		x = 7;
		y = 6;
	} else if(type == 97) {
		x = 7;
		y = 7;
	} else if(type == 98) {
		x = 8;
		y = 5;
	} else if(type == 99) {
		x = 8;
		y = 6;
	} else if(type == 100) {
		x = 8;
		y = 7;
	} else if(type == 101) {
		x = 6;
		y = 0;
	} else if(type == 102) {
		x = 3;
		y = 4;
	} else if(type == 103) {
		x = 3;
		y = 5;
	} else if(type == 104) {
		x = 4;
		y = 4;
	} else if(type == 105) {
		x = 4;
		y = 5;
	} else if(type == 150) {
		x = 0;
		y = 0;
	} else if(type == 151) {
		x = 0;
		y = 1;
	} else if(type == 152) {
		x = 0;
		y = 2;
	} else if(type == 153) {
		x = 1;
		y = 0;
	} else if(type == 154) {
		x = 1;
		y = 1;
	} else if(type == 155) {
		x = 1;
		y = 2;
	}
}

int Map::getTerrainType(int type, int x, int y)
{
	//type 1 - grass
	//type 2 - mud
	//type 3 - water
	if(type == 1 && x == 43 && y == 6) {
		return 20;
	} else if(type == 1 && x == 12 && y == 1) {
		return 30;
	} else if(type == 1 && x == 12 && y == 2) {
		return 31;
	} else if(type == 1 && x == 12 && y == 3) {
		return 32;
	} else if(type == 1 && x == 12 && y == 4) {
		return 33;
	} else if(type == 1 && x == 13 && y == 4) {
		return 34;
	} else if(type == 1 && x == 14 && y == 4) {
		return 35;
	} else if(type == 1 && x == 12 && y == 5) {
		return 36;
	} else if(type == 1 && x == 12 && y == 6) {
		return 37;
	} else if(type == 1 && x == 12 && y == 7) {
		return 38;
	} else if(type == 1 && x == 13 && y == 5) {
		return 39;
	} else if(type == 1 && x == 13 && y == 6) {
		return 40;
	} else if(type == 1 && x == 13 && y == 7) {
		return 41;
	} else if(type == 1 && x == 14 && y == 5) {
		return 42;
	} else if(type == 1 && x == 14 && y == 6) {
		return 43;
	} else if(type == 1 && x == 14 && y == 7) {
		return 44;
	} else if(type == 1 && x == 13 && y == 0) {
		return 45;
	} else if(type == 1 && x == 13 && y == 1) {
		return 46;
	} else if(type == 1 && x == 14 && y == 0) {
		return 47;
	} else if(type == 1 && x == 14 && y == 1) {
		return 48;
	} else if(type == 1 && x == 12 && y == 0) {
		return 49;
	} else if(type == 1 && x == 15 && y == 4) {
		return 50;
	} else if(type == 1 && x == 15 && y == 5) {
		return 51;
	} else if(type == 1 && x == 16 && y == 4) {
		return 52;
	} else if(type == 1 && x == 16 && y == 5) {
		return 53;
	} else if(type == 2 && x == 36 && y == 1) {
		return 70;
	} else if(type == 2 && x == 36 && y == 2) {
		return 71;
	} else if(type == 2 && x == 36 && y == 3) {
		return 72;
	} else if(type == 2 && x == 36 && y == 4) {
		return 73;
	} else if(type == 2 && x == 37 && y == 4) {
		return 74;
	} else if(type == 2 && x == 38 && y == 4) {
		return 75;
	} else if(type == 2 && x == 36 && y == 5) {
		return 76;
	} else if(type == 2 && x == 36 && y == 6) {
		return 77;
	} else if(type == 2 && x == 36 && y == 7) {
		return 78;
	} else if(type == 2 && x == 37 && y == 5) {
		return 79;
	} else if(type == 2 && x == 37 && y == 6) {
		return 80;
	} else if(type == 2 && x == 37 && y == 7) {
		return 81;
	} else if(type == 2 && x == 38 && y == 5) {
		return 82;
	} else if(type == 2 && x == 38 && y == 6) {
		return 83;
	} else if(type == 2 && x == 38 && y == 7) {
		return 84;
	} else if(type == 2 && x == 36 && y == 0) {
		return 85;
	} else if(type == 2 && x == 37 && y == 0) {
		return 86;
	} else if(type == 2 && x == 37 && y == 1) {
		return 87;
	} else if(type == 2 && x == 38 && y == 0) {
		return 88;
	} else if(type == 2 && x == 38 && y == 1) {
		return 89;
	} else if(type == 2 && x == 39 && y == 4) {
		return 90;
	} else if(type == 2 && x == 39 && y == 5) {
		return 91;
	} else if(type == 2 && x == 40 && y == 4) {
		return 92;
	} else if(type == 2 && x == 40 && y == 5) {
		return 93;
	} else if(type == 3 && x == 1 && y == 6) {
		return 120;
	}
}

void Map::getTerrainByType(int type, int &x, int &y)
{
	if(type == 20) {
		x = 43;
		y = 6;
	} else if(type == 30) {
		x = 12;
		y = 1;
	} else if(type == 31) {
		x = 12;
		y = 2;
	} else if(type == 32) {
		x = 12;
		y = 3;
	} else if(type == 33) {
		x = 12;
		y = 4;
	} else if(type == 34) {
		x = 13;
		y = 4;
	} else if(type == 35) {
		x = 14;
		y = 4;
	} else if(type == 36) {
		x = 12;
		y = 5;
	} else if(type == 37) {
		x = 12;
		y = 6;
	} else if(type == 38) {
		x = 12;
		y = 7;
	} else if(type == 39) {
		x = 13;
		y = 5;
	} else if(type == 40) {
		x = 13;
		y = 6;
	} else if(type == 41) {
		x = 13;
		y = 7;
	} else if(type == 42) {
		x = 14;
		y = 5;
	} else if(type == 43) {
		x = 14;
		y = 6;
	} else if(type == 44) {
		x = 14;
		y = 7;
	} else if(type == 45) {
		x = 13;
		y = 0;
	} else if(type == 46) {
		x = 13;
		y = 1;
	} else if(type == 47) {
		x = 14;
		y = 0;
	} else if(type == 48) {
		x = 14;
		y = 1;
	} else if(type == 49) {
		x = 12;
		y = 0;
	} else if(type == 50) {
		x = 15;
		y = 4;
	} else if(type == 51) {
		x = 15;
		y = 5;
	} else if(type == 52) {
		x = 16;
		y = 4;
	} else if(type == 53) {
		x = 16;
		y = 5;
	} else if(type == 70) {
		x = 36;
		y = 1;
	} else if(type == 71) {
		x = 36;
		y = 2;
	} else if(type == 72) {
		x = 36;
		y = 3;
	} else if(type == 73) {
		x = 36;
		y = 4;
	} else if(type == 74) {
		x = 37;
		y = 4;
	} else if(type == 75) {
		x = 38;
		y = 4;
	} else if(type == 76) {
		x = 36;
		y = 5;
	} else if(type == 77) {
		x = 36;
		y = 6;
	} else if(type == 78) {
		x = 36;
		y = 7;
	} else if(type == 79) {
		x = 37;
		y = 5;
	} else if(type == 80) {
		x = 37;
		y = 6;
	} else if(type == 81) {
		x = 37;
		y = 7;
	} else if(type == 82) {
		x = 38;
		y = 5;
	} else if(type == 83) {
		x = 38;
		y = 6;
	} else if(type == 84) {
		x = 38;
		y = 7;
	} else if(type == 85) {
		x = 36;
		y = 0;
	} else if(type == 86) {
		x = 37;
		y = 0;
	} else if(type == 87) {
		x = 37;
		y = 1;
	} else if(type == 88) {
		x = 38;
		y = 0;
	} else if(type == 89) {
		x = 38;
		y = 1;
	} else if(type == 90) {
		x = 39;
		y = 4;
	} else if(type == 91) {
		x = 39;
		y = 5;
	} else if(type == 92) {
		x = 40;
		y = 4;
	} else if(type == 93) {
		x = 40;
		y = 5;
	} else if(type == 120) {
		x = 1;
		y = 6;
	}
}

Map::~Map(void)
{
}
