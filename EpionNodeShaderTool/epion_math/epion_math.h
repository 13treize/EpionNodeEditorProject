#pragma	once
#include	"cereal/cereal.hpp"

#include	"epion_vector2.h"
#include	"epion_vector3.h"
#include	"epion_vector4.h"

#include	"epion_random.h"

namespace	epion::math
{
	template	<class	T>
	constexpr	T	pi = static_cast<T>(3.14159265358979323846);

	using	FVector2 = Vector2<float>;
	using	FVector3 = Vector3<float>;
	using	FVector4 = Vector4<float>;


}

#include	"epion_matrix.h"
