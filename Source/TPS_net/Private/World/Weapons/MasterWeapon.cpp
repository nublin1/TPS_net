// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Weapons/MasterWeapon.h"

#include "Net/UnrealNetwork.h"
#include "Weapon/WeaponBase.h"


AMasterWeapon::AMasterWeapon(): WeaponBaseRef(nullptr), SkeletalMeshWeapon(nullptr), TargetPoint(nullptr)
{
		
	// Initialize the SkeletalMeshWeapon component
	SkeletalMeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(SkeletalMeshWeapon);

	// Initialize the TargetPoint component
	TargetPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetPoint"));
	TargetPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TargetPoint->SetWorldLocation(FVector(0, 1000.0f, 10.0f));
	TargetPoint->SetWorldScale3D(FVector(0.1f));
	TargetPoint->SetupAttachment(SkeletalMeshWeapon);
	//TargetPoint->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMesh.Succeeded())
	{
		TargetPoint->SetStaticMesh(SphereMesh.Object);
	}
}

void AMasterWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitWeaponBaseData();
}

void AMasterWeapon::InitWeaponBaseData()
{
	if (HasAuthority()) 
	{
		if (WeaponTable && !StartingWeapon.IsNone())
		{
			const FWeaponData* WData = WeaponTable->FindRow<FWeaponData>(StartingWeapon, StartingWeapon.ToString());
			if (WData)
			{
				WeaponBaseRef = NewObject<UWeaponBase>(this, UWeaponBase::StaticClass());
				WeaponBaseRef->SetID(WData->Name);
				WeaponBaseRef->SetBulletMode(WData->BulletMode);
				WeaponBaseRef->SetCharacteristicsOfTheWeapon(WData->CharacteristicsOfTheWeapon);
				WeaponBaseRef->SetWeaponAssetData(WData->WeaponAssetData);
				WeaponBaseRef->SetWeaponType(WData->HolsterType);

				SelectedFireMode = WData->CharacteristicsOfTheWeapon.AvailableShootingModes[0];
				Reload();
				UpdateVisual();
			}
		}
	}
}

void AMasterWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AMasterWeapon::UpdateVisual() 
{
	if (!WeaponBaseRef)
	{
		UE_LOG(LogTemp, Warning, TEXT(" AMasterWeapon WeaponBaseRef is null"));
		return;
	}

	SkeletalMeshWeapon->SetSkeletalMesh(WeaponBaseRef->GetWeaponAssetData().SkeletalMesh);

	if (WeaponBaseRef->GetWeaponAssetData().AnimationBlueprint)
		SkeletalMeshWeapon->SetAnimInstanceClass(
			WeaponBaseRef->GetWeaponAssetData().AnimationBlueprint->GetAnimBlueprintGeneratedClass());
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load animation class: %s"),
		       *WeaponBaseRef->GetWeaponAssetData().AnimationBlueprint->GetBlueprintClass()->GetName());
	}

	//FString AnimClassName = TEXT("WeaponAnimClass_C");		
	//UClass* AnimInstanceClass = FindObject<UClass>(ANY_PACKAGE, *AnimClassName);
	//if (AnimInstanceClass)
	{
		//SkeletalMeshWeapon->SetAnimInstanceClass(AnimInstanceClass);
	}
	//else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Failed to load animation class: %s"), *AnimClassName);
	}
}

void AMasterWeapon::Reload()
{
	RoundsInMagazine = WeaponBaseRef->GetCharacteristicsOfTheWeapon().MagazineSize;
}

void AMasterWeapon::SwitchFireMode()
{
	if (SelectedFireMode == EFireMode::None)
	{
		SelectedFireMode = WeaponBaseRef->GetCharacteristicsOfTheWeapon().AvailableShootingModes[0];
		return;
	}

	int32 CurrentIndex = WeaponBaseRef->GetCharacteristicsOfTheWeapon().AvailableShootingModes.IndexOfByKey(SelectedFireMode);
	CurrentIndex++;
	if (CurrentIndex < WeaponBaseRef->GetCharacteristicsOfTheWeapon().AvailableShootingModes.Num())
	{
		SelectedFireMode = WeaponBaseRef->GetCharacteristicsOfTheWeapon().AvailableShootingModes[CurrentIndex];
	}
	else
		SelectedFireMode = WeaponBaseRef->GetCharacteristicsOfTheWeapon().AvailableShootingModes[0];
	
	
	UE_LOG(LogTemp, Log, TEXT("Fire Mode: %d"), static_cast<int>(SelectedFireMode));
}

void AMasterWeapon::SetWeaponTableAndName(UDataTable* Table, FName Name)
{
	//if (!Table)
	//	UE_LOG(LogTemp, Log, TEXT("Table null: "));
	//WeaponTable = Table;
	StartingWeapon = Name;
}

void AMasterWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AMasterWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
}
