#include "Radar.h"

FVector2 RevolveCoordinatesSystem(float RevolveAngle, FVector2 OriginPos, FVector2 DestPos)
{
	FVector2 ResultPos;
	if (RevolveAngle == 0)
		return DestPos;
	ResultPos.X = OriginPos.X + (DestPos.X - OriginPos.X) * cos(RevolveAngle * M_PI / 180) + (DestPos.Y - OriginPos.Y) * sin(RevolveAngle * M_PI / 180);
	ResultPos.Y = OriginPos.Y - (DestPos.X - OriginPos.X) * sin(RevolveAngle * M_PI / 180) + (DestPos.Y - OriginPos.Y) * cos(RevolveAngle * M_PI / 180);
	return ResultPos;
}


void Base_Radar::SetRange(const float& Range)
{
	this->RenderRange = Range;
}

void Base_Radar::SetCrossColor(const ImColor& Color)
{
	this->CrossColor = Color;
}

void Base_Radar::SetPos(const FVector2& Pos)
{
	this->Pos = Pos;
}

void Base_Radar::SetSize(const float& Size)
{
	this->Width = Size;
}

float Base_Radar::GetSize()
{
	return this->Width;
}

FVector2 Base_Radar::GetPos()
{
	return this->Pos;
}

void Base_Radar::SetProportion(const float& Proportion)
{
	this->Proportion = Proportion;
}

void Base_Radar::SetDrawList(ImDrawList* DrawList)
{
	this->DrawList = DrawList;
}

void Base_Radar::AddPoint(const FVector& LocalPos, const float& LocalYaw, const FVector& Pos, ImColor Color, int Type, float Yaw)
{
	FVector2 PointPos;
	float Distance;
	float Angle;

	this->LocalYaw = LocalYaw;

	Distance = sqrt(pow(LocalPos.x - Pos.x, 2) + pow(LocalPos.y - Pos.y, 2));



	Angle = atan2(Pos.y - LocalPos.y, Pos.x - LocalPos.x) * 180 / M_PI;
	//Angle = (this->LocalYaw - Angle) * M_PI / 180;

	Angle = this->LocalYaw - Angle;
	Angle = -Angle * 3.1415926f / 180;

	Distance = Distance / this->Proportion * this->RenderRange * 2;

	PointPos.X = this->Pos.X + Distance * sin(Angle);
	PointPos.Y = this->Pos.Y - Distance * cos(Angle);

	// Circle range
	//Distance = sqrt(pow(this->Pos.X - PointPos.X, 2) + pow(this->Pos.Y - PointPos.Y, 2));
	//if (Distance > this->RenderRange)
	//	return;

	// Rectangle range

	if (PointPos.X < this->Pos.X - RenderRange || PointPos.X > this->Pos.X + RenderRange
		|| PointPos.Y > this->Pos.Y + RenderRange || PointPos.Y < this->Pos.Y - RenderRange)
		return;

	std::tuple<FVector2, ImColor, int, float> Data(PointPos, Color, Type, Yaw);
	this->Points.push_back(Data);
}


void Base_Radar::Render()
{
	if (this->DrawList == nullptr)
		return;
	if (Width <= 0)
		return;

	// Cross
	std::pair<FVector2, FVector2> Line1;
	std::pair<FVector2, FVector2> Line2;

	Line1.first = FVector2(this->Pos.X - this->Width / 2, this->Pos.Y);
	Line1.second = FVector2(this->Pos.X + this->Width / 2, this->Pos.Y);
	Line2.first = FVector2(this->Pos.X, this->Pos.Y - this->Width / 2);
	Line2.second = FVector2(this->Pos.X, this->Pos.Y + this->Width / 2);

	if (this->Opened)
	{
		if (this->ShowCrossLine)
		{
			this->DrawList->AddLine(Line1.first.ToImVec2(), Line1.second.ToImVec2(), this->CrossColor, 1);
			this->DrawList->AddLine(Line2.first.ToImVec2(), Line2.second.ToImVec2(), this->CrossColor, 1);
		}

		for (auto PointSingle : this->Points)
		{
			FVector2	PointPos = std::get<0>(PointSingle);
			ImColor PointColor = std::get<1>(PointSingle);
			int		PointType = std::get<2>(PointSingle);
			float	PointYaw = std::get<3>(PointSingle);
			if (PointType == 0)
			{
				// 圆形样式
				this->DrawList->AddCircle(PointPos.ToImVec2(), this->CircleSize, PointColor);
				this->DrawList->AddCircleFilled(PointPos.ToImVec2(), this->CircleSize, ImColor(255, 0, 0));
			}
			else if (PointType == 1)
			{
				// 箭头样式
				FVector2 a, b, c;
				FVector2 Re_a, Re_b, Re_c;
				FVector2 Re_Point;
				float Angle = (this->LocalYaw - PointYaw) + -180;
				Re_Point = RevolveCoordinatesSystem(Angle, this->Pos, PointPos);

				Re_a = FVector2(Re_Point.X, Re_Point.Y + this->ArrowSize);
				Re_b = FVector2(Re_Point.X - this->ArrowSize / 1.5, Re_Point.Y - this->ArrowSize / 2);
				Re_c = FVector2(Re_Point.X + this->ArrowSize / 1.5, Re_Point.Y - this->ArrowSize / 2);

				a = RevolveCoordinatesSystem(-Angle, this->Pos, Re_a);
				b = RevolveCoordinatesSystem(-Angle, this->Pos, Re_b);
				c = RevolveCoordinatesSystem(-Angle, this->Pos, Re_c);

				this->DrawList->AddQuadFilled(
					ImVec2(a.X, a.Y),
					ImVec2(b.X, b.Y),
					ImVec2(PointPos.X, PointPos.Y),
					ImVec2(c.X, c.Y),
					PointColor
				);
				this->DrawList->AddQuad(
					ImVec2(a.X, a.Y),
					ImVec2(b.X, b.Y),
					ImVec2(PointPos.X, PointPos.Y),
					ImVec2(c.X, c.Y),
					ImColor(0, 0, 0, 150),
					0.1
				);
			}
			else
			{
				// 圆弧箭头
				ImVec2 TrianglePoint, TrianglePoint_1, TrianglePoint_2;
				float Angle = (this->LocalYaw - PointYaw) - 90;

				this->DrawList->AddCircleFilled(PointPos.ToImVec2(), 0.85 * this->ArcArrowSize, PointColor, 30);
				this->DrawList->AddCircle(PointPos.ToImVec2(), 0.95 * this->ArcArrowSize, ImColor(0, 0, 0, 150), 0, 0.1);

				TrianglePoint.x = PointPos.X + (this->ArcArrowSize + this->ArcArrowSize / 3) * cos(-Angle * M_PI / 180);
				TrianglePoint.y = PointPos.Y - (this->ArcArrowSize + this->ArcArrowSize / 3) * sin(-Angle * M_PI / 180);

				TrianglePoint_1.x = PointPos.X + this->ArcArrowSize * cos(-(Angle - 30) * M_PI / 180);
				TrianglePoint_1.y = PointPos.Y - this->ArcArrowSize * sin(-(Angle - 30) * M_PI / 180);

				TrianglePoint_2.x = PointPos.X + this->ArcArrowSize * cos(-(Angle + 30) * M_PI / 180);
				TrianglePoint_2.y = PointPos.Y - this->ArcArrowSize * sin(-(Angle + 30) * M_PI / 180);

				this->DrawList->PathLineTo(TrianglePoint);
				this->DrawList->PathLineTo(TrianglePoint_1);
				this->DrawList->PathLineTo(TrianglePoint_2);
				this->DrawList->PathFillConvex(ImColor(220, 220, 220, 240));
			}
		}
	}

	if (this->Points.size() > 0)
		this->Points.clear();
}