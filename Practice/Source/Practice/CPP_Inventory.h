// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomStructs.h"
#include "CPP_Inventory.generated.h"

UCLASS()
class PRACTICE_API ACPP_Inventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Inventory();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaxSlots;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<FItemStruct> Inventory;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitProperties() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& ProperyChangedEvent) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PrintInfo();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Add(FItemStruct Item);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Set(int32 Index, FItemStruct Item);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Remove(int32 Index);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Get(int32 Index, bool& IsEmpty, FItemStruct& Item);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SearchByName(FName Name, bool& IsFind, TArray<int32>& Indices, TArray<FItemStruct>& Items);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SearchByItemStruct(FItemStruct ItemStruct, bool& IsFind, TArray<int32>& Indices, TArray<FItemStruct>& Items);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void CheckEmptySlot(bool& IsEmpty);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddNewItem(FItemStruct ItemStruct, bool& IsSucceed, FItemStruct& _ItemStuct);
};
