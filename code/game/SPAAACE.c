//* SPAAACE!
#include "../qcommon/q_shared.h"
#include "bg_public.h" 
/*
===============
CalcMuzzlePoint

set muzzle location relative to pivoting eye
===============
*/
void CalcMuzzlePointStuff ( playerState_t *ps, vec3_t forward, vec3_t right, vec3_t up, vec3_t muzzlePoint ) {
	entityState_t s;
	BG_PlayerStateToEntityState(ps, &s, qtrue);
	VectorCopy( /*ent->*/s.pos.trBase, muzzlePoint );
	muzzlePoint[2] += /*ent->client->*/ps->viewheight;
	VectorMA( muzzlePoint, 14, forward, muzzlePoint );
	// snap to integer coordinates for more efficient network bandwidth usage
	SnapVector( muzzlePoint );
}
/*
===============
Inv_CalcMuzzlePoint

set muzzle location relative to pivoting eye
===============
*/
void Inv_CalcMuzzleStuff(playerState_t ps, vec3_t forward, vec3_t right, vec3_t up, vec3_t muzzlePoint)
{
	//gclient_t *cl = ent->client;
	//int i;
	//vec3_t Gravity;

	//if (!cl)
	//{
		CalcMuzzlePointStuff(&ps, forward, right, up, muzzlePoint);
		return;
	//}
/*
	Inv_GetVectorFromStat(cl->ps.stats[STAT_GRAVITY], Gravity);
	entityState_t s;
	BG_PlayerStateToEntityState(&ps, &s, qtrue); 
	VectorCopy(/*ent->*\/s.pos.trBase, muzzlePoint);
	for (i = 0; i < 3; ++i)
		muzzlePoint[i] -= ent->client->ps.viewheight * Gravity[i];
	VectorMA(muzzlePoint, 8, forward, muzzlePoint);
	// snap to integer coordinates for more efficient network bandwidth usage
	SnapVector(muzzlePoint);
*/
}

/*
===============
CalcMuzzlePointOrigin

set muzzle location relative to pivoting eye
===============
*/
/**************************************************************************************************************/
void CalcMuzzlePointOriginStuff ( playerState_t ps, vec3_t origin, vec3_t forward, vec3_t right, vec3_t up, vec3_t muzzlePoint ) {

	AngleVectors(ps.viewangles, forward, right, up);
	CalcMuzzlePointStuff(&ps, forward, right, up, muzzlePoint);
}

void CalcVecDir(pmove_t *pm, vec3_t forward, vec3_t right, vec3_t up, vec3_t muzzle) {
	vec3_t oldOrigin;
	// set aiming directions
	AngleVectors (pm->ps->viewangles, forward, right, up);
	VectorCopy(pm->ps->origin,oldOrigin);
	//oldOrigin[0] = pm->ps->persistant[PERS_ORIGIN0]/100.0f;
	//oldOrigin[1] = pm->ps->persistant[PERS_ORIGIN1]/100.0f;
	//oldOrigin[2] = pm->ps->persistant[PERS_ORIGIN2]/100.0f;
	CalcMuzzlePointOriginStuff(*(pm->ps), oldOrigin, forward, right, up, muzzle );
	// Recalculate using muzzle as origin
	CalcMuzzlePointOriginStuff( *(pm->ps), muzzle, forward, right, up, muzzle);
}
/**************************************************************************************************************/
