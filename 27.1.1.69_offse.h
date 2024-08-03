constexpr auto Offset_GUObjects = 0x09B9A5F0;
constexpr auto Offset_GWorld = 0x09BDB918;
constexpr auto Offset_XenuineDecrypt = 0x08460F28;
constexpr auto Offset_GNames = 0x09DE7B58;
constexpr auto Offset_ElementsPerChunk = 0x4098;

constexpr auto Offset_ObjID = 0x0018;
constexpr auto Offset_XorKey1 = 0x1635779C;
constexpr auto Offset_XorKey2 = 0xA9614873;
constexpr auto Offset_Value = 0x0006;
constexpr auto Offset_UsingRor = 0x0001;


namespace DecryptOuter{
constexpr unsigned long long xor_key_1 = 0xB5578897B823ED2A;
constexpr unsigned long long xor_key_2 = 0x54C59F447BE8BC81;
constexpr unsigned char offset = 0x10;
constexpr unsigned char rval = 0x01;
constexpr bool IsingRor = false;
};


namespace DecryptClass{
constexpr unsigned long long xor_key_1 = 0xF1940B86B5EDD9CD;
constexpr unsigned long long xor_key_2 = 0x3E111025D4F64C8C;
constexpr unsigned char offset = 0x28;
constexpr unsigned char rval = 0x15;
constexpr bool IsingRor = true;
};


namespace DecryptNameIndex{
constexpr unsigned int xor_key_1 = 0x1635779C;
constexpr unsigned int xor_key_2 = 0xA9614873;
constexpr unsigned char offset = 0x18;
constexpr unsigned char rval = 0x06;
constexpr bool IsingRor = true;
};


namespace DecryptNameNumber{
constexpr unsigned int xor_key_1 = 0xE1124873;
constexpr unsigned int xor_key_2 = 0x61A9779C;
constexpr unsigned char offset = 0x1C;
constexpr unsigned char rval = 0x02;
constexpr bool IsingRor = false;
};

//-------------------------------------------

struct {
uint32_t ArrayDim = 0x0038;
uint32_t ElementSize = 0x003C;
uint32_t Offset = 0x0058;
uint32_t PropertyFlags = 0x0040;
uint32_t Size = 0x0080;
} UProperty;

struct {
uint32_t FunctionFlags = 0x00EC;
uint32_t Function = 0x0110;
} UFunction;

struct {
uint32_t SuperStruct = 0x0048;
uint32_t Children = 0x0070;
uint32_t PropertiesSize = 0x0088;
} UStruct;

//-------------------------------------------


constexpr auto Offset_CurrentLevel = 0x0158;
constexpr auto Offset_Actors = 0x0130;
constexpr auto Offset_GameInstance = 0x0160;
constexpr auto Offset_LocalPlayers = 0x0060;
constexpr auto Offset_PlayerController = 0x0038;
constexpr auto Offset_AcknowledgedPawn = 0x0488;
constexpr auto Offset_PlayerCameraManager = 0x04A8;
constexpr auto Offset_LocalPlayersPTR = 0x09D20FB0;

// Class Engine.Controller
constexpr auto Offset_ControlRotation = 0x045C;
constexpr auto Offset_StateName = 0x0408;

//World
constexpr auto Offset_OriginLocation = 0x09B4;

constexpr auto Offset_LineTraceSingle = 0x064B5C74;
constexpr auto Offset_CurrentBuildNumber = 0x09A08CA0;
constexpr auto Offset_GameWindowSize = 0x099AA500;
constexpr auto Offset_CheckTab = 0x09E1D1B6;
constexpr auto Offset_IsLobbyReady = 0x099DBA38;

constexpr auto Offset_InactiveStateInputComponent = 0x06C8;
constexpr auto Offset_MyHUD = 0x04A0;
constexpr auto Offset_WidgetStateMap = 0x0500;
constexpr auto Offset_BlockInputWidgetList = 0x0568;
constexpr auto Offset_TrainingMapGrid = 0x06C0;
constexpr auto Offset_SelectMinimapSizeIndex = 0x05C0;
constexpr auto Offset_Slot = 0x0038;
constexpr auto Offset_LayoutData = 0x0040;
constexpr auto Offset_Visibility = 0x00A9;

//TslCharacter
constexpr auto Offset_PlayerState = 0x0438;
constexpr auto Offset_PlayerName = 0x0440;
constexpr auto Offset_PlayerStatistics = 0x0A74;
constexpr auto Offset_PartnerLevel = 0x0656;
constexpr auto Offset_ClanInfo = 0x0C28;
constexpr auto Offset_bIsInAircraft = 0x0C60;
constexpr auto Offset_PubgIdData = 0x0E78;
constexpr auto Offset_DamageDealtOnEnemy = 0x0A80;
constexpr auto Offset_SpectatedCount = 0x1310;
constexpr auto Offset_Health = 0x0990;
constexpr auto Offset_GroggyHealth = 0x3460;
constexpr auto Offset_CharacterState = 0x0F58;
constexpr auto Offset_Team = 0x1B18;
constexpr auto Offset_LastTeamNum = 0x1B20;
constexpr auto Offset_CharacterName = 0x0DC0;
constexpr auto Offset_AimOffsets = 0x1680;

constexpr auto Offset_Mesh = 0x0480;
constexpr auto Offset_StaticMesh = 0x0AD0;

constexpr auto Offset_LastSubmitTime = 0x0758;
constexpr auto Offset_LastRenderTime = 0x075C;
constexpr auto Offset_LastRenderTimeOnScreen = 0x0760;

//Actor
constexpr auto Offset_OwnedComponents = 0x0390;
constexpr auto Offset_RootComponent = 0x0198;

//SceneComponent
constexpr auto Offset_AttachParent = 0x0218;
constexpr auto Offset_RelativeLocation = 0x037C;
constexpr auto Offset_ComponentVelocity = 0x0234;
constexpr auto Offset_ComponentToWorld = 0x02F0;
constexpr auto Offset_ComponentLocation = 0x0300;

//PlayerCameraManager
constexpr auto Offset_CameraLocation = 0x0A74;
constexpr auto Offset_CameraRotation = 0x0A94;
constexpr auto Offset_CameraFov = 0x0AA8;

//Package
constexpr auto Offset_ItemPackage = 0x0588;

//Items
constexpr auto Offset_ItemTableRowBase = 0x00B0;
constexpr auto Offset_ItemID = 0x0268;
constexpr auto Offset_DroppedItem = 0x0440;
constexpr auto Offset_DroppedItemGroup_UItem = 0x0728;

//ATslWeapon
constexpr auto Offset_WeaponProcessor = 0x08F0;
constexpr auto Offset_EquippedWeapons = 0x0208;
constexpr auto Offset_CurrentWeaponIndex = 0x0311;
constexpr auto Offset_WeaponTrajectoryData = 0x1038;
constexpr auto Offset_TrajectoryGravityZ = 0x0F9C;
constexpr auto Offset_TrajectoryConfig = 0x0108;
constexpr auto Offset_FloatCurves = 0x0038;

//CharacterMovement
constexpr auto Offset_CharacterMovement = 0x0558;
constexpr auto Offset_Acceleration = 0x03A8;
constexpr auto Offset_MaxAcceleration = 0x0308;
constexpr auto Offset_LastUpdateVelocity = 0x03D0;

constexpr auto Offset_AnimScriptInstance = 0x0C70;
constexpr auto Offset_ControlRotation_CP = 0x07FC;
constexpr auto Offset_RecoilADSRotation_CP = 0x09FC;
constexpr auto Offset_LeanLeftAlpha_CP = 0x0E04;
constexpr auto Offset_LeanRightAlpha_CP = 0x0E08;
constexpr auto Offset_bIsScoping_CP = 0x0D26;

constexpr auto Offset_VehicleRiderComponent = 0x1DC0;
constexpr auto Offset_SeatIndex = 0x0230;
constexpr auto Offset_LastVehiclePawn = 0x0270;
constexpr auto Offset_ReplicatedMovement = 0x0060;

//UTslVehicleCommonComponent
constexpr auto Offset_VehicleCommonComponent_Floating = 0x04D0;
constexpr auto Offset_VehicleCommonComponent_Wheeled = 0x0C08;
constexpr auto Offset_VehicleHealth = 0x02D8;
constexpr auto Offset_VehicleHealthMax = 0x02DC;
constexpr auto Offset_VehicleFuel = 0x02E0;
constexpr auto Offset_VehicleFuelMax = 0x02E4;