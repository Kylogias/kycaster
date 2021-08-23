#ifndef KYCASTER_KCM_FORMAT_H
#define KYCASTER_KCM_FORMAT_H

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <memory.h>

// File Structure:
//
// Header (KCMFF_MapHeader_J*)
// For all data associated with map:
//     Data Identifier (uint16_t)
//     Corresponding Data (KCMFF_MapPoint || KCMFF_MapSegment || KC_MapBlock || KC_MapEntity)
// Checksum of all previous data (2 uint64_t)

enum {
	KCMFF_MAPDATA_POINT, KCMFF_MAPDATA_SEGMENT, KCMFF_MAPDATA_FACE, KCMFF_MAPDATA_BLOCK, KCMFF_MAPDATA_ENTITY
};

typedef struct KCMFF_Header {
	uint32_t magic; // should be (50 4D 43 4B), aka KCMP
	uint32_t v_major; // Major version number
	uint64_t mapPnt; // Number of Map Points
	uint64_t mapSeg; // Number of Map Segments
	uint64_t mapBlk; // Number of Map Blocks
	uint64_t mapEnt; // Number of Map Entities
} KCMFF_Header;

typedef struct KCMFF_MapPoint {
	uint64_t ID; // Unique identifier
	double X; // X coordinate
	double Y; // Y coordinate
} KCMFF_MapPoint;

typedef struct KCMFF_MapSegment {
	uint64_t ID; // Unique identifier
	uint64_t PointID1; // First point ID
	uint64_t PointID2; // Second point ID
} KCMFF_MapSegment;

typedef struct KCMFF_MapFace {
	
} KCMFF_MapFace;

typedef struct KCMFF_MapBlock {
	uint64_t ID; // Unique identifier
	uint64_t TexID; // ID of texture type
	uint8_t extAxis; // Axis to extend to. 0=X, 1=Y, 2=Z;
	double axStart; // Start of the block along the axis
	double axEnd; // End of the block along the axis
	uint64_t SegID1; // ID of first segment
	uint64_t SegID2; // ID of second segment
	uint64_t SegID3; // ID of third segment
} KCMFF_MapBlock;

typedef struct KCMFF_MapEntity {
	uint64_t ID; // Unique identifier
	uint64_t EntID; // ID of entity type
	double xPos, yPos, zPos; // Entity position
	float yaw, pitch; // Entity rotation
} KCMFF_MapEntity;

typedef struct KCMFF_LoadedMap {
	char* name;
	uint32_t nameLen;
	
	KCMFF_Header head;
	
	KCMFF_MapEntity* ents;
	KCMFF_MapSegment* segs;
	KCMFF_MapBlock* blks;
	KCMFF_MapPoint* pnts;
} KCMFF_LoadedMap;



void KCMFF_BeginSave(char* name, uint32_t nameLen);
void KCMFF_EndSave();
void KCMFF_SaveEntity(KCMFF_MapEntity ent);
void KCMFF_SaveBlock(KCMFF_MapBlock block);
void KCMFF_SaveSegment(KCMFF_MapSegment seg);

char* KCMFF_LoadMapAsBuffer(char name[]);
KCMFF_LoadedMap KCMFF_LoadMap(char name[]);
void KCMFF_UnloadMap(KCMFF_LoadedMap map);

#endif