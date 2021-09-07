#include "../common.h"

KCMFF_LoadedMap _KCMFF_SaveMap;
#define smap _KCMFF_SaveMap

void KCMFF_BeginSave(char* name, uint32_t nameLen) {
	smap.name = name;
	smap.nameLen = nameLen;
	smap.head.magic = KCMFF_MAGIC_NUMBER;
	smap.head.v_major = KCMFF_VERSION_NUMBER;
}

void KCMFF_EndSave() {
	FILE* fp;
	int32_t err = fopen_s(&fp, smap.name, "wb");



	free(smap.bents);
	free(smap.fces);
	free(smap.pents);
	free(smap.segs);
	free(smap.pnts);

	smap.head.magic = 0;
	smap.head.v_major = UINT32_MAX;

	smap.head.mapBEnt = 0;
	smap.head.mapFce = 0;
	smap.head.mapPEnt = 0;
	smap.head.mapPnt = 0;
	smap.head.mapSeg = 0;
}





KCMFF_LoadedMap KCMFF_LoadMap(char name[]) {
	KCMFF_LoadedMap map;
	FILE* fp;
	int32_t err = fopen_s(&fp, name, "rb");
	if (fp == NULL) {
		printf("Something went wrong loading the map, %s\n", strerror(err));
		map.head.magic = err;
		return map;
	}

	fread(&map.head, sizeof(KCMFF_Header), 1, fp);
	if (map.head.magic != KCMFF_MAGIC_NUMBER) {
		char magic[5];
		magic[0] =  map.head.magic & 0x000000FF;
		magic[1] = (map.head.magic & 0x0000FF00) >> 8;
		magic[2] = (map.head.magic & 0x00FF0000) >> 16;
		magic[3] = (map.head.magic & 0xFF000000) >> 24;
		magic[4] = '\0';
		printf("Magic Number does not match. Expected KCMP, got %s", magic);
		return map;
	}
	if (map.head.v_major != KCMFF_VERSION_NUMBER) {
		printf("Map version not supported, expected %i, got %i", KCMFF_VERSION_NUMBER, map.head.v_major);
		return map;
	}
	map.name = name;
	map.nameLen = 0;

	map.bents = malloc(sizeof(KCMFF_LoadedMapBEnt) * map.head.mapBEnt);
	map.pents = malloc(sizeof(KCMFF_LoadedMapPEnt) * map.head.mapPEnt);
	map.fces = malloc(sizeof(KCMFF_LoadedMapFace) * map.head.mapFce);
	map.pnts = malloc(sizeof(KCMFF_MapPoint) * map.head.mapPnt);
	map.segs = malloc(sizeof(KCMFF_MapSegment) * map.head.mapSeg);

	uint64_t curPoint = 0;
	uint64_t curSegment = 0;
	uint64_t curFace = 0;
	uint64_t curBEnt = 0;
	uint64_t curPEnt = 0;

	while (1) {
		KCMFF_MAPDATA_TYPE dataType;

		fread(&dataType, sizeof(dataType), 1, fp);
		if (dataType == KCMFF_MAPDATA_STOP) break;
		switch (dataType) {
			case KCMFF_MAPDATA_POINT: {
				fread(&map.pnts[curPoint], sizeof(map.pnts[curPoint]), 1, fp);
				curPoint += 1;
				break;
			}
			case KCMFF_MAPDATA_FACE: {
				fread(&map.fces[curFace].initial, sizeof(map.fces[curFace]), 1, fp);

				map.fces[curFace].segments = malloc(sizeof(map.fces[curFace].segments) * map.fces[curFace].initial.numSegs);
				fread(&map.fces[curFace].segments, sizeof(map.fces[curFace].segments), map.fces[curFace].initial.numSegs, fp);

				curFace += 1;

				break;
			}
			case KCMFF_MAPDATA_SEGMENT: {
				fread(&map.segs[curSegment], sizeof(map.segs[curSegment]), 1, fp);
				curSegment += 1;
				break;
			}
			case KCMFF_MAPDATA_BLOCK_ENTITY: {
				fread(&map.bents[curBEnt].initial, sizeof(map.bents[curBEnt]), 1, fp);

				map.bents[curBEnt].name = malloc(sizeof(map.bents[curBEnt].name) * map.bents[curBEnt].initial.nameLen);
				fread(&map.bents[curBEnt].name, sizeof(map.bents[curBEnt].name), map.bents[curBEnt].initial.nameLen, fp);

				map.bents[curBEnt].faces = malloc(sizeof(map.bents[curBEnt].faces) * map.bents[curBEnt].initial.numFaces);
				fread(&map.bents[curBEnt].faces, sizeof(map.bents[curBEnt].faces), map.bents[curBEnt].initial.numFaces, fp);

				curBEnt += 1;
				break;
			}
			case KCMFF_MAPDATA_POINT_ENTITY: {
				fread(&map.pents[curPEnt].initial, sizeof(map.pents[curPEnt]), 1, fp);

				map.pents[curPEnt].name = malloc(sizeof(map.pents[curPEnt].name) * map.pents[curPEnt].initial.nameLen);
				fread(&map.pents[curPEnt].name, sizeof(map.pents[curPEnt].name), map.pents[curPEnt].initial.nameLen, fp);

				curPEnt += 1;
				break;
			}
		}
	}

	fclose(fp);
	return map;
}
void KCMFF_UnloadMap(KCMFF_LoadedMap map) {
	
}