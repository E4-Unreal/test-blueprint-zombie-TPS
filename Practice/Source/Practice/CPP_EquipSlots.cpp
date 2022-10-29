// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EquipSlots.h"

// Sets default values
ACPP_EquipSlots::ACPP_EquipSlots()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponNum = 2;
	EquipNum = 2;
	WeaponCursor = 0;
}

// Called when the game starts or when spawned
void ACPP_EquipSlots::BeginPlay()
{
	Super::BeginPlay();
	SocketNames.SetNum(TotalNum);
	EquipSlots.SetNum(TotalNum);
}

// Called every frame
void ACPP_EquipSlots::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_EquipSlots::PostInitProperties()
{
	Super::PostInitProperties();
	CalTotalNum();
}

void ACPP_EquipSlots::PostEditChangeProperty(FPropertyChangedEvent& ProperyChangedEvent)
{
	CalTotalNum();
	Super::PostEditChangeProperty(ProperyChangedEvent);
}

void ACPP_EquipSlots::CalTotalNum()
{
	TotalNum = WeaponNum + EquipNum;
}

void ACPP_EquipSlots::CheckType(int32 Offset, int32 Num, bool& IsEmpty, int32& Index)
{
	IsEmpty = false;
	for (int i = Offset; i < Num - 1; i++)
	{
		if (EquipSlots[i].Name == "None")
		{
			IsEmpty = true;
			Index = i;
			break;
		}
	}
}

void ACPP_EquipSlots::CheckNewEquip(FItemStruct EquipInfo, bool& IsEmpty, int32& Index)
{
	IsEmpty = false;
	int32 Offset = 0;

	switch (EquipInfo.EquipType)
	{
		case EWeaponType::Weapon:
			CheckType(Offset, WeaponNum, IsEmpty, Index);
			Offset += WeaponNum;
			break;
		case EWeaponType::Equip:
			CheckType(Offset, EquipNum, IsEmpty, Index);
			Offset += EquipNum;
			break;
	}

	if (IsEmpty)
	{
		EquipInfo.SpawnedActor = SpawnNewEquip(EquipInfo);
		EquipSlots[Index] = EquipInfo;
	}
}

AActor* ACPP_EquipSlots::SpawnNewEquip(FItemStruct EquipInfo)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	FRotator spawnRotator;
	FVector spawnLocation = GetActorLocation();

	UWorld* world = GetWorld();

	if (world)
	{
		return world->SpawnActor<AActor>(EquipInfo.SpawnedClass, spawnLocation, spawnRotator, spawnParams);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "SpawnNewEquip Err: GetWorld() failed");
		return NULL;
	}
}

