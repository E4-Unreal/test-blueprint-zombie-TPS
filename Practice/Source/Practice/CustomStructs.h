// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomEnums.h"
#include "CustomStructs.generated.h"

/**
 * 
 */
class PRACTICE_API CustomStructs
{
public:
	CustomStructs();
	~CustomStructs();
};

USTRUCT(Atomic, BlueprintType)
struct FItemStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> DroppedClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> SpawnedClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* SpawnedActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanEquip;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType EquipType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxCount;
};

USTRUCT(Atomic, BlueprintType)
struct FDeathInfoStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AController* Instigator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> KilledClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HeadShot;
};

USTRUCT(Atomic, BlueprintType)
struct FPlayRecordStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AController* Instigator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int KillCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HeadShot;
};