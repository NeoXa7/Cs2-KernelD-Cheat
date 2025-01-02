#pragma once
#include "sdkincs.h"
#include <Maths/Vector.hpp>

namespace Coords
{
	// Upper
	inline Vector3 GetHeadCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::HEAD * 0x20));
	}

	inline Vector3 GetPenisCoordinates3D()
	{
		return cEntities->Position + cEntities->View * 0.5;
	}

	inline Vector3 GetNeckCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::NECK * 0x20));
	}

	inline Vector3 GetChestCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::CHEST * 0x20));
	}

	inline Vector3 GetStomachCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::STOMACH * 0x20));
	}

	// Upper Left
	inline Vector3 GetLShoulderCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::LSHOULDER * 0x20));
	}

	inline Vector3 GetLArmCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::LARM * 0x20));
	}

	inline Vector3 GetLHandCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::LHAND * 0x20));
	}

	// Lower Left
	inline Vector3 GetLThighCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::LTHIGH * 0x20));
	}

	inline Vector3 GetLCalfCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::LCALF * 0x20));
	}

	inline Vector3 GetLFootCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::LFOOT * 0x20));
	}

	// Upper Right
	inline Vector3 GetRShoulderCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::RSHOULDER * 0x20));
	}

	inline Vector3 GetRArmCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::RARM * 0x20));
	}

	inline Vector3 GetRHandCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::RHAND * 0x20));
	}

	// Lower Right
	inline Vector3 GetRThighCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::RTHIGH * 0x20));
	}

	inline Vector3 GetRCalfCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::RCALF * 0x20));
	}

	inline Vector3 GetRFootCoordinates3D()
	{
		return Driver::RPM<Vector3>(cEntities->BoneMatrix + (CBone::Index::RFOOT * 0x20));
	}
}