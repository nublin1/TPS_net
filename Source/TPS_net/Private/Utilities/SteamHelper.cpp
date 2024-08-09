// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/SteamHelper.h"
#include "Runtime/Engine/Public/EngineGlobals.h"

#include "AdvancedSteamFriendsLibrary.h"
#include "OnlineSubsystem.h"

/*
FUniqueNetIdRepl USteamHelper::GetSteamID()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get(STEAM_SUBSYSTEM); // "STEAM_SUBSYSTEM" typically defined as "Steam"
    if (!OnlineSubsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("OnlineSubsystem not found!"));
        return nullptr;
    }

    // Get the first local player from the world context
    UWorld* World = GEngine->GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("World not found!"));
        return nullptr;
    }

    const ULocalPlayer* LocalPlayer = World->GetFirstLocalPlayerFromController();
    if (!LocalPlayer)
    {
        UE_LOG(LogTemp, Error, TEXT("LocalPlayer not found!"));
        return nullptr;
    }

    auto UserId = LocalPlayer->GetPreferredUniqueNetId();
    if (!UserId.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("UserId not valid!"));
        return nullptr;
    }

    return UserId;
}

UTexture2D* USteamHelper::GetSteamFriendAvatar(const uint64 UniqueNetId, EPlayerAvatarSize PlayerAvatarSize)
{	
	uint32 Width = 0;
	uint32 Height = 0;

	if (SteamAPI_Init())
	{
		//Getting the PictureID from the SteamAPI and getting the Size with the ID
		//virtual bool RequestUserInformation( CSteamID steamIDUser, bool bRequireNameOnly ) = 0;
		
		int Picture = 0;
		
		switch(PlayerAvatarSize)
		{
		case EPlayerAvatarSize::PlayerAvatar_Small: Picture = SteamFriends()->GetSmallFriendAvatar(UniqueNetId); break;
		case EPlayerAvatarSize::PlayerAvatar_Medium: Picture = SteamFriends()->GetMediumFriendAvatar(UniqueNetId); break;
		case EPlayerAvatarSize::PlayerAvatar_Large: Picture = SteamFriends()->GetLargeFriendAvatar(UniqueNetId); break;
		default: break;
		}

		if (Picture == -1)
		{
			return nullptr;
		}

		SteamUtils()->GetImageSize(Picture, &Width, &Height);

		if (Width > 0 && Height > 0)
		{
			//Creating the buffer "oAvatarRGBA" and then filling it with the RGBA Stream from the Steam Avatar
			uint8 *oAvatarRGBA = new uint8[Width * Height * 4];


			//Filling the buffer with the RGBA Stream from the Steam Avatar and creating a UTextur2D to parse the RGBA Steam in
			SteamUtils()->GetImageRGBA(Picture, (uint8*)oAvatarRGBA, 4 * Height * Width * sizeof(char));
			
			//UTexture2D* Avatar = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
			UTexture2D* Avatar = UTexture2D::CreateTransient(Width, Height, PF_R8G8B8A8);
			// Switched to a Memcpy instead of byte by byte transer
			uint8* MipData = (uint8*)Avatar->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(MipData, (void*)oAvatarRGBA, Height * Width * 4);
			Avatar->GetPlatformData()->Mips[0].BulkData.Unlock();

			// Original implementation was missing this!!
			// the hell man......
			delete[] oAvatarRGBA;

			//Setting some Parameters for the Texture and finally returning it
			Avatar->GetPlatformData()->SetNumSlices(1);
			Avatar->NeverStream = true;
			//Avatar->CompressionSettings = TC_EditorIcon;

			Avatar->UpdateResource();

			//TextureCacheMap.Add(UniqueNetId, Avatar);
			return Avatar;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Bad Height / Width with steam avatar!"));
		}
		
		return nullptr;
	}
	return nullptr;
}
*/
