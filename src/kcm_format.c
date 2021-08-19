#include "kcm_format.h"

KCMFF_LoadedMap_J1 _KCMFF_SaveMap;

void _KCMFF_u128_add(uint64_t* toHigh, uint64_t* toLow, uint64_t add) {
	uint64_t oldToLow = *toLow;
	*toLow += add;
	if (oldToLow > *toLow) *toHigh += 1;
}

void KCMFF_BeginSave(char* name, uint32_t nameLen) {
	_KCMFF_SaveMap.name = name;
	_KCMFF_SaveMap.nameLen = nameLen;
	_KCMFF_SaveMap.head.magic = 0x504D434B;
	_KCMFF_SaveMap.head.v_major = 1;
	_KCMFF_SaveMap.blks = malloc(0);
	_KCMFF_SaveMap.ents = malloc(0);
	_KCMFF_SaveMap.segs = malloc(0);
}
void KCMFF_EndSave() {
	uint64_t checksumH = 0;
	uint64_t checksumL = 0;
	#define csumAdd(x) _KCMFF_u128_add(&checksumH, &checksumL, x)
	#define smap _KCMFF_SaveMap
	FILE* fp = fopen(_KCMFF_SaveMap.name, "wb");
	if (!fp) {
		printf("File could not be opened, TERMINATION IMMINENT\n");
		exit(404);
	}
	fwrite(&_KCMFF_SaveMap.head, sizeof(_KCMFF_SaveMap.head), 1, fp);
		csumAdd(smap.head.magic); csumAdd(smap.head.mapBlk); csumAdd(smap.head.mapEnt);
		csumAdd(smap.head.mapSeg); csumAdd(smap.head.v_major);
	for (uint32_t i = 0; i < smap.head.mapSeg; i++) {
		uint16_t typeID = KCMFF_MAPDATA_SEGMENT;
		fwrite(&typeID, sizeof(uint16_t), 1, fp);
		csumAdd(typeID);
		
		fwrite(&smap.segs[i], sizeof(KCMFF_MapSegment), 1, fp);
		csumAdd(smap.segs[i].AX); csumAdd(smap.segs[i].AY); csumAdd(smap.segs[i].BX); csumAdd(smap.segs[i].BY); csumAdd(smap.segs[i].ID);
	}
	for (uint32_t i = 0; i < smap.head.mapBlk; i++) {
		uint16_t typeID = KCMFF_MAPDATA_BLOCK;
		fwrite(&typeID, sizeof(uint16_t), 1, fp);
		csumAdd(typeID);
		
		fwrite(&smap.blks[i], sizeof(KCMFF_MapBlock), 1, fp);
		csumAdd(smap.blks[i].ID); csumAdd(smap.blks[i].SegID3); csumAdd(smap.blks[i].SegID2); csumAdd(smap.blks[i].SegID1); csumAdd(smap.blks[i].TexID);
		csumAdd(smap.blks[i].axEnd); csumAdd(smap.blks[i].axStart); csumAdd(smap.blks[i].extAxis);
	}
	for (uint32_t i = 0; i < smap.head.mapEnt; i++) {
		uint16_t typeID = KCMFF_MAPDATA_ENTITY;
		fwrite(&typeID, sizeof(uint16_t), 1, fp);
		csumAdd(typeID);
		
		fwrite(&smap.ents[i], sizeof(KCMFF_MapEntity), 1, fp);
		csumAdd(smap.ents[i].EntID); csumAdd(smap.ents[i].ID); csumAdd(smap.ents[i].zPos); csumAdd(smap.ents[i].yPos); csumAdd(smap.ents[i].zPos);
		csumAdd(smap.ents[i].pitch); csumAdd(smap.ents[i].yaw);
	}
	
	fwrite(&checksumL, sizeof(uint64_t), 1, fp);
	fwrite(&checksumH, sizeof(uint64_t), 1, fp);
	fclose(fp);
	
	
	
	free(_KCMFF_SaveMap.blks);
	free(_KCMFF_SaveMap.ents);
	free(_KCMFF_SaveMap.segs);
	
	_KCMFF_SaveMap.nameLen = 0;
	_KCMFF_SaveMap.name = NULL;
	
	_KCMFF_SaveMap.head.magic = 0;
	_KCMFF_SaveMap.head.v_major = 4294967295;
	_KCMFF_SaveMap.head.mapSeg = 0;
	_KCMFF_SaveMap.head.mapEnt = 0;
	_KCMFF_SaveMap.head.mapBlk = 0;
}
void KCMFF_SaveEntity(KCMFF_MapEntity ent) {
	_KCMFF_SaveMap.head.mapEnt += 1;
	_KCMFF_SaveMap.ents = realloc(_KCMFF_SaveMap.ents, sizeof(KCMFF_MapEntity) * _KCMFF_SaveMap.head.mapEnt);
	_KCMFF_SaveMap.ents[_KCMFF_SaveMap.head.mapEnt-1] = ent;
}
void KCMFF_SaveBlock(KCMFF_MapBlock block) {
	_KCMFF_SaveMap.head.mapBlk += 1;
	_KCMFF_SaveMap.blks = realloc(_KCMFF_SaveMap.blks, sizeof(KCMFF_MapBlock) * _KCMFF_SaveMap.head.mapBlk);
	_KCMFF_SaveMap.blks[_KCMFF_SaveMap.head.mapBlk-1] = block;
}
void KCMFF_SaveSegment(KCMFF_MapSegment seg) {
	_KCMFF_SaveMap.head.mapSeg += 1;
	_KCMFF_SaveMap.segs = realloc(_KCMFF_SaveMap.segs, sizeof(KCMFF_MapSegment) * _KCMFF_SaveMap.head.mapSeg);
	_KCMFF_SaveMap.segs[_KCMFF_SaveMap.head.mapSeg-1] = seg;
}

char* KCMFF_LoadMapAsBuffer(char name[]) {
	char* buf;
	return buf;
}
KCMFF_LoadedMap_J1 KCMFF_LoadMap(char name[]) {
	KCMFF_LoadedMap_J1 map;
	return map;
}
void KCMFF_UnloadMap(KCMFF_LoadedMap_J1 map) {
	
}