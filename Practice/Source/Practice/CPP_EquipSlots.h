// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomStructs.h"
#include "CustomEnums.h"
#include "CPP_EquipSlots.generated.h"

UCLASS()
class PRACTICE_API ACPP_EquipSlots : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_EquipSlots();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipSlots")
	int32 WeaponNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipSlots")
	int32 EquipNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipSlots")
	int32 WeaponCursor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipSlots")
	TArray<FItemStruct> EquipSlots;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "EquipSlots")
	int32 TotalNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipSlots")
	TArray<FName> SocketNames;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitProperties() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& ProperyChangedEvent) override;

	void CalTotalNum();
	UFUNCTION(BlueprintCallable, Category = "EquipSlots")
	void CheckType(int32 Offset, int32 Num, bool& IsEmpty, int32& Index);
	UFUNCTION(BlueprintCallable, Category = "EquipSlots")
	void CheckNewEquip(FItemStruct EquipInfo, bool& IsEmpty, int32& Index);
	UFUNCTION(BlueprintCallable, Category = "EquipSlots")
	AActor* SpawnNewEquip(FItemStruct EquipInfo);

};
