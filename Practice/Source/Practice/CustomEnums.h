// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PRACTICE_API CustomEnums
{
public:
	CustomEnums();
	~CustomEnums();
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Weapon UMETA(DisplayName = "Weapon"),
	Equip UMETA(DisplayName = "Equip")
};