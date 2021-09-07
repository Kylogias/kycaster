#ifndef KYCASTER_KCM_FORMAT_H
#define KYCASTER_KCM_FORMAT_H

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <memory.h>
#include "../common.h"

// File Structure:
//
// Header (KCMFF_Header)
// For all data associated with map:
//     Data Identifier (uint16_t)
//     Corresponding Data (KCMFF_Map*)

#define KCMFF_VERSION_NUMBER 3
#define KCMFF_MAGIC_NUMBER 0x504D434B
#define KCMFF_MAPDATA_TYPE uint8_t

enum {
	KCMFF_MAPDATA_POINT, KCMFF_MAPDATA_SEGMENT, KCMFF_MAPDATA_FACE, KCMFF_MAPDATA_POINT_ENTITY, KCMFF_MAPDATA_BLOCK_ENTITY, KCMFF_MAPDATA_STOP = 255
};

typedef struct KCMFF_Header {
	uint32_t magic; // should be (50 4D 43 4B), aka KCMP
	uint32_t v_major; // Major version number
	uint64_t mapPnt; // Number of Map Points
	uint64_t mapSeg; // Number of Map Segments
	uint64_t mapFce; // Number of Map Faces
	uint64_t mapPEnt; // Number of Map Point Entities
	uint64_t mapBEnt; // Number of Map Block Entities
} KCMFF_Header;

typedef struct KCMFF_MapPoint {
	uint64_t ID; // Unique identifier
	double X; // X coordinate
	double Y; // Y coordinate
	double Z; // Z coordinate
} KCMFF_MapPoint;

typedef struct KCMFF_MapSegment {
	uint64_t ID; // Unique identifier
	uint64_t PointID1; // First point ID
	uint64_t PointID2; // Second point ID
} KCMFF_MapSegment;

typedef struct KCMFF_MapFace {
	uint64_t ID; // Unique identifier
	uint64_t numSegs; // Number of segments
} KCMFF_MapFace;

typedef struct KCMFF_LoadedMapFace {
	KCMFF_MapFace initial;
	uint64_t* segments;
} KCMFF_LoadedMapFace;

typedef struct KCMFF_MapBEnt {
	uint16_t nameLen; // Length of Name
	uint64_t ID; // Unique identifier
	uint64_t EntID; // ID of entity type
	uint64_t numFaces; // Number of faces
} KCMFF_MapBEnt;

typedef struct KCMFF_LoadedMapBEnt {
	KCMFF_MapBEnt initial;
	char* name;
	uint64_t* faces;
} KCMFF_LoadedMapBEnt;

typedef struct KCMFF_MapPEnt {
	uint16_t nameLen; // Length of Name
	uint64_t ID; // Unique identifier
	uint64_t EntID; // ID of entity type
	double xPos, yPos, zPos; // Entity position
	float yaw, pitch; // Entity rotation
} KCMFF_MapPEnt;

typedef struct KCMFF_LoadedMapPEnt {
	KCMFF_MapPEnt initial;
	char* name;
} KCMFF_LoadedMapPEnt;

typedef struct KCMFF_LoadedMap {
	char* name;
	uint32_t nameLen;
	
	KCMFF_Header head;
	
	KCMFF_LoadedMapPEnt* pents;
	KCMFF_MapSegment* segs;
	KCMFF_MapPoint* pnts;
	KCMFF_LoadedMapFace* fces;
	KCMFF_LoadedMapBEnt* bents;
} KCMFF_LoadedMap;



void KCMFF_BeginSave(char* name, uint32_t nameLen);
void KCMFF_EndSave();

void KCMFF_SavePointEntity(KCMFF_LoadedMapPEnt pent);
void KCMFF_SaveBlockEntity(KCMFF_LoadedMapBEnt bent);
void KCMFF_SaveFace(KCMFF_LoadedMapFace face);
void KCMFF_SaveSegment(KCMFF_MapSegment seg);
void KCMFF_SavePoint(KCMFF_MapPoint point);

KCMFF_LoadedMap KCMFF_LoadMap(char name[]);
void KCMFF_UnloadMap(KCMFF_LoadedMap map);

#endif