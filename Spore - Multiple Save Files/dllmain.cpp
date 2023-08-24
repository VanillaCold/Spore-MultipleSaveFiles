// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "SwapSaveCheat.h"

void Initialize()
{
	// Just add the new cheat.
	CheatManager.AddCheat("setSaveFile", new SwapSaveCheat());
}

void Dispose()
{
	// This method is called when the game is closing
}

static_detour(SetSaveDetour, Resource::Database* (Resource::SaveAreaID))
{
	Resource::Database* detoured(Resource::SaveAreaID area) //Detour the function that gets a database from a save area code
	{
		if (area == Resource::SaveAreaID::GamesGame0 && SwapSaveCheat::saveDatabase != nullptr) //Check if the save area is Game0; if it is, and we have a specified override, we do stuff.
		{
			return SwapSaveCheat::saveDatabase.get(); //Instead of returning the original value, we return the custom database pointer.
		}

		return original_function(area); //If we can't override it for any reason, return the original function's return value instead.
	}
};

void AttachDetours()
{
	//Attach the detour to the GetSaveArea function.
	SetSaveDetour::attach(GetAddress(Resource::Paths, GetSaveArea));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

