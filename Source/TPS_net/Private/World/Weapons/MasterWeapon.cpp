// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Weapons/MasterWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/WeaponBase.h"


AMasterWeapon::AMasterWeapon(): WeaponBaseRef(nullptr), SkeletalMeshWeapon(nullptr)
{
	bReplicates = true;
	bReplicateUsingRegisteredSubObjectList = true;

	
	// Initialize the SkeletalMeshWeapon component
	SkeletalMeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(SkeletalMeshWeapon);

	/*// Initialize the TargetPoint component
	TargetPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetPoint"));
	TargetPoint->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TargetPoint->SetWorldLocation(FVector(0, 1000.0f, 10.0f));
	TargetPoint->SetWorldScale3D(FVector(0.1f));
	//TargetPoint->RegisterComponent();
	TargetPoint->AttachToComponent(SkeletalMeshWeapon, FAttachmentTransformRules::KeepRelativeTransform);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereMesh.Succeeded())
	{
		TargetPoint->SetStaticMesh(SphereMesh.Object);
	}*/
	
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
				WeaponBaseRef->SetWeaponType(WData->WeaponType);

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

void AMasterWeapon::OnRep_WeaponBaseRef()
{
	//UE_LOG(LogTemp, Warning, TEXT(" AMasterWeapon WeaponBaseRef is replicate"));
	UpdateVisual();
}

void AMasterWeapon::OnRep_RoundsInMagazine() const
{
	if (OnCompleteReloadDelegate.IsBound())
		OnCompleteReloadDelegate.Broadcast(RoundsInMagazine);
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
}

void AMasterWeapon::PlayShootEffect(UParticleSystem* ParticleSystem, FName SocketName)
{
	if (!ParticleSystem || !SkeletalMeshWeapon) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid ParticleSystem or SkeletalMeshWeapon"));
		return;
	}

	if (HasAuthority())
	{
		PlayShootEffect_Multicast(ParticleSystem, SocketName);
	}
	else
	{
		PlayShootEffect_Server(ParticleSystem, SocketName);
	}
	
}

void AMasterWeapon::PlayShootEffect_Server_Implementation(UParticleSystem* ParticleSystem, FName SocketName)
{
	PlayShootEffect_Multicast(ParticleSystem, SocketName);
}

void AMasterWeapon::PlayShootEffect_Multicast_Implementation(UParticleSystem* ParticleSystem, FName SocketName)
{
	UParticleSystemComponent* ParticleComponent = UGameplayStatics::SpawnEmitterAttached(
		ParticleSystem,                          // Шаблон эмиттера
		SkeletalMeshWeapon,                      // К какому компоненту прикрепляем
		SocketName,                              // Имя сокета, куда прикрепить
		FVector::ZeroVector,                     // Локальная позиция
		FRotator::ZeroRotator,                   // Локальная ротация
		FVector(1.0f, 1.0f, 1.0f),               // Масштаб
		EAttachLocation::KeepRelativeOffset,     // Тип привязки
		true                                     // Автоматическое уничтожение
	);

	if (!ParticleComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn emitter!"));
	}
}

void AMasterWeapon::DecreaseRoundsInMagazine()
{
	if (HasAuthority())
		RoundsInMagazine--;
	else
		ServerDecreaseRoundsInMagazine();
}

void AMasterWeapon::ServerDecreaseRoundsInMagazine_Implementation()
{
	RoundsInMagazine--;
}

void AMasterWeapon::Reload()
{
	if (HasAuthority())
	{
		RoundsInMagazine = WeaponBaseRef->GetCharacteristicsOfTheWeapon().MagazineSize;
		OnRep_RoundsInMagazine();
	}
	else
	{
		ServerReload();
	}
}

void AMasterWeapon::ServerReload_Implementation()
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
	
	
	//UE_LOG(LogTemp, Log, TEXT("Fire Mode: %d"), static_cast<int>(SelectedFireMode));
}

void AMasterWeapon::SetWeaponBaseRef(UWeaponBase* _WeaponBase)
{
	if (!_WeaponBase)
		return;

	if(IsValid(WeaponBaseRef))
	{
		RemoveReplicatedSubObject(WeaponBaseRef->GetSelectedAmmoData());
		RemoveReplicatedSubObject(WeaponBaseRef);
	}
	WeaponBaseRef = _WeaponBase;

	AddReplicatedSubObject(WeaponBaseRef);
	AddReplicatedSubObject(WeaponBaseRef->GetSelectedAmmoData());
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
	
	DOREPLIFETIME(AMasterWeapon, WeaponBaseRef);
	DOREPLIFETIME(AMasterWeapon, RoundsInMagazine);
	DOREPLIFETIME(AMasterWeapon, SelectedFireMode);
}
