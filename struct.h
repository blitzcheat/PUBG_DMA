#pragma once
#include "Includes.h"

#define ºìÉ« ImColor(255,0,0) 
#define »ÆÉ« ImColor(255,255,0)
#define ºÚÉ« ImColor(105,105,105)
#define ÉîÇà ImColor(0,139,139)
#define ³È»Æ ImColor(255,127,0)
#define ÌìÀ¶ ImColor(0,191,255)
#define À¶É« ImColor(30,144,255)
#define ÂÌÉ« ImColor(118,238,0)
#define °×É« ImColor(211,211,211)
#define ÌÒºì ImColor(238,44,44)


#define M_PI       3.14159265358979323846   // pi

enum class ESlateVisibility : uint8_t
{
	Visible = 0,
	Collapsed = 1,
	Hidden = 2,
	HitTestInvisible = 3,
	SelfHitTestInvisible = 4,
	ESlateVisibility_MAX = 5
};
enum ECharacterState : uint8_t
{
	Unk,
	Fire,
	Wounded,
	BeHit,
	Offline,
};

template<class T>
class TArrayDrink {

public:
	TArrayDrink() {
		Data = nullptr;
		Count = 0;
		Max = 0;
	}
	size_t size(size_t MaxSize = 0x2000) const {
		return Count < MaxSize ? Count : MaxSize;
	}

	bool GetValue(int i, T& value) const {
		if (i < 0 || i >= size(0x2000)) return false;
		G::Mem.ReadMemory((ULONG64)(Data + sizeof(T) * i), &value, sizeof(T));

		return true;// memcpy(&value, (PVOID)(Data + sizeof(T) * i), sizeof(T));
	}

	bool GetValues(T& value, size_t MaxSize = 0x2000) const {
		
		G::Mem.ReadMemory((ULONG64)Data, &value, sizeof(T) * size(MaxSize));
		return true;// memcpy(&value, (PVOID)Data, sizeof(T) * size(MaxSize));
	}

	std::vector<T> GetVector(size_t MaxSize = 0x2000) const {
		std::vector<T> v(size(MaxSize));
		if (!GetValues(v[0], MaxSize))
			v.clear();

		return v;
	}

	operator std::vector<T>() const { return GetVector(); }

	T operator [](int i) const {
		T Value;
		if (!GetValue(i, Value))
			ZeroMemory(&Value, sizeof(Value));
		return Value;
	}

	T* Data;
	unsigned int Count;
	unsigned int Max;
};
struct FTslWidgetState
{
	unsigned char Pad[0x30];
	ULONG64 WidgetClass;	                                                                             // 0x0030(0x0008) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0038(0x0008) MISSED OFFSET
	ULONG64 Widget;                                                                               // 0x0040(0x0008) (CPF_ExportObject, CPF_ZeroConstructor, CPF_Transient, CPF_InstancedReference, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x20];                                      // 0x0048(0x0018) MISSED OFFSET
};

struct FString : private TArrayDrink<wchar_t> {
	/*inline FString() {}

	FString(const wchar_t* other) {
		if (other != nullptr) {
			Max = Count = std::wcslen(other) + 1;
			Data = new wchar_t[Count];
			std::wmemcpy(Data, other, Count);
		}
	}

	~FString() {
		if (Data != nullptr) {
			delete[] Data;
			Data = nullptr;
		}
	}

	inline bool IsValid() const {
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const {
		if (Data != nullptr)
			return Data;
		return L"";
	}

	std::string ToString() const {
		if (Data != nullptr) {
			auto length = wcslen(Data);
			std::string str(length, '\0');
			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);
			return str;
		}
		return "";
	}

	std::wstring ToWString() const {
		std::wstring str(Data);
		return str;
	}*/
};
template<class T>
struct TSetElement {
	T Value;//0
	int HashNextId;//9
	int HashIndex;//A
};

template<class T>
class TSet : public TArrayDrink<TSetElement<T>> {};

template<class KeyType, class ValueType>
struct TPair {
	KeyType Key;
	ValueType Value;
};

template<class KeyType, class ValueType>
class TMap : public TSet<TPair<KeyType, ValueType>> {
public:
	bool GetValue(const KeyType& Key, ValueType& Value) const {

		for (const auto& Elem : this->GetVector()) {
			if (Elem.Value.Key == Key) {
				Value = Elem.Value.Value;
				return true;
			}
		}
		return false;
	}
};

struct ItemGrounp
{
	int ÎïÆ·×é;
};

class FVector2
{
public:
	float X = 0;
	float Y = 0;
	inline FVector2() : X(0), Y(0) {}

	inline FVector2(float x, float y) : X(x), Y(y) {}

	float DistanceTo(const FVector2& Pos)
	{
		float ×¼ÐÇX = Pos.X - X;
		float ×¼ÐÇY = Pos.Y - Y;
		return sqrtf(×¼ÐÇX * ×¼ÐÇX + ×¼ÐÇY * ×¼ÐÇY);
	}
	bool IsZero()
	{
		if (this->X == 0 || this->Y == 0)
			return true;
		return false;
	}
	inline FVector2 operator + (const FVector2& other) const { return FVector2(X + other.X, Y + other.Y); }

	ImVec2 ToImVec2()
	{
		return ImVec2(X, Y);
	}


};

class FVector3 : public FVector2
{
public:



	float Z = 0;
};
struct FNameEntryHeader
{
public:
	uint16_t bIsWide : 1;
	static constexpr uint32_t ProbeHashBits = 5;
	uint16_t LowercaseProbeHash : ProbeHashBits;
	uint16_t Len : 10;
};
struct FNameEntry
{
public:
	FNameEntryHeader Header;
};

class FVector
{
public:
	FVector() : x(0.f), y(0.f), z(0.f)
	{

	}

	FVector(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}
	~FVector()
	{

	}

	float x;
	float y;
	float z;
	inline bool isZero()
	{
		if (this->x == 0 || this->y == 0 || this->z == 0) return true;
		return false;
	}
	inline float Dot(FVector v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(FVector v)
	{
		float x = this->x - v.x;
		float y = this->y - v.y;
		float z = this->z - v.z;

		return sqrtf((x * x) + (y * y) + (z * z)) * 0.03048f;
	}

	FVector operator+(FVector v)
	{
		return FVector(x + v.x, y + v.y, z + v.z);
	}

	FVector operator-(FVector v)
	{
		return FVector(x - v.x, y - v.y, z - v.z);
	}
	FVector operator - (const FVector& v) const {
		return FVector(x - v.x, y - v.y, z - v.z);
	}

	FVector operator*(float number) const {
		return FVector(x * number, y * number, z * number);
	}

	__forceinline float Magnitude() const {
		return sqrtf(x * x + y * y + z * z);
	}

	inline float Length()
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}

	__forceinline FVector Normalize() {
		FVector vector;
		float length = this->Magnitude();

		if (length != 0) {
			vector.x = x / length;
			vector.y = y / length;
			vector.z = z / length;
		}
		else {
			vector.x = vector.y = 0.0f;
			vector.z = 1.0f;
		}
		return vector;
	}

	__forceinline FVector& operator+=(const FVector& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
};
typedef struct StringA
{
	char buffer[1024];
};
class FMatrix
{
public:
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
	float m[4][4];
	FMatrix MatrixMultiplication(const FMatrix& other);
};
struct Box
{
	float x, y, w, h;
};
struct Index
{
	int Í·²¿,
		¾±²¿,
		¹ÇÅè,
		×ó¼ç,
		×óÖâ,
		×óÊÖ,
		ÓÒ¼ç,
		ÓÒÖâ,
		ÓÒÊÖ;
	int	×óÍÎ,
		×óÏ¥,
		×ó½Å,
		ÓÒÍÎ,
		ÓÒÏ¥,
		ÓÒ½Å;
};
inline float ConvertToRadians(float Degrees) { return Degrees * (3.1415926 / 180.0f); }
inline float ConvertToDegrees(float Radians) { return Radians * (180.0f / 3.1415926); }
struct FRotator
{
	float Pitch;
	float Yaw;
	float Roll;
	FRotator(float pitch, float yaw, float roll) : Pitch(pitch), Yaw(yaw), Roll(roll) {}
	inline FRotator operator+(FRotator a) {
		return { a.Pitch + Pitch,a.Yaw + Yaw, a.Roll + Roll };
	}

	inline FRotator operator-(FRotator a) {
		return { a.Pitch - Pitch,a.Yaw - Yaw, a.Roll - Roll };
	}

	inline FRotator operator*(FRotator a) {
		return { a.Pitch * Pitch,a.Yaw * Yaw, a.Roll * Roll };
	}

	inline FRotator operator*(float a) {
		return { round(a * Pitch),round(a * Yaw), round(a * Roll) };
	}
	inline 	FVector GetUnitVector() const
	{
		float radPitch = ConvertToRadians(Pitch);
		float radYaw = ConvertToRadians(Yaw);

		float SP = sinf(radPitch);
		float CP = cosf(radPitch);
		float SY = sinf(radYaw);
		float CY = cosf(radYaw);

		return FVector(CP * CY, CP * SY, SP);
	}
	inline FMatrix ToMatrix(FVector origin)
	{
		float radPitch = (Pitch * float(M_PI) / 180.f);
		float radYaw = (Yaw * float(M_PI) / 180.f);
		float radRoll = (Roll * float(M_PI) / 180.f);

		float SP = sinf(radPitch);
		float CP = cosf(radPitch);
		float SY = sinf(radYaw);
		float CY = cosf(radYaw);
		float SR = sinf(radRoll);
		float CR = cosf(radRoll);

		FMatrix matrix;
		matrix.m[0][0] = CP * CY;
		matrix.m[0][1] = CP * SY;
		matrix.m[0][2] = SP;
		matrix.m[0][3] = 0.f;

		matrix.m[1][0] = SR * SP * CY - CR * SY;
		matrix.m[1][1] = SR * SP * SY + CR * CY;
		matrix.m[1][2] = -SR * CP;
		matrix.m[1][3] = 0.f;

		matrix.m[2][0] = -(CR * SP * CY + SR * SY);
		matrix.m[2][1] = CY * SR - CR * SP * SY;
		matrix.m[2][2] = CR * CP;
		matrix.m[2][3] = 0.f;

		matrix.m[3][0] = origin.x;
		matrix.m[3][1] = origin.y;
		matrix.m[3][2] = origin.z;
		matrix.m[3][3] = 1.f;

		return matrix;
	}
};

struct FQuat
{
	float X;
	float Y;
	float Z;
	float W;
};

struct FMinimalViewInfo {
	FVector Location; // 0x00(0x0c)
	FVector Rotation; // 0x0c(0x0c)
	float FOV; // 0x18(0x04)
};

struct FTransform
{
	FQuat Rotation;
	FQuat Translation;
	FQuat Scale3D;

	FMatrix ToMatrixWithScale();
};
struct FMargin
{
	float                                              Left;                                                     // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Top;                                                      // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Right;                                                    // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Bottom;                                                   // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

inline float DotProduct(FVector VecA, FVector VecB)
{
	return VecA.x * VecB.x + VecA.y * VecB.y + VecA.z * VecB.z;
}

inline void SubVector(FVector VecA, FVector VecB, FVector* VecC)
{
	VecC->x = VecA.x - VecB.x;
	VecC->y = VecA.y - VecB.y;
	VecC->z = VecA.z - VecB.z;
}
inline void AddVector(FVector VecA, FVector VecB, FVector* VecC)
{
	VecC->x = VecA.x + VecB.x;
	VecC->y = VecA.y + VecB.y;
	VecC->z = VecA.z + VecB.z;
}
inline bool IsNearlyZero(float Value, float ErrorTolerance = 1.e-8f)
{
	return fabs(Value) <= ErrorTolerance;
}
inline void GetAxes(FVector Rotation, FVector* X, FVector* Y, FVector* Z)
{
	float radPitch = (Rotation.x * float(M_PI) / 180.f);
	float radYaw = (Rotation.y * float(M_PI) / 180.f);
	float radRoll = (Rotation.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	X->x = CP * CY;
	X->y = CP * SY;
	X->z = SP;

	Y->x = SR * SP * CY - CR * SY;
	Y->y = SR * SP * SY + CR * CY;
	Y->z = -SR * CP;

	Z->x = -(CR * SP * CY + SR * SY);
	Z->y = CY * SR - CR * SP * SY;
	Z->z = CR * CP;
}

struct FWeaponTrajectoryConfig {
	float                                              InitialSpeed;                                             // 0x0000(0x0004) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	int                                                HitDamage;                                                // 0x0004(0x0004) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              VehicleDamageScalar;                                      // 0x0008(0x0004) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              LowerClampDamage;                                         // 0x000C(0x0004) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	DWORD64                                            BallisticCurve;                                           // 0x0010(0x0008) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              RangeModifier;                                            // 0x0018(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              ReferenceDistance;                                        // 0x001C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              TravelDistanceMax;                                        // 0x0020(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned char                                      bUseMaxDamageDistance : 1;                                // 0x0024(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0025(0x0003) MISSED OFFSET
	float                                              SimulationSubstepTime;                                    // 0x0028(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              VDragCoefficient;                                         // 0x002C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              BDS;                                                      // 0x0030(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned char                                      bUseAdvancedBallistics : 1;                               // 0x0034(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned char                                      bCanProduceCrackSound : 1;                                // 0x0035(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned char                                      IsPenetrable : 1;                                         // 0x0036(0x0001) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x1];                                       // 0x0037(0x0001) MISSED OFFSET
	DWORD64                                            DamageType;                                               // 0x0038(0x0008) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned char                                      bIsTrajectoryReplicationEnabled : 1;                      // 0x0040(0x0001) (CPF_Edit, CPF_DisableEditOnInstance)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0041(0x0003) MISSED OFFSET
	float                                              WeaponSpread;                                             // 0x0044(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
};
struct FLoaclWeaponData
{
	BOOL WeaponMap;
	BOOL WeaponHold;
	PCSTR WeaponName;
	ULONG WeaponBullet;
	FLOAT WeaponInitialSpeed;
	FLOAT TrajectoryGravityZ;
	FWeaponTrajectoryConfig TrajectoryConfig;
};