#pragma once

namespace	epion::Node
{
	class NormalFromHeightTangent final
	{
	public:
	private:
	};
	class NormalFromHeightWorld final
	{
	public:
	private:
	};

	//void NormalFromHeight_Tangent(float In, out float3 Out)
	//{
	//	float3 worldDirivativeX = ddx(Position * 100);
	//	float3 worldDirivativeY = ddy(Position * 100);
	//	float3 crossX = cross(TangentMatrix[2].xyz, worldDirivativeX);
	//	float3 crossY = cross(TangentMatrix[2].xyz, worldDirivativeY);
	//	float3 d = abs(dot(crossY, worldDirivativeX));
	//	float3 inToNormal = ((((In + ddx(In)) - In) * crossY) + (((In + ddy(In)) - In) * crossX)) * sign(d);
	//	inToNormal.y *= -1.0;
	//	Out = normalize((d * TangentMatrix[2].xyz) - inToNormal);
	//	Out = TransformWorldToTangent(Out, TangentMatrix);
	//}
}