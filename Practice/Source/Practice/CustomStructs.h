// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	FName EquipType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxCount;
};