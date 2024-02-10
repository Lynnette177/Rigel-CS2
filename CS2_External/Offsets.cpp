#include "Offsets.h"

DWORD64 SearchOffsets(std::string Signature, DWORD64 ModuleAddress)
{
	std::vector<DWORD64> TempAddressList;
	DWORD64 Address = 0;
	DWORD Offsets = 0;

	TempAddressList = ProcessMgr.SearchMemory(Signature, ModuleAddress, ModuleAddress + 0x4000000);

	if (TempAddressList.size() <= 0)
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD>(TempAddressList.at(0) + 3, Offsets))
		return 0;

	Address = TempAddressList.at(0) + Offsets + 7;
	return Address;
}

bool Offset::UpdateOffsets()
{
	Offset::EntityList = 0x17C18E0;//TempAddress - ClientDLL;
	Offset::LocalPlayerController = 0x1810EE0;//TempAddress - ClientDLL;
	Offset::Matrix = 0x1820100;
	Offset::GlobalVars = 0x16BDE28;
	Offset::ViewAngle = 0x1880D60;
	Offset::LocalPlayerPawn = 0x16C8ED8;
	Offset::ForceJump = 0x16C2340;
	return true;
}