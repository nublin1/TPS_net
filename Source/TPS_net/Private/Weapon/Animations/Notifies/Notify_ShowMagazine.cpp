// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Animations/Notifies/Notify_ShowMagazine.h"

FString UNotify_ShowMagazine::GetNotifyName_Implementation() const
{
	FString Loc = (Location == EMagazineLocation::InWeapon) ? TEXT("Weapon") : TEXT("Hand");
	FString Act = (Action == EMagazineVisibilityAction::Hide) ? TEXT("Hide") : TEXT("Show");
	return FString::Printf(TEXT("%s Magazine (%s)"), *Act, *Loc);
}
